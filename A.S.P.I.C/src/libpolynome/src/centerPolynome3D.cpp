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
#include "centerPolynome3D.h"
#include "string4Polynomes.h"

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// The Default constructor.
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
centerPolynome3D::centerPolynome3D(void)
: polynome3D() , Center(0)
{
	;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// The Copy constructor.
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
centerPolynome3D::centerPolynome3D(const centerPolynome3D & centerPoly)
: polynome3D() , Center(0)
{
	copy(centerPoly);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Le constructeur avec sp�cification des coefficients.
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
centerPolynome3D::centerPolynome3D(const polynome3D & poly)
: polynome3D() , Center(0)
{
	setPolynomeCoefficients(poly);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Le constructeur avec sp�cification des coefficients et du centre.
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
centerPolynome3D::centerPolynome3D(const polynome3D & poly , const dpoint<3> & center)
: polynome3D() , Center(0)
{
	setPolynomeCoefficients(poly);
	setCenter(center);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// The Destructor.
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
centerPolynome3D::~centerPolynome3D(void)
{
	;
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// M�thode qui ajoute root comme racine au polynome3D.
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
centerPolynome3D centerPolynome3D::centerMonomeMultiply(const double & root , const int & dimension) const
{
	assert(dimension >= 0);
	assert(dimension < 3);

	centerPolynome3D shiftedPolynome3D;

	shiftedPolynome3D.setPolynomeCoefficients(polynome3D::centerMonomeMultiply(root - getCenter()[dimension] , dimension));
	shiftedPolynome3D.setCenter(getCenter());

	return shiftedPolynome3D;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// M�thode qui ajoute root comme racine  avec un ordre degree au polynome3D.
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
centerPolynome3D centerPolynome3D::centerMonomeMultiply(const double & root , const int & dimension , const int & degree) const
{
	int i;
	centerPolynome3D shiftedPolynome3D(*this);

	for(i=0 ; i < degree ; i++) {
		shiftedPolynome3D = shiftedPolynome3D.centerMonomeMultiply(root,dimension);
	}

	return shiftedPolynome3D;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// The method that changes the center of the polynome3D without changing the polynome3D.
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
centerPolynome3D centerPolynome3D::changeCenter(const dpoint<3> & center) const
{
	if(getCenter() == center) {
		return *this;
	}

	centerPolynome3D newPolynome3D(0);

	polynome3D basePolynome3D;	
	polynome shiftPolynome[3];

	shiftPolynome[0].setPolynomeCoefficients(1);
	shiftPolynome[1].setPolynomeCoefficients(1);
	shiftPolynome[2].setPolynomeCoefficients(1);

	for(ipoint<3> i = begin() ; i!=end() ; i= next(i)) {

		for(int dim = 0 ; dim < 3 ; dim++) {	
			int offset = i[dim] - shiftPolynome[dim].getDegree();
			if(offset < 0) {
				shiftPolynome[dim].setPolynomeCoefficients(1);
				offset = i[dim]; 
			}

			if(offset > 0) {
				shiftPolynome[dim] = shiftPolynome[dim].centerMonomeMultiply(getCenter()[dim] -center[dim], offset);
			}
		}

		basePolynome3D.setPolynomeCoefficients(shiftPolynome[0] , shiftPolynome[1] , shiftPolynome[2]);
		newPolynome3D.add( getData(i) * basePolynome3D );
	}

	return newPolynome3D;
}


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// The Copy method.
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void centerPolynome3D::copy(const centerPolynome3D & cp)
{
	polynome3D::copy(cp);
	setCenter(cp.getCenter());
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// M�thode pour d�river.
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
centerPolynome3D centerPolynome3D::derivate(const int & dimension) const
{
	assert(dimension >= 0);
	assert(dimension < 3);

	centerPolynome3D deriv;
	deriv.setPolynomeCoefficients(polynome3D::derivate(dimension));
	deriv.setCenter(getCenter());
	return deriv;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// M�thode pour d�river.
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
centerPolynome3D centerPolynome3D::derivateX(void) const
{
	return derivate(0);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// M�thode pour d�river.
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
centerPolynome3D centerPolynome3D::derivateY(void) const
{
	return derivate(1);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// M�thode pour d�river.
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
centerPolynome3D centerPolynome3D::derivateZ(void) const
{
	return derivate(2);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// The GET method for the string that represents the basis for the polynomial decomposition.
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const string centerPolynome3D::getBaseString(int degree) const
{
	return monome3D2string(degree, getCenter());
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// The GET method for the center of the polynome3D.
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const dpoint<3> & centerPolynome3D::getCenter(void) const
{
	return Center;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// M�thode qui permet d'ajouter un z�ro au polynome.
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
centerPolynome3D centerPolynome3D::monomeMultiply(const int & degree) const
{
	assert( degree >=0);

	centerPolynome3D shiftedPolynome3D;

	shiftedPolynome3D = polynome3D::monomeMultiply(degree);
	shiftedPolynome3D.setCenter(getCenter());

	return shiftedPolynome3D;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Op�rateur d'affectation.
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
centerPolynome3D & centerPolynome3D::operator= (const centerPolynome3D & centerPoly)
{
	copy(centerPoly);
	return *this;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Op�rateur d'affectation pour un polynome3D standart.
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
centerPolynome3D & centerPolynome3D::operator= (const polynome3D & poly)
{
	polynome3D::copy(poly);
	setCenter(0);
	return *this;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Operateur pour faire l'addition de deux polynomes.
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
centerPolynome3D centerPolynome3D::operator+ (const centerPolynome3D & p) const
{
	centerPolynome3D tmp , pCentered;

	if(getCenter() != p.getCenter()) {
		pCentered = p.changeCenter(getCenter());
	} else {
		pCentered = p;
	}
	
	tmp.add(*this,pCentered);
	tmp.setCenter(getCenter());

	return tmp;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Operateur pour faire l'addition unaire de deux polynomes.
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
centerPolynome3D & centerPolynome3D::operator+= (const centerPolynome3D & p)
{
	centerPolynome3D pCentered;
	
	if(getCenter() != p.getCenter()) {
		pCentered = p.changeCenter(getCenter());
	} else {
		pCentered = p;
	}
	
	add(pCentered);

	return *this;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Operateur pour faire la multiplication de deux polynomes.
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
centerPolynome3D centerPolynome3D::operator* (const centerPolynome3D & p) const
{
	centerPolynome3D tmp , pCentered;

	if(getCenter() != p.getCenter()) {
		pCentered = p.changeCenter(getCenter());
	} else {
		pCentered = p;
	}
	
	tmp.multiply(*this,pCentered);
	tmp.setCenter(getCenter());

	return tmp;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Operateur pour faire la multiplication unaire de deux polynomes.
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
centerPolynome3D & centerPolynome3D::operator*= (const centerPolynome3D & p)
{
	centerPolynome3D pCentered;
	
	if(getCenter() != p.getCenter()) {
		pCentered = p.changeCenter(getCenter());
	} else {
		pCentered = p;
	}
	
	multiply(pCentered);

	return *this;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Operateur pour faire la multiplication d'un polynome3D et d'un scalaire.
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
centerPolynome3D centerPolynome3D::operator* (const double & scalar) const
{
	centerPolynome3D tmp;
	tmp.setCenter(getCenter());
	tmp.multiply(*this,scalar);
	return tmp;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Operateur pour faire la multiplication unaire d'un polynome3D et d'un scalaire.
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
centerPolynome3D & centerPolynome3D::operator*= (const double & scalar)
{
	multiply(scalar);
	return *this;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Operateur pour faire la multiplication d'un scalaire et d'un polynome3D.
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
centerPolynome3D operator* (const double & scalar , const centerPolynome3D & p)
{
	return p*scalar;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Operateur pour faire la soustraction de deux polynomes.
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
centerPolynome3D centerPolynome3D::operator- (const centerPolynome3D & p) const
{
	centerPolynome3D tmp , pCentered;

	if(getCenter() != p.getCenter()) {
		pCentered = p.changeCenter(getCenter());
	} else {
		pCentered = p;
	}
	
	tmp.soustract(*this,pCentered);
	tmp.setCenter(getCenter());

	return tmp;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Operateur pour faire la soustraction unaire de deux polynomes.
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
centerPolynome3D & centerPolynome3D::operator-= (const centerPolynome3D & p)
{
	centerPolynome3D pCentered;
	
	if(getCenter() != p.getCenter()) {
		pCentered = p.changeCenter(getCenter());
	} else {
		pCentered = p;
	}
	
	soustract(pCentered);

	return *this;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Op�rateur pour la division d'un polynome3D par un scalaire.
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
centerPolynome3D centerPolynome3D::operator/ (const double & scalar) const
{
	assert(scalar != 0);
	centerPolynome3D tmp;
	tmp.setCenter(getCenter());
	tmp.divide(*this,scalar);
	return tmp;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Op�rateur pour la division unaire d'un polynome3D par un scalaire.
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
centerPolynome3D & centerPolynome3D::operator /=(const double & scalar)
{
	assert(scalar != 0);
	divide(scalar);
	return *this;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// M�thode pour faire un changement de variable lin�aire.
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
centerPolynome3D centerPolynome3D::scale(const double & scalar) 
{
	centerPolynome3D scaledPolynome3D;

	if(scalar == 0) {
		scaledPolynome3D.clear();
		return scaledPolynome3D;
	}

	scaledPolynome3D = polynome3D::scale(scalar);
	scaledPolynome3D.setCenter(getCenter() / scalar);
	return scaledPolynome3D;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// The SET method for the center of the polynome3D.
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void centerPolynome3D::setCenter(const dpoint<3> & center)
{
	Center = center;
}
