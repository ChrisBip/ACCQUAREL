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
#ifndef _D_POINT_
#define _D_POINT_

#define _USE_MATH_DEFINES

#include "tpoint.h"
#include <math.h>

template <int Dimension>
class dpoint : public tpoint<double,Dimension>
{

public:
	
	/**
	 * Constructeur par d�faut.
	 */
	inline dpoint(void) 
	{
		;
	}

	/**
	 * Constructeur par lequel tous les �l�ments du tableau sont initialis�s avec une m�me valeur.
	 *
	 * @param value la valeur de tous les �l�ments du tableau ainsi construit.
	 */
	inline dpoint(const double & value)
	{
		this->setDatas(value);
	}

	/**
	 * Constructeur de copie.
	 *
	 * @param p le tableau � recopier dans l'objet nouvellement cr��.
	 */
	inline dpoint(const dpoint<Dimension> & p)
	{
		// ALH - 9/2/7 - sp�cifie la classe d'origine de copy()
		// sinon g++ 4.1 recherche une fonction globale.
		tpoint<double,Dimension>::copy(p);
	}

	/**
	 * Constructeur avec les valeurs des trois �l�ments du tableau.
	 *
	 * @param x la valeur du premier element.
	 * @param y la valeur du second element.
	 * @param z la valeur du troisi�me �l�ment. 
	 *
	 * @warning ce constructeur ne doit etre utilis� que pour 
	 * les objets de type dpoint<3>.
	 */
	inline dpoint(const double & x , const double & y , const double & z) 
	{
		assert(Dimension == 3);
		this->setDatas(x,y,z);
	}

	/**
	 * Constrcuteur avec les valeur des deux �l�ments du tableau.
	 *
	 * @param x la valeur du premier element.
	 * @param y la valeur du second element.
	 *
	 * @warning ce constructeur ne doit etre utilis� que pour 
	 * les objets de type dpoint<2>.
	 */
	inline dpoint(const double & x , const double & y) 
	{
		assert(Dimension == 2);
		this->setDatas(x,y);
	}
	
	/**
	 * Operateur de sommation pour deux tableaux de r�els.
	 *
	 * @param p le tableau que l'on souhaite ajouter au tableau appelant.
	 *
	 * @return un tableau qui contient la somme des deux tableaux.
	 */	
	inline dpoint<Dimension> operator+ (const dpoint<Dimension> & p) const
	{
		dpoint<Dimension> tmp;
		for(int i=0 ; i < Dimension ; i++)
			tmp[i] = p[i] + this->getData(i);
		return tmp;
	}

	/**
	 * Operateur unaire de sommation pour deux tableaux de r�els.
	 *
	 * @param p le tableau que l'on souhaite ajouter au tableau appelant.
	 *
	 * @return une r�f�rence vers le tableau qui contient la somme des deux tableaux.
	 */
	inline dpoint<Dimension> & operator+= (const dpoint<Dimension> & p)
	{
		for(int i=0 ; i < Dimension ; i++)
			this->getData(i) += p[i];
		return *this;
	}

	/**
	 * Operateur de soustraction pour deux tableaux de r�els.
	 *
	 * @param p le tableau que l'on souhaite soustraire au tableau appelant.
	 *
	 * @return un tableau qui contient la diff�rence des deux tableaux.
	 */	
	inline dpoint<Dimension> operator- (const dpoint<Dimension> & p) const
	{
		dpoint<3> tmp;
		for(int i=0 ; i <Dimension ; i++) {
			tmp[i] = this->getData(i) - p[i];
		}
		return tmp;
	}

	/**
	 * Operateur unaire de soustraction pour deux tableaux de r�els.
	 *
	 * @param p le tableau que l'on souhaite soustraire au tableau appelant.
	 *
	 * @return une r�f�rence vers le tableau qui contient la diff�rence des deux tableaux.
	 */
	inline dpoint<Dimension> & operator-= (const dpoint<Dimension> & p)
	{
		for(int i=0 ; i < Dimension ; i++)
			this->getData(i) -= p[i];
		return *this;
	}

	/**
	 * Operateur de multiplication pour un tableau de r�els et un scalaire.
	 *
	 * @param scalar le r�el avec lequel on souhaite multiplier le tableau appelant.
	 *
	 * @return un tableau qui contient le produit du tableau et du scalaire.
	 */
	inline dpoint<Dimension> operator* (const double & scalar) const
	{
		dpoint<Dimension> tmp;
		for(int i=0 ; i < Dimension ; i++)
			tmp[i] = scalar * this->getData(i);
		return tmp;
	}

	/**
	 * Operateur unaire de multiplication pour un tableau de r�els et un scalaire.
	 *
	 * @param scalar le r�el avec lequel on souhaite multiplier le tableau appelant.
	 *
	 * @return une r�f�rence vers le tableau qui contient le produit du tableau et du scalaire.
	 */
	inline dpoint<Dimension> & operator*= (const double & scalar)
	{
		for(int i=0 ; i < Dimension ; i++) {
			this->getData(i) *= scalar;
		}
		return *this;	
	}
	
	/**
	 * Operateur unaire de division d'un tableau de r�els par un scalaire.
	 *
	 * @param scalar le r�el par lequel on souhaite diviser le tableau appelant.
	 *
	 * @return une r�f�rence vers le tableau qui contient la division du tableau par le scalaire.
	 *
	 * @warning le scalaire doit etre non nul.
	 */
	inline dpoint<Dimension> & operator/= (double scalar)
	{
		assert(scalar != 0);

		for(int i=0 ; i < Dimension ; i++) {
			this->getData(i) /= scalar;
		}
		return *this;	
	}
		
	/**
	 * Operateur de division d'un tableau de r�els par un scalaire.
	 *
	 * @param scalar le r�el par lequel on souhaite diviser le tableau appelant.
	 *
	 * @return un tableau qui contient la division du tableau par le scalaire.
	 *
	 * @warning le scalaire doit etre non nul.
	 */
	inline dpoint<Dimension> operator /(double scalar) const
	{
		assert(scalar != 0);

		dpoint<Dimension> tmp(*this);
		tmp /= scalar;
		return tmp;
	}

	/**  
   * M�thode pour calculer le barycentre pond�r� de deux points.
	 *
	 * @param p1 le premier point.
	 * @param p2 le second point.
	 * @param s1 le poid associer au premier point.
	 * @param s2 le poid associer au second point.
	 */
	inline void bary(const dpoint<Dimension> & p1 , const double & s1 , const dpoint<Dimension> & p2 , const double & s2)
	{	
		double s = s1 +s2;
		for(int i= 0 ; i < Dimension ; i++) {
			setData(i , ( s1*p1[i] + s2*p2[i])/s);
		}
	}

	/**
	 * Op�rateur pour faire un produit scalaire entre le point courrant
	 * et un point p.
	 *
	 * @param p le deuxi�me point pour faire le produit scalaire.
	 *
	 * @return la valeur du produit scalaire.
	 */
	double operator* (const dpoint<Dimension> & p) const
	{
		double tmp = 0;
		for(int i=0 ; i < Dimension ; i++) {
			tmp += this->getData(i) * p[i];
		}
		return tmp;
	}

	/**
	 * M�thode pour caluler la norme 2 au carr� d'un point
	 *
	 * @return la nomre 2 au carr� de l'objet.
	 */
	inline double sq_norme_2(void) const
	{
		double tmp =0;
		for(int i=0 ; i < Dimension ; i++)
			tmp += pow(this->getData(i) , 2);
		return tmp;
	}

	/**
	 * M�thode pour caluler la norme 2 d'un point.
	 *
	 * @return la nomre 2 de l'objet.
	 */
	inline double norme_2(void) const
	{
		return sqrt(sq_norme_2());
	}

	/**
	 * M�thode pour calculer la distance au carr� 
	 * entre deux points.
	 * 
	 * @param p1 le premier point.
	 * @param p2 le second point.
	 *
	 * @return la distance au carr� entre les deux points.
	 */
	inline static double sq_distance(const dpoint<Dimension> & p1 , const dpoint<Dimension> & p2)
	{
		double distance = 0 ;
		for(int i=0 ; i < Dimension ; i++) {
			distance += pow((p1[i]-p2[i]) , 2);	
		}
		return distance;
	}

	/**
	 * M�thode pour calculer la distance entre deux points.
	 * 
	 * @param p1 le premier point.
	 * @param p2 le second point.
	 * @return la distance entre les deux points.
	 */
	inline static double distance(const dpoint<Dimension> & p1 , const dpoint<Dimension> & p2)
	{
		return sqrt(sq_distance(p1,p2));
	}		

	/**
	 * M�thode pour copier.
	 */
	inline dpoint<Dimension> & operator= (const dpoint<Dimension> & p)
	{
		// ALH - 9/2/7 - sp�cifie la classe d'origine de copy()
		// sinon g++ 4.1 recherche une fonction globale.
		tpoint<double,Dimension>::copy(p);
		return *this;
	}

	/**
	* M�thode pour comparer deux points.
	*
	* @param p le tableau avec lequel on souhaite comparer l'objet.
	*
	* @return true si les deux points sont identiques et false sinon. 
	*
	* @warning nous travaillons ici avec des r�els donc deux tableaux qui devraient
	* etre identiques peuvent etre diff�rents par exemple s'ils sont les r�sultats de calculs
	* avec des erreurs d'arrondis.
	*/
	inline bool operator ==(const dpoint<Dimension> & p) const
	{
		for(int i=0 ; i<Dimension ;i++) {
			if(this->getData(i) != p[i]) {
				return false;
			}	
		}
		return true;
	}

	/**
	* M�thode pour comparer deux points.
	*
	* @param p le tableau avec lequel on souhaite comparer l'objet.
	*
	* @return true si les deux points sont identiques, et false sinon.
	*
	* @warning nous travaillons ici avec des r�els donc deux tableauxt qui devraient
	* etre identiques peuvent etre diff�rents par exemple s'ils sont les r�sultats de calculs
	* avec des erreurs d'arrondis.
	*/
	inline bool operator !=(const dpoint<Dimension> & p) const
	{
		return !((*this)==p);
	}

};

/**
 * Op�rateur de multiplication entre un scalaire et un tableau.
 *
 * @param scalar le scalaire.
 * @param p le point.
 *
 * @return un tableau qui contient le r�sultat de la multiplication.
 */
template <int Dimension>
inline dpoint<Dimension> operator * (const double & scalar , const dpoint<Dimension> & p)
{
	return p*scalar;
}

#endif
