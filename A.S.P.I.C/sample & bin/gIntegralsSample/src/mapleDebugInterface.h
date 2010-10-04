#ifndef _MAPLE_DEBUG_INTERFACE_
#define _MAPLE_DEBUG_INTERFACE_

#include <fstream>
#include <gaussianBasisFunction.h>
#include <hermiteProjector.h>
#include <polynome.h>
#include <iostream>
using namespace std;

///////////////////////////////////////////////////////////////////////////
// G�n�ration d'un fichier maple pour la v�rification des calculs.
////////////////////////////////////////////////////////////////////////////
class mapleDebugInterface {

private:
	
	////////////////////////////////////
	// Le flux dans lequel on souhaite
	// �crire les donn�es Mapple.
	////////////////////////////////////
	ofstream OutFileStream;

protected:
	
	///////////////////////////////////////////////////////
	// M�thode pour savoir si le flux sortant est 
	// overt et si l'on peut �crire dedans.
	////////////////////////////////////////////////////////
	bool isOutFileStreamAvailable(void);

public:

	/////////////////////////////////////////////////////
	// M�thode d'acc�s au flux sortant.
	/////////////////////////////////////////////////////
	ofstream & getOutFileStream(void);

	////////////////////////////////////////////////////////
	// Cette m�thode � pour but de construire 
	// des tableaux avec des valeurs dedans dans un fichier
	// mapple.
	/////////////////////////////////////////////////////////
	void initMapleArray(const string & arrayName , const containor<double> & array);

	//////////////////////////////////////////////////////////
	// Cette m�thode permet d'�crire dans un fichier Mapple 
	// un ensemblre de proc�dures qui sont les fonctions de 
	// base gaussiennes.
	///////////////////////////////////////////////////////////
	string initMapleGaussianBasisFunction(const string & functionBaseName , const gaussianBasisFunction & phi);
	
	///////////////////////////////////////////////////////////
	// M�thode qui cr�e une proc�dure Maple avec un polynome
	// dedans.
	////////////////////////////////////////////////////////////
	string initMapleGaussianPolynome3D(const string & polyBaseName , const gaussianPolynome3D & poly);

	///////////////////////////////////////////////////////////
	// M�thode qui cr�e une proc�dure Maple avec un polynome
	// dedans.
	////////////////////////////////////////////////////////////
	string initMapleHermiteProjector(const string & polyBaseName , const hermiteProjector & poly);

	///////////////////////////////////////////////////////////
	// M�thode qui cr�e une proc�dure Maple avec un polynome
	// dedans.
	////////////////////////////////////////////////////////////
	string initMaplePolynome(const string & polyBaseName , const gaussianPolynome3D & poly);

	///////////////////////////////////////////////////////////
	// M�thode qui cr�e une proc�dure Maple avec un polynome
	// dedans.
	////////////////////////////////////////////////////////////
	string initMaplePolynome(const string & polyBaseName , const polynome & poly , const double & center =0);

	///////////////////////////////////////////////////////////
	// M�thode qui cr�e une proc�dure Maple avec un polynome
	// dedans.
	////////////////////////////////////////////////////////////
	string initMaplePolynome(const string & polyBaseName , const polynome3D & poly , const dpoint<3> & center = dpoint<3>(0));

	/////////////////////////////////////////////////////
	// M�thode qui construit le flux de donn�es sortant
	// vers le fichier dont le path est la valeur de 
	// la variable filePath.
	//
	// Cette m�thode s'assure que le flux est bien ferm�
	// d'ouvrir un nouveau flux.
	/////////////////////////////////////////////////////
	void initOutFileStream(const string & filePath);
	
	/////////////////////////////////////////////////////
	// M�thode qui construit le flux de donn�es sortant
	// vers le fichier dont le path est la valeur de 
	// la variable filePath.
	//
	// Cette m�thode s'assure que le flux est bien ferm�
	// d'ouvrir un nouveau flux.
	/////////////////////////////////////////////////////
	void terminateOutFileStream(void);
};

#endif

