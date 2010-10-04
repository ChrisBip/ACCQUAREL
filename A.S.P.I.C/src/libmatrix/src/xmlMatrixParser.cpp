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
#include "xmlMatrixParser.h"

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Constructor.
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
xmlMatrixParser::xmlMatrixParser(void)
: xmlParser()
{
	;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Constructor.
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
xmlMatrixParser::xmlMatrixParser(DOMElement * rootElement)
: xmlParser(rootElement)
{
	;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Destructor.
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
xmlMatrixParser::~xmlMatrixParser(void)
{
	;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// GET a coefficient.
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
matrixCoefficientData xmlMatrixParser::getCoefficient(int item) const
{
	assert(item >=0);
	assert(item < getNbrOfCoefficients());
	
	
	DOMElement * coefficientElement =(DOMElement *) getElementsByTagName(getCoefficientTagName())->item(item);
	matrixCoefficientData coefficient;
	
	
	if(coefficientElement == NULL) {
		
		coefficient.Row = -1;
		coefficient.Column = -1;
		coefficient.Value = 0;
	
		return coefficient;
	}
	
	coefficient.Row = getNodeIntegerValue(getElementByTagName(coefficientElement , getCoefficientRowTagName()));
	coefficient.Column = getNodeIntegerValue(getElementByTagName(coefficientElement , getCoefficientColumnTagName()));
	coefficient.Value = getNodeDoubleValue(getElementByTagName(coefficientElement , getCoefficientValueTagName()));
	
	assert( coefficient.Row >= 0 );
	assert( coefficient.Row < getNbrOfRows() );

	assert( coefficient.Column >= 0 );
	assert( coefficient.Column < getNbrOfColumns() );

	return coefficient;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// GET for the coefficient tag name.
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
double xmlMatrixParser::getCoefficientsDefaultValue(void) const
{
	DOMNode * coefficientsDefaultValueNode = getElementByTagName(getCoefficientsDefaultValueTagName());

	if(coefficientsDefaultValueNode == NULL) 
		return 0;
	else 
		return getNodeDoubleValue(coefficientsDefaultValueNode);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// GET for the coefficient tag name.
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const string xmlMatrixParser::getCoefficientsDefaultValueTagName(void)
{
	return "CoefficientsDefaultValue";
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// GET for the coefficient tag name.
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const string xmlMatrixParser::getCoefficientTagName(void)
{
	return "Coefficient";
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// GET for the column tag name.
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const string xmlMatrixParser::getCoefficientColumnTagName(void)
{
	return "Column";
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// GET for the matrix type.
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
matrixSymetric xmlMatrixParser::getMatrixSymetricFull(void) const
{
	assert(getMatrixType() == matrix::SYMETRIC_FULL);
	
	assert(getNbrOfRows() == getNbrOfColumns());
	
	int i;
	matrixCoefficientData coef;
	matrixSymetric m;

	m.setMatrixSize(getNbrOfRows(),getNbrOfColumns());
	m.setCoefficients(getCoefficientsDefaultValue());
	
	for(i=0 ;  i<getNbrOfCoefficients() ; i++) {
		coef = getCoefficient(i);
		m.setCoefficient(coef.Row , coef.Column, coef.Value);	
	}	

	return m;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// GET for the matrix type.
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
matrixFull xmlMatrixParser::getMatrixFull(void) const
{
	assert(getMatrixType() == matrix::FULL);
	
	int i;
	matrixCoefficientData coef;
	matrixFull m;
	
	
	m.setMatrixSize(getNbrOfRows(),getNbrOfColumns());
	m.setCoefficients(getCoefficientsDefaultValue());
	
	for(i=0 ;  i<getNbrOfCoefficients() ; i++) {
		coef = getCoefficient(i);
		m.setCoefficient(coef.Row , coef.Column, coef.Value);	
	}	
	
	return m;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// GET for the matrix type.
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
matrix::matrixType xmlMatrixParser::getMatrixType(void) const
{
	return matrix::string2MatrixType(getMatrixTypeString());
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// GET for the matrix type string.
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
string xmlMatrixParser::getMatrixTypeString(void) const
{	
	return getAttributeValue(getMatrixTypeAttributeName());
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// GET for the matrix type tag name.
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const string xmlMatrixParser::getMatrixTypeAttributeName(void)
{
	return "MatrixType";
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// GET for the number of coefficients.
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int xmlMatrixParser::getNbrOfCoefficients(void) const
{
	return getNbrOfElementsWithTagName(getCoefficientTagName());
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// GET for the number of columns.
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int xmlMatrixParser::getNbrOfColumns(void) const
{
	return getNodeIntegerValue(getElementByTagName(getNbrOfColumnsTagName()));
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// GET for the number of columns tag name.
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const string xmlMatrixParser::getNbrOfColumnsTagName(void)
{
	return "NbrOfColumns";
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// GET for the number of rows.
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int xmlMatrixParser::getNbrOfRows(void) const
{
	return getNodeIntegerValue(getElementByTagName(getNbrOfRowsTagName()));
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// GET for the number of rows tag name.
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const string xmlMatrixParser::getNbrOfRowsTagName(void)
{
	return "NbrOfRows";
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// GET for the row tag name.
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const string xmlMatrixParser::getCoefficientRowTagName(void)
{
	return "Row";
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// GET for the row tag name.
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const string xmlMatrixParser::getCoefficientValueTagName(void)
{
	return "Value";
}

