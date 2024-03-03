//////////////////////////////////////////////////////////////////////////////
// spoint.hpp
// Copyright (c) 2020 by Alexander Kuslya <kuslya.alexander@gmail.com>


#ifndef SCIENCE_SPOINT_HPP_INCLUDED__
#define SCIENCE_SPOINT_HPP_INCLUDED__


#include <science/geometry/coord.hpp>


/////////////////////////////////////////////////////////////////////
namespace science {

/////////////////////////////////////////////////////////////////////
namespace d3 {


/* Класс точки в сферической СК */
/////////////////////////////////////////////////////////////////////
struct SPoint : SCoord
{
	SPoint();

	SPoint(
		  sreal_t const d
		, sreal_t const p
		, sreal_t const t
	);

	explicit SPoint(sreal_t const ptr[3]);

	explicit SPoint(SCoord const& coord);

	SCoord& coord();

	SCoord const& coord() const;

	SPoint& assign(
		  sreal_t const d
		, sreal_t const p
		, sreal_t const t
	);

	SPoint& assign(sreal_t const ptr[3]);
};


}//namespace d3

}//namespace science



#endif  SCIENCE_SPOINT_HPP_INCLUDED__