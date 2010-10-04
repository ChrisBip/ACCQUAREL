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
#ifndef _GAUSSIAN_3D_
#define _GAUSSIAN_3D_

#include <containor3D.h>
#include <dpoint.h>

/**
 * On d�clare ici la classe gaussianPolynome_3D.
 */
class gaussianPolynome3D;

class gaussian3D
{
private:
	/** 
	 * Le centre de la gaussienne.
	 */
	dpoint<3> Center;

	/**
	 * Le coefficient devant la gaussienne.
	 */
	double Coefficient;

	/**
	 * L'exposant de la gaussienne.
	 */
	double Exponent;
	
protected:

	/**
	 * M�thode pour copier les gaussiennes.
	 */
	void copy(const gaussian3D & g);	

public:

	/**
	 * Constructeur de la classe gaussienne.
	 */
	gaussian3D(void);
	
	/**
	 * Constrcuteur avec sp�cification des param�tres.
	 */
	gaussian3D(const dpoint<3> & center , const double & coefficient , const double & exponent);

	/**
	 * Constructeur de copie.
	 */
	gaussian3D(const gaussian3D & g);

	/**
	 * Destructeur de la classe gaussienne.
	 */
	~gaussian3D(void);

	/**
	 * M�thode pour comparer deux gaussiennes :
	 * @TO DEFINE.
	 */
	static double compare(const gaussian3D & ga , const gaussian3D & gb);
	
	/**
	 * M�thode pour calculer le centre de la gaussienne
	 * produit de deux gaussiennes.
	 */
	static dpoint<3> computeCenter(const gaussian3D  & ga , const gaussian3D & gb);


	/**
	 * M�thode pour calculer le coefficient de la gaussienne
	 * produit de deux gaussiennes.
	 */
	static double computeCoefficient(const gaussian3D & ga , const gaussian3D & gb);

	/**
	 * M�thode pour calculer le coefficient de la gaussienne
	 * produit de deux gaussiennes.
	 */
	static double computeExponent(const gaussian3D & ga , const gaussian3D & gb);

	/**
	 * M�thode pour calculer la d�riv�e d'une gaussienne.
	 *
	 * Attention !! le parametre dim repr�sente la direction
	 * de d�rivation : 0 rep�sente la d�rivation par rapport
	 * � x, 1 par rapport � y, 2 par rapport � z.
	 */
	gaussianPolynome3D derivate(int dim) const;

	/**
	 * Method to eval the value of the gaussian 
	 * in the point x.
	 */
	double eval(const dpoint<3> & position) const;
	
	/**
	 * M�thode pour connaitre le centre.
	 */
	const dpoint<3> & getCenter(void) const;
	
	/**
	 * M�thode pour connaitre le coefficient.
	 */
	const double & getCoefficient(void) const;

	/**
	 * M�thode pour connaitre l'exposant.
	 */ 
	const double & getExponent(void) const;

	/**
	 * M�thode pour calculer l'int�grale sur R de la gaussienne.
	 *
	 * \f[ 
	 * \int_{R}{C \exp(-\alpha (X-X_0)^2 )}
	 * \f]
	 */
	double integral(void) const;
	
	/**
	 * M�thode pour calculer l'int�grale sur R de la gaussienne.
	 */
	void integrals(const ipoint<3> & deg_max , containor3D<double> & overlaps) const;
	
	/**
	 * M�thode pour faire la multiplication.
	 */
	void multiply(const gaussian3D & ga , const gaussian3D & gb);

	/**
	 * M�thode pour faire la multiplication.
	 */
	void multiply(const gaussian3D & g);
	
	/**
	 * M�thode pour faire la multiplication.
	 */
	void multiply(const gaussian3D & g , const double & scalar);

	/**
	 * M�thode pour faire la multiplication.
	 */
	void multiply(const double & scalar);
	
	/**
	 * Multiplication sous forme d'op�rateur.
	 */
	gaussian3D operator*(const gaussian3D & g) const;
	
	/**
	 * Multiplication sous forme d'op�rateur.
	 */
	gaussian3D & operator*=(const gaussian3D & g);
	
	/**
	 * Multiplication sous forme d'op�rateur.
	 */
	gaussian3D operator*(const double & scalar) const;
	
	/**
	 * Multiplication sous forme d'op�rateur.
	 */
	gaussian3D & operator*=(const double & scalar);
	
	/**
	 * M�thode pour fixer le centre.
	 */
	void setCenter(const dpoint<3> & center);

	/**
	 * M�thode pour fixer le centre.
	 */
	void setCenter(const double & center_x, const double & center_y , const double & center_z);

	/**
	 * M�thode pour fixer le coefficient.
	 */
	void setCoefficient(const double & coefficient);

	/**
	 * M�thode pour fixer l'exposant.
	 */
	void setExponent(const double & exponent);

	/**
	 * M�thode pour �crire.
	 */
	void write(ostream & outStream) const;
	
};

/**
 * Op�rateur externe de multiplication par un scalaire.
 */
extern gaussian3D operator*(const double & scalar , const gaussian3D & g);


/**
 * Op�rateur externe d'�criture dans un flux.
 */
extern ostream & operator<<(ostream & outStream , const gaussian3D & g);


/////////////////////////////////////////////////////////////////////////////////////
//  !! DO NOT MOVE !!
//
// On inclut les d�claration de classe gaussianPolynome3D pour que l'utilisateur 
// puisse utiliser la m�thode d�rivate ais�ment (pas vraiment d'include � rajouter
// dans le bon ordre dans le programe appelant).
//
// Mais il faut mettre cet include apr�s les d�claration de la classe gaussian3D 
// parce que la compilation de la classe gaussianPolynome3D n�cessite 
// la connaissance de la classe gaussienne
////////////////////////////////////////////////////////////////////////////////////
#include "gaussianPolynome3D.h"


#endif

