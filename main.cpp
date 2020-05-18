#include <QtCore/QCoreApplication>
#include "qserver.h"

int main(int argc, char *argv[])
{
    qSetMessagePattern("[ %{file}: %{line} ] %{message}");
    QCoreApplication a(argc, argv);
    QString fullPath = QDir::cleanPath(a.applicationDirPath());
    int port = 8000;
    QServer Server(fullPath, port);
    Server.StartServer();
    return a.exec();
}