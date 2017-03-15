#include "tcpsocketconnection.h"

TcpSocketConnection::TcpSocketConnection(int ID, QObject *parent, QString fileSize) :
    QThread(parent)
{
    this->fileSize = fileSize.toInt();
    this->socketDescriptor = ID;
}
TcpSocketConnection::~TcpSocketConnection()
{
    socket->close();
    socket->deleteLater();
}

void TcpSocketConnection::run()
{
     qDebug() << "Starting Thread";
     socket = new QTcpSocket();

     if(!socket->setSocketDescriptor(this->socketDescriptor))
     {
        emit error(socket->error());
        return;
     }

     connect(socket, SIGNAL(readyRead()), this, SLOT(readyRead()), Qt::DirectConnection);
     connect(socket, SIGNAL(disconnected()), this, SLOT(disconnected()), Qt::DirectConnection);

     qDebug() << "Client Connected" << socketDescriptor;

     exec();
}

void TcpSocketConnection::readyRead()
{
    QByteArray data = socket->readAll();
    dataHandler(data);
}

void TcpSocketConnection::disconnected()
{
    qDebug() << socketDescriptor << " disconnected!";
    socket->deleteLater();
    exit(0);
}

void TcpSocketConnection::dataHandler(QByteArray data)
{
    QFile file(fileName);
    if(!file.open(QIODevice::WriteOnly | QIODevice::Append | QIODevice::Text))
    {
        qDebug() << "Failed to open file.";
        return;
    }
    if (file.size() >= fileSize)
    {
        file.close();
        fileName.append(QString::number(i++));
        file.setFileName(fileName);
        if(!file.open(QIODevice::WriteOnly | QIODevice::Append | QIODevice::Text))
        {
            qDebug() << "Failed to open file.";
            return;
        }
    }
    QTextStream ts(&file);
    ts << data;
    file.close();
}

