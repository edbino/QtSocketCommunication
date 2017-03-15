#include "tcpserver.h"

TcpServer::TcpServer(QObject *parent) :
    QTcpServer(parent)
{

}
void TcpServer::startServer(QString rootDoc)
{
    requestHandler(rootDoc);

    if(!this->listen(QHostAddress::Any, port.toInt()))
    {
        qDebug() << "Could not start server...";
    }
    else
    {
        qDebug() << "Server started!";
        qDebug() << "Listening...";
    }
}

void TcpServer::incomingConnection(int socketDescriptor)
{
     qDebug() << socketDescriptor << "Connecting...";
     TcpSocketConnection *connection = new TcpSocketConnection(socketDescriptor, this, fileSize);
     connect(connection, SIGNAL(finished()), connection, SLOT(deleteLater()));
     connection->start();
}

void TcpServer::requestHandler(QString rootDoc)
{
    QFile file(rootDoc);
    if(!file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        qDebug() << "Failed to open file.";
        return;
    }
    QTextStream ts(&file);
    port = ts.readLine();
    fileSize = ts.readLine();
    file.close();
}
