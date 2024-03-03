/*!
********************************************************
* 
*   @file   Arguments.cpp
*   @author Kalikin D.M.
*   @date	2023/06/28
*   @brief  Реализация методов Arguments.h
* 
**********************************************************
*/
#include "LIDPacker/maker/Brain/Arguments.h"
#include <QMap>
namespace lid {
idArguments::idArguments() 
{

}
const int idArguments::max_length_arg() const
{
	int max = 0;

	for (int i = 0; i < Num(); ++i)
		if (max < list[i].get_full_scale_v().size())
			max = list[i].get_full_scale_v().size();

	return max;
}
const int idArguments::amount_rows() const
{
	int sum = 1;
	for (int i = 1; i < Num(); ++i)
		sum *= list[i].get_full_scale_v().size();
	return sum;
}
const int idArguments::get_sum() const
{
	int sum = 1;
	for (int i = 0; i < Num(); ++i)
		sum *= list[i].get_full_scale_v().size();
	return sum;
}

void idArguments::swap_by_name(const QString f, const QString s)
{
	int f1, f2;
	f1 = f2 = -1;
	for (int i = 0; i < Num(); ++i)
	{
		if (list[i].get_name() == f)
			f1 = i;
		if (list[i].get_name() == s)
			f2 = i;
	}
	if (f1 != -1 && f2 != -1)
		std::swap(list[f1], list[f2]);
}
void idArguments::swap(const int A1, const int A2)
{
	std::swap(list[A1], list[A2]);
}
void idArguments::move_to(int pos_move, int where_move)
{
	int wht = pos_move;
	int wh = 0;
	if(pos_move < where_move)
		for (int i = 0; i < Num(); ++i)
		{
			if (i == where_move)
				break;
			wh++;
			std::swap(list[wht], list[wh]);
			wht++;
		}
	else
	{
		wh = pos_move;
		for (int i = Num()-1; i > 0; --i)
		{
			if (i == where_move)
				break;
			wh--;
			std::swap(list[wh], list[wht]);
			wht--;
		}
	}
}
const int idArguments::position_by_name(const QString nameofargument)
{
	for (int i = 0; i < Num(); ++i)
	{
		if (list[i].get_name() == nameofargument)
			return i;
	}
	return NULL;
}

const std::vector<int> idArguments::get_Sizes() const
{
	std::vector<int> sizes_args;
	for (int i = 0; i < Num(); ++i)
		sizes_args.push_back(list[i].get_full_scale_v().size());
	return sizes_args;
}
const QMap<int, QVector<sreal_t>> idArguments::get_AllValues() const
{
	QMap<int, QVector<sreal_t>> All;

	for (int i = 0; i < Num(); ++i)
		All[i] = list[i].get_full_scale_v();

	return All;
}
const int idArguments::get_pos(const QString nm)const
{
	for (int i = 0; i < Num(); ++i)
		if (list[i].get_name() == nm)
			return i;
	return NULL;
}
}