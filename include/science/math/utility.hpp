/*!*****************************************************************************
	@file utility.hpp				               
	@author Kuslya A.M.
	@date 2023/05/30
	@copyright Copyright (c) 2023 by Alexander Kuslya <alexander.kuslya@gmail.com>
	@brief Модуль вспомагательных функций, связанных  с математическими операциями
*******************************************************************************/


#ifndef __LIBSCIENCE_MATH_UTILITY_HPP_INCLUDED__
#define __LIBSCIENCE_MATH_UTILITY_HPP_INCLUDED__


#include <science/core/type.hpp>
#include <science/core/constants.hpp>
#include <assert.h>
#include <algorithm>
#include <array>


/** \brief science - Common utilities library */
namespace science {


/* Pre-Define */
struct Limits;


/*!***************************************************************************** 
	@brief Проверка равенства значений с заданной точностью
    @tparam Type - тип проверяемых значений
	@param lv - первое сравниваемое значение
	@param rv - второе сравниваемое значение
	@param epsilon - точность, с которой сравниваются значения
	@return true или false, в зависимости от точности сходимости значений
	
	Шаблонная функция, проверяет, насколько близко друг к другу находятся значения
    lv и rv. Если разница между двумя значениями не превышает заданной точности
    epsilon, то возвращает true, в противном случае возвращает false.

    \b Пример: 
	\code{.cpp}
	is_close(1.1, 1.2, 0.01); // -> false
	is_close(1.1, 1.2, 0.2); // -> true
	\endcode
*******************************************************************************/
template<typename Type>
inline bool is_close(Type const& lv, Type const& rv, Type const& epsilon)
{
	return (rv >= lv - epsilon && rv <= lv + epsilon);
}


/*!***************************************************************************** 
	@brief Ограничение значения переменной заданным диапазоном без исменения исходного значения
	@tparam Type - тип ограничиваемого значения
	@param arg - ограничиваемый аргумент
	@param lv - минимальое значение ограничения
	@param rv - максимальное значение ограничения
	@return ограниченное значение
	
    Функция преднаначена для ограничения значения arg типа Type величиной lv 
    снизу и величиной rv сверху. В случае, если значение rv оказалось меньше,
    чем значение lv, функция генерирует исключениие. При вызове функции исходное
    значение arg остается неизменным.

	\b Пример:
	\code{.cpp}
	saturation(1.1, 1.0, 2.0); // -> 1.1
	saturation(0.7, 1.0, 2.0); // -> 1.0
	\endcode
*******************************************************************************/
template<typename Type>
inline Type const& saturation(Type const& arg, Type const& lv, Type const& rv)
{
	if (lv > rv)
		throw std::runtime_error("saturation ERR: left value must be smaller than right value!");

	if (arg <= lv)
		return lv;
	if (arg >= rv)
		return rv;
	return arg;
}


/*!***************************************************************************** 
	@brief Перегруженная версия функции с типом аргументов sreal_t
	@param arg - ограничиваемый аргумент
	@param lv - минимальое значение ограничения
	@param rv - максимальное значение ограничения
	@return ограниченное значение
	
	Перегруженная версия функции
*******************************************************************************/
sreal_t const saturation(sreal_t const arg, sreal_t const lv, sreal_t const rv);


/*!*****************************************************************************
    @brief Перегруженная версия функции
    @param arg - ограничиваемый аргумент
    @param lim - структура с минимальным и максимальным значеним аргумента
    @return ограниченное значение
    @sa Limits

    Перегруженная версия функции
*******************************************************************************/
sreal_t const saturation(sreal_t const arg, Limits const& lim);


/*!*****************************************************************************
    @brief Ограничение значения переменной заданным диапазоном с исменением исходного значения
    @tparam Type - тип ограничиваемого значения
    @param arg - ограничиваемый аргумент
    @param lv - минимальое значение ограничения
    @param rv - максимальное значение ограничения
    @return ограниченное значение

    Функция преднаначена для ограничения значения arg типа Type величиной lv
    снизу и величиной rv сверху. В случае, если значение rv оказалось меньше,
    чем значение lv, функция генерирует исключениие. При вызове функции изменяется
    значение переданного аргумента arg.

    \b Пример:
	\code{.cpp}
    saturate(1.1, 1.0, 2.0); // -> compile error. В этом случае нужно использовать saturation()
    double arg = 0.7;
    saturate(arg, 1.0, 2.0); // -> 1.0
    std::cout << arg;   // 1.0
	\endcode
*******************************************************************************/
template<typename Type>
inline Type const& saturate(Type& arg, Type const& lv, Type const& rv)
{
	if (lv >= rv)
		throw std::runtime_error("saturation ERR: left value must be smaller than right value!");

	if (arg <= lv)
		return arg = lv;
	if (arg >= rv)
		return arg = rv;
	return arg;
}


/*!*****************************************************************************
    @brief Перегруженная версия функции с типом sreal_t
    @param arg - ограничиваемый аргумент
    @param lv - минимальое значение ограничения
    @param rv - максимальное значение ограничения
    @return ограниченное значение

    Перегруженная версия функции
*******************************************************************************/
sreal_t const saturate(sreal_t& arg, sreal_t const lv, sreal_t const rv);


/*!*****************************************************************************
    @brief Перегруженная версия функции с типом sreal_t
    @param arg - ограничиваемый аргумент
    @param lim - структура с минимальным и максимальным значеним аргумента
    @return ограниченное значение

    Перегруженная версия функции
*******************************************************************************/
sreal_t const saturate(sreal_t& arg, Limits const& lim);


/*!***************************************************************************** 
	@brief Получение знака переменной
	@tparam Type - тип проверяемого параметра
	@param arg - проверяемый параметр
	@return -1; 0; +1 в зависимости от значения arg
	
	Функция проверяет знак переменной arg типа Type и возвращает -1, если arg отрицательный,
    0, если arg == 0 и 1, если arg положительный.
    Тип передаваемого аргумента должен иметь возможность приведения к типу int.

	\b Пример:
	\code{.cpp}
	sign(2.3);   // 1
	sign(-2.3);  // -1
	sign(0);     // 0
	\endcode
*******************************************************************************/
template<typename Type>
inline int sign(Type const& arg)
{
	if (arg > static_cast<Type>(0))
		return 1;
	else if (arg < static_cast<Type>(0))
		return -1;
	else
		return 0;
}


/*!*****************************************************************************
    @brief Получение знака переменной без нулевого значения
    @tparam Type - тип проверяемого параметра
    @param arg - проверяемый параметр
    @return -1; +1 в зависимости от значения arg

    Функция проверяет знак переменной arg типа Type и возвращает -1, если arg отрицательный
    и 1, если arg неотрицательный (включая 0).
    Тип передаваемого аргумента должен иметь возможность приведения к типу int.

    \b Пример:
	\code{.cpp}
	sign(2.3);   // 1
    sign(-2.3);  // -1
    sign(0);     // 1
	\endcode
*******************************************************************************/
template<typename Type>
inline int sign2(Type const& arg)
{
	if (arg < static_cast<Type>(0))
		return -1;
	else
		return 1;
}


/*!***************************************************************************** 
	@brief Поиск индексов ячеек массива, граничащих с заданным значением
	@tparam Type - тип значений, используемых в функции
	@param arr - массив значений, в котором осуществляется поиск
	@param as - размер массива
	@param arg - искомое значение
	@param lbor - индекс ячейки слева от искомого значения
	@param rbor - индекс ячейки справа от искомого значения
	
	Функция осуществляет поиск индексов соседних с заданным значением arg
    ячеек в массиве arr размера as и инедекс левой ячейки записывает в переменную
    lbor, а индекс правой ячейки в переменную rbor.

	\b Пример:
	\code{.cpp}
	double arr[] = {0.1, 1.3, 2.1, 3.4, 5.6, 11};
	unsigned lbor, rbor;
	get_cell_borders(arr, 6, 2.2, lbor, rbor);
	printf("%d %d");	// 2 3
	\endcode
*******************************************************************************/
template<typename Type>
inline void get_cell_borders(
	  Type const* arr
	, size_t const as
	, Type const& arg
	, unsigned& lbor
	, unsigned& rbor
)
{
	if (arr[0] < arr[as - 1]) {
		if (arg < arr[0]) {
			lbor = rbor = 0;
			return;
		}
		if (arg > arr[as - 1]) {
			lbor = rbor = as - 1;
			return;
		}
	}
	else {
		if (arg > arr[0]) {
			lbor = rbor = 0;
			return;
		}
		if (arg < arr[as - 1]) {
			lbor = rbor = as - 1;
			return;
		}
	}
	if (is_close(arr[as - 1], arg, (Type)FLT_EPSILON)) {
		lbor = as - 1;
		rbor = as - 1;
		return;
	}
	for (unsigned i = 0; i < as - 1; ++i) {
		if (is_close(arr[i], arg, (Type)FLT_EPSILON)) {
			lbor = i;
			rbor = i;
			return;
		}
		if (between_strict(arg, arr[i], arr[i + 1])) {
			lbor = i;
			rbor = i + 1;
			return;
		}
	}


	lbor = rbor = -1;
}


/*!*****************************************************************************
	@brief Строгая проверка нахождения значения в заданном диапазоне
	@tparam Type - тип значений, используемых в функции
	@param val - проверяемое значение
	@param lp - левая граница диапазона
	@param rp - правая граница диапазона
	@return true если значение в диапазоне и false в противном случае

	Функция осуществляет проверку нахождения значения val между значениями lp и rp
	и возвращает true, если оно строго между ними, в противном случае возвраащет
	false.

	\b Пример:
	\code{.cpp}
	between_strict(1, 1, 2);	// -> false
	between_strict(0, 1, 2);	// -> false
	between_strict(1, 0, 2);	// -> true
	\endcode
*******************************************************************************/
template<typename _Type>
inline bool between_strict(
	_Type const& val
	, _Type const& lp
	, _Type const& rp
)
{
	return ((val < rp && val > lp) || (val > rp&& val < lp));
}


/*!*****************************************************************************
	@brief Нестрогая проверка нахождения значения в заданном диапазоне
	@tparam Type - тип значений, используемых в функции
	@param val - проверяемое значение
	@param lp - левая граница диапазона
	@param rp - правая граница диапазона
	@return true если значение в диапазоне и false в противном случае

	Функция осуществляет проверку нахождения значения val между значениями lp и rp
	и возвращает true, если оно нестрого между ними, в противном случае возвраащет
	false.

	\b Пример:
	\code{.cpp}
	between_strict(1, 1, 2);	// -> true
	between_strict(0, 1, 2);	// -> false
	between_strict(1, 0, 2);	// -> true
	\endcode
*******************************************************************************/
template<typename _Type>
inline bool between_slack(
	_Type const& val
	, _Type const& lp
	, _Type const& rp
)
{
	return ((val <= rp && val >= lp) || (val >= rp && val <= lp));
}


/*!*****************************************************************************
	@brief Проверка массива на монотонность
	@tparam Type - тип значений, используемых в функции
	@param arr - проверяемое значение
	@param arraySize - левая граница диапазона
	@return true если массив монотонен и false в противном случае

	Функция осуществляет проверку элементов массива arr размера arraySize и
	возвращает true если элементы монотонно возрастают или монотонно убывают и
	возвращает false в противном случае.
	Кроме того, функция возвращает true, если в массиве только один элемент.

	\b Пример:
	\code{.cpp}
	int aArr[] = {1, 2, 3, 4};
	int bArr[] = {1, 2, 4, 3};

	is_monotonic(aArr, 4);	// true
	is_monotonic(bArr, 4);	// false
	\endcode
*******************************************************************************/
template<typename Type>
inline bool is_monotonic(
	  Type const* arr
	, size_t arraySize
)
{
	assert(arraySize > 0);

	if (arraySize < 2)
		return true;

	int const derivativeSign = sign(arr[1] - arr[0]);
	for (unsigned i = 1; i < arraySize; ++i)
		if (sign(arr[i] - arr[i - 1]) != derivativeSign)
			return false;
	return true;
}


/*!*****************************************************************************
	@brief Проверка массива на возрастающую последовательность
	@tparam Type - тип значений, используемых в функции
	@param arr - входной массив
	@param arraySize - размер массива
	@return true если массив возрастающий и false в противном случае

	Функция осуществляет проверку на монотоность и на возрастающую последовательность

	\b Пример:
	\code{.cpp}
	int aArr[] = {1, 2, 3, 4};
	int bArr[] = {1, 2, 4, 3};

	is_monotonic(aArr, 4);	// true
	is_monotonic(bArr, 4);	// false
	\endcode
*******************************************************************************/
template<typename Type>
inline bool is_increase(
	Type* arr
	, size_t const arraySize
)
{
	if (!is_monotonic(arr, arraySize))
		assert("Array is not monotonic");
	for (int i = 1; i < arraySize; ++i)
		if (arr[i] < arr[i - 1])
			return false;
	return true;
}


/*!*****************************************************************************
	@brief Проверка массива на убывающую последовательность
	@tparam Type - тип значений, используемых в функции
	@param arr - входной массив
	@param arraySize - размер массива
	@return true если массив убывающий и false в противном случае

	Функция осуществляет проверку на монотоность и на убывающую последовательность

	\b Пример:
	\code{.cpp}
	int aArr[] = {4, 3, 2, 1};
	int bArr[] = {4, 3, 4, 1};

	is_monotonic(aArr, 4);	// true
	is_monotonic(bArr, 4);	// false
	\endcode
*******************************************************************************/
template<typename Type>
inline bool is_decrease(
	Type* arr
	, size_t const arraySize
)
{
	if (!is_monotonic(arr, arraySize))
		science::die("Array is not monotonic");
	for (int i = 1; i < arraySize; ++i)
		if (arr[i] > arr[i - 1])
			return false;
	return true;
}

/*!*****************************************************************************
	@brief Преобразование исходного массива в монотонно возрастающий
	@tparam Type - тип значений, используемых в функции
	@param arr - входной массив
	@param arraySize - размер массива

	Функция осуществляет сортировку массива arr пузырьковым методом и преобразовывает
	его в монотонно возрастающий.

	\b Пример:
	\code{.cpp}
	int arr[] = {1, 2, 4, 3};

	to_increase(arr, 4);	// arr = {1, 2, 3, 4};
	\endcode
*******************************************************************************/
template<typename Type>
inline void to_increase(
	  Type* arr
	, size_t const arraySize
)
{
	std::array<Type, arraySize> a;
	for (int i = 0; i < arraySize; i++)
		a[i] = arr[i];

	std::sort(a.begin(), a.end(), std::greater<Type>());
	for (int i = 0; i < arraySize; i++)
		arr[i] = a[i];
}


/*!*****************************************************************************
	@brief Перегруженная версия, не меняющая исходный массив
	@tparam Type - тип значений, используемых в функции
	@param arr - исходный массив
	@param arraySize - размер массива
	@param ourArr - выходной массив

	Функция осуществляет сортировку массива arr пузырьковым методом и сохраняет 
	отсортированный массив в outArr.

	\b Пример:
	\code{.cpp}
	int arr[] = {1, 2, 4, 3};
	int out[4];

	to_increase(arr, 4, out);	// arr = {1, 2, 4, 3}; out = {1, 2, 3, 4};
	\endcode
*******************************************************************************/
template<typename Type>
inline void to_increase(
	  Type* arr
	, size_t const arraySize
	, Type* out
)
{
	std::array<Type, arraySize> a;
	for (int i = 0; i < arraySize; i++)
		a[i] = arr[i];

	std::sort(a.begin(), a.end(), std::greater<Type>());
	for (int i = 0; i < arraySize; i++)
		out[i] = a[i];
}


/*!*****************************************************************************
	@brief Преобразование исходного массива в монотонно убывающий
	@tparam Type - тип значений, используемых в функции
	@param arr - входной массив
	@param arraySize - размер массива

	Функция осуществляет сортировку массива arr пузырьковым методом и преобразовывает
	его в монотонно убывающий.

	\b Пример:
	\code{.cpp}
	int arr[] = {1, 2, 4, 3};

	to_decrease(arr, 4);	// arr = {4, 3, 2, 1};
	\endcode
*******************************************************************************/
template<typename Type>
inline void to_decrease(
	  Type* arr
	, size_t const arraySize
)
{
	std::array<Type, arraySize> a;
	for (int i = 0; i < arraySize; i++)
		a[i] = arr[i];

	std::sort(a.begin(), a.end(), std::less<Type>());
	for (int i = 0; i < arraySize; i++)
		arr[i] = a[i];
}


/*!*****************************************************************************
	@brief Перегруженная версия, не меняющая исходный массив
	@tparam Type - тип значений, используемых в функции
	@param arr - массив данных
	@param arraySize - размер массива
	@param ourArr - выходной массив

	Функция осуществляет сортировку массива arr пузырьковым методом и сохраняет
	отсортированный массив в outArr.

	\b Пример:
	\code{.cpp}
	int arr[] = {1, 2, 4, 3};
	int out[4];

	to_decrease(arr, 4, out);	// arr = {1, 2, 4, 3}; out = {4, 3, 2, 1};
	\endcode
*******************************************************************************/
template<typename Type>
inline void to_decrease(
	Type* arr
	, size_t const arraySize
	, Type* out
)
{
	std::array<Type, arraySize> a;
	for (int i = 0; i < arraySize; i++)
		a[i] = arr[i];

	std::sort(a.begin(), a.end(), std::less<Type>());
	for (int i = 0; i < arraySize; i++)
		out[i] = a[i];
}


/*!***************************************************************************** 
	@brief Возведение в квадрат
	@tparam T - тип переменной функции
	@param v - возводимое в квадрат значение
	@return квадрат значения
	
	Функция осуществляет возведение в квадрат (как тебе такое, Страуструп?) 
	значения переменной v типа T путем простого перемножения величины на себя.
*******************************************************************************/
template<typename T>
inline T const sqr(T const& v)
{
	return v * v;
}


/*!***************************************************************************** 
	@brief Линейная интерполяция по точкам
	@tparam T - тип перменных функции
	@param x0 - левое значение аргумента
	@param x1 - правое значение аргумента
	@param y0 - левое значение функции
	@param y1 - правое значение функции
	@param x - значение аргумента для интерполяции
	@return рассчитанное путем линейной интерполяции значение
	
	Функция предназначена для формирования линейной функции по двум заданным
	точка с координатами {x0;y0} и {x1;y1} и вычисления на ее основе значения
	типа y в точке, со значением x по оси абсцисс.

	\b Пример:
	\code{.cpp}
	\/* Задаем две точки *\/
	sreal_t x0 = 0, y0 = 0;
	sreal_t x1 = 2, y1 = 2;
	\/* Вычисляем значение функции для аргумента x = 1 *\/
	linterpolate(x0, y0, x1, y1, 1);	// -> 1
	\endcode
*******************************************************************************/
template <typename T>
inline T const linterpolate(
	  T const& x0
	, T const& x1
	, T const& y0
	, T const& y1
	, T const& x
)
{
	if (is_close(x0, x1, Const::flt_epsilon))
		return y0;

	T y = T(0);

	y = y0 + (y1 - y0) * (x - x0) / (x1 - x0);

	return y;
}


/*!***************************************************************************** 
	@brief Перечисление, определяющее в какую сторону ведется округление при 
	возникновении спорных ситуаций (например x = 1.5).
	Используется в функции rounding
	@sa rounding()
*******************************************************************************/
enum RoundingPolicy
{
      RoundUp		/**< Округление в большую сторону */
    , RoundDown		/**< Округление в меньшую сторону */
};


/*!*****************************************************************************
	@brief Округление числа до заданной точности
	@tparam T - тип перменных функции
	@param value - исходное значение
	@param decimal - минимальный делитель, к которому округляется число
	@param policy - выбранное правило округления для спорных ситуаций
	@return значение переменной после округления
	@sa RoundingPolicy

	Функция предназначена для округления значения value типа T до минимального 
	делителя decimal (например, при decimal = 0.25 число 1.73 округлится до 1.75).
	При этом, при возникновении спорных ситуаций (например число 1.5 при округлении
	до целого), сторона округления будет выбираться исходя из заданной политики 
	округления policy (по-умолчанию выбрано округление в большую сторону RoundUp).

	\b Пример:
	\code{.cpp}
	
	\endcode
*******************************************************************************/
template<typename T>
T const rounding(
	  T const& value
	, T const& decimal
	, RoundingPolicy const policy = RoundUp
)
{
	assert(decimal > 0);

	T delta = abs(value - (int)(value / decimal) * decimal);

	if (is_close(delta, 0., Const::flt_epsilon))
		return value;

	int sub_value =
		delta < 0.5 * decimal ? 0
		: is_close(delta, 0.5 * decimal, Const::flt_epsilon) && policy == RoundUp
		? 1
		: is_close(delta, 0.5 * decimal, Const::flt_epsilon) && policy == RoundDown
		? 0
		: 1;

	return sign(value) * (abs((int)(value / decimal) * decimal) + sub_value * decimal);
}

} /* namespace science */


#endif  // __LIBSCIENCE_MATH_UTILITY_HPP_INCLUDED__