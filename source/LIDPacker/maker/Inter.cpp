/*!
********************************************************
*   @file Inter.cpp
*   @author Kalikin D.M.
*   @date 
*   @brief 
**********************************************************
*/
#include "LIDPacker/maker/Inter.h"
#include <science/math/interpolation/interpolator.hpp>

#include <QtConcurrent> 
namespace lid {
/* PUBLIC */
Inter::Inter(QWidget* parent)
    : QWidget(parent)
{
    ui = new Ui::InterUI;
    ui->setupUi(this);
    setAttribute(Qt::WA_DeleteOnClose);
    QObject::connect(ui->act_interpolate, SIGNAL(triggered()), SLOT(InterClick()));
}

Inter::~Inter() 
{
    //QtConcurrent::run(clear_items);
    //for_delete.clear();
    delete ui;
}
void Inter::set_interpolator(const science::Interpolator & icz)
{
    R = icz.get_arguments_count();
    interz = icz;
    Steps.resize(R);
    MakeArgsIntervalsLayout(R, icz);
    QtConcurrent::run(Manager, R, icz, ui->table_inter);
}
/* PRIVATE */
void Inter::MakeArgsIntervalsLayout(int R, const science::Interpolator& icz) 
{
    QStringList s;

    for (int i = 0; i < icz.get_arguments_count(); ++i)
        s << QString::fromWCharArray(icz.get_name_argument(i).c_str());
    s << "F";
    ui->table_inter->setColumnCount(R + 1);
    ui->table_inter->setHorizontalHeaderLabels(s);
    ui->table_inter->setRowCount(1);
    for (int i = 0; i < R; ++i)
    {

        QHBoxLayout*    H_lay       = new QHBoxLayout();
        QLineEdit*      ln_name     = new QLineEdit();
        QSpacerItem*    HSpacer1    = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);
        QSpacerItem*    HSpacer2    = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);
        QDoubleSpinBox* Spin_dw     = new QDoubleSpinBox();
        QDoubleSpinBox* Spin_up     = new QDoubleSpinBox();

        QDoubleSpinBox* Spin_step   = new QDoubleSpinBox();
        QObject::connect(Spin_step, static_cast<void (QDoubleSpinBox::*)(double)>(&QDoubleSpinBox::valueChanged), this, &Inter::Step);
        Spin_step->setObjectName(QString::number(i));

        ln_name->setText(QString::fromWCharArray(icz.get_name_argument(i).c_str()));

        auto tmp = icz.get_argument(i);
        auto max = std::max_element(tmp.begin(), tmp.end());
        auto min = std::min_element(tmp.begin(), tmp.end());

        Max.push_back(max[0]);
        Min.push_back(min[0]);
        Steps.push_back((abs(min[0]) + abs(max[0])) / 4);
        Spin_step->setValue((abs(min[0]) + abs(max[0])) / 4);
        ln_name->setFont(QFont(SHRIFT, mFON));

        Spin_dw->setFont(QFont(SHRIFT, mFON));
        Spin_dw->setMinimum(min[0]);
        Spin_dw->setMaximum(max[0]);
        Spin_dw->setValue(min[0]);

        Spin_up->setFont(QFont(SHRIFT, mFON));
        Spin_up->setMinimum(min[0]);
        Spin_up->setMaximum(max[0]);
        Spin_up->setValue(max[0]);

        Spin_step->setFont(QFont(SHRIFT, mFON));

        H_lay->addWidget(ln_name);
        H_lay->addItem(HSpacer1);
        H_lay->addWidget(Spin_dw);
        H_lay->addWidget(Spin_up);
        H_lay->addItem(HSpacer2);
        H_lay->addWidget(Spin_step);
        ui->V_lay->insertLayout(i + 1, H_lay);
    }
}
void Inter::Step()
{
    QDoubleSpinBox* cat = qobject_cast<QDoubleSpinBox*>(sender());
    Steps[cat->objectName().toInt()] = cat->value();
}
void Inter::InterClick()
{
    QtConcurrent::run(Manager, R, interz, ui->table_inter);
}
namespace {
    /**/
    void Manager(int R, const science::Interpolator& icz, QTableWidget* table_inter)
    {
        //return;
        switch (R)
        {
        case 1:
            R1(icz, table_inter);
            break;
        case 2:
            R2(icz, table_inter);
            break;
        case 3:
            R3(icz, table_inter);
            break;
        case 4:
            R4(icz, table_inter);
            break;
        case 5:
            R5(icz, table_inter);
            break;
        case 6:
            R6(icz, table_inter);
            break;
        case 7:
            R7(icz, table_inter);
            break;
        default:
            break;
        }
    }
    void R1(const science::Interpolator& icz, QTableWidget* table_inter)
    {
        return;
    }
    void R2(const science::Interpolator& icz, QTableWidget* table_inter)
    {
        int k = 0;
        for (sreal_t a = Min[0]; a <= Max[0]; a += Steps[0])
            for (sreal_t b = Min[1]; b <= Max[1]; b += Steps[1])
            {
                    QTableWidgetItem* item1 = new QTableWidgetItem();
                    QTableWidgetItem* item2 = new QTableWidgetItem();
                    QTableWidgetItem* item3 = new QTableWidgetItem();

                    item1->setData(0, a);
                    item2->setData(0, b);
                    item3->setData(0, icz(a, b));

                    table_inter->setItem(k, 0, item1);
                    table_inter->setItem(k, 1, item2);
                    table_inter->setItem(k, 2, item3);
                    k++;
                    table_inter->setRowCount(k + 1);
            }
    }
    void R3(const science::Interpolator& icz, QTableWidget* table_inter)
    {
        int k = 0;
        for (sreal_t a = Min[0]; a <= Max[0]; a += Steps[0])
            for (sreal_t b = Min[1]; b <= Max[1]; b += Steps[1])
                for (sreal_t c = Min[2]; c <= Max[2]; c += Steps[2])
                {
                    QTableWidgetItem* item1 = new QTableWidgetItem();
                    QTableWidgetItem* item2 = new QTableWidgetItem();
                    QTableWidgetItem* item3 = new QTableWidgetItem();
                    QTableWidgetItem* item4 = new QTableWidgetItem();

                    item1->setData(0, a);
                    item2->setData(0, b);
                    item3->setData(0, c);
                    item4->setData(0, icz(a, b, c));

                    table_inter->setItem(k, 0, item1);
                    table_inter->setItem(k, 1, item2);
                    table_inter->setItem(k, 2, item3);
                    table_inter->setItem(k, 3, item4);
                    k++;
                    table_inter->setRowCount(k + 1);
                }
    }
    void R4(const science::Interpolator& icz, QTableWidget* table_inter)
    {
        int k = 0;
        for (sreal_t a = Min[0]; a <= Max[0]; a += Steps[0])
            for (sreal_t b = Min[1]; b <= Max[1]; b += Steps[1])
                for (sreal_t c = Min[2]; c <= Max[2]; c += Steps[2])
                    for (sreal_t d = Min[3]; d <= Max[3]; d += Steps[3])
                    {
                        sreal_t t = Max[3];
                        QTableWidgetItem* item1 = new QTableWidgetItem();
                        QTableWidgetItem* item2 = new QTableWidgetItem();
                        QTableWidgetItem* item3 = new QTableWidgetItem();
                        QTableWidgetItem* item4 = new QTableWidgetItem();
                        QTableWidgetItem* item5 = new QTableWidgetItem();

                        item1->setData(0, a);
                        item2->setData(0, b);
                        item3->setData(0, c);
                        item4->setData(0, d);
                        item5->setData(0, icz(a, b, c, d));

                        table_inter->setItem(k, 0, item1);
                        table_inter->setItem(k, 1, item2);
                        table_inter->setItem(k, 2, item3);
                        table_inter->setItem(k, 3, item4);
                        table_inter->setItem(k, 4, item5);
                        k++;
                        table_inter->setRowCount(k + 1);
                    }
    }
    void R5(const science::Interpolator& icz, QTableWidget* table_inter)
    {
        int k = 0;
        for (sreal_t a = Min[0]; a <= Max[0]; a += Steps[0])
            for (sreal_t b = Min[1]; b <= Max[1]; b += Steps[1])
                for (sreal_t c = Min[2]; c <= Max[2]; c += Steps[2])
                    for (sreal_t d = Min[3]; d <= Max[3]; d += Steps[3])
                        for (sreal_t e = Min[4]; d <= Max[4]; d += Steps[4])
                        {
                            QTableWidgetItem* item1 = new QTableWidgetItem();
                            QTableWidgetItem* item2 = new QTableWidgetItem();
                            QTableWidgetItem* item3 = new QTableWidgetItem();
                            QTableWidgetItem* item4 = new QTableWidgetItem();
                            QTableWidgetItem* item5 = new QTableWidgetItem();
                            QTableWidgetItem* item6 = new QTableWidgetItem();

                            item1->setData(0, a);
                            item2->setData(0, b);
                            item3->setData(0, c);
                            item4->setData(0, d);
                            item5->setData(0, e);
                            item6->setData(0, icz(a, b, c, d, e));

                            table_inter->setItem(k, 0, item1);
                            table_inter->setItem(k, 1, item2);
                            table_inter->setItem(k, 2, item3);
                            table_inter->setItem(k, 3, item4);
                            table_inter->setItem(k, 4, item5);
                            table_inter->setItem(k, 4, item6);
                            k++;
                            table_inter->setRowCount(k + 1);
                    }
    }
    void R6(const science::Interpolator& icz, QTableWidget* table_inter)
    {
        int k = 0;
        for (sreal_t a = Min[0]; a <= Max[0]; a += Steps[0])
            for (sreal_t b = Min[1]; b <= Max[1]; b += Steps[1])
                for (sreal_t c = Min[2]; c <= Max[2]; c += Steps[2])
                    for (sreal_t d = Min[3]; d <= Max[3]; d += Steps[3])
                        for (sreal_t e = Min[4]; d <= Max[4]; d += Steps[4])
                            for (sreal_t f = Min[5]; f <= Max[5]; f += Steps[5])
                            {
                                QTableWidgetItem* item1 = new QTableWidgetItem();
                                QTableWidgetItem* item2 = new QTableWidgetItem();
                                QTableWidgetItem* item3 = new QTableWidgetItem();
                                QTableWidgetItem* item4 = new QTableWidgetItem();
                                QTableWidgetItem* item5 = new QTableWidgetItem();
                                QTableWidgetItem* item6 = new QTableWidgetItem();
                                QTableWidgetItem* item7 = new QTableWidgetItem();

                                item1->setData(0, a);
                                item2->setData(0, b);
                                item3->setData(0, c);
                                item4->setData(0, d);
                                item5->setData(0, e);
                                item6->setData(0, e);
                                item7->setData(0, icz(a, b, c, d, e, f));

                                table_inter->setItem(k, 0, item1);
                                table_inter->setItem(k, 1, item2);
                                table_inter->setItem(k, 2, item3);
                                table_inter->setItem(k, 3, item4);
                                table_inter->setItem(k, 4, item5);
                                table_inter->setItem(k, 5, item6);
                                table_inter->setItem(k, 6, item7);
                                k++;
                                table_inter->setRowCount(k + 1);
                            }
    }
    void R7(const science::Interpolator& icz, QTableWidget* table_inter)
    {

    }
    /**/
}
}