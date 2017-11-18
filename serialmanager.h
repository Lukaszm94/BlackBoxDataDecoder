#ifndef SERIALMANAGER_H
#define SERIALMANAGER_H

#include <QObject>
#include <QSerialPort>

class SerialManager : public QObject
{
	Q_OBJECT
public:
	SerialManager(QObject* parent = 0);
	bool isConnected();
	bool connectToSerialPort(QString portName);
	bool disconnectFromSerialPort();

private slots:
	void onReadyRead();
	void onSerialPortError(QSerialPort::SerialPortError error);
signals:
	void onNewDataReady(QByteArray data);
	void serialPortError(QString errorMessage);
private:

	QSerialPort* serialPort;
};

#endif // SERIALMANAGER_H
