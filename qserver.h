#ifndef QSERVER_H
#define QSERVER_H

#include <QTcpServer>
#include <QTcpSocket>
#include <QDebug>
#include <QDateTime>
#include "qclientthread.h"

class QServer : public QTcpServer
{
    Q_OBJECT

public:
    explicit QServer(QString storageFolder, int port, QObject *parent = nullptr);
    void StartServer();

protected:
    void incomingConnection(qintptr socketDescriptor);

private:
    QString storageFolder;
    int port;

};

#endif // QSERVER_H