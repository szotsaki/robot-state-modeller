#include "Network.h"

Network::Network()
    : receiveStream(&socket)
{
    QObject::connect(&socket, SIGNAL(error(QAbstractSocket::SocketError)), this, SLOT(handleError(QAbstractSocket::SocketError)));
    QObject::connect(&socket, SIGNAL(readyRead()), this, SIGNAL(readyRead()));
}

bool Network::connected() const
{
    return socket.state() == QTcpSocket::ConnectedState;
}

QDataStream * Network::getSendStream()
{
    return new QDataStream(&sendArray, QIODevice::WriteOnly);
}

QDataStream & Network::getReceiveStream()
{
    return receiveStream;
}

void Network::connect()
{
    socket.connectToHost("localhost", 9999, QIODevice::ReadWrite);
}

void Network::disconnect()
{
    socket.disconnectFromHost();
}

void Network::send()
{
    //qDebug() << "SendArray" << sendArray.size() << sendArray.toHex();
    socket.write(sendArray);
    sendArray.clear();
}

void Network::handleError(QAbstractSocket::SocketError socketError)
{
    Q_UNUSED(socketError)
    emit this->errorOccurred(socket.errorString());
}
