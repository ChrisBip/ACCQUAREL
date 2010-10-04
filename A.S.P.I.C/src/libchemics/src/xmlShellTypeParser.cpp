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
#include "xmlShellTypeParser.h"
#include <xmlIPoint3Parser.h>

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Le nom du tag qui contient le nom du type de couche.
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const string xmlShellTypeParser::getShellTypeNameTagName(void)
{
	return "Name";
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Le nom du tag qui contient le nom du type de couche.
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const string xmlShellTypeParser::getShellTypeKeyAttributeName(void)
{
	return "ShellTypeKey";
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Le nom du tag qui contient le nom du type de couche.
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const string xmlShellTypeParser::getShellTypeTagName(void)
{
	return "ShellType";
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Le nom du tag qui contient le degr� d'un monome.
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const string xmlShellTypeParser::getMonomeDegreesListTagName(void)
{
	return "MonomeDegreesList";
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Le nom du tag qui contient le degr� d'un monome.
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const string xmlShellTypeParser::getMonomeDegreeTagName(void)
{
	return "MonomeDegree";
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Le constructeur par d�faut.
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
xmlShellTypeParser::xmlShellTypeParser(void)
 : xmlParser()
{
	;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Le constrcteur avec la racine.
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
xmlShellTypeParser::xmlShellTypeParser(DOMElement * gaussianBasisShellTypeRoot)
 : xmlParser(gaussianBasisShellTypeRoot)
{
	;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Le Destructeur
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
xmlShellTypeParser::~xmlShellTypeParser(void)
{
	;
}


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// M�thode pour retourver les infos.
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
shellType xmlShellTypeParser::getShellType(const DOMElement * rootElement) const
{
	shellType shellT;
	int nbrOfBasisFunctions	, basisFunction ;

	DOMElement * shellTypeElement;
	DOMElement * monomeDegreesList;
	DOMNodeList * monomeDegreeNodesList;
	DOMNode * shellTypeNameNode;
	xmlIPoint3Parser monomeDegreeParser;

	
	//////////////////////////////////////////////////////////////////////////////////////
	// On commence par retrouve l'�l�ment racine dans le document.
	// on r�cup�re la cl� si elle existe.
	//
	// - Lorsque l'on ne trouve pas cet �l�ment on arr�te le programme.
	//////////////////////////////////////////////////////////////////////////////////////
	shellTypeElement = (DOMElement *)getElementByTagName(rootElement , getShellTypeTagName());

	if(shellTypeElement == NULL ) {
		cerr << "Error : in shellType xmlShellTypeParser::getShellType(void) const" << endl;
		cerr << "Error : the shell type description was not found in the document." << endl;
		cerr << "Error : aborting." << endl;
		exit(1);
	}

	shellT.setShellTypeKey(getAttributeValue(shellTypeElement , getShellTypeKeyAttributeName()));

	
	////////////////////////////////////////////////////////////////////////////////////////////
	// On r�cup�re le nom du type de couche.
	//
	// Cette fois ci on est cl�ment, ce champ n'est pas obligatoire. 
	////////////////////////////////////////////////////////////////////////////////////////////
	shellTypeNameNode = getElementByTagName(shellTypeElement , getShellTypeNameTagName());

	if(shellTypeNameNode == NULL) {
		shellT.setShellTypeName("");
	} else {
		shellT.setShellTypeName(getNodeStringValue(shellTypeNameNode,Remove_White_Space));
	}

	//////////////////////////////////////////////////////////////////////////////////////////////
	// On r�cup�re la liste des monomes ...
	//
	// On utilise le xmlIPoint3Parser avec le tag root <monomeDegree>
	///////////////////////////////////////////////////////////////////////////////////////////////
	monomeDegreesList = (DOMElement *) getElementByTagName(shellTypeElement , getMonomeDegreesListTagName());

	if(shellTypeElement == NULL ) {
		cerr << "Error : in shellType xmlShellTypeParser::getShellType(void) const" << endl;
		cerr << "Error : the monome degree list was not found in the shell type." << endl;
		cerr << "Error : aborting." << endl;
		exit(1);
	}

	monomeDegreeNodesList = getElementsByTagName(monomeDegreesList , getMonomeDegreeTagName());
	
	if(monomeDegreeNodesList == NULL || (nbrOfBasisFunctions = monomeDegreeNodesList->getLength()) == 0) {
		cerr << "Error : in shellType xmlShellTypeParser::getShellType(void) const" << endl;
		cerr << "Error : no monome degree  was not found in the m�onome degree list." << endl;
		cerr << "Error : aborting." << endl;
		exit(1);
	}
	
	shellT.setNbrOfBasisFunctions(nbrOfBasisFunctions);

	/////////////////////////////////////////////////////////////////////////////////////////////
	// Pour chaque fonction de base on lit le degr� du monome. Pour cela 
	// on refile le travaille au monomeDegreePArser qui dont le tag racine
	// a �t� reconfigur�r pour bien choper les degr�s des monomes.
	/////////////////////////////////////////////////////////////////////////////////////////////
	monomeDegreeParser.setIPoint3TagName(getMonomeDegreeTagName());

	for(basisFunction =0 ; basisFunction < nbrOfBasisFunctions ; basisFunction++) {
		shellT.setMonomeDegree(basisFunction,monomeDegreeParser.getIPoint3((DOMElement *)monomeDegreeNodesList->item(basisFunction) ));
	}

	/////////////////////////////////////////
	// On renvoie ...
	/////////////////////////////////////////
	return shellT;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// M�thode pour retrouver le type de couche dans le document attach� au parser.
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
shellType xmlShellTypeParser::getShellType(void) const
{
	return getShellType(getRootElement());
}
