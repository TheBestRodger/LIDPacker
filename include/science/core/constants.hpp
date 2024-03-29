//////////////////////////////////////////////////////////////////////////////
// constants.hpp
// Copyright (c) 2013 by Alexander Kuslya

#ifndef SCIENCE_CONSTANTS_HPP_INCLUDED_
#define SCIENCE_CONSTANTS_HPP_INCLUDED_

#include <science/core/type.hpp>

//////////////////////////////////////////////////////////////////////////////
namespace science{

//////////////////////////////////////////////////////////////////////////////
template<typename T>
struct Const_
{
    static T const degree;
    static T const radian;
    static T const pi;
    static T const half_pi;
    static T const sqr_pi;
    static T const sqrt_pi;
    static T const gravity;
    static T const earth_radius;
    static T const flt_epsilon;
    static T const flt_max;
    static T const light_speed;
};

//////////////////////////////////////////////////////////////////////////////
struct Const : public Const_<sreal_t> {};

//////////////////////////////////////////////////////////////////////////////
template<typename T>
T const Const_<T>::degree = static_cast<T>(57.295779513082320876798154814105170332405);

//////////////////////////////////////////////////////////////////////////////
template<typename T>
T const Const_<T>::radian = static_cast<T>(0.017453292519943295769236907684886127134);

//////////////////////////////////////////////////////////////////////////////
template<typename T>
T const Const_<T>::pi = static_cast<T>(3.141592653589793238462643383279502884197);

//////////////////////////////////////////////////////////////////////////////
template<typename T>
T const Const_<T>::half_pi = static_cast<T>(1.570796326794896619231321691639751442099);

//////////////////////////////////////////////////////////////////////////////
template<typename T>
T const Const_<T>::sqr_pi = static_cast<T>(9.869604401089358618834490999876151135314);

//////////////////////////////////////////////////////////////////////////////
template<typename T>
T const Const_<T>::sqrt_pi = static_cast<T>(1.772453850905516027298167483341145182798);

//////////////////////////////////////////////////////////////////////////////
template<typename T>
T const Const_<T>::gravity = static_cast<T>(9.80665);

//////////////////////////////////////////////////////////////////////////////
template<typename T>
T const Const_<T>::earth_radius = static_cast<T>(6378137.);

//////////////////////////////////////////////////////////////////////////////
template<typename T>
T const Const_<T>::flt_epsilon = static_cast<T>(1.192092896e-07F);

//////////////////////////////////////////////////////////////////////////////
template<typename T>
T const Const_<T>::flt_max = static_cast<T>(3.402823466e+38F);

//////////////////////////////////////////////////////////////////////////////
template<typename T>
T const Const_<T>::light_speed = static_cast<T>(299792458);

}
#endif