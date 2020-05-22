#include "qserver.h"
#include <QtCore/QCoreApplication>

int main(int argc, char *argv[])
{
    qSetMessagePattern("[ %{file}: %{line} ] %{message}");
    QCoreApplication a(argc, argv);    
    QString path = a.applicationDirPath();
    int port = 8000;
    QServer Server(path, port);
    Server.StartServer();
    return a.exec();
}