/* 
* The gaussian library of the A.S.P.I.C. 
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
#ifndef _GAUSSIAN_POLYNOME_
#define _GAUSSIAN_POLYNOME_

#define _USE_MATH_DEFINES

#include "gaussian.h"
#include <iostream>
#include <math.h>
#include <polynome.h>
#include <string4Polynomes.h>
using namespace std;

/**
 * D�finition d'une classe qui est le produit d'un polynome et d'une gaussienne.
 * 
 * Cette classe impl�mente les objets de la forme 
 * 
 * \f C.exp(- alpha (x - x)^2 ) ( sum_{k}{a_k (x-x)^k}) \f
 *
 *
 */ 
class gaussianPolynome : public gaussian , protected polynome
{
private:


protected:

	/**
	 * M�thode pour faire la copie.
	 */
	virtual void copy(const gaussianPolynome & gp);
	
	/**
	 * M�thode pour afficher la tete des monomes de base du polynome.
	 */
	const virtual string getBaseString(const int & i) const;
	
public:
	/**
	 * Constrcteur par d�faut.
	 */
	gaussianPolynome(void);

	/**
	 * Constructeur de copie.
	 */
	gaussianPolynome(const gaussianPolynome & gp);

	/**
	 * Constrcteur avec une gaussienne.
	 */
	gaussianPolynome(const gaussian & g);

	/**
	 * Destructeur.
	 */
	virtual ~gaussianPolynome(void);

	/**
	 * Methode qui multiplie un polynome par (variable-root)
	 * Autrement dit cela revient � ajouter root comme z�ro du polynome.
	 *
	 * @param root la valeur du z�ro � ajouter au polynome.
	 *
	 * @return le polynome produit de (variable-root) et de l'objet.
	 *
	 * @warning la dimension ne peut prendre que les valeur 0,1 ou 2.
	 */
	gaussianPolynome centerMonomeMultiply(const double & root)const;

	/**
	 * Methode qui multiplie un polynome par (x-root)^degree
	 *
	 * @param root la valeur du z�ro � ajouter au polynome.
	 *
	 * @return le polynome produit de (x-root)^degree et de l'objet.
	 *
	 * @warning il faut que le degr� soit positif ou nul.
	 */
	gaussianPolynome centerMonomeMultiply(const double & root , const int & degree)const;

	/**
	 * M�thode pour changer le centre de la gaussienne.
	 *
	 * Attention !! :
	 * En fait la m�thode set_center permet de fixer la valeur du centre
	 * tout betement. Cette m�thode � pour objectif de changer la valeur
	 * du centre et de conserver le polynome comme il �tait auparavant.
	 */
	void changeCenter(const double & center);

	/**
	 * M�thode pour mettre le polynome � 0.
	 */
	void clearPolynome(void);

	/**
	 * M�thode pour d�river.
	 */
	gaussianPolynome derivate(void) const;

	/**
	 * M�thode pour claculer l'int�grale sur R du polynome gaussien.
	 */
	double integral(void) const;

	/**
	 * M�thode pour acc�der aux coefficients du polynome
	 *
	 * A cause de l'heritage multiple cette m�thode doit
	 * etre r�impl�ment�e dans la classe gaussianPolynome.
	 */
	const polynome & getPolynomeCoefficients(void) const;

	/**
	 * M�thode pour acc�der aux coefficients du polynome
	 *
	 * A cause de l'heritage multiple cette m�thode doit
	 * etre r�impl�ment�e dans la classe gaussianPolynome.
	 */
	double getPolynomeCoefficient(const int & degree) const;
	
	/**
	 * M�thode pour acc�der au degr� du polynome.
	 */
	int getPolynomeDegree(void) const;

	/**
	 * La multiplication de deux gaussiennes polynomes.
	 */
	void multiply(gaussianPolynome gp_a , gaussianPolynome gp_b);

	/**
	 * La multiplication unaire de deux gaussiennes polynomes.
	 */
	void multiply(const gaussianPolynome & gaussianPoly);

	/**
	 * La multiplication d'une gaussienne polynome et d'in scalaire.
	 */
	void multiply(const gaussianPolynome & gaussianPoly , const double & scalar);

	/**
	 * La multiplication uanire d'une gaussienne polynome et d'un scalaire.
	 */
	void multiply(const double & scalar);

	/**
   * Op�rateur pour faire la multiplication de deux gaussiennes
	 * polynome.
	 */
	gaussianPolynome operator* (const gaussianPolynome & gaussianPoly) const;

	/**
   * Op�rateur pour faire la multiplication de deux gaussiennes
	 * polynome.
	 */
	gaussianPolynome operator* (const double & scalar) const;

	/**
   * Op�rateur pour faire la multiplication unaire de deux gaussiennes
	 * polynome.
	 */
	gaussianPolynome & operator*= (const gaussianPolynome & gaussianPoly);

	/**
   * Op�rateur pour faire la multiplication unaire de deux gaussiennes
	 * polynome.
	 */
	gaussianPolynome & operator*= (const double & scalar);

	/**
	 * Op�rateur d'affectation.
	 */
	gaussianPolynome & operator =(const gaussianPolynome & gaussianPoly);

	/**
	 * Op�rateur d'affectation.
	 */
	gaussianPolynome & operator =(const gaussian & g);

	/**
	 * M�thode qui calcule la valeur de la primitive
	 * du polynome gaussien en x.
	 */
	double primitive(const double & x) const;

	/**
	 * M�thode pour donner au polynome une valeur constante.
	 */
	void setPolynomeCoefficients(const double & value);

	/**
	 * M�thode pour fixer le polynome.
	 */
	void setPolynomeCoefficients(const polynome & poly);

	/**
	 * M�thode pour modifier les coefficients du polynome.
	 *
	 * @param degree le degr� du coefficient � modifier.
	 *
	 * @param value la nouvelle valeur du coefficient.
	 */
	void setPolynomeCoefficient(const int & deg , const double & value);

	/**
	 * M�thode pour �crire dans un flux.
	 *
	 * @param out le flux dans lequel on souhaite afficher.
	 */
	void write(ostream & outStream) const;
};

/**
 * Op�rateur externe pour l'affichage.
 *
 * @param outStream le flux dans lequel on souahaire afficher.
 *
 * @param gaussianPoly le polynome gaussien que l'on souahite afficher.
 */
extern ostream & operator<<( ostream & outStream , const gaussianPolynome & gaussianPoly);

#endif
