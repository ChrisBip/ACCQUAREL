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
#ifndef _CONTAINOR_SPARSE_
#define _CONTAINOR_SPARSE_

#include <assert.h>
#include <iostream>
#include <iomanip>
#include<map>
using namespace std;

/**
 * Classe pour g�r�r des tableaux dont la taille n'est pas connue
 * et qui vont comporter de nombreux z�ros.
 */
template<typename Type>
class containorSparse
{	

 private:
  
	 /**
	  * D�finition du type de stockage qui va �tre utilis� pour les containor sparse.
	  * Nous utilisons les map de la STL dont les cl�s seront des entiers et les le valeurs
		* de objets de type Type.
		*/
	 typedef map<int , Type> _containorSparse;
  
	 /**
	  * Les �lements du tableau.
		*/
	 _containorSparse Datas;
  
 protected:
  
  /**
   * M�thode pour copier un objet containorSparse.
	 *
	 * @param arraySparse le tableau que l'on d�sire copier.
   */
	inline void copy(const containorSparse<Type> & arraySparse)
	{
		Datas = arraySparse.Datas;
	}
  
 public:
  
  /**
   * Constructeur par d�faut.
	 *
	 * Construit un tableau qui ne contient que des �l�ments nuls
   */
  inline containorSparse(void)
		 : Datas()
	{
		clear();
	}

  /**
   * Destucteur.
   */
  inline virtual ~containorSparse(void)
	{
		clear();
	}

  /**
   * M�thode qui r�initialise le tableau.
   */
  inline void clear(void)
  {
		Datas.clear();
	}

  /**
   * M�thode pour savoir si le tableau est vide.
	 *
	 * @return true lorsque le tableau ne contient aucun �l�ment
	 * et false sinon.
   */
	inline bool empty(void) const
	{
	  return Datas.empty();
	}

  /**
   * Methode qui renvoie la valeur de l'indicateur de
   * fin.
   */
	inline int end(void) const 
	{
	  return -1;
	} 
  
	/**
   * Methode pour acceder � un �l�ment du tableau.
	 *
	 * @param i la positon de l'�l�ment dont on souhaite connaitre la valeur, 
   *
	 * @return la valeur du i-eme �l�ment.
	 *
	 * @warning la valeur de la position doit etre un entier positif ou nul.
	 */
  inline Type getData(const int & i) const 
	{
		assert( i >= 0);

		typename _containorSparse::const_iterator it = Datas.find(i);
		
		if(it == Datas.end()) {
			return 0;
		} else {
			return it->second;
		}
	
	}

	/**
	 * M�thode pour connaitre le nombre de lignes �quivalents stoqu�s dans le tableau.
	 *
	 * @return la taille qu'il faudrait allouer pour stoquer tout les �l�ments
	 * dans un tableau standart.
	 */
	inline int getNbrOfRows(void) const 
	{
		return getSize(0);
	}

	/**
	 * M�thode pour connaitre le nombre d'�l�ments �quivalents stoqu�s dans le tableau.
	 *
	 * @return la taille qu'il faudrait allouer pour stoquer tout les �l�ments
	 * dans un tableau standart.
	 */
	inline int getSizes(void) const 
	{
		return rbegin()+1;
	}

	/**
	 * M�thode pour connaitre le nombre d'�l�ments �quivalents stoqu�s dans le tableau.
	 *
	 *
	 * @param dimension comme nous travaillons ici sur des tableaux monodimensionnels,
	 * la dimension est forc�ment 0.
	 *
	 * @return la taille qu'il faudrait allouer pour stoquer tout les �l�ments
	 * dans un tableau standart.
	 */
	inline int getSize(const int & dimension) const 
	{
		assert(dimension==0);

		return getSizes();
	}

	/**
	 * M�thode pour connaitre le nombre d'�l�ments stoqu�s dans le tableau.
	 *
	 * @return  le nombre d'�l�ments stock�s dans le tableau.
	 */
	inline int getStorageSize(void) const 
	{
		return Datas.size();
	}

	/**
   * Methode pour connaitre la position du premier element
   *
	 * @return la position du premier �l�ment.
	 */
  inline int begin(void) const
	{
		typename _containorSparse::const_iterator it = Datas.begin();
  
		if(it == Datas.end()) {
			return end();
		} else {
			return it->first;
		}
	}
  
  /**
   * Methode pour connaitre l'�l�ment suivant.
	 *
	 * @param i la position de l'�l�ment dont on souhaite connaitre le suivant.
	 *
	 * @return la position de l'�l�ment suivant l'�l�ment i.
	 *
	 * @warning Lorsque l'on utilise cette m�thode il vaut mieux etre sur
	 * que le tableau contient un �l�ment � la position i.
	 *
	 * @warning la position de l'�l�ment dont on cherche le suivant doit avoir
	 * une valuer positive ou nulle.
   */
	inline int next(const int & i) const
	{
		assert(i >=0);

		typename _containorSparse::const_iterator it = Datas.find(i);

		if(it == Datas.end()) {
			cerr << "Error : in int containorSparse::next(const int & i) const" << endl;
			cerr << "Error : no coefficient for key" << i << " was found." << endl;
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
 	 * Op�rateur pour acceder � un �l�ment du tableau.
	 *
	 * @param i la positon de l'�l�ment dont on souhaite connaitre la valeur, 
	 *
	 * @return la valeur du i-eme �l�ment.
	 *
	 * @warning la valeur de la position doit etre un entier positif ou nul.
	 */
  Type operator[] (const int & i) const
	{
		assert ( i >= 0);

		return getData(i);
	}
	
	/**
   * M�thode pour connaitre le dernier element present.
   *
	 * @return la position du dernier �l�ment du tableau.
	 */
  inline int rbegin(void) const
	{
		typename _containorSparse::const_reverse_iterator it = Datas.rbegin();
  
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
	 * @warning monome de degr� degree � tout interet � etre
	 * pr�sent dans le polynome_base consid�r�, sinon la valeur
	 * renvoy�e par cette m�thode n'aura pas de sens.
	 *
	 * @warning la position de l'�l�ment que l'on souahite oter du tableau 
	 * doit etre positvie ou nulle.
	 */
  inline int removeData(const int & i) 
	{
		assert(i >= 0);

		int nextDegree = next(i);
		Datas.erase(i);
		return nextDegree;
	}

	/**
   * Methode qui renvoie la valeur de l'indicateur de
   * fin.
   */
  int rend(void) const
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
  inline int rnext(const int & i) const
	{
		assert(i >=0);
		
		typename _containorSparse::const_iterator it = Datas.find(i);
  
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
	 * @warning la position de l'�l�ment doit etre un eniter positif ou nul.
	 */
  inline void setData(const int & i , const Type &  value)
	{
		assert( i >= 0);

		if(value == 0) {
			Datas.erase(i);		
		} else {
			pair<typename _containorSparse::iterator,bool> insert_result = Datas.insert(pair<int,Type>(i,value));
			if(insert_result.second == false && insert_result.first == Datas.end()) {
				cerr << "Error : in void containorSparse::setData(const int & i , const Type & value)." << endl;
				cerr << "Error : something wrong occurs when inserting " << value << " for position " << i << "." <<  endl;
			} else {
				(insert_result.first)->second = value;
			}	
		}
	}

	/**
	 * M�thode pour mettre les valeurs d'un tableau � lidentique de
	 * celle s'un autre tableau.
	 *
	 * @param arraySparse le tableau dont on souhaite copier les valeurs.
	 *
	 * @see operator=(const containorSparse & arraySparse)
	 */
	inline void setDatas(const containorSparse & arraySparse)
	{
		copy(arraySparse);
	}
  
  /**
   * Methode pour l'affchage du polynome.
   *
	 * @param outStream le flux dans lequel on souhaite afficher le tableau.
	 */
	inline void write(ostream & outStream) const 
	{
		int i;

		outStream<< "[ ";
		if(empty()) {
			outStream<< "0";
		} else {

			for(i=begin() ; i != end() ; i = next(i)) {
				if( i != begin() ) {
					outStream<< " ; " ;
				}
				outStream << "( " << i << " , " << getData(i) << " )" ;
			}
		}
		outStream << " ]";
	}


  /**
   * Methode pour l'affchage du polynome.
   * Cette m�thode affiche le tableau comme un tableau normal avec des x
	 * la ou la m�thode getData renvoie 0.
	 *
	 * @param outStream le flux dans lequel on souhaite afficher le tableau.
	 */
	inline void writeAsContainor(ostream & outStream) const 
	{
		int i , nbrOfRows;
		Type data;

		nbrOfRows = getNbrOfRows();

		outStream << "[ ";
		
		for(i=0 ; i < nbrOfRows ; i++) {
			
			if(i>0) {
				outStream << " , "; 
			}
			
			data = getData(i);
			
			if(data == 0) {
				outStream << setw(8) << "x"; 
			} else {
				outStream << setw(8) << data;
			}
		
		}
		outStream << " ]";
	}

};

/**
 * Op�rateur pour �crire un containorSparse dans un flux.
 *
 * @param outStream le flux dans lequel on souhaite �crire le tableau.
 *
 * @param arraySparse le tableau qui doit �tre �crit.
 *
 * @return une r�f�rence vers le flux modifi�.
 */ 
template<typename Type>
inline ostream & operator<<(ostream & outStream , const containorSparse<Type> & arraySparse) 
{
	arraySparse.write(outStream);
	return outStream;
}

#endif
