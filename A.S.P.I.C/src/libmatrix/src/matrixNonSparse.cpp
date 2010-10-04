/* 
* The martix library of the A.S.P.I.C. 
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
#include "matrixNonSparse.h"
#include <cstdlib>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Default constructor.
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
matrixNonSparse::matrixNonSparse(void)
	: matrix() , Storage(NULL) , StorageSize(0)
{
		;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Destructor.
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
matrixNonSparse::~matrixNonSparse(void)
{
		clear();
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Method to add two matrixes.
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void matrixNonSparse::add(const matrixNonSparse & matrixA)
{
	// first step is to perform sizes matching verifications.
	assert(matrixA.getNbrOfRows() == getNbrOfRows());
	assert(matrixA.getNbrOfColumns() == getNbrOfColumns());
	assert(matrixA.getMatrixType() == getMatrixType());

	int item , storageSize;

	storageSize = getStorageSize();

	for(item = 0 ; item < storageSize ; item++) {
		getStorage(item) += matrixA.getStorage(item);
	}

}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Method to add two symetric matrixes.
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void matrixNonSparse::add(const matrixNonSparse & matrixA , const matrixNonSparse & matrixB)
{
	assert(matrixA.getNbrOfRows() == matrixB.getNbrOfRows());
	assert(matrixA.getNbrOfColumns() == matrixB.getNbrOfColumns());
	assert(matrixA.getMatrixType() == matrixB.getMatrixType());
	assert(getMatrixType() == matrixA.getMatrixType());

	copy(matrixA);
	add(matrixB);
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Method for the allocation of the storage memory.
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void matrixNonSparse::allocStorage(const int & storageSize)
{
	if(getStorageSize() > 0) {
		freeStorage();
	}
	
	if(storageSize <= 0) {
		return;
	}
	
	Storage = new double [storageSize];
	StorageSize = storageSize;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// The CLEAR Method.
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void matrixNonSparse::clear(void)
{
	matrix::clear();
	freeStorage();
}	

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// The COPY Method.
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void matrixNonSparse::copy(const matrixNonSparse & m)
{
	// The following exception may occur :
	//
	// one trys to copy a matrix FULL in a SYMETRIC one.
	// as this point this may not be very smart as the storage
	// and access method for those types of objects are very different
	//
	// to ensure that shall not appen, we olny copy matrixes from the same
	// types.
	if(m.getMatrixType() != getMatrixType()) {
		cerr << "Error : in void matrixNonSparse::copy(const matrixNonSparse & m)" << endl;
		cerr << "Error : unable to copy a " << m.getMatrixType() << " matrix in a " << getMatrixType() << " matrix " << endl;
		cerr << "Error : assertion failed." << endl;
		exit(1);
	}

	if(m.empty()) {
		clear();
		return;
	}
		
	// We copy informations about the matrix.
	matrix::copy(m);
	
	// We copy the storage.
	setStorageSize(m.getStorageSize());
	for(int i=0 ; i < getStorageSize() ; i++) {
		setStorage(i , m.getStorage(i));
	}
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Method to divide a matrix and a scalar value
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void matrixNonSparse::divide(const double & scalar)
{
	assert(scalar != 0);

	int item , storageSize;

	storageSize = getStorageSize();
	for(item = 0 ; item < storageSize ; item++) {
		getStorage(item) /= scalar;
	}

}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Method to multiply a matrix and a scalar value
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void matrixNonSparse::divide(const matrixNonSparse & matrixA , const double & scalar)
{
	assert(matrixA.getMatrixType() == getMatrixType());
	assert(scalar != 0);

	copy(matrixA);
	divide(scalar);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Method for the desallocation of the storage memory.
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void matrixNonSparse::freeStorage(void)
{
	if(getStorageSize() == 0) {
		return;
	}
		
	delete [] Storage;
	Storage = NULL;
	StorageSize = 0;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Method GET for the item element of the storage array.
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const double & matrixNonSparse::getCoefficient(const int & row , const int & column) const
{
	assert(row >= 0);
	assert(row < getNbrOfRows());

	assert(column >= 0);
	assert(column < getNbrOfColumns());

	return getStorage(hash(row , column));
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Method GET for the item element of the storage array.
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
double & matrixNonSparse::getCoefficient(const int & row , const int & column)
{
	assert(row >= 0);
	assert(row < getNbrOfRows());
	
	assert(column >= 0);
	assert(column < getNbrOfColumns());
	
	return getStorage(hash(row , column));
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Method GET for the pointer of the Array.
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const double * matrixNonSparse::getStorage(void) const
{
	return Storage;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Method GET for the item element of the storage array.
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const double & matrixNonSparse::getStorage(const int & item) const
{
	assert(item >= 0);
	assert(item < getStorageSize());
	
	return Storage[item];
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Method GET for the item element of the storage array.
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
double & matrixNonSparse::getStorage(const int & item)
{
	assert(item >= 0);
	assert(item < getStorageSize());
	
	return Storage[item];
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Method GET for the size of the storage array.
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const int & matrixNonSparse::getStorageSize(void) const
{	
	return StorageSize;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Method to multiply a matrix and a scalar value
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void matrixNonSparse::multiply(const double & scalar)
{
	int item , storageSize;

	storageSize = getStorageSize();
	
	for(item = 0 ; item < storageSize ; item++) {
		getStorage(item) *= scalar;
	}
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Method to multiply a matrix and a scalar value
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void matrixNonSparse::multiply(const matrixNonSparse & matrixA , const double & scalar)
{
	assert(matrixA.getMatrixType() == getMatrixType());

	copy(matrixA);
	multiply(scalar);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Operator to access elements of the matrix.
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const double & matrixNonSparse::operator[](const int & item) const
{	
	assert(item >= 0);
	assert(item < getStorageSize());
		
	return getStorage(item);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Operator to access elements of the matrix.
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
double & matrixNonSparse::operator[](const int & item)
{	
	assert(item >= 0);
	assert(item < getStorageSize());
		
	return getStorage(item);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Operator to access elements of the matrix.
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const double & matrixNonSparse::operator()(const int & row , const int & column) const
{	
	assert(row >= 0);
	assert(row < getNbrOfRows());
	
	assert(column >= 0);
	assert(column < getNbrOfColumns());
	
	return getCoefficient(row,column);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Operator to access elements of the matrix.
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
double & matrixNonSparse::operator()(const int & row , const int & column)
{	
	assert(row >= 0);
	assert(row < getNbrOfRows());
	
	assert(column >= 0);
	assert(column < getNbrOfColumns());
	
	return getCoefficient(row,column);
}


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Method SET for the element row x column of the matrix.
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void matrixNonSparse::setCoefficient(const int & row , const int & column , const double & value)
{
	assert(row >= 0);
	assert(row < getNbrOfRows());
	
	assert(column >= 0);
	assert(column < getNbrOfColumns());
	
	return setStorage(hash(row , column) , value);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Method SET for the element row x column of the matrix.
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void matrixNonSparse::setCoefficients(const double & value)
{
	int i , storageSize;
	
	storageSize = getStorageSize();
	for(i=0 ; i < storageSize ; i++) {
		setStorage(i,value);
	}
	
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Method SET for the matrix size.
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void matrixNonSparse::setMatrixSize(const int & nbrOfRows , const int & nbrOfColumns)
{
	setNbrOfColumns(nbrOfColumns);
	setNbrOfRows(nbrOfRows);
	
	setStorageSize(computeStorageSize());
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Method SET for the item element of the storage array.
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void matrixNonSparse::setStorage(const int & item , const double & value)
{
	assert(item >= 0);
	assert(item < getStorageSize());
	
	Storage[item] = value;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Method SET for the storage size.
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void matrixNonSparse::setStorageSize(const int & storageSize)
{
	assert(storageSize > 0);
	
	if(storageSize == getStorageSize() ) {
		return;
	}
	
	if(getStorageSize() > 0) {
		freeStorage();
	}

	allocStorage(storageSize);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Method to soustract two matrixes.
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void matrixNonSparse::soustract(const matrixNonSparse & matrixA)
{
	// first step is to perform sizes matching verifications.
	assert(matrixA.getNbrOfRows() == getNbrOfRows());
	assert(matrixA.getNbrOfColumns() == getNbrOfColumns());
	assert(matrixA.getMatrixType() == getMatrixType());

	int item , storageSize;

	storageSize = getStorageSize();

	for(item = 0 ; item < storageSize ; item++) {
		getStorage(item) -= matrixA.getStorage(item);
	}
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Method to soustract two symetric matrixes.
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void matrixNonSparse::soustract(const matrixNonSparse & matrixA , const matrixNonSparse & matrixB)
{
	assert(matrixA.getNbrOfRows() == matrixB.getNbrOfRows());
	assert(matrixA.getNbrOfColumns() == matrixB.getNbrOfColumns());
	assert(matrixA.getMatrixType() == matrixB.getMatrixType());
	assert(getMatrixType() == matrixA.getMatrixType());

	copy(matrixA);
	soustract(matrixB);
}





