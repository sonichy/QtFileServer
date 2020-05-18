#include "qserver.h"
#include <QNetworkInterface>

QServer::QServer(QString storageFolder, int port, QObject *parent) :
    QTcpServer(parent)
{
    // Запоминаем рабочий каталог
    this->storageFolder = storageFolder;
    // Сохраняем номер порта, который слушает сервер
    this->port = port;
    // Проверяем есть ли рабочая директория указанная как хранилище
    if(!QDir(storageFolder).exists())
    {
        // Если нету - создаем пустую
        QDir().mkdir(storageFolder);
    }
}
// Запуск сервера
void QServer::StartServer()
{
    // Слушаем указанный порт
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
// Новый клиент
void QServer::incomingConnection(qintptr socketDescriptor)
{
    // Отладочное сообщение в консоль
    qDebug() << socketDescriptor << " Connecting...";
    // Создаем рабочий поток
    QClientThread *thread = new QClientThread( storageFolder, socketDescriptor, this );
    connect(thread, SIGNAL(finished()), thread, SLOT(deleteLater()));
    // Запускаем поток
    thread->start();
}
