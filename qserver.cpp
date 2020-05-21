#include "qserver.h"
#include <QNetworkInterface>

QServer::QServer(QString storageFolder, int port, QObject *parent) :
    QTcpServer(parent)
{    
    this->storageFolder = storageFolder;    
    this->port = port;
}

void QServer::StartServer()
{    
    if(!this->listen(QHostAddress::Any, port))
    {
        qDebug() << "Could not start server";
    }
    else
    {
        QList<QNetworkInterface> list = QNetworkInterface::allInterfaces();
        foreach(QNetworkInterface interface, list) {
            QList<QNetworkAddressEntry> entryList = interface.addressEntries();
            foreach(QNetworkAddressEntry entry, entryList) {
                if(!entry.ip().toString().contains("::") && entry.ip().toString() != "127.0.0.1")
                    qDebug() << entry.ip().toString() + ":" + QString::number(port);
            }
        }
    }
}

void QServer::incomingConnection(qintptr socketDescriptor)
{   
    qDebug() << socketDescriptor << " Connecting...";   
    QClientThread *thread = new QClientThread( storageFolder, socketDescriptor, this );
    connect(thread, SIGNAL(finished()), thread, SLOT(deleteLater()));   
    thread->start();
}