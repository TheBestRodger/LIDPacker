/*!
********************************************************
*   @file DialogPlain.cpp
*   @author Dmitry
*   @date 17/02/2023
*   @brief Реализация dialogViewArgs.h
**********************************************************
*/
#include "LIDPacker/maker/Dialogs/DialogPlain.h"
#include <qheaderview.h>
DialogPlain::DialogPlain(QStringList names, QMap<int, QVector<sreal_t>> args_vals, int pos, QVector<int> _p)
{
	ui = new Ui::DialogPl();
	Valmodel = new QStandardItemModel();
	ui->setupUi(this);

	scales = args_vals;
	pl = _p;

	ui->Args_box->addItems(names);
	ui->Args_box->setCurrentIndex(pos);

	change_table_data(pos);

	connect(ui->btn_ok, SIGNAL(clicked()), SLOT(accept()));
	connect(ui->btn_no, SIGNAL(clicked()), SLOT(reject()));
	connect(ui->Args_box, QOverload<int>::of(&QComboBox::currentIndexChanged), this, &DialogPlain::change_table_data);
}
DialogPlain::~DialogPlain() {
	delete ui;
}
const int DialogPlain::get_plain() const
{
	return ui->tabel_vals_arg->selectionModel()->selectedIndexes()[0].column();
}
const int DialogPlain::get_pos() const
{
	return ui->Args_box->currentIndex();
}
/* PRIVATE SLOTS */
void DialogPlain::change_table_data(int index)
{
	int num = scales[index].size();

	Valmodel->clear();
	Valmodel->setRowCount(1);
	Valmodel->setColumnCount(num);

	for (int i = 0; i < num; ++i)
		Valmodel->setData(Valmodel->index(0, i), QString::number(scales[index][i]));
	
	Valmodel->item(0, pl[index])->setBackground(Qt::green);

	ui->tabel_vals_arg->setModel(Valmodel);	
	ui->tabel_vals_arg->selectionModel()->clear();
	ui->tabel_vals_arg->verticalHeader()->setVisible(false);
	ui->tabel_vals_arg->selectionModel()->setCurrentIndex(Valmodel->index(0, pl[index]), QItemSelectionModel::Select);
}
