/*!
********************************************************
*	@file Dialogdelete.cpp
*	@author Dmitry
*	@date Декабрь  08/12/2022
*	@brief Модуль содержит реализацию файла Dialogdelete.h
**********************************************************
*/
#include "LIDPacker/maker/Dialogs/dialogdelete.h"
#include <qheaderview.h>
Dialogdelete::Dialogdelete(QStringList names, QMap<int, QVector<sreal_t>> args_vals, int pos)
{
	ui = new Ui::DialogDel();
	Valmodel = new QStandardItemModel();
	ui->setupUi(this);

	scales = args_vals;

	ui->Args_box->addItems(names);
	ui->Args_box->setCurrentIndex(pos);

	change_table_data(pos);	

	connect(ui->btn_ok, SIGNAL(clicked()), SLOT(accept()));
	connect(ui->btn_no, SIGNAL(clicked()), SLOT(reject()));
	connect(ui->Args_box, QOverload<int>::of(&QComboBox::currentIndexChanged), this, &Dialogdelete::change_table_data);
}
const int Dialogdelete::get_pos() const
{
	return ui->Args_box->currentIndex();
}
const QVector<int> Dialogdelete::get_deleted_pos()
{
	QVector<int> p;

	auto sel = ui->tabel_vals_arg->selectionModel()->selectedIndexes();

	for (int i = 0; i < sel.size(); ++i)
		p.push_back(sel[i].column());

	return p;
}
/* PRIVATE SLOTS */
void Dialogdelete::change_table_data(int index)
{
	int num = scales[index].size();

	Valmodel->setRowCount(1);
	Valmodel->setColumnCount(num);

	for (int i = 0; i < num; ++i)
		Valmodel->setData(Valmodel->index(0, i), QString::number(scales[index][i]));

	ui->tabel_vals_arg->setModel(Valmodel);
	ui->tabel_vals_arg->verticalHeader()->setVisible(false);
}