/*!
********************************************************
*   @file Main.cpp
*   @author Kalikin D.M.
*   @date Ноябрь  01/11/2022
*   @brief Запуск главного класса Lid 
**********************************************************
*/
#include "LIDPacker/maker/Lid.h"

#include <QApplication>
#include <QCommandLineParser>

int main(int argc, char *argv[])
{
    //Q_INIT_RESOURCE(RIm);

    QApplication a(argc, argv);
    QApplication::setApplicationName("LIDPacker");
    QApplication::setOrganizationName("OKB");
    QApplication::setApplicationVersion(QT_VERSION_STR);
    QCommandLineParser parser;
    parser.setApplicationDescription("Kalibr_85");
    parser.addHelpOption();
    parser.addVersionOption();
    parser.process(a);
    //QString g = a.sessionId();
    //QString g2 = a.sessionKey();
    lid::Lid W;
    W.show();
    
    return a.exec();
}
