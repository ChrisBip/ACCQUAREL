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
#ifndef _CONTAINOR_SPARSE_2D_
#define _CONTAINOR_SPARSE_2D_

#include "ipoint.h"
#include <cstdlib>
#include <iostream>
#include <iomanip>
#include <map>

using namespace std;

/**
 * Classe qui permet de g�rer les tableaux creux dans le cas bi-dimensionnel.
 */
template<typename Type>
class containorSparse2D
{
private:

	/**
	 * d�finition d'un type de map qui va contenir les coefficients non nuls du tableau.
	 */
	typedef map<ipoint<2>,Type,ipointAlphebiticalCmp<2> > _containorSparse2D;
	
	/**
	 * Les coefficients du tableau.
	 */
	 _containorSparse2D Datas;

protected : 
	
	/**
	 * M�thode qui fait la copie.
	 *
	 * @param array le tableau � copier.
	 */
	inline void copy(const containorSparse2D & array)
	{
		Datas = array.Datas;
	}

public:
	
	/**
	 * Constructeur par d�faut.
	 */
	inline containorSparse2D(void)
	{
		;
	}

	/**
	 * Constrcuteur de copie.
	 *
	 * @param array le tableau avec lequel on souhaite initialiser l'objet.
	 */
	inline containorSparse2D(const containorSparse2D & array)
	{
		copy(array);
	}

	/**
	 * Destrcuteur.
	 */
	inline virtual ~containorSparse2D(void)
	{
		clear();
	}

	/**
	 * M�thode pour connaitre le premier degr� non nul qui compose le tableau.
	 * 
	 * @return la postion du "premier" �l�ment pr�sent dans le tableau.
	 */
	inline ipoint<2> begin(void) const
	{
		typename _containorSparse2D::const_iterator it = Datas.begin();	
		if(it == Datas.end()) {
			return end();
		} else {
			return it->first;
		}
	}

	/**
	 * M�thode pour remettre le tableau � z�ro.
	 */
	inline void clear(void)
	{
		Datas.clear();
	}

	/**
	 * M�thode pour savoir si le tableau est vide.
	 *
	 * @return true lorsque tous les coefficients du tableau sont nuls , false sinon.
	 */
	inline bool empty(void) const
	{
		return Datas.empty();
	}

	/**
	 * M�thode pour connaitre la marque de fin des it�rateurs pour les �l�ments du tableau.
	 *
	 * @return la marque de fin.
	 */
	inline ipoint<2> end(void) const
	{
		return ipoint<2>(-1,-1);	
	}

	/**
	 * M�thode get pour les �l�m�nts du tableau.
	 *
	 * @param position la position de l'�l�ment dont on souhaite connaitre la valeur.
	 *
	 * @return la valeur du ccoefficient pour la postion demand�e.
	 */
	Type getData(const ipoint<2> & position) const
	{
		assert(position[0] >= 0);
		assert(position[1] >= 0);

		typename _containorSparse2D::const_iterator it = Datas.find(position);

		if(it == Datas.end()) 
			return 0;
		else 
			return it->second;
	}

	/**
	 * M�thode get pour les �l�ments du tableau.
	 *
	 * @param row la ligne de l'�l�ment dont on souhaite connaitre la valeur.
	 *
	 * @param column la colone de l'�l�ment dont on souhaite connaitre la valeur.
	 *
	 * @return la valeur de l'�l��ment pour la position (row , column , layer)
   * 
	 * @warning la valeur de la ligne doit etre positive ou nulle.
	 *
	 * @warning la valeur de la colone doit etre positive ou nulle.
	 */
	Type getData(const int & row ,const int & column) const
	{
		assert(row >= 0);
		assert(column >= 0);

		return getData(ipoint<2>(row,column));
	}
	
	/**
	 * M�thode pour connaitrel le nombres de colones �quivalentes du tableau.
	 */
	inline int getNbrOfColumns(void) const
	{
		return getSize(1);
	}

	/**
	 * M�thode pour connaitrel le nombres de lignes �quivalentes du tableau.
	 */
	inline int getNbrOfRows(void) const
	{
		return getSize(0);
	}

	/**
	 * M�thode pour connaitre les la taille du tableau.
	 *
	 * Cette m�thode existe pour faire le lien avec les containor2D qui ne sont pas 
	 * sparse et renvoie un trip^let d'entiers (nombre de lignes, colones et couches) qu'il faudrait allouer 
	 * pour stocker les m�mes inforamtions dans un containor2D.
	 * 
	 * Par exemple pour le tableau qui s'�crit [(1,1,1)] cette m�thode renvoie (2,2,2). 
	 *
	 * @return la taille du tableau tridimensionnel au sens usuel du terme.
	 *
	 */
	inline ipoint<2> getSizes(void) const
	{
		ipoint<2> position , sizes(0);
		
		for(position = begin() ; position != end() ; position = next(position)) {
			sizes = ipoint<2>::uniformMax(position , sizes);
		}
		
		sizes+=ipoint<2>(1);

		return sizes;
	}

	/**
	 * M�thode pour connaitre les la taille du tableau dans une direction donn�e.
	 *
	 * Cette m�thode existe pour faire le lien avec les containor qui ne sont pas 
	 * sparse et renvoie le nombre de lignes, colones ou couches qu'il faudrait allouer 
	 * pour stocker les m�mes inforamtions dans un containor2D.
	 *
	 * @return la taille du tableau tridimensionnel au sens usuel du terme dans la direction
	 * demand�e.
	 *
	 * @warning comme le tableau est tridimensionnel, le parametre de dimension ne peut
	 * prendre que les valeurs 0 (pour acc�der au "nombre de lignes"), 1 (pour acc�der au "nombre de colones"), 
	 * ou 2(pour acc�der au "nombre de couches").
	 */
	inline int getSize(const int & dimension) const
	{
		assert(dimension >= 0);
		assert(dimension < 2);
		return getSizes()[dimension];
	}

	/**
	 * M�thode pour connaitre la position de l'�l�ment qui suit dans le tableau.
	 *
	 * @param position la position de l'�l�ment dont on souhaite connaitre le suivant.
	 *
	 * @return la position de l'�l�ment suivant.
	 *
	 * @warning la postion pass�e en argument doit �tre une position pr�sente dans
	 * le tableau.
	 */
	inline ipoint<2> next(const ipoint<2> & position) const
	{
		typename _containorSparse2D::const_iterator it = Datas.find(position);

		if(it == Datas.end()) {
			cerr << "Error : in ipoint<2> containorSparse2D::next(const ipoint<2> & positon) const" << endl;
			cerr << "Error : coefficient for key " << position << " not found" << endl;
			cerr << "Error : result may vary." << endl;
		}

		it++;

		if(it == Datas.end()) {
			return end();
		} else {
			return it->first;
		}
	}

	/**
	 * Op�rateur d'affectation.
	 *
	 * @param array le tableau � copier dans l'objet.
	 *
	 * @return une r�f�rence vers la tablleau qui contient les nouvelles valeurs.
	 */
	containorSparse2D<Type> & operator = (const containorSparse2D<Type> & array)
	{
		copy(array);
		return *this;
	}

	/**
	 * Op�rateur constant qui permet d'acc�der aux �l�ments du tableau.
	 *
	 * @param position la position de l'�l�ment dont on souhaite connaitre la valeur.
	 *
	 * @return la valeur demand�e.
	 *
	 * @warning la position de l'�l�ment que l'on souahite trouver dans le tableau 
	 * doit avoir toute ces composantes positvies ou nulles.
	 */
	inline Type operator() (const ipoint<2> & position) const
	{
		assert(position[0] >= 0);
		assert(position[1] >= 0);

		return getData(position);
	}

	/**
   * M�thode pour connaitre le dernier element present.
   *
	 * @return la position du dernier �l�ment du tableau.
	 */
  inline ipoint<2> rbegin(void) const
	{
		typename _containorSparse2D::const_reverse_iterator it = Datas.rbegin();
  
		if(it == Datas.rend()) {
			return rend();
		} else {
			return it->first;
		}
	}
  
	/**
	 * Op�rateur constant qui permet d'acc�der au coefficientsdu tableau.
	 *
	 * @param row la ligne de l'�l�ment dont on souhaite connaitre la valeur.
	 *
	 * @param column la colone de l'�l�ment dont on souhaite connaitre la valeur.
	 *
	 * @return la valeur de l'�l��ment pour la position (row , column)
	 *
	 * @warning la valeur de la ligne doit etre positive ou nulle.
	 *
	 * @warning la valeur de la colone doit etre positive ou nulle.
	 */
	inline Type operator() (const int & row , const int & column) const
	{
		assert(row >= 0);
		assert(column >= 0);

		return getData(row,column);
	}

	/**
   * M�thode qui ote du tableau le i-�me �l�ment.
	 *
   * @param i la position de l'�l�ment � oter.
	 *
	 * @return la position de l'�l�ment qui suit l'�l�ment qui a �t� ot�.
   *
	 * @warning monome de degr� degree � tout interet � etre
	 * pr�sent dans le tableau_base consid�r�, sinon la valeur
	 * renvoy�e par cette m�thode n'aura pas de sens.
	 *
	 * @warning la position de l'�l�ment que l'on souahite oter du tableau 
	 * doit avoir toute ces composantes positvies ou nulles.
	 */	
	inline ipoint<2> removeData(const ipoint<2> & i)
	{
		ipoint<2> nextDegree = next(i);
		Datas.erase(i);
		return nextDegree;
	}

	/**
   * Methode qui renvoie la valeur de l'indicateur de
   * fin.
   */
  ipoint<2> rend(void) const
	{
		return end();
	}


	/**
	 * M�thode pour connaitre l'�l�ment qui pr�c�de un �l�ment.
	 *
	 * @param i la position de l'�l�ment dont on souhaite connaitre le pr�c�dent.
	 *
	 * @return la position de l'�l�ment pr�c�dent l'�l�ment i.
	 *
	 * @warning Lorsque l'on utilise cette m�thode il vaut mieux etre sur
	 * que le tableau contient un �l�ment � la position i.
	 *
	 * @warning la position de l'�l�ment dont on cherche le pr�c�dent doit avoir
	 * une valuer positive ou nulle.
   *
	 */
  inline ipoint<2> rnext(const ipoint<2> & i) const
	{
		assert(i[0] >=0);
		assert(i[1] >=0);
		
		typename _containorSparse2D::const_iterator it = Datas.find(i);
  
		if(it == Datas.end()) {
			cerr << "Error : in int containorSparse::rnext(const int & i) const" << endl;
			cerr << "Error : no coefficient for key" << i << " was found." << endl;
			cerr << "Error : result may vary." << endl;
		}

		if(it == Datas.begin()) {
			return rend();
		} else {
			it--;
			return it->first;
		}
	}
	
  /**
   * Methode pour donner une valeur au i-eme �l�ment.
   *
	 * @param i la position de l'�l�ment � modifier.
	 *
	 * @param value la valeur que l'on souhaite attribuer � l'�l�ment.
	 *
	 * @warning la position de l'�l�ment doit avoir toutes ces copmposantes positives ou nulles.
	 */
	inline void setData(const ipoint<2> & position , const Type & value)
	{
		assert(position[0] >= 0);
		assert(position[1] >= 0);

		if(value == 0) {
			Datas.erase(position);		
		} else {
			pair<typename _containorSparse2D::iterator,bool> insert_result = Datas.insert(pair<ipoint<2>,Type>(position,value));

			if(insert_result.second == false && insert_result.first == Datas.end()) {
				cerr << "Error : in void containorSparse2D<Type>::set_coefficient(const ipoint<2> & position , const Type & value)." << endl;
				cerr << "Error : something wrong occurs when inserting " << value << " for position " << position << "." <<  endl;
				cerr << "Error : aborting program." << endl;
				exit(1);
			} else {
				(insert_result.first)->second = value;
			}	
		} 
	}

	/**
	 * M�thode SET pour le coefficient d'un monome.
	 * 
	 * @param row la ligne de l'�l�ment dont on souhaite modifier la valeur.
	 *
	 * @param column la colone de l'�l�ment dont on souhaite modifier la valeur.
	 *
	 * @warning la valeur de la ligne doit etre positive ou nulle.
	 *
	 * @warning la valeur de la colone doit etre positive ou nulle.
	 */
	inline void setData(const int & row , const int & column , const Type & value)
	{
		assert(row >= 0);
		assert(column >= 0);
	
		setData(ipoint<2>(row,column) , value);
	}

	/**
	 * M�thode pour mettre les valeurs d'un tableau � lidentique de
	 * celle s'un autre tableau.
	 *
	 * @param arraySparse le tableau dont on souhaite copier les valeurs.
	 *
	 * @see operator=(const containorSparse2D & arraySparse)
	 */
	inline void setDatas(const containorSparse2D & arraySparse)
	{
		copy(arraySparse);
	}

	/**
   * Methode pour l'affchage du tableau.
   *
	 * Cette m�thode affiche le tableau comme un tableau normal avec des x
	 * la ou la m�thode getData renvoie 0.
	 *
	 * @param outStream le flux dans lequel on souhaite afficher le tableau.
	 */
	inline void writeAsContainor(ostream & outStream) const 
	{
		int row , column  , nbrOfRows , nbrOfColumns;
		Type data;

		nbrOfRows = getNbrOfRows();
		nbrOfColumns = getNbrOfColumns();

		for(row=0 ; row < nbrOfRows ; row++) {
			for(column=0 ; column < nbrOfColumns ; column++) {
				data = getData(row,column);
				if(data == 0) {
				outStream << setw(8) << "x"; 
			} else {
				outStream << setw(8) << data;
			}
			}
			if(row < (nbrOfRows-1)) 
				outStream << endl;
		}
	}

	/**
	 * M�thode pour �crire le tableau dans un flux.
	 *
	 * Cette m�thode d�crit le tableau dans un format texte tout bete.
	 * 
	 * @param outStream le flux dans lequel on souhaite �crire le tableau.
	 */
	inline void writeText(ostream & outStream) const
	{
		ipoint<2> i;

		outStream << "[ ";
		if(empty()) {
			outStream << "0";
		} else {

			for(i=begin() ; i != end() ; i = next(i)) {
				if( i != begin() ) {
					outStream << " ; " ;
				}
				outStream << "( " << i << " , " << getData(i) << " )" ;
			}
		}
		outStream << " ]";
	}

	/**
	 * M�thode pour �crire le tableau dans un flux.
	 *
	 * Cette m�thode d�crit le tableau dans un format XML.
	 * 
	 * @param outStream le flux dans lequel on souhaite �crire le tableau.
	 */
	inline void writeXML(ostream & outStream) const
	{
		ipoint<2> i;
		for(i=begin() ; i != end() ; i = next(i)) {
			outStream << "<Data>" << endl;
			outStream << "\t<Row>" << i[0] << "</Row>" << endl;
			outStream << "\t<Column>" << i[1] << "</Column>" << endl;
			outStream << "\t<Value>" << getData(i) << endl ;
			outStream << "</Data>" << endl;
		}
	}
};

/**
 * Op�rateur pour �crire un containorSparse2D dans un flux.
 *
 * @param outStream le flux dans lequel on souhaite �crire le tableau.
 *
 * @param arraySparse2D le tableau � �crire dans le flux.
 *
 * @return le flux contenant le tableau.
 */
 template<typename Type>
 inline ostream & operator<<(ostream & outStream , const containorSparse2D<Type> & arraySparse2D)
 {
	arraySparse2D.writeText(outStream);
	return outStream;
 }

#endif

