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
#ifndef _CENTER_POLYNOME_3D_
#define _CENTER_POLYNOME_3D_

#include "polynome3D.h"

class centerPolynome3D : public polynome3D
{
private:
	
	/**
	 * The centering point of the polynome.
	 */
	dpoint<3> Center;

protected:
	/**
	 * M�thode pour faire la copie.
	 *
	 * @param centerPoly le polynome que l'on souhaite copier dans l'objet.
	 */
	void copy(const centerPolynome3D & centerPoly);
  
 	/**
	 * Methode pour afficher les fonction de base.
	 *
	 * Comme nous travaillons ici avec les polyn�mes usuel la 
	 * fonction de base pour un degr� d, s'�criit "x^d".
	 *
	 * @param i le degr� de la fonction de base qui l'on cherche � convertir en
	 * chaine de charact�res.
	 *
	 * @return la chaine de charact�re qui rep�sente la fonction de base, ie "1" lorsque
	 * le degr� est nul et "x^d" lorsque le degr� demand� est sup�rieur ou �gal � 1.
	 */
 virtual const string getBaseString(int i) const;

public:

	/**
	 * The default constructor.
	 */
	centerPolynome3D(void);

	/**
	 * Le constructeur de copie.
	 *
	 * @param centerPoly le polynome avec lequel on souhaite initialiser le nouvel objet.
	 */
	centerPolynome3D(const centerPolynome3D & centerPoly);

	/**
	 * Le constructeur avec sp�cification des coefficients du polynome.
	 *
	 * @param poly les coefficients avec lequels on souhaite initialiser l'objet.
	 */
	centerPolynome3D(const polynome3D & poly);

	/**
	 * Le constructeur avec sp�cification des coefficients du polynome et du centre.
	 *
	 * @param poly les coefficients avec lequels on souhaite initialiser l'objet.
	 *
	 * @param center le point de centrage de l'objet cr��.
	 */
	centerPolynome3D(const polynome3D & poly , const dpoint<3> & center);

	/**
	 * The destructor.
	 */
	~centerPolynome3D(void);

	/**
	 * Methode qui multiplie un polynome par (x-root).
	 * Autrement dit cela revient � ajouter root comme z�ro du polynome.
	 *
	 * @param root la valeur du z�ro � ajouter au polynome.
	 *
 	 * @param dimension la dimension (x,y ou z).
	 *
	 * @return le polynome produit de (x-root) et de l'objet.
	 */
	centerPolynome3D centerMonomeMultiply(const double & root , const int & dimension)const;

	/**
	 * Methode qui multiplie un polynome par (vatiable-root)^degree.
	 *
	 * @param root Point de centrage du monome..
	 *
	 * @param dimension parametre pour choisr avec quelle variable on souhaite op�rer.
	 * Lorsque dimension prend la valeur 0, alors on op�re sur la variable x, lorsque dimension
	 * prend la valeur 1 alors on op�-re sur la varaible y et lorsque dimension vaut 3 on op�re
	 * avec la variable z.
	 *
	 * @param degree l'ordre avec lequel on souhaite ajouter la racine au polynome. 
	 *
	 * @return le polynome produit de (variable-root) et de l'objet.
	 */
	 centerPolynome3D centerMonomeMultiply(const double & root , const int & dimension , const int & degree) const;

	/**
	 * M�thode qui calcule la nouvelle expression du polynome lorsque l'on change sont centre
	 * mais qu'il reste identique...
	 *
	 * @param center la valeur du nouveau centrage pour le polynome.
	 */
	centerPolynome3D changeCenter(const dpoint<3> & center) const;
	
	/**	
	 * Methode pour d�river le polynome.
	 *
	 * @return le polynome issu de la d�rivation de l'objet.
	 */
	 centerPolynome3D derivate(const int & dimension) const;

	/**	
	 * Methode pour d�river le polynome.
	 *
	 * @return le polynome issu de la d�rivation de l'objet.
	 */
	 centerPolynome3D derivateX(void) const;

	/**	
	 * Methode pour d�river le polynome.
	 *
	 * @return le polynome issu de la d�rivation de l'objet.
	 */
	 centerPolynome3D derivateY(void) const;

	/**	
	 * Methode pour d�river le polynome.
	 *
	 * @return le polynome issu de la d�rivation de l'objet.
	 */
	 centerPolynome3D derivateZ(void) const;

	/**
	 * M�thode pour connaitre la valeur du centre du polynome
	 *
	 * @return le point de centrage pour les monomes qui composent le polynome.
	 */
	const dpoint<3> & getCenter(void) const;

	/**
	 * Methode qui multiplie un polynome par x^degree.
	 *
	 * @param degree le degree du monome avec lequel souhaite multiplier le polynome.
	 *
	 * @return le polynome qui contient le produit de (x-center)^d et de l'objet.
	 */
	centerPolynome3D monomeMultiply(const int & degree=1) const;

	/**
	 * Operateur pour l'assignement.
	 * 
	 * @param centerPoly le polynome que l'on souhaite copier dans
	 * l'objet appelant.
	 *
	 * @return une r�f�rence vers le nouveau polynome.
	 */
	centerPolynome3D & operator= (const centerPolynome3D & centerPoly);

	/**
	 * Operateur pour l'assignement.
	 * 
	 * @param poly le polynome que l'on souhaite copier dans
	 * l'objet appelant. Dans ce cas le centre du polynome centr� 
	 * sera fix� � z�ro.
	 *
	 * @return une r�f�rence vers le nouveau polynome.
	 */
	centerPolynome3D & operator= (const polynome3D & poly);

	/**
	 * Operateur pour faire l'addition de deux polynomes.
	 *
	 * @param p le polynome que l'on souhaite ajouter � l'objet.
	 *
	 * @return un polynome qui contient la somme demand�e.
	 */
	centerPolynome3D operator+ (const centerPolynome3D & p) const;

	/**
	 * Op�rateur pour faire une addition unaire de deux polynomes.
	 *
	 * @param p le polynome que l'on souhaite ajouter � l'objet.
	 *
	 * @return une r�f�rence vers le polynome qui contient la somme demand�e.
	 */
	centerPolynome3D & operator+= (const centerPolynome3D & p);	

		/**
	 * Operateur pour faire la soustraction de deux polynomes.
	 *
	 * @param p le polynome que l'on souhaite soustraire ajouter � l'objet.
	 *
	 * @return un polynome qui contient la diff�rence demand�e.
	 */
	centerPolynome3D operator- (const centerPolynome3D & p) const;

	/**
	 * Operateur pour faire la soustraction unaire de deux polynomes.
	 *
	 * @param p le polynome que l'on souhaite soustraire � l'objet.
	 *
	 * @return une r�f�rence vers le polynome qui contient la diff�rence demand�e.
	 */
	centerPolynome3D & operator-= (const centerPolynome3D & p);

	/**
	 * Operateur pour faire la multiplication de deux polynomes.
	 * 
	 * @param p le polynome avec lequel on souhaite multiplier l'objet.
	 *
	 * @return un polynome qui contient le produit demand�.
	 */
	centerPolynome3D operator* (const centerPolynome3D & p) const;

	/**
	 * Operateur pour faire une multiplication unaire de deux polynomes.
	 * 
	 * @param p le polynome avec lequel on souhaite multiplier l'objet.
	 *
	 * @return une r�f�rence vers le polynome qui contient le produit demand�.
	 */
	centerPolynome3D & operator*= (const centerPolynome3D & p);

	/**
	 * Operateur pour faire la multiplication d'un polynome et d'un scalaire.
	 * 
	 * @param scalar le scalaire avec lequel on souhaite multiplier l'objet.
	 *
	 * @return un polynome qui contient le produit demand�.
	 */
	centerPolynome3D operator* (const double & scalar) const;

	/**
	 * Operateur pour faire une multiplication unaire d'un polynome et d'un scalaire.
	 * 
	 * @param scalar le scalaire avec lequel on souhaite multiplier l'objet.
	 *
	 * @return une r�f�rence vers le polynome qui contient le produit demand�.
	 */
	centerPolynome3D & operator *= (const double & scalar);

	/**
	 * Operateur pour faire la disision d'un polynome et d'un scalaire.	
	 *
	 * @param scalar le scalaire par lequel on souhaite diviser l'objet.
	 *
	 * @return un polynome qui contient le quotient demand�.
	 */
	centerPolynome3D operator/ (const double & scalar) const;

	/**
	 * Operateur pour faire une division unaire d'un polynome et d'un sclaire.
	 *
	 * @param scalar le scalaire par lequel on souhaite diviser l'objet.
	 *
	 * @return une r�f�rence vers le polynome qui contient le quotient demand�.
	 */
	centerPolynome3D & operator/= (const double & scalar);

	/**
	 * M�thode pour changer la varialble lin�aire.
	 *
	 * @param scalar le facteur du changement de variable.
	 *
	 * @return la forme du polynome apr�s le changement de variable.
	 */
	centerPolynome3D scale(const double & scalar);

	/**
	 * The SET method for the centering point of the polynome.
	 */
	void setCenter(const dpoint<3> & center);
};

/**
 * Op�rateur de multiplication d'un scalaire et d'un polynome.
 *
 * @param scalar un scalaire.
 *
 * @param poly un polynome
 *
 * @return le polynome produit du scalaire et du polynome.
 */
extern centerPolynome3D operator*(const double & scalar , const centerPolynome3D & poly);

#endif
