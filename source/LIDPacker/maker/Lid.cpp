/*!
********************************************************
*   @file Lid.cpp
*   @author Kalikin D.M. - ot.106
*   @date  09/02/2023
*   @brief реализация методов Lid.h
**********************************************************
*/

#include "LIDPacker/maker/Lid.h"
#include "LIDPacker/maker/Graph.h"
#include "LIDPacker/maker/Inter.h"
#include <LIDPacker/maker/stylesdefine.h>

#include <QSettings>
#include <QScreen>
#include <QCloseEvent>
#include <QMessageBox>
#include <QFileDialog>
namespace lid {
/* PUBLIC */
Lid::Lid(QWidget* parent)
    : QMainWindow(parent)
{
    QTextCodec::setCodecForLocale(QTextCodec::codecForName(ANSI));
    /* Объявления */
    ui  = new Ui::ULid();
    
    last_mod = 0;
    /* Запуск и настройка программы */
    ui->setupUi(this);

    QGuiApplication::setFallbackSessionManagementEnabled(false);
    setUnifiedTitleAndToolBarOnMac(true);
    setAcceptDrops(true);
 
    ui->action_mn_Analis->setVisible(false);
    ui->action_mn_Redact->setVisible(true);
 
    ReadSettings();
    this->setWindowTitle("LIDPacker. Current file -> " + path);

    AllConnects();
}

Lid::~Lid()
{
    delete ui;
}

/* PROTECTED */
void Lid::dragEnterEvent(QDragEnterEvent* event)
{
    if (event->mimeData()->hasUrls())
        event->accept();
}
void Lid::dropEvent(QDropEvent* event)
{
    if (event->mimeData()->hasUrls()) {
        QString str = event->mimeData()->urls().at(0).toLocalFile();
        path = str.toLocal8Bit();
        event->accept();
        
        if (path != "" || path != " ") {
            switch (last_mod)
            {
            case 0:
                Mod_View();
                break;
            case 1:
                Mod_Redaction();
                break;
            case 2:
                Mod_Analis();
                break;
            default:
                break;
            }
        }
    }
}
void Lid::closeEvent(QCloseEvent* event)
{
    if (MaybeSave()) {
        WriteSettings();
        event->accept();
    }
    else {
        event->ignore();
    }
}
/* PRIVATE */
/************************************************************************/
/* Чтение и запись настроек программы */
void Lid::ReadSettings() {
    QSettings settings(QCoreApplication::organizationName(), QCoreApplication::applicationName());
    QFileInfo inf;
    const QByteArray geometry   = settings.value("geometry", QByteArray()).toByteArray();
    const QByteArray _path      = settings.value("lastpath", QByteArray()).toByteArray();
    const QByteArray _mod       = settings.value("mod",      QByteArray()).toByteArray();
    const QByteArray _fill      = settings.value("fill",     QByteArray()).toByteArray();
    if (geometry.isEmpty()) 
    {
        const QRect availableGeometry = screen()->availableGeometry();
        resize(availableGeometry.width() / 1.5, availableGeometry.height() / 1.5);
    }
    else 
    {
        restoreGeometry(geometry);
    }
    inf.setFile(_path);
    if (_path.isEmpty() || !inf.exists())
    {
        path = "";
    }
    else
    {
        path = _path;
    }
    switch (_mod.toInt())
    {
    case 0:
        Mod_View();
        break;
    case 1:
        Mod_Redaction();
        break;
    case 2:
        Mod_Analis();
        break;
    default:
        break;
    }
}
void Lid::WriteSettings() {
    QSettings settings(QCoreApplication::organizationName(), QCoreApplication::applicationName());
    settings.setValue("geometry", saveGeometry());
    settings.setValue("lastpath", path);
    settings.setValue("mod", last_mod);
}
/* В конце работы программы предупреждение о сохранении */
bool Lid::MaybeSave() {
    const QMessageBox::StandardButton ret
        = QMessageBox::warning(this, tr("LIDPacker"),
            QString::fromLocal8Bit("Данные были изменены, хотите их сохранить?\nПуть файла: " + path.toLocal8Bit()),
            QMessageBox::Save | QMessageBox::Discard | QMessageBox::Cancel);

    switch (ret) {

    case QMessageBox::Save:
        return SaveFile();

    case QMessageBox::Cancel:
        return false;

    default:
        break;
    }
    return true;
}
QMenuBar* Lid::MakeFastMenu()
{
    QTextCodec::setCodecForLocale(QTextCodec::codecForName("Windows-1251"));

    QMenuBar* menu_P_N = new QMenuBar();//!< menu - Главное меню
    menu_P_N->setFont(QFont(SHRIFT, mFON));

    QAction* action_mn_Save_IMG     = new QAction(menu_P_N);
    QAction* action_mn_Save_As_IMG  = new QAction(menu_P_N);
    QAction* action_mn_Open_IMG     = new QAction(menu_P_N);
    QAction* action_mn_Interpol     = new QAction(menu_P_N);

    menu_P_N->addAction(action_mn_Open_IMG);
    menu_P_N->addAction(action_mn_Save_IMG);
    menu_P_N->addAction(action_mn_Save_As_IMG);
    menu_P_N->addSeparator();
    menu_P_N->addAction(action_mn_Interpol);

    const QIcon saveIcon    = QIcon::fromTheme("document-save",     QIcon(":/images/save.png"));
    const QIcon saveasIcon  = QIcon::fromTheme("document-save-as",  QIcon(":/images/paste.png"));
    const QIcon openIcon    = QIcon::fromTheme("document-open",     QIcon(":/images/open.png"));

    action_mn_Save_IMG->setIcon(saveIcon);
    action_mn_Save_IMG->setStatusTip(QString::fromLocal8Bit("Сохранить (Ctrl+S)"));

    action_mn_Save_As_IMG->setIcon(saveasIcon);
    action_mn_Save_As_IMG->setStatusTip(QString::fromLocal8Bit("Сохранить как (Ctrl+Shift+S)"));

    action_mn_Open_IMG->setIcon(openIcon);
    action_mn_Open_IMG->setStatusTip(QString::fromLocal8Bit("Открыть файл (Ctrl+O)"));

    QString translate = QString::fromLocal8Bit("Интерполяция");
    action_mn_Interpol->setText(translate);
    action_mn_Interpol->setFont(QFont(SHRIFT, mFON));
    action_mn_Interpol->setStatusTip(QString::fromLocal8Bit("Интерполяция"));
    //action_mn_Interpol->setVisible(false);
    QObject::connect(action_mn_Open_IMG,    SIGNAL(triggered()), SLOT(OpenFile()));
    QObject::connect(action_mn_Save_IMG,    SIGNAL(triggered()), SLOT(SaveFile()));
    QObject::connect(action_mn_Save_As_IMG, SIGNAL(triggered()), SLOT(SaveAsFile()));
    QObject::connect(action_mn_Interpol,    SIGNAL(triggered()), SLOT(App_Interpol()));
    return menu_P_N;
}
/************************************************************************/
/* PRIVATE SLOTS */
/************************************************************************/
/* Управление режимами программы */
void Lid::Mod_View()
{
    /* Режим под вопросом */
    Mod_Redaction();
}
void Lid::Mod_Redaction()
{
    last_mod = 1;
    ui->action_mn_Analis->setVisible(true);
    ui->action_mn_Redact->setVisible(false);
    Red = new Redaction(MakeFastMenu(), ui->statusbar);
    this->setCentralWidget(Red);
    if (path != "" && path != " ")
    {
        if (if_in_qvec(Vec_To_Files, path))
        {
            QAction* act = new QAction();
            act->setText(path);
            QObject::connect(act, SIGNAL(triggered()), SLOT(OpenLastFile()));
            ui->mn_last_Files->insertAction(ui->action_clear_last_Files, act);
            Vec_To_Files.append(path);
        }
        Red->set_path(path.toLocal8Bit());
    }
}
void Lid::Mod_Analis()
{
    last_mod = 2;
    ui->action_mn_Analis->setVisible(false);
    ui->action_mn_Redact->setVisible(true);
    Anls = new Graph();
    this->setCentralWidget(Anls);

    if (path != "" && path != " ")
    {
        if (if_in_qvec(Vec_To_Files, path))
        {
            QAction* act = new QAction();
            act->setText(path);
            QObject::connect(act, SIGNAL(triggered()), SLOT(OpenLastFile()));
            ui->mn_last_Files->insertAction(ui->action_clear_last_Files, act);
            Vec_To_Files.append(path);
        }
        Anls->set_path(path.toLocal8Bit());
    }
}
/* В РАЗРАБОТКЕ */
void Lid::App_Interpol()
{
    auto Red = (Redaction*)this->centralWidget();
    Q_CHECK_PTR(Red);
    /* В РАЗРАБОТКЕ */
    Inter* win = new Inter;
    win->show();
    win->set_interpolator(Red->get_interpolator());
}
/************************************************************************/
/* Работа с файлом */
bool Lid::OpenFile()
{
    QString str = QFileDialog::getOpenFileName(this, tr("Open File"), "", tr("Files "
        "(*.lid; *.dat; *.txt)"));

    if (!str.isEmpty()) {
        path = str;
        this->setWindowTitle("LIDPacker. Current file -> " + path);
    }
    else
    {
        return false;
    }
    
    switch (last_mod)
    {
    case 0:
        Mod_View();
        break;
    case 1:
        Mod_Redaction();
        break;
    case 2:
        Mod_Analis();
        break;
    default:
        break;
    }

    return false;
}
bool Lid::ResetFile()
{
    if (path != "" || path != " ")
    {
        switch (last_mod)
        {
        case 0:
            Mod_View();
            break;
        case 1:
            Mod_Redaction();
            break;
        case 2:
            Mod_Analis();
            break;
        default:
            break;
        }
        return true;
    }
    else
        return false;
}
bool Lid::SaveFile()
{
    if(!path.contains(".lid"))
        return SaveAsFile();
    if (path == "" || path == " ")
        return SaveAsFile();
    else
        return Red->save_as_binaries(path.toLocal8Bit());
}
bool Lid::SaveAsFile()
{
    QString str = QFileDialog::getSaveFileName(this, tr("Save File"), "", tr("Files"
        "(*.lid)"));
    this->setWindowTitle("LIDPacker. Current file -> " + str);
    if (!str.isEmpty()) 
    {
        path = str;
        return Red->save_as_binaries(path.toLocal8Bit());
    }
    return false;
}
void Lid::NewFile()
{
    this->setWindowTitle("LIDPacker. Last file was -> " + path);
    path = "";
    if (this->centralWidget() != nullptr)
        delete this->centralWidget();
    switch (last_mod)
    {
    case 0:
        Mod_View();
        break;
    case 1:
        Mod_Redaction();
        break;
    case 2:
        Mod_Analis();
        break;
    default:
        break;
    }
}
void Lid::Exit()
{
    this->close();
}
void Lid::OpenLastFile()
{
    QAction* cat;
    cat = qobject_cast<QAction*>(QObject::sender());
    path = cat->text();
    this->setWindowTitle("LIDPacker. Current file -> " + path);
    QFileInfo inf;
    inf.setFile(path);
    if (inf.exists())
        switch (last_mod)
        {
        case 0:
            Mod_View();
            break;
        case 1:
            Mod_Redaction();
            break;
        case 2:
            Mod_Analis();
            break;
        default:
            break;
        }
    else
        OpenFile();
}
void Lid::ClearLastFiles()
{
    QList<QAction*> tmp;
    tmp = ui->mn_last_Files->actions();
    for (int i = 0; i < tmp.size()-2; ++i)
        tmp[i]->deleteLater();
    Vec_To_Files.clear();
}
/************************************************************************/
/* Текстовая информация о ПК */
void Lid::INFOQT()
{
    QApplication::aboutQt();
}
void Lid::INFOLID()
{
    QTextCodec::setCodecForLocale(QTextCodec::codecForName("Windows-1251"));

    /*******************************************/
    const char message[] =
        "<p><b>Описание программы</b></p>"

        "<p> Программа предназначена для обработки базы исходных данных (БИД) для модуля многомерной интерполяции </p>"

        "<p>И для создание многомерной интерполяции (в режиме редактирование)</p>"

        "<p> Режимы работы: </p>"

        "<p><b>Интерполяция. В РАЗРАБОТКЕ</b></p>"

        "<p><b>Режим редактирования.</b></p>"

        "<p><b>Режим анализа.</b></p>"
        ;

    QString translate = QString::fromLocal8Bit(message);
    QMessageBox::about(this, tr("Linear Interpolation Data Packer (LIDPacker)"),
        translate);
}

} //end namespace lid
