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
#ifndef _XML_DPOINT_3_PARSER_
#define _XML_DPOINT_3_PARSER_

#include "dpoint.h"
#include <xmlParser.h>

/**
 * Classe pour lire une position dans un document XML.
 *
 * Cette classe permet de lire des document de la forme :
 *
 * <Position>
 *		<x> 1 </x>
 *		<y> 2 </y> 
 *		<z> 3 </z>
 * </Position>
 *
 * A partir d'un tel document (ou partie de document) cette classe 
 * construit un objet dpoint<3> qui a pour valeur (1,2,3) si on l'applique
 * � l'exemple ici propos�.
 */
class xmlDPoint3Parser : virtual public xmlParser
{
private:
	
	string DPoint3TagName;
	string XTagName;
	string YTagName;
	string ZTagName;


public :
	
	/**
	 * Constructeur.
	 */
	xmlDPoint3Parser(void);

	/**
	 * Constructeur.
	 */
	xmlDPoint3Parser(DOMElement * DOMPointElement);

	/**
	 * Destructeur.
	 */
	virtual ~xmlDPoint3Parser(void);

	
	/**
	 * M�thode pour acc�der � la valeur.
	 *
	 * @return la valeur de l'objet dpoint<3> lu dans le 
	 * document auquel le parser est attach�.
	 */
	dpoint<3> getDPoint3(const DOMElement * root) const;


	/**
	 * M�thode pour acc�der � la valeur.
	 *
	 * @return la valeur de l'objet dpoint<3> lu dans le 
	 * document auquel le parser est attach�.
	 */
	dpoint<3> getDPoint3(void) const;

	/**
	 * M�thode pour acc�der au nom de la balise qui contient 
	 * la positon.
	 */
	const string & getDPoint3TagName(void) const;

		/**
	 * M�thode pour acc�der au nom de la balise qui contient 
	 * la premi�re coordonn�e de positon.
	 */
	const string & getXTagName(void) const;

		/**
	 * M�thode pour acc�der au nom de la balise qui contient 
	 * la seconde coordonn�es de positon.
	 */
	const string & getYTagName(void) const;

		/**
	 * M�thode pour acc�der au nom de la balise qui contient 
	 * la troisi�me coordonn�e positon.
	 */
	const string & getZTagName(void) const;

	/**
	 * M�thode pour acc�der au nom de la balise qui contient 
	 * la positon.
	 */
	void setDPoint3TagName(const string & dPoint3TagName);

	/**
	 * M�thode pour acc�der au nom de la balise qui contient 
	 * la premi�re coordonn�e de positon.
	 */
	void setXTagName(const string & xTagName);

	/**
	 * M�thode pour acc�der au nom de la balise qui contient 
	 * la seconde coordonn�es de positon.
	 */
	void setYTagName(const string & yTagName);

	/**
	 * M�thode pour acc�der au nom de la balise qui contient 
	 * la troisi�me coordonn�e positon.
	 */
	void setZTagName(const string & zTagName);

	/** 
	 * M�thode pour remettre les tags � leurs valeurs initiale.
	 */
	void resetTagNames(void);
};

#endif


