#ifndef BBDATAPACKET_H
#define BBDATAPACKET_H

#include <QObject>
#include <stdint.h>
#include <QString>
#include <QByteArray>
#include <QMetaType>


#define BB_DATA_PACKET_SIZE 44

struct ProcessedDataPacket
{
	float timestamp; // sec
	uint8_t flight_state;

	float		voltages[8]; // Volts; 0 - main battery, 1 - pyro battery, rest - sense
	float		orient;		// deg
	float		speed;		// m/s
	float		height;		// m

	float		pres;		// Pa
	float		temp;		// degC

	float		accel_x;	// m/s^2
	float		accel_y;	// m/s^2
	float		accel_z;	// m/s^2

	float		gyro_x;		// dps
	float		gyro_y;		// dps
	float		gyro_z;		// dps

	float		mag_x;		// uT
	float		mag_y;		// uT
	float		mag_z;		// uT

	QString toQString();
};


class BBDataPacket : public QObject
{
	Q_OBJECT
public:
	explicit BBDataPacket(QObject *parent = 0);
	uint16_t	tick; //0
	uint8_t		flight_state; // 2

	uint16_t v_bat;
	uint16_t v_pbat;
	uint8_t		voltages[6]; // 3; 0 - main battery, 1 - pyro battery, rest - sense
	uint8_t		orient;		/* 11 angle from vertical */
	int16_t		speed;		/* 12 m/s * 16 */
	int16_t		height;		/* 14 m */

	int32_t		pres;		/*  16 Pa * 10 */
	int16_t		temp;		/* 20 °C * 100 */

	int16_t		accel_x;	/* 22 */
	int16_t		accel_y;	/* 24 */
	int16_t		accel_z;	/* 26 */

	int16_t		gyro_x;		/* 28 */
	int16_t		gyro_y;		/* 30 */
	int16_t		gyro_z;		/* 32 */

	int16_t		mag_x;		/* 34 */
	int16_t		mag_y;		/* 36 */
	int16_t		mag_z;		/* 38 */

	void deserialize(QByteArray raw);
	QString toQString() const;
	ProcessedDataPacket toProcessedDataPacket();
};

#endif // BBDATAPACKET_H
