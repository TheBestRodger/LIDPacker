//////////////////////////////////////////////////////////////////////////////
// quaternion.hpp
// Copyright (c) 2020 by Alexander Kuslya <kuslya.alexander@gmail.com>


#ifndef SCIENCE_QUATERNION_HPP_INCLUDED__
#define SCIENCE_QUATERNION_HPP_INCLUDED__


#include <science/core/type.hpp>
#include <science/geometry/vector/predefine.hpp>
#include <science/geometry/orientation/predefine.hpp>

#include <ostream>


//////////////////////////////////////////////////////////////////////////
namespace science {

//////////////////////////////////////////////////////////////////////////
namespace d3 {


/* Модель кватерниона */
//////////////////////////////////////////////////////////////////////////////
struct Quaternion
{
	sreal_t l0;
	sreal_t l1;
	sreal_t l2;
	sreal_t l3;

	Quaternion();

	Quaternion(
		  sreal_t const l0
		, sreal_t const l1
		, sreal_t const l2
		, sreal_t const l3
	);

	explicit Quaternion(sreal_t const ptr[4]);

	Quaternion(
		  sreal_t const scalar
		, RVector const& vector_
	);

	sreal_t const operator[] (unsigned const i) const;

	sreal_t& operator[] (unsigned const i);

	Quaternion& operator - ();

	Quaternion& operator += (Quaternion const& q);

	Quaternion& operator -= (Quaternion const& q);

	Quaternion& operator *= (sreal_t const c);

	Quaternion& operator /= (sreal_t const c);

	Quaternion& assign(
		  sreal_t const l0
		, sreal_t const l1
		, sreal_t const l2
		, sreal_t const l3
	);

	Quaternion& assign(sreal_t const ptr[4]);

	RVector const vector() const;

	void vector(RVector const& v);
};


/* Вспомогательные операторы и функции */

//////////////////////////////////////////////////////////////////////////////
Quaternion const conjugate(Quaternion const& q);


/////////////////////////////////////////////////////////////////////
Quaternion& normalize(Quaternion& q);


/////////////////////////////////////////////////////////////////////
sreal_t const norm(Quaternion const& q);


/////////////////////////////////////////////////////////////////////
sreal_t const module(Quaternion const& q);


/////////////////////////////////////////////////////////////////////
Quaternion const cross_prod(
	  Quaternion const& q1
	, Quaternion const& q2
);


/////////////////////////////////////////////////////////////////////
sreal_t const scalar_prod(
	  Quaternion const& q1
	, Quaternion const& q2
);


/////////////////////////////////////////////////////////////////////
Quaternion const operator + (
	  Quaternion const& q1
	, Quaternion const& q2
	);


/////////////////////////////////////////////////////////////////////
Quaternion const operator - (
	  Quaternion const& q1
	, Quaternion const& q2
	);


/////////////////////////////////////////////////////////////////////
Quaternion const operator * (
	  Quaternion const& ql
	, Quaternion const& qr
	);


/////////////////////////////////////////////////////////////////////
Quaternion const operator * (
	  Quaternion const& q
	, sreal_t const& v
	);


/////////////////////////////////////////////////////////////////////
RVector const operator * (
	  Quaternion const& q
	, RVector const& v
	);


/////////////////////////////////////////////////////////////////////
Quaternion const operator / (
	  Quaternion const& q
	, sreal_t const& v
	);


/////////////////////////////////////////////////////////////////////
template <
	  typename CharT
	, typename TraitsT
>
std::basic_ostream<CharT, TraitsT>& operator << (
	std::basic_ostream<CharT, TraitsT>& bos
	, Quaternion const& q
	)
{
	bos << '[' << q.l0 << ", " << q.l1 << ", " << q.l2 << ", " << q.l3 << ']';
	return bos;
}


/////////////////////////////////////////////////////////////////////
template <
	typename CharT
	, typename TraitsT
>
std::basic_istream<CharT, TraitsT>& operator >> (
	std::basic_istream<CharT, TraitsT>& is
	, Quaternion& q
	)
{
	is >> q.l0 >> q.l1 >> q.l2 >> q.l3;
	return is;
}


/* Функция преобразования кватерниона в углы Эйлера */
//////////////////////////////////////////////////////////////////////////////
Euler const to_euler(Quaternion const& q);


/* Функция преобразования кватерниона в матрицу направляющих косинусов */
//////////////////////////////////////////////////////////////////////////////
RMatrix const to_matrix(Quaternion const& q);


} /* namespace d3 */

} /* namespace science */


#endif  SCIENCE_QUATERNION_HPP_INCLUDED__