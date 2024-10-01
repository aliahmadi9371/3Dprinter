
#include "ProjectorCOMM.h"
#include "ProjectorRS232.h"
#include <QDebug>

#define I2C_DELAY_TIME 1000

ProjectorCOMM::ProjectorCOMM()
{
    deviceNumber = NULL;
    i2cDevices = 0, numDevices = 0;
    deviceAddedRemoved = false;
}

bool ProjectorCOMM::isCypressDevice (int deviceNum) {
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
void ProjectorCOMM::printListOfDevices (bool isPrint)
{
    int  index_i = 0, index_j = 0, i, j, countOfDevice = 0, devNum;
    int length, index = 0, numInterfaces, interfaceNum;
    bool set1 = false;

    unsigned char deviceID[CY_MAX_DEVICES];
    char functionality[64]; //unsigned char functionality[64];
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
//        printf ("\n\n---------------------------------------------------------------------------------\n");
//        printf ("Device Number | VID | PID | INTERFACE NUMBER | FUNCTIONALITY \n");
//        printf ("---------------------------------------------------------------------------------\n");

        qDebug() << "---------------------------------------------------------------------------------";
        qDebug() << "ProjectorCOMM: printListOfDevices: Device Number | VID | PID | INTERFACE NUMBER | FUNCTIONALITY";
        qDebug() << "---------------------------------------------------------------------------------";

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
            strcpy(functionality, "NA");
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

//                    printf ("%d         |%x  |%x    | %d     | %s\n", index, deviceInfo.vidPid.vid, deviceInfo.vidPid.pid, interfaceNum, functionality );
                    qDebug() << "ProjectorCOMM: printListOfDevices: " << index << deviceInfo.vidPid.vid <<  deviceInfo.vidPid.pid <<  interfaceNum << functionality;

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


char ProjectorCOMM::GpioReadData (char gpio)
{
    CY_HANDLE handle;
    char pData;
    CY_RETURN_STATUS rStatus;
    rStatus = CyOpen (glDevice[0].deviceNumber, 0, &handle);
    if (rStatus != CY_SUCCESS){

//        printf("CY: Open failed \n");
        qDebug() << "ProjectorCOMM: GpioReadData: CY: Open failed" ;

        return rStatus;
    }
//    CyGetGpioValue(handle, static_cast<UINT8>(gpio), &pData);
    UINT8 temp;
    CyGetGpioValue(handle, gpio, &temp );

    CyClose (handle);
    pData = temp;
    return pData;
}

char ProjectorCOMM::GpioWriteData (char gpio,char Data)
{
    CY_HANDLE handle;
    CY_RETURN_STATUS rStatus;
    rStatus = CyOpen (glDevice[0].deviceNumber, 0, &handle);
    if (rStatus != CY_SUCCESS){

//        printf("CY: Open failed \n");
        qDebug() << "ProjectorCOMM: GpioWriteData: CY: Open failed";

        return rStatus;
    }
    CySetGpioValue(handle,gpio,Data);
    CyClose (handle);
    return 0;
}

int ProjectorCOMM::i2cReadData (char *rbuffer,int len)
{
    CY_DATA_BUFFER dataBufferRead;
    CY_HANDLE handle;
    CY_RETURN_STATUS rStatus;
    CY_I2C_DATA_CONFIG i2cDataConfig;

    rStatus = CyOpen (glDevice[0].deviceNumber, 0, &handle);
    if (rStatus != CY_SUCCESS){

//        printf("CY_I2C: Open failed \n");
        qDebug() << "ProjectorCOMM: i2cReadData: CY_I2C: Open failed";

        return rStatus;
    }
    dataBufferRead.buffer = (UCHAR*)rbuffer;
    dataBufferRead.length = len;

    i2cDataConfig.slaveAddress = ProjectorDevice.I2CAddr;
    i2cDataConfig.isStopBit = true;
    i2cDataConfig.isNakBit = true;
    
    rStatus = CyI2cRead (handle, &i2cDataConfig, &dataBufferRead, 5000); 
    if (rStatus != CY_SUCCESS){

//        printf ("Error in doing i2c read ... Error is %d \n", rStatus);
        qDebug() << "ProjectorCOMM: i2cReadData: Error in doing i2c read ... Error is " << rStatus;

        CyClose (handle);
        return -1;
    }    
    CyClose (handle); 
    return rStatus;
}

int ProjectorCOMM::i2cWriteData (char *wbuffer,int len)
{
    CY_DATA_BUFFER dataBufferWrite;
    CY_HANDLE handle;
    CY_RETURN_STATUS rStatus;
    CY_I2C_DATA_CONFIG i2cDataConfig;

    rStatus = CyOpen (glDevice[0].deviceNumber, 0, &handle);
    if (rStatus != CY_SUCCESS){

//        printf("CY_I2C: Open failed \n");
        qDebug() << "ProjectorCOMM: i2cWriteData: CY_I2C: Open failed";

        return rStatus;
   }

    dataBufferWrite.buffer = (UCHAR*)wbuffer;
    dataBufferWrite.length = len;

    i2cDataConfig.slaveAddress = ProjectorDevice.I2CAddr;
    i2cDataConfig.isStopBit = true;

    
    rStatus = CyI2cWrite (handle, &i2cDataConfig, &dataBufferWrite, 5000);
    if (rStatus != CY_SUCCESS){

//        printf ("Error in doing i2c write :   %d\n",rStatus);
        qDebug() << "ProjectorCOMM: i2cWriteData: Error in doing i2c write: " << rStatus;

        CyClose (handle);
        return -1;
    }
    
    CyClose (handle);
    return 0;
}


int ProjectorCOMM::HIDWriteData (unsigned char *wbuffer,int len)
{
    hid_device *handle;
    handle = hid_open(ProjectorDevice.VID, ProjectorDevice.PID, NULL);

    int res = hid_write(handle, wbuffer , len);

	if (res < 0) {

//		printf("Unable to write()\n");
        qDebug() << "ProjectorCOMM: HIDWriteData: Unable to write()";

//		printf("Error: %ls\n", hid_error(handle));
        qDebug() << "ProjectorCOMM: HIDWriteData: Error: " << QString::fromWCharArray(hid_error(handle));

        return -1;
	}

    hid_close(handle);

    return 0;
}

int ProjectorCOMM::HIDReadData (unsigned char *rbuffer,int len)
{
    hid_device *handle;
    handle = hid_open(ProjectorDevice.VID, ProjectorDevice.PID, NULL);

    hid_set_nonblocking(handle, 1);

    int res = hid_get_feature_report(handle, rbuffer, len);
	if (res < 0) {

//		printf("Unable to get a feature report.\n");
        qDebug() << "ProjectorCOMM: HIDReadData: Unable to get a feature report";

//		printf("%ls", hid_error(handle));
        qDebug() << "ProjectorCOMM: HIDReadData: Error: " << QString::fromWCharArray(hid_error(handle));

        return -1;
	}
	else {
		// Print out the returned buffer.

//		printf("Feature Report\n   ");
        qDebug() << "ProjectorCOMM: HIDReadData: Feature Report";

        for (int i = 0; i < res; i++){

//            printf("%02hhx ", rbuffer[i]);
            qDebug() << "ProjectorCOMM: HIDReadData: " << rbuffer[i];

        }
        qDebug() << "";
//		printf("\n");
    }
    hid_close(handle);

    return 0;
}

CY_RETURN_STATUS ProjectorCOMM::cySPIWaitForIdle(CY_HANDLE cyHandle)
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


CY_RETURN_STATUS ProjectorCOMM::FlashBlockRead(int address, int len, char *buf)
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



//    printf("Opening SPI device with device number %d...\n", deviceNumber);
    qDebug() << "CY_RETURN_STATUS ProjectorCOMM: FlashBlockRead: Opening SPI device with device number";

	rStatus = CyOpen(deviceNumber, interfaceNum, &handle);

	if (rStatus != CY_SUCCESS){

//		 printf("SPI Device open failed.\n");
        qDebug() << "CY_RETURN_STATUS ProjectorCOMM: FlashBlockRead: SPI Device open failed.";

		return rStatus;
	}

    qDebug() << "CY_RETURN_STATUS ProjectorCOMM: FlashBlockRead: SPI Open successfull ...";
//	printf("SPI Open successfull ...\n");

	//D(printf("Performing Flash Read operation..."));
	while (len > 0)

    {
//		printf("Read data from start address :0x%X \n", address);
        qDebug() << "CY_RETURN_STATUS ProjectorCOMM: Read data from start address :" << address;

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

//			printf("Error in doing SPI data write :0x%X \n", cyDatabufferWrite.transferCount);
            qDebug() << "CY_RETURN_STATUS ProjectorCOMM: Error in doing SPI data write :" << cyDatabufferWrite.transferCount;

			return rStatus;
		}

		for (int i = 0; i < cReadSize; i++)
			buf[address - str_addr + i] = rbuffer[cWriteSize + i];

		//D(printf("Wait for EEPROM active state..."));
		rStatus = cySPIWaitForIdle(handle);
		if (rStatus){

//			printf("Error in Waiting for Flash active state:0x%X \n", rStatus);
            qDebug() << "CY_RETURN_STATUS ProjectorCOMM: for Flash active state: " << rStatus;

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


//	printf("Flash Read Done ...");
    qDebug() << "CY_RETURN_STATUS ProjectorCOMM: fFlash Read Done ...";

	return CY_SUCCESS;
}


//==============================================================================================
void ProjectorCOMM::ProjectorOnOff(bool Enable)
{
    if (ProjectorDevice.Model==1280){

    }else if (ProjectorDevice.Model==1675){

    }else{
        char sendBuf[8];
        int couner = 25;

        if (ProjectorDevice.Model==2150 || ProjectorDevice.Model==21100 || ProjectorDevice.Model==2162)
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
                // printf("Turned On the projecor \n");
                GpioWriteData(ProjectorDevice.ProjectorOnOffGPIO, 1);
                usleep(2*1000*1000);
            }
            else
            {
                GpioWriteData(ProjectorDevice.ProjectorOnOffGPIO, 0);
                usleep(2*1000*1000);
            }
        }
    }
    
    
}

//=====================================================================================================================================================

int ProjectorCOMM::ConnectToProjector(int Model) 
{
    CY_RETURN_STATUS rStatus;
    ProjectorDevice.Model = Model;
    sprintf(ProjectorDevice.ProjectorPort,"");

    if (ProjectorDevice.Model==1280){
        return 0;
    }else if (ProjectorDevice.Model==1675){

        
        int res;
        unsigned char buf[256];
        #define MAX_STR 255
        wchar_t wstr[MAX_STR];
        hid_device *handle;
        int i;

        struct hid_device_info *devs, *cur_dev;

        ProjectorDevice.VID = 0x2da0;
        ProjectorDevice.PID = 0x0120;
        // ProjectorDevice.MinIntensity = 1000;
        // ProjectorDevice.MaxIntensity = 22000;

        
        if (hid_init())
		    return -1;
        devs = hid_enumerate(0x0, 0x0);
        cur_dev = devs;

        const char* text = "IN-VISION";
        std::string t(text);
        std::wstring a(t.begin(), t.end());

        while (cur_dev) {
             std::wstring k(cur_dev->manufacturer_string);
            if (a.compare(k) == 0){  // cur_dev->manufacturer_string == "IN-VISION"
//                printf("Device Found\n  type: %04hx %04hx\n  path: %s\n  serial_number: %ls", cur_dev->vendor_id, cur_dev->product_id, cur_dev->path, cur_dev->serial_number);
//                printf("\n");
//                printf("  Manufacturer: %ls\n", cur_dev->manufacturer_string);
//                printf("  Product:      %ls\n", cur_dev->product_string);
//                printf("  Release:      %hx\n", cur_dev->release_number);
//                printf("  Interface:    %d\n",  cur_dev->interface_number);
//                printf("\n");

                qDebug() << "ProjectorCOMM: ConnectToProjector: Device Found: type: " <<  cur_dev->vendor_id << " " << cur_dev->product_id << " path: " << QString::fromStdString(cur_dev->path) << " serial_number: " << QString::fromWCharArray(cur_dev->serial_number);
                qDebug() << "ProjectorCOMM: ConnectToProjector: Manufacturer: " << QString::fromWCharArray(cur_dev->manufacturer_string);
                qDebug() << "ProjectorCOMM: ConnectToProjector: Manufacturer: " << QString::fromWCharArray(cur_dev->manufacturer_string);
                qDebug() << "ProjectorCOMM: ConnectToProjector: Product: " << QString::fromWCharArray(cur_dev->product_string);
                qDebug() << "ProjectorCOMM: ConnectToProjector: Release: " << cur_dev->release_number;
                qDebug() << "ProjectorCOMM: ConnectToProjector: Interface: " << cur_dev->interface_number;
                qDebug() << "";

                break;
            }
            
            cur_dev = cur_dev->next;
        }
        hid_free_enumeration(devs);

        return 0;

    }else{
        ProjectorDevice.ProjectorOnOffGPIO = 0;
        ProjectorDevice.LedOnOffGPIO = 14;
        ProjectorDevice.ASICREADYGPIO =15;
        for (int i=0;i<32;i++)
        ProjectorDevice.i2cbuff[i] = 0;

        // CY_RETURN_STATUS rStatus;
        //signal (SIGUSR1, deviceHotPlug);
        glDevice = (CY_DEVICE_STRUCT *)malloc (CY_MAX_DEVICES *sizeof (CY_DEVICE_STRUCT));
        if (glDevice == NULL){

            printf ("Memory allocation failed ...!! \n");
            qDebug() << "ProjectorCOMM: ConnectToProjector: Memory allocation failed ...!!";

            return -1;
        }
        rStatus = CyLibraryInit ();
        if (rStatus != CY_SUCCESS) {

//            printf ("CY:Error in Doing library init Error NO:<%d> \n", rStatus);
            qDebug() << "ProjectorCOMM: ConnectToProjector: CY:Error in Doing library init Error NO:<" << rStatus << ">" ;

            return rStatus;
        }
        rStatus = CyGetListofDevices ((UINT8 *)&numDevices);
        if (rStatus != CY_SUCCESS) {

//            printf ("CY:Error in Getting List of Devices: Error NO:<%d> \n", rStatus);
            qDebug() << "ProjectorCOMM: ConnectToProjector: CY:Error in Getting List of Devices: Error NO:<" << rStatus << ">" ;

        }

        if (ProjectorDevice.Model==2150 || ProjectorDevice.Model==21100 || ProjectorDevice.Model==2162)
        {
            ProjectorDevice.I2CAddr = 0x1A;
            // ProjectorDevice.MinIntensity = 50;
            // ProjectorDevice.MaxIntensity = 1000;
            ProjectorDevice.ProjectorOnOffGPIO = 0;
            ProjectorDevice.LedOnOffGPIO = 14;
        }
        else if (ProjectorDevice.Model==1075)
        {
            ProjectorDevice.I2CAddr = 0x1B;
            // ProjectorDevice.MinIntensity = 50;
            // ProjectorDevice.MaxIntensity = 0x32A;
            ProjectorDevice.ProjectorOnOffGPIO = 2;
            // ProjectorDevice.LedOnOffGPIO = ??;
        }

        printListOfDevices(true);
        //ProjectorOnOff(true);
        return rStatus;
    }
   
}

// //=====================================================================================================================================================

void ProjectorCOMM::SetIntensityMinMax(int MinIntensity,int MaxIntensity,int MinIntensitySensor,int MaxIntensitySensor)
{   
    ProjectorDevice.MinIntensity = MinIntensity;
    ProjectorDevice.MaxIntensity = MaxIntensity;
    ProjectorDevice.MinIntensitySensor = MinIntensitySensor;
    ProjectorDevice.MaxIntensitySensor = MaxIntensitySensor;
}

//=====================================================================================================================================================

int ProjectorCOMM::DisConncetFromProjector(void)
{
    if (ProjectorDevice.Model==1280){
        return 0;
    }else if (ProjectorDevice.Model==1675){
        ProjectorOnOff(false);
        hid_exit();
    }else{
        ProjectorOnOff(false);
        free (glDevice);
    }
    
    return 0;
}

void ProjectorCOMM::EnableIntensity(bool Enable)
{
    if (ProjectorDevice.Model==1280){
    }else if (ProjectorDevice.Model==1675){
        unsigned char sendBuf[8];
        sendBuf[0] = 0x00;  // In linux I should add the report Id before sending (here it is 00)
        sendBuf[1] = 0x00;
        sendBuf[2] = 0x11;
        sendBuf[3] = 0x03;
        sendBuf[4] = 0x00;
        sendBuf[5] = 0x05;
        sendBuf[6] = 0x1A;
        sendBuf[7] = 0x00;
		if (Enable== true) {
			sendBuf[7] = 0x01;
		}
		HIDWriteData(sendBuf,sizeof(sendBuf));

    }else{
        char sendBuf[8];
        if (ProjectorDevice.Model==2150 || ProjectorDevice.Model==21100 || ProjectorDevice.Model==2162)
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
            i2cWriteData(sendBuf, 2);

            // GpioWriteData(ProjectorDevice.LedOnOffGPIO, (char)Enable);
        }
    }
    
    
}

int ProjectorCOMM::SetIntensity(int Percent)
{
    int level = ((ProjectorDevice.MaxIntensity-ProjectorDevice.MinIntensity)*Percent)/100+ProjectorDevice.MinIntensity;

//    printf("Intensity : %d \n", level);
    qDebug() << "ProjectorCOMM: SetIntensity: Intensity: " << level;

    if (ProjectorDevice.Model==1280){
    }else if (ProjectorDevice.Model==1675){
        unsigned char sendBuf[11];

        sendBuf[0] = 0x00;   // In linux I should add the report Id before sending (here it is 00)
        sendBuf[1] = 0x00;
        sendBuf[2] = 0x01;
        sendBuf[3] = 0x06;
        sendBuf[4] = 0x00;
        sendBuf[5] = 0x04;
        sendBuf[6] = 0x1A;

        sendBuf[7] = 0x00;
        sendBuf[8] = 0x00;

        sendBuf[9] = (char)((level >> 8) & 0xFF);
        sendBuf[10] = (char)(level & 0xFF);

        HIDWriteData(sendBuf,sizeof(sendBuf));

    }else{
        
        char sendBuf[8];

        if (ProjectorDevice.Model==2150 || ProjectorDevice.Model==21100 || ProjectorDevice.Model==2162)
        {
                sendBuf[0] = D4422_LED_CURRENT_DAC;
                sendBuf[1] = (char)((level >> 8) & 0xFF);   // shifts all bits of level to 8 and changes 0 to 1 and 1 to 0 (for converting big endians)
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

    return level;

    
}


void ProjectorCOMM::SetIntensityVal(int value)
{
    int level = ProjectorDevice.MinIntensity+value;

//    qDebug()<< "SetIntensityVal:::::::::::::::::"<<level;


    if (level > ProjectorDevice.MaxIntensity)
    {
        level = ProjectorDevice.MaxIntensity;
    }
//    printf("Intensity : %d \n", level);
    if (ProjectorDevice.Model==1280){
    }else if (ProjectorDevice.Model==1675){
        unsigned char sendBuf[11];

        sendBuf[0] = 0x00;   // In linux I should add the report Id before sending (here it is 00)
        sendBuf[1] = 0x00;
        sendBuf[2] = 0x01;
        sendBuf[3] = 0x06;
        sendBuf[4] = 0x00;
        sendBuf[5] = 0x04;
        sendBuf[6] = 0x1A;

        sendBuf[7] = 0x00;
        sendBuf[8] = 0x00;

        sendBuf[9] = (char)((level >> 8) & 0xFF);
        sendBuf[10] = (char)(level & 0xFF);

        HIDWriteData(sendBuf,sizeof(sendBuf));

    }else{

        char sendBuf[8];

        if (ProjectorDevice.Model==2150 || ProjectorDevice.Model==21100 || ProjectorDevice.Model==2162)
        {
                sendBuf[0] = D4422_LED_CURRENT_DAC;
                sendBuf[1] = (char)((level >> 8) & 0xFF);   // shifts all bits of level to 8 and changes 0 to 1 and 1 to 0 (for converting big endians)
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


}

void ProjectorCOMM::SetIntensitySensor(int Percent)
{
    int level = ((ProjectorDevice.MaxIntensitySensor-ProjectorDevice.MinIntensitySensor)*Percent)/100+ProjectorDevice.MinIntensitySensor;
    qDebug() << "ProjectorCOMM: SetIntensitySenso: SetIntensitySensor level at :::::::::::::::::" << level;
    if (ProjectorDevice.Model==1280){
    }else if (ProjectorDevice.Model==1675){
        unsigned char sendBuf[11];

        sendBuf[0] = 0x00;   // In linux I should add the report Id before sending (here it is 00)
        sendBuf[1] = 0x00;
        sendBuf[2] = 0x01;
        sendBuf[3] = 0x06;
        sendBuf[4] = 0x00;
        sendBuf[5] = 0x04;
        sendBuf[6] = 0x1A;

        sendBuf[7] = 0x00;
        sendBuf[8] = 0x00;

        sendBuf[9] = (char)((level >> 8) & 0xFF);
        sendBuf[10] = (char)(level & 0xFF);

        HIDWriteData(sendBuf,sizeof(sendBuf));

    }else{



        int error = 10000;
        int Threshold = 0.005*ProjectorDevice.MaxIntensitySensor;
        qDebug() << "ProjectorCOMM: SetIntensitySenso: Threshold:::::::::::::::::" << Threshold;

        int Intensityval = ((ProjectorDevice.MaxIntensity-ProjectorDevice.MinIntensity)*Percent)/100;   // first guess
        SetIntensityVal(Intensityval);

//        EnableIntensity(1);

//        error = (level-GetLightSensor());

//        while(error>Threshold || error<-Threshold)
//        {
//            Intensityval = Intensityval + (error*static_cast<int>(ProjectorDevice.MaxIntensity))/static_cast<int>(ProjectorDevice.MaxIntensitySensor);
//            if (Intensityval>0)
//            {
//                SetIntensityVal(Intensityval);
//            }else {
//                qDebug()<< "error, Intensityval is negative";
//            }
//            error = (level-GetLightSensor());
//            usleep(.2*1000*1000);
//        }

//        qDebug()<< "SetIntensitySensor done at:::::::::::::::::"<<GetLightSensor();

    }
}





int ProjectorCOMM::GetIntensity(void)
{
    int val;
    if (ProjectorDevice.Model==1280){
        return 0;
    }else if (ProjectorDevice.Model==1675){
        val = 0;

        unsigned char sendBuf[10];

        sendBuf[0] = 0x00;   // In linux I should add the report Id before sending (here it is 00)
        sendBuf[1] = 0xc0;
        sendBuf[2] = 0x11;
        sendBuf[3] = 0x02;
        sendBuf[4] = 0x00;
        sendBuf[5] = 0x01;
        sendBuf[5] = 0x1A;

        HIDWriteData(sendBuf,sizeof(sendBuf));

        unsigned char readBuf[20];
        HIDReadData(readBuf,sizeof(readBuf));


    }else{

        val = 0;
        char sendBuf[8];
        char getBuf[8];

        if (ProjectorDevice.Model==2150 || ProjectorDevice.Model==21100 || ProjectorDevice.Model==2162)
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
    }
   
   return val;
}

int ProjectorCOMM::GetLightSensor(void)
{
    int val;
    if (ProjectorDevice.Model==1280){
        val = -1;
    }else if (ProjectorDevice.Model==1675){
        val = -1;
    }else{
        val = -1;
        char sendBuf[8];
        char getBuf[8];

        if (ProjectorDevice.Model==2150 || ProjectorDevice.Model==21100 || ProjectorDevice.Model==2162)
        {
                sendBuf[0] = D4422_I2C_READ;
                sendBuf[1] = D4422_READ_LIGHT;
                i2cWriteData(sendBuf,2);
                usleep(I2C_DELAY_TIME*1000);
                if(i2cReadData(getBuf, 2) != -1)
                {
//                    val = (getBuf[1] << 8) | getBuf[0];

//                    val = static_cast<unsigned int>(static_cast<unsigned char>((getBuf[1] << 8) | getBuf[0]));
                    unsigned int data1 = static_cast<unsigned int>(static_cast<unsigned char>(getBuf[0]));
                    unsigned int data2 = static_cast<unsigned int>(static_cast<unsigned char>(getBuf[1]));
                    val = (data1 + data2 *256) ;
//                    qDebug()<<"Intensity val from proj is::::"<<val;
                }

        }
        else if (ProjectorDevice.Model==1075)
        {
        }
    }
   
   return val;
}

float ProjectorCOMM::GetTemperature(int id)
{
    float fval;
    if (ProjectorDevice.Model==1280){
        fval = -1;
    }else if (ProjectorDevice.Model==1675){
        fval = -1;
    }else{
        fval = -1;
        char sendBuf[8];
        char getBuf[8];

        if (ProjectorDevice.Model==2150  || ProjectorDevice.Model==2162)
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
    }
   
   return fval;
}

int ProjectorCOMM::ReadProjectorMask(int Address, const char* m_path)
{
    if (ProjectorDevice.Model==1280){
    }else if (ProjectorDevice.Model==1675){
    }else{
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
//            printf("\nFailed to Read.");
            qDebug() << "ProjectorCOMM: ReadProjectorMask: Failed to Read.";

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

//        printf("pngfile length: %d, checksum: %d", png_len, png_cksum);
        qDebug() << "ProjectorCOMM: ReadProjectorMask: pngfile length: " << png_len << ", checksum: " << png_cksum;

        if (png_len == 0){

//            printf("Size of png equal to zero....");
            qDebug() << "ProjectorCOMM: ReadProjectorMask: Size of png equal to zero....";

            return -1;
        }
        //Reading PNG file from SPI Flash
        png_buf = (char *)malloc(png_len);
        status = FlashBlockRead(addr + 8, png_len, png_buf);
        if (status != CY_SUCCESS)
        {
//            printf("\nFailed to Read.");
            qDebug() << "ProjectorCOMM: ReadProjectorMask: Failed to Read.";

        }
        UINT32 cksum = 0;
        for (int i = 0; i< png_len; i++)
        {
            cksum += png_buf[i] & 0xff;
        }
        if (cksum != png_cksum)
        {

//            printf("\nFfile check sum is NG.");
            qDebug() << "ProjectorCOMM: ReadProjectorMask: File check sum is NG";

            return -1;
        }
        else {

//            printf("\nFile check sum is OK.");
            qDebug() << "ProjectorCOMM: ReadProjectorMask: File check sum is OK.";

        }
        //Saving the PNG file FILE *pFile;
        FILE *pFile;
        pFile = fopen(m_path, "wb");
        if (NULL == pFile){

//            printf("file open failure!\n");
           qDebug() << "ProjectorCOMM: ReadProjectorMask: file open failure!";

            return -1;
        }
        else{
            fwrite(png_buf, 1, png_len, pFile);
        }
        fclose(pFile);
        free(png_buf);
    }
	
	return 0;
}


