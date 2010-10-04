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
#ifndef POLYNOME3D
#define POLYNOME3D

#include "polynome.h"
#include "polynomeBase3D.h"

class polynome3D : public polynomeBase3D<double>
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
	polynome3D(void);

	/**
	 * Constructeur de copie.
	 *
	 * @param poly le polynome avec lequel on souhaite initialiser l'objet.
	 */
	polynome3D(const polynome3D & poly);

	/**
	 * Construcuteur de polynome constant.
	 *
	 * Ce constructeur permet de cr�er un polynome constant dont la
	 * valeur est pass�e en argument.
	 */
	polynome3D(const double & value);

	/**
	 * Destructeur.
	 */
	virtual ~polynome3D(void);

	/**
	 * Methode qui multiplie un polynome par (variable-root)
	 * Autrement dit cela revient � ajouter root comme z�ro du polynome.
	 *
	 * @param root la valeur du z�ro � ajouter au polynome.
	 *
	 * @param dimension la dimension pour laquelle on veut ajouter la racine.
	 *
	 * @return le polynome produit de (variable-root) et de l'objet.
	 *
	 * @warning la dimension ne peut prendre que les valeur 0,1 ou 2.
	 */
	polynome3D centerMonomeMultiply(const double & root , const int & dimension)const;

	/**	
	 * Methode qui multiplie un polynome par (variable-root)^d
	 * Autrement dit cela revient � ajouter root comme z�ro du polynome.
	 *
	 * @param root la valeur du z�ro � ajouter au polynome.
	 *
	 * @param dimension la dimension pour laquelle on veut ajouter la racine.
	 *
	 * @param degree l'ordre de multiplicit� de la racine � ajouter.
	 *
	 * @return le polynome produit de (variable-root) et de l'objet.
	 *
	 * @warning la dimension ne peut prendre que les valeur 0,1 ou 2.
	 *
	 * @warning il faut que le degr� soit positif ou nul.
	 */
	polynome3D centerMonomeMultiply(const double & root , const int & dimension , const int & degree)const;

	/**
	 * Methode qui multiplie un polynome par (x-root)^degree
	 *
	 * @param root la valeur du z�ro � ajouter au polynome.
	 *
	 * @param degree l'ordre de multiplicit� de la racine � ajouter.
	 *
	 * @return le polynome produit de (x-root)^degree et de l'objet.
	 *
	 * @warning il faut que le degr� soit positif ou nul.
	 */
	polynome3D centerMonomeMultiplyX(const double & root , const int & degree =1)const;

	/**
	 * Methode qui multiplie un polynome par (y-root)^degree
	 *
	 * @param root la valeur du z�ro � ajouter au polynome.
	 *
	 * @param degree l'ordre de multiplicit� de la racine � ajouter.
	 *
	 * @return le polynome produit de (x-root)^degree et de l'objet.
	 *
	 * @warning il faut que le degr� soit positif ou nul.
	 */
	polynome3D centerMonomeMultiplyY(const double & root , const int & degree =1)const;

	/**
	 * Methode qui multiplie un polynome par (z-root)^degree
	 *
	 * @param root la valeur du z�ro � ajouter au polynome.
	 *
	 * @param degree l'ordre de multiplicit� de la racine � ajouter.
	 *
	 * @return le polynome produit de (z-root)^degree et de l'objet.
	 *
	 * @warning il faut que le degr� soit positif ou nul.
	 */
	polynome3D centerMonomeMultiplyZ(const double & root , const int & degree =1)const;

	/**	
	 * Methode qui multiplie un polynome par (variable-root)^d
	 * Autrement dit cela revient � ajouter root comme z�ro du polynome.
	 *
	 * @param root la valeur du z�ro � ajouter au polynome.
	 *
	 * @param dimension la dimension pour laquelle on veut ajouter la racine.
	 *
	 * @param degree l'ordre de multiplicit� de la racine � ajouter.
	 *
	 * @return le polynome produit de (variable-root) et de l'objet.
	 *
	 * @warning la dimension ne peut prendre que les valeur 0,1 ou 2.
	 *
	 * @warning il faut que le degr� soit positif ou nul.
	 */
	polynome3D centerMonomeMultiply(const dpoint<3> & root , const ipoint<3> & degree=ipoint<3>(1))const;

	/**
	 * Methode de base pour la d�rivation.
	 *
	 * Cette m�thode permet de d�river un polynome par rapport � la variable x , y ou z
	 * suivant la valeur du parametre dimension.
	 *
	 * @param dimension dimension par rapport � laquelle on souhaite d�river le polynome, 
	 * lorsque dimension prend la valeur 0 on d�rive par rapport � , 1 par rapport � y et 2
	 * par rapport � z.
	 *
	 * @return le polynome d�riv�.
	 *
	 * @warning la vaelrude la dimension ne peut etre que 0, 1 ou 2.
	 */
	polynome3D derivate(const int & dimension) const;

	/**
	 * Methode qui d�rive un polynome par rapport � la variable x.
	 *
	 * @param derivationDegree le degr� de d�rivation du polynome, sachant que
	 * la premi�re composante du triplet d'entier contient la valeur du nombre de d�rivation
	 * par rapport � la premi�re variable, la seconde la valeur du nombre de d�rivation par 
	 * rapport � la seconde variable, et la derniere le nombre de d�rivation par rapport
	 * � la derni�re variable.
	 *
	 * @return le polynome issu de la d�rivation.
	 */
	polynome3D derivate(const ipoint<3> & derivationDegree) const;

	/**
	 * Methode qui d�rive un polynome par rapport � la variable x.
	 *
	 * @return le polynome d�riv� par rapport � la premi�re variable.
	 */
	polynome3D derivateX(void) const;
	
	/**
	 * Methode qui d�rive un polynome par rapport � la variable y.
	 *
	 * @return le polynome d�riv� par rapport � la seconde variable.
	 */
	polynome3D derivateY(void) const;

	/**
	 * Methode qui d�rive un polynome par rapport � la variable z.
	 *
	 * @return le polynome d�riv� par rapport � la troisi�me variable.
	 */
	polynome3D derivateZ(void) const;
	
	
	/**
	 * Method to eval the value of the polynome 
	 * in the point x.
	 */
	double eval(const dpoint<3> & position) const;
	
	

	/**
	 * Methode qui multiplie un polynome par varaible^degree
	 *
	 * @param degree le degree du monome avec lequel souhaite multiplier le polynome.
	 *
	 * @param dimension la variable avec laquelle  on souahite op�rer.
	 *
	 * @return le polynome qui contient le produit de x^d et de l'objet.
	 */
	polynome3D monomeMultiply(const int & dimension , const int & degree = 1) const;

	/**
	 * Methode qui multiplie un polynome par x^degreeX
	 *
	 * @param degree le degree du monome avec lequel souhaite multiplier le polynome.
	 *
	 * @return le polynome qui contient le produit de x^d et de l'objet.
	 */
	polynome3D monomeMultiplyX(const int & degree = 1) const;

	/**
	 * Methode qui multiplie un polynome par y^degree
	 *
	 * @param degree le degree du monome avec lequel souhaite multiplier le polynome.
	 *
	 * @return le polynome qui contient le produit de y^degree et de l'objet.
	 */
	polynome3D monomeMultiplyY(const int & degree = 1) const;
	
	/**
	 * Methode qui multiplie un polynome par z^degree
	 *
	 * @param degree le degree du monome avec lequel souhaite multiplier le polynome.
	 *
	 * @return le polynome qui contient le produit de z^degree et de l'objet.
	 */
	polynome3D monomeMultiplyZ(const int & degree = 1) const;
	
	/**
	 * Methode qui multiplie un polynome par x^degreeX * y^degreeY * z^degreeZ.
	 *
	 * @param degree le degree du monome avec lequel souhaite multiplier le polynome.
	 *
	 * @return le polynome qui contient le produit de x^d et de l'objet.
	 */
	polynome3D monomeMultiply(const ipoint<3> & degree = ipoint<3>(1)) const;

	/**
	 * Operateur pour l'assignement.
	 * 
	 * @param p le polynome que l'on souhaite copier dans
	 * l'objet appelant.
	 *
	 * @return une r�f�rence vers le nouveau polynome.
	 */
	polynome3D & operator= (const polynome3D & p);

	/**
	 * Operateur pour faire l'addition de deux polynomes.
	 *
	 * @param p le polynome que l'on souhaite ajouter � l'objet.
	 *
	 * @return un polynome qui contient la somme demand�e.
	 */
	polynome3D operator+ (const polynome3D & p) const;

	/**
	 * Op�rateur pour faire une addition unaire de deux polynomes.
	 *
	 * @param p le polynome que l'on souhaite ajouter � l'objet.
	 *
	 * @return une r�f�rence vers le polynome qui contient la somme demand�e.
	 */
	polynome3D & operator+= (const polynome3D & p);	
	

	/**
	 * Operateur pour faire la soustraction de deux polynomes.
	 *
	 * @param p le polynome que l'on souhaite soustraire ajouter � l'objet.
	 *
	 * @return un polynome qui contient la diff�rence demand�e.
	 */
	polynome3D operator- ( const polynome3D & p) const;

	/**
	 * Operateur pour faire la soustraction unaire de deux polynomes.
	 *
	 * @param p le polynome que l'on souhaite soustraire � l'objet.
	 *
	 * @return une r�f�rence vers le polynome qui contient la diff�rence demand�e.
	 */
	polynome3D & operator-= (const polynome3D & p);

	/**
	 * Operateur pour faire la multiplication de deux polynomes.
	 * 
	 * @param p le polynome avec lequel on souhaite multiplier l'objet.
	 *
	 * @return un polynome qui contient le produit demand�.
	 */
	polynome3D operator* (const polynome3D & p) const;

	/**
	 * Operateur pour faire la multiplication d'un polynome et d'un scalaire.
	 * 
	 * @param scalar le scalaire avec lequel on souhaite multiplier l'objet.
	 *
	 * @return un polynome qui contient le produit demand�.
	 */
	polynome3D operator* (const double & scalar) const;

	/**
	 * Operateur pour faire une multiplication unaire de deux polynomes.
	 * 
	 * @param p le polynome avec lequel on souhaite multiplier l'objet.
	 *
	 * @return une r�f�rence vers le polynome qui contient le produit demand�.
	 */
	polynome3D & operator*= (const polynome3D & p);

	/**
	 * Operateur pour faire une multiplication unaire d'un polynome et d'un scalaire.
	 * 
	 * @param scalar le scalaire avec lequel on souhaite multiplier l'objet.
	 *
	 * @return une r�f�rence vers le polynome qui contient le produit demand�.
	 */
	polynome3D & operator*= (const double & scalar);

	/**
	 * Operateur pour faire la disision d'un polynome et d'un scalaire.	
	 *
	 * @param scalar le scalaire par lequel on souhaite diviser l'objet.
	 *
	 * @return un polynome qui contient le quotient demand�.
	 */
	polynome3D operator/ (const double & scalar) const;

	/**
	 * Operateur pour faire une division unaire d'un polynome et d'un sclaire.
	 *
	 * @param scalar le scalaire par lequel on souhaite diviser l'objet.
	 *
	 * @return une r�f�rence vers le polynome qui contient le quotient demand�.
	 */
	polynome3D & operator/= (const double & scalar);

	/**
	 * M�thode pour changer la varialble lin�aire.
	 *
	 * @param scalar le facteur du changement de variable.
	 *
	 * @return la forme du polynome apr�s le changement de variable.
	 */
	polynome3D scale(const dpoint<3> & scalar);

	/**
	 * M�thode pour donner au polynome une valeur constante.
	 *
	 * @param value la valeur que l'on souhaite donner au polynome.
	 */
	void setPolynomeCoefficients(const double & value);

	/**
	 * M�thode pour recopier les coefficients d'un polynome.
	 *
	 * @param poly les coefficients � recopier dans l'objet.
	 */
	void setPolynomeCoefficients(const polynome3D & poly);

	/**
	 * M�thode pour construire un polynome tri dimensionel comme un produit de
	 * polynome mono dimensionnel.
	 *
	 * @param polyX le polynome en x.
	 * @param polyY le polynome en y.
	 * @param polyZ le polynome en z.
	 */
	void setPolynomeCoefficients(const polynome & polyX , const polynome & polyY , const polynome & polyZ);

};

////////////////////////////////////////////////////////////////////////////////
// Operateurs externe de multiplication pour les scalaires :
//
// 1- La multplication :
extern polynome3D operator*(const double & scalar , const polynome3D & p);


#endif

