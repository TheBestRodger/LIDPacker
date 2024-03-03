/*!*****************************************************************************
	@file utility.hpp				               
	@author Kuslya A.M.
	@date 2023/05/30
	@copyright Copyright (c) 2023 by Alexander Kuslya <alexander.kuslya@gmail.com>
	@brief Модуль вспомагательных функций для работы с текстовыми строками, их 
    генерации и конвертирования
*******************************************************************************/

#ifndef __LIBSCIENCE_STRING_UTILITY_HPP_INCLUDED__
#define __LIBSCIENCE_STRING_UTILITY_HPP_INCLUDED__


#include <science/enforce/exception.hpp>

#include <sstream>
#include <string>
#include <vector>


/** \brief science - Common utilities library */
namespace science {


/*!***************************************************************************** 
	@brief Функция форматирования строки
	@param format - форматируемая строка
	@return форматированная строка
	
	Функция предназначена для того, упростить работу с форматированием строки.
    Является аналогом boost::format и сделана, в первую очередь, чтобы исключить
    необходимость развоварачивания буста, ради одной фичи. Поддерживает весь
    синтаксис форматирования строк из стандарта языка C.
*******************************************************************************/
std::string sformat(std::string const format, ...);


/*!*****************************************************************************
	@brief Перегруженная версия для работы с юникодом
	@param format - форматируемая строка в формате UTF16
	@return форматированная строка

	Функция предназначена для того, упростить работу с форматированием строки.
	Является аналогом boost::format и сделана, в первую очередь, чтобы исключить
	необходимость развоварачивания буста, ради одной фичи. Поддерживает весь
	синтаксис форматирования строк из стандарта языка C.
*******************************************************************************/
std::u16string sformat(std::u16string const format, ...);


/*!***************************************************************************** 
	@brief Преобразование строки в заданный тип данных
	@tparam Type - тип, к которому преобразовывается строка
	@param s - преобразуемая строка
	@return Преобразованное значение, типа Type
	
	Функция осуществляет преобразование строки s к заданному типу Type и 
	возвращает преобразованное значение. В случае, если строка не может быть
	преобразована к заданному типу функция вызывает исключение.
*******************************************************************************/
template <class Type>
inline Type string_to(std::string const& s)
{
	Type out;

	std::istringstream in(s);
	if (!(in >> out))
		die("s_to_type error: unable to convert string to type!\nstring: \"%s\"\ntype: \"%s\"", s.c_str(), typeid(Type).name());

	return out;
}


/*!*****************************************************************************
	@brief Разбиение строки на элементы и преобразования их в вектор
	@tparam Type - тип элементов выходного вектора
	@param s - преобразуемая строка
	@param vt - вектор, в который записываются элементы строки после разбиения

	Функция осуществляет преобразование строки s в вектор vt элементы которого
	имеют тип Type. Строка для этого должна содержать набор числовых элементов, 
	разделенных пробелами (либо лубыми другими whitespace символами).
*******************************************************************************/
template <class Type >
inline void string_to_vector(
	  std::string const& s
	, std::vector<Type>& vt
)
{
	std::istringstream in(s);
	while (!in.eof()) {
		Type out;
		if (!(in >> out))
			die("s_to_type error: unable to convert string to vector!\nstring: \"%s\"\ntype: \"%s\"", s.c_str(), typeid(Type).name());

		vt.push_back(out);
	}
}


/*!*****************************************************************************
	@brief Перегруженная версия, возвращающая копию вектора
	@tparam Type - тип элементов выходного вектора
	@param s - преобразуемая строка
	@param vt - вектор, в который записываются элементы строки после разбиения
	@return вектор, сформированный в результате преобразования

	Функция осуществляет преобразование строки s в вектор, элементы которого
	имеют тип Type и возвращает его из функции в качестве результата. Логика
	функции аналогична функции с двумя аргументами.
*******************************************************************************/
template <class Type >
inline std::vector<Type> string_to_vector(std::string const& s)
{
	std::vector<Type> vt;
	std::istringstream in(s);

	while (!in.eof()) {
		Type out;
		if (!(in >> out))
			die("s_to_type error: unable to convert string to vector!\nstring: \"%s\"\ntype: \"%s\"", s.c_str(), typeid(Type).name());

		vt.push_back(out);
	}

	return vt;
}


/*!*****************************************************************************
	@brief Преобразование u16string в string
	@param in - u16string строка в 16 битном юникоде
	@return string стандартная строка

	Функция преобразовывает входную 16 битную строку in в юникоде в стандартную
	строку C++ типа std::string.
*******************************************************************************/
std::string to_stdstring(std::u16string const& in);


/*!*****************************************************************************
	@brief Преобразование std::string в u16string
	@param in - std::string строка
	@return u16string 16 битная юникод строка

	Функция преобразовывает входную стандартную C++ строку in в 16 битную юникод
	строку.
*******************************************************************************/
std::u16string to_u16string(std::string const& in);


/*!***************************************************************************** 
	@brief Разбиение строки на части
	@param line - разбиваемая строка
	@param delimiter - символ-разделитель
	@param ignoreEmpties - признак игнорирования пустых строк, получаемых при разбиении
	@return вектор строк, полученный после разбиения одной строки
	
	Функция осуществляет разбиение строки на элементы, используя в качестве 
	разделителя заданный delimiter. Если задан ignoreEmpties = true, то при 
	получении после разбиения строки в одном из элементов пустой строки она 
	не добавляется в результирующий вектор. По-умолчанию ignoreEmpties = true.

	Пример:
	для строки:
	std::string line = "Hello, darkness, my old friend!" 
	вызов функции split(line, ' ');
	вернет массив следующего содержания:
	[0] - "Hello,"
	[1] - "darkness,"
	[2] - "my"
	[3] - "old"
	[4] - "friend!"

	Добавив пробел между my и old получитм следующее:
	std::string line = "Hello, darkness, my  old friend!"
	и зменим вызов функции split(line, ' ', false);
	вернет массив следующего содержания:
	[0] - "Hello,"
	[1] - "darkness,"
	[2] - "my"
	[3] - ""
	[4] - "old"
	[5] - "friend!"
*******************************************************************************/
std::vector<std::string> split(std::string const& line, char delimiter, bool ignoreEmpties = true);


/*!*****************************************************************************
	@brief Шаблонная версия функции
	@tparam Type - тип данных, к которому преобразовывается разбиваемая строка
	@param line - разбиваемая строка
	@param delimiter - символ-разделитель
	@param ignoreEmpties - признак игнорирования пустых строк, получаемых при разбиении
	@return вектор строк, полученный после разбиения одной строки

	Функция осуществляет разбиение строки на элементы и преобразовывает их к 
	заданному типу Type.
*******************************************************************************/
template <class Type>
std::vector<Type> split(std::string const& line, char delimiter, bool ignoreEmpties = true)
{
	auto sVector = split(line, delimiter, ignoreEmpties);
	std::vector<Type> tVector;
	for (auto&& elem : sVector)
		tVector.push_back(string_to<Type>(elem));

	return tVector;
}


/*!***************************************************************************** 
	@brief Перегруженная версия функции для whitespace
	@param line - разбиваемая строка
	@param ignoreEmpties - признак игнорирования пустых строк, получаемых при разбиении
	@return вектор строк, полученный после разбиения одной строки
	
	Перегруженная версия функции разбиения строк. Данная функция отличается от
	основной тем, что пользователь не может настроить разделитель строк, тут
	всегда в качестве разделителя используются любые whitespace символы. Кроме
	того, данная функции всегда игнорирует любые пустые строки.
*******************************************************************************/
std::vector<std::string> split(std::string const& line);


/*!*****************************************************************************
	@brief Перегруженная шаблонная версия функции для whitespace
	@tparam Type - тип данных, к которому преобразовывается разбиваемая строка
	@param line - разбиваемая строка
	@param ignoreEmpties - признак игнорирования пустых строк, получаемых при разбиении
	@return вектор строк, полученный после разбиения одной строки

	Перегруженная версия функции разбиения строк. Данная функция отличается от
	основной тем, что пользователь не может настроить разделитель строк, тут
	всегда в качестве разделителя используются любые whitespace символы. Кроме
	того, данная функции всегда игнорирует любые пустые строки.
*******************************************************************************/
template <class Type>
std::vector<Type> split(std::string const& line)
{
	auto sVector = split(line);
	std::vector<Type> tVector;
	for (auto&& elem : sVector)
		tVector.push_back(string_to<Type>(elem));

	return tVector;
}

/*!***************************************************************************** 
	@brief Провека, что строка является числовой
	@param line - строка с данными
	@return bool - true если строка числовая и false в противном случае
	
	Функция осуществляет проверку, что строка является числовой. Под числовой 
	понимается такая строка, в которой все элементы могут быть преобразованы к
	числам с плавающей запятой.

	Пример:
	"1.234 -0.123 5.3131 9.81 -12.3"  - числовая строка
	"0.0.0.1 12.411-4 5.11 15.-3" - не числовая строка
	"sin(x) 1e-5 123.321" - не числовая строка
*******************************************************************************/
bool is_numerical(std::string const& line);

} /* namespace science */



#endif  // __LIBSCIENCE_STRING_UTILITY_HPP_INCLUDED__
