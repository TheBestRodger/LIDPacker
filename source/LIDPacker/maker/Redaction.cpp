/*!
********************************************************
*   @file   Redaction.cpp
*   @author Kalikin D.M.
*   @date   2023/11/03
*   @brief  Модуль содержит описание главного окна
**********************************************************
*/

#include "LIDPacker/maker/Redaction.h"
#include "LIDPacker/maker/Dialogs/dialogadd.h"
#include "LIDPacker/maker/Dialogs/dialogdelete.h"
#include "LIDPacker/maker/Brain/TransValues.h"
#include "LIDPacker/maker/Brain/Dimensions.h"
#include <LIDPacker/maker/stylesdefine.h>
#include <LIDPacker/maker/Dialogs/dialogplain.h>
#include <LIDPacker/maker/Dialogs/dialogedit.h>

#include <QMessageBox>
#include <QTextCodec>
#include <QtConcurrent> 
/*!
*************************************************
*   @author  Kalikin D.M.
*   @version 3.0
*   @date    2023/02/09
*   @brief   Режим редактирования файла
**********************************************************
*/

namespace lid {
/*
* PUBLIC
*/
Redaction::Redaction(const char* pth, QMenuBar* _menubar, QStatusBar* b, QWidget* parent)
    : count_args(-1)
    , path(pth)
{
    ui = new Ui::URedact(); 
    ui->setupUi(this);
    Args     = std::make_shared<idArguments>();
    data     = std::make_shared<Data>();
    Argmodel = std::make_shared<QStandardItemModel>();

    table = nullptr;
    bar = b;

    ui->split_lay->insertWidget(0, _menubar);
    ui->treeView->setModel(Argmodel.get());
    ui->treeView->header()->setVisible(false);
    science::Interpolator  icz;
    if (path.contains(".lid"))
        icz.set_file(path, science::BINARY);
    else if (path.contains(".txt"))
        icz.set_file(path, science::TEXT);
    else if (path.contains(".dat"))
        icz.set_file(path, science::TEXT);
    else
        return;

    ConvertDataFromInterpol(icz);
    DrawTreeArgs();
    DrawTableVals();
    SetDescFile();
    SetDescTable();

    /**/
    AllConnects();
    /**/
}
Redaction::Redaction(QMenuBar* _menubar, QStatusBar* b,  QWidget* parent)
    : count_args(-1)
{
    ui = new Ui::URedact();    
    ui->setupUi(this);
    Args     = std::make_shared<idArguments>();
    data     = std::make_shared<Data>();
    Argmodel = std::make_shared<QStandardItemModel>();
    bar = b;
    table = nullptr;

    ui->split_lay->insertWidget(0, _menubar);
    ui->treeView->setModel(Argmodel.get());
    ui->treeView->header()->setVisible(false);
    /**/
    AllConnects();
    /**/
}
Redaction::~Redaction() {
    clear();
    delete ui;
}
/****************************************************************/
void Redaction::set_path(const char* pth)
{
    /** \brief  Объект интерполяции */
    science::Interpolator  icz;
    path = pth;
    try {
        if (path.contains(".lid"))
            icz.set_file(path, science::BINARY);
        else if (path.contains(".txt"))
            icz.set_file(path, science::TEXT);
        else if (path.contains(".dat"))
            icz.set_file(path, science::TEXT);
        else
            return;

    ConvertDataFromInterpol(icz);
    DrawTreeArgs();
    DrawTableVals();
    SetDescFile();
    SetDescTable();     
    }  
    catch (std::runtime_error const& err)
    {
        QMessageBox ret;
        ret.addButton(QString::fromLocal8Bit("Ок"), QMessageBox::AcceptRole);
        ret.setText(path);
        ret.setInformativeText("Error file!");
        ret.setIcon(QMessageBox::Critical);
        if (!(ret.exec() == QMessageBox::Accepted)){}
        ret.deleteLater();
        return;
    }
}
bool Redaction::save_binaries()
{
    return Save(path);
}
bool Redaction::save_as_binaries(const char* pth)
{
    path = pth;
    return Save(path);
}
void Redaction::clear()
{
    Args->Clear();
    data->clear();
    Argmodel->clear();
    delete table;
    table = nullptr;
    path = "";
    count_args = -1;
    ui->text_desc->clear();
    ui->value_desc->clear();
}
const science::Interpolator Redaction::get_interpolator()
{
    return ConvertDataToInterpol();
}
/* PRIVATE */
/****************************************************************/
void Redaction::DrawTreeArgs()
{

    QVector<sreal_t> tmpV;

    int R = count_args = Args->Num();
    count_args--;
    Argmodel->clear();
    QObject::disconnect(Argmodel.get(), &QStandardItemModel::itemChanged, this, &Redaction::Changed_Argument);
    Argmodel->setRowCount(R);
    Argmodel->setColumnCount(Args->max_length_arg());

    for (int i = 0; i < R; ++i)
    {
        tmpV = Args->get_full_scale_v(i);
        QModelIndex index = Argmodel->index(i, 0);

        Argmodel->itemFromIndex(Argmodel->index(i, 0))->setTextAlignment(Qt::AlignCenter);
        Argmodel->itemFromIndex(Argmodel->index(i, 0))->setFont(QFont(SHRIFT, FON));

        Argmodel->setData(index, Args->get_name(i));
        Argmodel->insertColumns(0, tmpV.size(), index);
        Argmodel->insertRows(0, 1, index);

        Argmodel->itemFromIndex(index)->setDropEnabled(false);

        for (int j = 0; j < tmpV.size(); ++j)
            Argmodel->setData(Argmodel->index(0, j, index), QString::number(tmpV[j]), Qt::DisplayRole);

        tmpV.clear();
    }   
    QObject::connect(Argmodel.get(), &QStandardItemModel::itemChanged, this, &Redaction::Changed_Argument);

}
void Redaction::DrawTableVals()
{
    const QVector<QVector<sreal_t>> tmpD = data->get_dataX2q();// Табличные данные  
    const QVector<sreal_t> tmpA1 = Args->get_full_scale_v(0);
    int k = 0;
    int l = Args->amount_rows();
    int lA1 = Args->get_full_scale_v(0).size();
    int num = Args->Num();
    int LA = num - 1 + lA1;//пропуск первых столбцов

    Valmodel  = std::make_shared<QStandardItemModel>(l, LA);
    header_H  = new QHeaderView(Qt::Horizontal);
    Headmodel = std::make_shared<QStandardItemModel>(0, LA);

    for (unsigned i = 0; i < l; ++i)
    {
        k = 0;
        for (unsigned j = num - 1; j < LA; ++j) {
            Valmodel->setData(Valmodel->index(i, j), QString::number(tmpD[i][k]));
            Valmodel->itemFromIndex(Valmodel->index(i, j))->setFont(QFont(SHRIFT, mFON));
            ++k;
        }
    }


    k = 0;
    int count = 0;

    for (unsigned i = 0; i < LA; ++i)
    {

        if (count < num - 1)
        {
            Headmodel->setHeaderData(i, Qt::Horizontal, Args->get_name(num - count - 1)); /* Имена колонок */
        }
        else
        {
            Headmodel->setHeaderData(i, Qt::Horizontal, tmpA1[k]); /* Значение аргумент А1*/
            k++;
        }
        count++;
    }
    header_H->setModel(Headmodel.get());
    header_H->setSectionsClickable(true);
    header_H->setFont(QFont(SHRIFT, FON));
    table = new TableView();
    QObject::connect(table, &QTableView::clicked, this, &Redaction::SetWhatArgInTable);
    table->setModel(Valmodel.get());
    table->setHorizontalHeader(header_H);
    table->resize(1000, 2000);
    //table->verticalHeader()->setVisible(false);//true
    QtConcurrent::run(manager_table,num, Args.get(), Valmodel.get(), table);
    QObject::connect(Valmodel.get(), &QStandardItemModel::itemChanged, this, &Redaction::Save_Data_Table);
    for(int i = 0; i < num - 1; ++i)/* Уменьшение размера колонок */
        table->setColumnWidth(i, 60);

    ui->split_lay->addWidget(table);

}
void Redaction::SetDescFile()
{
    QString str = data->get_desc_file();
    str.remove("#");
    ui->text_desc->setPlainText(str);
}
void Redaction::SetDescTable()
{
    QString str = data->get_name_tdata();
    str.remove("#");
    ui->value_desc->setPlainText(str);
}
/****************************************************************/
void Redaction::ConvertDataFromInterpol(science::Interpolator& icz)
{
    int num = icz.get_arguments_count();
    data->set_datax1(icz.get_values());
    for (int i = 0; i < num; ++i)
    {
        std::unique_ptr<Argument> arg = std::make_unique<Argument>();
        arg->set_name(icz.get_name_argument(i).c_str());
        arg->set_description(icz.get_description_argument(i).c_str());
        arg->set_position(i);
        arg->set_full_scale_v(icz.get_argument(i));
        Args->Append(*arg);
    }
    data->convert_n1_to_n2(Args->get_full_scale_v(0).size());
    data->set_desc_file(icz.get_description_file().c_str());
    data->set_name_tdata(icz.get_description_table().c_str());
}
science::Interpolator Redaction::ConvertDataToInterpol()
{
    int n = Args->Num();
    if (n <= 0)
        return nullptr;
    science::Interpolator  icz;
    icz.make_data(n);
    QString s1 = ui->text_desc->toPlainText();
    QString s2 = ui->value_desc->toPlainText();
    if (s1 == "")
        s1 = " ";
    if (s2 == "")
        s2 = " ";
    data->set_desc_file(s1);
    data->set_name_tdata(s2);
    icz.set_description_file(data->get_desc_file().toStdWString());
    for (int i = 0; i < n; ++i)
    {
        icz.set_argument(i, Args->get_full_scale_v(i).toStdVector());
        icz.set_name_argument(i,Args->get_name(i).toStdWString());
        icz.set_description_argument(i, Args->get_description(i).toStdWString());
    }
    icz.set_description_table(data->get_name_tdata().toStdWString());
    data->convert_n2_to_n1(Args->get_full_scale_v(0).size());
    icz.set_values(data->get_datax1_v());
    return icz;
}
bool Redaction::Save(const char* pth)
{    
    if (pth == "")
        return false;
    if (Args->Num() <= 0)
        return false;

    ConvertDataToInterpol().dump(pth, science::BINARY);
    return true;
}
/****************************************************************/
bool Redaction::CheckPositionArgs()
{   
    int i = 0, ks = 0;
    bool f = false;
    while (ks < Args->Num()) {
        if (Argmodel->index(i, 0).data().toString() != " " && Argmodel->index(i, 0).data().toString() != "") {
            if (Args->get_name(ks) != Argmodel->index(i, 0).data().toString())
                f = true;    
            ks++;
        }
        ++i;
    }
    return f;
}
int  Redaction::TransTable()
{
    int last = NULL;
    std::vector<int> prev_lens;
    std::vector<int> curr_lens;
    std::vector<int> AllOr;
    std::vector<QString> curr_Nameargs;
    std::vector<QString> prev_Nameargs;
    int x, y;
    x = 1;
    y = 0;
    for (int i = 0; i < Args->Num(); ++i)
    {
        prev_lens.push_back(Args->get_full_scale_v(i).size());
        AllOr.push_back(i);
        curr_Nameargs.push_back(Argmodel->index(i, 0).data().toString());

        int u = Argmodel->itemFromIndex(Argmodel->index(i, 0))->columnCount();

        if (i > 0)
            x *= u;
        else
            y = u;

        curr_lens.push_back(u);
        prev_Nameargs.push_back(Args->get_name(i));
    }

    Dimensions* dem  = new Dimensions(Args->Num(), curr_lens);

    TransValues* trn = new TransValues(prev_Nameargs/*Args->get_prevNames()*/, curr_Nameargs);

    for (int k = 0; k < y; ++k) {
        for (int i = 0; i < x; ++i) {
            for (int j = k; j < y - (y - k - 1); ++j) {
                trn->get_strk_args(dem->ArgsByXY(j, i), i);
            }
        }
        trn->get_clmn_args(k);
    }

    data->set_datax2(trn->get_new_arr(AllOr, prev_lens, data->get_dataX2v()));

    delete trn;
    delete dem;
    return 0;
}
/****************************************************************/
void Redaction::ChangeValModel()
{
    const QVector<QVector<sreal_t>> tmpD = data->get_dataX2q();// Табличные данные
    const QVector<sreal_t> tmpA1 = Args->get_full_scale_v(0); // Значения первого аргумента для заголовка

    const int length_row = tmpD.size(); // Кол-во строк
    const int size_of_A1 = Args->get_full_scale_v(0).size(); // Кол-во значение у первого элемента
    const int num = Args->Num(); // Всего аргументов
    const int LA = num - 1 + size_of_A1; // Пропуск столбцов с информаций (начало табличных значений)

    int k = 0; // Независимый счетчик
    QObject::disconnect(Valmodel.get(), &QStandardItemModel::itemChanged, this, &Redaction::Save_Data_Table);
    Valmodel->clear();
    Headmodel->clear();
    if (num == 0)
        return;
    Valmodel->setRowCount(length_row);
    Valmodel->setColumnCount(LA);
    Headmodel->setRowCount(0);
    Headmodel->setColumnCount(LA);

    for (unsigned i = 0; i < length_row; ++i)
    {
        k = 0;
        for (unsigned j = num - 1; j < LA; ++j) {
            Valmodel->setData(Valmodel->index(i, j), QString::number(tmpD[i][k]));
            Valmodel->itemFromIndex(Valmodel->index(i, j))->setFont(QFont(SHRIFT, mFON));
            ++k;
        }
    }

    k = 0;
    int count = 0;

    for (unsigned i = 0; i < LA; ++i)
    {
        if (count < num - 1)
        {
            Headmodel->setHeaderData(i, Qt::Horizontal, Args->get_name(num - count - 1)); /* Имена колонок */
        }
        else
        {
            Headmodel->setHeaderData(i, Qt::Horizontal, tmpA1[k]); /* Значение аргумент А1*/
            k++;
        }
        count++;
    }
    header_H->setModel(Headmodel.get());
    header_H->setSectionsClickable(true);
    header_H->setFont(QFont(SHRIFT, FON));

    QObject::disconnect(table, &QTableView::clicked, this, &Redaction::SetWhatArgInTable);
    QObject::connect(table, &QTableView::clicked, this, &Redaction::SetWhatArgInTable);

    table->setModel(Valmodel.get());
    table->setHorizontalHeader(header_H);
    ///table->verticalHeader()->setVisible(false);//trueъ
    QtConcurrent::run(manager_table, num, Args.get(), Valmodel.get(), table);
    QObject::connect(Valmodel.get(), &QStandardItemModel::itemChanged, this, &Redaction::Save_Data_Table);
    for (int i = 0; i < num - 1; ++i)/* Уменьшение размера колонок */
        table->setColumnWidth(i, 60);

}
void Redaction::SaveChangesOfArgument(int pos)
{
    int DEFCOL = 2;// Миниму создание аргумента начинается от двух значений 
    if (pos >= Args->Num())//Не существует объекта его нужно создать
    {
        QString name, vals;
        std::unique_ptr<Argument> arg = std::make_unique<Argument>();
        QModelIndex index = Argmodel->index(pos, 0);

        arg->set_name(Argmodel->data(index).toString());
        arg->set_description(Argmodel->data(index).toString());

        for (int j = 0; j < DEFCOL; ++j)
            arg->set_scale(Argmodel->data(Argmodel->index(0, j, index)).toDouble());

        Args->Insert(*arg, pos);
    }
    else// Уже существует объект аргумент и его нужно только изменить
    {
        QString name, vals;

        QModelIndex index = Argmodel->index(pos, 0);

        Args->set_name(pos, Argmodel->data(index).toString());
        Args->set_description(pos, Argmodel->data(index).toString());
        Args->remove_scales(pos);

        for (int j = 0; j < Argmodel->columnCount(index); ++j)
            Args->set_scale(pos, Argmodel->data(Argmodel->index(0, j, index)).toDouble());
    }

}
void Redaction::SaveFullChangesOfArguments()
{
    int R = Argmodel->rowCount();

    QObject::disconnect(Argmodel.get(), &QStandardItemModel::itemChanged, this, &Redaction::Changed_Argument);
    for (int i = 0; i < R; ++i) //Сохраняем все аргументы
    {
        std::unique_ptr<Argument> arg = std::make_unique<Argument>();
        QModelIndex index = Argmodel->index(i, 0);

        arg->set_name(Argmodel->data(index).toString());
        arg->set_description(Args->get_description(i));
        arg->set_plain(Args->get_plain(i));
        arg->set_policy_sort(Args->get_sort_policy(i));
        arg->set_position(i);

        int clmn = Argmodel->columnCount(index);

        for (int j = 0; j < clmn; ++j)
            arg->set_scale(Argmodel->data(Argmodel->index(0, j, index)).toDouble());

        Args->RemoveIndex(i);
        Args->Insert(*arg, i);

        Args->sort_argument(i);

        for (int j = 0; j < clmn; ++j)
            Argmodel->setData(Argmodel->index(0, j, index), QString::number(Args->get_full_scale_v(i)[j]));
    }

    ui->treeView->update();
    QObject::connect(Argmodel.get(), &QStandardItemModel::itemChanged, this, &Redaction::Changed_Argument);
}
void Redaction::SaveFullChangesOfArgumentsAfterTrans()
{
    int R = Argmodel->rowCount();
    QMap<QString, int> plains;
    QMap<QString, bool> policy;
    QMap<QString, QString> desc;

    // Временное решение (надеюсь)
    for (int i = 0; i < R; ++i)
    {
        QString name_tmp = Args->get_name(i);
        int tmp_pl = Args->get_plain(i);
        plains.insert(name_tmp, tmp_pl);
        bool tmp_po = Args->get_sort_policy(i);
        policy.insert(name_tmp, tmp_po);
        QString desc_tmp = Args->get_description(i);
        desc.insert(name_tmp, desc_tmp);
    }
    Args->Clear();
    QObject::disconnect(Argmodel.get(), &QStandardItemModel::itemChanged, this, &Redaction::Changed_Argument);
    for (int i = 0; i < R; ++i) //Сохраняем все аргументы
    {
        std::unique_ptr<Argument> arg = std::make_unique<Argument>();
        QModelIndex index = Argmodel->index(i, 0);

        QString name_tmp = Argmodel->data(index).toString();
        int tmp_pl = plains.find(name_tmp).value();
        bool tmp_po = policy.find(name_tmp).value();
        QString desc_tmp = desc.find(name_tmp).value();

        arg->set_name(name_tmp);
        arg->set_description(desc_tmp);
        arg->set_plain(tmp_pl);
        arg->set_policy_sort(tmp_po);
        arg->set_position(i);
        int clmn = Argmodel->columnCount(index);
        for (int j = 0; j < clmn; ++j)
            arg->set_scale(Argmodel->data(Argmodel->index(0, j, index)).toDouble());

        Args->Append(*arg);

        Args->sort_argument(i);

        // Обновление модели
        for (int j = 0; j < clmn; ++j)
            Argmodel->setData(Argmodel->index(0, j, index), QString::number(Args->get_full_scale_v(i)[j]));
    }

    ui->treeView->update();
    QObject::connect(Argmodel.get(), &QStandardItemModel::itemChanged, this, &Redaction::Changed_Argument);
}
void Redaction::HandMoveArgToPos(int pos_arg, int pos_in, bool f)
{
    std::vector<int> prev_lens;
    QVector<int> curr_lens;
    std::vector<int> AllOr;
    QVector<QString> curr_Nameargs;
    std::vector<QString> prev_Nameargs;
    std::vector<QString>::iterator it;
    int x, y;
    x = 1;
    for (int i = 0; i < Args->Num(); ++i)
    {
        prev_lens.push_back(Args->get_full_scale_v(i).size());            
        prev_Nameargs.push_back(Args->get_name(i));
        AllOr.push_back(i);

        if (i != pos_arg)
        {
            curr_Nameargs.push_back(Argmodel->index(i, 0).data().toString());

            int u = Argmodel->itemFromIndex(Argmodel->index(i, 0))->columnCount();

            curr_lens.push_back(u);
        }
    }

    curr_Nameargs.insert(pos_in, Argmodel->index(pos_arg, 0).data().toString());

    int u = Argmodel->itemFromIndex(Argmodel->index(pos_arg, 0))->columnCount();

    curr_lens.insert(pos_in, u);

    for (int i = 1; i < curr_lens.size(); ++i)
        x *= curr_lens[i];

    if (f)
        y = Args->get_full_scale_v(1).size();
    else
        y = prev_lens[pos_arg];

    Dimensions* dem = new Dimensions(Args->Num(), curr_lens.toStdVector());

    TransValues* trn = new TransValues(prev_Nameargs, curr_Nameargs.toStdVector());

    for (int k = 0; k < y; ++k) {
        for (int i = 0; i < x; ++i) {
            for (int j = k; j < y - (y - k - 1); ++j) {
                trn->get_strk_args(dem->ArgsByXY(j, i), i);
            }
        }
        trn->get_clmn_args(k);
    }

    data->set_datax2(trn->get_new_arr(AllOr, prev_lens, data->get_dataX2v()));
    Args->move_to(pos_arg, pos_in);
    delete trn;
    delete dem;
}
/****************************************************************/
namespace {
    void manager_table(int R, const idArguments* Args, QStandardItemModel* Valmodel, TableView* table)
    {
        switch (R)
        {
        case 1:
            add_R1_table(Args, Valmodel, table);
            break;
        case 2:
            add_R2_table(Args, Valmodel, table);
            break;
        case 3:
            add_R3_table(Args, Valmodel, table);
            break;
        case 4:
            add_R4_table(Args, Valmodel, table);
            break;
        case 5:
            add_R5_table(Args, Valmodel, table);
            break;
        case 6:
            add_R6_table(Args, Valmodel, table);
            break;
        case 7:
            add_R7_table(Args, Valmodel, table);
            break;
        default:
            break;
        }
    }
    /*
    =============
    Работа метода setSpan (откуда, на сколько, столбец, строка) в R строка всегда 1, столбец по аргументам
    =============
    */
    void add_R1_table(const idArguments* Args, QStandardItemModel* Valmodel, TableView* table)
    {

    }
    /**/
    void add_R2_table(const idArguments* Args, QStandardItemModel* Valmodel, TableView* table)
    {
        int size_A2 = Args->get_full_scale_v(1).size();
        for (int i = 0; i < size_A2; ++i)
        {
            Valmodel->setData(Valmodel->index(i, 0), Args->get_full_scale_v(1)[i]);//2
            Valmodel->itemFromIndex(Valmodel->index(i, 0))->setFont(QFont(SHRIFT, FON + 10));
            Valmodel->itemFromIndex(Valmodel->index(i, 0))->setEditable(false);
            Valmodel->itemFromIndex(Valmodel->index(i, 0))->setTextAlignment(Qt::AlignCenter);
        }
    }
    /**/
    void add_R3_table(const idArguments* Args, QStandardItemModel* Valmodel, TableView* table)
    {
        int size_A2 = Args->get_full_scale_v(1).size();
        int size_A3 = Args->get_full_scale_v(2).size();

        int II = 0;

        table->setSpan(0, 0, size_A2, 1);


        for (int i = 0; i < size_A3; ++i)
        {
            for (int j = 0; j < size_A2; ++j, ++II)
            {
                Valmodel->setData(Valmodel->index(II, 0), Args->get_full_scale_v(2)[i]);//3
                Valmodel->setData(Valmodel->index(II, 1), Args->get_full_scale_v(1)[j]);//2
                Valmodel->itemFromIndex(Valmodel->index(II, 0))->setFont(QFont(SHRIFT, FON + 10));
                Valmodel->itemFromIndex(Valmodel->index(II, 0))->setEditable(false);
                Valmodel->itemFromIndex(Valmodel->index(II, 0))->setTextAlignment(Qt::AlignCenter);
                Valmodel->itemFromIndex(Valmodel->index(II, 1))->setFont(QFont(SHRIFT, FON + 7));
                Valmodel->itemFromIndex(Valmodel->index(II, 1))->setEditable(false);
                Valmodel->itemFromIndex(Valmodel->index(II, 1))->setTextAlignment(Qt::AlignCenter);
            }
            table->setSpan(II - size_A2, 0, size_A2, 1);
        }
    }
    /**/
    void add_R4_table(const idArguments* Args, QStandardItemModel* Valmodel, TableView* table)
    {
        int size_A2 = Args->get_full_scale_v(1).size();
        int size_A3 = Args->get_full_scale_v(2).size();
        int size_A4 = Args->get_full_scale_v(3).size();
        int II = 0;
        table->setSpan(0, 1, size_A2, 1);
        table->setSpan(0, 0, size_A2 * size_A3, 1);
        for (int i = 0; i < size_A4; ++i)
        {
            for (int j = 0; j < size_A3; ++j)
            {
                for (int k = 0; k < size_A2; ++k, ++II)
                {
                    Valmodel->setData(Valmodel->index(II, 0), Args->get_full_scale_v(3)[i]);//4
                    Valmodel->setData(Valmodel->index(II, 1), Args->get_full_scale_v(2)[j]);//3
                    Valmodel->setData(Valmodel->index(II, 2), Args->get_full_scale_v(1)[k]);//2
                    Valmodel->itemFromIndex(Valmodel->index(II, 0))->setFont(QFont(SHRIFT, FON + 10));
                    Valmodel->itemFromIndex(Valmodel->index(II, 0))->setEditable(false);
                    Valmodel->itemFromIndex(Valmodel->index(II, 0))->setTextAlignment(Qt::AlignCenter);
                    Valmodel->itemFromIndex(Valmodel->index(II, 1))->setFont(QFont(SHRIFT, FON + 7));
                    Valmodel->itemFromIndex(Valmodel->index(II, 1))->setEditable(false);
                    Valmodel->itemFromIndex(Valmodel->index(II, 1))->setTextAlignment(Qt::AlignCenter);
                    Valmodel->itemFromIndex(Valmodel->index(II, 2))->setFont(QFont(SHRIFT, FON + 5));
                    Valmodel->itemFromIndex(Valmodel->index(II, 2))->setEditable(false);
                    Valmodel->itemFromIndex(Valmodel->index(II, 2))->setTextAlignment(Qt::AlignCenter);
                }
                table->setSpan(II - size_A2, 1, size_A2, 1);
            }
            table->setSpan(II - size_A3 * size_A2, 0, size_A3 * size_A2, 1);
        }

    }
    /**/
    void add_R5_table(const idArguments* Args, QStandardItemModel* Valmodel, TableView* table)
    {
        int size_A2 = Args->get_full_scale_v(1).size();
        int size_A3 = Args->get_full_scale_v(2).size();
        int size_A4 = Args->get_full_scale_v(3).size();
        int size_A5 = Args->get_full_scale_v(4).size();
        int II = 0;
        table->setSpan(0, 2, size_A2, 1);
        table->setSpan(0, 1, size_A2 * size_A3, 1);
        table->setSpan(0, 0, size_A2 * size_A3 * size_A4, 1);
        for (int c = 0; c < size_A5; ++c)
        {
            for (int i = 0; i < size_A4; ++i)
            {
                for (int j = 0; j < size_A3; ++j)
                {
                    for (int k = 0; k < size_A2; ++k, ++II)
                    {
                        Valmodel->setData(Valmodel->index(II, 0), Args->get_full_scale_v(4)[c]);//5
                        Valmodel->setData(Valmodel->index(II, 1), Args->get_full_scale_v(3)[i]);//4
                        Valmodel->setData(Valmodel->index(II, 2), Args->get_full_scale_v(2)[j]);//3
                        Valmodel->setData(Valmodel->index(II, 3), Args->get_full_scale_v(1)[k]);//2
                        Valmodel->itemFromIndex(Valmodel->index(II, 0))->setFont(QFont(SHRIFT, FON + 10));
                        Valmodel->itemFromIndex(Valmodel->index(II, 0))->setEditable(false);
                        Valmodel->itemFromIndex(Valmodel->index(II, 0))->setTextAlignment(Qt::AlignCenter);
                        Valmodel->itemFromIndex(Valmodel->index(II, 1))->setFont(QFont(SHRIFT, FON + 7));
                        Valmodel->itemFromIndex(Valmodel->index(II, 1))->setEditable(false);
                        Valmodel->itemFromIndex(Valmodel->index(II, 1))->setTextAlignment(Qt::AlignCenter);
                        Valmodel->itemFromIndex(Valmodel->index(II, 2))->setFont(QFont(SHRIFT, FON + 5));
                        Valmodel->itemFromIndex(Valmodel->index(II, 2))->setEditable(false);
                        Valmodel->itemFromIndex(Valmodel->index(II, 2))->setTextAlignment(Qt::AlignCenter);
                        Valmodel->itemFromIndex(Valmodel->index(II, 3))->setFont(QFont(SHRIFT, FON + 5));
                        Valmodel->itemFromIndex(Valmodel->index(II, 3))->setEditable(false);
                        Valmodel->itemFromIndex(Valmodel->index(II, 3))->setTextAlignment(Qt::AlignCenter);
                    }
                    table->setSpan(II - size_A2, 2, size_A2, 1);
                }
                table->setSpan(II - size_A3 * size_A2, 1, size_A3 * size_A2, 1);
            }
            table->setSpan(II - size_A4 * size_A3 * size_A2, 0, size_A4 * size_A3 * size_A2, 1);
        }
    }
    /**/
    void add_R6_table(const idArguments* Args, QStandardItemModel* Valmodel, TableView* table)
    {
        int size_A2 = Args->get_full_scale_v(1).size();
        int size_A3 = Args->get_full_scale_v(2).size();
        int size_A4 = Args->get_full_scale_v(3).size();
        int size_A5 = Args->get_full_scale_v(4).size();
        int size_A6 = Args->get_full_scale_v(5).size();
        int II = 0;
        table->setSpan(0, 3, size_A2, 1);
        table->setSpan(0, 2, size_A2 * size_A3, 1);
        table->setSpan(0, 1, size_A2 * size_A3 * size_A4, 1);
        table->setSpan(0, 0, size_A2 * size_A3 * size_A4 * size_A5, 1);
        for (int a = 0; a < size_A6; ++a)
        {
            for (int c = 0; c < size_A5; ++c)
            {
                for (int i = 0; i < size_A4; ++i)
                {
                    for (int j = 0; j < size_A3; ++j)
                    {
                        for (int k = 0; k < size_A2; ++k, ++II)
                        {
                            Valmodel->setData(Valmodel->index(II, 0), Args->get_full_scale_v(5)[a]);//6
                            Valmodel->setData(Valmodel->index(II, 1), Args->get_full_scale_v(4)[c]);//5
                            Valmodel->setData(Valmodel->index(II, 2), Args->get_full_scale_v(3)[i]);//4
                            Valmodel->setData(Valmodel->index(II, 3), Args->get_full_scale_v(2)[j]);//3
                            Valmodel->setData(Valmodel->index(II, 4), Args->get_full_scale_v(1)[k]);//2
                            Valmodel->itemFromIndex(Valmodel->index(II, 0))->setFont(QFont(SHRIFT, FON + 10));
                            Valmodel->itemFromIndex(Valmodel->index(II, 0))->setEditable(false);
                            Valmodel->itemFromIndex(Valmodel->index(II, 0))->setTextAlignment(Qt::AlignCenter);
                            Valmodel->itemFromIndex(Valmodel->index(II, 1))->setFont(QFont(SHRIFT, FON + 7));
                            Valmodel->itemFromIndex(Valmodel->index(II, 1))->setEditable(false);
                            Valmodel->itemFromIndex(Valmodel->index(II, 1))->setTextAlignment(Qt::AlignCenter);
                            Valmodel->itemFromIndex(Valmodel->index(II, 2))->setFont(QFont(SHRIFT, FON + 5));
                            Valmodel->itemFromIndex(Valmodel->index(II, 2))->setEditable(false);
                            Valmodel->itemFromIndex(Valmodel->index(II, 2))->setTextAlignment(Qt::AlignCenter);
                            Valmodel->itemFromIndex(Valmodel->index(II, 3))->setFont(QFont(SHRIFT, FON + 5));
                            Valmodel->itemFromIndex(Valmodel->index(II, 3))->setEditable(false);
                            Valmodel->itemFromIndex(Valmodel->index(II, 3))->setTextAlignment(Qt::AlignCenter);
                            Valmodel->itemFromIndex(Valmodel->index(II, 4))->setFont(QFont(SHRIFT, FON + 5));
                            Valmodel->itemFromIndex(Valmodel->index(II, 4))->setEditable(false);
                            Valmodel->itemFromIndex(Valmodel->index(II, 4))->setTextAlignment(Qt::AlignCenter);
                        }
                        table->setSpan(II - size_A2, 3, size_A2, 1);
                    }
                    table->setSpan(II - size_A3 * size_A2, 2, size_A3 * size_A2, 1);
                }
                table->setSpan(II - size_A4 * size_A3 * size_A2, 1, size_A4 * size_A3 * size_A2, 1);
            }
            table->setSpan(II - size_A5 * size_A4 * size_A3 * size_A2, 0, size_A5 * size_A4 * size_A3 * size_A2, 1);
        }

    }
    /**/
    void add_R7_table(const idArguments* Args, QStandardItemModel* Valmodel, TableView* table)
    {
        int size_A2 = Args->get_full_scale_v(1).size();
        int size_A3 = Args->get_full_scale_v(2).size();
        int size_A4 = Args->get_full_scale_v(3).size();
        int size_A5 = Args->get_full_scale_v(4).size();
        int size_A6 = Args->get_full_scale_v(5).size();
        int size_A7 = Args->get_full_scale_v(6).size();
        int II = 0;
        table->setSpan(0, 4, size_A2, 1);
        table->setSpan(0, 3, size_A2 * size_A3, 1);
        table->setSpan(0, 2, size_A2 * size_A3 * size_A4, 1);
        table->setSpan(0, 1, size_A2 * size_A3 * size_A4 * size_A5, 1);
        table->setSpan(0, 0, size_A2 * size_A3 * size_A4 * size_A5 * size_A6, 1);
        for (int b = 0; b < size_A7; ++b)
        {
            for (int a = 0; a < size_A6; ++a)
            {
                for (int c = 0; c < size_A5; ++c)
                {
                    for (int i = 0; i < size_A4; ++i)
                    {
                        for (int j = 0; j < size_A3; ++j)
                        {
                            for (int k = 0; k < size_A2; ++k, ++II)
                            {
                                Valmodel->setData(Valmodel->index(II, 0), Args->get_full_scale_v(6)[b]);//7
                                Valmodel->setData(Valmodel->index(II, 1), Args->get_full_scale_v(5)[a]);//6
                                Valmodel->setData(Valmodel->index(II, 2), Args->get_full_scale_v(4)[c]);//5
                                Valmodel->setData(Valmodel->index(II, 3), Args->get_full_scale_v(3)[i]);//4
                                Valmodel->setData(Valmodel->index(II, 4), Args->get_full_scale_v(2)[j]);//3
                                Valmodel->setData(Valmodel->index(II, 5), Args->get_full_scale_v(1)[k]);//2
                                Valmodel->itemFromIndex(Valmodel->index(II, 0))->setFont(QFont(SHRIFT, FON + 10));
                                Valmodel->itemFromIndex(Valmodel->index(II, 0))->setEditable(false);
                                Valmodel->itemFromIndex(Valmodel->index(II, 0))->setTextAlignment(Qt::AlignCenter);
                                Valmodel->itemFromIndex(Valmodel->index(II, 1))->setFont(QFont(SHRIFT, FON + 7));
                                Valmodel->itemFromIndex(Valmodel->index(II, 1))->setEditable(false);
                                Valmodel->itemFromIndex(Valmodel->index(II, 1))->setTextAlignment(Qt::AlignCenter);
                                Valmodel->itemFromIndex(Valmodel->index(II, 2))->setFont(QFont(SHRIFT, FON + 5));
                                Valmodel->itemFromIndex(Valmodel->index(II, 2))->setEditable(false);
                                Valmodel->itemFromIndex(Valmodel->index(II, 2))->setTextAlignment(Qt::AlignCenter);
                                Valmodel->itemFromIndex(Valmodel->index(II, 3))->setFont(QFont(SHRIFT, FON + 5));
                                Valmodel->itemFromIndex(Valmodel->index(II, 3))->setEditable(false);
                                Valmodel->itemFromIndex(Valmodel->index(II, 3))->setTextAlignment(Qt::AlignCenter);
                                Valmodel->itemFromIndex(Valmodel->index(II, 4))->setFont(QFont(SHRIFT, FON + 5));
                                Valmodel->itemFromIndex(Valmodel->index(II, 4))->setEditable(false);
                                Valmodel->itemFromIndex(Valmodel->index(II, 4))->setTextAlignment(Qt::AlignCenter);
                                Valmodel->itemFromIndex(Valmodel->index(II, 5))->setFont(QFont(SHRIFT, FON + 5));
                                Valmodel->itemFromIndex(Valmodel->index(II, 5))->setEditable(false);
                                Valmodel->itemFromIndex(Valmodel->index(II, 5))->setTextAlignment(Qt::AlignCenter);
                            }
                            table->setSpan(II - size_A2, 4, size_A2, 1);
                        }
                        table->setSpan(II - size_A3 - size_A2, 3, size_A3 * size_A2, 1);
                    }
                    table->setSpan(II - size_A4 - size_A3 - size_A2, 2, size_A4 * size_A3 * size_A2, 1);
                }
                table->setSpan(II - size_A5 - size_A4 - size_A3 - size_A2, 1, size_A5 * size_A4 * size_A3 * size_A2, 1);
            }
            table->setSpan(II - size_A6 * size_A5 * size_A4 * size_A3 * size_A2, 0, size_A6 * size_A5 * size_A4 * size_A3 * size_A2, 1);
        }
    }
}
/****************************************************************/
/* PROTECTED SLOTS */
void Redaction::showContextMenu(QPoint pos)
{
    if (Args->Num() <= 0)
        return;
    ui->menu_arg->popup(ui->treeView->viewport()->mapToGlobal(pos));
    int pos_a = ui->treeView->selectionModel()->currentIndex().row();

    QTextCodec* codec = QTextCodec::codecForName(CODEC);
    
    bool p = Args->get_sort_policy(pos_a);
    if (p)
    {
        QString str = codec->toUnicode("Сортировка по возрастанию");
        ui->modSorting->setText(str);
    }
    else
    {
        QString str = codec->toUnicode("Сортировка по убыванию");
        ui->modSorting->setText(str);
    }
}
/* PRIVATE SLOTS */
/****************************************************************/
/* Автоматическое сохранение/получение информации в процессе работы */
void Redaction::Changed_Argument(QStandardItem* item)
{
    if (Args->Num() >= 1 && (Argmodel->rowCount() == Args->Num()))
    {
        SaveFullChangesOfArguments();

        if (table == nullptr)
            DrawTableVals();
        else
            ChangeValModel();
    }
}
void Redaction::Save_Data_Table(QStandardItem* item)
{
    Args->Num();
    int i = item->row();
    int j = item->column();    
    sreal_t tmp = (sreal_t)Valmodel->data(Valmodel->index(i, j)).toDouble();
    j = j - Args->Num() + 1;
    data->set_data(i, j, tmp);
}
void Redaction::SetWhatArgInTable(const QModelIndex& index)
{
    int x = index.column();
    int y = index.row();
    if (x < Args->Num() - 1)
        return;
    x = x - Args->Num() + 1;
    std::vector<int> lens;
    for (int i = 0; i < Args->Num(); ++i)
        lens.push_back(Args->get_full_scale_v(i).size());

    Dimensions* dem = new Dimensions(Args->Num(), lens);
    std::vector<int> ColorArg;
    std::vector<sreal_t> tmp;
    std::vector<sreal_t>::iterator it;
    QString str = "Arguments of cell = ";
    ColorArg = dem->ArgsByXY(x, y);
    for (int i = 0; i < Args->Num(); ++i) {
        tmp = Args->get_full_scale_v(i).toStdVector();
        it = tmp.begin();
        for (int j = 0; j < ColorArg[i]; ++j) {
            ++it;
        }
        str += Args->get_name(i) + " : " + QString::number(*it) + " | ";
    }
    delete dem;
    bar->showMessage(str);
}
/* Работа с аргументами в дереве */
void Redaction::Add_Argument()
{
    if (count_args == 5)
        return;
    QObject::disconnect(Argmodel.get(), &QStandardItemModel::itemChanged, this, &Redaction::Changed_Argument);
    count_args++;
    int row = Argmodel->rowCount();
    int cln = Argmodel->columnCount();
    const unsigned DEFCOL = 2;

    Argmodel->setRowCount(row + 1);

    if(cln <= 1)
        Argmodel->setColumnCount(cln + 2);

    QModelIndex index = Argmodel->index(row, 0);

    Argmodel->itemFromIndex(Argmodel->index(row, 0))->setTextAlignment(Qt::AlignCenter);
    Argmodel->itemFromIndex(Argmodel->index(row, 0))->setFont(QFont(SHRIFT, mFON));

    Argmodel->setData(index, "Name_Arg" + QString::number(count_args));
    Argmodel->insertColumns(0, DEFCOL, index);
    Argmodel->insertRows(0, 1, index);

    for (int j = 0; j < DEFCOL; ++j)
        Argmodel->setData(Argmodel->index(0, j, index), QString::number(j));


    // Сохраняем изменения
    SaveChangesOfArgument(count_args);

    // Добавили аргумент в конец таблицы
    Dimensions* dim = new Dimensions(Args->Num(), Args->get_Sizes());
    if (count_args == 0)
        data->add_data_by_A1(2);
    else
        data->add_data_by_AN(count_args, 2, dim);
    delete dim;

    if (table == nullptr)
        DrawTableVals();
    else
        ChangeValModel();
    QObject::connect(Argmodel.get(), &QStandardItemModel::itemChanged, this, &Redaction::Changed_Argument);
}
void Redaction::Delete_Argument()
{
    if (count_args < 0)
    {
        count_args = -1;
        return;
    }
    QTextCodec::setCodecForLocale(QTextCodec::codecForName(ANSI));
    QMessageBox ret;
    ret.addButton(QString::fromLocal8Bit("Отмена"), QMessageBox::RejectRole);
    ret.addButton(QString::fromLocal8Bit("Согласен"), QMessageBox::AcceptRole);
    QString name = Args->get_name(count_args);
    ret.setText(QString::fromLocal8Bit("Удалить аргумент < " + name.toLocal8Bit() + " > ?"));
    ret.setIcon(QMessageBox::Warning);
    if (!(ret.exec() == QMessageBox::Accepted)) 
    {
        ret.deleteLater();
        return;
    }
    if (Args->Num() == 1)
    {
        Argmodel->clear();
        Valmodel->clear();
        Headmodel->clear();
        data->clear_data();
        Args->Clear();
        --count_args;
        return;
    }
    QObject::disconnect(Argmodel.get(), &QStandardItemModel::itemChanged, this, &Redaction::Changed_Argument);
    Argmodel->removeRow(count_args);
    // Удаляем даннын из таблицы
    Dimensions* dim = new Dimensions(Args->Num(), Args->get_Sizes());
    int r = Argmodel->rowCount();
    data->remove_data_by_AN(r, Args->get_full_scale_v(r).size(), Args->get_plain(r), dim);
    delete dim;
    // Сохраняем изменения
    Args->RemoveIndex(count_args);

    --count_args;

    if (table == nullptr)
        DrawTableVals();
    else
        ChangeValModel();
    QObject::connect(Argmodel.get(), &QStandardItemModel::itemChanged, this, &Redaction::Changed_Argument);
}
void Redaction::Act_Delete_Pos_Argument()
{
    if (count_args < 0)
    {
        count_args = -1;
        return;
    }
    int pos = ui->treeView->selectionModel()->currentIndex().row();
    QTextCodec::setCodecForLocale(QTextCodec::codecForName(ANSI));
    QMessageBox ret;
    ret.addButton(QString::fromLocal8Bit("Отмена"), QMessageBox::RejectRole);
    ret.addButton(QString::fromLocal8Bit("Согласен"), QMessageBox::AcceptRole);
    QString name = Args->get_name(pos);
    //ret.setInformativeText("SS");
    ret.setText(QString::fromLocal8Bit("Удалить аргумент < " + name.toLocal8Bit() + " > ?"));
    ret.setIcon(QMessageBox::Warning);
    if (!(ret.exec() == QMessageBox::Accepted))
    {
        ret.deleteLater();
        return;
    }
    if (pos == 0)
    {
        if (Args->Num() == 1)
        {
            Argmodel->clear();
            Valmodel->clear();
            Headmodel->clear();
            data->clear_data();
            Args->Clear();
            --count_args;
            return;
        }
        QObject::disconnect(Argmodel.get(), &QStandardItemModel::itemChanged, this, &Redaction::Changed_Argument);
        HandMoveArgToPos(0, Args->Num()-1, true);
        DrawTreeArgs();
        
        pos = Args->Num() - 1;
        Argmodel->removeRow(pos);
        // Удаляем данныe из таблицы
        Dimensions* dim = new Dimensions(Args->Num(), Args->get_Sizes());;
        data->remove_data_by_AN(pos, Args->get_full_scale_v(pos).size(), Args->get_plain(pos), dim);
        delete dim;
        // Сохраняем изменения
        Args->RemoveIndex(pos);
        
        --count_args;

        if (table == nullptr)
            DrawTableVals();
        else
            ChangeValModel();
        return;
    }
    else
    {
        QObject::disconnect(Argmodel.get(), &QStandardItemModel::itemChanged, this, &Redaction::Changed_Argument);
        Argmodel->removeRow(pos);
        // Удаляем данныe из таблицы
        Dimensions* dim = new Dimensions(Args->Num(), Args->get_Sizes());;
        data->remove_data_by_AN(pos, Args->get_full_scale_v(pos).size(), Args->get_plain(pos), dim);
        delete dim;
        // Сохраняем изменения
        if (count_args >= 0)
        {
            Args->RemoveIndex(pos);
        }
    }
    --count_args;

    if (table == nullptr)
        DrawTableVals();
    else
        ChangeValModel();
    QObject::connect(Argmodel.get(), &QStandardItemModel::itemChanged, this, &Redaction::Changed_Argument);

}
void Redaction::Edit_Argument_Description()
{
    int pos = ui->treeView->selectionModel()->currentIndex().row();

    DialogEdit* d = new DialogEdit(Args->get_description(pos));

    if (d->exec() == QDialog::Accepted)
        Args->set_description(pos, d->get_desc());

    delete d;
}
void Redaction::Plain_Argument()
{
    //Нужна чтоб отобразить в диалоговом окне имя аргумента
    int pos = ui->treeView->selectionModel()->currentIndex().row();

    //Имена аргументов для бокса в диалоговом окне
    QStringList names;
    QVector<int> plains;
    for (int i = 0; i < Args->Num(); ++i)
    {
        names << Args->get_name(i);
        plains.push_back(Args->get_plain(i));
    }
    //Окно изменение аргумента
    DialogPlain* d = new DialogPlain(names, Args->get_AllValues(), pos, plains);

    if (d->exec() != QDialog::Accepted)
    {
        delete d;
        return;
    }
    //Получение новых значений
    int plain = d->get_plain();
    //Если в диал.окне изменили аргумент
    int pos_vals = d->get_pos();

    Args->set_plain(pos_vals, plain);

    delete d;
}
void Redaction::Insert_ArgumentUp()
{    
    if (count_args == 5)
        return;
    QObject::disconnect(Argmodel.get(), &QStandardItemModel::itemChanged, this, &Redaction::Changed_Argument);
    
    count_args++;

    int pos = ui->treeView->selectionModel()->currentIndex().row();

    const unsigned DEFCOL = 2;
    std::unique_ptr<Argument> arg = std::make_unique<Argument>();

    arg->set_name("Name_Arg" + QString::number(count_args));
    arg->set_description("Desc_Arg");
    for (int j = 0; j < DEFCOL; ++j)
        arg->set_scale(j);

    if (pos == 0)
        Args->Insert(*arg, count_args);
    else
        Args->Insert(*arg, pos);

    int row = Argmodel->rowCount();
    int cln = Argmodel->columnCount();

    QStandardItem* item = new QStandardItem();

    item->setColumnCount(DEFCOL);
    item->setRowCount(1);

    if (pos == 0)
        Argmodel->insertRow(count_args, item);
    else
        Argmodel->insertRow(pos, item);

    QModelIndex index;
    if (pos == 0)
        index = Argmodel->index(count_args, 0);
    else
        index = Argmodel->index(pos, 0);

    Argmodel->setData(index, "Name_Arg" + QString::number(count_args));

    for (int j = 0; j < DEFCOL; ++j)
        Argmodel->setData(Argmodel->index(0, j, index), QString::number(j), Qt::DisplayRole);

    Argmodel->itemFromIndex(Argmodel->index(pos, 0))->setTextAlignment(Qt::AlignCenter);
    Argmodel->itemFromIndex(Argmodel->index(pos, 0))->setFont(QFont(SHRIFT, mFON));
    if (pos == 0)
    {
        Dimensions* dim = new Dimensions(Args->Num(), Args->get_Sizes());
        data->add_data_by_AN(count_args, 2, dim);
        HandMoveArgToPos(count_args, 0);
        delete dim;
        DrawTreeArgs();
    }
    else
    {
        Dimensions* dim = new Dimensions(Args->Num(), Args->get_Sizes());
        data->add_data_by_AN(pos, 2, dim);
        delete dim;
    }

    if (table == nullptr)
        DrawTableVals();
    else
        ChangeValModel();

    QObject::connect(Argmodel.get(), &QStandardItemModel::itemChanged, this, &Redaction::Changed_Argument);
}
void Redaction::Insert_ArgumentDw()
{
    if (count_args == 5)
        return;
    QObject::disconnect(Argmodel.get(), &QStandardItemModel::itemChanged, this, &Redaction::Changed_Argument);

    count_args++;

    int pos = ui->treeView->selectionModel()->currentIndex().row();
    ++pos;
    const unsigned DEFCOL = 2;
    std::unique_ptr<Argument> arg = std::make_unique<Argument>();

    arg->set_name("Name_Arg" + QString::number(count_args));
    arg->set_description("Desc_Arg");
    for (int j = 0; j < DEFCOL; ++j)
        arg->set_scale(j);

    if (pos == 0)
        Args->Insert(*arg, count_args);
    else
        Args->Insert(*arg, pos);

    int row = Argmodel->rowCount();
    int cln = Argmodel->columnCount();

    QStandardItem* item = new QStandardItem();

    item->setColumnCount(DEFCOL);
    item->setRowCount(1);

    if (pos == 0)
        Argmodel->insertRow(count_args, item);
    else
        Argmodel->insertRow(pos, item);

    QModelIndex index;
    if (pos == 0)
        index = Argmodel->index(count_args, 0);
    else
        index = Argmodel->index(pos, 0);

    Argmodel->setData(index, "Name_Arg" + QString::number(count_args));

    for (int j = 0; j < DEFCOL; ++j)
        Argmodel->setData(Argmodel->index(0, j, index), QString::number(j), Qt::DisplayRole);

    Argmodel->itemFromIndex(Argmodel->index(pos, 0))->setTextAlignment(Qt::AlignCenter);
    Argmodel->itemFromIndex(Argmodel->index(pos, 0))->setFont(QFont(SHRIFT, mFON));
    if (pos == 0)
    {
        Dimensions* dim = new Dimensions(Args->Num(), Args->get_Sizes());
        data->add_data_by_AN(count_args, 2, dim);
        HandMoveArgToPos(count_args, 0);
        delete dim;
        DrawTreeArgs();
    }
    else
    {
        Dimensions* dim = new Dimensions(Args->Num(), Args->get_Sizes());
        data->add_data_by_AN(pos, 2, dim);
        delete dim;
    }

    if (table == nullptr)
        DrawTableVals();
    else
        ChangeValModel();

    QObject::connect(Argmodel.get(), &QStandardItemModel::itemChanged, this, &Redaction::Changed_Argument);
}
void Redaction::Add_Column()
{   
    //Нужна чтоб отобразить в диалогово окне имя аргумента
    int pos = ui->treeView->selectionModel()->currentIndex().row();

    //Имена аргументов для бокса в диалоговом окне
    QStringList names;
    for (int i = 0; i < Args->Num(); ++i)
    {
        names << Args->get_name(i);
    }
    //Окно изменение аргумента
    DialogAdd* d = new DialogAdd(names, Args->get_AllValues(), pos);

    if (d->exec() != QDialog::Accepted)
    {
        delete d;
        return;
    }
    //Получение новых значений
    QVector<double> new_vals = d->get_args();
    QObject::disconnect(Argmodel.get(), &QStandardItemModel::itemChanged, this, &Redaction::Changed_Argument);
    //Если в диал.окне изменили аргумент
    int pos_vals = d->get_pos();
    int plain = Args->get_plain(pos_vals);
    int vals_of_plain = Args->get_full_scale_v(pos_vals)[plain];
    std::sort(new_vals.begin(), new_vals.end());

    for (int i = 0; i < new_vals.size(); ++i)
        Args->set_scale(pos_vals, new_vals[i]);

    Args->sort_argument(pos_vals);

    //Длинна аргумента с учетом новых значений
    int len = Args->get_full_scale_v(pos_vals).size();
    //Макс длинна колонки
    int col = Argmodel->columnCount();

    QModelIndex index = Argmodel->index(pos_vals, 0);
    
    QVector<sreal_t> tmpA = Args->get_full_scale_v(pos_vals);

    //Новые колонки с учетом их сортировки относительно других аргументов
    QVector<int> new_columns;

    for (int i = 0; i < new_vals.size(); ++i)
        for (int j = 0; j < tmpA.size(); ++j)
        {
            if (new_vals[i] == tmpA[j])
                new_columns.push_back(j);
        }
    for (int j = 0; j < tmpA.size(); ++j)
    {
        if (vals_of_plain == tmpA[j])
        {
            Args->set_plain(pos_vals, j);
            break;
        }
    }
    Argmodel->itemFromIndex(index)->setColumnCount(tmpA.size());

    // Если нужно расширить колонки
    if (col < tmpA.size())
        Argmodel->setColumnCount(tmpA.size());

    //Добавляем значения аргумента с новыми данными
    for (int j = 0; j < tmpA.size(); ++j)
        Argmodel->setData(Argmodel->index(0, j, index), QString::number(tmpA[j]));

    //Размерность
    Dimensions* dem = new Dimensions(Args->Num(), Args->get_Sizes());

    //Если A1 or AN
    if(pos_vals == 0)
        data->resize_data_by_A1(tmpA.size(), new_columns);
    else
        data->resize_data_by_AN(pos_vals, Args->amount_rows(), new_columns, dem);

    delete dem;
    delete d;
    ui->treeView->update();//Реврешеp
    //Перерисовка таблицы
    if (table == nullptr)
        DrawTableVals();
    else
        ChangeValModel();
    QObject::connect(Argmodel.get(), &QStandardItemModel::itemChanged, this, &Redaction::Changed_Argument);
}
void Redaction::Delete_Column()
{
    int pos = ui->treeView->selectionModel()->currentIndex().row();

    //Имена аргументов для бокса в диалоговом окне
    QStringList names;
    for (int i = 0; i < Args->Num(); ++i)
    {
        names << Args->get_name(i);
    }
    //Окно изменение аргумента
    Dialogdelete* d = new Dialogdelete(names, Args->get_AllValues(), pos);

    if (d->exec() != QDialog::Accepted)
    {
        delete d;
        return;
    }
    QObject::disconnect(Argmodel.get(), &QStandardItemModel::itemChanged, this, &Redaction::Changed_Argument);
    QVector<int> del_columns;
    del_columns = d->get_deleted_pos();
    //Если в диал.окне изменили аргумент
    int pos_vals = d->get_pos();
    int plain = Args->get_plain(pos_vals);
    int vals_of_plain = Args->get_full_scale_v(pos_vals)[plain];
    for (int i = 0; i < del_columns.size(); ++i)
        if (plain >= del_columns[i])
            plain--;
    Args->set_plain(pos_vals, plain);
    //Размерность
    Dimensions* dem = new Dimensions(Args->Num(), Args->get_Sizes());

    for (int i = 0; i < del_columns.size(); ++i)
        Args->remove_scale(pos, del_columns[i] - i);

    QModelIndex index = Argmodel->index(pos_vals, 0);
    QVector<sreal_t> tmpA = Args->get_full_scale_v(pos_vals);

    Argmodel->itemFromIndex(index)->setColumnCount(tmpA.size());

    //Добавляем значения аргумента с новыми данными
    for (int j = 0; j < tmpA.size(); ++j)
        Argmodel->setData(Argmodel->index(0, j, index), QString::number(tmpA[j]));

    //Если A1 or AN
    if (pos_vals == 0)
        data->resize_data_by_A1_d(del_columns);
    else
        data->resize_data_by_AN_d(pos_vals, del_columns, dem);

    delete dem;
    delete d;
    ui->treeView->update();//Реврешеp

    //Перерисовка таблицы
    if (table == nullptr)
        DrawTableVals();
    else
        ChangeValModel();
    QObject::connect(Argmodel.get(), &QStandardItemModel::itemChanged, this, &Redaction::Changed_Argument);
}
void Redaction::Mod_Sort()
{
    int pos = ui->treeView->selectionModel()->currentIndex().row();

    if (Args->get_sort_policy(pos))
        Args->set_sort_policy(pos, false);
    else
        Args->set_sort_policy(pos, true);
}
void Redaction::Transportation()
{
    if (Args->Num() > 1 && Argmodel->rowCount() == Args->Num())
    {
        TransTable();
        SaveFullChangesOfArgumentsAfterTrans();
        if (table == nullptr)
            DrawTableVals();
        else
            ChangeValModel();
    }
}
/* Опции */
void Redaction::ShowFileDesc()
{
    if (ui->text_desc->isVisible())
        ui->text_desc->setVisible(false);
    else
        ui->text_desc->setVisible(true);
}
void Redaction::ShowTableDesc()
{
    if (ui->value_desc->isVisible())
        ui->value_desc->setVisible(false);
    else
        ui->value_desc->setVisible(true);
}
void Redaction::ChangeFillTable()
{
    data->fill = ui->ln_fill->text();
}
}// end namespace lid
