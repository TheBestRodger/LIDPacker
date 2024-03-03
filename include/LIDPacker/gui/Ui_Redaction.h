
#ifndef TRANSZHQULY_H
#define TRANSZHQULY_H
/*!
********************************************************
*   @file Ui_Redaction.h
*   @author Dmitry
*   @date  18/01/2023
*   @brief Описание графических элементов
*   namespace RedactionClass
**********************************************************
*/
#include <LIDPacker/maker/Helper/TreeView.h>

#include <QObject>
#include <QGridLayout>
#include <QSplitter>
#include <QPlainTextEdit>
#include <QPushButton>
#include <QAction>
#include <QMenu>
#include <QLineEdit>
/*!***********************************************
*
*   @brief Класс Ui_Redaction реализации окна редактирования
*   Класс содержит описание графических элементов
*   Наследован от QObject
*   @author Dmitry
*   @version 2.0
*   @date  09.02.2023
*
*
***************************************************
*/
QT_BEGIN_NAMESPACE
class Ui_Redaction : QObject
{
public:
    ~Ui_Redaction();
    /* Меню при нажатии пкм */
    QMenu* menu_arg;
    QAction* addArg;
    QAction* insArgUp;
    QAction* insArgDw;
    QAction* chngArg;
    QAction* deleteArg;
    QAction* addValArg;
    QAction* remValArg;
    QAction* chngArgArea;
    QAction* modSorting;
    /************************/

    QPushButton* btn_plus;//!    btn_plus - Кнопка добавить аргумент
    QAction*     action_plus;
    QPushButton* btn_minus;//!   btn_minus - Кнопка удалить аргумент 
    QAction*     action_minus;

    QPushButton* btn_show_file_d;    
    QAction*    action_show_file;

    QPushButton* btn_show_table_d;
    QAction*    action_show_table_d;

    QSpacerItem* hspacer;
    QSpacerItem* hspacer2;
    QHBoxLayout* hbox_for_btn;
    QSplitter* split_btn;//! split_btn - разделитель кнопок плюс-минус-
    QSplitter* split_lay;//!   split_lay - разделитель описания/аргументов/таблицы


    /*
    * Используется во всем файле
    */

    QPlainTextEdit* text_desc;//! Описание файла
    QPlainTextEdit* value_desc;//! Описание значений
    // Модели представления
    lid::TreeView* treeView;


    QGridLayout* grid_lay_Redact;//!< Главный лайаут   
    QGridLayout* grd_add_args;//!< Второстепенный для динамичкского расширения аргмуентов

    /////////////////////////////////////////
    QVBoxLayout* VLay_All_Desc;
    QVBoxLayout* VLay_file;
    QVBoxLayout* VLay_tbl;
    QHBoxLayout* HBox_btn_file;
    QHBoxLayout* HBox_btn_tbl;
    QSpacerItem* hspacer_btn_file;
    QSpacerItem* hspacer_btn_tbl;
    QWidget*     wgt_all;
    QVBoxLayout* VLay_tree;
    QWidget*     wgt_tree;
    ////////////////////////////////////////
    QLineEdit*   ln_fill;
    void setupUi(QWidget* MainWind);

private:
    void retranslateUi(QWidget* MainWind);
};
namespace Ui {
    class URedact : public Ui_Redaction {};
}
QT_END_NAMESPACE

#endif // TRANSZHQULY_H