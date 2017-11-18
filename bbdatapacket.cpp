#include "bbdatapacket.h"
#include <QTextStream>
#include <QDebug>

BBDataPacket::BBDataPacket(QObject *parent) : QObject(parent)
{

}

void BBDataPacket::deserialize(QByteArray raw)
{
	qDebug() << "BBDataPacket::deserialize(): buffer size: " << raw.size() << ",data: " << raw;
	char* buffer = raw.data();
	memcpy((void*)(&tick), buffer, 2);
	flight_state = buffer[2];
	memcpy(&v_bat, &buffer[3], 2);
	memcpy(&v_pbat, &buffer[5], 2);
	for(int i = 0; i < 6; i++) {
		voltages[i] = buffer[i + 7];
	}
	orient = buffer[13];
	memcpy(&speed, &buffer[14], 2);
	memcpy(&height, &buffer[16], 2);

	memcpy(&pres, &buffer[18], 4);
	memcpy(&temp, &buffer[22], 2);

	memcpy(&accel_x, &buffer[24], 2);
	memcpy(&accel_y, &buffer[26], 2);
	memcpy(&accel_z, &buffer[28], 2);

	memcpy(&gyro_x, &buffer[30], 2);
	memcpy(&gyro_y, &buffer[32], 2);
	memcpy(&gyro_z, &buffer[34], 2);

	memcpy(&mag_x, &buffer[36], 2);
	memcpy(&mag_y, &buffer[38], 2);
	memcpy(&mag_z, &buffer[40], 2);
}

QString BBDataPacket::toQString() const
{
	QString str;
	QTextStream stream(&str);
	stream << tick << "," << flight_state << ",";
	for(int i = 0; i < 8; i++) {
		stream << (int)voltages[i] << ",";
	}
	stream << orient << "," << speed << "," << height << "," << pres << "," << temp << "," << accel_x << "," << accel_y << "," << accel_z;
	stream << "," << gyro_x << "," << gyro_y << "," << gyro_z << "," << mag_x << "," << mag_y << "," << mag_z;
	return str;
}

ProcessedDataPacket BBDataPacket::toProcessedDataPacket()
{
	ProcessedDataPacket output;
	output.timestamp = tick / 100.0;
	output.flight_state = flight_state;
	output.voltages[0] = voltages[0] / 4095.0 * (156.0 / 100.0) * 3.3;
	output.voltages[1] = voltages[1] / 4095.0 * (127.0 / 27.0) * 3.3;
	//TODO

	return output;
}

QString ProcessedDataPacket::toQString()
{
	QString str;
	QTextStream stream(&str);
	stream << timestamp << "," << flight_state << "," << voltages[0] << "," << voltages[1];
	//TODO
	return str;
}
