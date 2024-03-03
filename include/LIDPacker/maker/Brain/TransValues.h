#pragma once
/*!********************************************************
*
*	@file TransValues.h
*	@author Dmitry
*	@date Февраль  02/02/2023
*	@brief Преобразоваие данных значений
*
***********************************************************/
#include <QString>
#include <list>
#include <vector>
#include <map>
#include <QStandardItemModel>
#include "Dimensions.h"
#include "Data.h"
/*!***********************************************************
*
*    @author Dmitry
*    @version 1.0
*	 @date Февраль  02/02/2023
*    @brief Класс для транспанирования значение при перестановки аргументов
*
******************************************************************/

class TransValues
{
public:
	TransValues(std::vector<QString>, std::vector<QString>);
	~TransValues();
	/*
	*   @brief void get_strk_args - используется в TreeView получает на вход позиции аргументов и их i позицию
	*	формирует часть таблицы координат значение аргументов
	*	@param std::vector<int> - аргументы
	*	@param int - строка
	*/
	const void get_strk_args(std::vector<int>, int);
	/*
	*   @brief void get_clmn_args - используется в TreeView получает на вход номер столбца, формирует полную таблицу координат значений
	*	@param int - столбец
	*/
	const void get_clmn_args(int);
	/*
	*   @brief QStandardItemModel* get_new_Arr - фомирует новую (транспонированную таблицу) на основани метода get_clmn_args
	*	@param std::vector<int> - получает порядок аргументов
	*	@param std::vector<int> - получает длинны аргументов
	*	@param std::vector<std::vector<QString>> - массив значений в таблице.
	*/
	std::vector<std::vector<sreal_t>> get_new_arr(std::vector<int>, std::vector<int>, std::vector<std::vector<sreal_t>>);

private:
	/*
	*   @brief tmpxyVal - обменник массивом таблицы
	*/
	std::vector<std::vector<sreal_t>> tmpxyVal;
	std::map<int, std::multimap<int, std::vector<int> > > colmnTab;
	std::map<int, std::multimap<int, std::vector<int> > >::iterator it_Tab;
	std::map<int, std::multimap<int, std::vector<int> > > ColmnStrTab;

	std::multimap<int, std::vector<int> > strokTab;
	std::multimap<int, std::vector<int> >::iterator it_strokTab;

	std::vector<QString> prOrd, crOrd;

	std::multimap<int, std::vector<int> > swap_args();
};