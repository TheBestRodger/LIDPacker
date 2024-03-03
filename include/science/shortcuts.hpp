//////////////////////////////////////////////////////////////////////////////
// shortcuts.hpp
// Copyright (c) 2017 by Alexander Kuslya <kuslya.alexander@gmail.com>

/*****************************************************************************
Files name:			shortcuts.hpp				               
Description:        Helpful file, which is keep typedefs for all useful types. 
                    For using with specified namespace define CUSTOM_NAMESPACE 
                    macros with namespace of your project, whew this header is 
                    included
******************************************************************************/



#include <science/geometry/coord.hpp>
#include <science/geometry/point.hpp>
#include <science/geometry/vector.hpp>
#include <science/geometry/orientation.hpp>




/* NameSpaces logic */
//////////////////////////////////////////////////////////////////////////////
#ifdef CUSTOM_NAMESPACE


#ifndef NAMESPACE_OPEN
#define NAMESPACE_OPEN namespace CUSTOM_NAMESPACE {
#endif

#ifndef NAMESPACE_CLOSE
#define NAMESPACE_CLOSE }
#endif


#else


#ifndef NAMESPACE_OPEN
#define NAMESPACE_OPEN
#endif

#ifndef NAMESPACE_CLOSE
#define NAMESPACE_CLOSE
#endif


#endif
//////////////////////////////////////////////////////////////////////////////




/* Typedefs for simplify */
NAMESPACE_OPEN
/*************************************************************************/
typedef science::d3::RCoord         RCoord;
typedef science::d3::SCoord         SCoord;
typedef science::d3::RVector        RVector;
typedef science::d3::SVector        SVector;
typedef science::d3::RMatrix        RMatrix;
typedef science::d3::Euler          Euler;
typedef science::d3::Quaternion     Quaternion;
/*************************************************************************/
NAMESPACE_CLOSE
