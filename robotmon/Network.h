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
    QDataStream& getSendStream();
    QDataStream& getReceiveStream();

    void connect();
    void disconnect();
    void send();

signals:
    void errorOccurred(const QString&);

private:
    QTcpSocket socket;
    QDataStream receiveStream;
    QByteArray sendArray;
	QDataStream sendStream;


private slots:
    void onReceive();
    void handleError(QAbstractSocket::SocketError socketError);

};
#endif // NETWORK_H_
