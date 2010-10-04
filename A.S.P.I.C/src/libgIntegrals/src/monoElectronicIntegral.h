/* 
 * The gaussian integrals library of A.S.P.I.C. 
 * Written and directed by Fran�ois Lodier support.aspic@gmail.com.
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
#ifndef _MONO_ELECTRONIC_INTEGRAL_
#define _MONO_ELECTRONIC_INTEGRAL_

#include <gaussianBasisFunction.h>

/**
 * Classe pour faire les calculs d'int�grales mono �lectronique.
 */
class monoElectronicIntegral
{
private:
	
protected:
/**
 * Fonctions pour le calcul d'int�grales intervenant dans le cas relativiste.
 * (dernier ajout le 23/09/2008 par G. Legendre (CEREMADE - universit� de Paris-Dauphine))
 **/
        static double computeDeriv(const gaussianPolynome3D & gp_a , const gaussianPolynome3D & gp_b , const int & dimension);

        static double computeXDeriv(const gaussianPolynome3D & gp_a , const gaussianPolynome3D & gp_b , const int & dimension1, const int & dimension2);
/**
 * Fin des ajouts.
 **/ 
	/**
	 * M�thode pour calculer l'�nergie cin�tique du produit de deux polynomes gaussiens.
	 *
	 * @param gp_a le premier polynome gaussien.
	 *
	 * param gp_b la second polynome gaussien.
	 *
	 * return la valeur de l'int�grale sur R^3 du produit des gradients deux polyn�mes.
	 */
	static double computeKinetic(const gaussianPolynome3D & gp_a , const gaussianPolynome3D & gp_b);

	/**
	 * M�thode pour calculer l'�nergie cin�tique du produit de deux polynomes gaussiens.
	 *
	 * @param gp_a le premier polynome gaussien.
	 *
	 * param gp_b la second polynome gaussien.
	 *
	 * return la valeur de l'int�grale sur R^3 du produit des gradients deux polyn�mes.
	 */
	static double computeOverlap(const gaussianPolynome3D & gp_a , const gaussianPolynome3D & gp_b);

public:

	/**
	 * Constructeur par d�faut.
	 **/
	monoElectronicIntegral(void);

/**
 * Fonctions pour le calcul d'int�grales intervenant dans le cas relativiste.
 * (dernier ajout le 23/09/2008 par G. Legendre (CEREMADE - universit� de Paris-Dauphine))
 **/
        double getDerivValue(const gaussianBasisFunction & phi_a , const gaussianBasisFunction & phi_b , const int & dimension) const;

        double getXDerivValue(const gaussianBasisFunction & phi_a , const gaussianBasisFunction & phi_b , const int & dimension1 , const int & dimension2) const;
/**
 * Fin de l'ajout.
 **/
	/**
	 * M�thode qui calcule l'�nergie cin�tique pour deux fonctions de base.
	 *
	 *
	 * @param phi_a la premi�re fonction de base.
	 *
	 * param phi_b la seconde fonction de base.
	 *
	 * return la valeur de l'int�grale sur R^3 du produit des gradients deux fonctions de base.
	 */
	double getKineticValue(const gaussianBasisFunction & phi_a , const gaussianBasisFunction & phi_b) const;

	/**
	 * M�thode qui calcule l'�nergie cin�tique pour les d�riv�es deux fonctions de base :
	 * 
	 * @param phi_a la premi�re fonction de base.
	 *
	 * @param deg_a le degr� de d�rivation de la premi�re fonction de base.
	 *
	 * param phi_b la seconde fonction de base.
	 *
	 * @param deg_b le degr� de d�rivation de la premi�re fonction de base.
	 *
	 * @return la valeur de l'int�grale sur R^3 du produit des gradients des d�riv�es des deux fonctions de base.
	 */
	double getKineticValue(const gaussianBasisFunction & phi_a , const ipoint<3> & deg_a , const gaussianBasisFunction & phi_b , const ipoint<3> & deg_b) const;

	/**
	 * M�thode qui calcule le recouvrement pour deux fonctions de base.
	 *
	 * @param phi_a la premi�re fonction de base.
	 *
	 * param phi_b la seconde fonction de base.
	 *
	 * @return la valeur de l'int�grale sur R^3 du produit des deux fonctions de base.
	 */
	double getOverlapValue(const gaussianBasisFunction & phi_a , const gaussianBasisFunction & phi_b) const;

	/**
	 * M�thode qui calcule le recouvrement pour deux d�riv�es de fonctions de base.
	 *
	 * @param phi_a la premi�re fonction de base.
	 *
	 * @param deg_a le degr� de d�rivation de la premi�re fonction de base.
	 *
	 * param phi_b la seconde fonction de base.
	 *
	 * @param deg_b le degr� de d�rivation de la premi�re fonction de base.
	 *
	 * @return la valeur de l'int�grale sur R^3 du produit des d�riv�es des deux fonctions de base.
	 */
	double getOverlapValue(const gaussianBasisFunction & phi_a , const ipoint<3> & deg_a , const gaussianBasisFunction & phi_b , const ipoint<3> & deg_b) const;
	
	
	/**
	 * M�thode pour faire la normalisation de'une fonction de base gaussienne.
	 */
	void normalize(gaussianBasisFunction & phi) const;
};

#endif

