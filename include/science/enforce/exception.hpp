/*!*****************************************************************************
    @file exception.hpp
    @author Kuslya A.M.
    @date 2023/05/30
    @copyright Copyright (c) 2023 by Alexander Kuslya <alexander.kuslya@gmail.com>
    @brief Модуль, содержащий различного рода исключения и вспомогательные 
    функции для их генерации.
*******************************************************************************/


#ifndef __LIBSCIENCE_ENFORCE_EXCEPTION_HPP_INCLUDED__
#define __LIBSCIENCE_ENFORCE_EXCEPTION_HPP_INCLUDED__


/** \brief science - Common utilities library */
namespace science {

    
/*!***************************************************************************** 
	@brief Функция для удобной генерации std::runtime_error
	@param errstr - форматируемая строка, выводимая в сообщении об ошибке
	
	Функция генерирует std::runtime_error с текстом, сформированным форматируемой
    строкой в стиле C errstr.

    \b Пример:
    \code{.cpp}
    int line = 12;
    int code = 123;
    std::string what = "Bad conditions for multiplication!";
    try {
        die("Error %d: in line=%d \"%s\"\n", code, line, whar.c_str());
    }
    catch (std::runtime_error const& err) {
        std::cout << err.what() << std::endl;   // -> Error 123: in line=12 "Bad conditions for multiplication!"
    }
    \endcode
*******************************************************************************/
void die(const char *errstr, ...);


/*!*****************************************************************************
    @brief Шаблонная версия функции die
    @tparam ErrorT - тип формируемой ошибки
    @param errstr - форматируемая строка, выводимая в сообщении об ошибке

    Функция генерирует исключение заданного типа с текстом, сформированным форматируемой
    строкой в стиле C errstr. В остальном является полным аналогом нешаблонной
    функции die.
*******************************************************************************/
template <typename ErrorT>
inline void die(const char *errstr, ...)
{
    va_list ap;
    char msg[256];

    va_start(ap, errstr);
    vsprintf(msg, errstr, ap);
    va_end(ap);
    throw ErrorT(msg);
}


} /* namespace science */


#endif  // __LIBSCIENCE_ENFORCE_EXCEPTION_HPP_INCLUDED__
