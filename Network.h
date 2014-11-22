#ifndef NETWORK_H_
#define NETWORK_H_

#include <QDataStream>
#include <QTcpSocket>

#include "dataID_t.h"

class Network : QObject
{
    Q_OBJECT

public:
    void send(dataID_t dataID);
	void disconnect();
	bool connected();
    QDataStream& getSendStream() const;
    QDataStream& getReceiveStream() const;
	void connect();

private:
	QDataStream receiveStream;
	QDataStream sendStream;
	QTcpSocket socket;

private slots:
    void onReceive();

};
#endif // NETWORK_H_
