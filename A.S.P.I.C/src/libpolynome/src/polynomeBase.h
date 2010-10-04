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
#ifndef _POLYNOME_BASE_
#define _POLYNOME_BASE_

#include <assert.h>
#include <containorSparse.h>
#include <iostream>
#include <map>
#include <string>
#include "string4Polynomes.h"

using namespace std;

/**
 * Cette classe permet de stocker les coefficients
 * d'un objet sur une base qui peut etre 
 * inifinie.
 */
template<typename Type>
class polynomeBase : public containorSparse<Type>
{	
private:
	
protected:
	/**
	 * M�thode pour afficher une fonction de base
	 *
	 * Le probl�me est de pouvoir afficher tout les polynomes
	 * sans avoir � r��crire de m�thode write ou d'op�rateur <<.
	 * Pour cela on demande � toutes les classes enfants de r�impl�menter
	 * cette m�thode comme cela chaque classe affichera correctement
	 * la base de polyn�mes qui lui convient.
	 *
	 * Par exemple dans polynome le getBaseString affichera quelque
	 * chose comme X^d . Y^dy . Z^dz alors que pour un polynome centr�
	 * on pourra afcher (X-CenterX)^dx . (Y-CenterY)^dy . (Z-CenterZ)^dz
	 *
	 * @param degree le degr�� de la fonction de base du polynome dont 
	 * on souhaite connaitre la repr�sentation.
	 */  
	virtual const string getBaseString(const int & degree) const;
  
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
	void add(const polynomeBase<Type> & p , const polynomeBase<Type> & q);

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
	void add(const polynomeBase<Type> & q);

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
	void divide(const polynomeBase<Type> & poly , const Type & scalar);

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
	void multiply(const polynomeBase<Type> & p , const polynomeBase<Type> & q);
	
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
	void multiply(const polynomeBase<Type> & q);

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
	void multiply(const polynomeBase<Type> & poly , const Type & scalar);

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
	 * M�thode de base pour faire la soustraction de deux polynomes.
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
	void soustract(const polynomeBase<Type> & p , const polynomeBase<Type> & q);

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
	void soustract(const polynomeBase<Type> & q);

public:
  
  /**
   * Constructeur par d�faut.
   */
  polynomeBase(void);
  
  /**
   * Construcuteur de copie.
   *
	 * @param poly le polynome avec lequel le nouvel objet est initialis�.
	 */
	polynomeBase(const polynomeBase<Type> & poly);

	/**
   * Destucteur.
   */
  virtual ~polynomeBase(void);
    
  /**
   * Methode pour connaitre le degr� du polynome.
	 *
	 * @return le degr� du polynome.
   */
  int getDegree(void) const;
  
  /**
   * Mehode pour l'affchage du polynome.
	 *
	 * @param os le flux dans lequel on souahite �crire le polynome.
   */
  void write(ostream & os) const;
};


/**
 * Op�rateur pour �crire un polynome dans un flux.
 * 
 * @param out le flux dans lequel on souhaite �crire le polynome.
 *
 * @param poly le polynome que l'on souahite �crire.
 */ 
template<typename Type>
ostream & operator<<(ostream & out , const polynomeBase<Type> & poly);


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Le constructeur par d�faut.
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
template<typename Type>
polynomeBase<Type>::polynomeBase(void)
: containorSparse<Type>()
{
 this->clear();
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Le constructeur copie.
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
template<typename Type>
polynomeBase<Type>::polynomeBase(const polynomeBase<Type> & poly)
: containorSparse<Type>()
{
  containorSparse<Type>::copy(poly);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Le destructeur.
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
template<typename Type>
polynomeBase<Type>::~polynomeBase(void)
{
  this->clear();
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// M�thode pour faire l'addition de deux polynomes.
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
template<typename Type>
void polynomeBase<Type>::add(const polynomeBase<Type> & p , const polynomeBase<Type> & q)
{
	containorSparse<Type>::copy(p);
	add(q);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// M�thode pour faire l'addition unaire de deux polynomes.
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
template<typename Type>
void polynomeBase<Type>::add(const polynomeBase<Type> & q)
{
	int degree;
	Type value;

	for(degree = q.begin() ; degree != q.end() ; degree = q.next(degree)) {
		value = q[degree] + this->getData(degree);
		setData(degree , value);
	}
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// M�thode pour faire la division d'un polynome et d'un scalaire.
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
template<typename Type>
void polynomeBase<Type>::divide(const polynomeBase<Type> & poly , const Type & scalar)
{
	assert(scalar != 0);

	containorSparse<Type>::copy(poly);
	divide(scalar);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// M�thode pour faire la division unaire d'un polynome et d'un scalaire.
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
template<typename Type>
void polynomeBase<Type>::divide(const Type & scalar)
{
	assert(scalar != 0);

	int i;
	Type value;
	
	for(i=(this->begin()) ; i != (this->end()) ; i= (this->next(i))) {
		value = this->getData(i) / scalar;
		setData(i,value);
	}
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// M�thode pour conaitre le degr� du polynome.
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
template<typename Type>
int polynomeBase<Type>::getDegree(void) const
{
	// !! Attention !! lorsque le polynome est vide : le polynome est nul.
	// Donc son degr� est 0. Si on ne catch pas l'exception ici le rbegin
	// est un rend et cela renvoie -1. Ce qui est une ab�ration.
	if(this->empty()) {
		return 0;
	}

	return this->rbegin();
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// M�thode pour conaitre le degr� du polynome.
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
template<typename Type>
const string polynomeBase<Type>::getBaseString(const int & degree) const
{
	return monome2string("x",0,degree);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Methode pour faire la multiplication de deux polynomes
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
template<typename Type>
void polynomeBase<Type>::multiply(const polynomeBase<Type> & p , const polynomeBase<Type> & q)
{
	int i,j;
	Type value;

	this->clear();

	for(i=q.begin() ; i != q.end() ; i=q.next(i)) {
		for(j=p.begin() ; j != p.end() ; j=p.next(j)) {
			value = this->getData(i+j) + q[i] * p[j];
			setData(i+j , value);
		}
	}
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Methode pour faire la multiplication unaire de deux polynomes
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
template<typename Type>
void polynomeBase<Type>::multiply(const polynomeBase<Type> & q)
{
	polynomeBase tmp(*this);
	multiply(tmp,q);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// M�thode pour faire la multiplication unaire de d'un polynome et d'un scalaire.
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
template<typename Type>
void polynomeBase<Type>::multiply(const Type & scalar)
{
	int degree;
	Type value;

	if(scalar == 0) {
		this->clear();
		return;
	}
	
	for(degree = (this->begin()) ; degree != (this->end()) ; degree =(this->next(degree))) {
		value = scalar *  (this->getData(degree));
		setData(degree , value);
	}
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// M�thode pour faire la multiplication de d'un polynome et d'un scalaire.
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
template<typename Type>
 void polynomeBase<Type>::multiply(const polynomeBase<Type> & p , const Type & scalar)
{
	containorSparse<Type>::copy(p);
	multiply(scalar);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// M�thode pour faire la soustraction de deux polynomes.
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
template<typename Type>
void polynomeBase<Type>::soustract(const polynomeBase<Type> & p , const polynomeBase<Type> & q)
{
	containorSparse<Type>::copy(p);
	soustract(q);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// M�thode pour faire la soustraction unaire de deux polynomes.
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
template<typename Type>
void polynomeBase<Type>::soustract(const polynomeBase<Type> & q)
{
	int degree;
	Type value;

	for(degree = q.begin() ; degree != q.end() ; degree = q.next(degree)) {
		value = this->getData(degree) - q[degree];
		setData(degree , value);
	}

}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Method WRITE for the polynome.
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
template<typename Type>
void polynomeBase<Type>::write(ostream & os) const
{
	bool has_previous = false;
	Type coefficient;
	int i;

	if(this->empty()) {
		os << "0.";
		return;
	}

	for( i=(this->begin()) ; i != (this->end()) ; i =(this->next(i))) {

		coefficient = this->getData(i);

		if(has_previous) {
			os << (coefficient > 0 ? " +" :" ");
		}

		has_previous = false;

		if(i==0) {
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
ostream & operator << (ostream & out , const polynomeBase<Type> & poly)
{
	poly.write(out);
	return out;
}

#endif
