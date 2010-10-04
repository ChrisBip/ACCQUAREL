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
#ifndef _COMPLEX_POLYNOME_3D_
#define _COMPLEX_POLYNOME_3D_

#include "polynomeBase3D.h"
#include <complex.h>

class complexPolynome3D : public polynomeBase3D<complex>
{
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
	virtual const string  getBaseString(const ipoint<3> & i) const;

public:

	/**
	 * Constructeur par defaut.
	 */
	complexPolynome3D(void);

	/**
	 * Constructeur de copie.
	 *
	 * @param poly le complexPolynome avec lequel on souhaite initialiser l'objet.
	 */
	complexPolynome3D(const complexPolynome3D & poly);

	/**
	 * Construcuteur de complexPolynome constant.
	 *
	 * Ce constructeur permet de cr�er un complexPolynome constant dont la
	 * valeur est pass�e en argument.
	 */
	complexPolynome3D(const complex & value);

	/**
	 * Destructeur.
	 */
	virtual ~complexPolynome3D(void);

	/**
	 * Methode qui multiplie un complexPolynome par (variable-root)
	 * Autrement dit cela revient � ajouter root comme z�ro du complexPolynome.
	 *
	 * @param root la valeur du z�ro � ajouter au complexPolynome.
	 *
	 * @param dimension la dimension pour laquelle on veut ajouter la racine.
	 *
	 * @return le complexPolynome produit de (variable-root) et de l'objet.
	 *
	 * @warning la dimension ne peut prendre que les valeur 0,1 ou 2.
	 */
	complexPolynome3D centerMonomeMultiply(const complex & root , const int & dimension)const;


	/**	
	 * Methode qui multiplie un complexPolynome par (variable-root)^d
	 * Autrement dit cela revient � ajouter root comme z�ro du complexPolynome.
	 *
	 * @param root la valeur du z�ro � ajouter au complexPolynome.
	 *
	 * @param degree le degr� du monome par lequel on multiplie le polynome.
	 *
	 * @param dimension la dimension pour laquelle on veut ajouter la racine.
	 *
	 * @return le complexPolynome produit de (variable-root) et de l'objet.
	 *
	 * @warning la dimension ne peut prendre que les valeur 0,1 ou 2.
	 */
	complexPolynome3D centerMonomeMultiply(const complex & root, const int & dimension , const int & degree)const;

	/**
	 * Methode de base pour la d�rivation.
	 *
	 * Cette m�thode permet de d�river un complexPolynome par rapport � la variable x , y ou z
	 * suivant la valeur du parametre dimension.
	 *
	 * @param dimension dimension par rapport � laquelle on souhaite d�river le complexPolynome, 
	 * lorsque dimension prend la valeur 0 on d�rive par rapport � , 1 par rapport � y et 2
	 * par rapport � z.
	 *
	 * @return le complexPolynome d�riv�.
	 *
	 * @warning la vaelrude la dimension ne peut etre que 0, 1 ou 2.
	 */
	complexPolynome3D derivate(const int & dimension) const;

	/**
	 * Methode qui d�rive un complexPolynome par rapport � la variable x.
	 *
	 * @param derivationDegree le degr� de d�rivation du complexPolynome, sachant que
	 * la premi�re composante du triplet d'entier contient la valeur du nombre de d�rivation
	 * par rapport � la premi�re variable, la seconde la valeur du nombre de d�rivation par 
	 * rapport � la seconde variable, et la derniere le nombre de d�rivation par rapport
	 * � la derni�re variable.
	 *
	 * @return le complexPolynome issu de la d�rivation.
	 */
	complexPolynome3D derivate(const ipoint<3> & derivationDegree) const;

	/**
	 * Methode qui d�rive un complexPolynome par rapport � la variable x.
	 *
	 * @return le complexPolynome d�riv� par rapport � la premi�re variable.
	 */
	complexPolynome3D derivateX(void) const;
	
	/**
	 * Methode qui d�rive un complexPolynome par rapport � la variable y.
	 *
	 * @return le complexPolynome d�riv� par rapport � la seconde variable.
	 */
	complexPolynome3D derivateY(void) const;

	/**
	 * Methode qui d�rive un complexPolynome par rapport � la variable z.
	 *
	 * @return le complexPolynome d�riv� par rapport � la troisi�me variable.
	 */
	complexPolynome3D derivateZ(void) const;

		/**
	 * Methode qui multiplie un complexPolynome par x^degreeX * y^degreeY * z^degreeZ.
	 *
	 * @param degree le degree du monome avec lequel souhaite multiplier le complexPolynome.
	 *
	 * @return le complexPolynome qui contient le produit de x^d et de l'objet.
	 */
	complexPolynome3D monomeMultiply(const ipoint<3> & degree = ipoint<3>(1)) const;

	/**
	 * Operateur pour l'assignement.
	 * 
	 * @param p le complexPolynome que l'on souhaite copier dans
	 * l'objet appelant.
	 *
	 * @return une r�f�rence vers le nouveau complexPolynome.
	 */
	complexPolynome3D & operator= (const complexPolynome3D & p);

	/**
	 * Operateur pour faire l'addition de deux complexPolynomes.
	 *
	 * @param p le complexPolynome que l'on souhaite ajouter � l'objet.
	 *
	 * @return un complexPolynome qui contient la somme demand�e.
	 */
	complexPolynome3D operator+ (const complexPolynome3D & p) const;

	/**
	 * Op�rateur pour faire une addition unaire de deux complexPolynomes.
	 *
	 * @param p le complexPolynome que l'on souhaite ajouter � l'objet.
	 *
	 * @return une r�f�rence vers le complexPolynome qui contient la somme demand�e.
	 */
	complexPolynome3D & operator+= (const complexPolynome3D & p);	
	

	/**
	 * Operateur pour faire la soustraction de deux complexPolynomes.
	 *
	 * @param p le complexPolynome que l'on souhaite soustraire ajouter � l'objet.
	 *
	 * @return un complexPolynome qui contient la diff�rence demand�e.
	 */
	complexPolynome3D operator- ( const complexPolynome3D & p) const;

	/**
	 * Operateur pour faire la soustraction unaire de deux complexPolynomes.
	 *
	 * @param p le complexPolynome que l'on souhaite soustraire � l'objet.
	 *
	 * @return une r�f�rence vers le complexPolynome qui contient la diff�rence demand�e.
	 */
	complexPolynome3D & operator-= (const complexPolynome3D & p);

	/**
	 * Operateur pour faire la multiplication de deux complexPolynomes.
	 * 
	 * @param p le complexPolynome avec lequel on souhaite multiplier l'objet.
	 *
	 * @return un complexPolynome qui contient le produit demand�.
	 */
	complexPolynome3D operator* (const complexPolynome3D & p) const;

	/**
	 * Operateur pour faire la multiplication d'un complexPolynome et d'un scalaire.
	 * 
	 * @param scalar le scalaire avec lequel on souhaite multiplier l'objet.
	 *
	 * @return un complexPolynome qui contient le produit demand�.
	 */
	complexPolynome3D operator* (const complex & scalar) const;

	/**
	 * Operateur pour faire une multiplication unaire de deux complexPolynomes.
	 * 
	 * @param p le complexPolynome avec lequel on souhaite multiplier l'objet.
	 *
	 * @return une r�f�rence vers le complexPolynome qui contient le produit demand�.
	 */
	complexPolynome3D & operator*= (const complexPolynome3D & p);

	/**
	 * Operateur pour faire une multiplication unaire d'un complexPolynome et d'un scalaire.
	 * 
	 * @param scalar le scalaire avec lequel on souhaite multiplier l'objet.
	 *
	 * @return une r�f�rence vers le complexPolynome qui contient le produit demand�.
	 */
	complexPolynome3D & operator*= (const complex & scalar);

	/**
	 * Operateur pour faire la disision d'un complexPolynome et d'un scalaire.	
	 *
	 * @param scalar le scalaire par lequel on souhaite diviser l'objet.
	 *
	 * @return un complexPolynome qui contient le quotient demand�.
	 */
	complexPolynome3D operator/ (const complex & scalar) const;

	/**
	 * Operateur pour faire une division unaire d'un complexPolynome et d'un sclaire.
	 *
	 * @param scalar le scalaire par lequel on souhaite diviser l'objet.
	 *
	 * @return une r�f�rence vers le complexPolynome qui contient le quotient demand�.
	 */
	complexPolynome3D & operator/= (const complex & scalar);

	/**
	 * M�thode pour changer la varialble lin�aire.
	 *
	 * @param scalar le facteur du changement de variable.
	 *
	 * @return la forme du complexPolynome apr�s le changement de variable.
	 */
	//complexPolynome3D scale(const dpoint<3> & );

};

////////////////////////////////////////////////////////////////////////////////
// Operateurs externe de multiplication pour les scalaires :
//
// 1- La multplication :
extern complexPolynome3D operator*(const double & complex , const complexPolynome3D & p);


#endif

