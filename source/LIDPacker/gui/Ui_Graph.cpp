/*!
********************************************************
*	@file Ui_Graph.cpp
*	@author Kalikin D.M.
*	@date   18.01.2023
*	@brief Реализация файла Ui_Graph.h
**********************************************************
*/
#include "LIDPacker/gui/Ui_Graph.h"
#include <LIDPacker/maker/predefine.h>
#include <QTextCodec>
#include <LIDPacker/maker/stylesdefine.h>
void Ui_Graph::setupUi(QWidget* graphics) {
    graphics->resize(1200, 1000);
    graphics->setStyleSheet(style_app);
    grd_central_lay = new QVBoxLayout(graphics);

    verticalLayout = new QVBoxLayout();
    lay_X = new QHBoxLayout();
    lbl_X = new QLabel();
    SpinBox_X_dwn = new QDoubleSpinBox();
    SpinBox_X_top = new QDoubleSpinBox();

    lay_Y = new QHBoxLayout();
    lbl_Y = new QLabel();
    SpinBox_Y_dwn = new QDoubleSpinBox();
    SpinBox_Y_top = new QDoubleSpinBox();

    SpinBox_X_dwn->setMaximum(LONG_MAX);
    SpinBox_X_dwn->setMinimum(LONG_MIN);
    SpinBox_X_top->setMaximum(LONG_MAX);
    SpinBox_X_top->setMinimum(LONG_MIN);
    SpinBox_Y_dwn->setMaximum(LONG_MAX);
    SpinBox_Y_dwn->setMinimum(LONG_MIN);
    SpinBox_Y_top->setMaximum(LONG_MAX);
    SpinBox_Y_top->setMinimum(LONG_MIN);

    del_menu = new QMenu();
    act_del  = new QAction();
    del_menu->addAction(act_del);
    /*/////////////////////*/
    lay_X->addWidget(lbl_X);
    lay_X->addWidget(SpinBox_X_dwn);
    lay_X->addWidget(SpinBox_X_top);

    lay_Y->addWidget(lbl_Y);
    lay_Y->addWidget(SpinBox_Y_dwn);
    lay_Y->addWidget(SpinBox_Y_top);

    verticalLayout->addLayout(lay_X);
    verticalLayout->addLayout(lay_Y);
    /*////////////////////*/
    tmp             = new QWidget();
    wgt_05          = new QWidget();
    wgt_1           = new QWidget();
    wgt_2           = new QWidget();
    wgt_3           = new QWidget();

    ScrollArea      = new QScrollArea();
    Main_Vlay       = new QVBoxLayout();

    Vlay_1 = new QVBoxLayout();
    VLay_2 = new QVBoxLayout();
    VLay_3 = new QVBoxLayout();

    lbl_table_val   = new QLabel();
    lbl_ch_OCX      = new QLabel();
    lbl_val_args    = new QLabel();

    spl_H           = new QSplitter(Qt::Horizontal);
    spl_V           = new QSplitter(Qt::Vertical);

    tree_tbl_val    = new QTreeView();
    tree_tbl_val->setContextMenuPolicy(Qt::CustomContextMenu);
    list_vals_args  = new QListWidget();
    list_vals_args->setFont(QFont(SHRIFT, mFON));
    table_ch_values = new QTableWidget();

    btn_choose = new QPushButton();

    chartview = new ChartView();

    menu            = new QMenuBar;

    act_align       = new QAction;
    act_OCXY        = new QAction;
    act_delete_view = new QAction;
    Export_Pic      = new QMenu;
    act_Save_As_PNG     = new QAction;
    act_Save_As_JPEG    = new QAction;
    act_Save_As_PDF     = new QAction;
    Export_Pic->addAction(act_Save_As_PNG);
    Export_Pic->addAction(act_Save_As_JPEG);
    Export_Pic->addAction(act_Save_As_PDF);

    menu_options = new QMenu;
    act_opt_dots     = new QAction;
    act_opt_lines    = new QAction;
    act_opt_splines  = new QAction;
    act_anime        = new QAction;
    menu_options->addAction(act_opt_dots);
    menu_options->addAction(act_opt_lines);
    menu_options->addAction(act_opt_splines);
    menu_options->addAction(act_anime);

    menu->addMenu(menu_options);
    menu->addAction(act_align);
    menu->addAction(act_OCXY);
    menu->addMenu(Export_Pic);
    menu->addSeparator();
    menu->addAction(act_delete_view);
    chartview->setStyleSheet(style_app);
    chartview->resize(1000, 1000);
    wgt_05->setLayout(verticalLayout);
    wgt_05->setVisible(false);
    Vlay_1->addWidget(wgt_05);
    Vlay_1->addWidget(lbl_ch_OCX);
    Vlay_1->addWidget(list_vals_args);
    wgt_1->setLayout(Vlay_1);
   
    VLay_2->addWidget(lbl_val_args);
    VLay_2->addWidget(ScrollArea);
    VLay_2->addWidget(btn_choose);
    wgt_2->setLayout(VLay_2);

    VLay_3->addWidget(lbl_table_val);
    VLay_3->addWidget(tree_tbl_val);
    wgt_3->setLayout(VLay_3);
    menu->setVisible(false);
    spl_V->addWidget(menu);
    spl_V->addWidget(wgt_1);
    spl_V->addWidget(wgt_2);
    spl_V->addWidget(wgt_3);

    //tmp->setwd(Main_Vlay);

    spl_H->addWidget(chartview);
    spl_V->resize(400, 1000);
    spl_H->addWidget(spl_V);
    grd_central_lay->addWidget(spl_H);
    retranslateUi(this);

    QMetaObject::connectSlotsByName(this);
}
void Ui_Graph::retranslateUi(QWidget* graphics) {
    QTextCodec* codec = QTextCodec::codecForName(CODEC);
    QString str = codec->toUnicode("Табличные значения");
    lbl_table_val->setText(str);
    lbl_table_val->setFont(QFont(SHRIFT, mFON));
    str = codec->toUnicode("Укажите ось Х");
    lbl_ch_OCX->setText(str);
    lbl_ch_OCX->setFont(QFont(SHRIFT, mFON));
    str = codec->toUnicode("Выбрать");
    btn_choose->setText(str);
    btn_choose->setFont(QFont(SHRIFT, mFON));
    btn_choose->setVisible(false);
    str = codec->toUnicode("Точки построения");
    lbl_val_args->setText(str);
    lbl_val_args->setFont(QFont(SHRIFT, mFON));

    str = codec->toUnicode("Меню");
    menu->setWindowTitle(str);
    menu->setFont(QFont(SHRIFT, mFON));

    str = codec->toUnicode("Опции");
    Export_Pic->setTitle(str);
    Export_Pic->setFont(QFont(SHRIFT, mFON));

    str = codec->toUnicode("Экспорт");
    Export_Pic->setTitle(str);
    Export_Pic->setFont(QFont(SHRIFT, mFON));

    str = codec->toUnicode("Опции");
    menu_options->setTitle(str);
    menu_options->setFont(QFont(SHRIFT, mFON));

    str = codec->toUnicode("Очистить");
    act_delete_view->setText(str);
    act_delete_view->setFont(QFont(SHRIFT, mFON));

    str = codec->toUnicode("Легенда");
    act_align->setText(str);
    act_align->setFont(QFont(SHRIFT, mFON));

    str = codec->toUnicode("Настройка осей");
    act_OCXY->setText(str);
    act_OCXY->setFont(QFont(SHRIFT, mFON));

    str = codec->toUnicode("Выгрузить как PNG");
    act_Save_As_PNG->setText(str);
    act_Save_As_PNG->setFont(QFont(SHRIFT, mFON));

    str = codec->toUnicode("Выгрузить как JPEG");
    act_Save_As_JPEG->setText(str);
    act_Save_As_JPEG->setFont(QFont(SHRIFT, mFON));

    str = codec->toUnicode("Выгрузить как PDF");
    act_Save_As_PDF->setText(str);
    act_Save_As_PDF->setFont(QFont(SHRIFT, mFON));

    str = codec->toUnicode("Вкл/Выкл точки");
    act_opt_dots->setText(str);
    act_opt_dots->setFont(QFont(SHRIFT, mFON));

    str = codec->toUnicode("Вкл/Выкл линии");
    act_opt_lines->setText(str);
    act_opt_lines->setFont(QFont(SHRIFT, mFON));
    act_opt_lines->setVisible(false);

    str = codec->toUnicode("Вкл/Выкл сплайн");
    act_opt_splines->setText(str);
    act_opt_splines->setFont(QFont(SHRIFT, mFON));
    act_opt_splines->setVisible(false);

    str = codec->toUnicode("Вкл/Выкл анимацию");
    act_anime->setText(str);
    act_anime->setFont(QFont(SHRIFT, mFON));

    str = codec->toUnicode("Ось Х");
    lbl_X->setText(str);
    lbl_X->setFont(QFont(SHRIFT, mFON));

    str = codec->toUnicode("Ось У");
    lbl_Y->setText(str);
    lbl_Y->setFont(QFont(SHRIFT, mFON));

    str = codec->toUnicode("Удалить");
    act_del->setText(str);
    act_del->setFont(QFont(SHRIFT, mFON));
    const QIcon cutIcon = QIcon::fromTheme("edit-cut", QIcon(":/images/cut.png"));
    act_del->setIcon(cutIcon);
}
