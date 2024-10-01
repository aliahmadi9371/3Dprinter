
#include "ProjectorHID.h"

#define I2C_DELAY_TIME 1000

ProjectorHID::ProjectorHID()
{
    deviceNumber = NULL;
    i2cDevices = 0, numDevices = 0;
    deviceAddedRemoved = false;
}

bool ProjectorHID::isCypressDevice (int deviceNum) {
    CY_HANDLE handle;
    unsigned char interfaceNum = 0;
    unsigned char sig[6];
    CY_RETURN_STATUS rStatus;
    rStatus = CyOpen (deviceNum, interfaceNum, &handle);
    if (rStatus == CY_SUCCESS){
        rStatus = CyGetSignature (handle, sig);
        if (rStatus == CY_SUCCESS){
            CyClose (handle);
            return true;
        }
        else {
            CyClose (handle);
            return false;
        }
    }
    else 
        return false;
}
void ProjectorHID::printListOfDevices (bool isPrint)
{
    int  index_i = 0, index_j = 0, i, j, countOfDevice = 0, devNum;
    int length, index = 0, numInterfaces, interfaceNum;
    bool set1 = false;

    unsigned char deviceID[CY_MAX_DEVICES];
    unsigned char functionality[64];
    CY_DEVICE_INFO deviceInfo;
    CY_DEVICE_CLASS deviceClass[CY_MAX_INTERFACES];
    CY_DEVICE_TYPE  deviceType[CY_MAX_INTERFACES];
    CY_RETURN_STATUS rStatus;

    deviceAddedRemoved = false; 
    CyGetListofDevices ((UINT8 *)&numDevices);
    //printf ("The number of devices is %d \n", numDevices); 
    for (i = 0; i < numDevices; i++){
        for (j = 0; j< CY_MAX_INTERFACES; j++)
            glDevice[i].interfaceFunctionality[j] = -1;
    }
    if (isPrint){
        printf ("\n\n---------------------------------------------------------------------------------\n");
        printf ("Device Number | VID | PID | INTERFACE NUMBER | FUNCTIONALITY \n");
        printf ("---------------------------------------------------------------------------------\n");
    }
    cyDevices = 0;
    for (devNum = 0; devNum < numDevices; devNum++){
        rStatus = CyGetDeviceInfo (devNum, &deviceInfo);
        interfaceNum = 0;
        if (!rStatus)
        {
            if (!isCypressDevice (devNum)){
                continue;
            }
            strcpy (functionality, "NA");
            numInterfaces = deviceInfo.numInterfaces;
            glDevice[index].numInterface = numInterfaces;
            cyDevices++;
            
            while (numInterfaces){
                if (deviceInfo.deviceClass[interfaceNum] == CY_CLASS_VENDOR)
                {
                    glDevice[index].deviceNumber = devNum;
                    switch (deviceInfo.deviceType[interfaceNum]){
                        case CY_TYPE_I2C:
                            glDevice[index].interfaceFunctionality[interfaceNum] = CY_TYPE_I2C;
                            strcpy (functionality, (char *)"VENDOR_I2C");
                            glDevice[index].isI2c = true;
                            break;
                        case CY_TYPE_SPI:
                            glDevice[index].interfaceFunctionality[interfaceNum] = CY_TYPE_SPI;
                            strcpy (functionality, (char *)"VENDOR_SPI");
                            glDevice[index].isSpi = true;
                            break;
                        default:
                            strcpy (functionality, "NA");
                            break;    
                    }
                }
                else if (deviceInfo.deviceClass[interfaceNum] == CY_CLASS_CDC){
                    strcpy (functionality, "NA");
                }
                if (isPrint) {
                    printf ("%d         |%x  |%x    | %d     | %s\n", index, deviceInfo.vidPid.vid, deviceInfo.vidPid.pid, interfaceNum, functionality );
                }
                interfaceNum++;
                numInterfaces--;
            }
            index++;
        }
    }
    if (isPrint){
        printf ("---------------------------------------------------------------------------------\n\n");
    }
}


char ProjectorHID::GpioReadData (char gpio)
{
    CY_HANDLE handle;
    char pData;
    CY_RETURN_STATUS rStatus;
    rStatus = CyOpen (glDevice[0].deviceNumber, 0, &handle);
    if (rStatus != CY_SUCCESS){
        printf("CY: Open failed \n");
        return rStatus;
    }
    CyGetGpioValue(handle,gpio,&pData);
    CyClose (handle);
    return pData;
}

char ProjectorHID::GpioWriteData (char gpio,char Data)
{
    CY_HANDLE handle;
    CY_RETURN_STATUS rStatus;
    rStatus = CyOpen (glDevice[0].deviceNumber, 0, &handle);
    if (rStatus != CY_SUCCESS){
        printf("CY: Open failed \n");
        return rStatus;
    }
    CySetGpioValue(handle,gpio,Data);
    CyClose (handle);
    return 0;
}

int ProjectorHID::i2cReadData (char *rbuffer,int len)
{
    CY_DATA_BUFFER dataBufferRead;
    CY_HANDLE handle;
    CY_RETURN_STATUS rStatus;
    CY_I2C_DATA_CONFIG i2cDataConfig;

    rStatus = CyOpen (glDevice[0].deviceNumber, 0, &handle);
    if (rStatus != CY_SUCCESS){
        printf("CY_I2C: Open failed \n");
        return rStatus;
    }
    dataBufferRead.buffer = (UCHAR*)rbuffer;
    dataBufferRead.length = len;

    i2cDataConfig.slaveAddress = ProjectorDevice.I2CAddr;
    i2cDataConfig.isStopBit = true;
    i2cDataConfig.isNakBit = true;
    
    rStatus = CyI2cRead (handle, &i2cDataConfig, &dataBufferRead, 5000); 
    if (rStatus != CY_SUCCESS){
        printf ("Error in doing i2c read ... Error is %d \n", rStatus);
        CyClose (handle);
        return -1;
    }    
    CyClose (handle); 
}

int ProjectorHID::i2cWriteData (char *wbuffer,int len)
{
    CY_DATA_BUFFER dataBufferWrite;
    CY_HANDLE handle;
    CY_RETURN_STATUS rStatus;
    CY_I2C_DATA_CONFIG i2cDataConfig;

    rStatus = CyOpen (glDevice[0].deviceNumber, 0, &handle);
    if (rStatus != CY_SUCCESS){
        printf("CY_I2C: Open failed \n");
        return rStatus;
   }

    dataBufferWrite.buffer = (UCHAR*)wbuffer;
    dataBufferWrite.length = len;

    i2cDataConfig.slaveAddress = ProjectorDevice.I2CAddr;
    i2cDataConfig.isStopBit = true;
    
    rStatus = CyI2cWrite (handle, &i2cDataConfig, &dataBufferWrite, 5000);
    if (rStatus != CY_SUCCESS){
        printf ("Error in doing i2c write :   %d\n",rStatus);
        CyClose (handle);
        return -1;
    }
    
    CyClose (handle);
    return 0;
}

CY_RETURN_STATUS ProjectorHID::cySPIWaitForIdle(CY_HANDLE cyHandle)
{
	char rd_data[2], wr_data[2];
	CY_DATA_BUFFER writeBuf, readBuf;
	int timeout = 0xFFFF;
	CY_RETURN_STATUS status;

	//printf("\nSending SPI Status query command to device...");
	writeBuf.length = 2;
	writeBuf.buffer = (unsigned char *)wr_data;

	readBuf.length = 2;
	readBuf.buffer = (unsigned char *)rd_data;

	// Loop here till read data indicates SPI status is not idle
	// Condition to be checked: rd_data[1] & 0x01

	do
	{
		wr_data[0] = 0x05; /* Get SPI status */
		status = CySpiReadWrite(cyHandle, &readBuf, &writeBuf, 5000);

		if (status != CY_SUCCESS)
		{
			//D(printf("\nFailed to send SPI status query command to device."));
			break;
		}
		timeout--;
		if (timeout == 0)
		{
			//D(printf("\nMaximum retries completed while checking SPI status, returning with error code."));
			status = CY_ERROR_IO_TIMEOUT;
			return status;
		}

	} while (rd_data[1] & 0x03); //Check SPI Status

	//D(printf("\nSPI is now in idle state and ready for receiving additional data commands."));
	return status;
}


CY_RETURN_STATUS ProjectorHID::FlashBlockRead(int address, int len, char *buf)
{
    CY_HANDLE handle;
	int BlockSize = 0x1000; //Block read 4KB size
	unsigned char wbuffer[0x1004], rbuffer[0x1004];  //array size is equal to BlockSize+4

	CY_DEVICE_SERIAL_BLOCK dev = SerialBlock_SCB1;
	//Assmumptions:
	//SCB1 is configured as SPI     
	int deviceNumber = glDevice[0].deviceNumber;

	CY_DATA_BUFFER cyDatabufferWrite, cyDatabufferRead;
	CY_RETURN_STATUS rStatus;
	int interfaceNum = 1;
	int cWriteSize, cReadSize;
	int str_addr = address;


	printf("Opening SPI device with device number %d...\n", deviceNumber);

	rStatus = CyOpen(deviceNumber, interfaceNum, &handle);

	if (rStatus != CY_SUCCESS){
		 printf("SPI Device open failed.\n");
		return rStatus;
	}

	printf("SPI Open successfull ...\n");

	//D(printf("Performing Flash Read operation..."));
	while (len > 0)
	{
		printf("Read data from start address :0x%X \n", address);
		wbuffer[0] = 0x3;  // SPI read command
		wbuffer[1] = (address >> 16 & 0xff);
		wbuffer[2] = (address >> 8 & 0xff);
		wbuffer[3] = (address & 0xff);

		cWriteSize = 4;
		if (len > BlockSize)
			cReadSize = BlockSize;
		else
			cReadSize = len;

		//SPI uses a single CySpiReadWrite to perform both read and write 
		//and flush operations.       
		cyDatabufferWrite.buffer = wbuffer;
		cyDatabufferWrite.length = 4 + cReadSize; //4 bytes command + 256 bytes page size

		cyDatabufferRead.buffer = rbuffer;
		cyDatabufferRead.length = 4 + cReadSize;
		// As per the EEPROM datasheet we need to perform simeltanious read and write
		// to do read/write operation on EEPROM.
		// In this case cyDatabufferRead contains data pushed out by EEPROM and not real data.
		rStatus = CySpiReadWrite(handle, &cyDatabufferRead, &cyDatabufferWrite, 5000);
		if (rStatus != CY_SUCCESS){
			printf("Error in doing SPI data write :0x%X \n", cyDatabufferWrite.transferCount);
			return rStatus;
		}

		for (int i = 0; i < cReadSize; i++)
			buf[address - str_addr + i] = rbuffer[cWriteSize + i];

		//D(printf("Wait for EEPROM active state..."));
		rStatus = cySPIWaitForIdle(handle);
		if (rStatus){
			printf("Error in Waiting for Flash active state:0x%X \n", rStatus);
			return rStatus;
		}

		address += BlockSize;
		if (len > BlockSize)
			len -= BlockSize;
		else
			len = 0;
	}

	//printf("Closeing SPI device...\n");
	rStatus = CyClose(handle);
	if (rStatus != CY_SUCCESS){
		//printf("SPI Device close failed.\n");
		return rStatus;
	}

	printf("Flash Read Done ...");
	return CY_SUCCESS;
}


//==============================================================================================
void ProjectorHID::ProjectorOnOff(bool Enable)
{
    char sendBuf[8];
    int couner = 25;

    if (ProjectorDevice.Model==2150)
    {
        if (Enable)
        {
            GpioWriteData(ProjectorDevice.ProjectorOnOffGPIO, 1);
            while(GpioReadData(ProjectorDevice.ASICREADYGPIO) == 0)
            {
                usleep(1000*1000);
                couner--;
                if (couner <1)
                    break;
            }
        }
        else
        {
            GpioWriteData(ProjectorDevice.LedOnOffGPIO, 0);
            GpioWriteData(ProjectorDevice.ProjectorOnOffGPIO, 0);
        }
    }
    else if (ProjectorDevice.Model==1075)
    {
        if (Enable)
        {
            GpioWriteData(ProjectorDevice.ProjectorOnOffGPIO, 1);
        }
        else
        {
            GpioWriteData(ProjectorDevice.ProjectorOnOffGPIO, 0);
        }
    }
    
}


int ProjectorHID::ConncetToProjector(int Model) 
{
    ProjectorDevice.Model = Model;
    sprintf(ProjectorDevice.ProjectorPort,"");
    ProjectorDevice.ProjectorOnOffGPIO = 0;
    ProjectorDevice.LedOnOffGPIO = 14;
    ProjectorDevice.ASICREADYGPIO =15;
    for (int i=0;i<32;i++)
	ProjectorDevice.i2cbuff[i] = 0;

    CY_RETURN_STATUS rStatus;
    //signal (SIGUSR1, deviceHotPlug);
    glDevice = (CY_DEVICE_STRUCT *)malloc (CY_MAX_DEVICES *sizeof (CY_DEVICE_STRUCT));
    if (glDevice == NULL){
        printf ("Memory allocation failed ...!! \n");
        return -1;
    }
    rStatus = CyLibraryInit ();
    if (rStatus != CY_SUCCESS) {
        printf ("CY:Error in Doing library init Error NO:<%d> \n", rStatus);
        return rStatus;
    }
    rStatus = CyGetListofDevices ((UINT8 *)&numDevices);
    if (rStatus != CY_SUCCESS) {
        printf ("CY:Error in Getting List of Devices: Error NO:<%d> \n", rStatus);
    }

   if (ProjectorDevice.Model==2150)
   {
       ProjectorDevice.I2CAddr = 0x1A;
       ProjectorDevice.MinIntensity = 50;
       ProjectorDevice.MaxIntensity = 1000;
       ProjectorDevice.ProjectorOnOffGPIO = 0;
       ProjectorDevice.LedOnOffGPIO = 14;
   }
   else if (ProjectorDevice.Model==1075)
   {
       ProjectorDevice.I2CAddr = 0x1B;
       ProjectorDevice.MinIntensity = 50;
       ProjectorDevice.MaxIntensity = 0x32A;
       ProjectorDevice.ProjectorOnOffGPIO = 2;
       //ProjectorDevice.LedOnOffGPIO = ??;
   }

   printListOfDevices(true);

   //ProjectorOnOff(true);
   return rStatus;
}

int ProjectorHID::DisConncetFromProjector(void)
{
    ProjectorOnOff(false);
    free (glDevice);
    return 0;
}

void ProjectorHID::EnableIntensity(bool Enable)
{
    char sendBuf[8];
    if (ProjectorDevice.Model==2150)
    {
        if (Enable)
            GpioWriteData(ProjectorDevice.LedOnOffGPIO, 1);
        else
            GpioWriteData(ProjectorDevice.LedOnOffGPIO, 0);
    }
    else if (ProjectorDevice.Model==1075)
    {
        sendBuf[0] = D343_WRITE_LED_ENABLE;
        if (Enable)
        {
            sendBuf[1] = 7;
        }
        else
        {
            sendBuf[1] = 0;
        }
        i2cWriteData(sendBuf, 0);

        GpioWriteData(ProjectorDevice.LedOnOffGPIO, (char)Enable);
    }
    
}

void ProjectorHID::SetIntensity(int Percent)
{
    int level = ((ProjectorDevice.MaxIntensity-ProjectorDevice.MinIntensity)*Percent)/100+ProjectorDevice.MinIntensity;
    char sendBuf[8];

  if (ProjectorDevice.Model==2150)
   {
        sendBuf[0] = D4422_LED_CURRENT_DAC;
        sendBuf[1] = (char)((level >> 8) & 0xFF);
        sendBuf[2] = (char)(level & 0xFF);
        i2cWriteData(sendBuf,3);
   }
   else if (ProjectorDevice.Model==1075)
   {
        sendBuf[0] = D343_WRITE_LED_CURRENT;
        sendBuf[1] = (level & 0xFF);
        sendBuf[2] = ((level >> 8) & 0xFF);
        sendBuf[3] = (level & 0xFF);
        sendBuf[4] = ((level >> 8) & 0xFF);
        sendBuf[5] = (level & 0xFF);
        sendBuf[6] = ((level >> 8) & 0xFF);
        i2cWriteData(sendBuf, 7);
   }
}

int ProjectorHID::GetIntensity(void)
{
   int val = 0;
   char sendBuf[8];
   char getBuf[8];

   if (ProjectorDevice.Model==2150)
   {
        sendBuf[0] = D4422_I2C_READ;
        sendBuf[1] = D4422_LED_CURRENT_DAC;
        i2cWriteData(sendBuf,2);
        usleep(I2C_DELAY_TIME*1000);
        i2cReadData(getBuf, 2);
        val = (getBuf[0] << 8) | getBuf[1];
   }
   else if (ProjectorDevice.Model==1075)
   {
        sendBuf[0] = D343_READ_LED_CURRENT;
        i2cWriteData(sendBuf, 1);
        usleep(I2C_DELAY_TIME*1000);
        i2cReadData(getBuf, 6);
        val = (getBuf[3] << 8) | getBuf[2];
   }
   return val;
}

int ProjectorHID::GetLightSensor(void)
{
   int val = -1;
   char sendBuf[8];
   char getBuf[8];

   if (ProjectorDevice.Model==2150)
   {
        sendBuf[0] = D4422_I2C_READ;
        sendBuf[1] = D4422_READ_LIGHT;
        i2cWriteData(sendBuf,2);
        usleep(I2C_DELAY_TIME*1000);
        i2cReadData(getBuf, 2);
        val = (getBuf[1] << 8) | getBuf[0];
   }
   else if (ProjectorDevice.Model==1075)
   {
   }
   return val;
}

float ProjectorHID::GetTemperature(int id)
{
   float fval = -1;
   char sendBuf[8];
   char getBuf[8];

   if (ProjectorDevice.Model==2150)
   {
        if (id == 0)
        {
            sendBuf[0] = D4422_I2C_READ;
            sendBuf[1] = D4422_LED_TEMPERATURE;
            i2cWriteData(sendBuf,2);
            usleep(I2C_DELAY_TIME*1000);
            i2cReadData(getBuf, 4);
            memcpy (&fval,&getBuf,4);
        }
        else if (id == 1)
        {
            sendBuf[0] = D4422_I2C_READ;
            sendBuf[1] = D4422_TEMPERATURE_SENSOR;
            i2cWriteData(sendBuf,2);
            usleep(I2C_DELAY_TIME*1000);
            i2cReadData(getBuf, 1);
            fval = (float)(getBuf[0]);
        }
   }
   else if (ProjectorDevice.Model==1075)
   {
        if (id == 0)
        {
            sendBuf[0] = D343_READ_TEMPERATRUE;
            i2cWriteData(sendBuf, 1);
            usleep(I2C_DELAY_TIME*1000);
            i2cReadData(getBuf, 2);
            fval = (float)((getBuf[1] << 8) | getBuf[0]);
        }
   }
   return fval;
}

int ProjectorHID::ReadProjectorMask(int Address, const char* m_path)
{
	int len = 0;
	int addr = Address;  // 0x10000; //PNG file starting address
	char header_buf[] = { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 }; //4bytes file check sum and 4bytes file check sum
	char *png_buf = NULL;
	int status;
	UINT32 png_len = 0;
	UINT32 png_cksum = 0;
	//Reading PNG file Length and check sum from SPI flash
	status = FlashBlockRead(addr, 8, header_buf);
	if (status != CY_SUCCESS)
	{
		printf("\nFailed to Read.");
		return -1;
	}
    else
    {
        //printf("\nRead Flash OK \n");
    }
    

	png_len = header_buf[0] & 0xff | header_buf[1] << 8 & 0xff00 | header_buf[2] << 16 & 0xff0000 | header_buf[3] << 24 &
		0xff000000;
	png_cksum = header_buf[4] & 0xff | header_buf[5] << 8 & 0xff00 | header_buf[6] << 16 & 0xff0000 | header_buf[7] << 24 &
		0xff000000;
	printf("pngfile length: %d, checksum: %d", png_len, png_cksum);
	if (png_len == 0){
		printf("Size of png equal to zero....");
		return -1;
	}
	//Reading PNG file from SPI Flash
	png_buf = (char *)malloc(png_len);
	status = FlashBlockRead(addr + 8, png_len, png_buf);
	if (status != CY_SUCCESS)
	{
		printf("\nFailed to Read.");
	}
	UINT32 cksum = 0;
	for (int i = 0; i< png_len; i++)
	{
		cksum += png_buf[i] & 0xff;
	}
	if (cksum != png_cksum)
	{
		printf("\nFfile check sum is NG.");
		return -1;
	}
	else printf("\nFile check sum is OK.");
	//Saving the PNG file FILE *pFile;
	FILE *pFile;
	pFile = fopen(m_path, "wb");
	if (NULL == pFile){
		printf("file open failure!\n");
		return -1;
	}
	else{
		fwrite(png_buf, 1, png_len, pFile);
	}
	fclose(pFile);
	free(png_buf);
	return 0;
}
