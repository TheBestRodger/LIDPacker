/////////////////////////////////////////////////////////////////////
// rcoord.hpp
// Copyright (c) 2014 by Alexander Kuslya


#ifndef SCIENCE_GEOMETRY_COORD_RCOORD_HPP_INCLUDED_
#define SCIENCE_GEOMETRY_COORD_RCOORD_HPP_INCLUDED_


#include <science/core/type.hpp>
#include <science/geometry/coord/predefine.hpp>

#include <assert.h>
#include <ostream>



/////////////////////////////////////////////////////////////////////
namespace science {

/////////////////////////////////////////////////////////////////////
namespace d3 {

//////////////////////////////////////////////////////////////////////////
namespace detail {


/* Вспомогательный базовый класс для реализации модели инициализации сферических координат */
//////////////////////////////////////////////////////////////////////////////
class RCoordAssign
{
public:
    RCoord& assign_from(SCoord const& sc);
};


} /* namespace detail */



/* Координата в прямоугольной системе координат */
/////////////////////////////////////////////////////////////////////
struct RCoord : private detail::RCoordAssign
{
    sreal_t x;  /**< Составляющая координаты по оси OX */
    sreal_t y;  /**< Составляющая координаты по оси OY */
	sreal_t z;  /**< Составляющая координаты по оси OZ */


    /* Конструктор по-умолчанию. Все поля равны нулю. */
    RCoord();

    /* Конструктор с присвоением всем полям значений */
    RCoord(sreal_t const& x_, sreal_t const& y_, sreal_t const& z_);

    /*
        Конструктор с присвоением всем полям значений из элементов входного массива

        Элементы в массиве должны идти в следующем порядке:
        [0] - координата по оси OX
        [1] - координата по оси OY
        [2] - координата по оси OZ
    */
    explicit RCoord(sreal_t const ptr[3]);

    /* Конструктор с присвоеним всем полям значений из элементов входной координаты в сферической системе координат */
    explicit RCoord(SCoord const& sc);

    /* Оператор присвоения всем полям значений из элементов входной координаты в сферической системе координат */
    RCoord& operator = (SCoord const& sc);
    
    /* Функция для инициализации всех полей координаты заданными значениями */
    RCoord& assign(sreal_t const& x_, sreal_t const& y_, sreal_t const& z_);	

    /* Функция для инициализации всех полей координаты заданными значениями из элементов массива */
    RCoord& assign(sreal_t const ptr[3]);

    /*
        Константная веврсия оператор поэлементого доступа к полям координаты.

        Элементы индексируются следующем порядке:
		[0] - координата по оси OX
		[1] - координата по оси OY
		[2] - координата по оси OZ

        Имеется проверка на значение индекса!
    */
    sreal_t const& operator[](size_t const i) const;
	
    /*
        Оператор поэлементого доступа к полям координаты.

        Элементы индексируются следующем порядке:
		[0] - координата по оси OX
		[1] - координата по оси OY
		[2] - координата по оси OZ

        Имеется проверка на значение индекса!
    */
    sreal_t& operator[](size_t const i);

    /* Константная версия функции, возвращающей указатель на координату OX  */
    sreal_t const* begin() const;

    /* Функция, возвращающая указатель на координату OX */
    sreal_t* begin();

    /* Константная версия функции, возвращающей указатель на элемент, следующий за координатой OZ */
    sreal_t const* end() const;

    /* Функция, возвращающая указатель на элемент, следующий за координатой OZ */
    sreal_t* end();
};


/////////////////////////////////////////////////////////////////////
template <
	  typename CharT
	, typename TraitsT
>
std::basic_ostream<CharT, TraitsT>& operator << (
	  std::basic_ostream<CharT, TraitsT>& os
	, science::d3::RCoord const& rc
	)
{
	os << '[' << rc.x << ", " << rc.y << ", " << rc.z << ']';
	return os;
}

/////////////////////////////////////////////////////////////////////
template <
	  typename _Elem
	, typename _Traits
>
std::basic_istream<_Elem, _Traits>& operator >> (
	  std::basic_istream<_Elem, _Traits>& is
	, science::d3::RCoord& rc
	)
{
    is >> rc.x >> rc.y >> rc.z;

	return is;
}


}//namespace d3




/////////////////////////////////////////////////////////////////////
namespace d2 {


//////////////////////////////////////////////////////////////////////////
namespace detail {


/* Вспомагательный базовый класс для реализации модели инициализации сфяерических коодинат */
//////////////////////////////////////////////////////////////////////////////
class RCoordAssign
{
public:
	RCoord& assign_from(SCoord const& sc);
};


} /* namespace detail */


/////////////////////////////////////////////////////////////////////
struct RCoord : public detail::RCoordAssign
{
	sreal_t x;  /* Составляющая координаты по оси OX */
	sreal_t y;  /* Составляющая координаты по оси OY */

	/* Конструктор по-умолчанию. Все поля равны нулю. */
    RCoord();

	/* Конструктор с присвоением всем полям значений */
    RCoord(sreal_t const& x_, sreal_t const& y_);

    /*
        Конструктор с присвоением всем полям значений из элементов входного массива

        Элементы в массиве должны идти в следующем порядке:
        [0] - координата по оси OX
        [1] - координата по оси OY
    */
    explicit RCoord(sreal_t const ptr[2]);

	/* Конструктор с присвоеним всем полям значений из элементов входной координаты в полярной системе координат */
	explicit RCoord(SCoord const& sc);

    /* Функция для инициализации всех полей координаты заданными значениями */
    RCoord& assign(sreal_t const& x_, sreal_t const& y_);

    /* Функция для инициализации всех полей координаты заданными значениями из элементов массива */
    RCoord& assign(sreal_t const ptr[2]);

    /*
        Константная веврсия оператора поэлементого доступа к полям координаты.

        Элементы индексируются следующем порядке:
        [0] - координата по оси OX
        [1] - координата по оси OY

        Имеется проверка на значение индекса!
    */
    sreal_t const& operator[](size_t const i) const;

    /*
        Оператор поэлементого доступа к полям координаты.

        Элементы индексируются следующем порядке:
        [0] - координата по оси OX
        [1] - координата по оси OY

        Имеется проверка на значение индекса!
    */
    sreal_t& operator[](size_t const i);
};


/////////////////////////////////////////////////////////////////////
template <
      typename CharT
    , typename TraitsT
>
std::basic_ostream<CharT, TraitsT>& operator << (
      std::basic_ostream<CharT, TraitsT>& os
    , science::d2::RCoord const& rc
)
{
    os << '[' << rc.x << ", " << rc.y << ']';
    return os;
}


/////////////////////////////////////////////////////////////////////
template <
	typename CharT
	, typename TraitsT
>
std::basic_istream<CharT, TraitsT>& operator >> (
	std::basic_istream<CharT, TraitsT>& is
	, science::d2::RCoord& rc
	)
{
    is >> rc.x >> rc.y;
	return is;
}

}//namespace d2

}//namespace science


#endif