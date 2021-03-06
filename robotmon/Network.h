#ifndef NETWORK_H_
#define NETWORK_H_

#include <QDataStream>
#include <QByteArray>
#include <QTcpSocket>

class Network : public QObject
{
    Q_OBJECT

public:
    Network();

    bool connected() const;
    QDataStream* getSendStream();
    QDataStream& getReceiveStream();

    void connect();
    void disconnect();
    void send();

signals:
    void errorOccurred(const QString&);
    void readyRead();

private:
    QTcpSocket socket;
    QDataStream receiveStream;
    QByteArray sendArray;

private slots:
    void handleError(QAbstractSocket::SocketError socketError);

};
#endif // NETWORK_H_
