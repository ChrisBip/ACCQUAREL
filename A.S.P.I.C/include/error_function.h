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
#ifndef _ERROR_FUNCTION_
#define _ERROR_FUNCTION_

/**
 * @file error_function.h
 * Ceci permet de d�finir la fonction d'erreur.
 * En effet les plateformes windows ne poss�dent pas de fonction
 * d'erreur dans leur librairies standard cette impl�mentation a 
 * donc �t� port�e afon que le module GimC fonctionne sous windows.
 */

/**
	 * M�thode pour calculer la valeur de la fonction d'erreur
	 * \f[
	 * erf(x) = \frac{2}{\sqrt{\pi}} \int_{0}^{x}{\exp(-u^2)du}
	 * \f].
	 *
	 * La fonction d'erreur est de la forme 
	 *
	 * @param x la borne sup�rieure de l'int�grale.
	 * @return la valeur de la fonction d'erreur au point \f$x\f$.
	 */
	extern double error_function(double x);
	

	/**
	 * M�thode pour calculer la valeur de la fonction d'erreur compl�mentaire
	 * \f[
	 * erfc(x) = \frac{2}{\sqrt{\pi}} \int_{x}^{+\infty}{\exp(-u^2)du}
	 * \f].
	 *
	 * @param x la borne sup�rieure de l'int�grale.
	 * @return la valeur de la fonction d'erreur au point.
	 */
	extern double error_function_c(double x);

#endif


