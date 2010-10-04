/* 
 * The optimisation library of the A.S.P.I.C. 
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
#include <assert.h>
#include "roothan.h"
#include <generalizedEigenSolver.h>

////////////////////////////////////////////////////////////////////////
// The default constructor of the class :
// this one does nothing at all.
/////////////////////////////////////////////////////////////////////////
roothan4RestrictedHartreeFock::roothan4RestrictedHartreeFock(void)
: NbrOfIterations(0) , NbrOfIterationsMax(10) , Max4Error(10E-5)
{
	;
}

////////////////////////////////////////////////////////////////////////
// The copy constructor of the class :
// - If this one is used we print the a message and abort the programm.
// This is because the copy constructor shall not be used for the 
// rotthan4RestrictedHartreeFock class.
/////////////////////////////////////////////////////////////////////////
roothan4RestrictedHartreeFock::roothan4RestrictedHartreeFock(const roothan4RestrictedHartreeFock & roothan4RHF)
{
	cerr << "Error : in class roothan4RestrictedHartreeFock::roothan4RestrictedHartreeFock(const roothan4RestrictedHartreeFock & roothan4RHF)" << endl;
	cerr << "Error : the copy constructor of the class shall not be used." << endl;
	cerr << "Error : aborting." << endl;
	exit(1);
}

////////////////////////////////////////////////////////////////////////
// The destructor of the class :
// this one does nothing at all.
/////////////////////////////////////////////////////////////////////////
roothan4RestrictedHartreeFock::~roothan4RestrictedHartreeFock(void)
{
	clear();
}

////////////////////////////////////////////////////////////////////////
// The clear method :
// This method just clears the density matrixes stored and resets the 
// number of iterations.
/////////////////////////////////////////////////////////////////////////
void roothan4RestrictedHartreeFock::clear(void)
{
	if(empty()){
		assert(getNbrOfIterations() == 0);
		return;
	}

	Densitys[0].clear();
	Densitys[1].clear();
	EigenValues[0].clear();
	EigenValues[1].clear();

	NbrOfIterations = 0;
}

//////////////////////////////////////////////////////////////////////////////
// This method test if the convergence as been reached.
//
// - TODO...
//
// - For the moment we will use a the very simple method , where we ensure that 
// the density matrixes are the same. In the future functunality will be increase.
//////////////////////////////////////////////////////////////////////////////
bool roothan4RestrictedHartreeFock::convergenceHasBeenReached(void) const
{
	int i , j , nbrOfRows;
	double errorMax;

	nbrOfRows = getNbrOfRows4Density();
	errorMax = 0;

	for(i=0 ; i < nbrOfRows ; i++) {
		for(j=i ; j < nbrOfRows ; j++) {
			errorMax = max(errorMax , fabs(getDensity(0)(i,j) - getDensity(1)(i,j)));
		}
	}

	if(errorMax < getMax4Error()) {
		return true;
	} else {
		return false;
	}
}

////////////////////////////////////////////////////////////////////////
// The empty method :
// If there are some matrix that are allocated then we return true
// and if the matrixes are empty we return false.
/////////////////////////////////////////////////////////////////////////
bool roothan4RestrictedHartreeFock::empty(void) const
{
	return getDensity().empty();
}

////////////////////////////////////////////////////////////////////////
// The the get density method (constant version):
// - For the roothan algorithm we switch between to density matrixes. To 
// do so the two matrixes are stored, and this method enable access to those
// matrixes. When the parameter item is odd the method returns the fisrt
// matrix stored else the second.
/////////////////////////////////////////////////////////////////////////
const  matrixSymetric & roothan4RestrictedHartreeFock::getDensity(const int & item) const
{
	if(item % 2) {
		return Densitys[1];
	} else {
		return Densitys[0];
	}
}

////////////////////////////////////////////////////////////////////////
// The the get density method :
// - For the roothan algorithm we switch between to density matrixes. To 
// do so the two matrixes are stored, and this method enable access to those
// matrixes. When the parameter item is odd the method returns the fisrt
// matrix stored else the second.
/////////////////////////////////////////////////////////////////////////
 const matrixSymetric & roothan4RestrictedHartreeFock::getDensity(void) const
{
	return getDensity(getNbrOfIterations());
}

////////////////////////////////////////////////////////////////////////
// The the set eigenvalues method :
/////////////////////////////////////////////////////////////////////////
const containor<double> & roothan4RestrictedHartreeFock::getEigenValues(const int & item) const
{
	if(item % 2){
		return EigenValues[1];
	} else {
		return EigenValues[0];
	}
}

////////////////////////////////////////////////////////////////////////
// The the set eigenvalues method :
/////////////////////////////////////////////////////////////////////////
const containor<double> & roothan4RestrictedHartreeFock::getEigenValues(void) const
{
	return getEigenValues(getNbrOfIterations());
}

////////////////////////////////////////////////////////////////////////
// This is the algorithm ...
////////////////////////////////////////////////////////////////////////
const matrixSymetric & roothan4RestrictedHartreeFock::getGroundStateDensity(const restrictedHartreeFock & rhfState , const bool & log) 
{
 
	//////////////////////////////////////////////////////////
	// First step is to do the initialisation of the algorithm
	//
	// - We set the sizes of the density matrixes.
	// - We copy the current density matrix in the initial density.
	///////////////////////////////////////////////////////////
	setNbrOfRows4Density(rhfState.getNbrOfBasisFunctions());
	setDensity(0,rhfState.getDensity());

	if(log) {
		cout << " -----------------------------------------------------------------------------------------" << endl;
		cout << " -----------------------------------------------------------------------------------------" << endl;
		cout << " - Initialisation of the Roothaan algorithm." << endl;
		cout << " - Initial Energy: " << rhfState.getEnergy() << endl;
		cout << " -----------------------------------------------------------------------------------------" << endl;
	}
	////////////////////////////////////////////////////////////
	// This is the loop of the algorithm.
	////////////////////////////////////////////////////////////
	generalizedEigenSolver eigenSolver;

	for(NbrOfIterations=0 ; NbrOfIterations < getNbrOfIterationsMax() ; NbrOfIterations++) {

		//////////////////////////////////////////////////
		// We compute the next density from the one that 
		// we already know
		//////////////////////////////////////////////////
		eigenSolver.solve(rhfState.getFockMatrix(getDensity()) , rhfState.getOverlap());		
		setDensity(NbrOfIterations+1 , eigenSolver.getEigenVectors() , rhfState.getNbrOfElectrons() / 2);
		setEigenValues(NbrOfIterations , eigenSolver.getEigenValues());

		if(log) {
			cout << " -----------------------------------------------------------------------------------------" << endl;
			cout << " - Iteration  : " << NbrOfIterations << "." << endl;
			cout << " - Eigenvalues: " <<  eigenSolver.getEigenValues() << endl;
			for(int k=0 ; k < getNbrOfRows4Density() ; k++) {
				cout << " - Eigenvector: " <<  eigenSolver.getEigenVector(k) << endl;
				}
			cout << " - Energy     : " <<  rhfState.getEnergy(getDensity()) << endl;
			cout << " -----------------------------------------------------------------------------------------" << endl;
		}
		
		///////////////////////////////////////////////////
		// This is the test to know if the convergence has
		// been reached.
		///////////////////////////////////////////////////
		if(convergenceHasBeenReached()) {
			break;
		}
	}

	/////////////////////////////////////////////////////////
	// At last we return the density matrix for convergence.
	/////////////////////////////////////////////////////////
	return getDensity();
}

////////////////////////////////////////////////////////////////////////
// The get method for the max error:
// - this method just returns the number of iterations that have been performed
// by the algorithm.
/////////////////////////////////////////////////////////////////////////
const double & roothan4RestrictedHartreeFock::getMax4Error(void) const
{
	return Max4Error;
}

////////////////////////////////////////////////////////////////////////
// The the get number of iterations method :
// - this method just returns the number of iterations that have been performed
// by the algorithm.
/////////////////////////////////////////////////////////////////////////
 const int & roothan4RestrictedHartreeFock::getNbrOfIterations(void) const
{
	return NbrOfIterations;
}

////////////////////////////////////////////////////////////////////////
// The the get number of iterations max method :
// - this method just returns the number of iterations max that shall be done during the
// roothan loop.
/////////////////////////////////////////////////////////////////////////
 const int & roothan4RestrictedHartreeFock::getNbrOfIterationsMax(void) const
{
	return NbrOfIterationsMax;
}

////////////////////////////////////////////////////////////////////////
// The the get number of rows for density method :
// - This method just returns the size of the density matrix used by the
// algorithm.
/////////////////////////////////////////////////////////////////////////
const int & roothan4RestrictedHartreeFock::getNbrOfRows4Density(void) const
{
	return getDensity().getNbrOfRows();
}

////////////////////////////////////////////////////////////////////////
// The the set density method :
/////////////////////////////////////////////////////////////////////////
void roothan4RestrictedHartreeFock::setDensity(const int & item , const matrixSymetric & density)
{
	assert(density.getNbrOfRows() == getNbrOfRows4Density());

	if(item % 2) {
		Densitys[1] = density;
	} else {
		Densitys[0] = density;
	}
}

////////////////////////////////////////////////////////////////////////
// The the set density method :
/////////////////////////////////////////////////////////////////////////
void roothan4RestrictedHartreeFock::setDensity(const int & item , const containor<vector> & eigenVectors , const int & nbrOfColumns)
{

	assert(eigenVectors.getNbrOfRows() > 0);
	assert(eigenVectors[0].getNbrOfRows() == getNbrOfRows4Density());
	assert(nbrOfColumns > 0);

	int i , j , k , nbrOfRows;
	double value;

	nbrOfRows = eigenVectors[0].getNbrOfRows();

	for(i = 0 ; i < nbrOfRows ; i++) {
		for(j = i ; j < nbrOfRows ; j++) {
		
			value = 0;

			for(k = 0 ; k < nbrOfColumns ; k++) {
				value += eigenVectors[k][i] * eigenVectors[k][j];
			}  
		
			Densitys[(item % 2)](i,j) = value;
		}
	} 

}

////////////////////////////////////////////////////////////////////////
// The the set eigenvalues method :
/////////////////////////////////////////////////////////////////////////
void roothan4RestrictedHartreeFock::setEigenValues(const int & item , const containor<double> & eigenValues)
{
	assert(eigenValues.getNbrOfRows() == getNbrOfRows4Density());

	if(item % 2){
		EigenValues[1] = eigenValues;
	} else {
		EigenValues[0] = eigenValues;
	}
}
////////////////////////////////////////////////////////////////////////
// The get method for the max error:
// - this method just returns the number of iterations that have been performed
// by the algorithm.
/////////////////////////////////////////////////////////////////////////
void roothan4RestrictedHartreeFock::setMax4Error(const double &  max4Error)
{
	assert(max4Error >= 0);
	Max4Error = max4Error;
}

////////////////////////////////////////////////////////////////////////
// The the set number of rows for density method :
// - This method just allocs the size of the density matrix used by the
// algorithm.
/////////////////////////////////////////////////////////////////////////
void roothan4RestrictedHartreeFock::setNbrOfIterationsMax(const int & nbrOfIterationsMax)
{
	assert(nbrOfIterationsMax > 0);
	NbrOfIterationsMax = nbrOfIterationsMax;
}
////////////////////////////////////////////////////////////////////////
// The the set number of rows for density method :
// - This method just allocs the size of the density matrix used by the
// algorithm.
/////////////////////////////////////////////////////////////////////////
void roothan4RestrictedHartreeFock::setNbrOfRows4Density(const int & nbrOfRows)
{
	assert(nbrOfRows > 0);

	if(getNbrOfRows4Density() == nbrOfRows) {
		return;
	}

	Densitys[0].setMatrixSize(nbrOfRows);
	Densitys[1].setMatrixSize(nbrOfRows);
	EigenValues[0].setSizes(nbrOfRows);
	EigenValues[1].setSizes(nbrOfRows);
}
