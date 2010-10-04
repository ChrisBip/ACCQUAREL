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
#ifndef _I_POINT_
#define _I_POINT_

#include "tpoint.h"


/**
 * Classe de tableau d'entier dont la taille est connue 
 * � la compilation.
 *
 * Deplus on ajoute quelques op�rateurs pour faire des op�rations sur ces 
 * tableaux.
 */
template <int Dimension>
class ipoint : public tpoint<int,Dimension>
{
private:

protected:

public:

	
	/**
	 * Constructeur par d�faut.
	 */
	inline ipoint(void)
	{
		;
	}
	
	/**
	 * Constructeur de copie.
	 *
	 * @param p le tableau que l'on souhaite copier dans l'objet construit.
	 */
	inline ipoint(const ipoint<Dimension> & p)
	{
		// ALH - 9/2/7 - sp�cifie la classe d'origine de copy()
		// sinon g++ 4.1 recherche une fonction globale.
		tpoint<int,Dimension>::copy(p);
	}

	/**
	 * Construcuteur qui remplit le tableau avec des �l�ments qui prennent la 
	 * m�me valeur.
	 *
	 * @param value la valeur de tous les �l�ments du tableau construit.
	 */
	inline ipoint(const int & value)
	{
		this->setDatas(value);
	}

	/**
	 * Constrcuteur avec les valeur des trois �l�ments du tableau.
	 *
	 * @param x la valeur du premier element.
	 * @param y la valeur du second element.
	 * @param z la valeur du troisi�me �l�ment. 
	 *
	 * @warning ce constructeur ne doit etre utilis� que pour 
	 * les objets de type ipoint<3>.
	 */
	inline ipoint(const int & x , const int & y , const int & z) 
	{
		assert(this->getDimension() == 3);
		this->setDatas(x,y,z);
	}

	/**
	 * Constrcuteur avec les valeur des deux �l�ments du tableau.
	 *
	 * @param x la valeur du premier element.
	 * @param y la valeur du second element.
	 *
	 * @warning ce constructeur ne doit etre utilis� que pour 
	 * les objets de type ipoint<2>.
	 */
	inline ipoint(const int & x , const int & y) 
	{
		assert(this->getDimension() == 2);
		this->setDatas(x,y);
	}

	/**
	 * M�thode qui calcule un tableau dont les �l�ments sont les maxs
	 * des �l�ments des tableaux pass�s en argument.
	 * 
	 * @param p le premier tableau.
	 *
	 * @param q le second tableau.
	 *
	 * @return un tableau dont chaque �l�ment i est le max de l'�l�ment i du premier 
	 * tableau et de l'�lement i du second tableau.
	 */
	inline static ipoint<Dimension> uniformMax(const ipoint<Dimension> & i , const ipoint<Dimension> & j) 
	{
		ipoint<Dimension> tmp;
		for(int dim=0 ; dim < Dimension ; dim++) {
			tmp[dim] = max(i[dim],j[dim]);
		}
		return tmp;
	}

	/**
	 * M�thode pour calculer la norme
	 */
	inline int norme_1(void) const
	{
		int _norme_1 = 0;
		for(int i=0 ; i < Dimension ; i++) _norme_1 += abs(this->getData(i));
		return _norme_1;
	}

	/**
	 * Operateur de sommation pour deux tableaux d'entiers.
	 *
	 * @param p le tableau que l'on souhaite ajouter au tableau appelant.
	 *
	 * @return un tableau qui contient la somme des deux tableaux.
	 */
	inline ipoint<Dimension> operator+(const ipoint<Dimension> & p) const
	{
		ipoint<Dimension> tmp;
		for(int i=0 ; i < this->getDimension() ; i++) {
			tmp[i] = p[i] + this->getData(i); 
		}
		return tmp; 
	}

	
	/**
	 * Operateur unaire de sommation pour deux tableaux d'entiers.
	 *
	 * @param p le tableau que l'on souhaite ajouter au tableau appelant.
	 *
	 * @return une r�f�rence vers le tableau qui contient la somme des deux tableaux.
	 */
	inline ipoint<Dimension> & operator+=(const ipoint<Dimension> & p)
	{
		for(int i=0 ; i < Dimension ; i++) {
			this->getData(i) += p[i]; 
		}
		return *this;
	}

	/**
	 * Operateur de comparaison pour deux tableaux d'entiers.
	 *
	 * @param p le tableau que l'on souhaite comparer au tableau appelant.
	 *
	 * @return true si les deux tableaux sont identiques false sinon.
	 */
	inline virtual bool operator==(const ipoint<Dimension> & p) const
	{
		if(alphabeticalCmp(*this ,p) == 0) return true;
		return false;
	}
		
	/**
	 * Operateur de comparaison pour deux tableaux d'entiers.
	 *
	 * @param p le tableau que l'on souhaite comparer au tableau appelant.
	 *
	 * @return false si les deux tableaux sont identiques true sinon.
	 */
	inline virtual bool operator!=(const ipoint<Dimension> & p) const
	{
		return !(this->operator==(p));
	}

	/**
	 * M�thode la comparaison lexicographique de deux tableaux.
	 *
	 * Si p et q sont deux tableaux on cherche le premier �l�ment de chaque
	 * tableau qui les distingue. Si cet �l�ment n'existe pas alors les deux tableaux sont
	 * identiques (on renvoie alors la valeur 0). Sinon le signe de la diff�rence de ces
	 * �l�ments donne l'ordre qui existe entre les deux tableaux.
	 *
	 * Par exemple si l'on consid�re les tableaux (2,4,8) et (2,5,1) alors le premier
	 * �l�ement qui les diff�re est le deuxieme et nous pouvons dire que, au sens 
	 * lexicographique, (2,4,8) < (2,5,1) puisque 4-5 = -1 < 0.
	 *
	 * @return 0 si les deux tableaux sont identiques, un nombre
	 * positif si le premier tableau est "apr�s" le second et un nombre n�gatif
	 * si le premier tableau se trouve "avant" le second.
	 */
	inline static int alphabeticalCmp(const ipoint<Dimension> & p1 , const ipoint<Dimension> & p2)
	{
		int value;
		for(int i=0 ; i < Dimension ; i++) {
			value = p1[i] - p2[i];
			if(value != 0) return value;
		}
		return 0;
	}

};

/**
 * structure qui permet d'utiliser la comparaison 
 * alphab�tique de deux tableaux d'entier lorsque l'il sont 
 * la cl� d'un objet de type map.
 */
template<int Dimension>
struct ipointAlphebiticalCmp {
	inline bool operator()(const ipoint<Dimension> & p1 , const ipoint<Dimension> & p2) const
	{
		return ipoint<Dimension>::alphabeticalCmp(p1,p2) < 0;
	}
};



#endif
