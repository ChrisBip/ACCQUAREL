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
#include "xmlAtomParser.h"
#include <xmlDPoint3Parser.h>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// M�thode pour trouver le nom du tag qui va contenir toutes les informations
// sur l'�lement chimique.
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const string xmlAtomParser::getAtomTagName(void)
{
	return "Atom";
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// M�thode pour trouver le nom du tag qui va contenir toutes les informations
// sur l'�lement chimique.
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const string xmlAtomParser::getChemicalElementTagName(void)
{
	return "ChemicalElement";
}


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// M�thode pour trouver le nom du tag qui contient la cl� de l'�lement chimique.
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const string xmlAtomParser::getChemicalElementKeyTagName(void)
{
	return "ChemicalElementKey";
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// M�thode pour retrouver le nom du tag qui contient le nombre de neutrons 
// de l'�l�ment chimique.
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const string xmlAtomParser::getNbrOfNeutronsTagName(void)
{
	return "NbrOfNeutrons";
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Le nom de la balise qui contient les informations sur le positionnement de l'atome.
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const string xmlAtomParser::getAtomCenterTagName(void)
{
	return "AtomCenter";
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Le nom de la balise qui contient les information � propos des unit�es des atomes.
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const string xmlAtomParser::getAtomCenterUnitTagName(void)
{
	return "DistanceUnit";
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Constructor of the class.
//
// @param rootAtomElement the root node that contains all informations about the atom that is gone be read.
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
xmlAtomParser::xmlAtomParser(void)
{
	;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Constructor of the class.
//
// @param rootAtomElement the root node that contains all informations about the atom that is gone be read.
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
xmlAtomParser::xmlAtomParser(DOMElement * rootAtomElement)
{
	setRootElement(rootAtomElement);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Destructor of the class.
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
xmlAtomParser::~xmlAtomParser(void)
{
	;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// M�thode pour construire totalement un atome.
//
// @return l'atome initialis� � partir de donn�es du document XML.
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
atom xmlAtomParser::getAtom(void) const
{
	atom a;	
	pair<dpoint<3>,atom::distanceUnit> atomCenter;
	pair<chemicalElement,int> atomChemicalElement;
	
	////////////////////////////////////////////////////////////////////////
	// On commence par l'�l�ment chimique sur lequel
	// s'appuie l'atome.
	// 
	// - R�cup�ration des informations concernant l'�l�ment chimique.
	// - On recopie l'�l�ment chipmique trouv�.
	// - On recopie le nombre de neutrons trouv�.
	////////////////////////////////////////////////////////////////////////
	atomChemicalElement = getAtomChemicalElement();
	a.setChemicalElement(atomChemicalElement.first);
	a.setNbrOfNeutrons(atomChemicalElement.second);

	////////////////////////////////////////////////////////////////////////
	// On G�re ensuite ce qui a trait � la positon de l'atome.
	//
	// - R�cup�ration des information sous forme simple.
	// - On recopie la position.
	// - On recopie l'unit�.
	/////////////////////////////////////////////////////////////////////////
	atomCenter = getAtomCenter();
	a.setPosition(atomCenter.first);
	a.setDistanceUnit(atomCenter.second);
	return a;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// M�thode pour r�cup�rer les informations qui concerne l'�l�ment chimique constituant 
// l'atome.
//
// @return the key for the chemical element. 
//
// @warning if the chemical element referecence is not found then an empty string is returned.	 
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
pair<chemicalElement,int> xmlAtomParser::getAtomChemicalElement(void) const
{
	DOMElement * chemicalElementElement;
	DOMNode * chemicalElementKeyNode;
	DOMNode * chemicalElementNbrOfNeutronsNode;
	pair<chemicalElement,int> atomChemicalElement;
	string chemicalElementKey;

	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// On commence par r�cup�rer la partie du document qui correspond � la description 
	// de l'�l�ment chimique. En fait cette partie est comprise entre les balises <ChemicalElement>
	// et </ChemicalElement>.
	// 
	// - Lorsque l'on ne trouve pas cela on va interrompre le programme car nous avons quelque
	// chose qui ne va pas.
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	chemicalElementElement = (DOMElement *)getElementByTagName(getChemicalElementTagName());

	if(chemicalElementElement == NULL) {
		cerr << "Error : in pair<chemicalElement,int> xmlAtomParser::getAtomChemicalElement(void) const" << endl;
		cerr << "Error : no chemical element was defined." << endl; 
		cerr << "Error : atoms need a chemical element description to be well defined. Aborting." << endl;
		exit(1);
	}

	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// Ensuite on r�cup�re les donn�es pour l'�l�ment chimique � proprement parler.
	// 
	// - On r�cup�re la cl� de l'�l�ment chimique.
	// - A l'aide de la base de donn�es des �l�ments chimiques on compl�te les informations
	// qui le concerne.
	// 
	// - Lorsque la ck� de l'�l�ment chimique n'est pas d�finie dans le document XML on 
	// arr�te le programme.
	// - Lorsque l'�l�ment chimique n'a pas �t� trouv� dans la base de donn�es on arrete le 
	// programme.
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	chemicalElementKeyNode = getElementByTagName(chemicalElementElement , getChemicalElementKeyTagName());

	if(chemicalElementKeyNode == NULL) {
		cerr << "Error : in pair<chemicalElement,int> xmlAtomParser::getAtomChemicalElement(void) const" << endl;
		cerr << "Error : no chemical element key was defined." << endl; 
		cerr << "Error : atoms need a chemical element key to be well defined. Aborting." << endl;	
		exit(1);
	}

	chemicalElementKey = getNodeStringValue(chemicalElementKeyNode , xmlParser::Remove_White_Space);
	atomChemicalElement.first = xmlChemicalElementsDataBaseInterface::getChemicalElement(chemicalElementKey);

	if(atomChemicalElement.first.empty()) {
		cerr << "Error : in pair<chemicalElement,int> xmlAtomParser::getAtomChemicalElement(void) const" << endl;
		cerr << "Error : no chemical element with key \"" << chemicalElementKey << "\" was found in the data base" << endl; 
		cerr << "Error : please check file:///$ASPICROOT/documentation/chemicalElements.html for more informations." << endl;	
		exit(1);
	}

	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// Enfin on r�cup�re le nombre de neutrons associ� � cet �l�ment chimique.
	// 
	// - Lorsque le nombre de neutrons n'est pas d�fini dans le document XML on renvoie l'isotope 
	// le plus probable.
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	chemicalElementNbrOfNeutronsNode = getElementByTagName(chemicalElementElement , getNbrOfNeutronsTagName());

	if(chemicalElementNbrOfNeutronsNode == NULL) {
		atomChemicalElement.second = atomChemicalElement.first.getNbrOfNeutrons4Isotope(0);
	} else {
		atomChemicalElement.second = getNodeIntegerValue(chemicalElementNbrOfNeutronsNode);
	}

	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// Pour finir on renvoie les informations r�cup�r�es dans le fichier.
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	return atomChemicalElement;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// M�thode pour r�cup�rer les infirmations sur le centre de l'atome.
// <AtomCenter>
//	
// <Position>
//	<x> ... </x>
//	<y> ... </y>
//	<z> ... </z>
// </Position>
//
// <DistanceUnit> ... <DistanceUnit>
// </AtomCenter> 
//
// @return les information n�cessaire au centrage de l'atome, c�d une paire compos�e des coordonn�es
// du centre de l'atome et de l'unit� dans laquelle celles ci sont exprim�es.
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
pair<dpoint<3>  , atom::distanceUnit> xmlAtomParser::getAtomCenter(void) const
{
	DOMElement * atomCenterElement;
	DOMNode * unitNode;
	pair<dpoint<3> ,  atom::distanceUnit> atomCenter;
	xmlDPoint3Parser positionParser;
	

	////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// 1 - On r�cup�re la partie du document qui correspond
	// au centre de l'atome.
	//
	// Lorsque cette partie n'est pas trouv�e alors on arrete l'execution 
	// du programme car on d�fini un atome et pas un �l�ment chimique.
	////////////////////////////////////////////////////////////////////////////////////////////////////////////
	atomCenterElement =  (DOMElement *)getElementByTagName(getAtomCenterTagName());

	if(atomCenterElement == NULL) {
		cerr << "Error : in dpoint<3> xmlAtomParser::getAtomCenterPosition(void) const" << endl;
		cerr << "Error : no atom center was defined." << endl;
		cerr << "Error : atoms need a center description to be well defined. Aborting." << endl;
		exit(1);
	}
		
	///////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// 2 - Ici on r�cup�re la partie coordonn�es pour le centre de l'atome.
	//
	// - Comme c'est un dpoint<3> que cela doit contenir on cherche le fils avec la racine d'un 
	// xmlDPoint3Parser et on cr�� le parser � partir de l'�l�ment retrouv�.
	// !! Si on ne trouve pas se fils cela provoque l'arret du programme.
	//
	// - Ensuite on laisse le parser faire son travail.
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	atomCenter.first = positionParser.getDPoint3(atomCenterElement);

	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// 3 - Enfin on r�cup�re l'unit� dans laquelle sont exprim�es les coordonn�es de la position.
	//
	//  - On cherche l'�l�ment qui correspond � l'unit�. Comme ceci est optionnel lorsque l'on ne le 
	// trouve pas on renvoie l'unit� par d�faut qui est l'unit� atomique.
	// 
	// - Lorsqu'on le trouve on converti la valeur de son contenu en atom::distanceUnit.
	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	unitNode = getElementByTagName(atomCenterElement , getAtomCenterUnitTagName());

	if(unitNode == NULL) {
		atomCenter.second = atom::ATOMIC_UNIT;
	} else {
		atomCenter.second = atom::string2DistanceUnit(getNodeStringValue(unitNode , xmlParser::Remove_White_Space));		
	}

	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// 4 - Il ne reste plus qu'� renvoyer ce que nous avons trouv�.
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	return atomCenter;
}
