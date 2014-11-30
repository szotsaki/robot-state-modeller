#ifndef NETWORK_H_
#define NETWORK_H_

#include <QDataStream>
#include <QByteArray>
#include <QTcpSocket>

class Network : QObject
{
    Q_OBJECT

public:
    Network();

    bool connected() const;
    QDataStream& getSendStream();
    QDataStream& getReceiveStream();

    void connect();
    void disconnect();
    void send();

private:
    QTcpSocket socket;
    QDataStream receiveStream;
    QByteArray sendArray;
	QDataStream sendStream;

private slots:
    void onReceive();

};
#endif // NETWORK_H_
