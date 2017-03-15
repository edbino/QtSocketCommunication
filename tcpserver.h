#ifndef TCPSERVER_H
#define TCPSERVER_H

#include <QDebug>
#include <QTcpServer>
#include <QFile>
#include <QTextStream>
#include "tcpsocketconnection.h"

class TcpServer : public QTcpServer
{
    Q_OBJECT
public:
    explicit TcpServer(QObject *parent = 0);
    void startServer(QString rootDoc = 0);

signals:

public slots:

protected:
    void incomingConnection(int socketDescriptor);

private:
    QString port = "3000";
    QString fileSize = "1000";
    void requestHandler(QString rootDoc);
};

#endif // TCPSERVER_H
