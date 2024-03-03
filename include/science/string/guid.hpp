/*!*****************************************************************************
	@file guid.hpp				               
	@author Kuslya A.M.
	@date 2023/05/30
	@copyright Copyright (c) 2023 by Alexander Kuslya <alexander.kuslya@gmail.com>
	@brief Модуль утилит для генерации GUID и работы с ними
*******************************************************************************/

#ifndef __LIBSCIENCE_GUID_HPP_INCLUDED__
#define __LIBSCIENCE_GUID_HPP_INCLUDED__


#include <ctime>
#include <string>


/** \brief science - Common utilities library */
namespace science {


/*!*****************************************************************************
    @brief Генерация уникального идентификатора
    @param length длина идентификатора
    @return string уникальный идентификатор

    Генерация уникального идентификатора состоящего из следующих допустимых
    символов: "abcdefghijklmnopqrstuvwxyz0123456789". Выбор следующего символа
    осуществляется на основании rand().
*******************************************************************************/
std::string make_guid(unsigned const length, unsigned const seed = time(NULL));


/*!*****************************************************************************
    @brief Генерация уникального идентификатора заданного формата
    @param format заданный формат GUID
    @return string уникальный идентификатор

    Генерация уникального идентификатора состоящего из следующих допустимых
    символов: "abcdefghijklmnopqrstuvwxyz0123456789". Выбор следующего символа
    осуществляется на основании rand(). Заданный формат GUID задается строкой,
    где генерируемый символ задается тегом ~. 
    Пример: format = "~~~~-~~~-~~~~~~~~~~"; return = "a0xd-12c-3f5e7q6gd5";
*******************************************************************************/
std::string make_guid(std::string const& format, unsigned const seed = time(NULL));


} /* namespace science */



#endif  // __LIBSCIENCE_GUID_HPP_INCLUDED__
