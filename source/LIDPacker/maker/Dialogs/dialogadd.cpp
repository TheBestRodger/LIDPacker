/*!
********************************************************
*	@file DialogAdd.cpp
*	@author Dmitry
*	@date Декабрь  08/12/2022
*	@brief Модуль содержит реализацию файла DialogAdd.h
**********************************************************
*/
#include "LIDPacker/maker/Dialogs/dialogadd.h"
#include <qheaderview.h>
//#include <qstandarditemmodel.h>
DialogAdd::DialogAdd(QStringList names, QMap<int, QVector<sreal_t>> _scales, int pos)
{
	ui = new Ui::DialogAdd();
	Valmodel = new QStandardItemModel();
	ui->setupUi(this);
	scales = _scales;

	connect(ui->btn_ok, SIGNAL(clicked()), SLOT(find_sames()));
	connect(ui->btn_no, SIGNAL(clicked()), SLOT(reject()));

	connect(ui->ln_amount, &QLineEdit::textEdited, this, &DialogAdd::add_columns_tabel);
	ui->Args_box->addItems(names);
	ui->Args_box->setCurrentIndex(pos);
}

DialogAdd::~DialogAdd()
{
	delete ui;
	delete Valmodel;
}
const int DialogAdd::get_pos() const
{
	return ui->Args_box->currentIndex();
}
const QVector<sreal_t> DialogAdd::get_args() const
{
	QVector<sreal_t> args;

	for (int i = 0; i < Valmodel->columnCount(); ++i)
	{
		QModelIndex index = ui->list_vals_arg->model()->index(0, i);
		double s = ui->list_vals_arg->model()->data(index).toDouble();
		Valmodel->item(0, i)->setBackground(Qt::white);
		args.push_back(s);
	}
	return args;
}
/* PRIVATE */
void DialogAdd::add_columns_tabel(const QString& text)
{
	int num = text.toInt();
	Valmodel->setRowCount(1);
	Valmodel->setColumnCount(num);
	ui->list_vals_arg->setModel(Valmodel);
	ui->list_vals_arg->verticalHeader()->setVisible(false);
}
void DialogAdd::find_sames()
{
	int pos = get_pos();
	QVector<sreal_t> tmpA = get_args();
	bool f = true;
	for (int i = 0; i < tmpA.size(); ++i)
		for (int j = 0; j < scales[pos].size(); ++j)
			if (tmpA[i] == scales[pos][j])
			{
				Valmodel->item(0, i)->setBackground(Qt::red);
				f = false;
			}
	if(f)
		accept();
}
