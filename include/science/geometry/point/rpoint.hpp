//////////////////////////////////////////////////////////////////////////////
// rpoint.hpp
// Copyright (c) 2020 by Alexander Kuslya <kuslya.alexander@gmail.com>


#ifndef SCIENCE_RPOINT_HPP_INCLUDED__
#define SCIENCE_RPOINT_HPP_INCLUDED__


#include <science/geometry/coord.hpp>


/////////////////////////////////////////////////////////////////////
namespace science {

/////////////////////////////////////////////////////////////////////
namespace d3 {

	
/* Класс точки в прямоугольной СК */
/////////////////////////////////////////////////////////////////////
struct RPoint : RCoord
{
	RPoint();

	RPoint(
		  sreal_t const x
		, sreal_t const y
		, sreal_t const z
	);

	explicit RPoint(sreal_t const ptr[3]);

	explicit RPoint(SCoord const& coord);

	RCoord& coord();

	RCoord const& coord() const;

	RPoint& assign(
		  sreal_t const x
		, sreal_t const y
		, sreal_t const z
	);

	RPoint& assign(sreal_t const ptr[3]);
};


}//namespace d3



//////////////////////////////////////////////////////////////////////////
namespace d2 {

/* Класс точки в прямоугольной СК */
/////////////////////////////////////////////////////////////////////
struct RPoint : RCoord
{
	RPoint();

	RPoint(
		  sreal_t const x
		, sreal_t const y
	);

	explicit RPoint(sreal_t const ptr[2]);

	explicit RPoint(SCoord const& coord);

	RCoord& coord();

	RCoord const& coord() const;

	RPoint& assign(
		  sreal_t const x
		, sreal_t const y
	);

	RPoint& assign(sreal_t const ptr[2]);
};

} /* namespace d2 */


}//namespace science



#endif  SCIENCE_RPOINT_HPP_INCLUDED__