/* 
 * The chemics library of A.S.P.I.C. 
 * Written and directed by Fran�ois Lodier francois.lodier@gmail.com.
 *
 * Copyright (C) 2005  Fran�ois Lodier
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
 */
#include "xmlMoleculeParser.h"

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// The constructor.
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
xmlMoleculeParser::xmlMoleculeParser(void)
	: xmlParser()
{
	;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// The constructor.
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
xmlMoleculeParser::xmlMoleculeParser(DOMElement * rootElement)
	: xmlParser(rootElement)
{
	;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// The destructor.
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
xmlMoleculeParser::~xmlMoleculeParser(void)
{
	;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Method GET for the atom tag name.
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const string xmlMoleculeParser::getElementsListTagName(void)
{
	return "ElementsList";
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Method GET for the atom tag name.
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const string xmlMoleculeParser::getElementTagName(void)
{
	return "Element";
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Method GET for the basis name tag name.
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const string xmlMoleculeParser::getElementBasisKeyTagName(void)
{
	return "BasisKey";
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Method GET for the charge
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const string xmlMoleculeParser::getChargeTagName(void)
{
	return "Charge";
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Method GET for the descrition of the molecule.
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const string xmlMoleculeParser::getDescriptionTagName(void)
{
	return "Description";
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Method GET for the whole molecule
//
// En fait on a un certains nombre de choses globale � r�cup�rer et une liste de chose basisElements...
//
// Les chose globales sont  :
//	-Le nom de la mol�cule.
// -La description de la mol�cule.
// -La charge de la mol�cule.
//
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
molecule xmlMoleculeParser::getMolecule(void) const
{
	int atom , nbrOfAtoms;

	molecule m;
	
	DOMNode * moleculeNameNode;
	DOMNode * moleculeDescriptionNode;
	DOMNode * moleculeChargeNode;
	DOMNode * basisKeyNode;
	DOMNodeList * moleculeElementNodes;
	DOMElement * moleculeElementsListElement;
	DOMElement * atomElement;

	string basisKey;

	xmlAtomParser atomParser;
	
	//////////////////////////////////////////////////////////////////////////////////////////////////
	// On r�cup�re le nom de la mol�cule.
	//
	// Normalement cette information doit etre dans le tag <Name> ... </Name>, mais comme
	// cela n'est pas vital pour la suite on va laisser cette cose la optionelle.
	//
	// - Lorsque le moleculeNameNode n'a pas �t� trouv� on donne un nom qui est "".
	//////////////////////////////////////////////////////////////////////////////////////////////////
	moleculeNameNode = getElementByTagName(getNameTagName());

	if(moleculeNameNode == NULL) {
		m.setName("");
	} else {
		m.setName(getNodeStringValue(moleculeNameNode,xmlParser::Remove_White_Space));
	}
	
	//////////////////////////////////////////////////////////////////////////////////////////////////
	// On r�cup�re la description de la mol�cule.
	//
	// Normalement cette information doit etre dans le tag <Desciption> ... </Description>, mais comme
	// cela n'est pas vital pour la suite on va laisser cette cose la optionelle.
	//
	// - Lorsque le moleculeDescriptionNode n'a pas �t� trouv� on donne une description qui est "".
	//////////////////////////////////////////////////////////////////////////////////////////////////
	moleculeDescriptionNode = getElementByTagName(getDescriptionTagName());

	if(moleculeDescriptionNode == NULL) {
		m.setDescription("");
	} else {
		m.setDescription(getNodeStringValue(moleculeDescriptionNode,xmlParser::Collapse_White_Space));
	}
	
	//////////////////////////////////////////////////////////////////////////////////////////////////////
	// On r�cup�re la charge de la mol�cule.
	//
	// Normalement cette information doit etre dans le tag <Charge> ... </Charge>. Mais 
	// comme toute les mol�cules ne sont pas charg�es alors on laisse se tag optionnel.
	//
	// -Lorsque le moleculeChargeNode n'a pas �t� trouv� on donne une charge 0 � la mol�cule.
	//////////////////////////////////////////////////////////////////////////////////////////////////////
	moleculeChargeNode = getElementByTagName(getChargeTagName());
	
	if(moleculeChargeNode == NULL) {
		m.setCharge(0);
	} else {
		m.setCharge(getNodeIntegerValue(moleculeChargeNode));
	}

	//////////////////////////////////////////////////////////////////////////////////////////////////////////
	// Pour finir joyeusement nous devons r�cup�rer la liste des atomes et des bases dans lesquelles
	// ils sont repr�sent�s.
	//
	// Pour cela il faut r�cup�rer le tag <MoleculElementsList> ... <MoleculeElementsList>
	// Et en �tudier les tout les noeuds <Element> </Element>
	//
	// -Lorsque l'on ne le trouve pas cela provoque l'arret du programme.
	//
	// -Lorsque la liste des �l�ments est vide cela provoque l'arret du programme.
	///////////////////////////////////////////////////////////////////////////////////////////////////////////
	moleculeElementsListElement = (DOMElement *)getElementByTagName(getElementsListTagName());

	if(moleculeElementsListElement == NULL) {
		cerr << "Error : in molecule xmlMoleculeParser::getMolecule(void) const" << endl;
		cerr << "Error : no elements list was found in the current document." << endl;
		cerr << "Error : elements list is needed to create a molecule. Aborting" << endl;
		
		exit(1);
	}

	moleculeElementNodes = getElementsByTagName(moleculeElementsListElement,getElementTagName());

	if(moleculeElementNodes== NULL || (nbrOfAtoms = moleculeElementNodes->getLength()) <= 0) {
		cerr << "Error : in molecule xmlMoleculeParser::getMolecule(void) const" << endl;
		cerr << "Error : no element was found in the element list." << endl;
		cerr << "Error : at least one element is needed to create a molecule. Aborting" << endl;
		
		exit(1);
	}

	///////////////////////////////////////////////////////////////////////////////////////////////////////////
	// Lorsque tout c'est bien d�roul�e on met la mol�cule � la taille.
	// 
	// Normalement tout devrait se d�rouler correctement.
	///////////////////////////////////////////////////////////////////////////////////////////////////////////
	m.setNbrOfAtoms(nbrOfAtoms);
	
	//////////////////////////////////////////////////////////////////////////////////////////////////////////
	// Pour chaque atome de la liste ...
	//////////////////////////////////////////////////////////////////////////////////////////////////////////
	for(atom=0 ; atom < nbrOfAtoms ; atom++) {
	

		/////////////////////////////////////////////////////////////////////////////////////////////////////////
		// On sp�cifie la'atome de la mol�cule tel que l'on peut le lire dans le fichier XML.
		// 
		// 1 - on r�cup�re la partie de la description de l'�l�ment qui se rapporte � l'atome. 
		// 2 - on v�rifie qu'elle existe.
		// 3 - on cr�e le parser d'atome.
		// 4 - on copie la valeur lue dans la mol�cule.
		/////////////////////////////////////////////////////////////////////////////////////////////////////////
		atomElement = (DOMElement *) getElementByTagName((DOMElement *)moleculeElementNodes->item(atom) , xmlAtomParser::getAtomTagName());
	
		if(atomElement == NULL) {
			cerr << "Error : in molecule xmlMoleculeParser::getMolecule(void) const" << endl;
			cerr << "Error : no atom was found in the element " << atom << " in list." << endl;
			cerr << "Error : the atom description  is needed to create a molecule element. Aborting" << endl;		
			
			exit(1);
		}
		
		atomParser.setRootElement(atomElement);

		m.setAtom(atom , atomParser.getAtom());
	
		/////////////////////////////////////////////////////////////////////////////////////////////////////////
		// On sp�cifie la base dans laquelle est repr�sent�e l'�l�ment telle que l'on peut la lire dans le fichier XML.
		// 
		// 1 - on r�cup�re la partie de la description de l'�l�ment qui se rapporte � la base. 
		// 2 - on v�rifie qu'elle existe.
		// 3 - on r�cup�re le nom de la base
		// 4 - on copie la valeur.
		/////////////////////////////////////////////////////////////////////////////////////////////////////////
		
		basisKeyNode = getElementByTagName((DOMElement *)moleculeElementNodes->item(atom) , getElementBasisKeyTagName());
	
		if(basisKeyNode == NULL) {
			cerr << "Error : in molecule xmlMoleculeParser::getMolecule(void) const" << endl;
			cerr << "Error : no basis was found in the element " << atom << " in list." << endl;
			cerr << "Error : the basis key  is needed to create a molecule element. Aborting" << endl;				
			
			exit(1);
		}

		basisKey = getNodeStringValue(basisKeyNode , xmlParser::Remove_White_Space);


		if(basisKey.empty()) {
			cerr << "Error : in molecule xmlMoleculeParser::getMolecule(void) const" << endl;
			cerr << "Error : no basis key value was found in the basis key element " << atom << " in list." << endl;
			cerr << "Error : the basis key  is needed to create a molecule element. Aborting" << endl;				
		
			exit(1);	
		}
	
		m.setBasis4Atom(atom , xmlBasisDataBaseInterface::getBasisElement(basisKey , m.getAtom(atom).getChemicalElementKey()));
	
		if(m.getBasis4Atom(atom).empty()) {
			cerr << "Error : in molecule xmlMoleculeParser::getMolecule(void) const" << endl;
			cerr << "Error : failed to find informations about element " << m.getAtom(atom).getChemicalElementKey() << " in basis  " << basisKey << "." << endl;
			cerr << "Error : please check file:///$ASPICROOT/documentation/gaussianBasis.html to find available infomration" << endl;				
					
			exit(1);
		}
	}

	return  m;
}


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Method GET for the name tag name.
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const string xmlMoleculeParser::getNameTagName(void) 
{
	return "Name";
}
