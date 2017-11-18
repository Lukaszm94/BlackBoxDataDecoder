#include "packetreceiever.h"
#include <QDebug>

PacketReceiver::PacketReceiver(QObject *parent) : QObject(parent)
{

}

void PacketReceiver::clearBuffer()
{
	buffer.clear();
}

void PacketReceiver::onNewData(QByteArray data)
{
	buffer.append(data);
	parseBuffer();
}

void PacketReceiver::parseBuffer()
{
	if(buffer.size() >= BB_DATA_PACKET_SIZE) {
		BBDataPacket packet;
		packet.deserialize(buffer);
		buffer.remove(0, BB_DATA_PACKET_SIZE);
		//buffer.clear();
		emit packetReceived(packet);
	}
}
