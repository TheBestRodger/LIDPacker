#pragma once
/*!
********************************************************
*   @file   Redaction.h
*   @author Kalikin D.M.
*   @date   2023/11/03
*   @brief  Описание методов и подключаемые библиотеки
**********************************************************
*/

#include "LIDPacker/gui/Ui_Redaction.h"
#include "LIDPacker/maker/Helper/TableView.h"
#include "LIDPacker/maker/Brain/Arguments.h"
#include "LIDPacker/maker/Brain/Data.h"

#include "science/math/interpolation.hpp"

#include <QMimeData>
#include <QStandardItemModel>
#include <QWidget>
#include <QHeaderView>
#include <QStatusBar>
#include <qmenubar.h>
/*!***********************************************
*
*   @brief Класс Redaction реализации окна редактирования
*   Класс содержащие методы для работы с данными
*   @author Kalikin D.M.
*   @version 3.0
*   @date 2023/02/09
*
****************************************************/

QT_BEGIN_NAMESPACE
namespace lid {
class Redaction : public QWidget
{
    Q_OBJECT
public:
    /** \brief Конструктор, который получает путь на файл и статус бар. */
    explicit                                Redaction(const char* pth, QMenuBar*, QStatusBar* bar, QWidget* parent = nullptr);

    /** \brief Конструктор, который получает статус бар, если получения пути просиходит с помощью метода. */
    explicit                                Redaction(QMenuBar*, QStatusBar* bar, QWidget* parent = nullptr);

    /** \brief Деструктор. */
                                            ~Redaction();

    /** \brief Установка путь до файла с данными. */
    void                                    set_path(const char* pth);

    /** \brief Сохранение файла как бинарный. */
    bool                                    save_binaries();

    /** \brief Сохранение файла как бинарный, но с выбором места сохранения. */
    bool                                    save_as_binaries(const char* pth);

    /** \brief Очищение данных. */
    void                                    clear();

    const science::Interpolator            get_interpolator();
private:
    /** \brief Логига сохранения файла.  */
    bool                                    Save(const char* pth);

    /** \brief Прорисовка аргументов. */
    void                                    DrawTreeArgs();

    /** \brief Прорисовка таблицы. */
    void                                    DrawTableVals();

    /** \brief Установка описания файла. */
    void                                    SetDescFile();

    /** \brief Установка описания таблицы. */
    void                                    SetDescTable();

    /** \brief Получение данных из интерполяции. */
    void                                    ConvertDataFromInterpol(science::Interpolator&);

    /** \brie Добавление данных в интерполятор для сохранения. */
    science::Interpolator                   ConvertDataToInterpol();

    /** \brief Коннекты всех кнопок кот. инициализировались в граф. интерфейсе. */
    void                                    AllConnects();

    /** \brief Транспонирование таблицы. first - позиция аргумента. */
    int                                     TransTable();

    /** \brief Проверка на изменение позиции аргументов. */
    bool                                    CheckPositionArgs();

    /** \brief Перерисовка таблицы, изменение модели данных на основе изменение аргументов. */
    void                                    ChangeValModel();

    /** \brief Сохранение изменений конкретного аргумента. */
    void                                    SaveChangesOfArgument(int pos);

    /** \brief Сохраняет/Перезаписывает все аргументы из модели. */
    void                                    SaveFullChangesOfArguments();

    /** \brief Сохраняет/Перезаписывает все аргументы из модели. из-за транспонирования. */
    void                                    SaveFullChangesOfArgumentsAfterTrans();

    /** \brief Автоматическое перемещение аргумента с изменением табличных данных (относительно перемещения). bool f - нужен для того если удаляем первый аргумент. */
    void                                    HandMoveArgToPos(int pos_arg, int pos_in, bool f = false);

protected slots:
    /** \brief */
    //virtual bool                            viewportEvent(QEvent* event);
    void                                    showContextMenu(QPoint pos); 

private slots:   

    // Добавить аргумент.
    void                                    Add_Argument();     
    // По кнопке удалить последний аргумент.
    void                                    Delete_Argument();  
    // Удалить конкретный аргумент.
    void                                    Act_Delete_Pos_Argument();  
    // Изменить аргумент.
    void                                    Edit_Argument_Description(); 
    // Изменить/Показать плоскость аргумента.
    void                                    Plain_Argument();
    // Вставить выше аргумента.
    void                                    Insert_ArgumentUp();
    // Вставить ниже аргумента.
    void                                    Insert_ArgumentDw(); 
    // Вставить/Расширить значение к аргументу.
    void                                    Add_Column();
    // Удалить значение аргумента.
    void                                    Delete_Column();   
    // Отображает в статусе информацию об ячейки таблицы.
    void                                    SetWhatArgInTable(const QModelIndex& index); 
    // Сохраняет изменение в таблице (если изменили данные в ячейке).
    void                                    Save_Data_Table(QStandardItem* item);
    // Выбор типа сортировки возрастающая или убывающая последовательность.
    void                                    Changed_Argument(QStandardItem* item);
    // Установка тип сортировки для поддержки работы с убывающей последовательностью
    void                                    Mod_Sort(); 

    // При удалении строки автоматически вызывается и проверяет изменилось ли положение строк.
    // Так как в QT реализованно изменение положение строк ("мышкой") в QTreeView это удаление взятой строчки и вставкой в новую позицию.
    void                                    Transportation();

    void                                    ShowFileDesc();// Окно вкл/выкл отображение описание файла.
    void                                    ShowTableDesc();// Окно вкл/выкл отображение описание таблицы.
    void                                    ChangeFillTable();// Заполнитель таблицы, при появление новых строк.
private:

    /** \brief Объявление граф.интерфейса редактора. */
    Ui::URedact* ui;

    /** \brief  Заголовок модели данных в таблице. */
    QHeaderView* header_H;

    /** \brief  Таблица-представление данных. */
    TableView* table;

    /** \brief  Статус бар которые отображает вспомогательную информацию. */
    QStatusBar* bar;

    /** \brief  Аргументы из считанного файла. */
    std::shared_ptr<idArguments>	        Args;

    /** \brief  Табличные данные и описание таблицы, файла.  */
    std::shared_ptr<Data>			        data;

    /** \brief  Модель для древовидного представления аргумента. */
    std::shared_ptr<QStandardItemModel>     Argmodel;

    /** \brief  Модель для табличных данных. */
    std::shared_ptr<QStandardItemModel>     Valmodel;

    /** \brief  Модель заголовка табличных данных. */
    std::shared_ptr<QStandardItemModel>     Headmodel;

    /** \brief Путь получающий из вне на файл. */
    QByteArray path;

    /** \brief Номер последнего аргумента инициализирауеться -1 так как ласт аргумент это всего аргументов - 1. */
    int count_args;

};
namespace {
    /**/
    void manager_table(int R, const idArguments* Args, QStandardItemModel* Valmodel, TableView* table);
    /**/
    void add_R1_table(const idArguments* Args, QStandardItemModel* Valmodel, TableView* table);
    /**/
    void add_R2_table(const idArguments* Args, QStandardItemModel* Valmodel, TableView* table);
    /**/
    void add_R3_table(const idArguments* Args, QStandardItemModel* Valmodel, TableView* table);
    /**/
    void add_R4_table(const idArguments* Args, QStandardItemModel* Valmodel, TableView* table);
    /**/
    void add_R5_table(const idArguments* Args, QStandardItemModel* Valmodel, TableView* table);
    /**/
    void add_R6_table(const idArguments* Args, QStandardItemModel* Valmodel, TableView* table);
    /**/
    void add_R7_table(const idArguments* Args, QStandardItemModel* Valmodel, TableView* table);
}
inline void Redaction::AllConnects()      
{    
    QObject::connect(ui->treeView,          &QTreeView::customContextMenuRequested, this, &Redaction::showContextMenu);
    QObject::connect(Argmodel.get(),        &QStandardItemModel::rowsRemoved,       this, &Redaction::Transportation);
    QObject::connect(ui->ln_fill,           &QLineEdit::editingFinished,            this, &Redaction::ChangeFillTable);

    QObject::connect(ui->action_plus,       SIGNAL(triggered()), this, SLOT(Add_Argument()));
    QObject::connect(ui->action_minus,      SIGNAL(triggered()), this, SLOT(Delete_Argument()));
    QObject::connect(ui->addArg,            SIGNAL(triggered()), this, SLOT(Add_Argument()));
    QObject::connect(ui->insArgUp,          SIGNAL(triggered()), this, SLOT(Insert_ArgumentUp()));
    QObject::connect(ui->insArgDw,          SIGNAL(triggered()), this, SLOT(Insert_ArgumentDw()));
    QObject::connect(ui->addValArg,         SIGNAL(triggered()), this, SLOT(Add_Column()));
    QObject::connect(ui->remValArg,         SIGNAL(triggered()), this, SLOT(Delete_Column()));
    QObject::connect(ui->modSorting,        SIGNAL(triggered()), this, SLOT(Mod_Sort()));
    QObject::connect(ui->chngArg,           SIGNAL(triggered()), this, SLOT(Edit_Argument_Description()));
    QObject::connect(ui->chngArgArea,       SIGNAL(triggered()), this, SLOT(Plain_Argument()));
    QObject::connect(ui->deleteArg,         SIGNAL(triggered()), this, SLOT(Act_Delete_Pos_Argument()));

    QObject::connect(ui->action_show_file,      SIGNAL(triggered()), this, SLOT(ShowFileDesc()));
    QObject::connect(ui->action_show_table_d,   SIGNAL(triggered()), this, SLOT(ShowTableDesc()));
}
}//end namespace lid
QT_END_NAMESPACE