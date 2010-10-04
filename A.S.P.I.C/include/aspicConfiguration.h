/* 
 * The coniguration manager library of A.S.P.I.C. 
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
#ifndef _ASPIC_CONFIGURATION_
#define _ASPIC_CONFIGURATION_

#include <containor.h>
#include <iostream>
#include <string>
#include <xmlDocumentParser.h>
using namespace std;

class aspicConfiguration 
{
private:

protected:

public:

	/**
	 * This method is use to find the root 
	 * of the ASPIC files.
	 * 
	 * When the ASPIC_ROOT environment variable
	 * is set, then the value stored in this varible
	 * is returned.
	 *
	 * When the ASPIC_ROOT environment varible is
	 * not set then we try to look in different places :
	 * first "/etc/aspic"
	 * then  "/usr/local/aspic".
	 *
	 * If nothing was found this print an error message
	 * and the calling program will be aborted.
	 */
	static const string getAspicRoot(void);

	/**
	 * M�thode pour retrouver le chemin vers le fichier XML qui contient la base de donn�es des 
	 * �l�ments chimiques.
	 *
	 * Lorsque le fichier XML ne peut pas �tre trouv� alors, une chaine 
	 * vide est renvoy�e.
	 */
	static const string getChemicalElementsDataBasePath(void);
	
	/**
	 * M�thode pour retrouver le chemin vers le fichier sch�ma de la 
	 * base de donn�es des �l�ments chimiques.
	 *
	 * Lorsque le fichier sch�ma ne peut pas �tre trouv� alors, une chaine 
	 * vide est renvoy�e.
	 */
	static const string getChemicalElementsDataBaseSchemaPath(void);
	
	/**
	 * M�thode pour retrouver le r�pertoire racine qui contient les
	 * tout les fichiers de bases gaussiennes.
	 */
	static const string getBasisDataBaseRoot(void);

	/**
	 * M�thode pour retrouver le chemin vers le fichier XML de la 
	 * base de donn�es des bases chimiques.
	 *
	 * Lorsque le fichier XML ne peut pas �tre trouv� alors, une chaine vide est renvoy�e.
	 */
	static const string getBasisDataBasePath(const string & basisName);

	/**
	 * M�thode pour retrouver le sch�ma des fichiers XMLs qui contiennent les
	 * base gaussiennes.
	 *
	 * Lorsque le fichier sch�ma n'a pas �t� trouv� alors on renvoie une chaine vide.
	 */
	static const string getBasisDataBaseSchemaPath(void);
	
	/**
	 * M�thode pour retrouver le sch�ma des fichiers XMLs qui contiennent une fonction de base.
	 *
	 * Lorsque le fichier sch�ma n'a pas �t� trouv� alors on renvoie une chaine vide.
	 */
	static const string getBasisFunctionSchemaPath(void);
	
	/**
	 * M�thode pour retrouver la liste de toute les bases gaussiennes existantes.
	 */
	static const string getBasisKeyListPath(void);
		
	/**
	 * M�thode pour retrouver la liste de toute les bases gaussiennes existantes.
	 */
	static const string getBasisKeyListSchemaPath(void);

	
	/**
	 * M�thode pour retrouver le fichier sch�ma pour les mol�cules.
	 *
	 * Lorsque le fichier XML n'est pas trouv� une chaine vide est renvoy�e.
	 */
	static const string getMoleculeSchemaPath(void);

	/**
	 * M�thode pour retrouver le chemin vers le fichier XML de la 
	 * base de donn�es des �l�ments chimiques.
	 *
	 * Lorsque le fichier XML ne peut pas �tre trouv� alors, une chaine vide est renvoy�e.
	 */
	static const string getShellTypesDataBasePath(void);

	/**
	 * M�thode pour retrouver le chemin vers le fichier sch�ma de la 
	 * base de donn�es des �l�ments chimiques.
	 *
	 * Lorsque le fichier sch�ma ne peut pas �tre trouv� alors, une chaine 
	 * vide est renvoy�e.
	 */
	static const string getShellTypesDataBaseSchemaPath(void);	

	/**
	 * M�thode pour retrouver le chemin vers le fichier sch�ma d'une matrice
	 *
	 * Lorsque le fichier sch�ma ne peut pas �tre trouv� alors, une chaine 
	 * vide est renvoy�e.
	 */
	static const string getMatrixSchemaPath(void);	
};


/**
 * Function to know if a directory exists.
 * 
 * This function returns true if the string "path" 
 * given as an argument is a directory. If the is a file
 * or does not exists it will return false.
 */
extern bool isDirectory(const string & path);

/**
 * Fonction pour savoir si un fichier existe et est accessible en lecture.
 *
 * @param path le chemin vers le fichier.
 *
 * @return vrai lorsque le fichier est accessible en lecture, faux lorsque le fichier n'existe pas
 * ou si l'utilsateur du programme ne poss�de pas les droit pour lire le fichier.
 */
extern bool isFileReadable(const string & path);

#endif

