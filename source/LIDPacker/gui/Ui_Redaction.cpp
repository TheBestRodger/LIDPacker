/*!
********************************************************
*   @file Ui_Redaction.cpp
*   @author Kalikin D.M.
*   @date Январь  18/01/2023
*   @brief Реализация графических элементов
*   Содержит класс SimpleDelegate
**********************************************************
*/
#include "LIDPacker/gui/Ui_Redaction.h"
#include "LIDPacker/maker/stylesdefine.h"
#include "LIDPacker/maker/predefine.h"

#include <QStatusBar>
#include <QTextCodec>
Ui_Redaction::~Ui_Redaction() {
    delete btn_minus;
    delete btn_plus;
    delete action_plus;
    delete action_minus;
    delete split_btn;
    delete split_lay;
    delete grid_lay_Redact;
    delete grd_add_args;
    //treeView;
    //hbox_for_save_btn;
    delete menu_arg;
    delete addArg;
    delete insArgUp;
    delete insArgDw;
    delete chngArg;
    delete deleteArg;
    delete addValArg;
    delete remValArg;
    delete chngArgArea;
    delete modSorting;
    //text_desc;
    //value_desc;
    //delete btn_show_file_d;
    //delete btn_show_table_d;
    delete action_show_file;
    delete action_show_table_d;
    //delete hspacer;
    //text_desc;
    //value_desc;
    //delete tmp;
}
void Ui_Redaction::setupUi(QWidget* MainWind) {

    treeView = new lid::TreeView();

    treeView->setContextMenuPolicy(Qt::CustomContextMenu);
    treeView->setDragDropMode(QAbstractItemView::DragDrop);
    treeView->setDefaultDropAction(Qt::MoveAction);
    treeView->setSelectionMode(QAbstractItemView::SingleSelection);
    treeView->setStyleSheet(style_btn_des);
    treeView->setAcceptDrops(true);
    treeView->setMouseTracking(true);
    grid_lay_Redact   = new QGridLayout(MainWind);
    grd_add_args      = new QGridLayout();

    menu_arg    = new QMenu();
    addArg      = new QAction();
    insArgUp    = new QAction();
    insArgDw    = new QAction();
    chngArg     = new QAction();
    deleteArg   = new QAction();
    addValArg   = new QAction();
    remValArg   = new QAction();
    chngArgArea = new QAction();
    modSorting  = new QAction();
    menu_arg->addAction(modSorting);
    menu_arg->addSeparator();
    menu_arg->addAction(addArg);
    menu_arg->addAction(insArgUp);
    menu_arg->addAction(insArgDw);
    menu_arg->addSeparator();
    menu_arg->addAction(addValArg);
    menu_arg->addAction(remValArg);
    menu_arg->addSeparator();
    menu_arg->addAction(chngArg);
    menu_arg->addAction(chngArgArea);
    menu_arg->addSeparator();
    menu_arg->addAction(deleteArg);

    btn_plus      = new QPushButton();
    btn_minus     = new QPushButton();

    btn_show_file_d  = new QPushButton();
    btn_show_file_d->setFlat(true);
    btn_show_table_d = new QPushButton();
    btn_show_table_d->setFlat(true);

    action_plus     = new QAction();
    action_minus    = new QAction();
    action_show_file    = new QAction();
    action_show_table_d = new QAction();
    /////////////////////////////////////////////////////////////////
    hspacer             = new QSpacerItem(100, 10, QSizePolicy::Expanding, QSizePolicy::Maximum);
    hspacer2            = new QSpacerItem(100, 10, QSizePolicy::Expanding, QSizePolicy::Maximum);
    hspacer_btn_file    = new QSpacerItem(100, 10, QSizePolicy::Expanding, QSizePolicy::Maximum);
    hspacer_btn_tbl     = new QSpacerItem(100, 10, QSizePolicy::Expanding, QSizePolicy::Maximum);
    VLay_All_Desc       = new QVBoxLayout();
    VLay_file           = new QVBoxLayout();
    VLay_tbl            = new QVBoxLayout();
    HBox_btn_file       = new QHBoxLayout();
    HBox_btn_tbl        = new QHBoxLayout();
    wgt_all             = new QWidget();
    text_desc           = new QPlainTextEdit;
    value_desc          = new QPlainTextEdit;

    hbox_for_btn        = new QHBoxLayout();
    split_btn           = new QSplitter(Qt::Horizontal);
    split_lay           = new QSplitter(Qt::Vertical);
    HBox_btn_file->addWidget(btn_show_file_d);
    HBox_btn_file->addItem(hspacer_btn_file);
    VLay_file->addLayout(HBox_btn_file);
    //text_desc->setVisible(false);
    VLay_file->addWidget(text_desc);
    VLay_All_Desc->addLayout(VLay_file);

    HBox_btn_tbl->addWidget(btn_show_table_d);
    HBox_btn_tbl->addItem(hspacer_btn_tbl);
    VLay_tbl->addLayout(HBox_btn_tbl);
    //value_desc->setVisible(false);
    VLay_tbl->addWidget(value_desc);
    VLay_All_Desc->addLayout(VLay_tbl);
    text_desc->setStyleSheet(style_btn_des);
    text_desc->setFont(QFont(SHRIFT, FON));
    value_desc->setStyleSheet(style_btn_des);
    value_desc->setFont(QFont(SHRIFT, FON));
    ln_fill   = new QLineEdit();
    split_btn->addWidget(btn_plus);
    split_btn->addWidget(btn_minus);
    split_btn->addWidget(ln_fill);
    hbox_for_btn->addWidget(split_btn);
    hbox_for_btn->addItem(hspacer);
    hbox_for_btn->addItem(hspacer2);
    //VLay_All_Desc->addLayout(hbox_for_btn);

    wgt_all->setLayout(VLay_All_Desc);
    /////////////////////////////////////////////////////////////////
    VLay_tree = new QVBoxLayout();
    wgt_tree  = new QWidget();
    VLay_tree->addLayout(hbox_for_btn);
    VLay_tree->addWidget(treeView);
    treeView->setFrameStyle(QFrame::Box | QFrame::Plain);
    wgt_tree->setLayout(VLay_tree);
    wgt_tree->resize(2000, 2000);
    /////////////////////////////////////////////////////////////////
    split_lay->addWidget(wgt_all);//! Описание файла
    split_lay->addWidget(wgt_tree);//! Аргументы

    /////////////////////////////////////////////////////////////////
    grid_lay_Redact->addWidget(split_lay, 0, 0, 1, 6);

    QObject::connect(btn_plus,             SIGNAL(clicked()), action_plus,          SLOT(trigger()));
    QObject::connect(btn_minus,            SIGNAL(clicked()), action_minus,         SLOT(trigger()));
    QObject::connect(btn_show_file_d,      SIGNAL(clicked()), action_show_file,     SLOT(trigger()));
    QObject::connect(btn_show_table_d,     SIGNAL(clicked()), action_show_table_d,  SLOT(trigger()));
    retranslateUi(MainWind);
}
void Ui_Redaction::retranslateUi(QWidget* MainWind)
{
    //QTextCodec::setCodecForLocale(QTextCodec::codecForName(CODEC));
    MainWind->setWindowTitle("Redaction");

    QTextCodec* codec = QTextCodec::codecForName(CODEC);
    btn_plus->setText("+");
    btn_plus->setFont(QFont(SHRIFT, FON));
    btn_plus->setShortcut(QKeySequence(Qt::Key_Plus));

    btn_minus->setText("-");
    btn_minus->setFont(QFont(SHRIFT, FON));
    btn_minus->setShortcut(QKeySequence(Qt::Key_Minus));
    QString str = codec->toUnicode("Заполнитель для таблицы, по умолчанию = 0");
    ln_fill->setText(str);
    ln_fill->setFont(QFont(SHRIFT, mFON-3));

    str = codec->toUnicode("Описание файла");
    btn_show_file_d->setText(str);
    btn_show_file_d->setFont(QFont(SHRIFT, FON));

    str = codec->toUnicode("Описание таблицы");
    btn_show_table_d->setText(str);
    btn_show_table_d->setFont(QFont(SHRIFT, FON));



    str = codec->toUnicode("Добавить аргумент");
    addArg->setText(str);
    str = codec->toUnicode("Вставить аргумент наверх");
    insArgUp->setText(str);
    str = codec->toUnicode("Вставить аргумент вниз");
    insArgDw->setText(str);
    
    str = codec->toUnicode("Добавить значения");
    addValArg->setText(str);

    str = codec->toUnicode("Удалить значения");
    remValArg->setText(str);

    str = codec->toUnicode("Сортировка по возрастанию");
    modSorting->setText(str);

    str = codec->toUnicode("Изменить описание аргумента");
    chngArg->setText(str);

    str = codec->toUnicode("Изменить плоскость аргумента");
    chngArgArea->setText(str);

    str = codec->toUnicode("Удалить аргумент");
    deleteArg->setText(str);

    treeView->setFont(QFont(SHRIFT, FON));
} // retranslateUi
