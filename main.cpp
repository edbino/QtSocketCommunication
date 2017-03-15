#include <QCoreApplication>
#include "tcpserver.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    QString fileName("input.txt");
    TcpServer server;
    server.startServer(fileName);

    return a.exec();
}
