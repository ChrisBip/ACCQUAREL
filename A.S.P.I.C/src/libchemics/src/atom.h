/* 
* The gaussian library of A.S.P.I.C. 
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
#ifndef _ATOM_
#define _ATOM_


#include "chemicalElement.h"
#include <dpoint.h>
#include <iostream>
#include <string>
using namespace std;

/**
* La classe "atom" est une classe pour la description et la manipulation des atomes.
 *
 * Au coeur de l'atome se trouve l'�l�ment chimique qui lme compose. La classe atome h�rite donc 
 * naturellement de cette classe. Cepedant l'atome, contrairement � l'�l�ment chimique est 
 * distinguable d'un autre atome compos� du m�me �l�ment chimique par sa position et son nombre 
 * de neutrons.
 *
 * Un atome est donc un �l�ment chimique pour lequel on a sp�cifie :
 * - Le nombre de neutrons
 * - La position
 * - L'unit� dans laquelle on souhaite exprimer les distances.
 */
class atom : public chemicalElement
{
public:

	/**
	 * Enum�ration pour les unit�s de la position.
	 * En gros on peut utiliser des angstr�ms ou des unit�s
	 * atomiques.
	 *
	 * - ANGSTROEM les distances sont exprim�es en angstr�ms (10E-10 m).
	 * - ATOMIC_UNIT les distances sont exprim�es en unit�s atomiques et (1 a.u = rayon de l'atome de Bohre).
	 */
	typedef enum _distanceUnit {ANGSTROEM , ATOMIC_UNIT} distanceUnit;

private:
	/**
	 * L'unit� pour les distances.
	 */
	distanceUnit DistanceUnit;

	/**
	 * Le nombre de neutrons de l'atome.
	 */
	int NbrOfNeutrons;

	/**
	 * La position de l'atome.
	 */
	dpoint<3> Position;
	
protected:

	/**
	 * M�thode pour copier un objet atome.
	 */
	void copy(const atom & a);

public :

	/**
	 * Constructeur par d�faut.
	 */
	atom(void);
	
	/**
	 * Constructeur de copie.
	 *
	 * @param a l'atome a recopier dans l'objet nouvellement cr��.
	 */
	 atom(const atom & a);

	 /**
	  * Destructeur de la classe.
		*/
	virtual ~atom(void);
	
	/**
	 * La valeur pour le rapport Unit� atomique et Angstr�m.
	 */
	static const double AtomicUnit2Angstroem;

	/**
	 * M�thode qui converti une distance exprim�e en unit� atomique
	 * en une distance exprim�e en angstr�m.
	 *
	 * @param la distance en angstr�m.
	 *
	 * @return la meme distance en unit� atomique.
	 */
	static double angstroem2AtomicUnitConverter(const double & distance);

	/**
	 * M�thode qui converti un triplet de distances (une position) exprim� en angstr�m 
	 * en une position exprim�e en unit� atomique.
	 *
	 * @param la position en angstr�m.
	 *
	 * @return la meme position en unit� atomique.
	 */
	static dpoint<3> angstroem2AtomicUnitConverter(const dpoint<3> & position);

	/**
	 * M�thode qui converti une distance exprim�e en unit� atomique
	 * en une distance en angstr�m.
	 *
	 * @param distance la distance en unit� atomique.
	 *
	 * @return la meme distance en angstr�m.
	 */
	static double atomicUnit2AngstroemConverter(const double & distance);

	/**
	 * M�thode qui converti un triplet de distances exprim�es en unit� atomique
	 * en une distance en angstr�m.
	 *
	 * @param postion une position exprim�e en unit� atomique.
	 *
	 * @return la position en angstr�m.
	 */
	static dpoint<3> atomicUnit2AngstroemConverter(const dpoint<3> & distance);

	 /**
	 * M�thode pour changer l'unit� pour la position de l'atome.
	 *
	 * Cette m�thode est "constante" car elle ne change pas l'objet
	 * � proprement parler m�me si elle change les valeurs de la 
	 * position de l'objet.
	 *
	 * @param unit l'unit� dans laquelle on souahite exprimer la position.
	 */
	 void changeDistanceUnit(const distanceUnit & unit) const;

	/**
	 * M�thode pour remmettre un atome � "z�ro".
	 */
	void clear(void);


	/**
	 * M�thode pour convertir une unit� de distance en chaine de charct�res.
	 *
	 * @param unit l'unit� de distance que l'on souahite repr�senter par une chaine de charact�res.
	 */
	static string distanceUnit2String(const distanceUnit & unit);

	/**
	 * M�thode GET pour l'unit� de la position.
	 *
	 * @return l'unit� de la position.
	 */
	const distanceUnit & getDistanceUnit(void) const;

	/**
	 * M�thode GET pour le nombre de neutrons.
	 *
	 * @return le nombre de neutrons de l'objet.
	 */
	const int & getNbrOfNeutrons(void) const;
	
	/**
	 * M�thode GET pour la position.
	 *
	 * @return la position de l'atome.
	 */
	const dpoint<3> & getPosition(void) const;

	/**
	 * Method GET for the atom position.
	 *
	 * @param unit the unit in which the position of the atom should be 
	 * expressed.
	 * 
	 * @return the position of the atom expressed in the unit unit.
	 */
	const dpoint<3> getPosition(const atom::distanceUnit & unit) const;
	
	/**
	 * Operateur d'affectation.
	 *
	 * @param a la valeur � affecter � l'objet.
	 */
	atom & operator=(const atom & a);
	
	/**
	 * M�thode pour recopier la valeur d'un atome dans l'objet.
	 *
	 * @param a l'atome � recopier dans l'objet.
	 */
	void setAtom(const atom & a);
	 
	/**
	 * M�thode SET pour l'unit� de la position.
	 *
	 * Cette m�thode permet uniquement de sp�cifier l'unit�. Pour les conversion
	 * il est fortement conseill� de se r�f�reer � la m�thode changePositionUnit.
	 * 
	 * @param unit l'unit� pour la position.
	 */
	 void setDistanceUnit(const distanceUnit & unit);

	/**
	 * M�thode pour modifier le nombre de neutrons.
	 * 
	 * @param nbrOfNeutrons le nombre de neutrons de l'objet.
	 *
	 * @warning le nombre de neutrons doit �tre positif ou nul.
	 */
	void setNbrOfNeutrons(const int & nbrOfNEutrons);
	
	/**
	 * M�thode pour modifier la position de l'atome.
	 *
	 * @param position la position de l'atome.
	 *
	 * @param unit l'unit� dans laquelle on exprime la position.
	 */
	void setPosition(const dpoint<3> & position , const distanceUnit & unit=atom::ATOMIC_UNIT);

	/**
	 * M�thode pour modifier la position de l'atome.
	 *
	 * @param x la premi�re coordon�e cart�sienne de la position.
	 *
	 * @param y la seconde coordon�e cart�sienne de la position.
	 *
	 * @param z la trois�me coordon�e cart�sienne de la position.
	 *
	 * @param unit l'unit� dans laquelle on exprime la poistion.
	 */
	 void setPosition(const double & x ,const double & y ,const double & z , const distanceUnit & unit=atom::ATOMIC_UNIT);
	
	/**
	 * M�thode pour convertir une cha�ne de carct�res en unit� de distance.
	 *
	 * @param distanceUnitString une chaine de charact�res sens�e repr�senter une unit� de distance.
	 * Les chaine connues sont : "au" , "AtomicUnit" , pour les unti�s atomiques et 
	 * 
	 * @TODO.
	 *
	 * @return l'unit�, lorsque celle ci � �t� trouv�e.
	 */
	 static atom::distanceUnit string2DistanceUnit(const string & distanceUnitString);

	 /**
	 * M�thode pour �crire un atome dans un flux.
	 *
	 * @param outStream le flux dans lequel on souhaite �crire l'atome.
	 *
	 * @param linePrefix le pr�fixe que l'on souahite mettre avant chaque d�but de ligne.
	 */
	void write(ostream & outStream , const string & linePrefix = "") const; 


	/**
	 * M�thode pour �crire un atome dans un flux.
	 *
	 * @param outStream le flux dans lequel on souhaite �crire l'atome.
	 *
	 * @param linePrefix le pr�fixe que l'on souahite mettre avant chaque d�but de ligne.
	 */
	void writeXML(ostream & outStream , const string & linePrefix = "") const; 

};

/**
 * Operateur externe pour �crire un objet atome dans un flux.
 *
 * @param outStream le flux dans lequel on souhaite �crire l'atome.
 *
 * @param a l'atome que l'on souhaite d�crire.
 *
 */
extern ostream & operator<<(ostream & outStream , const atom & a);


/**
 * Operateur externe pour �crire un objet atome dans un flux.
 *
 * @param outStream le flux dans lequel on souhaite �crire l'atome.
 *
 * @param a l'atome que l'on souhaite d�crire.
 *
 */
extern ostream & operator<<(ostream & outStream , const atom::distanceUnit & unit);


#endif

