#ifndef APPLICATION_H
#define APPLICATION_H
#include <QApplication>
#include <QSerialPort>
#include <mainwindow.h>
#include "serialmanager.h"
#include "packetreceiever.h"
#include "bbdatapacket.h"

class Application : public QApplication
{
	Q_OBJECT
public:
	Application(int &argc, char **argv);

private slots:
	void onConnectSerialPortClicked(QString portName);
	void onNewPacketReceived(BBDataPacket& packet);

private:
	MainWindow gui;
	SerialManager* serialManager;
	PacketReceiver* packetReceiver;
};

#endif // APPLICATION_H
