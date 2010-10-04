/* 
 * The gaussian integrals library of A.S.P.I.C. 
 * Written and directed by Fran�ois Lodier support.aspic@gmail.com.
 * Class modified by Frederic Legoll Nov 06
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
#ifndef _POTENTIAL_INTEGRAL_
#define _POTENTIAL_INTEGRAL_

#include <atom.h>
#include <dpoint.h>
#include <gaussianBasisFunction.h>
#include "hermiteProjector.h"

/**
 * Classe pour calculer les int�grales de Potentiel.
 */
class potentialIntegral 
{

private:
	
protected:
		
	/**
	 * M�thode pour calculer le point de centrage des int�grales de coulomb.
	 */
	static dpoint<3> computePotentialCenter(const hermiteProjector & h_ab , const dpoint<3> & center);
	
	/**
	 * M�thode pour calculer le coefficient � mettre devant les
	 * int�grales de coulomb.
	 */
	static double computePotentialCoefficient(const hermiteProjector & h_ab , const dpoint<3> & center);

	/**
	 * M�thode pour calculer l'exposant de l'int�grale pour le potentiel.
	 */
	static double computePotentialExponent(const hermiteProjector & h_ab , const dpoint<3> & center);
	
		
	/**
	 * M�thode pour effectuer le calcul dans le cas de deux polynomes gaussiens.
	 */
	static double computePotential(const gaussianPolynome3D & gp_a , const gaussianPolynome3D & gp_b , const dpoint<3> & center);

public:

		/**
		 * Constructeur par d�faut.
		 */
		potentialIntegral(void);
	
		/** 
		 * M�thode pour calculer l'int�grale de potentiel pour deux fonctions de base.
		 */
		double getPotentialValue(const gaussianBasisFunction & phi_a , const gaussianBasisFunction & phi_b , dpoint<3> center , const atom::distanceUnit & unit) const;

		/** 
		 * M�thode pour calculer l'int�grale de potentiel pour la derivee de deux fonctions de base.
		 */
		double getPotentialValue(const gaussianBasisFunction & Phi_A , const ipoint<3> & deg_a, const gaussianBasisFunction & Phi_B , const ipoint<3> & deg_b, dpoint<3> center, const atom::distanceUnit & unit) const;
		
};

#endif

