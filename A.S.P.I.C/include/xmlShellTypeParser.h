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
#ifndef _XML_GAUSSIAN_BASIS_SHELL_TYPE_PARSER_
#define _XML_GAUSSIAN_BASIS_SHELL_TYPE_PARSER_

#include "shellType.h"
#include <xmlParser.h>


/**
 * Classe pour parser un DOMElement (morceau de fichier XML) qui contient un
 * type de couche.
 * Le propos de cette classe est de construire un objet shellType contenant
 * les inforamtions qui sont pr�sente dans le document.
 */
class xmlShellTypeParser : public virtual xmlParser
{
private:

protected:

public:
	
	/**
	 * Le constructeur par d�faut.
	 */
	xmlShellTypeParser(void);

	/**
	 * Le constructeur avec la racine du document � parser.
	 */
	xmlShellTypeParser(DOMElement * rootShellTypeElement);

	/**
	 * Le destructeur.
	 */
	virtual ~xmlShellTypeParser(void);

	/**
   * M�thode qui lit et construit l'objet shellType pr�sent dans le document.
	 */
	shellType getShellType(void) const;

	/**
   * M�thode qui lit et construit l'objet shellType pr�sent dans le document.
	 */
	shellType getShellType(const DOMElement * rootElement) const;
	
	/**
	 * Le nom du tag qui contient le nom de la couche.
	 */
	static const string getShellTypeNameTagName(void);

	/**
	 * Le nom du tag qui contient le nom de la couche.
	 */
	static const string getShellTypeKeyAttributeName(void);

	/**
	 * Le nom du tag qui contient le le type de couche.
	 */
	static const string getShellTypeTagName(void);

	/**
	 * Le nom du tag qui contient le degr� d'un monome pr�sent dans la couche.
	 */
	static const string getMonomeDegreeTagName(void);

	/**
	 * Le nom du tag qui contient le degr� d'un monome pr�sent dans la couche.
	 */
	static const string getMonomeDegreesListTagName(void);

};

#endif

