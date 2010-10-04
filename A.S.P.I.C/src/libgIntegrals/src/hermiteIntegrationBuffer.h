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
#ifndef _HERMITE_INTEGRATION_BUFFER_
#define _HERMITE_INTEGRATION_BUFFER_

#include <containor3D.h>
#include <gaussianPolynome.h>
#include "hermiteProjector.h"

/**
 * Cette classe calcul des polynome de la forme
 * v^{r / 2} * H_r(sqrt(v)*R*u) [* exp(-v * R^2 * u^2)].
 * 
 * R = le centre.
 * v = l'exposant.
 * u = la variable.
 *
 * Le seul souci est que rien n'inerdit � R d'etre nul.
 * ceci peut donc poser pas mal de soucis.
 */

class hermiteBasisPolynome 
{
private :
	/**
	 * Ensuite on va aussi stocker le centre.
	 */
	double Center;

	/**
	 * Ensuite ib stocke le degr�.
	 */
	int Degree;
	
	/**
	 * Ensuit on va stocker l'exposant.
	 */
	double Exponent;

	/**
	 * Bon on va stocker le polynome sous
	 * cette forme la.
	 */
	gaussianPolynome HermiteBasisPolynome;
	
	/**
	 * Pour savoir si l'initialisation � �t� 
	 * faite correctement.
	 */
	bool HermiteBasisPolynomeIsInitialized;
	/**
	 * Markeur pour savoir si il faut recalculer
	 * le polynome.
	 */
	bool HermiteBasisPolynomeIsUp2Date;


protected :
	
	/**
	 * M�thode pour faire la copie d'un 
	 * objet hermiteBasisPolynome.
	 */
	void copy(const hermiteBasisPolynome & hBP);

	/**
	 * M�thode d'initialisation des polynomes.
	 */
	void initHermiteBasisPolynome(void);

	/**
	 * M�thode pour calculer le polynome.
	 */
	void computeHermiteBasisPolynome(void);

	/**
	 * M�thode sp�ciale pour calculer le polynome
	 * lorsque l'on choisit un centre nul.
	 */
	void computeHermiteBasisPolynomeNullCenterException(const int & degree);

	/**
	 * M�thode pour calculer le polynome.
	 */
	void computeNextHermiteBasisPolynome(void);

public:

	/**
	 * Constructeur de la classe Hermite Polynome.
	 */
	hermiteBasisPolynome(void);

	/**
	 * Destructeur de la classe Hermite Polynome.
	 */
	~hermiteBasisPolynome(void);

	/**
	 * M�thode pour ajouter un au degr� du polynome
	 */
	void addDegree(void);

	/**
	 * M�thode d'acc�s au centre.
	 */
	const double & getCenter(void) const;

	/**
	 * M�thode pour connaitre le degr� du polynome
	 * de hermite stock� dans l'objet.
	 */
	const int & getDegree(void) const;

	/**
	 * M�thode d'acc�s � l'Exposant.
	 */
	const double & getExponent(void) const;

	/**
	 * M�thode pour acc�der au polynome 
	 */
	const polynome & getPolynome(void) const;

	/**
	 * M�thode pour acc�der aux coefficient du 
	 * polynome.
	 */
	double getPolynomeCoefficient(const int & degree) const;

	/**
	 * M�thode pour fixer le centre.
	 */
	void setCenter(const double & center);

	/**
	 * M�thode pour fixer le degr� du polynome de Hermite
	 * que l'on souhaite connaitre.
	 */
	void setDegree(const int & degree);
	
	/**
	 * M�thode pour fixer l'exposant.
	 */
	void setExponent(const double & exponent);


	/**
	 * M�thode pour �crire le polynome
	 * dans un flux.
	 */
	void write(ostream & out) const;

};

/**
 * M�thode pour �crire la connerie dans un flux.
 */
extern ostream & operator<< (ostream & out , const hermiteBasisPolynome & hBP);



/**
 * Classe qui calcule et stocke  toutes les int�grales de la forme 
 * int_{0}^{1}{(v*u)^{r}H_r(vRu)exp(-v^{2} R^2 u^2) du}
 * avec  H_r(vRu) =   H_{r_y}(v R_x u)   H_{r_y}(v R_y u)   H_{r_z}(v R_z u) 
 * et 0 \leq r_x \leq r_x^max 
 * et 0 \leq r_y \leq r_y^max
 * et 0 \leq r_z \leq r_z^max
 */
class hermiteIntegrationBuffer 
{
private:

	/**
	 * Ceci est la variable R dans l'expression
	 * que nous cherchons � calculer.
	 */
	dpoint<3> Center;

	/**
	 * ---------- DEPRECATED -------------
	 * Variable permettant de mettre
	 * un coefficient constant devant l'int�grale.
	 */
	double Coefficient;

	/**
	 * Ceci est la variable v dans l'expression 
	 * que nous cherchons � calculer.
	 */
	double Exponent;
	
	/**
	 * Tableau � trois indices qui contient les valeurs
	 * des int�grales.
	 */
	containor3D<double> IntegrationBuffer;
	
	/**
	 * booleen pour qui permet de savoir si le tableau de r�sultats
	 * doit etre recaclul�.
	 */
	bool IntegrationBufferIsUp2Date;

protected:

	/**
	 * M�thode pour mettre le buffer � z�ro.
	 */
	void clearMonomeIntegrationBuffer(void);

	/**
	 * M�thode pour calculer les valeurs du Buffer.
	 */
	void computeHermiteIntegrationBuffer(void);

	/**
	 * Exception : lorsque le buffer ne 
	 * peut pas recevoir de donn�es.
	 */
	void nothing2DoException(void);

	/** ---------- DEPRECATED -------------
	 * M�thode qui permet de savoir si nous
	 * sommes dans le cas particulier o� les
	 * deux centres sont identiques.
	 */
	//void sameCenterException(void);

	/** ---------- DEPRECATED -------------
	 * M�thode qui calcule le centre.
	 */
	//void setCenter(const hermiteProjector & hermitePolynome_1 , const hermiteProjector & hermitePolynome_2);

	/** ---------- DEPRECATED -------------
	 * M�thode qui calcule le coefficient
	 * pour l'int�gration ...
	 */
	//void setCoefficient(const hermiteProjector & hermitePolynome_1 , const hermiteProjector & hermitePolynome_2);

	/** ---------- DEPRECATED -------------
	 * M�thode pour mettre le buffer � la taille.
	 */
	//void setIntegrationBufferSize(const hermiteProjector & hermitePolynome_1 , const hermiteProjector & hermitePolynome_2);

	/** ---------- DEPRECATED -------------
	 * M�thode pour calculer l'exposant.
	 */
	//void setExponent(const hermiteProjector & hermitePolynome_1 , const hermiteProjector & hermitePolynome_2);
	
public:

	/**
	 * Constructeur de la classe.
	 */
	hermiteIntegrationBuffer(void);

	/**
	 * M�thode pour connaitre le degr� maximal
	 * auquel on peut acc�der.
	 */
	const ipoint<3> getIntegrationBufferSize(void) const;

	/**
	 * M�thode pour connaitre le centre.
	 */
	const dpoint<3> & getCenter(void) const;

	/**
	 * M�thode pour connaitre le degr� maximal
	 * auquel on peut acc�der.
	 */
	int getIntegrationBufferSize(const int & dimension) const;
	
	/** ------ DEPRECATED ------------------
	 * M�thode pour connaitre le coefficient.
	 */
	//double getCoefficient(void) const;

	/**
	 * M�thode pour connaitre l'exposant.
	 */
	double getExponent(void) const;
	
	/**
	 * M�thode d'acc�s aux int�grales.
   */
	const double & getIntegrationValue(const int & rx ,const int & ry ,const int & rz) const;
	
	/**
	 * M�thode d'acc�s aux int�grales.
   */
	const double & getIntegrationValue(const ipoint<3> & r) const;

	/**
	 * M�thode pour mettre le buffer � la taille.
	 */
	void setIntegrationBufferSize(ipoint<3> degreeMax);
	
	/**
	 * M�thode pour fixer l'exposant.
	 */
	void setExponent(double exponent);
	
	/**
		* M�thode pour fixer le centre.
	 */
	void setCenter(const dpoint<3> & center);
	
	
	/** ------ DEPRECATED ------------------
	 * M�thode pour construire le buffer associ� aux projections
	 * de hermite.
	 */
	//void set(const hermiteProjector & hermitePolynome_1 , const hermiteProjector & hermitePolynome_2);
};

#endif 


