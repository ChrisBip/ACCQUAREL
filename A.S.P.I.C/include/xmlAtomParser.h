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
#ifndef _ATOM_PARSER_
#define _ATOM_PARSER_

#include "atom.h"
#include "chemicalElementsDataBaseInterface.h"
#include <dpoint.h>
#include <iostream>
#include <xmlParser.h>
using namespace std;

/**
 * Class Pour cr�er dans un programme C++ un objet de type
 * atome qui contient les informations contenus dans un fichier
 * XML.
 *
 * Voici un exemple de ce que sait lire la classe xmlAtomParser :
 * 
 *	<Atom>
 *		
 *		<ChemicalElement>
 *			<ChemicalElementKey> H </chemicalElementKey>
 *			<NbrOfNeutrons> 1 </NbrOfNeutrons>
 *   </ChemicalElement>
 * 
 *		<AtomCenter>
 *			<Position> 
 *				<x> 0 </x> 
 *				<y> 0 </y> 
 *				<z> 0 </z> 
 *			</Position>
 *
 *			<DistanceUnit> AU </DistanceUnit>
 *		</AtomCenter>
 *
 *	</Atom>
 *
 * A partir d'un tel fichier cette classe construit un (objet) atome qui contient les informations :
 *
 * - L'�l�ment chimique poss�de un cl� H:
 *		- son symbol est H.
 *	  - son nom est l'Hydrog�ne.
 *	  - Il contient 1 proton.
 *		- Il contient 1 neutron.
 *  
 * - La position de cet atome est (0,0,0) et elle est exprim�e en unit�s atomiques.
 */
class xmlAtomParser : public xmlParser
{
private:
			
protected:
	
	/**
	 * M�thode pour retrouver les informations qui concernent le 
	 * centre de l'atome.
	 *
	 * @return le couple form�e par la position de l'atome et de l'unit� dans laquelle
	 * la postion est exprim�e.
	 */
	pair<dpoint<3> , atom::distanceUnit> getAtomCenter(void) const;

	/**
	 * M�thode pour retrouver les information relative � l'�l�ment chimique
	 * que l'on manipule.
	 *
	 * En fait cette m�thode construit non seulement l'�l�ment chimique sur
	 * lequel s'appuie l'atome mais le sp�cifie aussi car, pour un atome, le nombre
	 * de neutrons doit etre connu. C'est pourquoi elle renvoie une paire et pas simplement
	 * un �l�ment chimique.
	 *
	 * @return la paire form� par l'�l�ment chimique sur lequel s'appuie l'atome et le nombre
	 * de neutrons de cet �l�ment.
	 */
	pair<chemicalElement,int> getAtomChemicalElement(void) const;
	
public:
	/**
	 * M�thode qui contient le nom du tag racine qui contient un atome.
	 */
	static const string getAtomTagName(void);

	/**
	 * M�thode pour trouver le nom du tag qui va contenir toutes les informations
	 * sur l'�lement chimique.
	 */
	static const string getChemicalElementTagName(void);

	/**
	 * M�thode pour trouver le nom du tag qui contient la cl� de l'�lement
	 * chimique.
	 */
	static const string getChemicalElementKeyTagName();
	
	/**
	 *	M�thode pour retrouver le nom du tag qui contient le nombre de neutrons 
	 * de l'�l�ment chimique.
	 */
	static const string getNbrOfNeutronsTagName();
	
	/**
	 * The name of the tag that contains the position of the atom.
	 */
	static const string getAtomCenterTagName();	

	/**
	 * The name of the tag that contains the position of the atom.
	 */
	static const string getAtomCenterUnitTagName();	

	/**
	 * Constructeur de la classe.
	 */
	xmlAtomParser(void);
	
	/**
	 * Constructeur de la classe.
	 *
	 * @param rootAtomElement l'�l�ment racine XML dans lequel on souhaite lire un
	 * atome.
	 */
	xmlAtomParser(DOMElement * rootAtomElement);
	
	/**
	 * Destructeur de  la classe.
	 */
	virtual ~xmlAtomParser(void);
	
	/**
	 * M�thode pour construire un objet atom � partir des 
	 * informations pr�sentes dans le document DOM.
	 *
	 * @return un objet de type atom qui a �t� initialis� � 
	 * partir des informations lues dans le document auquel 
	 * est attach� le parser.
	 */
	atom getAtom(void) const;	
};

#endif


