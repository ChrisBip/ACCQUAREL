/* 
* The xml parser library of A.S.P.I.C. 
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
#ifndef _XML_PARSER_
#define _XML_PARSER_


#include <iostream>
#include <string>
#include <xercesc/util/PlatformUtils.hpp>
#include <xercesc/dom/DOM.hpp>
#include <xercesc/dom/DOMImplementation.hpp>
#include <xercesc/dom/DOMImplementationLS.hpp>
#include <xercesc/dom/DOMWriter.hpp>
#include <xercesc/framework/StdOutFormatTarget.hpp>
#include <xercesc/framework/LocalFileFormatTarget.hpp>
#include <xercesc/parsers/XercesDOMParser.hpp>
#include <xercesc/util/XMLUni.hpp>
#include <xercesc/util/OutOfMemoryException.hpp>
#include <xercesc/util/XMLDouble.hpp>
#include <xercesc/util/XMLBigInteger.hpp>
#include "xmlErrorReporter.h"
using namespace std;

/**
 * Cette classe permet de lire des documents xml (DOM) dans le code
 * A.S.P.I.C. 
 */
class xmlParser 
{	
private:		

	/**
	 * La racine du document.
	 */
	DOMElement * RootElement;
	
protected:
	
	/**
	 * Une �num�ration pour le format des chaines de caract�res � lire.
	 *
	 * Les formatages disponibles sont :
	 * - No_Format : ne formate pas la chaine de caract�res lue et la renvoie telle qu'elle est �crite dans le 
	 * document XML.  
	 * - Collapse_White_Space : Dcollapse the white space from the string in the XML document.
	 * _ Remove_White_Space : Retire tout les espaces de la chaine de caract�re.
	 */
	typedef enum _stringFormatOption {
			Collapse_White_Space,
			No_Format ,
			Remove_White_Space
	} stringFormatOption;
	
	/**
	 * M�thode pour retrtouver la valeur d'un attribut.
	 *
	 * @param attributeName le nom de l'attribut pour lequel on souahite lire la valeur.
	 * @param element l'�l�ment pour lequel on souahite connaitre la valeur de l'attribut.
	 *
 	 * @return la chaine de charact�re trouver comme valeur d'attribut. Lorsque l'attribut nest pas
	 * trouv� alors une chaine vide est renvoy�e.
	 */
	string getAttributeValue(DOMElement * element , const string & attributeName) const;
	
	/**
	 * M�thode pour retrtouver la valeur d'un attribut.
	 *
	 * Cette m�thode est �quivalente � la m�thode getAttributeValue(DOMElement * element , const string & attributeName)
	 * ou element est la racine du document manipul�.
	 *
	 * @param attributeName le nom de l'attribut pour lequel on souahite lire la valeur.
	 *
 	 * @return la chaine de charact�re trouver comme valeur d'attribut. Lorsque l'attribut nest pas
	 * trouv� alors une chaine vide est renvoy�e.
	 */
	string getAttributeValue(const string & attributeName) const;
	
	/**
	 * M�thode pour retrouver la liste des enfants d'un �l�ment avec un m�me nom de balise
	 *
	 * @param element la partie du document xml dans laquelle on soouhaite effectuer la recherche.
	 *
	 * @param tagName le nom de balise des �l�ment que l'on recherche.
	 *
	 * @return La liste des �l�ments trouv�s. Lorsqu'aucun �lement n'a �t� trouv� le pointeur NULL est
	 * renvoy�.
	 */
	DOMNodeList * getElementsByTagName(const DOMElement * element , const string & tagName) const;
	
	/**
	 * M�thode pour retrouver la liste des �l�ments du document avec un m�me nom de balise
	 *
	 * Cette m�thode est �quivalente � la m�thode getElementsByTagName(DOMElement * element , const string & tagName)
	 * ou element est la racine du document manipul�.
	 *
	 * @param tagName le nom de balise des �l�ment que l'on recherche.
	 *
	 * @return La liste des �l�ments trouv�s. Lorsqu'aucun �lement n'a �t� trouv� le pointeur NULL est
	 * renvoy�.
	 */
	DOMNodeList * getElementsByTagName(const string & elementName) const;

	/**
	 * M�thode pour retrouver un unique enfant d'un �l�ment avec son nom de balise.
	 *
	 * @param element la partie du document dans laquelle on souhaite effectuer la recherche.
	 * @param tagName le nom de la balise que l'on recherche.
	 *
	 * @return le noeud du document qui contient l'�l�ment recherch�. Lorsque la recherche a �chou� le poiteur 
	 * NULL est renvoy�.
	 *
	 * @warning S'il existe plusieurs enfants avec le nom de tag recherch� alors le premier enfant trouv� est renvoy�.
	 */
	DOMNode * getElementByTagName(const DOMElement * element , const string & tagName) const;
	
	/**
	 * M�thode pour retrouver un unique enfant d'un �l�ment avec son nom de balise.
	 *
	 * Cette m�thode est �quivalente � la m�thode getElementByTagName(const DOMElement * element , const string & tagName)
	 * ou element est la racine du document manipul�.
	 *
	 * @param tagName le nom de la balise que l'on recherche.
	 *
	 * @return le noeud du document qui contient l'�l�ment recherch�. Lorsque la recherche a �chou� le poiteur 
	 * NULL est renvoy�.
	 *
	 * @warning S'il existe plusieurs enfants avec le nom de tag recherch� alors le premier enfant trouv� est renvoy�.
	 */
	DOMNode * getElementByTagName(const string & elementName) const;
	

	/**
	 * Method GET for the number of elements with tag name tagName.
	 *
	 * @param xmlElement the part of the XML document to search for the tag.
	 * @param tagName the tag to look for.
	 *
	 * @return the number of node with tag name tagName.
	 */
	int getNbrOfElementsWithTagName(const DOMElement * element , const string & elementName) const;

	/**
	 * Method GET for the number of elements with tag name tagName.
	 *
	 * This method is similar as getNbrOfElementsWithTagName(const DOMElement * xmlElement , const string & tagName) const,
	 * but the search is performed in the whole document.
	 *
	 * @param tagName the tag to look for.
	 *
	 * @return the number of node with tag name tagName.
	 */
	int getNbrOfElementsWithTagName(const string & elementName) const;
	
	/**
	 * Methode GET for a double node value.
   *
	 * @param the node from which the double value must be extracted.
	 *
	 * @returns the double value contianed the node.
	 */
	 double getNodeDoubleValue(const DOMNode * node) const;
	
	 /**
		* Methode GET for a integer node value.
		*
		* @param the node from which the integer value must be extracted.
		*
		* @returns the integer value contained in the node.
		*/
	 int getNodeIntegerValue(const DOMNode * node) const;
	
	 /**
		* Methode GET for a string node value.
		*
		* @param the node from which the string value must be extracted.
		* @param opt the formating of the extracted string.
		*
		* @returns the string value contained in the node.
		*/
	 string getNodeStringValue(const DOMNode * node , stringFormatOption opt = No_Format) const;
	
	 /**
		* Methode GET for a text node value.
		*
		* @param the node from which the text value must be extracted.
		*
		* @returns the text value contained in the node.
		*
		* @warning if the node does not contains a text child, then
		* a NULL pointer is returned.
		*/
	 const XMLCh *  getNodeTextValue(const DOMNode * node) const;
	
	/**
	 * Method GET for the root node of the document.
	 *
	 * @return the upper level of the document.
	 */
	 DOMElement * getRootElement(void) const;

public:
	
	/**
	 * Default Constructor.
	 */
	xmlParser(void);

	/**
	 * Constructor with the root node of the document.
	 */
	xmlParser(DOMElement * rootElement);

	/**
	 * Destructor.
	 */
	virtual ~xmlParser(void);

	/**
		* Method SET for the root node of the document.
	 */
	void setRootElement(DOMElement * rootElement);
	
};

#endif
