/*!*****************************************************************************
	@file polynom.hpp				               
	@author Kuslya A.M.
	@date 2023/05/31
	@copyright Copyright (c) 2023 by Alexander Kuslya <alexander.kuslya@gmail.com>
	@brief Модуль, содержащий реализацию полиномиальной функции
*******************************************************************************/

#ifndef SCIENCE_MATH_POLYNOM_HPP_INCLUED_
#define SCIENCE_MATH_POLYNOM_HPP_INCLUED_

#include <science/core/type.hpp>
#include <science/math/struct.hpp>

#include <vector>


/** \brief science - Common utilities library */
namespace science {


//////////////////////////////////////////////////////////////////////////////
/*
realization of a standard polynomial:
y = a0 + a1 * x^1 + a2 * x^2 + ... + an * x^n
y - is a result of Polynom::operator()
[a0, an] - an array, set in constructor or in method 'set()'.

Notice:
First element of array must be a0!

*/
//////////////////////////////////////////////////////////////////////////////
class Polynom
{	
    std::vector<sreal_t> coefficients_;

    science::Limits limits_;

public:
    Polynom();
    
    Polynom(
          unsigned const pow
        , sreal_t const* coefficients
        );

    Polynom(std::vector<sreal_t> const coefficients);

    sreal_t const operator () (sreal_t const x);

    void set(
          unsigned const pow
        , sreal_t const* coefficients
        );

    void set(std::vector<sreal_t> const coefficients);

    unsigned const pow() const;

    /*  Argument automatic will be bordered by limits value  */
    void set_x_limits(
          sreal_t const min_x
        , sreal_t const max_x
        );

    void set_x_limits(Limits const&);
        

    Limits const& get_x_limits() const;

    /*
        Operators
    */

    sreal_t const operator [] (unsigned const i) const;

    sreal_t& operator [] (unsigned const i);

    friend Polynom operator * (Polynom const& , sreal_t const& k);

    friend Polynom& operator *= (Polynom& , sreal_t const& k);

    friend Polynom operator / (Polynom const& , sreal_t const& k);

    friend Polynom& operator /= (Polynom& , sreal_t const& k);

    friend Polynom operator + (Polynom const&, Polynom const&);

    friend Polynom& operator += (Polynom&, Polynom const&);

    friend Polynom operator - (Polynom const&, Polynom const&);

    friend Polynom& operator -= (Polynom&, Polynom const&);

private:
    template <typename VectorT>
    void vector_initialization(
          unsigned const size
        , VectorT const& vector
        );
};





//////////////////////////////////////////////////////////////////////////////    
template <typename VectorT>
void Polynom::vector_initialization( 
      unsigned const size 
    , VectorT const& vector 
    )
{
    coefficients_.clear();
    coefficients_.resize(size);

    for (unsigned i = 0; i < size; ++i)
        coefficients_[i] = vector[i];
}

} /* namespace science */


#endif  // SCIENCE_MATH_POLYNOM_HPP_INCLUED_