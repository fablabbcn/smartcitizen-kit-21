#pragma once

// Include the necessary libraries for the auxiliary sensor to be used
#include <Wire.h>

// INA219 libs
#include <Adafruit_INA219.h>

// AlphaDelta libs
#include <AlphaDelta.h>

// Urban board library
#include <SckUrban.h>

// Groove_OLED libs
/* #include <U8g2lib.h> */

// DS2482 library (I2C-1Wire bridge)
#include <DS2482.h>

#include <Sensors.h>

extern TwoWire auxWire;

bool I2Cdetect(byte address);

class AuxBoards
{

	public:

		// List for storing Auxiliary sensors I2C address (SENSOR_COUNT - (BASE AND URBAN SENSORS))
		// TODO: store this in epprom, load it on boot, make a function to change the addresses by console command
		byte devAddress[SENSOR_COUNT - 18] {
				0x02,		// SENSOR_PM_1
				0x02,		// SENSOR_PM_25
				0x02,		// SENSOR_PM_10
				0x55,		// SENSOR_ALPHADELTA_AE1,
				0x55,		// SENSOR_ALPHADELTA_WE1,
				0x56,		// SENSOR_ALPHADELTA_AE2,
				0x56,		// SENSOR_ALPHADELTA_WE2,
				0x54,		// SENSOR_ALPHADELTA_AE3,
				0x54,		// SENSOR_ALPHADELTA_WE3,
				0x44,		// SENSOR_ALPHADELTA_TEMPERATURE,
				0x44,		// SENSOR_ALPHADELTA_HUMIDITY,
				0x59,		// SENSOR_GROOVE_I2C_ADC,
				0x41,		// SENSOR_INA219_BUSVOLT,
				0x41,		// SENSOR_INA219_SHUNT,
				0x41,		// SENSOR_INA219_CURRENT,
				0x41,		// SENSOR_INA219_LOADVOLT,
				0x18,		// SENSOR_WATER_TEMP_DS18B20,
				0x3c,		// SENSOR_GROOVE_OLED,
				0x63,		// SENSOR_ATLAS_PH,
				0x64,		// SENSOR_ATLAS_EC,
				0x64,		// SENSOR_ATLAS_EC_SG,
				0x61,		// SENSOR_ATLAS_DO,
				0x61		// SENSOR_ATLAS_DO_SAT,
		};

		bool begin(SensorType wichSensor);
		float getReading(SensorType wichSensor);
		bool getBusyState(SensorType wichSensor);
		String control(SensorType wichSensor, String command);
		void print(SensorType wichSensor, String payload);
		void displayReading(String title, String reading, String unit, String time);

	private:
};

class GrooveI2C_ADC
{
	public:

		bool begin();
		float getReading();

		const byte deviceAddress 	= 0x59;
		const float V_REF 			= 3.30;
		const byte REG_ADDR_RESULT	= 0x00;
		const byte REG_ADDR_ALERT	= 0x01;
		const byte REG_ADDR_CONFIG	= 0x02;
		const byte REG_ADDR_LIMITL	= 0x03;
		const byte REG_ADDR_LIMITH	= 0x04;
		const byte REG_ADDR_HYST	= 0x05;
		const byte REG_ADDR_CONVL	= 0x06;
		const byte REG_ADDR_CONVH	= 0x07;

	private:
};

class INA219
{
	public:

		const byte deviceAddress = 0x41;

		enum typeOfReading {BUS_VOLT, SHUNT_VOLT, CURRENT, LOAD_VOLT};

		Adafruit_INA219 ada_ina219 = Adafruit_INA219(deviceAddress);
		bool begin();
		float getReading(typeOfReading wichReading=CURRENT);

	private:
};

static const unsigned char scLogo[] PROGMEM =
{
	0x00, 0x00, 0x00, 0x00, 0x18, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x78, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0xf0, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0xf0, 0x0f, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0xf0, 0x3f, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0xf0, 0xff, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0xe0, 0xff, 0x07, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0xe0, 0xff, 0x1f, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0xe0, 0xff, 0x7f, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0xc0, 0xff, 0xff, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0xc0, 0xff, 0xff, 0x01, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0xfc, 0xff, 0xff, 0x01, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x80, 0xff, 0xff, 0xff, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0xe0, 0xff, 0xff, 0x7f, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0xf0, 0xff, 0xff, 0x3f, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0xfc, 0xff, 0xff, 0x1f, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0xff, 0xff, 0xff, 0x1f, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x80, 0xff, 0xff, 0xff, 0x0f, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0xe0, 0xff, 0x3f, 0xff, 0x07, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0xf0, 0xff, 0x07, 0xff, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0xf8, 0xff, 0x00, 0xfe, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0xfc, 0x7f, 0x00, 0xfe, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0xfe, 0x1f, 0x00, 0xfe, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0xff, 0x0f, 0x00, 0xfc, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x80, 0xff, 0x03, 0x00, 0x7c, 0x00, 0x00, 0x00, 0x00, 0x03, 0x00,
	0x00, 0x80, 0xff, 0x01, 0x00, 0x3c, 0x00, 0x00, 0x00, 0x80, 0x07, 0x00,
	0x00, 0xc0, 0xff, 0x00, 0x00, 0x38, 0x00, 0x00, 0x00, 0xc0, 0x07, 0x00,
	0x00, 0xe0, 0x7f, 0x00, 0x00, 0x18, 0x00, 0x00, 0x00, 0xe0, 0x0f, 0x00,
	0x00, 0xf0, 0x3f, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xf0, 0x1f, 0x00,
	0x00, 0xf0, 0x1f, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xf8, 0x1f, 0x00,
	0x00, 0xf8, 0x0f, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xf0, 0x3f, 0x00,
	0x00, 0xfc, 0x07, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xe0, 0x3f, 0x00,
	0x00, 0xfc, 0x07, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xe0, 0x7f, 0x00,
	0x00, 0xfe, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xc0, 0x7f, 0x00,
	0x00, 0xfe, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xc0, 0xff, 0x00,
	0x00, 0xfe, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0xff, 0x00,
	0x00, 0xff, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0xff, 0x01,
	0x00, 0xff, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xff, 0x01,
	0x80, 0xff, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xff, 0x01,
	0x80, 0x7f, 0xc0, 0xc3, 0x00, 0x03, 0x07, 0x7e, 0xf8, 0x07, 0xfe, 0x03,
	0x80, 0x7f, 0xe0, 0xc7, 0x00, 0x03, 0x07, 0xfe, 0xf8, 0x07, 0xfe, 0x03,
	0xc0, 0x3f, 0x70, 0xce, 0x00, 0x03, 0x07, 0xee, 0xf9, 0x07, 0xfc, 0x03,
	0xc0, 0x3f, 0x30, 0xcc, 0x81, 0x83, 0x0f, 0xc6, 0xc1, 0x00, 0xfc, 0x03,
	0xc0, 0x3f, 0x30, 0xc0, 0x81, 0x83, 0x0f, 0x86, 0xc1, 0x00, 0xfc, 0x07,
	0xc0, 0x1f, 0x30, 0xc0, 0x81, 0x83, 0x0d, 0x86, 0xc1, 0x00, 0xf8, 0x07,
	0xc0, 0x1f, 0x70, 0xc0, 0xc3, 0x83, 0x0d, 0x86, 0xc1, 0x00, 0xf8, 0x07,
	0xc0, 0x1f, 0xe0, 0xc0, 0xc3, 0xc3, 0x1d, 0xc6, 0xc1, 0x00, 0xf8, 0x07,
	0xe0, 0x1f, 0xc0, 0xc1, 0xe7, 0xc3, 0x18, 0xee, 0xc1, 0x00, 0xf8, 0x07,
	0xe0, 0x1f, 0x80, 0xc3, 0x66, 0xc3, 0x18, 0xfe, 0xc0, 0x00, 0xf8, 0x0f,
	0xe0, 0x1f, 0x00, 0xc7, 0x66, 0xc3, 0x18, 0x7e, 0xc0, 0x00, 0xf8, 0x0f,
	0xe0, 0x0f, 0x00, 0xce, 0x7e, 0xe3, 0x38, 0x66, 0xc0, 0x00, 0xf8, 0x0f,
	0xe0, 0x0f, 0x00, 0xcc, 0x3c, 0xe3, 0x3f, 0xe6, 0xc0, 0x00, 0xf0, 0x0f,
	0xe0, 0x0f, 0x30, 0xcc, 0x3c, 0xe3, 0x3f, 0xc6, 0xc0, 0x00, 0xf0, 0x0f,
	0xe0, 0x0f, 0x30, 0xcc, 0x18, 0x63, 0x30, 0xc6, 0xc0, 0x00, 0xf0, 0x0f,
	0xe0, 0x0f, 0x70, 0xc7, 0x18, 0x63, 0x30, 0xc6, 0xc1, 0x00, 0xf8, 0x0f,
	0xe0, 0x1f, 0xe0, 0xc7, 0x18, 0x63, 0x30, 0x86, 0xc1, 0x00, 0xf8, 0x0f,
	0xe0, 0x1f, 0xc0, 0xc3, 0x00, 0x63, 0x30, 0x86, 0xc1, 0x00, 0xf8, 0x0f,
	0xe0, 0x1f, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xf8, 0x07,
	0xc0, 0x1f, 0x00, 0x70, 0xec, 0x37, 0x9f, 0x6f, 0x0c, 0x00, 0xf8, 0x07,
	0xc0, 0x1f, 0x00, 0xf8, 0xec, 0x37, 0x9f, 0x6f, 0x0c, 0x00, 0xf8, 0x07,
	0xc0, 0x1f, 0x00, 0xd8, 0x8c, 0x31, 0x98, 0xe1, 0x0c, 0x00, 0xf8, 0x07,
	0xc0, 0x3f, 0x00, 0xd8, 0x8c, 0x31, 0x9c, 0xe1, 0x0c, 0x00, 0xfc, 0x07,
	0xc0, 0x3f, 0x00, 0x18, 0x8c, 0x31, 0x8c, 0xe1, 0x0d, 0x00, 0xfc, 0x03,
	0xc0, 0x3f, 0x00, 0x18, 0x8c, 0x31, 0x8e, 0xe7, 0x0d, 0x00, 0xfc, 0x03,
	0x80, 0x7f, 0x00, 0x18, 0x8c, 0x31, 0x86, 0x67, 0x0f, 0x00, 0xfe, 0x03,
	0x80, 0x7f, 0x00, 0x18, 0x8c, 0x31, 0x86, 0x61, 0x0f, 0x00, 0xfe, 0x03,
	0x80, 0xff, 0x00, 0xd8, 0x8c, 0x31, 0x87, 0x61, 0x0e, 0x00, 0xff, 0x01,
	0x00, 0xff, 0x00, 0xd8, 0x8c, 0x31, 0x83, 0x61, 0x0e, 0x00, 0xff, 0x01,
	0x00, 0xff, 0x01, 0xf8, 0x8c, 0x31, 0x9f, 0x6f, 0x0c, 0x80, 0xff, 0x01,
	0x00, 0xfe, 0x01, 0x70, 0x8c, 0x31, 0x9f, 0x6f, 0x0c, 0x80, 0xff, 0x00,
	0x00, 0xfe, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xc0, 0xff, 0x00,
	0x00, 0xfe, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xc0, 0x7f, 0x00,
	0x00, 0xfc, 0x07, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xe0, 0x7f, 0x00,
	0x00, 0xfc, 0x0f, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xf0, 0x3f, 0x00,
	0x00, 0xf8, 0x0f, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xf0, 0x3f, 0x00,
	0x00, 0xf0, 0x1f, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xf8, 0x1f, 0x00,
	0x00, 0xf0, 0x3f, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xfc, 0x1f, 0x00,
	0x00, 0xe0, 0x7f, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xfe, 0x0f, 0x00,
	0x00, 0xc0, 0xff, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xff, 0x07, 0x00,
	0x00, 0x80, 0xff, 0x03, 0x00, 0x00, 0x00, 0x00, 0xc0, 0xff, 0x03, 0x00,
	0x00, 0x80, 0xff, 0x07, 0x00, 0x00, 0x00, 0x00, 0xe0, 0xff, 0x01, 0x00,
	0x00, 0x00, 0xff, 0x0f, 0x00, 0x00, 0x00, 0x00, 0xf0, 0xff, 0x00, 0x00,
	0x00, 0x00, 0xfe, 0x1f, 0x00, 0x00, 0x00, 0x00, 0xf8, 0xff, 0x00, 0x00,
	0x00, 0x00, 0xfc, 0x7f, 0x00, 0x00, 0x00, 0x00, 0xfe, 0x7f, 0x00, 0x00,
	0x00, 0x00, 0xf8, 0xff, 0x01, 0x00, 0x00, 0x80, 0xff, 0x3f, 0x00, 0x00,
	0x00, 0x00, 0xf0, 0xff, 0x0f, 0x00, 0x00, 0xf0, 0xff, 0x1f, 0x00, 0x00,
	0x00, 0x00, 0xe0, 0xff, 0x7f, 0x00, 0x00, 0xfe, 0xff, 0x07, 0x00, 0x00,
	0x00, 0x00, 0x80, 0xff, 0xff, 0x1f, 0xf8, 0xff, 0xff, 0x03, 0x00, 0x00,
	0x00, 0x00, 0x00, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0xfc, 0xff, 0xff, 0xff, 0xff, 0x7f, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0xf0, 0xff, 0xff, 0xff, 0xff, 0x1f, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0xc0, 0xff, 0xff, 0xff, 0xff, 0x07, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x80, 0xff, 0xff, 0xff, 0xff, 0x01, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0xfc, 0xff, 0xff, 0x7f, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0xc0, 0xff, 0xff, 0x07, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0xf0, 0x1f, 0x00, 0x00, 0x00, 0x00, 0x00
};

/* class Groove_OLED */
/* { */
/* 	public: */

/* 		const byte deviceAddress = 0x3c; */

/* 		U8G2_SSD1327_SEEED_96X96_F_HW_I2C U8g2_oled = U8G2_SSD1327_SEEED_96X96_F_HW_I2C(U8G2_R0, U8X8_PIN_NONE, SCL, SDA); */

/* 		bool begin(); */
/* 		void print(String payload); */
/* 		void displayReading(String title, String reading, String unit, String time); */

/* 	private: */
/* }; */

/*! @class DS2482_100
 *  @brief class for handling the DS18B20 temperature sensor connected to the I2C port
 *   through the DS2482-100 board. This was based on an example made by
 *   <a href="https://github.com/paeaetech/paeae.git">paeae</a>
 */
class WaterTemp_DS18B20
{

	public:

		byte deviceAddress = 0x18;

		DS2482 DS_bridge = DS2482(0);

		byte data[8];
		byte addr[8];

		uint8_t conf =0x05;

		/* Start the transmission of data for the DS18B20 trough the DS2482_100 bridge */
		bool begin();
		/* Read the temperature of the DS18B20 through the DS2482_100 bridge */
		/* @return Temperature */
		float getReading();
	private:
};

class Atlas
{
	public:

		byte deviceAddress;
		SensorType atlasType;
		bool PH = false;
		bool EC = false;
		bool DO = false;
		float newReading;
		float newReadingB;
		String atlasResponse;
		uint32_t lastCommandSent = 0;
		enum State {
			REST,
			TEMP_COMP_SENT,
			ASKED_READING,
		};
		State state = REST;

		// Constructor varies by sensor type
		Atlas(SensorType wichSensor) {
			atlasType = wichSensor;

			switch(atlasType) {
				case SENSOR_ATLAS_PH: {
							      deviceAddress = 0x63;
							      PH = true;
							      break;

						      } case SENSOR_ATLAS_EC:
				case SENSOR_ATLAS_EC_SG: {
								 deviceAddress = 0x64;
								 EC = true;
								 break;

							 } case SENSOR_ATLAS_DO:
				case SENSOR_ATLAS_DO_SAT: {
								  deviceAddress = 0x61;
								  DO = true;
								  break;

							  } default: break;
			}

		}

		bool begin();
		bool beginDone = false;
		float getReading();
		bool getBusyState();

		void goToSleep();
		bool sendCommand(char* command);
		bool tempCompensation();
		uint8_t getResponse();

		uint16_t longWait = 910; //ms
		uint16_t mediumWait = 610; //ms
		uint16_t shortWait = 310; //ms

	private:
};

enum PMslot {SLOT_A, SLOT_B, SLOT_AVG};
enum PMcommands
{
         PM_START,          // Start both PMS
         GET_PMA,        // Get values for PMS in slot A
         GET_PMB,        // Get values for PMS in slot A
         GET_PM_AVG,     // Get values for both PMS averaged
         PM_STOP            // Stop both PMS
 };

class PMsensor
{
	public:

		PMsensor(PMslot wichSlot) {
			slot = wichSlot;
		}

		const byte deviceAddress = 0x02;

		uint16_t readingPM1;
		uint16_t readingPM25;
		uint16_t readingPM10;

		bool begin();
		float getReading(uint8_t wichReading);
	private:
		bool alreadyStarted = false;
		PMslot slot;
		uint8_t values[6];		// 6 bytes 0:1->pm1, 2:3->pm25, 4:5->pm10
};

void writeI2C(byte deviceAddress, byte instruction, byte data);
byte readI2C(byte deviceAddress, byte instruction);
