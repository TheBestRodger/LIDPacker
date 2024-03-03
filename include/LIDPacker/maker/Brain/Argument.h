/*!
********************************************************
* 
*   @file   Argument.h
*   @author Kalikin D.M.
*   @date   2023/06/28
*   @brief  Все что связанно с конктерным аргументом
* 
**********************************************************
*/
#ifndef __ARG_PUBLIC__
#define __ARG_PUBLIC__
#include "LIDPacker/maker/predefine.h"

#include <science/math/interpolation/common.h>
#include "science/math/interpolation/common.h"
#include <QVector>

namespace lid {
	/*!*****************************************************************************
		@brief Конкретный аргумент, переменная типа аргумент.
		@author Kalikin D.M.
		@version 1.0
		@date 2023/06/28

		Общее хранение информации в разном виде об аргументе.
	*******************************************************************************/
class Argument
{
	/* @brief Значения аргумента. */
	QVector<sreal_t>		scale_v;
	
	/* @brief Описания аргумента. */
	QString					description_of_argument;

	/* @brief Имя аргумента.  */
	QString					name_of_argument;	
	
	/* @brief Позиция аргумент.а */
	int						pos;
	
	/* @brief Плоскость аргумента. */
	int						plain;

	/* @brief Тип сортировки аргумента. */
	bool					mod_sorting_policy;

public:
	/* @brief Конструктор по умолчанию. */
							Argument();

	/* @brief Деструктор по умолчанию. */
							~Argument();

	/* @brief Установка позиции аргумента. */
	void					set_position(const int pos);

	/* @brief Установка имени аргумента. */
	void					set_name(const char* name);

	/* @brief Установка имени аргумента. */
	void					set_name(const wchar_t* name);

	/* @brief Установка имени аргумента. */
	void					set_name(const std::wstring name);

	/* @brief Установка имени аргумента. */
	void					set_name(const std::string name);

	/* @brief Установка имени аргумента. */
	void					set_name(const QString name);

	/* @brief Установка описания аргумента. */
	void					set_description(const char* desc);

	/* @brief Установка описания аргумента. */
	void					set_description(const std::string desc);

	/* @brief Установка описания аргумента. */
	void					set_description(const wchar_t* desc);

	/* @brief Установка описания аргумента. */
	void					set_description(const std::wstring desc);

	/* @brief Установка описания аргумента. */
	void					set_description(const QString desc);

	/* @brief Установка значения в конец списка аргумента. */
	void					set_scale(const sreal_t arg);

	/* @brief Установка/изменение плоскости аргумента. */
	void					set_plain(const int);

	/* @brief Установка/изменение плоскости аргумента. */
	void					set_policy_sort(const bool);

	/* @brief Удаление последнего значения аргумента. */
	void					remove_last_scale();

	/* @brief Удаление всех значений аргумента. */
	void					remove_scales();

	/* @brief Удаление конкретного значение аргумента. */
	void					remove_scale(int pos_scale);

	/* @brief Установка всех значений аргумента. */
	void					set_full_scale(const sreal_t* arg, const int size);

	/* @brief Установка всех значений аргумента. */
	void					set_full_scale_v(const QVector<sreal_t>& arg);

	/* @brief Установка всех значений аргумента. */
	void					set_full_scale_v(const std::vector<sreal_t>& arg);

	/* @brief Получение позиции аргумента. */
	const int				get_position()		const;

	/* @brief Получение плоскость аргумента. */
	const int				get_plain()			const;

	/* @brief Получение плоскость аргумента. */
	const sreal_t			get_max_scale()		const;

	/* @brief Получение плоскость аргумента. */
	const sreal_t			get_min_scale()		const;

	/* @brief Получение имени аргумента. */
	const QString			get_name()			const;

	/* @brief Получение вида сортировки убв./ворст.*/
	const bool				get_policy_sort()   const;

	/* @brief Получение описания аргумента. */
	const QString			get_description()	const;
	
	/* @brief Получение всех значений аргумента. */
	const QVector<sreal_t>	get_full_scale_v()  const;
	
	/* @brief Сортировка вектра аргумента. */
	void					sort_argument();
};


ID_INLINE void Argument::set_position(const int _pos)
{
	if(_pos >= 0)
		pos = _pos;
}


ID_INLINE void Argument::set_scale(const sreal_t arg)
{
	scale_v.push_back(arg);
}


ID_INLINE void Argument::remove_last_scale()
{
	scale_v.remove(scale_v.size()-1);
}


ID_INLINE void Argument::remove_scales()
{
	scale_v.clear();
}


ID_INLINE void Argument::set_full_scale(const sreal_t* _arg, const int size)
{
	if(size > 0)
	for (unsigned i = 0; i < size; ++i)
		scale_v.push_back(_arg[i]);
}


ID_INLINE void Argument::set_full_scale_v(const QVector<sreal_t>& arg)
{
	scale_v = arg;
}


ID_INLINE void Argument::set_full_scale_v(const std::vector<sreal_t>& arg)
{
	scale_v = QVector<sreal_t>(arg.begin(), arg.end());
}


ID_INLINE void Argument::set_plain(const int pl)
{
	if (pl < 0)
		plain = 0;
	else
		plain = pl;
}
ID_INLINE void Argument::set_policy_sort(const bool _p)
{
	mod_sorting_policy = _p;
}

ID_INLINE const int Argument::get_position() const
{
	return pos;
}


ID_INLINE const QString Argument::get_name() const
{
	return name_of_argument;
}


ID_INLINE const QString Argument::get_description() const
{
	return description_of_argument;
}


ID_INLINE const QVector<sreal_t> Argument::get_full_scale_v() const
{
	return scale_v;
}


ID_INLINE const int Argument::get_plain() const
{
	return plain;
}
ID_INLINE const bool Argument::get_policy_sort()	const
{
	return mod_sorting_policy;
}

}// end namespace
#endif /* !__ARG_PUBLIC__ */