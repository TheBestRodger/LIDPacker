#include "LIDPacker/maker/Graph.h"
#include <LIDPacker/maker/stylesdefine.h>
#include <LIDPacker/maker/Helper/ButtonArg.h>
#include <QMessageBox>
#include <QLineSeries>
#include <QFileDialog>
#include <QPrintDialog>
#include <QPrinter>
#include <QScatterSeries>
#include <QLegendMarker>
#include <QSplineSeries>
#include <QtConcurrent>

/*!
********************************************************
*	@file Graph.cpp
*	@author Kalikin D.M.
*	@date   09/01/2023
*	@brief Модуль содержит реализацию файла Graph.h
**********************************************************
*/

/* PUBLIC */
namespace lid
{
Graph::Graph(QWidget* parent)
    : QGraphicsView()
    , m_tooltip(0)
    , SrollAreaWidget(nullptr)
    , grid_args(nullptr)
    , pos_of_ocx(-1)
    , count_lines(0)

{
    ui = new Ui::UGraph();
    ui->setupUi(this);

    Args = std::make_shared<idArguments>();
    data = std::make_shared<Data>();
    TreeModel = new QStandardItemModel;
    chart = new Chart();
    axisX = new QValueAxis();
    axisY = new QValueAxis();
    connect(axisX, &QValueAxis::maxChanged, this, &Graph::updateViewOCXmax);
    connect(axisX, &QValueAxis::minChanged, this, &Graph::updateViewOCXmin);
    connect(axisY, &QValueAxis::maxChanged, this, &Graph::updateViewOCYmax);
    connect(axisY, &QValueAxis::minChanged, this, &Graph::updateViewOCYmin);
    chart->addAxis(axisX, Qt::AlignBottom);
    chart->addAxis(axisY, Qt::AlignLeft);
    dots            = false;
    lines           = false;
    splines         = false;
    anime           = false;
    align           = 0;
    //**//
    AllStaticConnects();

    this->setMouseTracking(true);
}
Graph::~Graph()
{
    delete ui;
}
void Graph::set_path(const char * _p)
{
    path = _p;
    science::Interpolator icz;
    try {
        if (path.contains(".lid"))
            icz.set_file(path, science::BINARY);
        else if (path.contains(".txt"))
            icz.set_file(path, science::TEXT);
        else if (path.contains(".dat"))
            icz.set_file(path, science::TEXT);
        else
            return;
    }
    catch (std::runtime_error const& err)
    {
        //QMessageBox ret;
        //ret.addButton(QString::fromLocal8Bit("Ок"), QMessageBox::AcceptRole);
        //ret.setText(path);
        //ret.setInformativeText("Error file!");
        //ret.setIcon(QMessageBox::Critical);
        //if (!(ret.exec() == QMessageBox::Accepted)){}
        //ret.deleteLater();
        return;
    }
    ConvertDataFromInterpol(icz);
    DrawNamesForOCX();
}
/* PRIVATE */
void Graph::ConvertDataFromInterpol(science::Interpolator& icz)
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
void Graph::DrawNamesForOCX()
{
    for (int i = 0; i < Args->Num(); ++i)
        ui->list_vals_args->addItem(Args->get_name(i));
}
void Graph::FormCoordinates()
{
    int ik = 0;
    int r = Args->Num();
    TextLineEdit* tmp;
    for (int i = 0; i < r; ++i)
    {
        if (i == pos_of_ocx)
            continue;
        int c = Args->get_full_scale_v(i).size();
        for (int j = 0; j < c; ++j)
        {
            tmp = (TextLineEdit*)grid_args->itemAtPosition(ik + 1, j)->widget();
            if (tmp->f)
            {
                QHash<int, QVector<int>>::iterator it;
                int p1 = tmp->pos_arg;
                int p2 = tmp->pos;
                it = AllCoordinates.find(p1);
                if (it != AllCoordinates.end())
                {
                    AllCoordinates.find(p1)->append(p2);
                    qSort(*AllCoordinates.find(p1));
                }
                else
                {
                    QVector<int> p;
                    p.append(p2);
                    AllCoordinates.insert(p1, p);
                }
            }
        }
        ik += 2;
    }
}
void Graph::MakeLinePoint(QVector<int> & _a, const QString & name)
{
    int clmn = Args->get_full_scale_v(pos_of_ocx).size();
    std::vector<int> AllOrd;
    for (int i = 0; i < Args->Num(); ++i)
        AllOrd.push_back(i);
    Dimensions* dim = new Dimensions(AllOrd, Args->get_Sizes());
    QVector<sreal_t> ans;
    QVector<int>::iterator it;
    QModelIndex index = TreeModel->index(count_lines, 0);

    TreeModel->itemFromIndex(TreeModel->index(count_lines, 0))->setTextAlignment(Qt::AlignCenter);
    TreeModel->itemFromIndex(TreeModel->index(count_lines, 0))->setFont(QFont(SHRIFT, mFON));
    TreeModel->itemFromIndex(TreeModel->index(count_lines, 0))->setEditable(false);
    TreeModel->setData(index, name);
    TreeModel->insertColumns(0, clmn, index);
    TreeModel->insertRows(0, 1, index);
    for (int i = 0; i < clmn; ++i)
    {
        _a.insert(pos_of_ocx, i);
        auto yx = dim->XYByArgs(_a.toStdVector());
        ans.append(data->get_data(yx[1], yx[0]));
        it = _a.begin();
        std::advance(it, pos_of_ocx);
        _a.erase(it);
        TreeModel->setData(TreeModel->index(0, i, index), QString::number(ans.at(i)), Qt::DisplayRole);
        TreeModel->itemFromIndex(TreeModel->index(0, i, index))->setEditable(false);
    }
    
    TreeModel->itemFromIndex(TreeModel->index(count_lines, 0))->setBackground(MakeLine(ans, name));
    delete dim;
}
QColor Graph::MakeLine(const QVector<sreal_t> & a, const QString & name)
{
    QScatterSeries* dots_series  = new QScatterSeries();
    QLineSeries* lines_series    = new QLineSeries();
    for (int i = 0; i < a.size(); ++i)
    {
        *dots_series   << QPointF(Args->get_full_scale_v(pos_of_ocx).at(i), a.at(i));
        *lines_series  << QPointF(Args->get_full_scale_v(pos_of_ocx).at(i), a.at(i));
    }
    chart->addSeries(dots_series);
    chart->addSeries(lines_series);

    dots_series->attachAxis(axisX);
    dots_series->attachAxis(axisY);
    dots_series->setName(name);

    QColor tmp = dots_series->color();
    lines_series->setColor(tmp);
    lines_series->attachAxis(axisX);
    lines_series->attachAxis(axisY);
    lines_series->setName(name);

    connect(dots_series, &QLineSeries::clicked, this, &Graph::keepCallout);
    connect(dots_series, &QLineSeries::hovered, this, &Graph::tooltip);

    connect(lines_series, &QSplineSeries::clicked, this, &Graph::keepCallout);
    connect(lines_series, &QSplineSeries::hovered, this, &Graph::tooltip);

    Max_Y = Max_list(a);
    Min_Y = Min_list(a);   
    return tmp;
}
void Graph::ClearTxt()
{
    int r = Args->Num();
    TextLineEdit* tmp;
    ButtonArg* tmp2;
    int ik = 0;
    for (int i = 0; i < r; ++i)
    {
        if (i == pos_of_ocx)
            continue;
        int c = Args->get_full_scale_v(i).size();
        tmp2 = (ButtonArg*)grid_args->itemAtPosition(ik, 0)->widget();
        tmp2->clicked_f = false;;
        for (int j = 0; j < c; ++j)
        {
            tmp = (TextLineEdit*)grid_args->itemAtPosition(ik + 1, j)->widget();
            tmp->clear_draw();
        }
        ik += 2;
    }
}
/* PRIVATE SLOTS */
void Graph::DrawArgsWithoutOCX(QListWidgetItem* item)
{
    if(count_lines > 0)
        if (!DeleteView())
            return;

    QString s = item->text();
    pos_of_ocx = Args->get_pos(s);
    int ik = 0;
    if (SrollAreaWidget == nullptr && grid_args == nullptr)
    {
        SrollAreaWidget = new QWidget();
        grid_args       = new QGridLayout();
    }
    else
    {
        SrollAreaWidget->layout()->deleteLater();
        delete SrollAreaWidget;
        SrollAreaWidget = new QWidget();
        grid_args       = new QGridLayout();
    }
    for (int i = 0; i < Args->Num(); ++i)
    {
        if (i == pos_of_ocx)
        {
            int siz = Args->get_full_scale_v(pos_of_ocx).size();

            axisX->setTickCount(siz);
            axisX->setMinorTickCount(4);
            axisX->setTitleText(s);
            axisX->setTitleFont(QFont(SHRIFT, FON));

            axisY->setTickCount(siz);
            axisY->setMinorTickCount(4);
            axisY->setTitleText(data->get_name_tdata());
            axisY->setTitleFont(QFont(SHRIFT, FON));

            Max_X = Args->get_max_scale(pos_of_ocx);
            ui->SpinBox_X_top->setValue(Max_X);
            Min_X = Args->get_min_scale(pos_of_ocx);
            ui->SpinBox_X_dwn->setValue(Min_X);

            if (Max_X < 1 && Max_X > 0)
                ui->SpinBox_X_top->setSingleStep(0.1);
            else
                ui->SpinBox_X_top->setSingleStep(1);

            if (Min_X < 1 && Min_X > 0)
                ui->SpinBox_X_dwn->setSingleStep(0.1);
            else
                ui->SpinBox_X_dwn->setSingleStep(1);

            continue;
        }
            
        ButtonArg* btn = new ButtonArg();
        //std::shared_ptr<QPushButton> btn = std::make_shared<QPushButton>();
        btn->setText(Args->get_name(i));
        btn->pos_as_btn = ik;
        btn->pos_as_arg = i;
        QObject::connect(btn, &QPushButton::clicked, this, &Graph::ChooseAllArg);
        grid_args->addWidget(btn, ik, 0);
        for (int j = 0; j < Args->get_full_scale_v(i).size(); ++j)
        {
            TextLineEdit* txt = new TextLineEdit();
            //std::shared_ptr<TextLineEdit> txt = std::make_shared<TextLineEdit>();
            txt->setText(QString::number(Args->get_full_scale_v(i)[j]));
            txt->pos_arg = i;
            txt->pos = j;
            grid_args->addWidget(txt, ik + 1, j);
            
        }
        ik += 2;
    }
    SrollAreaWidget->setLayout(grid_args);
    ui->ScrollArea->setWidget(SrollAreaWidget);
    ui->btn_choose->setVisible(true);
}
void Graph::DrawTableVals()
{
    FormCoordinates();
    if (AllCoordinates.size() != Args->Num()-1)
       return;
    ui->menu->setVisible(true);
    QVector<int> pos_args;
    int row = TreeModel->rowCount() + 1;
    for (int i = 0; i < Args->Num(); ++i)
    {
        if (i == pos_of_ocx)
            continue;
        pos_args.append(i);
        row *= AllCoordinates.find(i)->size();
    }
    row += TreeModel->rowCount();
    TreeModel->setRowCount(row);
    TreeModel->setColumnCount(Args->get_full_scale_v(pos_of_ocx).size());

    manager(Args->Num(), pos_args);// В процессе много поточности

    ui->tree_tbl_val->setModel(TreeModel);
    ui->chartview->setRenderHint(QPainter::Antialiasing);
    ui->chartview->setChart(chart);
}
void Graph::ChooseAllArg()
{
    TextLineEdit* tmp;
    ButtonArg* cat;
    cat = qobject_cast<ButtonArg*>(sender());

    int b = cat->pos_as_btn;
    int a = cat->pos_as_arg;
    int c = Args->get_full_scale_v(a).size();

    if (!cat->clicked_f)
    {
        cat->clicked_f = true;
        for (int j = 0; j < c; ++j)
        {
            tmp = (TextLineEdit*)grid_args->itemAtPosition(b + 1, j)->widget();
            tmp->make_draw();
        }
    }
    else
    {
        cat->clicked_f = false;
        for (int j = 0; j < c; ++j)
        {
            tmp = (TextLineEdit*)grid_args->itemAtPosition(b + 1, j)->widget();
            tmp->clear_draw();
        }
    }

}
bool Graph::DeleteView()
{
    QMessageBox ret;
    ret.resize(200, 200);
    ret.addButton(QString::fromLocal8Bit("Ок"), QMessageBox::AcceptRole);
    ret.addButton(QString::fromLocal8Bit("No"), QMessageBox::RejectRole);
    ret.setText("Attention!");
    ret.setInformativeText("Graph delete");
    ret.setIcon(QMessageBox::Warning);
    if (!(ret.exec() == QMessageBox::Accepted))
    {
        ui->menu->setVisible(true);
        chart->removeAllSeries();
        delete axisX;
        delete axisY;
        axisX = new QValueAxis();
        axisY = new QValueAxis();
        connect(axisX, &QValueAxis::maxChanged, this, &Graph::updateViewOCXmax);
        connect(axisX, &QValueAxis::minChanged, this, &Graph::updateViewOCXmin);
        connect(axisY, &QValueAxis::maxChanged, this, &Graph::updateViewOCYmax);
        connect(axisY, &QValueAxis::minChanged, this, &Graph::updateViewOCYmin);
        chart->addAxis(axisX, Qt::AlignBottom);
        chart->addAxis(axisY, Qt::AlignLeft);
        Max_X = Min_X = Max_Y = Min_Y = NULL;
        TreeModel->clear();
        pos_of_ocx = -1;
        ui->btn_choose->setVisible(false);
        ui->menu->setVisible(false);
        ui->wgt_05->setVisible(false);
        count_lines = 0;
        m_callouts.clear();
        SrollAreaWidget->layout()->deleteLater();
        delete SrollAreaWidget;
        SrollAreaWidget = nullptr;
        grid_args       = nullptr;
        return true;
    }
    return false;
    ret.deleteLater();
}
void Graph::DeleteLine()
{
    int pos_d = ui->tree_tbl_val->selectionModel()->currentIndex().row();
    TreeModel->removeRow(pos_d);
    QList<QAbstractSeries*> lst;
    lst = chart->series();
    pos_d *= 2;
    chart->removeSeries(lst.at(pos_d));
    chart->removeSeries(lst.at(pos_d + 1));
    count_lines--;
    if (count_lines <= 0)
    {
        int tmp = pos_of_ocx;
        DeleteView();
        pos_of_ocx = tmp;
    }
}
void Graph::showContextMenu(QPoint pos)
{
    if (count_lines <= 0)
        return;
    ui->del_menu->popup(ui->tree_tbl_val->viewport()->mapToGlobal(pos));
}
/*********************************************************/
/* Callout */
void Graph::resizeEvent(QResizeEvent* event)
{
    if (scene()) {
        scene()->setSceneRect(QRect(QPoint(0, 0), event->size()));
        chart->resize(event->size());
        m_coordX->setPos(chart->size().width() / 2 - 50, chart->size().height() - 20);
        m_coordY->setPos(chart->size().width() / 2 + 50, chart->size().height() - 20);
        const auto callouts = m_callouts;
        for (Callout* callout : callouts)
            callout->updateGeometry();
    }
    QGraphicsView::resizeEvent(event);
}

void Graph::mouseMoveEvent(QMouseEvent* event)
{
    //m_coordX->setText(QString("X: %1").arg(m_chart->mapToValue(event->pos()).x()));
    //m_coordY->setText(QString("Y: %1").arg(m_chart->mapToValue(event->pos()).y()));
    QGraphicsView::mouseMoveEvent(event);
}

void Graph::keepCallout()
{
    //m_callouts.append(m_tooltip);
    //m_tooltip = new Callout(chart);
}

void Graph::tooltip(QPointF point, bool state)
{
    if (m_tooltip == 0)
        m_tooltip = new Callout(chart);

    if (state) {
        m_tooltip->setText(QString("X: %1 \nY: %2 ").arg(point.x()).arg(point.y()));
        m_tooltip->setAnchor(point);
        m_tooltip->setZValue(11);
        m_tooltip->updateGeometry();
        m_tooltip->show();
    }
    else {
        m_tooltip->hide();
    }
}
/*********************************************************/
void Graph::PosAlign()
{
    switch (align)
    {
    case 0:
        align = 1;
        chart->legend()->setAlignment(Qt::AlignLeft);
        break;

    case 1:
        align = 2;
        chart->legend()->setAlignment(Qt::AlignBottom);
        break;

    case 2:
        align = 3;
        chart->legend()->setAlignment(Qt::AlignRight);
        break;

    case 3:
        align = 0;
        chart->legend()->setAlignment(Qt::AlignTop);
        break;

    default:
        break;
    }
}

void Graph::Print_PDF() {
    QPrinter* printer = new QPrinter();
    printer->setOrientation(QPrinter::Landscape);
    QPrintDialog* dialog = new QPrintDialog(printer);
    dialog->setWindowTitle("Print Plots");
    if (dialog->exec() != QDialog::Accepted)
        return;
    QPainter* painter = new QPainter();
    painter->begin(printer);
    painter->setRenderHints(QPainter::Antialiasing);
    ui->chartview->render(painter, printer->pageRect());
    painter->end();
    delete dialog;
    delete painter;
    delete printer;
}
void Graph::Print_PNG() {
    QPixmap* pix = new QPixmap(ui->chartview->size());
    (*pix) = ui->chartview->grab();
    QString strtm = QFileDialog::getSaveFileName(this,
        "Select a Directory", "", "*.png");
    bool f = pix->save(strtm, "PNG");
    delete pix;
}
void Graph::Print_JPEG() {
    QPixmap* pix = new QPixmap(ui->chartview->size());
    (*pix) = ui->chartview->grab();
    QString strtm = QFileDialog::getSaveFileName(this,
        "Select a Directory", "", "*.jpeg");
    bool f = pix->save(strtm, "JPEG");
    delete pix;
}

void Graph::OnOffDots()
{
    QList<QAbstractSeries*> lst;
    lst = chart->series();
    if (dots)
    {
        for (int i = 0; i < lst.size(); i += 2)
        {
            lst[i]->setVisible(true);
        }
        dots = false;
    }
    else
    {
        for (int i = 0; i < lst.size(); i += 2)
        {
            lst[i]->setVisible(false);
        }
        dots = true;
    }
    const auto markers = chart->legend()->markers();
    int mod_k = 0;
    for (QLegendMarker* marker : markers) {
        if (mod_k % 2 == 0)
            marker->setVisible(false);
        ++mod_k;
    }
}
void Graph::OnOffLines()
{
    QList<QAbstractSeries*> lst;
    lst = chart->series();
    if (lines)
    {
        lines = false;
    }
    else
    {
        lines = true;
    }
}
void Graph::OnOffSpline()
{
    if (splines)
    {
        splines = false;
    }
    else
    {
        splines = true;
    }
}
void Graph::OnOffAnime()
{
    if (anime)
    {
        anime = false;
        ui->chartview->chart()->setAnimationOptions(QChart::NoAnimation);
    }
    else
    {
        ui->chartview->chart()->setAnimationOptions(QChart::GridAxisAnimations);
        ui->chartview->chart()->setAnimationOptions(QChart::SeriesAnimations);
        anime = true;
    }
}

void Graph::OptOCXY()
{
    ui->SpinBox_Y_top->setValue(Max_Y);
    ui->SpinBox_Y_dwn->setValue(Min_Y);
    if (ui->wgt_05->isVisible())
        ui->wgt_05->setVisible(false);
    else
        ui->wgt_05->setVisible(true);
}
void Graph::updateViewOCXmax(qreal Max_x)
{
    ui->SpinBox_X_top->setValue(Max_x);
}
void Graph::updateViewOCXmin(qreal Min_x)
{
    ui->SpinBox_X_dwn->setValue(Min_x);
}
void Graph::updateViewOCYmax(qreal Max_y)
{
    ui->SpinBox_Y_top->setValue(Max_y);
}
void Graph::updateViewOCYmin(qreal Min_y)
{
    ui->SpinBox_Y_dwn->setValue(Min_y);
}
void Graph::Max_OCX()
{
    double tmp = ui->SpinBox_X_top->value();
    if (tmp < 1 && tmp > 0)
        ui->SpinBox_X_top->setSingleStep(0.1);
    else
        ui->SpinBox_X_top->setSingleStep(1);

    chart->axisX()->setMax(ui->SpinBox_X_top->value());
    Max_X = ui->SpinBox_X_top->value();
}
void Graph::Min_OCX()
{
    double tmp = ui->SpinBox_X_dwn->value();
    if (tmp < 1 && tmp > 0)
        ui->SpinBox_X_dwn->setSingleStep(0.1);
    else
        ui->SpinBox_X_dwn->setSingleStep(1);

    chart->axisX()->setMin(ui->SpinBox_X_dwn->value());
    Min_X = ui->SpinBox_X_dwn->value();
}
void Graph::Max_OCY()
{
    double tmp = ui->SpinBox_Y_top->value();
    if (tmp < 1 && tmp > 0)
        ui->SpinBox_Y_top->setSingleStep(0.1);
    else
        ui->SpinBox_Y_top->setSingleStep(1);

    chart->axisY()->setMax(ui->SpinBox_Y_top->value());
    Max_Y = ui->SpinBox_Y_top->value();
}
void Graph::Min_OCY()
{
    double tmp = ui->SpinBox_Y_dwn->value();
    if (tmp < 1 && tmp > 0)
        ui->SpinBox_Y_dwn->setSingleStep(0.1);
    else
        ui->SpinBox_Y_dwn->setSingleStep(1);

    chart->axisY()->setMin(ui->SpinBox_Y_dwn->value());
    Min_Y = ui->SpinBox_Y_dwn->value();
}

const sreal_t Graph::Max_list(const QVector<sreal_t> & scale_v)
{
    sreal_t max = scale_v[0];
    for (int i = 1; i < scale_v.size(); ++i)
        if (max < scale_v[i])
            max = scale_v[i];
    return max;
}
const sreal_t Graph::Min_list(const QVector<sreal_t> & scale_v)
{
    sreal_t min = scale_v[0];
    for (int i = 1; i < scale_v.size(); ++i)
        if (min > scale_v[i])
            min = scale_v[i];
    return min;
}


void Graph::manager(int R, QVector<int> _p)
{
   
    switch (R)
    {
    case 1:
        R1(_p);
        break;
    case 2:
        R2(_p);
        break;
    case 3:
        R3(_p);
        break;
    case 4:
        R4(_p);
        break;
    case 5:
        R5(_p);
        break;
    case 6:
        R6(_p);
        break;
    case 7:
        R7(_p);
        break;
    default:
        break;
    }
}
void Graph::R1(QVector<int> pos_args)
{
    return;
}
void Graph::R2(QVector<int> pos_args)
{
    QString name_line;
    QVector<int> a;
    for (int i = 0; i < AllCoordinates.find(pos_args.at(0))->size(); ++i)
    {
        a.clear();
        a.push_back(AllCoordinates.find(pos_args.at(0))->at(i));

        name_line = "\n";

        name_line += Args->get_name(pos_args.at(0));
        name_line += " = " + QString::number(Args->get_full_scale_v(pos_args.at(0))[a[0]]);

        MakeLinePoint(a, name_line);
        count_lines++;
    }
    const auto markers = chart->legend()->markers();
    int mod_k = 0;
    for (QLegendMarker* marker : markers) {
        if (mod_k % 2 == 0)
            marker->setVisible(false);
        ++mod_k;
    }
    ClearTxt();
    AllCoordinates.clear();
}
void Graph::R3(QVector<int> pos_args)
{
    QString name_line;
    QVector<int> a;
    for (int i = 0; i < AllCoordinates.find(pos_args.at(0))->size(); ++i)
    {
        for (int j = 0; j < AllCoordinates.find(pos_args.at(1))->size(); ++j)
        {
                a.clear();
                a.push_back(AllCoordinates.find(pos_args.at(0))->at(i));
                a.push_back(AllCoordinates.find(pos_args.at(1))->at(j));
                name_line = "\n";

                name_line += Args->get_name(pos_args.at(0));
                name_line += " = " + QString::number(Args->get_full_scale_v(pos_args.at(0))[a[0]]) + "\n";

                name_line += Args->get_name(pos_args.at(1));
                name_line += " = " + QString::number(Args->get_full_scale_v(pos_args.at(1))[a[1]]);

                MakeLinePoint(a, name_line);
                count_lines++;
        }
    }
    const auto markers = chart->legend()->markers();
    int mod_k = 0;
    for (QLegendMarker* marker : markers) {
        if (mod_k % 2 == 0)
            marker->setVisible(false);
        ++mod_k;
    }
    ClearTxt();
    AllCoordinates.clear();
}
void Graph::R4(QVector<int> pos_args)
{
    QString name_line;
    QVector<int> a;
    for (int i = 0; i < AllCoordinates.find(pos_args.at(0))->size(); ++i)
    {
        for (int j = 0; j < AllCoordinates.find(pos_args.at(1))->size(); ++j)
        {
            for (int k = 0; k < AllCoordinates.find(pos_args.at(2))->size(); ++k)
            {
                a.clear();
                a.push_back(AllCoordinates.find(pos_args.at(0))->at(i));
                a.push_back(AllCoordinates.find(pos_args.at(1))->at(j));
                a.push_back(AllCoordinates.find(pos_args.at(2))->at(k));
                name_line = "\n";

                name_line += Args->get_name(pos_args.at(0));
                name_line += " = " + QString::number(Args->get_full_scale_v(pos_args.at(0))[a[0]]) + "\n";

                name_line += Args->get_name(pos_args.at(1));
                name_line += " = " + QString::number(Args->get_full_scale_v(pos_args.at(1))[a[1]]) + "\n";

                name_line += Args->get_name(pos_args.at(2));
                name_line += " = " + QString::number(Args->get_full_scale_v(pos_args.at(2))[a[2]]);
                MakeLinePoint(a, name_line);
                count_lines++;
            }
        }
    }
    const auto markers = chart->legend()->markers();
    int mod_k = 0;
    for (QLegendMarker* marker : markers) {
        if (mod_k % 2 == 0)
            marker->setVisible(false);
        ++mod_k;
    }
    ClearTxt();
    AllCoordinates.clear();
}
void Graph::R5(QVector<int> pos_args)
{
    QString name_line;
    QVector<int> a;
    for (int i = 0; i < AllCoordinates.find(pos_args.at(0))->size(); ++i)
    {
        for (int j = 0; j < AllCoordinates.find(pos_args.at(1))->size(); ++j)
        {
            for (int k = 0; k < AllCoordinates.find(pos_args.at(2))->size(); ++k)
            {
                for (int z = 0; z < AllCoordinates.find(pos_args.at(3))->size(); ++z)
                {
                    a.clear();
                    a.push_back(AllCoordinates.find(pos_args.at(0))->at(i));
                    a.push_back(AllCoordinates.find(pos_args.at(1))->at(j));
                    a.push_back(AllCoordinates.find(pos_args.at(2))->at(k));
                    a.push_back(AllCoordinates.find(pos_args.at(3))->at(z));

                    name_line = "\n";

                    name_line += Args->get_name(pos_args.at(0));
                    name_line += " = " + QString::number(Args->get_full_scale_v(pos_args.at(0))[a[0]]) + "\n";

                    name_line += Args->get_name(pos_args.at(1));
                    name_line += " = " + QString::number(Args->get_full_scale_v(pos_args.at(1))[a[1]]) + "\n";

                    name_line += Args->get_name(pos_args.at(2));
                    name_line += " = " + QString::number(Args->get_full_scale_v(pos_args.at(2))[a[2]]) + "\n";

                    name_line += Args->get_name(pos_args.at(3));
                    name_line += " = " + QString::number(Args->get_full_scale_v(pos_args.at(3))[a[3]]);

                    MakeLinePoint(a, name_line);
                    count_lines++;
                }
            }
        }
    }
    const auto markers = chart->legend()->markers();
    int mod_k = 0;
    for (QLegendMarker* marker : markers) {
        if (mod_k % 2 == 0)
            marker->setVisible(false);
        ++mod_k;
    }
    ClearTxt();
    AllCoordinates.clear();
}
void Graph::R6(QVector<int> pos_args)
{
    QString name_line;
    QVector<int> a;
    for (int i = 0; i < AllCoordinates.find(pos_args.at(0))->size(); ++i)
    {
        for (int j = 0; j < AllCoordinates.find(pos_args.at(1))->size(); ++j)
        {
            for (int k = 0; k < AllCoordinates.find(pos_args.at(2))->size(); ++k)
            {
                for (int z = 0; z < AllCoordinates.find(pos_args.at(3))->size(); ++z)
                {
                    for (int x = 0; x < AllCoordinates.find(pos_args.at(4))->size(); ++x)
                    {
                        a.clear();
                        a.push_back(AllCoordinates.find(pos_args.at(0))->at(i));
                        a.push_back(AllCoordinates.find(pos_args.at(1))->at(j));
                        a.push_back(AllCoordinates.find(pos_args.at(2))->at(k));
                        a.push_back(AllCoordinates.find(pos_args.at(3))->at(z));
                        a.push_back(AllCoordinates.find(pos_args.at(4))->at(x));

                        name_line = "\n";

                        name_line += Args->get_name(pos_args.at(0));
                        name_line += " = " + QString::number(Args->get_full_scale_v(pos_args.at(0))[a[0]]) + "\n";

                        name_line += Args->get_name(pos_args.at(1));
                        name_line += " = " + QString::number(Args->get_full_scale_v(pos_args.at(1))[a[1]]) + "\n";

                        name_line += Args->get_name(pos_args.at(2));
                        name_line += " = " + QString::number(Args->get_full_scale_v(pos_args.at(2))[a[2]]) + "\n";

                        name_line += Args->get_name(pos_args.at(3));
                        name_line += " = " + QString::number(Args->get_full_scale_v(pos_args.at(3))[a[3]]);

                        name_line += Args->get_name(pos_args.at(4));
                        name_line += " = " + QString::number(Args->get_full_scale_v(pos_args.at(4))[a[4]]);

                        MakeLinePoint(a, name_line);
                        count_lines++;
                    }
                }
            }
        }
    }
    const auto markers = chart->legend()->markers();
    int mod_k = 0;
    for (QLegendMarker* marker : markers) {
        if (mod_k % 2 == 0)
            marker->setVisible(false);
        ++mod_k;
    }
    ClearTxt();
    AllCoordinates.clear();
}
void Graph::R7(QVector<int> pos_args)
{
    QString name_line;
    QVector<int> a;
    for (int i = 0; i < AllCoordinates.find(pos_args.at(0))->size(); ++i)
    {
        for (int j = 0; j < AllCoordinates.find(pos_args.at(1))->size(); ++j)
        {
            for (int k = 0; k < AllCoordinates.find(pos_args.at(2))->size(); ++k)
            {
                for (int z = 0; z < AllCoordinates.find(pos_args.at(3))->size(); ++z)
                {
                    for (int x = 0; x < AllCoordinates.find(pos_args.at(4))->size(); ++x)
                    {
                        for (int y = 0; y < AllCoordinates.find(pos_args.at(5))->size(); ++y)
                        {
                            a.clear();
                            a.push_back(AllCoordinates.find(pos_args.at(0))->at(i));
                            a.push_back(AllCoordinates.find(pos_args.at(1))->at(j));
                            a.push_back(AllCoordinates.find(pos_args.at(2))->at(k));
                            a.push_back(AllCoordinates.find(pos_args.at(3))->at(z));
                            a.push_back(AllCoordinates.find(pos_args.at(4))->at(x));
                            a.push_back(AllCoordinates.find(pos_args.at(5))->at(y));

                            name_line = "\n";

                            name_line += Args->get_name(pos_args.at(0));
                            name_line += " = " + QString::number(Args->get_full_scale_v(pos_args.at(0))[a[0]]) + "\n";

                            name_line += Args->get_name(pos_args.at(1));
                            name_line += " = " + QString::number(Args->get_full_scale_v(pos_args.at(1))[a[1]]) + "\n";

                            name_line += Args->get_name(pos_args.at(2));
                            name_line += " = " + QString::number(Args->get_full_scale_v(pos_args.at(2))[a[2]]) + "\n";

                            name_line += Args->get_name(pos_args.at(3));
                            name_line += " = " + QString::number(Args->get_full_scale_v(pos_args.at(3))[a[3]]);

                            name_line += Args->get_name(pos_args.at(4));
                            name_line += " = " + QString::number(Args->get_full_scale_v(pos_args.at(4))[a[4]]);

                            name_line += Args->get_name(pos_args.at(5));
                            name_line += " = " + QString::number(Args->get_full_scale_v(pos_args.at(5))[a[5]]);

                            MakeLinePoint(a, name_line);
                            count_lines++;
                        }
                    }
                }
            }
        }
    }
    const auto markers = chart->legend()->markers();
    int mod_k = 0;
    for (QLegendMarker* marker : markers) {
        if (mod_k % 2 == 0)
            marker->setVisible(false);
        ++mod_k;
    }
    ClearTxt();
    AllCoordinates.clear();
}

}


