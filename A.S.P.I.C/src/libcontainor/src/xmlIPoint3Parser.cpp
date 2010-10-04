/* 
 * The containor library of A.S.P.I.C. 
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
#include "xmlIPoint3Parser.h"

////////////////////////////////////////////////////////////////
// Constructeur.
////////////////////////////////////////////////////////////////
xmlIPoint3Parser::xmlIPoint3Parser(DOMElement * DOMPointElement)
: xmlParser(DOMPointElement)
{
	resetTagNames();
}

////////////////////////////////////////////////////////////////
// Constrcuteur.
////////////////////////////////////////////////////////////////
xmlIPoint3Parser::xmlIPoint3Parser(void)
{
	resetTagNames();
}

////////////////////////////////////////////////////////////////
// Destructeur.
////////////////////////////////////////////////////////////////
xmlIPoint3Parser::~xmlIPoint3Parser(void)
{
	;
}

/////////////////////////////////////////////////////////////////
// M�thode pour acc�der � la valeur du point.
/////////////////////////////////////////////////////////////////
ipoint<3> xmlIPoint3Parser::getIPoint3(const DOMElement * rootElement) const
{
	ipoint<3> value;
	
	DOMNode * xNode;
	DOMNode * yNode;
	DOMNode * zNode;
	DOMElement * positionElement;

	/////////////////////////////////////////////////////////////////////////
	// On r�cup�re l'�l�ment qui correspond � la position.
	//////////////////////////////////////////////////////////////////////////
	positionElement = (DOMElement *)getElementByTagName(rootElement , getIPoint3TagName());

	if(positionElement == NULL) {
		cerr << "Error : in dpoint<3> xmlIPoint3Parser::getIPoint3(DOMElement * rootElement) const" << endl;
		cerr << "Error : no " << getIPoint3TagName() << " tag name was found in the document" << endl;
		cerr << "Error : aborting." << endl;
	}
	
	/////////////////////////////////////////////////////////////////////////
	// On r�cup�re le noeud en x.
	//
	// - Lorsque ce noeud n'existe pas on arrete l'execution du 
	// programme.
	/////////////////////////////////////////////////////////////////////////
	xNode = getElementByTagName(positionElement , getXTagName());

	if(xNode == NULL) {
		cerr << "Error : in ipoint<3> xmlIPoint3Parser::getIPoint3(DOMElement * rootElement) const" << endl;
		cerr << "Error : no tag was found with first coordonate for position." << endl;
		cerr << "Error : unable to read position. Aborting." << endl;
		exit(1);
	}

	value[0] = getNodeIntegerValue(xNode);
	
	/////////////////////////////////////////////////////////////////////////
	// On r�cup�re le noeud en y.
	//
	// - Lorsque ce noeud n'existe pas on arrete l'execution du 
	// programme.
	/////////////////////////////////////////////////////////////////////////
	yNode = getElementByTagName(positionElement , getYTagName());

	if(yNode == NULL) {
		cerr << "Error : in ipoint<3> xmlIPoint3Parser::getIPoint3(DOMElement * rootElement) const" << endl;
		cerr << "Error : no tag was found with second coordonate for position." << endl;
		cerr << "Error : unable to read position. Aborting." << endl;
		exit(1);
	}
	
	value[1] = getNodeIntegerValue(yNode);

	/////////////////////////////////////////////////////////////////////////
	// On r�cup�re le noeud en z.
	//
	// - Lorsque ce noeud n'existe pas on arrete l'execution du 
	// programme.
	/////////////////////////////////////////////////////////////////////////
	zNode = getElementByTagName(positionElement , getZTagName());

	if(zNode == NULL) {
		cerr << "Error : in ipoint<3> xmlIPoint3Parser::getIPoint3(DOMElement * rootElement) const" << endl;
		cerr << "Error : no tag was found with third coordonate for position." << endl;
		cerr << "Error : unable to read position. Aborting." << endl;
		exit(1);
	}
	
	value[2] = getNodeIntegerValue(zNode);

	////////////////////////////////////////////////////////////////////////////
	// On renvoie la position qui a �t� lue.
	////////////////////////////////////////////////////////////////////////////
	return value;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// M�thode pour retrouver un triplet d'entier.
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
ipoint<3> xmlIPoint3Parser::getIPoint3(void) const
{
	return getIPoint3(getRootElement());
}


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// M�thode pour acc�der au nom du tag qui contient le triplet d'entier.
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const string & xmlIPoint3Parser::getIPoint3TagName(void) const
{
	return IPoint3TagName;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// M�thode pour acc�der au nom du tag qui contient le triplet d'entier.
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const string & xmlIPoint3Parser::getXTagName(void) const
{
	return XTagName;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// M�thode pour acc�der au nom du tag qui contient le triplet d'entier.
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const string & xmlIPoint3Parser::getYTagName(void) const
{
	return YTagName;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// M�thode pour acc�der au nom du tag qui contient le triplet d'entier.
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const string & xmlIPoint3Parser::getZTagName(void) const
{
	return ZTagName;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// M�thode pour acc�der au nom du tag qui contient le triplet d'entier.
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void xmlIPoint3Parser::setIPoint3TagName(const string & iPoint3TagName)
{
	IPoint3TagName = iPoint3TagName;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// M�thode pour acc�der au nom du tag qui contient le triplet d'entier.
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void xmlIPoint3Parser::setXTagName(const string & xTagName)
{
	XTagName = xTagName;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// M�thode pour acc�der au nom du tag qui contient le triplet d'entier.
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void xmlIPoint3Parser::setYTagName(const string & yTagName)
{
	YTagName = yTagName;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// M�thode pour acc�der au nom du tag qui contient le triplet d'entier.
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void xmlIPoint3Parser::setZTagName(const string &  zTagName)
{
	ZTagName = zTagName;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// M�thode pour remettre la valeur des tag � leur valeur par d�faut.
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void xmlIPoint3Parser::resetTagNames(void)
{
	IPoint3TagName = "IPoint3D";
	XTagName = "x";
	YTagName = "y";
	ZTagName = "z";
}
