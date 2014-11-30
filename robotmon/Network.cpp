#include "Network.h"

Network::Network()
    : receiveStream(&socket),
      sendStream(sendArray)
{
    QObject::connect(&socket, SIGNAL(error(QAbstractSocket::SocketError)), this, SLOT(handleError(QAbstractSocket::SocketError)));
}

bool Network::connected() const
{
    return socket.state() == QTcpSocket::ConnectedState;
}

QDataStream & Network::getSendStream()
{
    return sendStream;
}

QDataStream & Network::getReceiveStream()
{
    return receiveStream;
}

void Network::connect()
{
    socket.connectToHost("localhost", 9999);
}

void Network::disconnect()
{
    socket.disconnectFromHost();
}

void Network::send()
{
    socket.write(sendArray);
}

void Network::handleError(QAbstractSocket::SocketError socketError)
{
    Q_UNUSED(socketError)
    emit this->errorOccurred(socket.errorString());
}

void Network::onReceive()
{
    // Monitor::receive() comes here.
    // TODO: we dont know if enough data available for a whole
    //       command at this time. See also Monitor::receive().
}
