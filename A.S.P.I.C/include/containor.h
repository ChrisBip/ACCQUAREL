/* 
 * The containor library of the A.S.P.I.C. 
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
#ifndef _CONTAINOR_
#define _CONTAINOR_

#include <assert.h>
#include <stdlib.h>
#include <iostream>
using namespace std;

/**
 * @class containor.
 * Classe pour la gestion d'un conteneur d'un certains nombres d'objet.
 * 
 * Le propos de cette classe est de ne plus utiliser de new et delete
 * dans les programme, mais des objets containor.
 */
template<class Type>
class containor
{
	private:

	/**
	 * Le nombre de donn�es qui sont presentes dans le conteneur.
	 */
	int NbrOfRows;
	
	/**
	 * Tableau de donn�es.
	 */
	Type * Datas;

protected:

	/**
	 * M�thode qui permet d'allouer l'espace m�moire.
	 *
	 * @param nbrOfRows le nombre d'�l�ments qui pourront etre 
	 * contenues dans l'objet.
	 */
	inline void alloc(int nbrOfRows)
	{
		assert(NbrOfRows == 0);
		assert(nbrOfRows > 0);
		NbrOfRows = nbrOfRows;
		Datas = new Type[nbrOfRows];
	}

	/**
	 * M�thode qui permet de copier un conteneur dans l'objet courrant.
	 *
	 * @param c le containor � copier dans l'objet courrant.
	 */
	inline void copy(const containor<Type> & c)
	{
		int nbrOfRows = c.getNbrOfRows();
		setSizes(nbrOfRows);
		for(int i=0 ; i < nbrOfRows ; i++) setData(i , c.getData(i));
	}

	/**
	 * M�thode qui lib�re l'espace m�moire.
	 */
	inline void free(void)
	{
		if(NbrOfRows == 0) return;
		delete [] Datas;
		Datas = NULL;
		NbrOfRows = 0;
	}

public:

	/**
	 * Constructeur par d�faut.
	 * 
	 * Construit un objet vide qui ne peut contenir aucune 
	 * donn�e.
	 */
	inline containor(void)
		: NbrOfRows(0) , 
			Datas(NULL)
	{
		;
	}

	/**
	 * Constructeur avec une sp�cification de la taille.
	 *
	 * @param nbrOfRows la taille du conteneur qui doit etre construit.
	 *
	 * @warning il faut que le nombre d'�lements du tableu soit strictement
	 * positif.
	 */
	inline containor(const int & nbrOfRows)
		: NbrOfRows(0) , 
			Datas(NULL)
	{
		assert (nbrOfRows > 0);

		this->setSize(nbrOfRows);
	}

	/**
	 * Constructeur de copie.
	 *
	 * @param c le containor � copier dans l'objet construit.
	 */
	inline containor(const containor<Type> & c) 
		: NbrOfRows(0) , 
			Datas(NULL)
	{
		copy(c);
	}

	/**
	 * Destrucuteur.
	 */
	inline virtual ~containor(void)
	{
		free();
	}

	/**
	 * M�thode pour remettre tout le conteneur � z�ro.
	 *
	 * @warning ici remettre � z�ro revient � cr�er un containor vide.
	 */
	inline void clear(void) 
	{
		free();
	}

	/**
	 * Methode pour savoir si l'objet que l'on manipule est vide.
	 *
	 * @return true lorsque l'objet est vide, false sinon.
	 */
	inline bool empty(void) const
	{
		if(getNbrOfRows() == 0) {
			return true;
		} else {
			return false;
		}
	}

	/**
	 * M�thode pour connaitre la i-�me valeur contenue dans le tableau.
	 *
	 * @param i la position de la donn�es � laquelle on souhaite acc�der.
	 * @return une r�f�rence constante vers le i-�me �l�ment du containor.
	 *
	 * @warning lorsque l'on passe un argument n�gatif ou sup�rieur
	 * au nombre de donn�es cela provoque l'arret du programe.
	 */

	inline const Type & getData(const int & i) const
	{
		assert(i >= 0);
		assert(i < getNbrOfRows());

		return Datas[i];
	}

	/**
	 * M�thode pour connaitre la i-�me valeur contenue dans le tableau.
	 *
	 * @param i la position de la donn�es � laquelle on souhaite acc�der.
	 * @return une r�f�rence vers le i-�me �l�ment du containor.
	 *
	 * @warning lorsque l'on passe un argument n�gatif ou sup�rieur
	 * au nombre de donn�es cela provoque l'arret du programe.
	 */

	inline Type & getData(const int & i)
	{
		assert(i >= 0);
		assert(i < getNbrOfRows());
		return Datas[i];
	}

	/**
	 * M�thode acc�der aux tableau comme si c'�tait un pointeur.
	 *
	 * @return le pointeur qui contient tout les �l�ments.
	 */
	inline const Type * getDatas(void) const
	{
		return Datas;
	}

	/**
	 * M�thode pour connaitre la taille du tableau.
	 * 
	 * @return le nombre d'�l�ments qui peuvent etre stock�s
	 * dans l'objet.
   */
	inline const int & getNbrOfRows(void) const
	{
		return NbrOfRows;
	}

	/**
	 * M�thode pour connaitre la taille du tableau dans une direction donn�e.
	 *
	 * Cette m�thode est inutile, dans le cadre d'un containor tout simple, mais
	 * par homog�n�it� il me semble utile de la mettre. (Par ex. pour une future
	 * impl�mentation templatis�e de ces classes).
	 * 
	 * @param dimension la dimension dans laquelle on souhaite connaitre la taille, 
	 * ici ce param�tre doit etre 0.
	 *
	 * @return le nombre de lignes du le tableau.
	 *
	 * @warning la dimension doit prendre la valeur 0 ( pour acc�der aux nombre de lignes).
	 */
	inline const int & getSize(const int & dimension) const
	{
		assert(dimension == 0);
		return getNbrOfRows();
	}

	/**
	 * M�thode pour connaitre la taille du tableau.
	 * 
	 * @return le nombre d'�l�ments qui peuvent etre stock�s
	 * dans l'objet.
   */
	inline const int & getSizes(void) const
	{
		return getNbrOfRows();
	}

	/**
	 * M�thode pour connaitre la taille de l'espace m�moire allou�.
	 *
	 * @return le nombre d'�l�ments qui on �t�s allou�s �r la m�thode
	 * alloc.
	 */
	inline const int & getStorageSize(void) const
	{
		return getNbrOfRows();
	}

	/**
	 * Op�rateur pour acc�der aux �l�ments du conteneur.
	 *
	 * @param i la position de la donn�es � laquelle on souhaite acc�der.
	 * @return une r�f�rence constante vers le i-�me �l�ment du containor.
	 *
	 * @warning lorsque l'on passe un argument n�gatif ou sup�rieur
	 * au nombre de donn�es cela provoque l'arret du programe.
	 */
	inline const Type & operator[] (const int & i) const
	{
		assert(i >= 0);
		assert(i < getNbrOfRows());
		return getData(i);
	}

	/**
	 * Op�rateur pour acc�der aux �l�ments du conteneur.
	 *
	 * @param i la position de la donn�es � laquelle on souhaite acc�der.
	 * @return une r�f�rence vers le i-�me �l�ment du containor.
	 *
	 * @warning lorsque l'on passe un argument n�gatif ou sup�rieur
	 * au nombre de donn�es cela provoque l'arret du programe.
	 */
	inline Type & operator[] (const int & i) 
	{
		assert(i >= 0);
		assert(i < getNbrOfRows());
		return getData(i);
	}

	/**
	 * Op�rateur de copie
	 *
	 * @param c le containor que l'on souhaite copier dans l'objet courrant.
	 * @return une r�f�rence vers le nouvel objet qui contient le containor c.
	 */

	inline containor & operator=(const containor<Type> & c)
	{
		copy(c);
		return *this;
	}	

	/**
	 * M�thode pour changer la valeur d'un �l�ment du tableau.
	 *
	 * @param value la valeur avec laquelle on souhaite remplir le containor.
	 *
	 * @param i la positon de l'�l�ment � modifier.
	 *
	 * @warning lorsque l'on passe comme position un argument n�gatif ou sup�rieur
	 * au nombre de donn�es cela provoque l'arret du programe.
	 */
	inline void setData(const int & i , const Type & value)
	{
		assert(i >= 0);
		assert(i < getNbrOfRows());

		Datas[i] = value;
	}

	/**
	 * M�thode pour remplir le conteneur avec une seule valeure.
	 *
	 * @param value la valeur avec laquelle on souhaite remplir le containor.
	 */
	inline void setDatas(const Type & value)
	{
		for(int i=0 ; i < getNbrOfRows() ; i++) setData(i , value);
	}

	
	inline void setDatas(const containor<Type> & array)
	{
		copy(array);
	}


	/**
	 * M�thode pour sp�cifier la taille du containor.
	 *
	 * @param nbrOfRows le nombre de donn�es qui pourront etre contenues
	 * dans l'objet.
	 *
	 * @warning le nombre d'�l�ments que peut contenir le tableau doit etre un
	 * nombre strictement positif.
	 *
	 * @see clear.
	 */
	inline void setSizes(const int & nbrOfRows)
	{
		assert (nbrOfRows > 0);

		if(nbrOfRows == getNbrOfRows()) return;
		if(getNbrOfRows() > 0) free();
		alloc(nbrOfRows);
	}

	/**
	 * M�thode qui permet d'afficher le conteneur sous une forme
	 * lisible pour l'homme.
	 * 
	 * Il est iportant de remarquer que cette m�thode est virtuelle. 
	 * Cela permet � tous les objets qui h�ritent de la classe containor
	 *  et qui  r�impl�mentent cette m�thode, utiliser
	 * l'operator<< qui n'est qu'une encapsulation de cette m�thode.
	 * 
	 * @param out le flux dans lequel on veut �crire le contrainor. 
	 */
	inline virtual void writePretty(ostream & out) const
	{
		int i , nbrOfRows = getNbrOfRows();
		out << "[ " ;
		for( i = 0 ; i < nbrOfRows ; i++) {
			out << getData(i) << ( i == (nbrOfRows -1) ? " ]" : " , " );
		}
	}

	/**
	 * M�thode qui permet d'afficher le conteneur sous une forme
	 * lisible pour l'homme.
	 * 
	 * @param out le flux dans lequel on veut �crire le contrainor.
	 * @param enclosingTagName le nom du tag qui marquera le d�but et
	 * la fin des donn�es du containor.
	 *
	 */
	inline void writeXML(ostream & out , const string & enclosingTagName = "Containor") const
	{
		int i , nbrOfRows = getNbrOfRows();
		
		out << "<" << enclosingTagName << ">" << endl;
		
		for( i = 0 ; i < nbrOfRows ; i++) {
			out << "<Coefficient>" << endl;				
			out << "<Row>" << i << "</Row>" << endl;
			out << "<Value>" << getData(i)<< "</Value>" << endl; 
			out << "</Coefficient>" << endl;	
		}

		out << "</" << enclosingTagName << ">" << endl;
	}

};

/**
 * Op�rateur d'�criture d'un containor dns un flux.
 *
 * @param out le flux dans lequel on veut �crire le containor.
 * @param c le containor � �crire dans le flux.
 *
 * @param out le flux dans lequel on souhaite �crire le containor.
 */
template<class Type>
inline ostream & operator << ( ostream & out , const containor<Type> & c) 
{
	c.writePretty(out);
	return out;
}

#endif
