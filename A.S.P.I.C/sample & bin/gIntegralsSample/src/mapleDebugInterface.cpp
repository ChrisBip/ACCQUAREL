#include "mapleDebugInterface.h"
///////////////////////////////////////////////////////
// M�thode pour acc�der au flux sortant.
//
// @Warning : Afin que cette m�thode n'arrete pas le programme
// il faut que la valeure renvoi� par la m�thode
// isOutFileStreamAvailable soit true.
///////////////////////////////////////////////////////
ofstream & mapleDebugInterface::getOutFileStream(void)
{
	assert(isOutFileStreamAvailable());
	return OutFileStream;
}

///////////////////////////////////////////////////////////
// M�thode pour cr�er des varibles mapple qui sont des
// tableaux avec des valeurs dedans.
////////////////////////////////////////////////////////////
void mapleDebugInterface::initMapleArray(const string & arrayName , const containor<double> & array)
{
	getOutFileStream() << "> " << arrayName <<  " := [";
	for(int i=0 ; i < array.getSizes()  ; i++) {
		if(i >0) {
			getOutFileStream() << " , ";
		}
		getOutFileStream() << setprecision(16) <<  array[i];
	}
	getOutFileStream() << "];" << endl;
}

//////////////////////////////////////////////////////////////////////
// Initialisation Mapple avec des fonctions de bases.
///////////////////////////////////////////////////////////////////////
string mapleDebugInterface::initMapleGaussianBasisFunction(const string & functionBaseName , const gaussianBasisFunction & phi)
{
	////////////////////////////////////////////////////////////
	// G�n�ration des tableaux de coefficient et d'exposants pour la fonction
	// de base.
	////////////////////////////////////////////////////////////
	getOutFileStream() << "> nbrOfContractions_" << functionBaseName << " := " << phi.getNbrOfContractions() << ":" << endl;
	initMapleArray("Coefficients_" + functionBaseName , phi.getCoefficients());
	initMapleArray("Exponents_" + functionBaseName , phi.getExponents());


	///////////////////////////////////////////////////////////////////////
	// Ecriture du centre des gaussiennes.
	///////////////////////////////////////////////////////////////////////
	getOutFileStream() << ">Center_x_" << functionBaseName << " := " << phi.getCenter()[0] << ";" << endl;	
	getOutFileStream() << ">Center_y_" << functionBaseName << " := " << phi.getCenter()[1] << ";" << endl;	
	getOutFileStream() << ">Center_z_" << functionBaseName << " := " << phi.getCenter()[2] << ";" << endl;	

	////////////////////////////////////////////////////////////////////////
	// Ecriture du degr�.
	////////////////////////////////////////////////////////////////////////
	getOutFileStream() << ">Degree_x_" << functionBaseName << " := " << phi.getMonomeDegree()[0] << ";" << endl;	
	getOutFileStream() << ">Degree_y_" << functionBaseName << " := " << phi.getMonomeDegree()[1] << ";" << endl;	
	getOutFileStream() << ">Degree_z_" << functionBaseName << " := " << phi.getMonomeDegree()[2] << ";" << endl;	

	////////////////////////////////////////////////////////////////////////
	// On �crit la proc�dure qui d�fini la premiere gaussienne.
	////////////////////////////////////////////////////////////////////////
	for(int i=1 ; i <= phi.getNbrOfContractions() ; i++) {
		getOutFileStream() << "> basisFunction_" << functionBaseName <<" [" << i << "] := proc (x,y,z)" << endl;
		getOutFileStream() << "> Coefficients_" << functionBaseName << "[" << i << "] * " << endl;
		getOutFileStream() << "> (x - Center_x_" << functionBaseName << ")^Degree_x_" << functionBaseName << "*" << endl;
		getOutFileStream() << "> (y - Center_y_" << functionBaseName << ")^Degree_y_" << functionBaseName << "*" << endl;
		getOutFileStream() << "> (z - Center_z_" << functionBaseName << ")^Degree_z_" << functionBaseName << "*" << endl;
		getOutFileStream() << "> exp( - Exponents_" << functionBaseName << "[" << i << "] * (" << endl;
		getOutFileStream() << "> (x - Center_x_" << functionBaseName << ")^2 +" << endl;
		getOutFileStream() << "> (y - Center_y_" << functionBaseName << ")^2 +" << endl;
		getOutFileStream() << "> (z - Center_z_" << functionBaseName << ")^2" << endl;
		getOutFileStream() << ">));" << endl;
		getOutFileStream() << "> end:" << endl;
		getOutFileStream() << "> basisFunction_" << functionBaseName << "[" << i << "](x,y,z);" << endl;	
	}

	return "basisFunction_" + functionBaseName;
}

///////////////////////////////////////////////////////////////////////
// M�thode pur cr�er une varible maple qui est un polynome.
///////////////////////////////////////////////////////////////////////
string mapleDebugInterface::initMapleGaussianPolynome3D(const string & gaussianPolyBaseName , const gaussianPolynome3D & poly)
{
	ipoint<3> degree;

	getOutFileStream() << "> " << gaussianPolyBaseName << "_Exponent := " << poly.getExponent() << ";" << endl;
	getOutFileStream() << "> " << gaussianPolyBaseName << "_Coefficient := " << poly.getCoefficient() << ";" << endl;
	
	initMaplePolynome(gaussianPolyBaseName + "_Poly" , poly);
	getOutFileStream() << "> " << gaussianPolyBaseName << " := ( " << gaussianPolyBaseName <<"_Poly )*" << endl;
	getOutFileStream() << "> " << gaussianPolyBaseName << "_Coefficient *"<< endl;
	getOutFileStream() << "> exp(-" << gaussianPolyBaseName << "_Exponent * ( "<< endl;
	getOutFileStream() << "> (x - " << gaussianPolyBaseName << "_Poly_Center_x)^2 +"<< endl;
	getOutFileStream() << "> (y - " << gaussianPolyBaseName << "_Poly_Center_y)^2 +"<< endl;
	getOutFileStream() << "> (z - " << gaussianPolyBaseName << "_Poly_Center_z)^2 "<< endl;
	getOutFileStream() << "> )); "<< endl;

	
	return gaussianPolyBaseName;
}

///////////////////////////////////////////////////////////////////////
// M�thode pur cr�er une varible maple qui est un polynome.
///////////////////////////////////////////////////////////////////////
string mapleDebugInterface::initMapleHermiteProjector(const string & polyBaseName , const hermiteProjector & poly)
{
	ipoint<3> degree;

	getOutFileStream() << "> " << polyBaseName << "_Exponent := " << poly.getExponent() << ";" << endl;
	getOutFileStream() << "> " << polyBaseName << "_Coefficient := " << setprecision(15) << poly.getCoefficient() << ";" << endl;
	getOutFileStream() << "> " << polyBaseName << "_Center_x := " << poly.getCenter()[0] << ";" << endl;
	getOutFileStream() << "> " << polyBaseName << "_Center_y := " << poly.getCenter()[1] << ";" << endl;
	getOutFileStream() << "> " << polyBaseName << "_Center_z := " << poly.getCenter()[2] << ";" << endl;
	
	
	getOutFileStream() << "> " << polyBaseName << " := ( " << endl;

		
	for(degree = poly.getHermiteFirst() ; degree != poly.getHermiteEnd() ; degree = poly.getHermiteNext(degree)) {		
		double coefficient = poly.getHermiteCoeffcient(degree);
		getOutFileStream() << "> " << (coefficient > 0 ? "+" : "" ) << coefficient 
			<< " * sqrt(" << polyBaseName << "_Exponent)^(" << degree.norme_1() << ")" << endl;
		
		getOutFileStream()	<< "> * HermiteH( " << degree[0] 
			<< " , sqrt(" << polyBaseName << "_Exponent) * (x - " << polyBaseName << "_Center_x))" << endl;
		getOutFileStream()	<< "> * HermiteH( " << degree[1] 
			<< " , sqrt(" << polyBaseName << "_Exponent) * (y - " << polyBaseName << "_Center_y))" << endl;
		getOutFileStream()	<< "> * HermiteH( " << degree[2] 
			<< " , sqrt(" << polyBaseName << "_Exponent) * (z - " << polyBaseName << "_Center_z))" << endl;
		}

	getOutFileStream() <<	"> )*" << endl;
	getOutFileStream() << "> " << polyBaseName << "_Coefficient *"<< endl;
	getOutFileStream() << "> exp(-" << polyBaseName << "_Exponent * ( "<< endl;
	getOutFileStream() << "> (x - " << polyBaseName << "_Center_x)^2 +"<< endl;
	getOutFileStream() << "> (y - " << polyBaseName << "_Center_y)^2 +"<< endl;
	getOutFileStream() << "> (z - " << polyBaseName << "_Center_z)^2 "<< endl;
	getOutFileStream() << "> )); "<< endl;

	
	return polyBaseName;
}

///////////////////////////////////////////////////////////////////////
// M�thode pur cr�er une varible maple qui est un polynome.
///////////////////////////////////////////////////////////////////////
string mapleDebugInterface::initMaplePolynome(const string & polyBaseName , const polynome3D & poly , const dpoint<3> & center)
{
	ipoint<3> degree;
	double coefficient;

	getOutFileStream() << "> " << polyBaseName << "_Center_x := " << center[0] << ";" << endl;
	getOutFileStream() << "> " << polyBaseName << "_Center_y := " << center[1] << ";" << endl;
	getOutFileStream() << "> " << polyBaseName << "_Center_z := " << center[2] << ";" << endl;

	getOutFileStream() << "> " << polyBaseName << " := " << endl;
	if(poly.empty()) {
		getOutFileStream() << "> 0" << endl;
	} else {
		for(degree = poly.begin() ; degree != poly.end() ; degree = poly.next(degree)) {		
			coefficient = poly.getData(degree);
			getOutFileStream() << "> " << (coefficient > 0 ? "+" : "" ) << coefficient 
				<< " * (x - " << polyBaseName << "_Center_x)^(" << degree[0] << ")"
				<< " * (y - " << polyBaseName << "_Center_y)^(" << degree[1] << ")"
				<< " * (z - " << polyBaseName << "_Center_z)^(" << degree[2] << ")" << endl;
		}
	}
	getOutFileStream() << ">;" << endl; 

	return polyBaseName;
}

///////////////////////////////////////////////////////////////////////
// M�thode pur cr�er une varible maple qui est un polynome.
///////////////////////////////////////////////////////////////////////
string mapleDebugInterface::initMaplePolynome(const string & polyBaseName , const polynome & poly , const double & center)
{
	int degree;
	double coefficient;

	getOutFileStream() << "> " << polyBaseName << "_Center := " << center << ":" << endl;
	getOutFileStream() << "> " << polyBaseName << " := " << endl;
	
	if(poly.begin() == poly.end()) {
		getOutFileStream() << "> 0" << endl;
	}
	else {
		for(degree = poly.begin() ; degree != poly.end() ; degree = poly.next(degree)) {		
			coefficient = poly.getData(degree);
			getOutFileStream() << "> " << (coefficient > 0 ? "+" : "" ) << setprecision(16) <<  coefficient 
				<< " * (x - " << polyBaseName << "_Center)^(" << degree << ")" << endl;
		}
	}
	getOutFileStream() << ">:" << endl; 

	return polyBaseName;
}

///////////////////////////////////////////////////////////////////////
// M�thode pur cr�er une varible maple qui est un polynome.
///////////////////////////////////////////////////////////////////////
string mapleDebugInterface::initMaplePolynome(const string & polyBaseName , const gaussianPolynome3D & poly)
{
	return initMaplePolynome(polyBaseName,poly.getPolynomeCoefficients(),poly.getCenter());
}

//////////////////////////////////////////////////////////////////////
// M�thode d'initialisation du flux sortant vers le fichier.
//
// Descrition : Cette m�thode ouvre le flux vers le fichier
// donn� dont le path est l'argument de la m�thode.
//
// Todo : il faudrait que v�rifier que le fichier n'existe pas d�ja,
// sinon on risque d'�craser des choses.
///////////////////////////////////////////////////////////////////////
void mapleDebugInterface::initOutFileStream(const string & filePath)
{
	////////////////////////////////////////////////
	// Lorsque le flux est ouvert on appelle 
	// la m�thode terminateOutFileStream pour faire
	// le m�nage.
	////////////////////////////////////////////////
	if(OutFileStream.is_open()) {
		terminateOutFileStream();
	}

	OutFileStream.open(filePath.c_str());

	///////////////////////////////////////////////////
	// On v�rifie que le flux � bien �t� ouvert.
	///////////////////////////////////////////////////
	if(OutFileStream.fail()) {
		cerr << "Error : in void mapleDebugInterface::initOutFileStream(const string & filePath)" << endl;
		cerr << "Error : open stream to file " << filePath << " failed" << endl;
		cerr << "Error : output stream will not be availlable" << endl;
		OutFileStream.close();
	}

}

///////////////////////////////////////////////////////////////
// M�thode pour savoir si le flux vers le fichier 
// est dans un �tat qui permette l'�criture de donn�es.
//
// Descriton : Pour que le flux soit OK il faut que le fichier 
// soit ouvert et que l'on ai pas de falgs a failed
// ou bad.
////////////////////////////////////////////////////////////////
bool mapleDebugInterface::isOutFileStreamAvailable(void) 
{
	if(OutFileStream.is_open() && OutFileStream.good()) {
		return true;
	}

	return false;
}

//////////////////////////////////////////////////////////////////
// M�thode pour terminer l'�criture.
//
// Cette m�thode permet de fermer le flux mais aussi de 
// d�sallouer des choses qui auraient pu etre allou�es durant
// l'ecriture.
//////////////////////////////////////////////////////////////////
void mapleDebugInterface::terminateOutFileStream(void)
{
	//////////////////////////////////////////////////////
	// On ferme le flux.
	//////////////////////////////////////////////////////
	if(OutFileStream.is_open()) {
		OutFileStream.close();
	}
}

