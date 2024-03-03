//////////////////////////////////////////////////////////////////////////////
// euler.hpp
// Copyright (c) 2020 by Alexander Kuslya <kuslya.alexander@gmail.com>


#ifndef SCIENCE_EULER_HPP_INCLUDED__
#define SCIENCE_EULER_HPP_INCLUDED__


#include <science/core/type.hpp>
#include <science/geometry/orientation/predefine.hpp>

#include <ostream>



//////////////////////////////////////////////////////////////////////////
namespace science {

//////////////////////////////////////////////////////////////////////////
namespace d3 {


/* РЈРіР»С‹ Р­Р№Р»РµСЂР° */
//////////////////////////////////////////////////////////////////////////////
struct Euler
{
	sreal_t g; // СѓРіРѕР» РєСЂРµРЅР°
	sreal_t p; // СѓРіРѕР» СЂС‹СЃРєР°РЅСЊСЏ
	sreal_t t; // СѓРіРѕР» С‚Р°РЅРіР°Р¶Р°

	Euler();

	Euler(
		  sreal_t const g
		, sreal_t const p
		, sreal_t const t
	);

	explicit Euler(sreal_t const ptr[3]);		

	sreal_t const& operator[] (unsigned const i) const;	

	sreal_t& operator[] (unsigned const i);

	Euler& assign(
		  sreal_t const g_
		, sreal_t const p_
		, sreal_t const t_
	);

	Euler& operator += (Euler const& eul);

	Euler& operator -= (Euler const& eul);

	Euler& operator *= (sreal_t const v);

	Euler& operator /= (sreal_t const v);

	Euler& assign(sreal_t const ptr[3]);
};


/* Р”РѕРїРѕР»РЅРёС‚РµР»СЊРЅС‹Рµ РѕРїРµСЂР°С‚РѕСЂС‹ */

/////////////////////////////////////////////////////////////////////
Euler const operator + (
	  Euler const& e1
	, Euler const& e2
	);


/////////////////////////////////////////////////////////////////////
Euler const operator - (
	  Euler const& e1
	, Euler const& e2
	);


/////////////////////////////////////////////////////////////////////
Euler const operator * (
	  Euler const& e
	, sreal_t const& v
	);


/////////////////////////////////////////////////////////////////////
Euler const operator / (
	  Euler const& e
	, sreal_t const& v
	);


/////////////////////////////////////////////////////////////////////
template <
	  typename CharT
	, typename TraitsT
>
std::basic_ostream<CharT, TraitsT>& operator << (
	  std::basic_ostream<CharT, TraitsT>& bos
	, Euler const& e
	)
{
	bos << '[' << e.g << ", " << e.p << ", " << e.t << ']';
	return bos;
}


/////////////////////////////////////////////////////////////////////
template <
	  typename CharT
	, typename TraitsT
>
std::basic_istream<CharT, TraitsT>& operator >> (
	  std::basic_istream<CharT, TraitsT>& is
	, Euler& e
	)
{
	is >> e.g >> e.p >> e.t;
	return is;
}


/* Р¤СѓРЅРєС†РёСЏ РїСЂРµРѕР±СЂР°Р·РѕРІР°РЅРёСЏ СѓРіР»РѕРІ Р­Р№Р»РµСЂР° РІ РєРІР°С‚РµСЂРЅРёРѕРЅ */
//////////////////////////////////////////////////////////////////////////////
Quaternion const to_quaternion(Euler const& orn);


/* Р¤СѓРЅРєС†РёСЏ РїСЂРµРѕР±СЂР°Р·РѕРІР°РЅРёСЏ СѓРіР»РѕРІ Р­Р№Р»РµСЂР° РІ РјР°С‚СЂРёС†Сѓ РЅР°РїСЂР°РІР»СЏСЋС‰РёС… РєРѕСЃРёРЅСѓСЃРѕРІ */
//////////////////////////////////////////////////////////////////////////////
RMatrix const to_matrix(Euler const& orn);


/*!***************************************************************************** 
	@brief РџРµСЂРµРіСЂСѓР¶РµРЅРЅР°СЏ РІРµСЂСЃРёСЏ С„СѓРЅРєС†РёРё to_matrix
	@param g - СѓРіРѕР» СЃРѕР±СЃС‚РІРµРЅРЅРѕРіРѕ РІСЂР°С‰РµРЅРёСЏ (СЌРєРІРёРІР°Р»РµРЅС‚ РєСЂРµРЅР° РІ РґРёРЅР°РјРёРєРµ)
	@param p - СѓРіРѕР» РїСЂРµС†РµСЃСЃРёРё (СЌРєРІРёРІР°Р»РµРЅС‚ СЂС‹СЃРєР°РЅСЊСЏ РІ РґРёРЅР°РјРёРєРµ)
	@param t - СѓРіРѕР» РЅСѓС‚Р°С†РёРё (СЌРєРІРёРІР°Р»РµРЅС‚ С‚Р°РЅРіР°Р¶Р° РІ РґРёРЅР°РјРёРєРµ)
	@return RMatrix РјР°С‚СЂРёС†Р° С‚СЂРµС… РїРѕСЃР»РµРґРѕРІР°С‚РµР»СЊРЅС‹С… РїРѕРІРѕСЂРѕС‚РѕРІ
	
	РџРµСЂРµРіСЂСѓР¶РµРЅРЅР°СЏ РІРµСЂСЃРёСЏ РїСЂРµРѕР±СЂР°Р·РѕРІР°РЅРёСЏ С‚СЂРµС… СѓРіР»РѕРІ Р­Р№Р»РµСЂР° g, p, t РІ РјР°С‚СЂРёС†Сѓ 
	РїРѕСЃР»РµРґРѕРІР°С‚РµР»СЊРЅС‹С… РїРѕРІРѕСЂРѕС‚РѕРІ RMatrix.
*******************************************************************************/
RMatrix const to_matrix(
	  sreal_t const g
	, sreal_t const p
	, sreal_t const t
);


} /* namespace d3 */

} /* namespace science */



#endif  SCIENCE_EULER_HPP_INCLUDED__