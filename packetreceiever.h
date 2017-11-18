#ifndef PACKETRECEIEVER_H
#define PACKETRECEIEVER_H

#include <QObject>
#include "bbdatapacket.h"

class PacketReceiver : public QObject
{
	Q_OBJECT
public:
	PacketReceiver(QObject *parent = 0);
	void clearBuffer();

public slots:
	void onNewData(QByteArray data);

signals:
	void packetReceived(BBDataPacket& packet);

private:
	void parseBuffer();

	QByteArray buffer;
};

#endif // PACKETRECEIEVER_H
