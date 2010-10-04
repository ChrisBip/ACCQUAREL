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
#ifndef _GAUSSIAN_BASIS_SHELL_TYPE_DATA_BASE_INTERFACE_
#define _GAUSSIAN_BASIS_SHELL_TYPE_DATA_BASE_INTERFACE_

#include <xmlDataBaseInterface.h>
#include "shellType.h"
#include "xmlShellTypeParser.h"

class xmlShellTypesDataBaseInterface : public xmlDataBaseInterface
{
private :
	
	/**
	 * Le nom du tag qui contient une entr�e dans la base de donn�es.
	 */
	static const string	ShellTypeTagName;

	/**
	 * Le nom de l'attribut qui contient la cl� de chaque �l�ment dans la base de donn�e.
	 */
	static const string ShellTypeKeyAttributeName;
	
	/**
	 * L'objet xmlShellTypeDataBase instanci� lors d'une connection.
	 */
	static xmlShellTypesDataBaseInterface * ShellTypesDataBase;


	protected:
	
	/**
	 * Method GET to find the document location.
	 */
	virtual string getDocumentURI(void) const;
	
	/**
	 * Methog GET to find the schema location.
	 */
	virtual string getSchemaURI(void) const;

	/**
 	 * The constructor.
	 */
	xmlShellTypesDataBaseInterface(void);
	
	/**
 	 * The destructor.
	 */
	virtual ~xmlShellTypesDataBaseInterface(void);

	public:
	
	/**
	 * M�thode pour se connecter � la base de donn�es.
	 */		
	static void connect(void);
	
	/**
	 * M�thode pour savoir si l'on est connect� � la base de donn�es.
	 */		
	static bool connected(void);
	
	/**
	 * M�thode pour se deconnecter de la base de donn�es.
	 */
	static void disconnect(void);
	
	/**
	 * M�thode pour connaitre le nom de l'attribut qui contient la cl� pour les �l�ment de la base de donn�e.
	 */
	static const string & getShellTypeKeyAttibuteName(void);

	/**
	 * M�thode pour connaitre le nom de l'attribut qui contient la cl� pour les �l�ment de la base de donn�e.
	 */
	static const string & getShellTypeTagName(void);

	/**
	 * M�thode pour connaitre le nombre de type de couches stock�s dans la base de donn�es 
	 */
	static int getNbrOfShellTypes(void);

	/**
	 * M�thode pour retrouver un type de couche � partir de sa cl�.
	 */
	static shellType getShellType(const string & shellTypeKey);

	/**
	 * M�thode pour acc�der � un �l�m�nt item de la base de donn�e.
	 *
	 * @warning il faut que item soit positif ou nul et strictement inf�rieur
	 * aux nombre d'�l�ments contenus dans la base de donn�e.
	 */
	static shellType getShellType(const int & item);
};


#endif


