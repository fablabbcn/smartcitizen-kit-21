#include "SckUrban.h"
#include "SckBase.h"

// Hardware Serial UART PM
Uart SerialPM (&sercom5, pinPM_SERIAL_RX, pinPM_SERIAL_TX, SERCOM_RX_PAD_1, UART_TX_PAD_0);
void SERCOM5_Handler() {
	SerialPM.IrqHandler();
}

bool SckUrban::start(SensorType wichSensor)
{
    switch(wichSensor) {
        case SENSOR_LIGHT:              return sck_bh1730fvc.start();
        case SENSOR_TEMPERATURE:
        case SENSOR_HUMIDITY:           return sck_sht31.start();
        case SENSOR_NOISE_DBA:
        case SENSOR_NOISE_DBC:
        case SENSOR_NOISE_DBZ:
        case SENSOR_NOISE_FFT:          return sck_noise.start();
        case SENSOR_ALTITUDE:
        case SENSOR_PRESSURE:
        case SENSOR_PRESSURE_TEMP:      return sck_mpl3115A2.start();
        case SENSOR_CCS811_VOCS:        return sck_ccs811.start();
        case SENSOR_CCS811_ECO2:        return sck_ccs811.start();
        case SENSOR_PM_1:
        case SENSOR_PM_25:
        case SENSOR_PM_10:
        case SENSOR_PN_03:
        case SENSOR_PN_05:
        case SENSOR_PN_1:
        case SENSOR_PN_25:
        case SENSOR_PN_5:
        case SENSOR_PN_10:              return sck_pm.start();
        case SENSOR_SPS30_PM_1:
        case SENSOR_SPS30_PM_25:
        case SENSOR_SPS30_PM_4:
        case SENSOR_SPS30_PM_10:
        case SENSOR_SPS30_PN_05:
        case SENSOR_SPS30_PN_1:
        case SENSOR_SPS30_PN_25:
        case SENSOR_SPS30_PN_4:
        case SENSOR_SPS30_PN_10:
        case SENSOR_SPS30_TPSIZE:        return sck_sps30.start(wichSensor);
        case SENSOR_SEN5X_PM_1:
        case SENSOR_SEN5X_PM_25:
        case SENSOR_SEN5X_PM_4:
        case SENSOR_SEN5X_PM_10:
        case SENSOR_SEN5X_PN_05:
        case SENSOR_SEN5X_PN_1:
        case SENSOR_SEN5X_PN_25:
        case SENSOR_SEN5X_PN_4:
        case SENSOR_SEN5X_PN_10:
        case SENSOR_SEN5X_TPSIZE:
        case SENSOR_SEN5X_HUMIDITY:
        case SENSOR_SEN5X_TEMPERATURE:
        case SENSOR_SEN5X_VOCS_IDX:
        case SENSOR_SEN5X_NOX_IDX:
        case SENSOR_SEN5X_HUMIDITY_RAW:
        case SENSOR_SEN5X_TEMPERATURE_RAW:
        case SENSOR_SEN5X_VOCS_RAW:
        case SENSOR_SEN5X_NOX_RAW:      return sck_sen5x.start(wichSensor);
        default: break;
    }

    return false;
}
bool SckUrban::stop(SensorType wichSensor)
{
    switch(wichSensor) {
        case SENSOR_LIGHT:              return sck_bh1730fvc.stop();
        case SENSOR_TEMPERATURE:
        case SENSOR_HUMIDITY:           return sck_sht31.stop();
        case SENSOR_NOISE_DBA:
        case SENSOR_NOISE_DBC:
        case SENSOR_NOISE_DBZ:
        case SENSOR_NOISE_FFT:          return sck_noise.stop();
        case SENSOR_ALTITUDE:
        case SENSOR_PRESSURE:
        case SENSOR_PRESSURE_TEMP:      return sck_mpl3115A2.stop();
        case SENSOR_CCS811_VOCS:
        case SENSOR_CCS811_ECO2:        return sck_ccs811.stop();
        case SENSOR_PM_1:
        case SENSOR_PM_25:
        case SENSOR_PM_10:
        case SENSOR_PN_03:
        case SENSOR_PN_05:
        case SENSOR_PN_1:
        case SENSOR_PN_25:
        case SENSOR_PN_5:
        case SENSOR_PN_10:              return sck_pm.stop();
        case SENSOR_SPS30_PM_1:
        case SENSOR_SPS30_PM_25:
        case SENSOR_SPS30_PM_4:
        case SENSOR_SPS30_PM_10:
        case SENSOR_SPS30_PN_05:
        case SENSOR_SPS30_PN_1:
        case SENSOR_SPS30_PN_25:
        case SENSOR_SPS30_PN_4:
        case SENSOR_SPS30_PN_10:
        case SENSOR_SPS30_TPSIZE:       return sck_sps30.stop(wichSensor);
        case SENSOR_SEN5X_PM_1:
        case SENSOR_SEN5X_PM_25:
        case SENSOR_SEN5X_PM_4:
        case SENSOR_SEN5X_PM_10:
        case SENSOR_SEN5X_PN_05:
        case SENSOR_SEN5X_PN_1:
        case SENSOR_SEN5X_PN_25:
        case SENSOR_SEN5X_PN_4:
        case SENSOR_SEN5X_PN_10:
        case SENSOR_SEN5X_TPSIZE:
        case SENSOR_SEN5X_HUMIDITY:
        case SENSOR_SEN5X_TEMPERATURE:
        case SENSOR_SEN5X_VOCS_IDX:
        case SENSOR_SEN5X_NOX_IDX:
        case SENSOR_SEN5X_HUMIDITY_RAW:
        case SENSOR_SEN5X_TEMPERATURE_RAW:
        case SENSOR_SEN5X_VOCS_RAW:
        case SENSOR_SEN5X_NOX_RAW:      return sck_sen5x.stop(wichSensor);
        default: break;
    }

    return false;
}

void SckUrban::getReading(SckBase *base, OneSensor *wichSensor)
{
	wichSensor->state = 0;
	switch(wichSensor->type) {
		case SENSOR_LIGHT:                  if (sck_bh1730fvc.get())                    { wichSensor->reading = String(sck_bh1730fvc.reading);                          return; } break;
		case SENSOR_TEMPERATURE:            if (sck_sht31.getReading())                 { wichSensor->reading = String(sck_sht31.temperature);                          return; } break;
		case SENSOR_HUMIDITY:               if (sck_sht31.getReading())                 { wichSensor->reading = String(sck_sht31.humidity);                             return; } break;
		case SENSOR_NOISE_DBA:              if (sck_noise.getReading(SENSOR_NOISE_DBA)) { wichSensor->reading = String(sck_noise.readingDB);                            return; } break;
		case SENSOR_NOISE_DBC:              if (sck_noise.getReading(SENSOR_NOISE_DBC)) { wichSensor->reading = String(sck_noise.readingDB);                            return; } break;
		case SENSOR_NOISE_DBZ:              if (sck_noise.getReading(SENSOR_NOISE_DBZ)) { wichSensor->reading = String(sck_noise.readingDB);                            return; } break;
		case SENSOR_NOISE_FFT:              if (sck_noise.getReading(SENSOR_NOISE_FFT)) {
								// TODO find a way to give access to readingsFFT instead of storing them on a String (too much RAM)
								// For now it just prints the values to console
								for (uint16_t i=1; i<sck_noise.FFT_NUM; i++) SerialUSB.println(sck_noise.readingFFT[i]);
								return;
							}
		case SENSOR_CCS811_VOCS:            if (sck_ccs811.getReading(base))            { wichSensor->reading = String(sck_ccs811.VOCgas);                              return; } break;
		case SENSOR_CCS811_ECO2:            if (sck_ccs811.getReading(base))            { wichSensor->reading = String(sck_ccs811.ECO2gas);                             return; } break;
		case SENSOR_ALTITUDE:               if (sck_mpl3115A2.getAltitude())            { wichSensor->reading = String(sck_mpl3115A2.altitude);                         return; } break;
		case SENSOR_PRESSURE:               if (sck_mpl3115A2.getPressure())            { wichSensor->reading = String(sck_mpl3115A2.pressure);                         return; } break;
		case SENSOR_PRESSURE_TEMP:          if (sck_mpl3115A2.getTemperature())         { wichSensor->reading = String(sck_mpl3115A2.temperature);                      return; } break;
		case SENSOR_PM_1:                   if (sck_pm.getReading(wichSensor, base))    { wichSensor->reading = String(sck_pm.pm1);                                     return; } break;
		case SENSOR_PM_25:                  if (sck_pm.getReading(wichSensor, base))    { wichSensor->reading = String(sck_pm.pm25);                                    return; } break;
		case SENSOR_PM_10:                  if (sck_pm.getReading(wichSensor, base))    { wichSensor->reading = String(sck_pm.pm10);                                    return; } break;
		case SENSOR_PN_03:                  if (sck_pm.getReading(wichSensor, base))    { wichSensor->reading = String(sck_pm.pn03);                                    return; } break;
		case SENSOR_PN_05:                  if (sck_pm.getReading(wichSensor, base))    { wichSensor->reading = String(sck_pm.pn05);                                    return; } break;
		case SENSOR_PN_1:                   if (sck_pm.getReading(wichSensor, base))    { wichSensor->reading = String(sck_pm.pn1);                                     return; } break;
		case SENSOR_PN_25:                  if (sck_pm.getReading(wichSensor, base))    { wichSensor->reading = String(sck_pm.pn25);                                    return; } break;
		case SENSOR_PN_5:                   if (sck_pm.getReading(wichSensor, base))    { wichSensor->reading = String(sck_pm.pn5);                                     return; } break;
		case SENSOR_PN_10:                  if (sck_pm.getReading(wichSensor, base))    { wichSensor->reading = String(sck_pm.pn10);                                    return; } break;
        case SENSOR_SPS30_PM_1:             if (sck_sps30.getReading(wichSensor))       { wichSensor->reading = String(sck_sps30.pm_readings.mc_1p0);                   return; } break;
        case SENSOR_SPS30_PM_25:            if (sck_sps30.getReading(wichSensor))       { wichSensor->reading = String(sck_sps30.pm_readings.mc_2p5);                   return; } break;
        case SENSOR_SPS30_PM_4:             if (sck_sps30.getReading(wichSensor))       { wichSensor->reading = String(sck_sps30.pm_readings.mc_4p0);                   return; } break;
        case SENSOR_SPS30_PM_10:            if (sck_sps30.getReading(wichSensor))       { wichSensor->reading = String(sck_sps30.pm_readings.mc_10p0);                  return; } break;
        case SENSOR_SPS30_PN_05:            if (sck_sps30.getReading(wichSensor))       { wichSensor->reading = String(sck_sps30.pm_readings.nc_0p5);                   return; } break;
        case SENSOR_SPS30_PN_1:             if (sck_sps30.getReading(wichSensor))       { wichSensor->reading = String(sck_sps30.pm_readings.nc_1p0);                   return; } break;
        case SENSOR_SPS30_PN_25:            if (sck_sps30.getReading(wichSensor))       { wichSensor->reading = String(sck_sps30.pm_readings.nc_2p5);                   return; } break;
        case SENSOR_SPS30_PN_4:             if (sck_sps30.getReading(wichSensor))       { wichSensor->reading = String(sck_sps30.pm_readings.nc_4p0);                   return; } break;
        case SENSOR_SPS30_PN_10:            if (sck_sps30.getReading(wichSensor))       { wichSensor->reading = String(sck_sps30.pm_readings.nc_10p0);                  return; } break;
        case SENSOR_SPS30_TPSIZE:           if (sck_sps30.getReading(wichSensor))       { wichSensor->reading = String(sck_sps30.pm_readings.typical_particle_size);    return; } break;
        case SENSOR_SEN5X_PM_1:             if (sck_sen5x.getReading(wichSensor))       { wichSensor->reading = String(sck_sen5x.pM1p0);                                return; } break;
        case SENSOR_SEN5X_PM_25:            if (sck_sen5x.getReading(wichSensor))       { wichSensor->reading = String(sck_sen5x.pM2p5);                                return; } break;
        case SENSOR_SEN5X_PM_4:             if (sck_sen5x.getReading(wichSensor))       { wichSensor->reading = String(sck_sen5x.pM4p0);                                return; } break;
        case SENSOR_SEN5X_PM_10:            if (sck_sen5x.getReading(wichSensor))       { wichSensor->reading = String(sck_sen5x.pM10p0);                               return; } break;
        case SENSOR_SEN5X_PN_05:            if (sck_sen5x.getReading(wichSensor))       { wichSensor->reading = String(sck_sen5x.pN0p5);                                return; } break;
        case SENSOR_SEN5X_PN_1:             if (sck_sen5x.getReading(wichSensor))       { wichSensor->reading = String(sck_sen5x.pN1p0);                                return; } break;
        case SENSOR_SEN5X_PN_25:            if (sck_sen5x.getReading(wichSensor))       { wichSensor->reading = String(sck_sen5x.pN2p5);                                return; } break;
        case SENSOR_SEN5X_PN_4:             if (sck_sen5x.getReading(wichSensor))       { wichSensor->reading = String(sck_sen5x.pN4p0);                                return; } break;
        case SENSOR_SEN5X_PN_10:            if (sck_sen5x.getReading(wichSensor))       { wichSensor->reading = String(sck_sen5x.pN10p0);                               return; } break;
        case SENSOR_SEN5X_TPSIZE:           if (sck_sen5x.getReading(wichSensor))       { wichSensor->reading = String(sck_sen5x.tSize);                                return; } break;
        case SENSOR_SEN5X_HUMIDITY:         if (sck_sen5x.getReading(wichSensor))       { wichSensor->reading = String(sck_sen5x.humidity);                             return; } break;
        case SENSOR_SEN5X_TEMPERATURE:      if (sck_sen5x.getReading(wichSensor))       { wichSensor->reading = String(sck_sen5x.temperature);                          return; } break;
        case SENSOR_SEN5X_VOCS_IDX:         if (sck_sen5x.getReading(wichSensor))       { wichSensor->reading = String(sck_sen5x.vocIndex);                             return; } break;
        case SENSOR_SEN5X_NOX_IDX:          if (sck_sen5x.getReading(wichSensor))       { wichSensor->reading = String(sck_sen5x.noxIndex);                             return; } break;
        case SENSOR_SEN5X_HUMIDITY_RAW:     if (sck_sen5x.getReading(wichSensor))       { wichSensor->reading = String(sck_sen5x.rawHumidity);                          return; } break;
        case SENSOR_SEN5X_TEMPERATURE_RAW:  if (sck_sen5x.getReading(wichSensor))       { wichSensor->reading = String(sck_sen5x.rawTemperature);                       return; } break;
        case SENSOR_SEN5X_VOCS_RAW:         if (sck_sen5x.getReading(wichSensor))       { wichSensor->reading = String(sck_sen5x.rawVoc);                               return; } break;
        case SENSOR_SEN5X_NOX_RAW:          if (sck_sen5x.getReading(wichSensor))       { wichSensor->reading = String(sck_sen5x.rawNox);                               return; } break;
		default: break;
	}
	wichSensor->state = -1;
}
bool SckUrban::control(SckBase *base, SensorType wichSensor, String command)
{

	switch (wichSensor) {
		case SENSOR_NOISE_DBA:
		case SENSOR_NOISE_DBC:
		case SENSOR_NOISE_DBZ:
		case SENSOR_NOISE_FFT:
		{
				if (command.startsWith("debug")) {
					sck_noise.debugFlag = !sck_noise.debugFlag;
					sprintf(base->outBuff, "Noise debug: %s", sck_noise.debugFlag  ? "true" : "false");
					base->sckOut();
					return true;
				}
		} case SENSOR_CCS811_VOCS:
		case SENSOR_CCS811_ECO2:
		{
				if (command.startsWith("compensate")) {

					sck_ccs811.compensate = !sck_ccs811.compensate;
					return (sck_ccs811.compensate ? "True" : "False");

				} else if (command.startsWith("mode")) {

					command.replace("mode", "");
					command.trim();

					if (command.length() == 0) {
						sprintf(base->outBuff, "Current drive mode: %u", sck_ccs811.driveMode);
						base->sckOut();
						return "\r\n";
					}

					uint8_t newDriveMode = command.toInt();
					if ((newDriveMode == 0 and !command.equals("0")) || newDriveMode > 4 || newDriveMode < 0) return F("Wrong drive mode value received, try again");

					//Mode 0 = Idle
					//Mode 1 = read every 1s
					//Mode 2 = every 10s
					//Mode 3 = every 60s
					//Mode 4 = RAW mode
					if (sck_ccs811.setDriveMode(newDriveMode) != CCS811Core::CCS811_Stat_SUCCESS) return F("Failed to set new drive mode");
					else return String F("Drivemode set to ") + String(sck_ccs811.driveMode);

				} else if (command.startsWith("help") || command.length() == 0) {

					sprintf(base->outBuff, "Available commands:\r\n* compensate (toggles temp/hum compensation)\r\n* mode [0-4] (0-idle, 1-1s, 2-10s, 3-60s, 4-raw)");
					base->sckOut();
					return "\r\n";
				}

		}
		case SENSOR_PM_1:
		case SENSOR_PM_25:
		case SENSOR_PM_10:
		{
				if (command.startsWith("debug")) {

					command.replace("debug", "");
					command.trim();
					if (command.startsWith("1")) sck_pm.debug = true;
					else if (command.startsWith("0")) sck_pm.debug = false;

					sprintf(base->outBuff, "%s", sck_pm.debug  ? "true" : "false");
					base->sckOut();
					return true;

				} else if (command.startsWith("powersave")) {

					bool oldValue = sck_pm.powerSave;
					command.replace("powersave", "");
					command.trim();
					if (command.startsWith("1")) sck_pm.powerSave = true;
					else if (command.startsWith("0")) sck_pm.powerSave = false;

					sprintf(base->outBuff, "%s", sck_pm.powerSave  ? "true" : "false");
					base->sckOut();
					
					if (oldValue != sck_pm.powerSave) {
						base->config.extra.pmPowerSave = sck_pm.powerSave;
						base->saveConfig();
					}
					return true;

				} else if (command.startsWith("warmup")) {
					
					uint32_t oldValue = sck_pm.warmUpPeriod;
					command.replace("warmup", "");
					command.trim();

					// If user provide a value set new period
					if (command.length() > 0) {
						int newPeriod = command.toInt();
						sck_pm.warmUpPeriod = newPeriod;
					} 

					sprintf(base->outBuff, "%u seconds", sck_pm.warmUpPeriod);
					base->sckOut();

					if (oldValue != sck_pm.warmUpPeriod) {
						base->config.extra.pmWarmUpPeriod = sck_pm.warmUpPeriod;
						base->saveConfig();
					}
					return true;

				} else if (command.startsWith("help") || command.length() == 0) {

					sprintf(base->outBuff, "Available commands:\r\n* powersave: [0-1] Sets powersave (turn off PMS after reading it)\r\n* warmup [seconds] Changes warm up period for sensor\r\n* debug [0-1] Sets debug messages");
					base->sckOut();
					return "\r\n";
				}
		}
        case SENSOR_SPS30_PM_1:
        case SENSOR_SPS30_PM_25:
        case SENSOR_SPS30_PM_4:
        case SENSOR_SPS30_PM_10:
        case SENSOR_SPS30_PN_05:
        case SENSOR_SPS30_PN_1:
        case SENSOR_SPS30_PN_25:
        case SENSOR_SPS30_PN_4:
        case SENSOR_SPS30_PN_10:
        case SENSOR_SPS30_TPSIZE:
            {
                if (command.startsWith("debug")) {

                    command.replace("debug", "");
                    command.trim();
                    if (command.startsWith("1")) sck_sps30.debug = true;
                    else if (command.startsWith("0")) sck_sps30.debug = false;

                    sprintf(base->outBuff, "Debug: %s", sck_sps30.debug  ? "true" : "false");
                    base->sckOut();
                    return true;

                } else if (command.startsWith("cleanint")) {

					command.replace("cleanint", "");
					command.trim();

					if (command.length() > 0) {
    					uint8_t newInterval = command.toInt();
                        sprintf(base->outBuff, "Setting clean interval to %u days...", newInterval);
                        base->sckOut();
                        if (!sck_sps30.setCleaningInterval(newInterval)) {
                            base->sckOut("Error setting new interval!!");
                        }
                    } 

                    uint8_t currentInterval = sck_sps30.getCleaningInterval();
                    sprintf(base->outBuff, "Current clean interval: %u days", currentInterval);
                    base->sckOut();
                    return "\r\n";

                } else if (command.startsWith("doclean")) {

                    base->sckOut("SPS30 cleaning started, it will take 10s...");
                    sck_sps30.startCleaning();
                    base->sckOut("Done!!!");
                    return "\r\n";

                }  else if (command.startsWith("help") || command.length() == 0) {
					sprintf(base->outBuff, "Available commands:\r\n* debug: [0-1] Sets debug messages\r\n* doclean: Starts a cleaning\r\n* cleanint [interval in days]");
					base->sckOut();
					return "\r\n";
                }
            }
        case SENSOR_SEN5X_PM_1:
        case SENSOR_SEN5X_PM_25:
        case SENSOR_SEN5X_PM_4:
        case SENSOR_SEN5X_PM_10:
        case SENSOR_SEN5X_PN_05:
        case SENSOR_SEN5X_PN_1:
        case SENSOR_SEN5X_PN_25:
        case SENSOR_SEN5X_PN_4:
        case SENSOR_SEN5X_PN_10:
        case SENSOR_SEN5X_TPSIZE:
        case SENSOR_SEN5X_HUMIDITY:
        case SENSOR_SEN5X_TEMPERATURE:
        case SENSOR_SEN5X_VOCS_IDX:
        case SENSOR_SEN5X_NOX_IDX:
        case SENSOR_SEN5X_HUMIDITY_RAW:
        case SENSOR_SEN5X_TEMPERATURE_RAW:
        case SENSOR_SEN5X_VOCS_RAW:
        case SENSOR_SEN5X_NOX_RAW:
            {
                if (command.startsWith("debug")) {

                    command.replace("debug", "");
                    command.trim();
                    if (command.startsWith("1")) sck_sen5x.debug = true;
                    else if (command.startsWith("0")) sck_sen5x.debug = false;

                    sprintf(base->outBuff, "Debug: %s", sck_sen5x.debug  ? "true" : "false");
                    base->sckOut();
                    return true;

                } else if (command.startsWith("cleanint")) {

					command.replace("cleanint", "");
					command.trim();

					if (command.length() > 0) {
    					uint8_t newInterval = command.toInt();
                        sprintf(base->outBuff, "Setting clean interval to %u days...", newInterval);
                        base->sckOut();
                        if (!sck_sen5x.setCleaningInterval(newInterval)) {
                            base->sckOut("Error setting new interval!!");
                        }
                    } 

                    uint8_t currentInterval = sck_sen5x.getCleaningInterval();
                    sprintf(base->outBuff, "Current clean interval: %u days", currentInterval);
                    base->sckOut();
                    return "\r\n";

                } else if (command.startsWith("doclean")) {

                    base->sckOut("SEN5X cleaning started, it will take 10s...");
                    sck_sen5x.startCleaning();
                    base->sckOut("Done!!!");
                    return "\r\n";

                } else if (command.startsWith("version")) {

                    if (sck_sen5x.getVer()) {
                        sprintf(base->outBuff, 
                                "SEN5X Firmware: %u.%u\r\nSEN5X Hardware: %u.%u\r\nSEN5X Protocol: %u.%u\r\nSEN5X Firmware debug: %u",
                                sck_sen5x.firmwareMajor, sck_sen5x.firmwareMinor, 
                                sck_sen5x.hardwareMajor, sck_sen5x.hardwareMinor,
                                sck_sen5x.protocolMajor, sck_sen5x.protocolMinor,
                                sck_sen5x.firmwareDebug);
                        base->sckOut();
					return "\r\n";
                    }

                }  else if (command.startsWith("help") || command.length() == 0) {
					sprintf(base->outBuff, "Available commands:\r\n* debug: [0-1] Sets debug messages\r\n* doclean: Starts a cleaning\r\n* cleanint [interval in days]\r\n* version");
					base->sckOut();
					return "\r\n";
                }

            }


		default: break;
	}

	base->sckOut("Sensor not recognized!!");
	return false;
}

// Light
bool Sck_BH1730FVC::start()
{
	if (!I2Cdetect(&Wire, address)) return false;
	return true;
}
bool Sck_BH1730FVC::stop()
{
	// 0x00 register - CONTROL
	uint8_t CONTROL = B000000;
	// ADC_INTR: 	5	0:Interrupt is inactive.
	// 			1:Interrupt is active.
	// ADC_VALID:	4	0:ADC data is not updated after last reading.
	// 			1:ADC data is updated after last reading.
	// ONE_TIME:	3	0:ADC measurement is continuous.
	// 			1:ADC measurement is one time.
	// 			ADC	transits to power down automatically.
	// DATA_SEL:	2	0:ADC measurement Type0 and Type1.
	// 			1:ADC measurement Type0 only.
	// ADC_EN:	1	0:ADC measurement stop.
	// 			1:ADC measurement start.
	// POWER:	0	0:ADC power down.
	// 			1:ADC power on.

	// Send Configuration
	// This will save around 150 uA
	Wire.beginTransmission(address);
	Wire.write(0x80);
	Wire.write(CONTROL);
	Wire.endTransmission();

	return true;
}
bool Sck_BH1730FVC::updateValues()
{
	// Datasheet http://rohmfs.rohm.com/en/products/databook/datasheet/ic/sensor/light/bh1730fvc-e.pdf

	// 0x00 register - CONTROL
	uint8_t CONTROL = B000011;
	// ADC_INTR: 	5	0:Interrupt is inactive.
	// 			1:Interrupt is active.
	// ADC_VALID:	4	0:ADC data is not updated after last reading.
	// 			1:ADC data is updated after last reading.
	// ONE_TIME:	3	0:ADC measurement is continuous.
	// 			1:ADC measurement is one time.
	// 			ADC	transits to power down automatically.
	// DATA_SEL:	2	0:ADC measurement Type0 and Type1.
	// 			1:ADC measurement Type0 only.
	// ADC_EN:	1	0:ADC measurement stop.
	// 			1:ADC measurement start.
	// POWER:	0	0:ADC power down.
	// 			1:ADC power on.

	// 0x01 register - TIMMING
	// uint8_t ITIME  = 0xDA; 	// Datasheet default value (218 DEC)

	// 00h: Start / Stop of measurement is set by special command. (ADC manual integration mode)
	// 01h to FFh: Integration time is determined by ITIME value (defaultt is oxDA)
	// Integration Time : ITIME_ms = Tint * 964 * (256 - ITIME)
	// Measurement time : Tmt= ITIME_ms + Tint * 714

	// 0x02 register - INTERRUPT
	uint8_t INTERRUPT = B00000000;
	// RES 		7 	Write 0
	// INT_STOP	6	0 : ADC measurement does not stop.
	// 				1 : ADC measurement stops and transits to power down mode when interrupt becomes active.
	// RES 		5 	Write 0
	// INT_EN 	4 	0 : Disable interrupt function.
	// 				1 : Enable interrupt function.
	// PERSIST 	3:0 Interrupt persistence function.
	//	0000 : Interrupt becomes active at each measurement end.
	//	0001 : Interrupt status is updated at each measurement end.
	//	0010 : Interrupt status is updated if two consecutive threshold judgments are the same.
	//	When  set  0011  or  more,  interrupt  status  is  updated  if same threshold judgments continue consecutively same times as the number set in PERSIST.

	// 0x03, 0x04 registers - TH_LOW Low interrupt threshold
	uint8_t TH_LOW0 = 0x00;		// Lower byte of low interrupt threshold
	uint8_t TH_LOW1 = 0x00;		// Upper byte of low interrupt threshold

	// 0x05, 0x06 registers - TH_UP High interrupt threshold
	uint8_t TH_UP0 = 0xFF;		// Lower byte of high interrupt threshold
	uint8_t TH_UP1 = 0xFF;		// Upper byte of high interrupt threshold

	// 0x07 - GAIN
	uint8_t GAIN = 0x00;
	// GAIN  2:0	ADC resolution setting
	//	  X00 : x1 gain mode
	//	  X01 : x2 gain mode
	//	  X10 : x64 gain mode
	//	  X11 : x128 gain mode

	uint8_t DATA[8] = {CONTROL, ITIME, INTERRUPT, TH_LOW0, TH_LOW1, TH_UP0, TH_UP1, GAIN};

	// Send Configuration
	Wire.beginTransmission(address);
	Wire.write(0x80);
	for (int i= 0; i<8; i++) Wire.write(DATA[i]);
	Wire.endTransmission();

	// Calculate timming values
	ITIME_ms = (Tint * 964 * (256 - ITIME)) / 1000;
	Tmt =  ITIME_ms + (Tint * 714);

	// Wait for ADC to finish
	uint32_t started = millis();
	uint8_t answer = 0;
	while ((answer & 0x10) == 0) {
		delay(10);
		Wire.beginTransmission(address);
		Wire.write(0x80);
		Wire.endTransmission();
		Wire.requestFrom(address, 1);
		answer = Wire.read();
		if (millis() - started > Tmt) {
			if (debug) SerialUSB.println("ERROR: Timeout waiting for reading");
			return false;
		}
	}

	// Ask for reading
	Wire.beginTransmission(address);
	Wire.write(0x94);
	Wire.endTransmission();
	Wire.requestFrom(address, 4);

	// Get result
	uint16_t IDATA0 = 0;
	uint16_t IDATA1 = 0;
	IDATA0 = Wire.read();
	IDATA0 = IDATA0 | (Wire.read()<<8);
	IDATA1 = Wire.read();
	IDATA1 = IDATA1 | (Wire.read()<<8);
	DATA0 = (float)IDATA0;
	DATA1 = (float)IDATA1;

	// Setup gain
	Gain = 1;
	if (GAIN == 0x01) Gain = 2;
	else if (GAIN == 0x02) Gain = 64;
	else if (GAIN == 0x03) Gain = 128;

	return true;
}
bool Sck_BH1730FVC::get()
{
	// Start in the default integration time
	ITIME = 218;

	if (!updateValues()) return false;

	// Adjust the Integration Time (ITIME)
	for (uint8_t i=0; i<6; i++) {

		if (DATA0 > goUp || DATA1 > goUp) {
			ITIME += (((ITIME_max - ITIME) / 2) + 1);
			if (ITIME > 250) ITIME = ITIME_max;

			if (debug) {
				SerialUSB.print(DATA0);
				SerialUSB.print(" -- ");
				SerialUSB.print(DATA1);
				SerialUSB.print(" >> ");
				SerialUSB.println(ITIME);
			}
		} else break;

		if (!updateValues()) return false;
	}

	// Lux calculation (Datasheet page 13)
	float Lx = 0;
	if (DATA0 > 0 && DATA1 > 0) {
		if (DATA1/DATA0 < 0.26) Lx = ((1.290 * DATA0 - 2.733 * DATA1) / Gain) * (102.6 / ITIME_ms);
		else if (DATA1/DATA0 < 0.55) Lx = ((0.795 * DATA0 - 0.859 * DATA1) / Gain) * (102.6 / ITIME_ms);
		else if (DATA1/DATA0 < 1.09) Lx = ((0.510 * DATA0 - 0.345 * DATA1) / Gain) * (102.6 / ITIME_ms);
		else if (DATA1/DATA0 < 2.13) Lx = ((0.276 * DATA0 - 0.130 * DATA1) / Gain) * (102.6 / ITIME_ms);
		else Lx = 0;
	}

	Lx = max(0, Lx);
	reading  = (int)Lx;

	if (debug) {
		SerialUSB.print("Integration Time ITIME_ms: ");
		SerialUSB.println(ITIME_ms);
		SerialUSB.print("Measurement Time Tmt: ");
		SerialUSB.println(Tmt);
		SerialUSB.print("Gain: ");
		SerialUSB.println(Gain);
		SerialUSB.print("Visible Light DATA0: ");
		SerialUSB.println(DATA0);
		SerialUSB.print("Infrared Light DATA1: ");
		SerialUSB.println(DATA1);
		SerialUSB.print("Calculated Lux: ");
		SerialUSB.println(Lx);
	}

	stop();

	return true;
}

// SHT31 (Temperature and Humidity)
// TODO Implement calibration routine
// TODO implement heater controller
Sck_SHT31::Sck_SHT31(TwoWire *localWire, uint8_t customAddress)
{
	_Wire = localWire;
	address = customAddress;
}
bool Sck_SHT31::start()
{
    _Wire->begin();
	if (!I2Cdetect(_Wire, address)) return false;
	
	delay(1); 		// In case the device was off
	sendComm(SOFT_RESET); 	// Send reset command
	delay(50); 		// Give time to finish reset
	update();

	return true;
}
bool Sck_SHT31::stop()
{

	// It will go to idle state by itself after 1ms
	return true;
}
bool Sck_SHT31::update()
{
	uint8_t readbuffer[6];
	if (!sendComm(SINGLE_SHOT_HIGH_REP)) return false;

	uint32_t started = millis();
	while (_Wire->requestFrom(address, 6) < 6) {
		if (millis() - started > timeout) {
			if (debug) SerialUSB.println("ERROR: Timed out waiting for SHT31 sensor!!!");
			return false;
		}
	}

	// Read response
	if (debug) SerialUSB.print("Response: ");
	for (uint8_t i=0; i<6; i++) {
		readbuffer[i] = _Wire->read();
		if (debug) SerialUSB.print(readbuffer[i]);
	}
	if (debug) SerialUSB.println();

	uint16_t ST, SRH;
	ST = readbuffer[0];
	ST <<= 8;
	ST |= readbuffer[1];

	// Check Temperature crc
	if (readbuffer[2] != crc8(readbuffer, 2)) {
		if (debug) SerialUSB.println("ERROR: Temperature reading CRC failed!!!");
		return false;
	}
	SRH = readbuffer[3];
	SRH <<= 8;
	SRH |= readbuffer[4];

	// check Humidity crc
	if (readbuffer[5] != crc8(readbuffer+3, 2)) {
		if (debug) SerialUSB.println("ERROR: Humidity reading CRC failed!!!");
		return false;
	}

	double temp = ST;
	temp *= 175;
	temp /= 0xffff;
	temp = -45 + temp;
	temperature = (float)temp;

	double shum = SRH;
	shum *= 100;
	shum /= 0xFFFF;
	humidity = (float)shum;

	return true;
}
bool Sck_SHT31::sendComm(uint16_t comm)
{
	_Wire->beginTransmission(address);
	_Wire->write(comm >> 8);
	_Wire->write(comm & 0xFF);
	if (_Wire->endTransmission() != 0) return false;

	return true;
}
uint8_t Sck_SHT31::crc8(const uint8_t *data, int len)
{

	/* CRC-8 formula from page 14 of SHT spec pdf */

	/* Test data 0xBE, 0xEF should yield 0x92 */

	/* Initialization data 0xFF */
	/* Polynomial 0x31 (x8 + x5 +x4 +1) */
	/* Final XOR 0x00 */

	const uint8_t POLYNOMIAL(0x31);
	uint8_t crc(0xFF);

	for ( int j = len; j; --j ) {
		crc ^= *data++;
		for ( int i = 8; i; --i ) {
			crc = ( crc & 0x80 )
				? (crc << 1) ^ POLYNOMIAL
				: (crc << 1);
		}
	}
	return crc;
}
bool Sck_SHT31::getReading()
{
	uint8_t tried = retrys;
	while (tried > 0) {
		if (update()) return true;
		tried--;
	}

	return false;
}

// Noise
bool Sck_Noise::start()
{
	if (alreadyStarted) return true;

	REG_GCLK_GENCTRL = GCLK_GENCTRL_ID(4);  // Select GCLK4
	while (GCLK->STATUS.bit.SYNCBUSY);

    if (!getReading(SENSOR_NOISE_DBA)) return false;

	alreadyStarted = true;
	return true;
}
bool Sck_Noise::stop()
{
	return true;
}
bool Sck_Noise::getReading(SensorType wichSensor)
{
	if (!I2S.begin(I2S_PHILIPS_MODE, sampleRate, 32)) return false;

	// Wait 263000 I2s cycles or 85 ms at 441000 hz
	uint32_t startPoint = millis();
	while (millis() - startPoint < 200) I2S.read();

	// Fill buffer with samples from I2S bus
	int32_t source[SAMPLE_NUM];
	uint16_t bufferIndex = 0;

	startPoint = millis();
	uint8_t timeOut = 30; 	// (ms) Timeout to avoid hangs if the I2S is not responfing
	while (bufferIndex < SAMPLE_NUM) {
		int32_t buff = I2S.read();
		if (buff) {
			source[bufferIndex] = buff>>7;
			bufferIndex ++;
		}

		if (millis() - startPoint > timeOut) {
			I2S.end();
			return false;
		}
	}
	I2S.end();

	// Get de average of recorded samples
	int32_t sum = 0;
	for (uint16_t i=0; i<SAMPLE_NUM; i++) sum += source[i];
	int32_t avg = sum / SAMPLE_NUM;

	// Center samples in zero
	for (uint16_t i=0; i<SAMPLE_NUM; i++) source[i] = source[i] - avg;

	// FFT
	FFT(source);

	switch(wichSensor) {

		case SENSOR_NOISE_DBA:
			// Equalization and A weighting
			for (uint16_t i=0; i<FFT_NUM; i++) readingFFT[i] *= (double)(equalWeight_A[i] / 65536.0);
			break;
		case SENSOR_NOISE_DBC:
			// Equlization and C weighting
			for (uint16_t i=0; i<FFT_NUM; i++) readingFFT[i] *= (double)(equalWeight_C[i] / 65536.0);
			break;
		case SENSOR_NOISE_DBZ:
			// Just Equalization
			for (uint16_t i=0; i<FFT_NUM; i++) readingFFT[i] *= (double)(equalTab[i] / 65536.0);
			break;
		case SENSOR_NOISE_FFT:
			// Convert FFT to dB
			fft2db();
			return true;
			break;
		default: break;
	}

	// RMS
	long long rmsSum = 0;
	double rmsOut = 0;
	for (uint16_t i=0; i<FFT_NUM; i++) rmsSum += pow(readingFFT[i], 2) / FFT_NUM;
	rmsOut = sqrt(rmsSum);
	rmsOut = rmsOut * 1 / RMS_HANN * sqrt(FFT_NUM) / sqrt(2);

	// Convert to dB
	readingDB = (double) (FULL_SCALE_DBSPL - (FULL_SCALE_DBFS - (20 * log10(rmsOut * sqrt(2)))));

	if (debugFlag) {
		SerialUSB.println("samples, FFT_weighted");
		for (uint16_t i=0; i<SAMPLE_NUM; i++) {
			SerialUSB.print(source[i]);
			SerialUSB.print(",");
			if (i < 256) SerialUSB.println(readingFFT[i]);
			else SerialUSB.println();
		}
	}

	return true;
}
bool Sck_Noise::FFT(int32_t *source)
{
	int16_t scaledSource[SAMPLE_NUM];
	double divider = dynamicScale(source, scaledSource);

	applyWindow(scaledSource, hannWindow, SAMPLE_NUM);

	static int16_t ALIGN4 scratchData[SAMPLE_NUM * 2];

	// Split the data
	for(int i=0; i<SAMPLE_NUM*2; i+=2){
		scratchData[i] = scaledSource[i/2]; // Real
		scratchData[i+1] = 0; // Imaginary
	}

	arm_radix2_butterfly(scratchData, (int16_t)SAMPLE_NUM, (int16_t *)twiddleCoefQ15_512);
	arm_bitreversal(scratchData, SAMPLE_NUM, (uint16_t *)armBitRevTable8);

	for (int i=0; i<SAMPLE_NUM/2; i++) {

		// Calculate result and normalize SpectrumBuffer, also revert dynamic scaling
		uint32_t myReal = pow(scratchData[i*2], 2);
		uint32_t myImg = pow(scratchData[(i*2)+1], 2);

		readingFFT[i] = sqrt(myReal + myImg) * divider * 4;
	}

	// Exception for the first bin
	readingFFT[0] = readingFFT[0] / 2;

	return 0;
}
double Sck_Noise::dynamicScale(int32_t *source, int16_t *scaledSource)
{
	int32_t maxLevel = 0;
	for (uint16_t i=0; i<SAMPLE_NUM; i++) if (abs(source[i]) > maxLevel) maxLevel = abs(source[i]);
	double divider = (maxLevel+1) / 32768.0; // 16 bits
	if (divider < 1) divider = 1;

	for (uint16_t i=0; i<SAMPLE_NUM; i++) scaledSource[i] = source[i] / divider;

	return divider;
}
void Sck_Noise::applyWindow(int16_t *src, const uint16_t *window, uint16_t len)
{
	/* This code is from https://github.com/adafruit/Adafruit_ZeroFFT thank you!
		-------
		This is an FFT library for ARM cortex M0+ CPUs
		Adafruit invests time and resources providing this open source code,
		please support Adafruit and open-source hardware by purchasing products from Adafruit!
		Written by Dean Miller for Adafruit Industries. MIT license, all text above must be included in any redistribution
		------
	*/

	while(len--){
		int32_t val = *src * *window++;
		*src = val >> 15;
		src++;
	}
}
void Sck_Noise::arm_radix2_butterfly(int16_t * pSrc, int16_t fftLen, int16_t * pCoef)
{
	/* This code is from https://github.com/adafruit/Adafruit_ZeroFFT thank you!
		-------
		This is an FFT library for ARM cortex M0+ CPUs
		Adafruit invests time and resources providing this open source code,
		please support Adafruit and open-source hardware by purchasing products from Adafruit!
		Written by Dean Miller for Adafruit Industries. MIT license, all text above must be included in any redistribution
		------
	*/

	int i, j, k, l;
	int n1, n2, ia;
	int16_t xt, yt, cosVal, sinVal;

	n2 = fftLen;

	n1 = n2;
	n2 = n2 >> 1;
	ia = 0;

	// loop for groups
	for (j=0; j<n2; j++) {
		cosVal = pCoef[ia * 2];
		sinVal = pCoef[(ia * 2) + 1];
		ia++;

		// loop for butterfly
		for (i=j; i<fftLen; i+=n1) {
			l = i + n2;
			xt = (pSrc[2 * i] >> 2u) - (pSrc[2 * l] >> 2u);
			pSrc[2 * i] = ((pSrc[2 * i] >> 2u) + (pSrc[2 * l] >> 2u)) >> 1u;

			yt = (pSrc[2 * i + 1] >> 2u) - (pSrc[2 * l + 1] >> 2u);
			pSrc[2 * i + 1] =
				((pSrc[2 * l + 1] >> 2u) + (pSrc[2 * i + 1] >> 2u)) >> 1u;

			pSrc[2u * l] = (((int16_t) (((int32_t) xt * cosVal) >> 16)) +
					((int16_t) (((int32_t) yt * sinVal) >> 16)));

			pSrc[2u * l + 1u] = (((int16_t) (((int32_t) yt * cosVal) >> 16)) -
					((int16_t) (((int32_t) xt * sinVal) >> 16)));

		}                           // butterfly loop end
	}                             // groups loop end

	uint16_t twidCoefModifier = 2;

	// loop for stage
	for (k = fftLen / 2; k > 2; k = k >> 1) {
		n1 = n2;
		n2 = n2 >> 1;
		ia = 0;

		// loop for groups
		for (j=0; j<n2; j++) {
			cosVal = pCoef[ia * 2];
			sinVal = pCoef[(ia * 2) + 1];

			ia = ia + twidCoefModifier;

			// loop for butterfly
			for (i=j; i<fftLen; i+=n1) {
				l = i + n2;
				xt = pSrc[2 * i] - pSrc[2 * l];
				pSrc[2 * i] = (pSrc[2 * i] + pSrc[2 * l]) >> 1u;

				yt = pSrc[2 * i + 1] - pSrc[2 * l + 1];
				pSrc[2 * i + 1] = (pSrc[2 * l + 1] + pSrc[2 * i + 1]) >> 1u;

				pSrc[2u * l] = (((int16_t) (((int32_t) xt * cosVal) >> 16)) +
						((int16_t) (((int32_t) yt * sinVal) >> 16)));

				pSrc[2u * l + 1u] = (((int16_t) (((int32_t) yt * cosVal) >> 16)) -
						((int16_t) (((int32_t) xt * sinVal) >> 16)));

			}                         // butterfly loop end
		}                           // groups loop end
		twidCoefModifier = twidCoefModifier << 1u;
	}                             // stages loop end

	n1 = n2;
	n2 = n2 >> 1;
	ia = 0;
	// loop for groups
	for (j=0; j<n2; j++) {
		cosVal = pCoef[ia * 2];
		sinVal = pCoef[(ia * 2) + 1];

		ia = ia + twidCoefModifier;

		// loop for butterfly
		for (i=j; i<fftLen; i+=n1) {
			l = i + n2;
			xt = pSrc[2 * i] - pSrc[2 * l];
			pSrc[2 * i] = (pSrc[2 * i] + pSrc[2 * l]);

			yt = pSrc[2 * i + 1] - pSrc[2 * l + 1];
			pSrc[2 * i + 1] = (pSrc[2 * l + 1] + pSrc[2 * i + 1]);

			pSrc[2u * l] = xt;

			pSrc[2u * l + 1u] = yt;

		}                           // butterfly loop end
	}                             // groups loop end
}
void Sck_Noise::arm_bitreversal(int16_t * pSrc16, uint32_t fftLen, uint16_t * pBitRevTab)
{
	/* This code is from https://github.com/adafruit/Adafruit_ZeroFFT thank you!
		-------
		This is an FFT library for ARM cortex M0+ CPUs
		Adafruit invests time and resources providing this open source code,
		please support Adafruit and open-source hardware by purchasing products from Adafruit!
		Written by Dean Miller for Adafruit Industries. MIT license, all text above must be included in any redistribution
		------
	*/

	int32_t *pSrc = (int32_t *) pSrc16;
	int32_t in;
	uint32_t fftLenBy2, fftLenBy2p1;
	uint32_t i, j;

	/*  Initializations */
	j = 0u;
	fftLenBy2 = fftLen / 2u;
	fftLenBy2p1 = (fftLen / 2u) + 1u;

	/* Bit Reversal Implementation */
	for (i = 0u; i <= (fftLenBy2 - 2u); i += 2u) {
		if(i < j) {
			in = pSrc[i];
			pSrc[i] = pSrc[j];
			pSrc[j] = in;

			in = pSrc[i + fftLenBy2p1];
			pSrc[i + fftLenBy2p1] = pSrc[j + fftLenBy2p1];
			pSrc[j + fftLenBy2p1] = in;
		}

		in = pSrc[i + 1u];
		pSrc[i + 1u] = pSrc[j + fftLenBy2];
		pSrc[j + fftLenBy2] = in;

		/*  Reading the index for the bit reversal */
		j = *pBitRevTab;

		/*  Updating the bit reversal index depending on the fft length  */
		pBitRevTab++;
	}
}
void Sck_Noise::fft2db()
{
	for (uint16_t i=0; i<FFT_NUM; i++) {
		if (readingFFT[i] > 0) readingFFT[i] = FULL_SCALE_DBSPL - (FULL_SCALE_DBFS - (20 * log10(readingFFT[i] * sqrt(2))));
		if (readingFFT[i] < 0) readingFFT[i] = 0;
	}
}

// Barometric pressure and Altitude
bool Sck_MPL3115A2::start()
{
	if (!I2Cdetect(&Wire, address)) return false;
	if (Adafruit_mpl3115A2.begin()) return true;
	return false;
}
bool Sck_MPL3115A2::stop()
{

	return true;
}
bool Sck_MPL3115A2::getAltitude()
{

	Adafruit_mpl3115A2.begin();

	// TODO callibration with control interface
	// Maybe we could implement get online data to calibrate this
	// mpl3115A2.setSeaPressure(102250.0);

	// TODO timeout to prevent hangs on external lib
	altitude = Adafruit_mpl3115A2.getAltitude();

	return true;
}
bool Sck_MPL3115A2::getPressure()
{

	Adafruit_mpl3115A2.begin();

	// TODO timeout to prevent hangs on external lib
	pressure = Adafruit_mpl3115A2.getPressure() / 1000;

	return true;
}
bool Sck_MPL3115A2::getTemperature()
{

	Adafruit_mpl3115A2.begin();

	// TODO timeout to prevent hangs on external lib
	altitude = Adafruit_mpl3115A2.getAltitude();
	temperature =  Adafruit_mpl3115A2.getTemperature();	// Only works after a getAltitude! don't call this allone

	return true;
}

// PM sensor
bool Sck_PM::start()
{
	if (started) return true;
    else if (alreadyFailed) return false;

	pinMode(pinPM_ENABLE, OUTPUT);
	digitalWrite(pinPM_ENABLE, HIGH);
	SerialPM.begin(9600);
	delay(250);
	SerialPM.setTimeout(5000);

	if (fillBuffer()) {
		if (!sendCmd(PM_CMD_CHANGE_MODE, PM_MODE_PASSIVE, true)) {
			if (debug) Serial.println("PM: Failed setting passive mode");
			stop();
            alreadyFailed = true;
			return false;
		}

		started = true;
		wakeUpTime = rtc->getEpoch();
		if (debug) Serial.println("PM: Started OK");
		return true;
	}

	if (debug) Serial.println("PM: serial port didn't started correctly");
	stop();

    alreadyFailed = true;
	return false;
}
bool Sck_PM::stop()
{
	if (debug) Serial.println("PM: Stoping sensor");
	digitalWrite(pinPM_ENABLE, LOW);
	SerialPM.end();
	started = false;
	wakeUpTime = 0;
	return true;
}
bool Sck_PM::getReading(OneSensor *wichSensor, SckBase *base)
{
	uint32_t now = rtc->getEpoch();

	// If last reading is recent doesn't make sense to get a new one
	if (now - lastReading < warmUpPeriod && !monitor) {
		if (debug) Serial.println("PM: Less than warmUp period since last update, data is still valid...");
		return true;
	}

	// Check if sensor is on
	if (!started) start();

	// Check if sensor is sleeping
	if (wakeUpTime == 0) wake();
	
	// Are we still warming up?
	uint32_t warmUpPassed = now - wakeUpTime;
	if (warmUpPassed < warmUpPeriod) {
		wichSensor->state = warmUpPeriod - warmUpPassed; 	// Report how many seconds are missing to cover the warm up period
		if (debug) Serial.println("PM: Still on warm up period");

		// Old sensors seem to wakeUp on active mode so we need to set them to passive each time.
		if (SerialPM.available()) {
			if (debug) Serial.println("PM: This seems to be an old sensor... changing to passive mode");
			oldSensor = true;
			while (SerialPM.available()) SerialPM.read();
			if (!sendCmd(PM_CMD_CHANGE_MODE, PM_MODE_PASSIVE, true)) {
				if (debug) Serial.println("PM: Failed setting passive mode");
				stop();
				return false;
			}
		}
		return true;
	}

	// Empty SerialPM internal buffer
	while (SerialPM.available()) SerialPM.read();
	
	if (!sendCmd(PM_CMD_GET_PASSIVE_READING, 0x00, false)) return false;

	if (!fillBuffer()) return false;

	if (!processBuffer()) return false;

	// Only go to sleep if these conditions are met
	if ( 	powerSave &&  									// PowerSave is enabled
		((wichSensor->everyNint * base->config.readInterval) > (warmUpPeriod * 2)) && 	// Reading interval is twice the warmUpPeriod
		!base->st.dynamic && 								// We are not in dynamic mode
		!monitor) { 									// We are not in monitor mode

		if (debug) Serial.println("PM: going to sleep");
		if (oldSensor) delay(50); 	// Old sensors don't work without a small delay between commands
		if (!sleep()) return false;
	}

	monitor = false;

	return true;
}
bool Sck_PM::fillBuffer()
{
	// Wait for start char 1 (0x42)
	if (!SerialPM.find(PM_START_BYTE_1)) {
		if (debug) Serial.println("PM: Timeout waiting for data start");
		return false;
	}

	size_t readedBytes = SerialPM.readBytes(buffer, buffLong);

	// Did we get all needed bytes?
	if (readedBytes < buffLong - 1) {
		if (debug) Serial.println("PM: Error: received less data than expected");
		return false;
	}

	if (debug) Serial.println("PM: Buffer filled OK");
	return true;
}
bool Sck_PM::processBuffer()
{
	if (buffer[0] != PM_START_BYTE_2) {
		if (debug) Serial.println("PM: Error on received data");
		return false;
	}

	// Checksum
	uint16_t checkSum = (buffer[buffLong - 2]<<8) + buffer[buffLong - 1];
	uint16_t sum = 0x42; // Start_byte_1 is not included in buffer, but it needs to be on the sum
	for(int i=0; i<(buffLong - 2); i++) sum += buffer[i];
	if(sum != checkSum) {
		if (debug) Serial.println("PM: Checksum error");
		return false;
	}

	// Get the values
	pm1 = (buffer[3]<<8) + buffer[4];
	pm25 = (buffer[5]<<8) + buffer[6];
	pm10 = (buffer[7]<<8) + buffer[8];
	pn03 = (buffer[15]<<8) + buffer[16];
	pn05 = (buffer[17]<<8) + buffer[18];
	pn1 = (buffer[19]<<8) + buffer[20];
	pn25 = (buffer[21]<<8) + buffer[22];
	pn5 = (buffer[23]<<8) + buffer[24];
	pn10 = (buffer[25]<<8) + buffer[26];

	// This values are just for debug
	version = buffer[27];
	errorCode = buffer[28];

	if (debug) {
		Serial.print("PM: version: ");
		Serial.println(version);
		Serial.print("PM: Error code: ");
		Serial.println(errorCode);
		Serial.println("PM: Reading data received OK");
	}

	lastReading = rtc->getEpoch();
	return true;
}
bool Sck_PM::sendCmd(byte cmd, byte data, bool checkResponse)
{
	// Based on datasheet: Appendix B：Transport Protocol Passive Mode

	if (debug) {
		Serial.print("PM: Sending command: 0x");
		Serial.print(cmd, HEX);
		Serial.print(" with data: 0x");
		Serial.println(data, HEX);
	}

	uint8_t msgLong = 7;
	unsigned char buff[msgLong];

	buff[0] = PM_START_BYTE_1;
	buff[1] = PM_START_BYTE_2;
	buff[2] = cmd;  // Command
	buff[3] = 0x00; // Data 1 (DATAH)
	buff[4] = data; // Data 2 (DATAL)

	// Checksum
	uint16_t sum = 0;
	for(uint8_t i=0; i<(msgLong - 2); i++) sum += buff[i];
	buff[5] = ((sum >> 8) & 0xFF); 	// Verify byte 1 (LRCH)
	buff[6] = (sum & 0xFF) ; 	// Verify byte 2 (LRCL)

	// Clear buffer
	if (retries > 0) {
		while (SerialPM.available()) SerialPM.read();
	}

	// Send message
	SerialPM.write(buff, msgLong);

	// When asking for readings we don't check response
	if (!checkResponse) return true;

	// Wait for start char 1 (0x42)
	if (!SerialPM.find(PM_START_BYTE_1)) {
		if (debug) Serial.println("PM: Timeout waiting for response");
		if (retries < MAX_RETRIES) {
			if (debug) Serial.println("PM: Retrying command");
			retries++;
			return sendCmd(cmd, data, checkResponse);
		} else {
			retries = 0;
			return false;
		}
	}

	// Get response
	uint8_t resLong = 7;
	unsigned char res[resLong];
	uint8_t received = SerialPM.readBytes(res, resLong);

	// Checksum
	sum = 0x42;
	uint16_t checkSum = (res[resLong - 2]<<8) + (res[resLong - 1]);
	for(int i=0; i<(resLong - 2); i++) sum += res[i];
	if(sum != checkSum) {
		if (debug) Serial.println("PM: Checksum error on command response");
		if (retries < MAX_RETRIES) {
			if (debug) Serial.println("PM: Retrying command");
			retries++;
			return sendCmd(cmd, data, checkResponse);
		} else {
			retries = 0;
			return false;
		}
	}

	// Check response
	if ( 	(res[0] != 0x4d) ||
		(res[1] != 0x00) ||
		(res[2] != 0x04) ||
		(res[3] != cmd)  ||
		(res[4] != data)) {
	
		if (debug) Serial.println("PM: Error on command response");
		if (retries < MAX_RETRIES) {
			if (debug) Serial.println("PM: Retrying command");
			retries++;
			return sendCmd(cmd, data, checkResponse);
		} else {
			retries = 0;
			return false;
		}
	}

	if (debug) {
		Serial.print("PM: Success on command 0x");
		Serial.print(res[3], HEX);
		Serial.print(" with data: 0x");
		Serial.println(res[4], HEX);
	}

	return true;
}
bool Sck_PM::sleep()
{
	if (debug) Serial.println("PM: Sending sensor to sleep");

	if (wakeUpTime == 0) {
		if (debug) Serial.println("PM: Sensor is already sleeping");
		return true;
	}

	if (!sendCmd(PM_CMD_SLEEP_ACTION, PM_SLEEP)) {
		if (debug) Serial.println("PM: Error on going to sleep");
		return false;
	}

	wakeUpTime = 0;
	return true;
}
bool Sck_PM::wake()
{
	if (debug) Serial.println("PM: Waking up sensor");

	if (wakeUpTime > 0) {
		if (debug) Serial.println("PM: Sensor is already waked up");
		return true;
	}

	if (!sendCmd(PM_CMD_SLEEP_ACTION, PM_WAKEUP, false)) {
		if (debug) Serial.println("PM: Error on waking up");
		return false;
	}

	wakeUpTime = rtc->getEpoch();
	return true;
}

// VOC and ECO2
bool Sck_CCS811::start()
{
	if (alreadyStarted) return true;

	if (!I2Cdetect(&Wire, address)) return false;

	if (!ccs.begin()) return false;

	if (ccs.setDriveMode(driveMode) != CCS811Core::CCS811_Stat_SUCCESS) return false;

	startTime = rtc->getEpoch();
	alreadyStarted = true;
	return true;
}
bool Sck_CCS811::stop()
{
	// If the sensor is not there we don't need to stop it
	if (!I2Cdetect(&Wire, address)) return true;

	if (ccs.setDriveMode(0) != CCS811Core::CCS811_Stat_SUCCESS) return false;
	alreadyStarted = false;
	startTime = 0;
	return true;
}
bool Sck_CCS811::getReading(SckBase *base)
{
	if (!alreadyStarted) start();
	uint32_t rtcNow = rtc->getEpoch();
	if (((startTime == 0) || ((rtcNow - startTime) < warmingTime)) && !base->inTest) {
		if (debug) {
			SerialUSB.println("CCS811: in warming period!!");
			SerialUSB.print("CCS811: Readings will be ready in (sec): ");
			SerialUSB.println(warmingTime - (rtcNow - startTime));
		}
		return false;
	}
	if (millis() - lastReadingMill < 5000) {
		if (debug) SerialUSB.println("CCS811: (not enough time passed)");
		return true; // This prevents getting different updates for ECO2 and VOCS
	}

	if (!ccs.dataAvailable()) {
		uint32_t Uinterval = 60000; 	// Interval between sensor update (ms)
		switch (driveMode) {
			case 1: Uinterval = 1000; break;
			case 2: Uinterval = 10000; break;
			case 3: Uinterval = 60000; break;
		}

		if (debug) {
			SerialUSB.print("CCS811: Drivemode interval (ms): ");
			SerialUSB.println(Uinterval);
		}

		if (millis() - lastReadingMill < Uinterval) {
			if (debug) SerialUSB.println("CCS811: using old readings (not enough time passed)");
			return true;  // We will use last reading because  sensor is not programmed to give us readings so often
		}
		if (debug) SerialUSB.println("CCS811: ERROR obtaining reading!!");
		return false;
	}

	lastReadingMill = millis();

	ccs.readAlgorithmResults();

	VOCgas = ccs.getTVOC();
	ECO2gas = ccs.getCO2();

	if (compensate) {
		if (base->sensors[SENSOR_TEMPERATURE].enabled && base->sensors[SENSOR_HUMIDITY].enabled) {
			base->getReading(&base->sensors[SENSOR_HUMIDITY]);
			base->getReading(&base->sensors[SENSOR_TEMPERATURE]);
			if (base->sensors[SENSOR_HUMIDITY].state == 0 && base->sensors[SENSOR_TEMPERATURE].state == 0) {
				if (debug) SerialUSB.println("CCS811: Compensating readings with temp/hum");
				ccs.setEnvironmentalData(base->sensors[SENSOR_HUMIDITY].reading.toFloat(), base->sensors[SENSOR_TEMPERATURE].reading.toFloat());
			} else {
				if (debug) SerialUSB.println("CCS811: Compensation failed Error obtaining temp/hum readings!!");
			}
		} else {
			if (debug) SerialUSB.println("CCS811: temp/hum compensation failed, some sensors are disabled");
		}
	} else {
		if (debug) SerialUSB.println("CCS811: temp/hum compensation is disabled!");
	}
	return true;
}
uint16_t Sck_CCS811::getBaseline()
{
	if (!alreadyStarted) {
		if (!start()) return false;
	}
	return ccs.getBaseline();
}
bool Sck_CCS811::setBaseline(uint16_t wichBaseline)
{
	if (!alreadyStarted) {
		if (!start()) return false;
	}

	if (ccs.setBaseline(wichBaseline) != ccs.CCS811_Stat_SUCCESS) return false;

	return true;
}
bool Sck_CCS811::setDriveMode(uint8_t wichDrivemode)
{
	driveMode = wichDrivemode;
	if (ccs.setDriveMode(driveMode) != CCS811Core::CCS811_Stat_SUCCESS) return false;
	return true;
}

// Sensirion SPS30 PM sensor option
bool Sck_SPS30::start(SensorType wichSensor)
{
    // If detection already failed dont try again until next reset
    if (state == SPS30_NOT_DETECTED) return false;

	if (state != SPS30_OFF) {
		// Mark this specific metric as enabled
		for (uint8_t i=0; i<totalMetrics; i++) if (enabled[i][0] == wichSensor) enabled[i][1] = 1;
		return true;
	}

    // The SCK needs battery to survive the sensor startup current draw, with only usb power it normally does not work
    // If battery is not present it enters a reset loop
	pinMode(pinPM_ENABLE, OUTPUT);
	digitalWrite(pinPM_ENABLE, HIGH);
    delay(25);

    state = SPS30_NOT_DETECTED;

	if (!I2Cdetect(&Wire, address)) {
        if (debug) Serial.println("SPS30 ERROR no i2c address found");
        return false;
    }

    sensirion_i2c_init();

    int result = sps30_probe();
    if (result != 0) {
        Serial.print("Error probing for SPS30: ");
        Serial.println(result);
        return false;
    }

    // Detection succeeded
    if (debug) Serial.println("SPS30 Started OK");
	state = SPS30_IDLE;

    // Call start again to just enable the corresponding metric
	return start(wichSensor);
}
bool Sck_SPS30::stop(SensorType wichSensor)
{
    bool changed = false;

	// Mark this specific metric as disabled
	for (uint8_t i=0; i<totalMetrics; i++) {
        if (enabled[i][0] == wichSensor) {
            enabled[i][1] = 0;
            changed = true;
        }
    }

    // Check if any metric is still enabled
	for (uint8_t i=0; i<totalMetrics; i++) {
        if (enabled[i][1]) return changed;
    }

    // If no metric is enabled turn off power
	if (debug) Serial.println("SPS30 Stoping sensor");
	digitalWrite(pinPM_ENABLE, LOW);

    state = SPS30_OFF;

    return true;
}
bool Sck_SPS30::getReading(OneSensor* wichSensor)
{
	uint32_t now = rtc->getEpoch();

    switch (state) {
        case SPS30_SLEEP: {
            // If last reading is recent doesn't make sense to get a new one
            if (now - lastReading < warmUpPeriod[0] && !monitor) {
                if (debug) Serial.println("SPS30: Less than warmUp period since last update, data is still valid...");
                return true;
            }
            wake();
        }
        case SPS30_IDLE: {
            int16_t result = sps30_start_measurement();
            if (result < 0) {
                if (debug) {
                    Serial.print("Error starting measurement on SPS30: ");
                    Serial.println(result);
                }
                return false; 
            }

            if (debug) Serial.println("SPS30: Started measurement");
            measureStarted = now;
            state = SPS30_WARM_UP_1;
        }
        case SPS30_WARM_UP_1: {

            // On monitor mode we don't wait for warmUP'
            if (monitor) {
                if (!update(wichSensor->type)) return false;
                else {
                    lastReading = now;
                    wichSensor->state = 0;
                    return true;
                }
            }

            uint32_t passed = now - measureStarted;

            // If warmUp period has finished get a reading
            if (passed >= warmUpPeriod[0]) {

                if (!update(wichSensor->type)) return false;
 
                // If the reading is low (the tyhreshold is in #/cm3) and second warmUp hasn't passed we keep waiting
                if ((pm_readings.nc_4p0 / 100) < concentrationThreshold && passed < warmUpPeriod[1]) {
                    if (debug) Serial.println("SPS30: Concentration is low, we will wait for the second warm Up");
                    state = SPS30_WARM_UP_2;
                    wichSensor->state = warmUpPeriod[1] - passed; 	// Report how many seconds are missing to cover the first warm up period
                    return true;
                }

                // return the reading
                sleep();
                lastReading = now;
                wichSensor->state = 0;
                return true;
            }

            wichSensor->state = warmUpPeriod[0] - passed;
            if (debug) Serial.println("SPS30: Still on first warm up period");
            return true;
        }
        case SPS30_WARM_UP_2: {

            uint32_t passed = now - measureStarted;
 
            if (passed < warmUpPeriod[1]) {
                wichSensor->state = warmUpPeriod[1] - passed; 	// Report how many seconds are missing to cover the second warm up period
                if (debug) Serial.println("SPS30: Still on second warm up period");
                return true;
            }

            if (!update(wichSensor->type)) return false;

            if (!monitor) sleep();
            lastReading = now;
            wichSensor->state = 0;
            return true;
        }
    }

    return false;
}
uint8_t Sck_SPS30::getCleaningInterval()
{
    uint8_t interval_days;
    int16_t response = sps30_get_fan_auto_cleaning_interval_days(&interval_days);
    if (response < 0) {
        if (debug) Serial.println("SPS30: error setting cleaning interval");
        return response;
    }
    return interval_days;
}
bool Sck_SPS30::setCleaningInterval(uint8_t interval_days)
{
    //  max: 30 days, 0 to disable cleaning
    if (interval_days < 0 || interval_days > 30) return false;

    int16_t response = sps30_set_fan_auto_cleaning_interval_days(interval_days);
    if (response < 0) {
        if (debug) Serial.println("SPS30: error setting cleaning interval");
        return false;
    }

    if (debug) {
        Serial.print("SPS30: new cleaning interval: ");
        Serial.println(interval_days);
    }

    // A note from the library:
    // * (*) Note that due to a firmware bug, the reported interval is only updated on
    // * sensor restart/reset. If the interval was thus updated after the last reset,
    // * the old value is still reported. Power-cycle the sensor or call sps30_reset()
    // * first if you need the latest value.

    response = sps30_reset();
    delay(SPS30_RESET_DELAY_USEC/1000); // Wait for 100000 us
    if (response < 0) {
        if (debug) Serial.println("SPS30: error while resseting sensor, new cleaning interval will not be updated until a good reset");
        return false;
    }

    return true;
}
bool Sck_SPS30::startCleaning()
{
    wake();

    state = SPS30_CLEANING;

    // * Note that this command can only be run when the sensor is in measurement
    // * mode, i.e. after sps30_start_measurement() without subsequent
    // * sps30_stop_measurement().
    int16_t result = sps30_start_measurement();
    if (result < 0) {
        if (debug) Serial.print("SPS30: Error before starting cleaning");
        return false; 
    }

    int16_t response = sps30_start_manual_fan_cleaning();
    if (response < 0) {
        if (debug) Serial.println("SPS30: error on fan cleaning");
        return false;
    }

    // Block while the cleaning is happening (msg to the user is sent by the control funcion)
    delay(10500);
    sleep();

    return true;
}
bool Sck_SPS30::update(SensorType wichSensor)
{
    // Try to get new data
    uint16_t data_ready;
    int response = sps30_read_data_ready(&data_ready);
    if (response < 0) {
        if (debug) Serial.println("SPS30: error reading SPS30 data ready flag");
        return false; // TODO this shouldn't fail this soon, some retrys and diagnostics should be done
    } 

    // TODO what happens if I haven't read data since 5 seconds, do I get the most recent?? CHECK THE DATASHEET
    if (!data_ready) {
        if (debug) Serial.println("SPS30: Data is not ready");
        return false;
    }

    // Ask for the new data
    response = sps30_read_measurement(&pm_readings);

    // Convert PN readings from #/cm3 to #/0.1l
    pm_readings.nc_0p5  *= 100;
    pm_readings.nc_1p0  *= 100;
    pm_readings.nc_2p5  *= 100;
    pm_readings.nc_4p0  *= 100;
    pm_readings.nc_10p0 *= 100;

    if (response < 0) {
        if (debug) Serial.println("SPS30: error getting SPS30 data");
        return false;
    }

    return true;
}
bool Sck_SPS30::sleep()
{
    if (state != SPS30_IDLE) {
        int16_t result = sps30_stop_measurement();
        if (result < 0) {
            if (debug) {
                Serial.print("Error on stoping measurement SPS30: ");
                Serial.println(result);
            }
            return false; 
        }

        measureStarted = 0;
        state = SPS30_IDLE;
    }

    int16_t result = sps30_sleep();
    if (result < 0) {
        if (debug) {
            Serial.print("Error on sleep SPS30: ");
            Serial.println(result);
        }
        return false; 
    }

    if (debug) Serial.println("SPS30: going to sleep...");
    monitor = false;
    state = SPS30_SLEEP;
    return true;
}
bool Sck_SPS30::wake()
{
    int16_t result = sps30_wake_up();
    if (result < 0) {
        if (debug) {
            Serial.print("Error starting measurement on SPS30: ");
            Serial.println(result);
        }
        return false; 
    }

    if (debug) Serial.println("SPS30: Waking Up...");
    state = SPS30_IDLE;
    return true;
}

// this fixes a problem with Sensirion Arduino Core Library where sizeBuffer cannot hold more than 255, (samd21 i2c buffer is 256)
// https://github.com/Sensirion/arduino-core/blob/main/src/SensirionI2CCommunication.cpp#LL82C5-L82C5
#define I2C_BUFFER_LENGTH 255
bool Sck_SEN5X::start(SensorType wichSensor)
{
    // If detection already failed dont try again until next reset
    if (state == SEN5X_NOT_DETECTED) return false;

    // if state is not OFF the sensor is already started so we only enable the metric but we don't need to init the sensor again
    if (state != SEN5X_OFF) {

        bool wasEnabled = false;

        for (uint8_t i=0; i<totalMetrics; i++) {
            if (enabled[i][0] == wichSensor && (enabled[i][2] & model == 1)) {
                enabled[i][1] = 1;
                wasEnabled = true;
            }
        }
        return wasEnabled;
    }

    // The SCK needs battery to survive the sensor startup current draw, with only usb power it normally does not work
    // If battery is not present it  can enter a reset loop, (not always)
    pinMode(pinPM_ENABLE, OUTPUT);
    digitalWrite(pinPM_ENABLE, HIGH);
    delay(25);

    state = SEN5X_NOT_DETECTED;

    if (!I2Cdetect(&Wire, address)) {
        if (debug) Serial.println("SEN5X ERROR no device found on adress");
        return false;
    }

    sen5x.begin(Wire);

    delay(25); // without this there is an error on the deviceReset function

    if (isError(sen5x.deviceReset())) return false;

    if (!findModel()) {
        Serial.println("SEN5X: error finding sensor model");
        return false;
    }

    // Check if firmware version allows The direct switch between Measurement and RHT/Gas-Only Measurement mode
    if (!getVer()) return false;
    if (firmwareMajor < 2) {
        Serial.println("SEN5X: error firmware is too old and will not work with this implementation");
        return false;
    }

    // Detection succeeded
    state = SEN5X_IDLE;

    // Call start again to just enable the corresponding metric
    return start(wichSensor);
}
bool Sck_SEN5X::stop(SensorType wichSensor)
{
    bool changed = false;

    // Mark this specific metric as disabled
    for (uint8_t i=0; i<totalMetrics; i++) {
        if (enabled[i][0] == wichSensor) {
            enabled[i][1] = 0;
            changed = true;
        }
    }

    // Check if any metric is still enabled
    for (uint8_t i=0; i<totalMetrics; i++) {
        if (enabled[i][1]) return changed;
    }

    // If no metric is enabled turn off power
    if (debug) Serial.println("SEN5X: Stoping sensor");
    digitalWrite(pinPM_ENABLE, LOW);

    state = SEN5X_OFF;

    return true;
}
bool Sck_SEN5X::getReading(OneSensor* wichSensor)
{
    uint32_t now = rtc->getEpoch();

    switch (state) {
        case SEN5X_OFF: {
            return false;
        }
        case SEN5X_IDLE: {
            // TODO manage low power and fast metrics (non PM) when PM is not being read
            // if (wichSensor == SENSOR_SEN5X_HUMIDITY         ||
            //     wichSensor == SENSOR_SEN5X_TEMPERATURE      ||
            //     wichSensor == SENSOR_SEN5X_VOCS_IDX         ||
            //     wichSensor == SENSOR_SEN5X_NOX_IDX          ||
            //     wichSensor == SENSOR_SEN5X_HUMIDITY_RAW     ||
            //     wichSensor == SENSOR_SEN5X_TEMPERATURE_RAW  ||
            //     wichSensor == SENSOR_SEN5X_VOCS_RAW         ||
            //     wichSensor == SENSOR_SEN5X_NOX_RAW) 
            // {
            //     sen5x.
            // } else {
            //
            // }

            // If last reading is recent doesn't make sense to get a new one
            if (now - lastReading < warmUpPeriod[0] && !monitor) {
                if (debug) Serial.println("SEN5X: Less than warmUp period since last update, data is still valid...");
                return true;
            }

            if (isError(sen5x.startMeasurement())) return false;

            if (debug) Serial.println("SEN5X: Started measurement (with PMs)");
            measureStarted = now;
            state = SEN5X_MEAS_WARMUP;
        }
        case SEN5X_MEAS_WARMUP: {

            // On monitor mode we don't wait for warmUP'
            if (monitor) {
                if (!update(wichSensor->type)) return false;
                else {
                    lastReading = now;
                    wichSensor->state = 0;
                    return true;
                }
            }

            // PM readings
            uint32_t passed = now - measureStarted;

            // If warmUp period has finished get a reading
            if (passed >= warmUpPeriod[0]) {

                if (!update(wichSensor->type)) return false;

                // If the reading is low (the tyhreshold is in #/cm3) and second warmUp hasn't passed we keep waiting
                if ((pN4p0 / 100) < concentrationThreshold && passed < warmUpPeriod[1]) {
                    if (debug) Serial.println("SEN5X: Concentration is low, we will wait for the second warm Up");
                    state = SEN5X_MEAS_WARMUP_2;
                    wichSensor->state = warmUpPeriod[1] - passed; 	// Report how many seconds are missing to cover the first warm up period
                    return true;
                }

                // Save power
                idle();

                // Return the reading
                lastReading = now;
                wichSensor->state = 0;
                return true;
            }

            wichSensor->state = warmUpPeriod[0] - passed;
            if (debug) Serial.println("SEN5X: Still on first warm up period");
            return true;
            break;
        }
        case SEN5X_MEAS_WARMUP_2: {

            uint32_t passed = now - measureStarted;

            if (passed < warmUpPeriod[1]) {
                wichSensor->state = warmUpPeriod[1] - passed; 	// Report how many seconds are missing to cover the second warm up period
                if (debug) Serial.println("SEN5X: Still on second warm up period");
                return true;
            }

            if (!update(wichSensor->type)) return false;

            // Save power
            idle();

            lastReading = now;
            wichSensor->state = 0;
            return true;
        }
        case SEN5X_MEAS_GAS: {
            // TODO
            break;
        }
        case SEN5X_NOT_DETECTED: {
            return false;
        }
        default:
            break;
    }
    return false;
}
bool Sck_SEN5X::idle()
{
    if (isError(sen5x.stopMeasurement())) return false;
    else if (debug) Serial.println("SEN5X: Stopped measurement");

    monitor = false;
    state = SEN5X_IDLE;
    measureStarted = 0;
}
uint8_t Sck_SEN5X::getCleaningInterval()
{
    // TODO
    return true;
}
bool Sck_SEN5X::setCleaningInterval(uint8_t interval_days)
{
    // TODO 
    return true;
}
bool Sck_SEN5X::startCleaning()
{
    // TODO
    return true;
}
bool Sck_SEN5X::update(SensorType wichSensor)
{
    // Try to get new data
    bool data_ready = false;
    if(isError(sen5x.readDataReady(data_ready))) return false;

    if (!data_ready) {
        if (debug) Serial.println("SEN5X: Data is not ready");
        return false;
    }

    // Ask for the new data
    if (isError( sen5x.readMeasuredPmValues( pM1p0, pM2p5, pM4p0, pM10p0,
                                            pN0p5, pN1p0, pN2p5, pN4p0, pN10p0,
                                            tSize))) return false;

    // Convert PN readings from #/cm3 to #/0.1l
    pN0p5  *= 100;
    pN1p0  *= 100;
    pN2p5  *= 100;
    pN4p0  *= 100;
    pN10p0 *= 100;
    tSize  *= 100;


    // TODO manage temp hum and gas readings

    return true;
}
bool Sck_SEN5X::findModel()
{
    const uint8_t nameSize = 32;
    unsigned char name[nameSize];

    if (isError(sen5x.getProductName(name, nameSize))) return false;

    char cname[nameSize];
    for (uint8_t i=0; i<nameSize; i++) { cname[i] = (char)name[i]; }

    if (debug) {
        Serial.print("SEN5X: found sensor model ");
        Serial.println(cname);
    }


    if (strcmp(cname, "SEN50") == 0) model = SEN50;
    else if (strcmp(cname, "SEN54") == 0) model = SEN54;
    else if (strcmp(cname, "SEN55") == 0) model = SEN54;
    else return false;

    return true;
}
bool Sck_SEN5X::getVer()
{
    if (isError(sen5x.getVersion( firmwareMajor, firmwareMinor, firmwareDebug, 
                                 hardwareMajor, hardwareMinor, 
                                 protocolMajor, protocolMinor
                                 ))) return false;

    return true;
}
bool Sck_SEN5X::isError(uint16_t response)
{
    // No error return false;
    if (response == 0) return false;

    // In case of error (and debug is on), print msg
    if (debug) {
        char errorMessage[256];
        errorToString(response, errorMessage, 256);
        Serial.print("SEN5X: ");
        Serial.println(errorMessage);
    }
    return true;
}
