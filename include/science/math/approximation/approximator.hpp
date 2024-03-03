//////////////////////////////////////////////////////////////////////////////
// approximator.hpp
// Copyright (c) 2015 by Alexander Kuslya


#ifndef SCIENCE_APPROXIMATION_APPROXIMATOR_HPP_INCLUDED_
#define SCIENCE_APPROXIMATION_APPROXIMATOR_HPP_INCLUDED_


#include <science/core/base.hpp>
#include <science/geometry/point.hpp>
#include <science/geometry/coord.hpp>
#include <science/math/polynom.hpp>
#include <vector>


/** \brief science - Common utilities library */
namespace science {


/** \brief detail - вспомагательная область видимости */
namespace detail {


//////////////////////////////////////////////////////////////////////////////
class LagrangePolimolialApproximation
{
    typedef science::d2::RPoint RPoint;


public:
    static Polynom const get_polynomial(
          std::vector<RPoint> const points
        , unsigned const polynom_pow
        );

private:
    static Polynom const do_polynomial_getting(
          std::vector<RPoint> const filtered_points
        , unsigned const polynom_pow
        );

    static std::vector<RPoint> const do_filter_points_by_pow (
          std::vector<RPoint> const filtered_points
        , unsigned const polynom_pow
        );

    static sreal_t const summ_of_combination_multiplications(
          std::vector<sreal_t> const set
        , unsigned const number_of_combinators
        );

    static std::vector<RPoint> const get_sorted_vector(
        std::vector<RPoint> const points
        );
};


} /* namespace detail */



//////////////////////////////////////////////////////////////////////////////
class Approximator : public NonCopyable
{    
    Approximator();

public:        
	typedef science::d2::RPoint RPoint;


	static Polynom const least_squares(
          std::vector<RPoint> const points
        , unsigned const polynom_pow
        );

    static Polynom const lagrange_polynomial(
          std::vector<RPoint> const points
        , unsigned const polynom_pow
        );

private:
    static void check_vector(std::vector<RPoint> const points); // std::runtime_error
};


} /* namespace science */


#endif