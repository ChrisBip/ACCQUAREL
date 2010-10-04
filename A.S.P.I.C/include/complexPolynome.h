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
#ifndef _POLYNOME_COMPLEX_
#define _POLYNOME__COMPLEX_

#include "polynomeBase.h"
#include <complex.h>


/**
 * Classe pour la manipulation des polynomes standarts.
 * 
 * Usuellement , un polynome peut s'ecrire comme p(x) = sum_{i}{a_i * x^i}. Le propos de cette
 * classe est de permettre la manipulation de ces quantit�s. 
 * Cette classe d�finie pour ces objets les principaux op�rateurs qu'elle peut utiliser.
 *
 * une addition interne :  si p et q sont deux polynomes , il est possible d'�crire p+q
 * dans un programme pour effectuer la sommation de ces deux polynomes.
 * @see polynome::operator+ (const polynome &) const;
 * @see polynome::operator+= (const polynome &);
 * 
 * une soustraction interne : si p et q sont deux polynomes , il est possible d'�crire p-q
 * dans un programme pour effectuer la soustraction de ces deux polynomes.
 * @see polynome::operator- (const polynome &) const;
 * @see polynome::operator-= (const polynome &);
 *
 * une multiplication interne.
 * @see polynome::operator* (const polynome &) const;
 * @see polynome::operator*= (const polynome &);
 *
 * une multiplication avec les scalaire.
 * @see polynome::operator* (const complex &) const;
 * @see polynome::operator-= (const complex &);
 *
 * une division avec des scalaires.
 * @see polynome::operator/ (const complex &) const;
 * @see polynome::operator/= (const complex &);
 *
 * La classe propose aussi une m�thode pour effectuer l'op�ration de d�rivation 
 * d'un polynome par rapport � sa variable.
 * @see polynome::derviate().
 *
 *
 */
class complexPolynome : public polynomeBase<complex>
{
private:

protected:

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
	virtual const string  getBaseString(const int & i) const;

public:

	/**
	 * Constructeur par defaut.
	 */
	complexPolynome(void);

	/**
	 * Constructeur de copie.
	 *
	 * @param poly le polynome avec lequel on souhaite initialiser l'objet.
	 */
	complexPolynome(const complexPolynome & poly);

	/**
	 * Construcuteur de polynome constant.
	 *
	 * Ce constructeur permet de cr�er un polynome constant dont la
	 * valeur est pass�e en argument.
	 */
	complexPolynome(const complex & value);

	/**
	* Destructeur.
	*/
	virtual ~complexPolynome(void);

	/**
	 * Methode qui multiplie un polynome par (x-root).
	 * Autrement dit cela revient � ajouter root comme z�ro du polynome.
	 *
	 * @param root la valeur du z�ro � ajouter au polynome.
	 *
	 * @return le polynome produit de (x-roo) et de l'objet.
	 */
	complexPolynome centerMonomeMultiply(const complex & root)const;

	/**
	 * Methode qui multiplie un polynome par (x-root)^degree.
	 * Autrement dit cela revient � ajouter root comme z�ro du polynome
	 * avec un ordre degree.
	 *
	 * @param root la valeur du z�ro � ajouter au polynome.
	 *
	 * @param degree l'ordre avec lequel on souhaite ajouter la racine au polynome. 
	 *
	 * @return le polynome produit de (x-roo) et de l'objet.
	 */
	 complexPolynome centerMonomeMultiply(const complex & root , const int & degree) const;

	/**	
	 * Methode pour d�river le polynome.
	 *
	 * @return le polynome issu de la d�rivation de l'objet.
	 */
	 complexPolynome derivate(void) const;

	/**
	 * Methode qui multiplie un polynome par x^degree.
	 *
	 * @param degree le degree du monome avec lequel souhaite multiplier le polynome.
	 *
	 * @return le polynome qui contient le produit de x^d et de l'objet.
	 */
	complexPolynome monomeMultiply(const int & degree=1) const;

	/**
	 * Operateur pour l'assignement.
	 * 
	 * @param p le polynome que l'on souhaite copier dans
	 * l'objet appelant.
	 *
	 * @return une r�f�rence vers le nouveau polynome.
	 */
	complexPolynome & operator= (const complexPolynome & p);

	/**
	 * Operateur pour faire l'addition de deux polynomes.
	 *
	 * @param p le polynome que l'on souhaite ajouter � l'objet.
	 *
	 * @return un polynome qui contient la somme demand�e.
	 */
	complexPolynome operator+ (const complexPolynome & p) const;

	/**
	 * Op�rateur pour faire une addition unaire de deux polynomes.
	 *
	 * @param p le polynome que l'on souhaite ajouter � l'objet.
	 *
	 * @return une r�f�rence vers le polynome qui contient la somme demand�e.
	 */
	complexPolynome & operator+= (const complexPolynome & p);	
	
	/**
	 * Operateur pour faire la soustraction de deux polynomes.
	 *
	 * @param p le polynome que l'on souhaite soustraire ajouter � l'objet.
	 *
	 * @return un polynome qui contient la diff�rence demand�e.
	 */
	complexPolynome operator- (const complexPolynome & p) const;

	/**
	 * Operateur pour faire la soustraction unaire de deux polynomes.
	 *
	 * @param p le polynome que l'on souhaite soustraire � l'objet.
	 *
	 * @return une r�f�rence vers le polynome qui contient la diff�rence demand�e.
	 */
	complexPolynome & operator-= (const complexPolynome & p);

	/**
	 * Operateur pour faire la multiplication de deux polynomes.
	 * 
	 * @param p le polynome avec lequel on souhaite multiplier l'objet.
	 *
	 * @return un polynome qui contient le produit demand�.
	 */
	complexPolynome operator* (const complexPolynome & p) const;

	/**
	 * Operateur pour faire la multiplication d'un polynome et d'un scalaire.
	 * 
	 * @param scalar le scalaire avec lequel on souhaite multiplier l'objet.
	 *
	 * @return un polynome qui contient le produit demand�.
	 */
	complexPolynome operator* (const complex & scalar) const;

	/**
	 * Operateur pour faire une multiplication unaire de deux complexPolynomes.
	 * 
	 * @param p le polynome avec lequel on souhaite multiplier l'objet.
	 *
	 * @return une r�f�rence vers le polynome qui contient le produit demand�.
	 */
	complexPolynome & operator*= (const complexPolynome & p);

	/**
	 * Operateur pour faire une multiplication unaire d'un polynome et d'un scalaire.
	 * 
	 * @param scalar le scalaire avec lequel on souhaite multiplier l'objet.
	 *
	 * @return une r�f�rence vers le polynome qui contient le produit demand�.
	 */
	complexPolynome & operator *= (const complex & scalar);

	/**
	 * Operateur pour faire la disision d'un polynome et d'un scalaire.	
	 *
	 * @param scalar le scalaire par lequel on souhaite diviser l'objet.
	 *
	 * @return un polynome qui contient le quotient demand�.
	 */
	complexPolynome operator/ (const complex & scalar) const;

	/**
	 * Operateur pour faire une division unaire d'un polynome et d'un sclaire.
	 *
	 * @param scalar le scalaire par lequel on souhaite diviser l'objet.
	 *
	 * @return une r�f�rence vers le polynome qui contient le quotient demand�.
	 */
	complexPolynome & operator/= (const complex & scalar);
	
	/**
	 * M�thode pour changer la varialble lin�aire.
	 *
	 * @param scalar le facteur du changement de variable.
	 *
	 * @return la forme du polynome apr�s le changement de variable.
	 */
	complexPolynome scale(const complex & scalar);
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
extern complexPolynome operator*(const complex & scalar , const complexPolynome & poly);

#endif
