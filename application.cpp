#include "application.h"
#include <QDebug>

Application::Application(int &argc, char **argv) : QApplication(argc, argv)
{
	//TODO init stuff
	serialManager = new SerialManager;
	packetReceiver = new PacketReceiver;
	gui.show();

	connect(serialManager, SIGNAL(onNewDataReady(QByteArray)), packetReceiver, SLOT(onNewData(QByteArray)));
	connect(packetReceiver, SIGNAL(packetReceived(BBDataPacket&)), this, SLOT(onNewPacketReceived(BBDataPacket&)));
	connect(&gui, SIGNAL(connectSerialPort(QString)), this, SLOT(onConnectSerialPortClicked(QString)));

}

void Application::onConnectSerialPortClicked(QString portName)
{

	if(serialManager->isConnected()) {
		serialManager->disconnectFromSerialPort();
		gui.setSerialConnected(false);
	} else {
		if(serialManager->connectToSerialPort(portName)) {
			gui.setSerialConnected(true);
		} else {
			//TODO show error
		}
	}
	packetReceiver->clearBuffer();
}

void Application::onNewPacketReceived(BBDataPacket& packet)
{
	gui.appendRawData(packet.toQString());
	gui.appendProcessedData(packet.toProcessedDataPacket().toQString());
	qDebug() << packet.toQString();
}
