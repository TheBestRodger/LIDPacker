//////////////////////////////////////////////////////////////////////////////
// approximation.hpp
// Copyright (c) 2014 by Alexander Kuslya

#ifndef	SCIENCE_MATH_APPROXIMATION_APPROXIMATION_HPP_INCLUDED_
#define	SCIENCE_MATH_APPROXIMATION_APPROXIMATION_HPP_INCLUDED_


#include <science/core/type.hpp>


namespace science{

//////////////////////////////////////////////////////////////////////////////
void approximation(
      double **Points
    , size_t points_number
    , size_t polynom_power
    , double *result_matrix
    );

} 


#endif