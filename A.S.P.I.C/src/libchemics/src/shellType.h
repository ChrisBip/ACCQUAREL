/* 
* The chemics library of A.S.P.I.C. 
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
#ifndef _GAUSSIAN_BASIS_SHELL_TYPE_
#define _GAUSSIAN_BASIS_SHELL_TYPE_


#include <containor.h>
#include <ipoint.h>

class shellType
{
private:
	
	/**
	 * La chaine de charact�re pour qui contient la cl� du type de couche dans
	 * la base de donn�es.
	 */
	string ShellTypeKey;
	
	/**
   * La chaine de charact�re qui contient le nom de la couche.
	 */
	string ShellTypeName;

	/**
   * Les degres des monomes qui composent la couche.
	 */
	containor< ipoint<3> > MonomeDegrees;
	
protected:

	/**
	 * M�thode pour faire la copie d'un type de couche.
	 */
	void copy(const shellType & shell);

public:

	/**
   * Constructeur par d�faut.
	 */
	shellType(void);

	/**
	 * Constructeur de copie.
	 *
	 * @param shell le type de couche avec lequel l'objet nouvellement cr�er sera instanci�.
	 */
	shellType(const shellType & shell);

	/**
	 * Destructeur.
	 */
	~shellType(void);

	/**
	 * M�thode pour remmettre le type de couche � z�ro.
	 */
	void clear(void);
	
	/**
	 * M�thode pour savoir si le type de couche est vide.
	 */
	bool empty(void) const;
	
	/**
	 * M�thode pour connaitre le plus haut degr� de la couche.
	 */
	int getHigherDegree(void) const;
	
	/**
	 * M�thode pour connaitre le degr� du monome item de la couche.
	 *
	 * @warning il faut que le parametre item soit compris entre
	 * 0 et le nombre de monomes pr�sents dans la couche.
	 */
	const ipoint<3> & getMonomeDegree(int item) const;
	
	/**
	 * M�thode pour acc�der aux degr�s de la couche comme un tableau
	 * de degr�s.
	 */
	const containor< ipoint<3> > & getMonomeDegrees(void) const;
	
	/**
	 * M�thode pour connaitre le nombre de fonctions de base dans la couche.
	 * Cette m�thode revient � compter le nombre de degr� de monomes pr�sents dans la 
	 * couche.
	 */
	int getNbrOfBasisFunctions(void) const;
	
	/**
	 * M�thode pour connaitre le nom de la cl� du type 
	 * de couche dans la base de donn�es. Si l'objet n'a pas
	 * �t� cr�e par la lecture dans la base de donn�es alors
	 * la cahine retourn�e est vide.
	 */
	const string & getShellTypeKey(void) const;
	
	/**
	 * M�thode pour connaitre le nom du type de manipul� couche.
	 */
	const string & getShellTypeName(void) const;

	/**
	 * Op�rateur d'affectation.
	 */
	shellType & operator=(const shellType & shell);
	
	/**
	 * M�thode pour sp�cifier les degr�s de tout les monomes.
	 *
	 * Cette m�thode recopie le tableau pass�s en argument comme �tant
	 * l'ensemble de degr�s des monomes qui composent la couche.
	 */
	void setMonomeDegrees(const containor< ipoint<3> > & monomeDegrees);

	/**
	 * M�thode pour modifier le degr� d'un monome.
	 *
	 * @param item le num�ro du monome dont on souhaite modifier le degr�.
	 *
	 * @param monomeDegree la valeur du degr� � affecter au monome item. 
	 */
	void setMonomeDegree(int item , const ipoint<3> & monomeDegree);

	/**
	 * M�thode pour modifier le degr� d'un monome.
	 *
	 * @param item le num�ro du monome dont on souhaite modifier le degr�.
	 *
	 * @param monomeDegreeX la valeur du degr� � affecter au monome item pour la composante en X. 
	 * @param monomeDegreeY la valeur du degr� � affecter au monome item pour la composante en Y. 
	 * @param monomeDegreeZ la valeur du degr� � affecter au monome item pour la composante en Z. 
	 */
	void setMonomeDegree(int item , int monomeDegreeX , int monomeDegreeY , int monomeDegreeZ);

	/**
   * M�thode pour modifier le nombre de fonctions de bases pr�sentent dans la couche.
	 * 
	 * @param nbrOfBasisFunctions le nombre de fonctions de base pr�sentes dans la couche.
	 */
	void setNbrOfBasisFunctions(int nbrOfBasisFunctions);

	/**
	 * M�thode pour retrouver un type de couche � partir de sa cl� dans la base de donn�es.
	 *
	 * @parma shellTypeKey la cl� � rechercher dans la base de donn�es.
	 */
	void setShellType(const string & shellTypeKey);

	/**
	 * M�thode pour recopier les valeurs d'un type de couche dans l'objet.
	 *
	 * @param shell le type de couche � recopier dans l'objet.
	 */
	void setShellType(const shellType & shell);

	/**
	 * M�thode pour modifier la cl� du type de couche.
	 *
	 * @param shellTypeKey la cl� � attribuer au type de couche.
	 */
	void setShellTypeKey(const string & shellTypeKey);
	
	/**
	 * M�thode pour modifier le nom du type de couche.
	 *
	 * @param shellTypeName le nom a attribuer au type de couche.
	 */
	void setShellTypeName(const string & shellTypeName);
	
	/**
	 * M�thode pour �crire le type de couche dans un format humain.
	 */
	void writeHuman(ostream & out , const string & linePrefix = "") const;
};


/**
 * Op�rateur externe pour l'�criture dans un flux.
 *
 * @param outStream le flux dans lequel on souahite �crire la mol�cule.
 *
 * @param shell le type de couche � �crire dans le flux.
 */
ostream & operator<<(ostream & outStream , const shellType & shell);

#endif

