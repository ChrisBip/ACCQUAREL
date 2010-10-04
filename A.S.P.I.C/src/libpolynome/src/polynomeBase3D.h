/* 
* The polynome library of the A.S.P.I.C. 
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
#ifndef _POLYNOME_BASE_3D_
#define _POLYNOME_BASE_3D_

#define _USES_MATH_DEFINES
#include <containorSparse3D.h>
#include <iomanip>
#include <iostream>
#include <map>
#include <math.h>
#include <string>
#include "string4Polynomes.h"
using namespace std;

/**
 * Classe qui permet de g�rer les polynomes 
 * dans le cas tri - dimensionnel.
 */
template<typename Type>
class polynomeBase3D : public containorSparse3D<Type>
{
private:

	
protected : 
	
	/**
	 * M�thode pour afficher une fonction de base
	 *
	 * Le probl�me est de pouvoir afficher tout les polynomes
	 * sans avoir � r��crire de m�thode write ou d'op�rateur <<.
	 * Pour cela on demande � toutes les classes enfants de r�impl�menter
	 * cette m�thode comme cela chaque classe affichera correctement
	 * la base de polyn�mes qui lui convient.
	 *
	 * Par exemple dans polynome_3D le getBaseString affichera quelque
	 * chose comme X^dx . Y^dy . Z^dz alors que pour un polynome centr�
	 * on pourra afcher (X-CenterX)^dx . (Y-CenterY)^dy . (Z-CenterZ)^dz
	 *
	 * @param degree le degr�� de la fonction de base du polynome dont 
	 * on souhaite connaitre la repr�sentation.
	 */
	virtual const string getBaseString(const ipoint<3> & degree) const;

		/**
	 * M�thode de base pour faire l'addition de deux polynomes.
	 *
	 * Cette m�thode permet de calculer la somme des polynomes de base
	 * p et q et de stoquer le r�sultat de l'op�ration.
	 *
	 * @param p le premier polynome.
	 *
	 * @param q le second polynome.
	 *
	 * @warning cette m�thode est brute de fonderie, c'est a dire que les
	 * classes enfants auront la responsabilit� de la rendre accesible � 
	 * l'utilisateur.
	 */
	void add(const polynomeBase3D<Type> & p , const polynomeBase3D<Type> & q);

	/**
	 * M�thode de base pour faire l'addition unaire de deux polynomes.
	 *
	 * Cette m�thode permet de calculer la somme des polynomes de base
	 * q et du polynome appelant de stoquer le r�sultat de l'op�ration dans ce
	 * meme polynome.
	 *
	 * @param q � ajouter.
	 *
	 * @warning cette m�thode est brute de fonderie, c'est a dire que les
	 * classes enfants auront la responsabilit� de la rendre accesible � 
	 * l'utilisateur.
	 */
	void add(const polynomeBase3D<Type> & q);

	/**
	 * M�thode pour faire la division d'un polynome par un scalaire.
	 *
	 * Cette m�thode permet de calculer la division d'un polynome de base par un scalaire.
	 * Le r�sultat est stock� dans l'objet.
	 *
	 * @param poly le polynome dont on souhaite diviser tout les coefficients.
	 * 
	 * @param scalar le salaire.
	 *
	 * @warning cette m�thode est brute de fonderie, c'est a dire que les
	 * classes enfants auront la responsabilit� de la rendre accesible � 
	 * l'utilisateur.
	 */
	void divide(const polynomeBase3D<Type> & poly , const Type & scalar);

	/**
	 * M�thode pour faire la division unaire d'un polynome et d'un scalaire.
	 *
	 * Cette m�thode permet de calculer la division de l'objet par un scalaire.
	 * Le r�sultat est stock� dans l'objet.
	 *
	 * @param scalar le salaire.
	 *
	 * @warning cette m�thode est brute de fonderie, c'est a dire que les
	 * classes enfants auront la responsabilit� de la rendre accesible � 
	 * l'utilisateur.
	 *
	 * @warning le scalaire doit etre non nul.
	 */
	void divide(const Type & scalar);

	/**
	 * M�thode pour faire la multiplication de deux polynomes.
	 *
	 * Cette m�thode permet de calculer le produit des polynomes de base
	 * p et q et de stoquer le r�sultat de l'op�ration.
	 *
	 * @param p le premier polynome.
	 *
	 * @param q le second polynome.
	 *
	 * @warning cette m�thode est brute de fonderie, c'est a dire que les
	 * classes enfants auront la responsabilit� de la rendre accesible � 
	 * l'utilisateur.
	 */
	void multiply(const polynomeBase3D<Type> & p , const polynomeBase3D<Type> & q);
	
	/**
	 * M�thode pour faire la multiplication de deux polynomes.
	 *
	 * Cette m�thode permet de calculer le produit des polynomes de base
	 * p et q et de stoquer le r�sultat de l'op�ration.
	 *
	 * @param q le second polynome.
	 *
	 * @warning cette m�thode est brute de fonderie, c'est a dire que les
	 * classes enfants auront la responsabilit� de la rendre accesible � 
	 * l'utilisateur.
	 */
	void multiply(const polynomeBase3D<Type> & q);

	/**
	 * M�thode pour faire la multiplication d'un polynome et d'un scalaire.
	 *
	 * Cette m�thode permet de calculer le produit de l'objet avec un scalaire.
	 * Le r�sultat est stock� dans l'objet.
	 *
	 * @param poly le polynome dont on souhaite multiplier tout les coefficients
	 � par un scalaire.
	 *
	 * @param scalar le salaire.
	 *
	 * @warning cette m�thode est brute de fonderie, c'est a dire que les
	 * classes enfants auront la responsabilit� de la rendre accesible � 
	 * l'utilisateur.
	 */
	void multiply(const polynomeBase3D<Type> & poly , const Type & scalar);

	/**
	 * M�thode pour faire la multiplication unaire d'un polynome et d'un scalaire.
	 *
	 * Cette m�thode permet de calculer le produit de l'objet avec un scalaire.
	 * Le r�sultat est stock� dans l'objet.
	 *
	 * @param scalar le salaire.
	 *
	 * @warning cette m�thode est brute de fonderie, c'est a dire que les
	 * classes enfants auront la responsabilit� de la rendre accesible � 
	 * l'utilisateur.
	 */
	void multiply(const Type & scalar);

	/**
	 * M�thode de base pour faire l'addition de deux polynomes.
	 *
	 * Cette m�thode permet de calculer la somme des polynomes de base
	 * p et q et de stoquer le r�sultat de l'op�ration dans l'objet qui 
	 * effectue l'op�ration.
	 *
	 * @param p le premier polynome.
	 *
	 * @param q le second polynome.
	 *
	 * @warning cette m�thode est brute de fonderie, c'est a dire que les
	 * classes enfants auront la responsabilit� de la rendre accesible � 
	 * l'utilisateur.
	 */
	void soustract(const polynomeBase3D<Type> & p , const polynomeBase3D<Type> & q);

	/**
	 * M�thode de base pour faire la soustraction unaire de deux polynomes.
	 *
	 * Cette m�thode permet de calculer la diff�rence du polynome et du polynome pass� en argument.
	 * Le r�sultat de l'op�ration dans l'obet qui effectue l'op�ration.
	 *
	 * @param q � ajouter.
	 *
	 * @warning cette m�thode est brute de fonderie, c'est a dire que les
	 * classes enfants auront la responsabilit� de la rendre accesible � 
	 * l'utilisateur.
	 */
	void soustract(const polynomeBase3D<Type> & q);

public:
	
	/**
	 * Constructeur par d�faut.
	 */
	polynomeBase3D(void);
	
	/**
	 * Constrcuteur de copie.
	 *
	 * @param poly le polynome avec lequel on souhaite initialiser l'objet construit.
	 */
	polynomeBase3D(const polynomeBase3D<Type> & poly);

	/**
	 * Destrcuteur.
	 */
	virtual ~polynomeBase3D(void);

	/**
	 * M�thode pour connaitre les plus grands degr�s d'un polynome pour chacune des
	 * trois composantes.
	 *
	 * Cette m�thode renvoie un triplet d'entiers dont la premi�re composante 
	 * est le plus haut degr� pour la variable x, la seconde le plus haut degr� pour 
	 * la variable y et la derni�re le plus haut degr� pour la variable z. 
	 * 
	 * Par exemple pour le polynome x.y.z cette m�thode renvoie (1,1,1) et non pas 3. 
	 *
	 * @warning cette methode ne renvoie pas le degr� du polynome.
	 */
	int getDegree(void) const;

	/**
	 * M�thode pour connaitre les plus grands degr�s d'un polynome pour chacune des
	 * trois composantes.
	 *
	 * Cette m�thode renvoie un triplet d'entiers dont la premi�re composante 
	 * est le plus haut degr� pour la variable x, la seconde le plus haut degr� pour 
	 * la variable y et la derni�re le plus haut degr� pour la variable z. 
	 * 
	 * Par exemple pour le polynome x.y.z cette m�thode renvoie (1,1,1) et non pas 3. 
	 * @see getExtermPosition(void)
	 * @warning cette methode ne renvoie pas le degr� du polynome.
	 */
	ipoint<3> getUniformMax4Degree(void) const;

	/**
	 * Op�rateur d'assertion.
	 *
	 * @param poly le polynome � copier dans l'objet.
	 */
	polynomeBase3D & operator = ( const polynomeBase3D<Type> & poly);

	/**
	 * M�thode pour �crire le polynome dans un flux.
	 *
	 * @param os le lfux danslequel on souahite �crire le polynome.
	 */
	void write(ostream & os) const;
};

/**
 * Op�rateur pour �crire un polynome_base_3D dans un flux.
 *
 * @param out le flux dans lequel on souhaite �crire le polyn�me.
 *
 * @param poly le polynome � �crire dans le flux.
 *
 * @return le flux contenant le polynome.
 */
template<typename Type>
extern ostream & operator<<(ostream & out , const polynomeBase3D<Type> & poly);

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Le constructeur par d�faut.
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
template<typename Type>
polynomeBase3D<Type>::polynomeBase3D(void)
: containorSparse3D<Type>()
{
  this->clear();
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Le constructeur copie.
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
template<typename Type>
polynomeBase3D<Type>::polynomeBase3D(const polynomeBase3D<Type> & poly)
: containorSparse3D<Type>()
{
  containorSparse3D<Type>::copy(poly);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Le destructeur.
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
template<typename Type>
polynomeBase3D<Type>::~polynomeBase3D(void)
{
  this->clear();
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// M�thode pour faire l'addition de deux polynomes.
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
template<typename Type>
void polynomeBase3D<Type>::add(const polynomeBase3D<Type> & p , const polynomeBase3D<Type> & q)
{
	containorSparse3D<Type>::copy(p);
	add(q);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// M�thode pour faire l'addition unaire de deux polynomes.
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
template<typename Type>
void polynomeBase3D<Type>::add(const polynomeBase3D<Type> & q)
{
	ipoint<3> degree;
	Type value;

	for(degree = q.begin() ; degree != q.end() ; degree = q.next(degree)) {
		value = q(degree) + this->getData(degree);
		setData(degree , value);
	}
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// M�thode pour faire la division d'un polynome et d'un scalaire.
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
template<typename Type>
void polynomeBase3D<Type>::divide(const polynomeBase3D<Type> & poly , const Type & scalar)
{
	assert(scalar != 0);

	containorSparse3D<Type>::copy(poly);
	divide(scalar);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// M�thode pour faire la division unaire d'un polynome et d'un scalaire.
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
template<typename Type>
void polynomeBase3D<Type>::divide(const Type & scalar)
{
	assert(scalar != 0);

	ipoint<3> i;
	Type value;
	
	for(i=this->begin() ; i != this->end() ; i= this->next(i)) {
		value = this->getData(i) / scalar;
		setData(i,value);
	}
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// M�thode pour conaitre le degr� du polynome.
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
template<typename Type>
int polynomeBase3D<Type>::getDegree(void) const
{
	/* TODO */
  return 0;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// M�thode pour conaitre le degr� du polynome.
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
template<typename Type>
ipoint<3> polynomeBase3D<Type>::getUniformMax4Degree(void) const
{
	return this->getExtremPositions();
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// M�thode pour conaitre le degr� du polynome.
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
template<typename Type>
const string polynomeBase3D<Type>::getBaseString(const ipoint<3> & degree) const
{
	return monome3D2string(degree);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Methode pour faire la multiplication de deux polynomes
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
template<typename Type>
void polynomeBase3D<Type>::multiply(const polynomeBase3D<Type> & p , const polynomeBase3D<Type> & q)
{
	ipoint<3> i,j;
	Type value;

	this->clear();

	for(i=q.begin() ; i != q.end() ; i=q.next(i)) {
		for(j=p.begin() ; j != p.end() ; j=p.next(j)) {
			value = this->getData(i+j) + q(i) * p(j);
			setData(i+j , value);
		}
	}
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Methode pour faire la multiplication unaire de deux polynomes
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
template<typename Type>
void polynomeBase3D<Type>::multiply(const polynomeBase3D<Type> & q)
{
	polynomeBase3D tmp(*this);
	multiply(tmp,q);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// M�thode pour faire la multiplication unaire de d'un polynome et d'un scalaire.
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
template<typename Type>
void polynomeBase3D<Type>::multiply(const Type & scalar)
{
	ipoint<3> degree;
	Type value;

	if(scalar == 0) {
		this->clear();
		return;
	}
	
	for(degree = this->begin() ; degree != this->end() ; degree = this->next(degree)) {
		value = scalar *  this->getData(degree);
		setData(degree , value);
	}
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// M�thode pour faire la multiplication de d'un polynome et d'un scalaire.
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
template<typename Type>
 void polynomeBase3D<Type>::multiply(const polynomeBase3D<Type> & p , const Type & scalar)
{
	containorSparse3D<Type>::copy(p);
	multiply(scalar);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// M�thode pour faire la soustraction de deux polynomes.
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
template<typename Type>
void polynomeBase3D<Type>::soustract(const polynomeBase3D<Type> & p , const polynomeBase3D<Type> & q)
{
	containorSparse3D<Type>::copy(p);
	soustract(q);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// M�thode pour faire la soustraction unaire de deux polynomes.
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
template<typename Type>
void polynomeBase3D<Type>::soustract(const polynomeBase3D<Type> & q)
{
	ipoint<3> degree;
	Type value;

	for(degree = q.begin() ; degree != q.end() ; degree = q.next(degree)) {
		value = this->getData(degree) - q(degree);
		setData(degree , value);
	}

}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Method WRITE for the polynome.
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
template<typename Type>
void polynomeBase3D<Type>::write(ostream & os) const
{
	bool has_previous = false;
	Type coefficient;
	ipoint<3> i;

	if(this->empty()) {
		os << "0.";
		return;
	}

	for( i=this->begin() ; i != this->end() ; i = this->next(i)) {

		coefficient = this->getData(i);

		if(has_previous) {
			os << (coefficient > 0 ? " +" :" ");
		}

		has_previous = false;

		if(i==ipoint<3>(0)) {
			os << coefficient;
			has_previous = true;

		} else { 

			if(fabs(coefficient) != 1) {
				os << coefficient;
				has_previous = true;		
			} else if(coefficient == -1) {
				os << "-" ;
			}

			if(has_previous)
				os << "*";

			os  << getBaseString(i);
			has_previous = true;

		} 
	} 
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Extern Out Stream operator.
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
template<typename Type>
ostream & operator << (ostream & out , const polynomeBase3D<Type> & poly)
{
	poly.write(out);
	return out;
}
#endif

