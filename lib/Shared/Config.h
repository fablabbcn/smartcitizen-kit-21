#pragma once
#include "Sensors.h"

static const uint32_t default_reading_interval = 60;
static const uint32_t minimal_reading_interval = 5;
static const uint32_t max_reading_interval = 86400;		// One day
static const float speed_threshold = 1.4; 			// m/s -> faster than this we enter dynamic mode - 1.4 m/s ~= 5 km/h
static const uint32_t dynamicInterval = 5; 			// Seconds

static const uint32_t minimal_publish_interval = 5;
static const uint32_t default_publish_interval = 60 * 3;
static const uint32_t max_publish_interval = 3600;		// One hour

enum SCKmodes {
	MODE_NOT_CONFIGURED,
	MODE_NET,
	MODE_SD,
	MODE_SLEEP,

	MODE_COUNT
};

enum errorType { 
	ERROR_NONE, 
	ERROR_SD, 
	ERROR_SD_PUBLISH, 
	ERROR_TIME, 
	ERROR_NO_WIFI_CONFIG, 
	ERROR_AP, 
	ERROR_PASS, 
	ERROR_WIFI_UNKNOWN, 
	ERROR_MQTT, 
	ERROR_NO_TOKEN_CONFIG, 
	ERROR_BATT 
};

struct SensorConfig { bool enabled; uint8_t everyNint; bool oled_display=false; };
struct Credentials { bool set=false; char ssid[64]="null"; char pass[64]="null"; };
struct Token { bool set=false; char token[7]="null"; };
struct MAC { bool valid=false; char address[18]="not synced"; };
struct BattConf { int16_t chargeCurrent=768; uint32_t battCapacity=2000; };
struct Extra { bool ccsBaselineValid=false; uint16_t ccsBaseline; }; 			// Here we save variables that don't have an specific place
struct Debug { bool sdcard=false; bool esp=false; bool oled=false; bool flash=false; };

struct Configuration {
	bool valid = true;
	SCKmodes mode = MODE_NOT_CONFIGURED;				// This mode only changes on user configuration, it can only be MODE_SD or MODE_NET or MODE_NOT_CONFIGURED
	uint32_t publishInterval = default_publish_interval; 		// in seconds
	uint32_t readInterval = default_reading_interval; 		// in seconds
	MAC mac; 							// Stored here after first boot
	Credentials credentials;
	Token token;
	SensorConfig sensors[SENSOR_COUNT];
	Debug debug;
	BattConf battConf;
	Extra extra;
	uint16_t sleepTimer = 30; 					// Sleep after this amount of minutes, 480 minutes max (0 to disable sleep)
};
