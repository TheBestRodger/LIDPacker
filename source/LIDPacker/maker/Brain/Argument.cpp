#include "LIDPacker/maker/Brain/Argument.h"

#include <QTextCodec>
/*!
********************************************************
* 
*   @file   Argument.cpp
*   @author Kalikin D.M. - dep.106
*   @date   Декабрь  28/06/2023
*   @brief  Реализация методов Argument.h
* 
**********************************************************
*/
namespace lid {
Argument::Argument()
	: pos(0)
	, plain(0)
	, name_of_argument("")
	, description_of_argument("")
	, mod_sorting_policy(true)
{
	//scale_v = { 0 };
}
Argument::~Argument()
{
}


void Argument::set_name(const char* name)
{
	QTextCodec* codec = QTextCodec::codecForName(CODEC);
	QString str = codec->toUnicode(name);
	name_of_argument = str;
	name_of_argument.remove("#");
}
void Argument::set_name(const wchar_t* name)
{
	QString str = QString::fromWCharArray(name);
	name_of_argument = str;
	name_of_argument.remove("#");
}
void Argument::set_name(const std::wstring name)
{
	QString str = QString::fromWCharArray(name.c_str());
	name_of_argument = str;
	name_of_argument.remove("#");
}
void Argument::set_name(const std::string name)
{
	name_of_argument = QString::fromStdString(name);
	name_of_argument.remove("#");
}
void Argument::set_name(const QString name)
{
	name_of_argument = name;
	name_of_argument.remove("#");
}

void Argument::set_description(const char* desc)
{
	QTextCodec* codec = QTextCodec::codecForName(CODEC);
	QString str = codec->toUnicode(desc);
	description_of_argument = str;
	description_of_argument.remove("#");
}
void Argument::set_description(const wchar_t* desc)
{
	QString str = QString::fromWCharArray(desc);
	description_of_argument = str;
	description_of_argument.remove("#");
}

void Argument::set_description(const std::wstring desc)
{
	QString str = QString::fromWCharArray(desc.c_str());
	description_of_argument = str;
	description_of_argument.remove("#");
}

void Argument::set_description(const std::string desc)
{
	description_of_argument = QString::fromStdString(desc);
	description_of_argument.remove("#");
}
void Argument::set_description(const QString desc)
{
	description_of_argument = desc;
	description_of_argument.remove("#");
}
void Argument::remove_scale(int pos_scale)
{
	QVector<sreal_t>::iterator it;
	it = scale_v.begin();
	std::advance(it, pos_scale);
	scale_v.erase(it);
}
void Argument::sort_argument()
{
	qSort(scale_v);
	if (!mod_sorting_policy)
		std::reverse(scale_v.begin(), scale_v.end());
}
const sreal_t Argument::get_max_scale()	const
{
	sreal_t max = scale_v[0];
	for (int i = 1; i < scale_v.size(); ++i)
		if (max < scale_v[i])
			max = scale_v[i];
	return max;
}

const sreal_t Argument::get_min_scale()	const
{
	sreal_t min = scale_v[0];
	for (int i = 1; i < scale_v.size(); ++i)
		if (min > scale_v[i])
			min = scale_v[i];
	return min;
}
}// end namespace lid
