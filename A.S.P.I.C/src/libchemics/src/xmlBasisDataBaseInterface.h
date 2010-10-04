/* 
* The chemics library of A.S.P.I.C. 
 * Written and directed by Fran�ois Lodier support.aspic@gmail.com.
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
#ifndef _XML_BASIS_DATA_BASE_INTERFACE_
#define _XML_BASIS_DATA_BASE_INTERFACE_


#include "basisElement.h"
#include <xmlDataBaseInterface.h>

/**
 * Classe pour retrouver les information sur les bases gaussiennes disponibles avec 
 * le code A.S.P.I.C.
 *
 * Les principales fonctionnalit�s de cette classe sont :
 * 
 * - Lister l'ensemble des bases gaussiennes disponibles.
 * - Lister l'ensemble des �l�ments disponibles dans une base.
 * - Retrouver un �lement d�crit dans une base gaussienne � partir du nom de la base et du symbole de l'�l�ment chimique.
 * - Retrouver un �l�ment d�crit dans une base gaussienne � partir du nom de la base et de son num�ro dans la liste des
 * �l�ments disponibles pour cette base.
 *
 */
class xmlBasisDataBaseInterface : public xmlDataBaseInterface
{
private:
		
	/**
	 * Un pointeur vers le seul objet xmlBasisDataBaseInterface instanciable.
	 */
	static xmlBasisDataBaseInterface * BasisDataBase;
	
	/**
	 * Le nom de la base gaussienne manipul�e.
	 */
	string BasisName;

protected:
			
	/**
	 * Le constructeur par d�faut.
	 */
		xmlBasisDataBaseInterface(void);
	
	/**
	 * Le constructeur avec connection automatique � une base.
	 *
	 * @param basisName le nom de la base � laquelle on souahite se connecter.
	 */
	xmlBasisDataBaseInterface(const string basisName);
	
	/**
		* Le destructeur.
	 */
	virtual ~xmlBasisDataBaseInterface(void);
	
	/**
	 * M�thode pour retrouver le nom de la base contenue dans l'objet
	 *
	 * @warning Lorsque lorsque l'objet n'a pas �t� initialmis�, cette m�thode renvoie une
	 * chaine de charct�res vide.
	 */
	const string & getBasisName(void) const;
	
	/**
	 * M�thode pour connaitre la localisation du document � manipuler.
	 */
	virtual string getDocumentURI(void) const;
		
	/**
	 * M�thode pour connaitre la localisation du sch�ma.
	 */
	virtual string getSchemaURI(void) const;
	
	/**
	 * M�thode pour connaitre le nom de la base que contient l'objet.
	 */
	void setBasisName(const string & basisName);
	
public:
		
	/**
	 * Method connect.
	 * This method performs the connecction with the data base.
	 */
	static void connect(const string & basisName);
	
	/**
	 * Method to know if we are connected or not.
	 *
	 * @return true if we are connected, else false.
	 */
	static bool connected(void);
	
	/**
	 * Method connect.
	 * This method performs the connecction with the data base.
	 */
	static void disconnect(void);
	
	/**
	 * A string containing the name of the ID attribute.
	 */
	//static const string getBasisElementKeyAttributeName();

	/**
	 * A string containing the element tag name.
	 */
	//static const string getBasisElementShellTagName();

	/**
	 * A string containing the element tag name.
	 */
	//static const string getBasisElementShellTypeKeyTagName();
	
	/**
	 * A string containing the element tag name.
	 */
	//static const string getBasisElementTagName();

	/**
	 * M�thode pour retrouver le nom de la base avec laquelle nous sommes
	 * entraint de travailler (base � la quelle nous sommes connect�).
	 *
	 * @warning Lorsque la connection n'est pas �tablie, cette m�thode renvoie une
	 * chaine de charct�res vide.
	 */
	static const string getConnectionId(void);
	
	/**
	 * Method GET to find information about the chemical element ith symbol symbol
	 * in the gaussian basis set basis , and information are stored in a gaussian
	 * basis element element.
	 */
	static basisElement getBasisElement(const string & basis , const string & symbol);

	/**
		* Method GET to find information about the chemical element ith symbol symbol
	 * in the gaussian basis set basis , and information are stored in a gaussian
	 * basis element element.
	 */
	static basisElement getBasisElement(const string & symbol);
	
	/**
		* Method GET to find information about an element in the data base.
	 *
	 * @warning to use this method, a connection to a data base must be 
	 * available.
	 */
	static basisElement getBasisElement(const string & basisName , const int & item);
	
	/**
	 * Method GET to find information about an element in the data base.
	 *
	 * @warning to use this method, a connection to a data base must be 
	 * available.
	 */
	static basisElement getBasisElement(const int & item);
		
	/**
	 * Method GET for the number of elements in the data base.
	 */
	static int getNbrOfBasisElements(const string & basisName);
	
	/**
	 * Method GET for the number of elements in the data base.
	 */
	static int getNbrOfBasisElements(void);
};


#endif

