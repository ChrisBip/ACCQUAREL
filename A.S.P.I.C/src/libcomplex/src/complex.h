/* 
 * The complex library of the A.S.P.I.C. 
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
 *
 * CERMICS, ENPC, hereby disclaims all copyright interest in
 * the library `complex' (a library of complex for A.S.P.I.C.) written
 * by Fran�ois Lodier.
 */
#ifndef _COMPLEX_
#define _COMPLEX_

#include <iostream>
#include <math.h>

using namespace std;

/**
 * Classe pour la manipulation des nombres complexes.
 */
class complex 
{private:	
	/**
	 * La partie r�elle du nombre complexe.
	 */
	double Real;
	
	/**
	 * La partie imaginaire du nombre complexe.
   */
	double Im;protected:
	
	/**
	 * M�thode pour copier un nombre complexe. 
	 */
	void copy(const complex & c);public:
	
	/**
	 * Constructeur par d�faut.	
   */
	complex(void);	
	
	/**
	 * Constructeur � partir d'un nombre r�el.
	 *
	 * @param real le nombre r�el qui est transform� en complexe
	 * par l'appel de ce contructeur.
	 */
	complex(double real);	
	
	/**
	 * constructeur avec un reel et un imaginaire.
	 *
	 * @param real la partie r�elle du nombre complexe.
	 *
	 * @param im la partie imaginaire du nombre complexe.
	 */
	complex(double real , double im);	
	
	/**
	 * constrcteur de copie.
	 *
	 * @param c le nombre complexe � copier dans l'objet construit.
	 */
	complex(const complex & c);	
	
	/**
	 * Destructeur.
	 */
	~complex(void);	
	
	/**
	 * M�thode constante pour acc�der � la partie r�elle.
	 *
	 * @return une r�f�rence constante vers partie r�elle de l'objet.
	 */
	const double & real(void) const;	
	
	/**
	 * M�thode pour acc�der � la partie r�elle.
	 *
	 * @return une r�f�rence vers la partie r�elle de l'objet.
	 */
	double & real(void);	
	
	/**
	 * M�thode constante pour acc�der � la partie imaginaire.
	 *
	 * @return une r�f�rence constante vers partie imaginaire de l'objet.
	 */
	const double & im(void) const;	
	
	/**
	 * M�thode pour acc�der � la partie imaginaire.
	 *
	 * @return une r�f�rence vers partie imaginaire de l'objet.
	 */
	double & im(void);
	
	/**
	 * M�thode pour savoir si un nombre complexe est un imaginaire pur.
	 *
	 * @return true lorsque la partie reele est nulle et false sinon.
	 */
	bool is_pure_im(void) const;	
	
	/**
	 * M�thode pour savoir si l'objet est un nombre est un reel.
	 *
	 * @return true lorsque la partie r�elle est nulle, false sinon.
	 */
	bool is_real(void) const;	
	
	/**
	 * M�thode pour additionner deux complexes.
	 *
	 * @param c le nombre complex que l'on souhaite ajouter � l'objet appelant.
	 *
	 * @return un complex qui contient le r�sultat de l'addition de l'objet courrant 
	 * et de c.
	 */
	complex operator+(const complex & c) const;	
	
	/**
	 * M�thode pour additionner un complexe et un double :
	 *
	 * @param real le nombre r�el que l'on souhaite ajouter � l'objet appelant.
	 *
	 * @return un complex qui contient le r�sultat de l'addition de l'objet courrant 
	 * et de real.
	 */
	complex operator+(const double & real) const;	
	
	/**
	 * M�thode pour faire l'addition unaire de deux complexes.
	 * 
	 * @param c le nombre complex que l'on souhaite ajouter � l'objet appelant.
	 *
	 * @return une r�f�rence vers l'objet qui contient le r�sultat de l'addition 
	 * de c et de l'objet appelant.
	 */
	complex & operator+=(const complex & c);	
	
	/**
	 * M�thode pour faire l'addition unaire d'un complexe et d'un double.
	 * 
	 * @param real le nombre r�el que l'on souhaite ajouter � l'objet appelant.
	 *
	 * @return une r�f�rence vers le complex qui contient le r�sultat de l'addition de l'objet courrant 
	 * et de real.
	 */
	complex & operator+=(const double & real);	
	
	/**
	 * M�thode pour soustraire deux complexes.
	 *
	 * @param c le nombre complex que l'on souhaite soustraire � l'objet appelant.
	 *
	 * @return un complex qui contient le r�sultat de la soustraction de l'objet courrant 
	 * et de c.
	 */
	complex operator-(const complex & c) const;	
	
	/**
	 * M�thode pour soustraire un complexe et un double :
	 *
	 * @param real le nombre r�el que l'on souhaite soustraire � l'objet appelant.
	 *
	 * @return un complex qui contient le r�sultat de la soustraction de l'objet courrant 
	 * et de real.
	 */
	complex operator-(const double & real) const;	
	
	/**
	 * M�thode pour faire la soustraction unaire de deux complexes.
	 * 
	 * @param c le nombre complex que l'on souhaite soustraire � l'objet appelant.
	 *
	 * @return une r�f�rence vers l'objet qui contient le r�sultat de la soustraction 
	 * de c et de l'objet appelant.
	 */
	complex & operator-=(const complex & c);	
	
	/**
	 * M�thode pour faire la soustraction unaire d'un complexe et d'un double.
	 * 
	 * @param real le nombre r�el que l'on souhaite soustraire � l'objet appelant.
	 *
	 * @return une r�f�rence vers le complex qui contient le r�sultat de la soustraction de l'objet courrant 
	 * et de real.
	 */
	complex & operator-=(const double & real); 
	
	/**
	 * M�thode pour multiplier deux complexes.
	 *
	 * @param c le nombre complex que l'on souhaite multiplier avec l'objet appelant.
	 *
	 * @return un complex qui contient le r�sultat de la multiplication de l'objet courrant 
	 * et de c.
	 */
	complex operator*(const complex & c) const;	
	
	/**
	 * M�thode pour multiplier un complexe et un double :
	 *
	 * @param real le nombre r�el que l'on souhaite multiplier avec l'objet appelant.
	 *
	 * @return un complex qui contient le r�sultat de la multiplication de l'objet courrant 
	 * et de real.
	 */
	complex operator*(const double  & real) const;	
	
	/**
	 * M�thode pour faire la multiplication unaire de deux complexes.
	 * 
	 * @param c le nombre complex que l'on souhaite multiplier avec l'objet appelant.
	 *
	 * @return une r�f�rence vers l'objet qui contient le r�sultat de la multiplication 
	 * de c et de l'objet appelant.
	 */
	complex & operator*=(const complex & c);	
	
	/**
	 * M�thode pour faire la multiplication unaire d'un complexe et d'un double.
	 * 
	 * @param real le nombre r�el que l'on souhaite multiplier avec l'objet appelant.
	 *
	 * @return une r�f�rence vers le complex qui contient le r�sultat de la multiplication de l'objet courrant 
	 * et de real.
	 */
	complex & operator*=(const double & real); 

	/**
	 * M�thode pour diviser deux complexes.
	 *
	 * @param c le nombre complex par lequel on souhaite diviser l'objet appelant.
	 *
	 * @return un complex qui contient le r�sultat de la division de l'objet courrant 
	 * par c.
	 */
	complex operator /(const complex & c) const;	
	
	/**
	 * M�thode pour diviser un complexe et un double :
	 *
	 * @param real le nombre r�el par lequel souhaite diviser l'objet appelant.
	 *
	 * @return un complex qui contient le r�sultat de la division de l'objet courrant 
	 * par real.
	 */
	complex operator /(const double & real) const;	
	
	/**
	 * M�thode pour faire la division unaire de deux complexes.
	 * 
	 * @param c le nombre complex par lequel on souhaite diviser avec l'objet appelant.
	 *
	 * @return une r�f�rence vers l'objet qui contient le r�sultat de la division 
	 * de l'objet appelant par c.
	 */
	complex & operator/=(const complex & c);	
	
	/**
	 * M�thode pour faire la division unaire d'un complexe et d'un double.
	 * 
	 * @param real le nombre r�el par lequel on souhaite diviser l'objet appelant.
	 *
	 * @return une r�f�rence vers le complex qui contient le r�sultat de la division de l'objet courrant 
	 * par real.
	 */
	complex & operator/=(const double & real);
	
	/**
	 * Op�rateur d'affectation
	 * 
	 * @param c la valeur que l'on souhaite affecter � l'objet.
	 *
	 * @return une r�f�rence vers l'objet affect� de sa nouvelle valeur 
	 */
	complex & operator=(const complex & c);	
	
	/**
	 * Op�rateur d'affectation
	 * 
	 * @param real la valeur que l'on souhaite affecter � l'objet.
	 *
	 * @return une r�f�rence vers l'objet affect� de sa nouvelle valeur 
	 */
	complex & operator=(const double & real);	
	
	/**
	 * M�thode pour calculer le module au carr� d'un nombre complexe.
	 *
	 * @return la valeur du module au carr� du nombre complexe.
	 */
	double sq_module(void) const;	
	
	/**
	 * M�thode pour calculer le module d'un nombre complexe.
	 *
	 * @return la valeur du module du nombre complexe.
	 */
	double module(void) const;

	/**
	 * M�thode pour calculer le conjugu� d'un nombre complexe.
	 *
	 * @return le complex conjugu� de l'objet.
	 */
	complex conjugate(void) const;	
	
	/**
	 * Op�rateur de comparaison pour deux nombres complexes.
	 *
	 * @param c le nombre complexe avec lequel on souhaite comparer l'objet appelant.
	 *
	 * @return true lorsque c et l'objet sont identiques, flase sinon.
	 */
	bool operator==(const complex & c) const;	
	
	/**
	 * Op�rateur de comparaison pour deux nombres complexes.
	 *
	 * @param c le nombre complexe avec lequel on souhaite comparer l'objet appelant.
	 *
	 * @return false lorsque c et l'objet sont identiques, true sinon.
	 */
	bool operator!=(const complex & c) const;	
	
	/**
	 * Op�rateur de comparaison pour un nombre complexe et un reel.
	 *
	 * @param real le nombre r�el avec lequel on souhaite comparer l'objet appelant.
	 *
	 * @return true lorsque r et l'objet sont identiques, false sinon.
	 */
	bool operator==(const double & real) const;	
	
	/**
	 * Op�rateur de comparaison pour un nombre complexe et un reel.
	 *
	 * @param real le nombre r�el avec lequel on souhaite comparer l'objet appelant.
	 *
	 * @return false lorsque r et l'objet sont identiques, true sinon.
	 */
	bool operator!=(const double & real) const;	
	
	/**
	 * M�thode pour �crire un nombre complex dans un flux sortant.
	 *
	 * @param out le flux dans lequel on souhaite �crire le nombre complexe.
	 *
	 * @see operator<<( ostream & out , const complex &).
	 */
	void write(ostream & out) const;

};
	
/**
 * Op�rateur pour l'�criture d'un complexe dans un flux.
 *
 * @param out le flux dans lequel on souhaite �crire le nombre complexe.
 *
 * @param c le complex que l'on souohaite �crire dans le flux.
 *
 * @return une r�f�rence vers le flux dans lequel le complexe a �t� �crit.
 */
extern ostream & operator<<(ostream & out , const complex & c);

/**
 * Op�rateur pour faire l'addition d'un r�el et d'un complexe
 *
 * @param real le nombre r�el.
 *
 * @param c un complexe.
 *
 * @return le r�sultat de l'addition du complexe et du r�el.
 */
complex operator+(const double & real , const complex & c);

/**
 * Op�rateur pour faire soustraction d'un r�el et d'un complexe
 *
 * @param real le nombre r�el.
 *
 * @param c un complexe.
 *
 * @return le r�sultat de la soustraction de real et de c.
 */
complex operator-(const double & real , const complex & c);

/**
 * Op�rateur pour faire division d'un r�el par un complexe
 *
 * @param real le nombre r�el.
 *
 * @param c un complexe.
 *
 * @return le r�sultat de la division de real par c.
 */
complex operator/(const double & real , const complex & c);

/**
 * Op�rateur pour faire la multiplication d'un r�el et d'un complexe
 *
 * @param real le nombre r�el.
 *
 * @param c un complexe.
 *
 * @return le r�sultat de la multiplication du complexe et du r�el.
 */
complex operator*(const double & real , const complex & c);

/**
 * Op�rateur unaire -
 *
 * @param c un complexe dont on veut prendre l'oppos�.
 *
 * @return l'oppos� du nombre complexe pass� en argument.
 */
complex operator - (const complex & c);


#endif
