#ifndef TCPSOCKETCONNECTION_H
#define TCPSOCKETCONNECTION_H

#include <QThread>
#include <QTcpSocket>
#include <QDebug>
#include <QFile>
#include <QTextStream>


class TcpSocketConnection : public QThread
{
    Q_OBJECT

public:
    explicit TcpSocketConnection(int ID, QObject *parent = 0, QString fileSize = 0);
    void run();
    ~TcpSocketConnection();

signals:
    void error(QTcpSocket::SocketError socketerror);

public slots:
    void readyRead();
    void disconnected();

private:
    QTcpSocket *socket;
    int socketDescriptor;
    int fileSize = 100;
    QString fileName = "stream";
    int i = 0;
    void dataHandler(QByteArray data);
};

#endif // TCPSOCKETCONNECTION_H
