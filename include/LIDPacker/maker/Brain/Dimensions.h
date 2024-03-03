#pragma once
/*!********************************************************
* @file Dimensions.h
* @author Dmitry
* @date Январь  12/01/2023
* @brief Модуль содержит класс Dimensions
***********************************************************/
#include <vector>
#include <string>
#include <list>
#include <map>


/*!***********************************************************
*
*    @author Dmitry
*    @version 1.0
*    @date Январь  12.01.2023
*    @brief Класс Dimensions содает лист аргументов по (x;y) или наоборот
*    из файлового формата(графового и метричного).
*
******************************************************************/

class Dimensions
{
public:
	/*!
	*
	* @brief Конструктор для инициализации начальных значений
	* @param _amount - всего аргументов, также является выбором измерений
	* @param _lens - длинна каждого аргумента
	*/
	Dimensions(size_t _amount, std::vector<int> _lens);
	/*
	* @brief 
	* @param allord - текущий порядок аргументов 
	* @param curr_siz - текущие длинны в порядке allord
	*/
	Dimensions(std::vector<int> allord, std::vector<int> curr_siz);

	~Dimensions();

	/*!
	*
	* @brief ArgsByXY обрабатывает аргументы формируя список от AN до A1
	* @param x - позиция аргумента в таблице по x
	* @param y - позиция аргумента в таблице по y
	* @return тип vector, список аргументов от AN до A1
	*/
	std::vector<int> ArgsByXY(int x, int y);
	/*
	* @brief XYByArgs по аргументам находит x:y
	* @param vec - аргументы
	* @return тип vector, с vector[0] - y vector[1] - x
	*/
	std::vector<int> XYByArgs(std::vector<int>);
	/*
	* @brief AllArgsByXY возвращает таблицу где каждому x y, соотнесенны аргументы.
	*/
	std::map<int, std::vector<std::string>>	 AllArgsByXY();
private:
	/****************/
	size_t a2;
	std::vector<int> ord;
	std::vector<int> argsize;
	/****************/
	size_t amount;// кол-во аргуметов
	std::vector<int> lens;// разные(или одинаковые) длинный аргментов
	std::vector<int> position;
	std::map<int, std::vector<std::string>>	 map_y;
	std::map<int, std::vector<std::string>>	::iterator it_y;
	/*!
	* Dimensions R(1-18) это степени,
	* самое маленькое основание это 2
	* но при 2^18 программа уже не считает значения
	*/
	void Manager();
	std::string R1Cases(std::string format, int i);
	std::string R2Cases(std::string format, int i, int j);
	std::string R3Cases(std::string format, int i, int j, int k);
	std::string R4Cases(std::string format, int i, int j, int k, int z);
	std::string R5Cases(std::string format, int i, int j, int k, int z, int a);
	std::string R6Cases(std::string format, int i, int j, int k, int z, int a, int b);
	std::string R7Cases(std::string format, int i, int j, int k, int z, int a, int b, int c);
	std::string R8Cases(std::string format, int i, int j, int k, int z, int a, int b, int c, int d);
	std::string R9Cases(std::string format, int i, int j, int k, int z, int a, int b, int c, int d, int e);
	std::string R10Cases(std::string format, int i, int j, int k, int z, int a, int b, int c, int d, int e, int f);
	std::string R11Cases(std::string format, int i, int j, int k, int z, int a, int b, int c, int d, int e, int f, int g);
	std::string R12Cases(std::string format, int i, int j, int k, int z, int a, int b, int c, int d, int e, int f, int g, int h);
	std::string R13Cases(std::string format, int i, int j, int k, int z, int a, int b, int c, int d, int e, int f, int g, int h, int m);
	std::string R14Cases(std::string format, int i, int j, int k, int z, int a, int b, int c, int d, int e, int f, int g, int h, int m, int n);
	std::string R15Cases(std::string format, int i, int j, int k, int z, int a, int b, int c, int d, int e, int f, int g, int h, int m, int n, int l);
	std::string R16Cases(std::string format, int i, int j, int k, int z, int a, int b, int c, int d, int e, int f, int g, int h, int m, int n, int l, int o);
	std::string R17Cases(std::string format, int i, int j, int k, int z, int a, int b, int c, int d, int e, int f, int g, int h, int m, int n, int l, int o, int p);
	std::string R18Cases(std::string format, int i, int j, int k, int z, int a, int b, int c, int d, int e, int f, int g, int h, int m, int n, int l, int o, int p, int q);

	void R1();
	void R2();
	void R3();
	void R4();
	void R5();
	void R6();
	void R7();
	void R8();
	void R9();
	void R10();
	void R11();
	void R12();
	void R13();
	void R14();
	void R15();
	void R16();
	void R17();
	void R18();

	std::vector<int> makeAr(std::vector<int>);
	std::vector<int> makeAj(std::vector<int>);
	std::vector<int> makeSize(std::vector<int>);


};