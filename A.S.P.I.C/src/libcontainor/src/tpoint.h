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
#ifndef _T_POINT_
#define _T_POINT_

#include <iostream>
#include <string.h>
#include <assert.h>

using namespace std;

/**
 *  Classe pour manipuler des tableaux de taille
 * fixe (connue � la compilation).
 */
template<class Type , int Dimension>
class tpoint
{
private:

	/**
	 * Tableau de'elements de type Type est de taille Dimension.
	 */
	Type Datas[Dimension];

protected:

	/**
	 * M�thode pour copier le contenu d'un objet point
	 * dans l'objet courrant.
	 * 
	 * @param p le point que l'on souhaite copier.
	 * @return void.
	 */
	inline void copy(const tpoint<Type,Dimension> & p)
	{
		for(int i=0 ; i < Dimension ; i++) setData(i ,  p.getData(i)); 
	}

public:

	/**
	 * Constructeur par d�faut.
	 */
	inline tpoint(void)
	{
		;
	}

	/**
	 * Constructeur avec la meme valeur pour tout le monde.
	 *
	 * @param value la valeur que prendrons tout les �l�ments du tableau
	 * lorsqu'il aura �t� cr��.
	 */
	inline tpoint(const Type &  value)
	{
		setDatas(value);
	}

	/**
	 * Constrcuteur avec les valeur des trois �l�ments du tableau.
	 *
	 * @param x la valeur du premier element.
	 * @param y la valeur du second element.
	 * @param z la valeur du troisi�me �l�ment. 
	 *
	 * @warning ce constructeur ne doit etre utilis� que pour 
	 * les objets de type tpoint<Type,3>.
	 */
	inline tpoint(const Type &  x , const Type & y , const Type & z)
	{
		assert( Dimension == 3);

		setDatas(x,y,z);
	}

	/**
	 * Constrcuteur avec les valeur des deux �l�ments du tableau.
	 *
	 * @param x la valeur du premier element.
	 * @param y la valeur du second element.
	 *
	 * @warning ce constructeur ne doit etre utilis� que pour 
	 * les objets de type tpoint<Type,2>.
	 */
	inline tpoint(const Type &  x , const Type &  y)
	{
		assert(Dimension == 2);

		setDatas(x,y);
	}

	/**
	 * Constructeur de copie.
	 *
	 * @param p le tableau � copier dans l'objet contruit.
	 */
	inline tpoint(const tpoint<Type,Dimension> & p)
	{
		copy(p);
	}

	/**
	 * Destructeur.
	 */
	inline virtual ~tpoint(void)
	{
		;
	}

	/**
	 * M�thode constante qui permet d'acc�der un �l�ment du tableau.
	 * 
	 * @param i le num�ro de l'�l�ment.
	 *
	 * @return une r�f�rence constante vers la i-�me coordonn�e.
	 *
	 * @warning l'appel de cette fonction avec i n�gatif
	 * ou i sup�rieur ou �gal � la dimension provoque l'arret 
	 * du programme.
	 */
	inline const Type & getData(int i) const
	{
		assert( i >= 0);
		assert( i < getDimension());

		return Datas[i];
	}

	/**
	 * M�thode qui permet d'acc�der un �l�ment du tableau.
	 * 
	 * @param i le num�ro de l'�l�ment.
	 *
	 * @return une r�f�rence vers le i-�me �l�ment.
	 *
	 * @warning l'appel de cette fonction avec i n�gatif
	 * ou i sup�rieur ou �gal � la dimension provoque l'arret 
	 * du programme.
	 */
	inline Type & getData(int i)
	{
		assert( i >= 0);
		assert( i < Dimension);

		return Datas[i];
	}

	/**
	 * M�thode pour connaitre la di�mension du tableau.
	 *
	 * @return la valeur de la dimension du tableau.
	 */
	inline const int getDimension(void) const
	{
		return Dimension;
	}

	/**
	 * Op�rateur constant d'acc�s aux �l�ments du tableau.
	 *
	 * @param i le position de l'�l�ment recherch�.
   * 
	 * @return la une r�f�rence constante vers l'�l�ment recherch�.
	 *
	 * @warning la position de m'�l�ment demand� doit etre positive ou
	 * nulle et strictement inf�rieure � la dimension du tableau.
	 */
	inline const Type & operator[] (const int & i) const
	{
		assert(i >= 0);
		assert(i < Dimension);

		return getData(i);
	}

	/**
	 * Op�rateur constant d'acc�s aux �l�ments du tableau.
	 *
	 * @param i le position de l'�l�ment recherch�.
   * 
	 * @return la une r�f�rence constante vers l'�l�ment recherch�.
	 *
	 * @warning la position de m'�l�ment demand� doit etre positive ou
	 * nulle et strictement inf�rieure � la dimension du tableau.
	 */
	inline Type & operator[] (const int & i)
	{
		assert(i >= 0);
		assert(i < Dimension);

		return getData(i);
	}

	/**
	 * Op�rateur d'affectation.
	 *
	 * @param p le tableau que l'on souhaiote copier dans l'objet appelant.
	 *
	 * @return une r�f�rence vres le tableau modifi�.
	 */
	inline tpoint<Type,Dimension> & operator= (const tpoint<Type,Dimension> & p)
	{
		copy(p);
		return *this;
	}

	/**
	 * M�thode pour caster l'objet tpoint<Type,Dimension> vers un pointeur de Type.
	 *
	 * @return un pointeur constant vers le tableau de donn�es.
	 */
	inline operator const Type * (void) const 
	{
		return Datas;
	}

	/**
	 * M�thode qui permet la valeur d'un �l�ment du tableau.
	 *
	 * @param i la position de l'�l�ment dont on souhaite modifier la valeur.
	 * @param value la valeur � donner au i-�me �l�ment du tableau.
	 *
	 * @warning l'appel de cette fonction avec i n�gatif
	 * ou i sup�rieur ou �gal � la dimension provoque l'arret 
	 * du programme.
	 */
	inline void setData(const int & i , const Type & value)
	{
		assert( i >= 0);
		assert( i < Dimension);

		Datas[i] = value;
	}

	/**
	 * M�thode qui permet de donner � tous les �l�ments du 
	 * tableau une unique valeur.
	 *
	 * @param value la valeur � donner � tous les �l�ments du tableau.
	 */
	inline void setDatas(const Type & value)
	{
		for(int i=0 ; i < Dimension ; i++)
			setData(i,value);
	}

	/**
	 * M�thode pour donner des valeurs � tout les �l�ments
	 * d'un tableau de dimension 3 d'un seul coup.
	 *
	 * @param x la valeur du premier element.
	 * @param y la valeur du second element.
	 * @param z la valeur du troisi�me �l�ment. 
	 *
	 * @warning cette m�thode ne doit etre utilis� que pour 
	 * les objets de type tpoint<Type,3>.
	 */
	inline void setDatas(const Type & x , const Type & y , const Type & z)
	{
		assert(Dimension == 3);

		setData(0,x);
		setData(1,y);
		setData(2,z);
	}

	/**
	 * M�thode pour donner des valeurs � tout les �l�ments
	 * d'un tableau de dimension 3 d'un seul coup.
	 *
	 * @param x la valeur du premier element.
	 * @param y la valeur du second element.
	 *
	 * @warning cette m�thode ne doit etre utilis� que pour 
	 * les objets de type tpoint<Type,2>.
	 */
	inline void setDatas(const Type & x , const Type & y) 
	{
		assert(Dimension == 2);

		setData(0,x);
		setData(1,y);
	}

	/**
	 * M�thode pour donner des valeurs � tout les �l�ments
	 * d'un tableau en les recopiant depuis un autre tableau.
	 *
	 * @param p le tableau � recopier.
	 */
	inline void setDatas(const tpoint<Type,Dimension> & p)
	{
		copy(p);
	}

	/**
	 * M�thode pour �crire le tableau dans un flux.
	 *
	 * @param out le flux dans lequel on souhaite �crire le tableau.
	 *
	 * @see operator<<(ostream & , const tpoint<Type,Dimension> & )
	 */
	inline virtual void write(ostream & out) const
	{
		out << "(";
		for(int i=0 ; i < Dimension  ; i++)  {
			out << getData(i) << (i < (Dimension-1) ? " , " : "" ) ;
		}
		out << ")";
	}

};	

/**
 * Op�rateur �crire un tableau de type tpoint<Type,Dimension> dans 
 * flux.
 * 
 * @param out le flux dans lequel on souhaite �crire le tableau.
 *
 * @param p le tableau � �crire dans le flux.
 *
 * @return une r�f�rence vers le flux contenant la description du tableau.
 */
template<class Type , int Dimension>
inline ostream & operator<<(ostream & out , const tpoint<Type,Dimension> & p) 
{
	p.write(out);
	return out;
}

#endif



