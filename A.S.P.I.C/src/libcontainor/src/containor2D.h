/* 
 * The containor library of the A.S.P.I.C. 
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
#ifndef _CONTAINOR_2D_
#define _CONTAINOR_2D_

#include "containor.h"
#include "ipoint.h"
#include <iostream>
#include <iomanip>
using namespace std;

/**
 * Classe pour manipuler des tableaux bi dimensionnels.
 */
template<typename Type>
class containor2D : public containor<Type> {
private:
	
	/**
	 * Le nombre de lignes du tableau.
	 */
	int NbrOfRows; 	
	
	/**
	 * Le nombre de colones du tableau.
	 */
	int NbrOfColumns; protected: 	
	
	/**
	 * M�thode qui permet de faire la copie.
	 *
	 * @param c le tableau � copier dans l'objet appelant.
	 */
	inline void copy(const containor2D<Type> & c)
	{
		NbrOfRows = c.getNbrOfRows();
		NbrOfColumns = c.getNbrOfColumns();
		containor<Type>::copy(c);
	} 	
	
	/**
	 * M�thode qui permet de faire le hash.
	 *
	 * @param row la ligne de l'�l�ment du tableau auquel on souhaite acc�der.
	 * @param column la colone de l'�l�ment du tableau auquel on souhaite acc�der.
	 *
	 * @return la position le l'�l�ment (row , column) dans le containor qui stoque 
	 * les valeurs des �l�ments du tableau.
	 */ 	
	inline int hash(const int & row , const int & column) const
	{
		assert(row >= 0);
		assert(row < getNbrOfRows());
		assert(column >= 0);
		assert(column < getNbrOfColumns()); 		
		return row + getNbrOfRows() * column;
	} 

public: 	
	
	/**
	 * Constructeur par d�faut.
	 *
	 * Construit un objet totalement vide qui ne peut pas 
	 * contenir de donn�es.
	 */
	inline containor2D(void)
		: containor<Type>() ,
		NbrOfColumns(0) ,
		NbrOfRows(0)
	{
		;
	} 	
	
	/**
	 * Constructeur avec sp�cification des tailles.
	 *
	 * @param nbrOfRows le nombre de lignes que le tableau pourra contenir.
	 * @param nbrOfColumns le nombre de colones que le tableau pourra contenir.
	 */
	inline containor2D(const int & nbrOfRows , const int & nbrOfColumns)
		: containor<Type>() ,
		NbrOfColumns(0) ,
		NbrOfRows(0)
	{
		this->setSize(nbrOfRows,nbrOfColumns);
	} 	
	
	/**
	 * Constructeur de copie.
	 *
	 * @param c le tableau � copier.
	 */
	inline containor2D(const containor2D<Type> & c)
		: containor<Type>() ,
		NbrOfColumns(0) ,
		NbrOfRows(0)
	{
		copy(c);
	} 	
	
	/**
	 * Destructeur.
	 */
	inline virtual ~containor2D(void)
	{
		clear();
	} 	
	
	/**
	 * M�thode qui nettoie totalement l'objet.
	 * 
	 * Cette m�thode permet de reinitialiser totalement le tableau 
	 * � z�ro. Apr�s l'appel de celle ci, plus aucune donn�e ne peut
	 * etre stoqu�e dans le tableau.
	 */ 	inline void clear(void)
	{
		NbrOfColumns = 0;
		NbrOfRows = 0;
		containor<Type>::clear();
	} 	
	
	/**
	 * M�thode pour acc�der aux �lement du tableau.
	 *
	 * @param row la ligne de l'�l�ment dont on souhaite connaitre la valeur.
	 * @param column la colone de l'�l�ment dont on souhaite connaitre la valeur.
	 *
	 * @warning il faut que row soit non n�gatif et strictement inf�rieur aux
	 * nombre de lignes que peut contenir l'objet.
	 *
	 * @warning il faut que column soit non n�gatif et strictement inf�rieur aux
	 * nombre de colones que peut contenir l'objet.
	 */
	inline Type & getData(const int & row , const int & column) 
	{
		assert(row >=0);
		assert(column >=0); 		assert(row < getNbrOfRows());
		assert(column < getNbrOfColumns()); 		return containor<Type>::getData(hash(row,column));
	} 	
	
	/**
	 * M�thode constante pour acc�der aux �l�ments du tableau.
	 *
	 * @param row la ligne de l'�l�ment dont on souhaite connaitre la valeur.
	 * @param column la colone de l'�l�ment dont on souhaite connaitre la valeur.
	 *
	 * @warning il faut que row soit non n�gatif et strictement inf�rieur aux
	 * nombre de lignes que peut contenir l'objet.
	 *
	 * @warning il faut que column soit non n�gatif et strictement inf�rieur aux
	 * nombre de colones que peut contenir l'objet.
	 */
	inline const Type & getData(const int & row , const int & column) const
	{
		assert(row >=0);
		assert(column >=0); 		assert(row < getNbrOfRows());
		assert(column < getNbrOfColumns()); 		return containor<Type>::getData(hash(row,column));
	} 	
	
	/**
	 * M�thode pour connaitre le nombre de lignes du tableau.
	 *
	 * @return le nombre de lignes dans le tableau.
	 */
	inline const int & getNbrOfRows(void) const
	{
		return NbrOfRows;
	} 	
	
	/**
	 * M�thode pour connaitre le nombre de colones du tableau.
	 *
	 * @return le nombre de colones dans le tableau.
	 */
	inline const int & getNbrOfColumns(void) const
	{
		return NbrOfColumns;
	} 	
	
	/**
	 * M�thode pour connaitre la taille du tableau.
	 *
	 * @return une paire d'entiers qui contient le nombre de lignes
	 * respectivement le nombre de colones) du tableau pour la premi�re composante 
	 * (respectivement pour la seconde).
	 */
	inline ipoint<2> & getSizes(void) const
	{
		ipoint<2> sizes(getNbrOfRows() , getNbrOfColumns());
		return sizes;
	} 	
	
	/**
	 * M�thode pour connaitre la taille du tableau dans une direction donn�e.
	 *
	 * @param dimension la dimension dans laquelle on souhaite connaitre la taille.
	 *
	 * @return le nombre de lignes ou de colones dans le tableau suivant le num�ro de
	 * la dimension demand�e.
	 *
	 * @warning la dimension doit prendre la valeur 0 ( pour acc�der aux nombre de lignes)
	 * ou 1 (pour acc�der au nombre de colones) mais ne peut prendre aucune autre valeur.
	 */
	inline const int & getSize(int dimension) const
	{
		assert(dimension >= 0);
		assert(dimension < 2);

		if(dimension == 0) {
			return getNbrOfRows();
		} else {
			return getNbrOfColumns();
		}		
	} 	
	
	/**
	 * Op�rateur d'affectation.
	 *
	 * @param c le containor � copier.
	 */
	inline containor2D<Type> & operator=(const containor2D<Type> & c)
	{
		copy(c);
		return *this;
	} 	
	
	/**
	 * Op�rateur constant pour acc�der aux �l�ments du tableau.
	 *
	 * @param row la ligne de l'�l�ment dont on souhaite connaitre la valeur.
	 * @param column la colone de l'�l�ment dont on souhaite connaitre la valeur.
	 *
	 * @warning il faut que row soit non n�gatif et strictement inf�rieur aux
	 * nombre de lignes que peut contenir l'objet.
	 *
	 * @warning il faut que column soit non n�gatif et strictement inf�rieur aux
	 * nombre de colones que peut contenir l'objet.
	 */
	inline const Type & operator()(const int & row ,const int & column) const
	{
		assert(row >=0);
		assert(column >=0); 		assert(row < getNbrOfRows());
		assert(column < getNbrOfColumns()); 		return getData(row,column);
	} 	
	
	/**
	 * Op�rateur d'acc�s aux �l�ments du tableau.
	 *
	 * @param row la ligne de l'�l�ment dont on souhaite connaitre la valeur.
	 * @param column la colone de l'�l�ment dont on souhaite connaitre la valeur.
	 *
	 * @warning il faut que row soit non n�gatif et strictement inf�rieur aux
	 * nombre de lignes que peut contenir l'objet.
	 *
	 * @warning il faut que column soit non n�gatif et strictement inf�rieur aux
	 * nombre de colones que peut contenir l'objet.
	 */
	inline Type & operator()(const int & row , const int & column)
	{
		assert(row >=0);
		assert(column >=0); 		assert(row < getNbrOfRows());
		assert(column < getNbrOfColumns()); 		return getData(row,column);
	} 

	/**
	 * M�thode pour fixer les valeurs du tableau � partir d'un autre tableau.
	 *
	 * @param array le tableau que l'on souhaite recopier dans l'objet.
	 */
	inline void setDatas(const containor2D<Type> & array)
	{
		copy(array);
	}

	/**
	 * M�thode pour remplir le conteneur avec une seule valeure.
	 *
	 * @param value la valeur avec laquelle on souhaite remplir le containor.
	 */
	inline void setDatas(const Type & value)
	{
		containor<Type>::setDatas(value);
	}
	
	/**
	 * M�thode pour sp�cifier la taille du tableau
	 *
	 * @param nbrOfRows le nombre de lignes pour le tableau.
	 * @param nbrOfColumns le nombre de colones pour le tableau.
	 *
	 * @warning il faut que le param�tre nbrOfLines soit strictement
	 * positif.
	 *
	 * @warning il faut que le parametre nbrOfColumns soit strictement 
	 * positif.
	 *
	 * @see clear(void)
	 */
	inline void setSizes(const int & nbrOfRows , const int & nbrOfColumns)
	{
		assert(nbrOfRows > 0);
		assert(nbrOfColumns > 0); 		
		NbrOfRows = nbrOfRows;
		NbrOfColumns = nbrOfColumns; 		
		containor<Type>::setSizes(nbrOfRows * nbrOfColumns);
	} 	
	
	/**
	 * M�thode qui permet d'afficher le conteneur sous une forme
	 * lisible pour l'homme.
	 *  
	 * @param out le flux dans lequel on veut �crire le contrainor.
	 */
	inline virtual void writePretty(ostream & out) const
	{
		int row , column , nbrOfRows , nbrOfColumns;
		
		int width = 8;

		nbrOfRows = getNbrOfRows();
		nbrOfColumns = getNbrOfColumns();

		for( row = 0 ; row < nbrOfRows ; row++) {
			
			for(column = 0 ; column < nbrOfColumns ; column++) {	
				out << setw(width) << getData(row,column);
			}

			if(row != (nbrOfRows - 1)) 
				out << endl;
		}
	}

};

#endif  
