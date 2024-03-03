/*!*****************************************************************************
	@file struct.hpp				               
	@author Kuslya A.M.
	@date 2023/05/31
	@copyright Copyright (c) 2023 by Alexander Kuslya <alexander.kuslya@gmail.com>
	@brief Модуль, содержащий вспомагательные структуры для математического аппарата
*******************************************************************************/


#ifndef __LIBSCIENCE_MATH_STRUCT_HPP_INCLUDED__
#define __LIBSCIENCE_MATH_STRUCT_HPP_INCLUDED__


#include <science/core/type.hpp>


/** \brief science - Common utilities library */
namespace science {


/*!*****************************************************************************
	@brief Ограничение диапазона значений
	@author Kuslya A.M.
	@version 1.0
	@date 2023/05/31
	
	Сруктура содержит два значения, для ограничения диапазона. Применяется в 
	функциях, связанных с ограничениями, например saturate().
*******************************************************************************/
struct Limits
{
    sreal_t min;		/**< Нижняя граница диапазона */
    sreal_t max;		/**< Верхняя граница диапазона */
};

} /* namespace science */


#endif // __LIBSCIENCE_MATH_STRUCT_HPP_INCLUDED__