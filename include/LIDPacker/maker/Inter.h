#pragma once
/*!
********************************************************
*   @file Viewer.h
*   @author Kalikin D.M.
*   @date 11/02/2023
*   @brief Описание методов и подключаемые библиотеки
**********************************************************
*/
#include "LIDPacker/gui/Ui_Inter.h"
#include <science/math/interpolation/interpolator.hpp>

#include <QWidget>

/*!***********************************************
*
*   @brief Класс Viewer 
*   @author Kalikin D.M.
*   @version 1.0
*   @date 11/02/2023
*
****************************************************/
namespace lid {		
	
	class Inter : public QWidget
	{
		Q_OBJECT

	public:
		explicit	Inter(QWidget* parent = nullptr);
		~Inter();
		void set_interpolator(const science::Interpolator & icz);
	private:
		Ui::InterUI* ui;
		science::Interpolator interz;
		int R;
		void MakeArgsIntervalsLayout(int R, const science::Interpolator& icz);
	private slots:
		void Step();
		void InterClick();
	};
	namespace {
		std::vector<sreal_t> Max;
		std::vector<sreal_t> Min;
		std::vector<double>  Steps;
		/**/
		void Manager(int R, const science::Interpolator& icz, QTableWidget* table_inter);
		void R1(const science::Interpolator& icz, QTableWidget* table_inter);
		void R2(const science::Interpolator& icz, QTableWidget* table_inter);
		void R3(const science::Interpolator& icz, QTableWidget* table_inter);
		void R4(const science::Interpolator& icz, QTableWidget* table_inter);
		void R5(const science::Interpolator& icz, QTableWidget* table_inter);
		void R6(const science::Interpolator& icz, QTableWidget* table_inter);
		void R7(const science::Interpolator& icz, QTableWidget* table_inter);
		/**/
	}
}