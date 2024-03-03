//////////////////////////////////////////////////////////////////////////////
// svector.hpp
// Copyright (c) 2020 by Alexander Kuslya <kuslya.alexander@gmail.com>


#ifndef SCIENCE_SVECTOR_HPP_INCLUDED__
#define SCIENCE_SVECTOR_HPP_INCLUDED__


#include <science/geometry/point/predefine.hpp>
#include <science/geometry/vector/predefine.hpp>
#include <science/geometry/coord/scoord.hpp>


//////////////////////////////////////////////////////////////////////////
namespace science {

//////////////////////////////////////////////////////////////////////////
namespace d3 {

//////////////////////////////////////////////////////////////////////////
namespace detail {


/* Вспомагательный базовый класс для реализации модели инициализации вектора в сферической системе координат */
//////////////////////////////////////////////////////////////////////////////
class SVectorAssign : public SCoordAssign
{
public:
	SVector& assign_from(RVector const& sc);
};


} /* namespace detail */


//////////////////////////////////////////////////////////////////////////////
struct SVector
	: public SCoord
	, public detail::SVectorAssign
{
	SVector();

	SVector(
		  sreal_t const d
		, sreal_t const p
		, sreal_t const t
	);

	explicit SVector(sreal_t const ptr[3]);

	SVector(RCoord const& rc);

	SVector(SCoord const& sc);

	SVector& operator = (RVector const& rv);

	SCoord& coord();

	SCoord const& coord() const;

	SVector operator - () const;

	SVector& operator += (SVector const& v);

	SVector& operator -= (SVector const& v);

	SVector& operator *= (sreal_t const value);

	SVector& operator /= (sreal_t const value);

	SVector& assign(
		  sreal_t const t1
		, sreal_t const t2
		, sreal_t const t3
	);

	SVector& assign(sreal_t const ptr[3]);
};


/////////////////////////////////////////////////////////////////////
sreal_t const module(SVector const& v);


/////////////////////////////////////////////////////////////////////
SVector& normalize(SVector& v);


/////////////////////////////////////////////////////////////////////
sreal_t const scalar_prod(
	  SVector const& vl
	, SVector const& vr
);


/////////////////////////////////////////////////////////////////////
SVector const cross_prod(
	  SVector const& vl
	, SVector const& vr
);


/////////////////////////////////////////////////////////////////////
SVector operator + (
	  SVector const& lv
	, SVector const& rv
	);


/////////////////////////////////////////////////////////////////////
SVector operator - (
	SVector const& lv
	, SVector const& rv
	);


/////////////////////////////////////////////////////////////////////
SVector operator - (
	  SPoint const& lp
	, SPoint const& rp
	);


/////////////////////////////////////////////////////////////////////
SVector operator * (
	  SVector const& v
	, sreal_t const constant
	);


/////////////////////////////////////////////////////////////////////
SVector operator / (
	SVector const& v
	, sreal_t const constant
	);


} /* namespace d3 */

} /* namespace science */


#endif  SCIENCE_SVECTOR_HPP_INCLUDED__