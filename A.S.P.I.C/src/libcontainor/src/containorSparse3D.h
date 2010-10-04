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
#ifndef _CONTAINOR_SPARSE_3D_
#define _CONTAINOR_SPARSE_3D_

#include "ipoint.h"
#include <cstdlib>
#include <iostream>
#include <iomanip>
#include <map>

using namespace std;

/**
 * Classe qui permet de g�rer les tableaus 
 * dans le cas tri - dimensionnel.
 */
template<typename Type>
class containorSparse3D
{
private:

	/**
	 * d�finition d'un type de map qui va contenir les coefficients du tableau.
	 */
	typedef map<ipoint<3>,Type,ipointAlphebiticalCmp<3> > _containorSparse3D;
	
	/**
	 * Les coefficients du tableau.
	 */
	 _containorSparse3D Datas;

protected : 
	
	/**
	 * M�thode qui fait la copie.
	 *
	 * @param array le tableau � copier.
	 */
	inline void copy(const containorSparse3D & array)
	{
		Datas = array.Datas;
	}

public:
	
	/**
	 * Constructeur par d�faut.
	 */
	inline containorSparse3D(void)
	{
		;
	}

	/**
	 * Constrcuteur de copie.
	 *
	 * @param array le tableau avec lequel on souhaite initialiser l'objet.
	 */
	inline containorSparse3D(const containorSparse3D & array)
	{
		copy(array);
	}

	/**
	 * Destrcuteur.
	 */
	inline virtual ~containorSparse3D(void)
	{
		clear();
	}

	/**
	 * M�thode pour connaitre le premier degr� non nul qui compose le tableau.
	 * 
	 * @return la postion du "premier" �l�ment pr�sent dans le tableau.
	 */
	inline ipoint<3> begin(void) const
	{
		typename _containorSparse3D::const_iterator it = Datas.begin();	
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
	inline ipoint<3> end(void) const
	{
		return ipoint<3>(-1,-1,-1);	
	}

	/**
	 * M�thode get pour les �l�m�nts du tableau.
	 *
	 * @param position la position de l'�l�ment dont on souhaite connaitre la valeur.
	 *
	 * @return la valeur du ccoefficient pour la postion demand�e.
	 */
	Type getData(const ipoint<3> & position) const
	{
		assert(position[0] >= 0);
		assert(position[1] >= 0);
		assert(position[2] >= 0);

		typename _containorSparse3D::const_iterator it = Datas.find(position);

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
	 * @param layer la couche de l'�l�ment dont on souhaite connaitre la valeur.
	 *
	 * @return la valeur de l'�l��ment pour la position (row , column , layer)
   * 
	 * @warning la valeur de la ligne doit etre positive ou nulle.
	 *
	 * @warning la valeur de la colone doit etre positive ou nulle.
	 *
	 * @warning la valeur de couche doit etre positive ou nulle.
	 */
	Type getData(const int & row ,const int & column , const int & layer) const
	{
		assert(row >= 0);
		assert(column >= 0);
		assert(layer >= 0);

		return getData(ipoint<3>(row,column,layer));
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
	inline int getNbrOfLayers(void) const
	{
		return getSize(2);
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
	 * Cette m�thode existe pour faire le lien avec les containor3D qui ne sont pas 
	 * sparse et renvoie un trip^let d'entiers (nombre de lignes, colones et couches) qu'il faudrait allouer 
	 * pour stocker les m�mes inforamtions dans un containor3D.
	 * 
	 * Par exemple pour le tableau qui s'�crit [(1,1,1)] cette m�thode renvoie (2,2,2). 
	 *
	 * @return la taille du tableau tridimensionnel au sens usuel du terme.
	 *
	 */
	inline ipoint<3> getSizes(void) const
	{
		ipoint<3> sizes(0);
		sizes = getExtremPositions();		
		sizes+=ipoint<3>(1);
		return sizes;
	}

	/**
	 * M�thode pour connaitre les la taille du tableau dans une direction donn�e.
	 *
	 * Cette m�thode existe pour faire le lien avec les containor qui ne sont pas 
	 * sparse et renvoie le nombre de lignes, colones ou couches qu'il faudrait allouer 
	 * pour stocker les m�mes inforamtions dans un containor3D.
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
		assert(dimension < 3);
		return getSizes()[dimension];
	}

	/**
	 * M�thode le positions extermes du tableau.
	 *
	 * Cette m�thode existe pour faire le lien avec les containor3D qui ne sont pas 
	 * sparse et renvoie un trip^let d'entiers (nombre de lignes, colones et couches) qu'il faudrait allouer 
	 * pour stocker les m�mes inforamtions dans un containor3D.
	 * 
	 * Par exemple pour le tableau qui s'�crit [(1,1,1)] cette m�thode renvoie (2,2,2). 
	 *
	 * @return la taille du tableau tridimensionnel au sens usuel du terme.
	 *
	 */
	inline ipoint<3> getExtremPositions(void) const
	{
		ipoint<3> position , sizes(0);
		
		for(position = begin() ; position != end() ; position = next(position)) {
			sizes = ipoint<3>::uniformMax(position , sizes);
		}
		
		return sizes;
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
	inline ipoint<3> next(const ipoint<3> & position) const
	{
		typename _containorSparse3D::const_iterator it = Datas.find(position);

		if(it == Datas.end()) {
			cerr << "Error : in ipoint<3> containorSparse3D::next(const ipoint<3> & positon) const" << endl;
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
	containorSparse3D<Type> & operator = (const containorSparse3D<Type> & array)
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
	inline Type operator() (const ipoint<3> & position) const
	{
		assert(position[0] >= 0);
		assert(position[1] >= 0);
		assert(position[2] >= 0);

		return getData(position);
	}

	/**
	 * Op�rateur constant qui permet d'acc�der au coefficientsdu tableau.
	 *
	 * @param row la ligne de l'�l�ment dont on souhaite connaitre la valeur.
	 *
	 * @param column la colone de l'�l�ment dont on souhaite connaitre la valeur.
	 *
	 * @param layer la couche de l'�l�ment dont on souhaite connaitre la valeur.
	 *
	 * @return la valeur de l'�l��ment pour la position (row , column , layer)
	 *
	 * @warning la valeur de la ligne doit etre positive ou nulle.
	 *
	 * @warning la valeur de la colone doit etre positive ou nulle.
	 *
	 * @warning la valeur de couche doit etre positive ou nulle.
	 */
	inline Type operator() (const int & row , const int & column , const int & layer) const
	{
		assert(row >= 0);
		assert(column >= 0);
		assert(layer >= 0);
		return getData(row,column,layer);
	}
	
	/**
   * M�thode pour connaitre le dernier element present.
   *
	 * @return la position du dernier �l�ment du tableau.
	 */
  inline ipoint<3> rbegin(void) const
	{
		typename _containorSparse3D::const_reverse_iterator it = Datas.rbegin();
  
		if(it == Datas.rend()) {
			return rend();
		} else {
			return it->first;
		}
	}

	/**
   * M�thode qui ote du tableau le i-�me �l�ment.
	 *
   * @param i la position de l'�l�ment � oter.
	 *
	 * @return la position de l'�l�ment qui suit l'�l�ment qui a �t� ot�.
   *
	 * @warning un �l�ment � tout interet � etre
	 * pr�sent dans le tableau � la position i consid�r�, sinon la valeur
	 * renvoy�e par cette m�thode n'aura pas de sens.
	 *
	 * @warning la position de l'�l�ment que l'on souahite oter du tableau 
	 * doit avoir toute ces composantes positvies ou nulles.
	 */	
	inline ipoint<3> removeData(const ipoint<3> & i)
	{
		ipoint<3> nextDegree = next(i);
		Datas.erase(i);
		return nextDegree;
	}

	/**
   * Methode qui renvoie la valeur de l'indicateur de fin.
   */
  ipoint<3> rend(void) const
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
  inline ipoint<3> rnext(const ipoint<3> & i) const
	{
		assert(i[0] >=0);
		assert(i[1] >=0);
		assert(i[2] >=0);
		
		typename _containorSparse3D::const_iterator it = Datas.find(i);
  
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
	inline void setData(const ipoint<3> & position , const Type & value)
	{
		assert(position[0] >= 0);
		assert(position[1] >= 0);
		assert(position[2] >= 0);

		if(value == 0) {
			Datas.erase(position);		
		} else {
			pair<typename _containorSparse3D::iterator,bool> insert_result = Datas.insert(pair<ipoint<3>,Type>(position,value));

			if(insert_result.second == false && insert_result.first == Datas.end()) {
				cerr << "Error : in void containorSparse3D<Type>::set_coefficient(const ipoint<3> & position , const Type & value)." << endl;
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
	 * @param layer la couche de l'�l�ment dont on souhaite modifier la valeur.
	 *
	 * param value la valeur que l'on souahite attribuer � l'�l�m�ent du tableau.
	 *
	 * @warning la valeur de la ligne doit etre positive ou nulle.
	 *
	 * @warning la valeur de la colone doit etre positive ou nulle.
	 *
	 * @warning la valeur de couche doit etre positive ou nulle.
	 */
	inline void setData(const int & row , const int & column , const int & layer , const Type & value)
	{
		assert(row >= 0);
		assert(column >= 0);
		assert(layer >= 0);

		setData(ipoint<3>(row,column,layer) , value);
	}

	/**
	 * M�thode pour mettre les valeurs d'un tableau � lidentique de
	 * celle s'un autre tableau.
	 *
	 * @param arraySparse le tableau dont on souhaite copier les valeurs.
	 *
	 * @see operator=(const containorSparse3D & arraySparse)
	 */
	inline void setDatas(const containorSparse3D & arraySparse)
	{
		copy(arraySparse);
	}

	/**
	 * M�thode pour �crire le tableau dans un flux.
	 *
	 * @param outStream le flux dans lequel on souhaite �crire le tableau.
	 */
	inline void write(ostream & outStream) const
	{
		ipoint<3> i;

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
   * Methode pour l'affchage du tableau.
   *
	 * Cette m�thode affiche le tableau comme un tableau normal avec des x
	 * la ou la m�thode getData renvoie 0.
	 *
	 * @param outStream le flux dans lequel on souhaite afficher le tableau.
	 */
	inline void writeAsContainor(ostream & outStream) const 
	{
		int row , column , layer , nbrOfRows , nbrOfColumns , nbrOfLayers;
		Type data;

		nbrOfRows = getNbrOfRows();
		nbrOfColumns = getNbrOfColumns();
		nbrOfLayers = getNbrOfLayers();

		for(layer=0 ; layer < nbrOfLayers ; layer++) {

			outStream << setw(8*nbrOfColumns) << setfill('-') << "" << setfill(' ') << endl;

			for(row=0 ; row < nbrOfRows ; row++) {
				for(column=0 ; column < nbrOfColumns ; column++) {
					data = getData(row,column,layer);
					if(data == 0) {
						outStream << setw(8) << "x"; 
					} else {
						outStream << setw(8) << data;
					}
			}
				outStream<< endl;
		}
			
			if(layer <(nbrOfLayers-1)) {
				outStream << endl;
			}
		}
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
		ipoint<3> i;
		for(i=begin() ; i != end() ; i = next(i)) {
			outStream << "<Data>" << endl;
			outStream << "\t<Row>" << i[0] << "</Row>" << endl;
			outStream << "\t<Column>" << i[1] << "</Column>" << endl;
			outStream << "\t<Layer>" << i[2] << "</Layer>" << endl;
			outStream << "\t<Value>" << getData(i) << endl ;
			outStream << "</Data>" << endl;
		}
	}
};

/**
 * Op�rateur pour �crire un containorSparse3D dans un flux.
 *
 * @param outStream le flux dans lequel on souhaite �crire le tableau.
 *
 * @param arraySparse3D le le tableau � �crire dans le flux.
 *
 * @return le flux contenant le tableau.
 */
 template<typename Type>
 inline ostream & operator<<(ostream & outStream , const containorSparse3D<Type> & arraySparse3D)
 {
	arraySparse3D.write(outStream);
	return outStream;
 }

#endif

