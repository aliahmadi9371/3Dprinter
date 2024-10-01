
#ifndef PROJECTORHID_H
#define PROJECTORHID_H

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <getopt.h>
#include <string.h>
#include <signal.h>

#include <stdbool.h>
#include <unistd.h>
#include <sys/time.h>
#include <pthread.h>
#include <ctype.h>

#include "CyUSBSerial.h"
#define CY_MAX_DEVICES 30
#define CY_MAX_INTERFACES 4


typedef struct _CY_DEVICE_STRUCT {
    int deviceNumber;
    int interfaceFunctionality[CY_MAX_INTERFACES];
    bool isI2c;
    bool isSpi;
    int numInterface; 
}CY_DEVICE_STRUCT;


typedef struct projectorStruct00 {
	char ProjectorPort[128];    // HID or I2C or ... Dev Name
	char ProjectorPortTTL[128];
	int  Model;
	int  I2CAddr;
	unsigned int MinIntensity;
	unsigned int MaxIntensity;
	unsigned int ProjectorOnOffGPIO; // on I2C Models
	unsigned int LedOnOffGPIO;       // on I2C Models
	unsigned int ASICREADYGPIO;      // on I2C Models
	unsigned char i2cbuff[32];
}ProjectorStruct;


class ProjectorHID
{


enum Ddp442CommandId {
    // PC--> DDP4422
    D4422_LED_CURRENT_DAC             = 0xD1,         //Control the Current of LED
    D4422_TEMPERATURE_SENSOR          = 0x9C,         //Read DMD Temperature
    D4422_WRITE_TEST_PATTERNS         = 0x11,         //but not include the pattern type
    D4422_WRITE_INPUT_SOURCE          = 0x01,
    D4422_I2C_READ                    = 0x15,         //All Read cmd must use this first
    D4422_DMD_FAN_CYCLE               = 0xEB,
    D4422_LED_FAN1_CYCLE              = 0xEC,
    D4422_LED_FAN2_CYCLE              = 0xED,
    D4422_LED_TEMPERATURE             = 0x9F,         //Read LED Junction Temperature.
    D4422_LED_DRIVERBOARD_TEMPERATURE = 0x9E,         //Read LED Driverboard Temperature.
    D4422_READ_LIGHT                  = 0xF7,         //Read Light Sensor
    D4422_APPLICATION_VER             = 0x85,         //Read FW Version
    D4422_SEQ_VER                     = 0xBE,         //Read Sequence Revision
    D4422_MOTOR1_DIR                  = 0xB5,         //Motor Direction
    D4422_MOTOR1_STEP                 = 0xB6,         //Motor Step & Frequence
    D4422_MOTOR2_DIR                  = 0xBA,         //Motor Direction
    D4422_MOTOR2_STEP                 = 0xBB,         //Motor Step & Frequence
    D4422_SOLID_FIELD_GENERATOR       = 0x13,         //Use to set solid field color.
    D4422_LED_TYPE                    = 0xD2,         //To Read the LED Wavelength.
    D4422_PROJECTOR_FLIP_HORIZONTAL   = 0x1F,
    D4422_PROJECTOR_FLIP_VERTICAL     = 0x10,
    D4422_V_BY_ONE                    = 0xF3,         //Get Vx1 Status.
    D4422_EXTERNAL_SOURCE             = 0xF0,         //Use for changing projector resolution mode.
};

enum Ddp343xCommandId { 
    D343_WRITE_LED_ENABLE = 0x52,
    D343_READ_LED_ENABLE = 0x53,
    D343_WRITE_LED_CURRENT = 0x54,
    D343_READ_LED_CURRENT = 0x55,
    D343_READ_TEMPERATRUE = 0xd6,
    D343_WRITE_TEST_PATTERNS = 0x0b,
    D343_WRITE_INPUT_SOURCE = 0x05,
    D343_WRITE_PROJCETOR_FLIP = 0x14,
    D343_READ_PROJCETOR_FLIP = 0x15,
    D343_READ_FB_VER = 0xd9,
    D343_WRITE_PWR = 0xa0,
    D343_READ_LIGHT = 0xac,
    D343_WRITE_EXTERNAL_PAD_ADDRESS = 0xEB,
    D343_READ_EXTERNAL_PAD_DATA = 0xED,
};

private:
	ProjectorStruct ProjectorDevice;
	CY_DEVICE_STRUCT *glDevice;
	int i2cDeviceIndex[CY_MAX_DEVICES][CY_MAX_INTERFACES];

	unsigned char *deviceNumber;
	int cyDevices, i2cDevices, numDevices;
	bool deviceAddedRemoved;

public:
	ProjectorHID();
	int  ConncetToProjector(int Model);
	int  DisConncetFromProjector(void);
	void ProjectorOnOff(bool Enable);
	void EnableIntensity(bool Enable);
	void SetIntensity(int Percent);
	int  GetIntensity(void);
    int  GetLightSensor(void);
    float GetTemperature(int id); // 0 = LED  ,   1 = DMD
    int  ReadProjectorMask(int Address, const char* m_path);

private:
	bool isCypressDevice (int deviceNum);
	void printListOfDevices (bool isPrint);
	char GpioReadData (char gpio);
	char GpioWriteData (char gpio,char Data);
	int  i2cReadData (char *rbuffer,int len);
	int  i2cWriteData (char *wbuffer,int len);
    CY_RETURN_STATUS cySPIWaitForIdle(CY_HANDLE cyHandle);
    CY_RETURN_STATUS FlashBlockRead(int address, int len, char *buf);
};

#endif