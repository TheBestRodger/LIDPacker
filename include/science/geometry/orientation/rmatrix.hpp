//////////////////////////////////////////////////////////////////////////////
// rmatrix.hpp
// Copyright (c) 2020 by Alexander Kuslya <kuslya.alexander@gmail.com>


#ifndef SCIENCE_RMATRIX_HPP_INCLUDED__
#define SCIENCE_RMATRIX_HPP_INCLUDED__


#include <science/core/type.hpp>
#include <science/geometry/vector/predefine.hpp>
#include <science/geometry/orientation/predefine.hpp>

#include <ostream>



//////////////////////////////////////////////////////////////////////////
namespace science {

//////////////////////////////////////////////////////////////////////////
namespace d3 {


/*  Матрица преобразования (направляющих косинусов) между системами координат */
//////////////////////////////////////////////////////////////////////////////
class RMatrix
{
	sreal_t elem[3][3];

public:
	RMatrix();

	RMatrix(
		  sreal_t const a11
		, sreal_t const a12
		, sreal_t const a13
		, sreal_t const a21
		, sreal_t const a22
		, sreal_t const a23
		, sreal_t const a31
		, sreal_t const a32
		, sreal_t const a33
	);

	/* Элементы в массиве должны идти построчно */
	explicit RMatrix(sreal_t const arr[9]);

	explicit RMatrix(sreal_t const arr[3][3]);

	RMatrix(RMatrix const& matrix);

	RMatrix& operator = (RMatrix const& matrix);

	sreal_t const* operator[] (unsigned const i) const;

	sreal_t* operator[] (unsigned const i);

	RMatrix& operator - ();

	RMatrix& operator += (RMatrix const& m);

	RMatrix& operator -= (RMatrix const& m);

	RMatrix& operator *= (sreal_t const& c);

	RMatrix& operator /= (sreal_t const& c);

	RMatrix& assign(sreal_t const arr[9]);

	RMatrix& assign(sreal_t const arr[3][3]);

	static RMatrix const zero_matrix();

	static RMatrix const unit_matrix();

	static RMatrix const exchange_matrix();

	static RMatrix const allones_matrix();

	static RMatrix const utriangular_matrix();

	static RMatrix const ltriangular_matrix();
};



/* Вспомогательные операторы и функции */

/* Получение транспонированной матрицы */
//////////////////////////////////////////////////////////////////////////////
RMatrix const transposed(RMatrix const& m);


/* Транспонирование матрицы */
//////////////////////////////////////////////////////////////////////////////
RMatrix& transpose(RMatrix& m);


//////////////////////////////////////////////////////////////////////////////
sreal_t const determinant(RMatrix const& m);


//////////////////////////////////////////////////////////////////////////////
RMatrix const operator * (
	  RMatrix const& m1
	, RMatrix const& m2
	);


//////////////////////////////////////////////////////////////////////////////
RVector const operator * (
	  RMatrix const& m
	, RVector const& v
	);


//////////////////////////////////////////////////////////////////////////////
SVector const operator * (
	  RMatrix const& m
	, SVector const& v
	);


//////////////////////////////////////////////////////////////////////////////
RMatrix const operator * (
	  RMatrix const& m
	, sreal_t const& c
	);


//////////////////////////////////////////////////////////////////////////////
RMatrix const operator / (
	  RMatrix const& m
	, sreal_t const& v
	);


//////////////////////////////////////////////////////////////////////////////
RMatrix const operator + (
	  RMatrix const& m1
	, RMatrix const& m2
	);


//////////////////////////////////////////////////////////////////////////////
RMatrix const operator - (
	  RMatrix const& m1
	, RMatrix const& m2
	);


//////////////////////////////////////////////////////////////////////////////
template <
	  typename CharT
	, typename TraitsT
>
std::basic_ostream<CharT, TraitsT>& operator << (
	std::basic_ostream<CharT, TraitsT>& bos
	, RMatrix const& m
	)
{
	bos << '['
		<< '[' << m[0][0] << ", " << m[0][1] << ", " << m[0][2] << "], "
		<< '[' << m[1][0] << ", " << m[1][1] << ", " << m[1][2] << "], "
		<< '[' << m[2][0] << ", " << m[2][1] << ", " << m[2][2] << ']'
		<< ']';

	return bos;
}


//////////////////////////////////////////////////////////////////////////////
template <
	typename CharT
	, typename TraitsT
>
std::basic_istream<CharT, TraitsT>& operator >> (
	std::basic_istream<CharT, TraitsT>& is
	, RMatrix& m
	)
{
	is >> m[0][0] >> m[0][1] >> m[0][2]
		>> m[1][0] >> m[1][1] >> m[1][2]
		>> m[2][0] >> m[2][1] >> m[2][2];

	return is;
}


/* Функция преобразования матрицы направляющих косинусов в углы Эйлера */
//////////////////////////////////////////////////////////////////////////////
Euler const to_euler(RMatrix const& m);


/* Функция преобразования матрицы направляющих косинусов в кватернион */
//////////////////////////////////////////////////////////////////////////////
//Quaternion const to_quaternion(RMatrix const& m);

} /* namespace d3 */

} /* namespace science */





#endif  SCIENCE_RMATRIX_HPP_INCLUDED__