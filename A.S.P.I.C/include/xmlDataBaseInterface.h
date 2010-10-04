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
#ifndef _XML_DATA_BASE_INTERFACE_
#define _XML_DATA_BASE_INTERFACE_

#include "xmlDocumentParser.h"

/**
 * Generic class to manage XML data base.
 */
class xmlDataBaseInterface : protected xmlDocumentParser
{
private:

	/**
	 * Le nom du tag qui contient une entr�e.
	 */
	const string EntryTagName;
	
	/**
	 * Le nom de l'attribut qui est la cl� de l'�l�ment.
	 */
	const string IdAttributeName;
	
protected:
	
	/**
	 * Chaine de charact�re qui contient le chemin  vers le fichier de la base de donn�es.
	 */
	virtual string getDocumentURI(void) const =0;
	
	/**
	 * M�thode pour r�cup�rer uniquement la partie
	 * du document qui contient les informations
	 * sur l'�l�ment que nous recherchons.
	 */
	DOMElement * getElementById(const string & key) const;
	
	/**
	 * M�thode GET pour acc�der � une entr�e de la base de donn�es.
	 */
	DOMNode * getDataBaseEntry(int item) const;
	
	/**
	 * Method GET for the ID of an entry in the data base.
	 */
	string getID4Entry(int item) const;
	
	/**
	 * Chaine de charact�re qui contient le chemin vers le fichier de sch�ma.
	 */
	virtual string getSchemaURI(void) const =0;

	/**
	 * M�thode GET pour le nombre d'entr�es dans la base de donn�es
	 */
	int getNbrOfEntries(void) const;
	
public:
	
	/**
	 * Le constructeur.
	 */
		xmlDataBaseInterface(const string & entryTagName , const string & idAttributeName);
	
	/**
		* Le destructeur.
	 */
	virtual ~xmlDataBaseInterface(void);
};



#endif

