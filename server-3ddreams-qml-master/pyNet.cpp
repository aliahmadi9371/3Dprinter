
#include "pyNet.h"
#include <QDebug>
#include <QApplication>

NetWork::NetWork()
{

}

void NetWork::setLogger(spdlog::logger *log)
{
  logger = log;
  logger->info("********* NetWork::setLogger *************");
}

void NetWork::setDataBase(DataBase *dataBase)
{
  db = dataBase;
  if( db->openConnection() ) {
     MaterialSchema materialSchema;
     if(db->createTable(materialSchema)) {
         logger->info( "Material table created successfully");
     }
     MachineConfigSchema machineSchema;
     if(db->createTable(machineSchema)) {
         logger->info( "Machine table created successfully");
     }
     MotionSchema motionSchema;
     if(db->createTable(motionSchema)) {
         logger->info( "Motion table created successfully");
     }
     JobSchema jobSchema;
     if(db->createTable(jobSchema)) {
         logger->info( "Job table created successfully");
     }
  }

}

void NetWork::setMutex(mutex *m)
{
   mutexProtection = m;
}

void NetWork::setBackEndfd(vector<int> *cfd)
{
   clientsfd = cfd;
}

void NetWork::pynetMain()
{
   struct sockaddr_in clientaddr;
   socklen_t addrlen;
//   signal(SIGPIPE, SIG_IGN);
   //***********************************
   int sockfd,newsockfd;

       struct sockaddr_in serv_addr;
       struct sockaddr cli_addr;

       sockfd = socket(AF_INET, SOCK_STREAM, 0);   // create a socket
       cout<<"Creating server socket..."<<endl;
       if (sockfd<0) {
           cout<<"SORRY! Cannot create a socket ! "<<endl;
           return;
       }

       int enable = 1;
       if (setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, &enable, sizeof(int) ) < 0) {
           cout<<"setsockopt(SO_REUSEADDR) failed"<<endl;
       }

       memset(&serv_addr,0,sizeof serv_addr);

       int  portno = 7002;
       serv_addr.sin_family = AF_INET;     // ip4 family
       serv_addr.sin_addr.s_addr = INADDR_ANY;  // represents for localhost i.e 127.0.0.1
       serv_addr.sin_port = htons(portno);


       int binded = bind(sockfd, (struct sockaddr *)&serv_addr, sizeof(serv_addr));

       if (binded <0 ) {
           fprintf (stderr,"Error on binding! \n");
           return;
       }

       listen(sockfd, 100);

       int clilen = sizeof(struct sockaddr);



       // for each socket
       int set = 1;


       while(1) {

           newsockfd = accept(sockfd,&cli_addr, (socklen_t*) &clilen);
           cout<<"Accepted a request from client!"<<endl;
           if (newsockfd <0){
               cout<<"ERROR! On Accepting Request ! i.e requests limit crossed "<<endl;
           } else {
//               fcntl(newsockfd, F_SETFL, O_NONBLOCK);
               struct timeval timeout;
               timeout.tv_sec = 1;
               if (setsockopt (newsockfd, SOL_SOCKET, SO_RCVTIMEO, (char *)&timeout,sizeof(timeout)) < 0) {
                   logger->error("set sockopt RCV timeout failed");
               }
               if (setsockopt (newsockfd, SOL_SOCKET, SO_SNDTIMEO, (char *)&timeout, sizeof(timeout)) < 0) {
                   logger->error("set sockopt SND timeout failed");
               }

               setsockopt(newsockfd, SOL_SOCKET, MSG_NOSIGNAL, (void *)&set, sizeof(int));
               thread th(&NetWork::request_handler, this, newsockfd);
               th.detach();
           }

//           request_handler(newsockfd);

//           tempThread.detach();

       }
       close(newsockfd);
       close(sockfd);
}

int NetWork::netInit(NetCommands *lcmds)
{
    net_cmds = lcmds;
	return 0;
}

int NetWork::netClose()
{
    int n=0;
    for (n=0;n<CONNMAX;n++)
    {
       shutdown (clients[n], SHUT_RDWR);    //All further send and recieve operations are DISABLED...
       close(clients[n]);
       clients[n]=-1;
    }
    return 0;
}

void NetWork::startServer(char *port)
{
    struct addrinfo hints, *res, *p;

    // getaddrinfo for host
    memset (&hints, 0, sizeof(hints));
    hints.ai_family = AF_INET;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_flags = AI_PASSIVE;
    if (getaddrinfo( NULL, port, &hints, &res) != 0)
    {
       perror ("getaddrinfo() error");
       exit(1);
    }
    // socket and bind
    for (p = res; p!=NULL; p=p->ai_next)
    {
       listenfd = socket (p->ai_family, p->ai_socktype, 0);
       if (listenfd == -1) continue;
       if (bind(listenfd, p->ai_addr, p->ai_addrlen) == 0) break;
    }
    if (p==NULL)
    {
       perror ("socket() or bind()");
       exit(1);
    }

    freeaddrinfo(res);

    // listen for incoming connections
    if ( listen (listenfd, 1000000) != 0 )
    {
       perror("listen() error");
       exit(1);
    }
}

//=====================================================================================================================================================
int NetWork::CalculateKey(char RequestedCode[])
{
    string sTemp = "";

      int iKeyCountry;
    int iKeyCity;
    int iKeyCustomer;
    int iKeyCustomerReverse;

    int iKeyL;
    int iKeyM;
    int iKeyF;

    int iKeyF2;
    int iKeyM2;
    int iKeyL2;

    int Key;

    ///////////////////////////////////////

    sTemp =  sTemp + machine_cfg->MachineNo[10]+machine_cfg->MachineNo[11];
    iKeyCountry = stoi(sTemp);

    sTemp = "";
    sTemp =  sTemp + machine_cfg->MachineNo[12]+machine_cfg->MachineNo[13];
    iKeyCity = stoi(sTemp);

    sTemp = "";
    sTemp =  sTemp + machine_cfg->MachineNo[14]+machine_cfg->MachineNo[15]+machine_cfg->MachineNo[16];
    iKeyCustomer = stoi(sTemp);

    sTemp = "";
    sTemp =  sTemp + machine_cfg->MachineNo[16]+machine_cfg->MachineNo[15]+machine_cfg->MachineNo[14];
    iKeyCustomerReverse = stoi(sTemp);


    ///////////////////////////////////////

    sTemp = "";
    sTemp =  sTemp + RequestedCode[5]+RequestedCode[6]+RequestedCode[7];
    iKeyL = stoi(sTemp);


    sTemp = "";
    sTemp =  sTemp + RequestedCode[3]+RequestedCode[4];
    iKeyM = stoi(sTemp);


    sTemp = "";
    sTemp =  sTemp + RequestedCode[0]+RequestedCode[1]+RequestedCode[2];
    iKeyF = stoi(sTemp);


    ////////////////////////////////////////

     iKeyF2 = (((iKeyF*iKeyCountry)+(iKeyCity*iKeyCustomerReverse))*3)%1000;
     iKeyM2 = (((((iKeyM*iKeyCustomerReverse)+iKeyCustomer))+(iKeyCountry*5))*22)%100;
     iKeyL2 = (((((iKeyL*iKeyCity))*iKeyCountry)+iKeyCustomerReverse)*7)%1000;

     Key = (iKeyL2*100000)+(iKeyF2*100)+(iKeyM2);


     return Key;
}

//=====================================================================================================================================================
int NetWork::Activate()
{
    string sTemp = "";
    for (int i=0;i<sizeof(net_cmds->iLicenseKey);i++){

       sTemp += net_cmds->iLicenseKey[i];
    }

    if (CalculateKey(net_cmds->iRequestedCode) == stoi(sTemp))
       return 1;
    return 0;
}

//client connection

void NetWork::respond(int n)
{
    char mesg[1024];
    char rcvbuff[24*1024];
    unsigned char sendbuff[3*1024];
    char tmpbuff[320];
    int filesize = 0;
    int bytes_read = 0;

    int rcvd;
    int resn = 0;

    char *ptmesg = &mesg[0];

    int num = 0;
    int read = 0;
    int result = 0;



    rcvd = recv(clients[n], mesg, 1024, 0);
    
    printf ("respond() %s\r\n", mesg);

    if (rcvd<0)   // receive error
    {
       fprintf(stderr,("recv() error\n"));
    }
    else if (rcvd==0)   // receive socket closed
    {
       fprintf(stderr,"Client disconnected upexpectedly.\n");
    }
    else   // message received
    {
       // printf("%s\r\n", mesg);
       if (mesg[0] == 'x')
       {
          printf("\n-> %s\n",mesg+1);
          result = system(mesg+1);
       }
       else if ((mesg[0] == 't')&&(mesg[1] == 11))
       {
          net_cmds->iCalibrState = 7;
          printf("Start Projector Calib.  Message ! ...... \n");
       }
       else if ((mesg[0] == 't')&&(mesg[1] == 12))
       {
          net_cmds->iCalibrState = 8;
          printf("Projector Calib. Finish  Message ! ...... \n");
       }
       else if ((mesg[0] == 'h')&&(mesg[1] == 11))
       {
          net_cmds->iCalibrState = 0xffff11;
          printf("Go Home Message ! ...... \n");
       }
       else if ((mesg[0] == 'g')&&(mesg[1] == 11))
       {
          net_cmds->iCalibrState = 0xffff21;
          unsigned int value;
//          memcpy( net_cmds->iGoPos, mesg+2, 4);
          memcpy( &value, mesg+2, 4);
          net_cmds->iGoPos = value;
          printf("Position Message ! ...... [%d] \n",net_cmds->iGoPos);
       }
       else if ( (mesg[0] == 'i') && (mesg[1] == 11) )
       {
          net_cmds->iCalibrState = 0xffff91;
          unsigned int value;
//          memcpy(net_cmds->iGoPos, mesg+2, 4);
          memcpy(&value, mesg+2, 4);
          net_cmds->iGoPos = value;
          printf("LED Intensity Message ! ...... [%d] \n",net_cmds->iGoPos);
       }
       else if ((mesg[0] == 'm')&&(mesg[1] == 11))
       {
          net_cmds->iCalibrState = 0xffff81;
          unsigned int value;
//          memcpy(net_cmds->iGoPos,mesg+2,4);
          memcpy(&value, mesg+2, 4);
          net_cmds->iGoPos = value;
//          memcpy(net_cmds->iMatPat,mesg+6,4);
//          memcpy(value, mesg+6, 4);
          memcpy(&value, mesg+6, 4);
          net_cmds->iMatPat = value;
       }
       else if ((mesg[0] == 'p')&&(mesg[1] == 11))
       {
          printf("License %d \n",net_cmds->iLicenseStatus);
//          if(net_cmds->iMachineStatus == 0 && net_cmds->iLicenseStatus ==1)
//          {
             net_cmds->iPrintState = 11;
             net_cmds->iMaterial = mesg[2]-10;
             net_cmds->iMotion = mesg[3]-10;
             printf("Start Print Message ! ...... [Mtrl:%d] [Motion:%d] \n",net_cmds->iMaterial,net_cmds->iMotion);
//          }

       }
       else if ((mesg[0] == 'p')&&(mesg[1] == 12))
       {
          net_cmds->iPrintState = 12;
          printf("Stop Print Message ! .......\n");
       }
       else if ((mesg[0] == 'p')&&(mesg[1] == 13))
       {
          net_cmds->iPrintState = 13;
          printf("Pause Print Message ! .......\n");
       }
       else if ((mesg[0] == 'j')&&(mesg[1] == 11))
       {
          printf("Projector ON  Message ! .......   [%d] \n",mesg[2]);
          net_cmds->iCalibrState = mesg[2]+10;
       }
       else if ((mesg[0] == 'j')&&(mesg[1] == 12))
       {
          printf("Projector OFF  Message ! .......  \n");
          net_cmds->iCalibrState = 9;
       }
       else if (mesg[0] == 'c')
       {
          printf("\n-> %s\n",mesg+1);
           sprintf(tmpbuff,"%s",mesg+1);
          result = system(tmpbuff);
       }
       else if (mesg[0] == 's')
       {
           sprintf(mesg+512,"jobs/print.slc"); // Temp (for fix file name)
           file = fopen(mesg+512,"wb");
           read = 0;
           while (1) // read < filesize
           {
               num = recv(clients[n], rcvbuff, 1024, 0);
               if (num <1)
                  break;
              fwrite (rcvbuff , 1, num, file);
               read+=num;
           }
           fclose(file);
           printf("file copied to: %s \n",mesg+512);
       }
       else if( (mesg[0] == 'C') && (mesg[1] == '1') )
       {
           cout<<"machine file"<<endl;
           sprintf(mesg+512,"Configs/machineconfig.bin");
           file = fopen(mesg+512,"wb");
//           if(file<0) {

//           }
           read = 0;
           while (1) // read < filesize
           {
               num = recv(clients[n], rcvbuff, 1024, 0);
               if (num <1)
                  break;
               fwrite (rcvbuff , 1, num, file);
               read+=num;
           }
           fclose(file);
           printf("file copied to: %s \n",mesg+512);
       }
       else if( (mesg[0] == 'C') && (mesg[1] == '2') )
       {
            sprintf(mesg+512,"Configs/motnconfig.bin");
           file = fopen(mesg+512,"wb");
           read = 0;
           while (1) // read < filesize
           {
               num = recv(clients[n], rcvbuff, 1024, 0);
               if (num <1)
                  break;
               fwrite (rcvbuff , 1, num, file);
               read+=num;
           }
           fclose(file);
           printf("file copied to: %s \n",mesg+512);
       }
       else if( (mesg[0] == 'C') && (mesg[1] == '3') )
       {
           sprintf(mesg+512,"Configs/mtrlconfig.bin");
           file = fopen(mesg+512,"wb");
           read = 0;
           while (1) // read < filesize
           {
               num = recv(clients[n], rcvbuff, 1024, 0);
               if (num <1)
                  break;
               fwrite (rcvbuff , 1, num, file);
               read+=num;
           }
           fclose(file);
           printf("file copied to: %s \n",mesg+512);
       }
       else if (mesg[0] == '0')
       {
           file = fopen(mesg+512,"rb");
           fseek(file, 0, SEEK_END);
           filesize = ftell(file);
           printf("Request: %s   = %d Bytes\n",mesg+512,filesize);
           rewind(file);
           if (filesize > 0)
           {
               while ( (bytes_read=fread(sendbuff,1, 1024,file))>0 )
               {
                     resn = write(clients[n],sendbuff, bytes_read);
                     if (resn == -1)
                     {
                         printf("Trans Error! ....  %d \n",bytes_read);
                         break;  // ERROR
                     }
               }
           }
           fclose(file);
           printf("file transfered to client. \n");
       }
       else if (mesg[0] == 'l')
       {
           result = system("ls /home/root/Files > _lst");
           file = fopen("_lst","rb");
           fseek(file, 0, SEEK_END);
           filesize = ftell(file);
           rewind(file);
           if (filesize > 0)
           {
               //send(clients[n], "HTTP/1.0 200 OK\n\n", 17, 0);
               while ( (bytes_read=fread(sendbuff,1, 1024,file))>0 )
               {
                     resn = write(clients[n],sendbuff, bytes_read);
                     if (resn == -1)
                     {
                         printf("Trans Error! ....  %d \n",bytes_read);
                         break;  // ERROR
                     }
               }
           }
           fclose(file);
           printf("List transfered to client. \n");
       }
       else if (mesg[0] == '@')
       {
          net_cmds->iManualMV = mesg[1];
          printf("Movement  Message ! .......   [%d] \n",mesg[1]);
       }
       else if (mesg[0] == '~')
       {
          if (mesg[1]==11)
             net_cmds->iCalibrState = 0xffff31;
          else
             net_cmds->iCalibrState = 0xffff32;
          printf("Eject Calib.  Message ! .......   [%d] \n",mesg[1]);
       }
       else if (mesg[0] == '#')
       {
          memcpy(sendbuff+0,&sys_status.iTotalLayers,4);
          memcpy(sendbuff+4,&sys_status.iCurentLayer,4);
          memcpy(sendbuff+8,&sys_status.RemainedTime,8);
          memcpy(sendbuff+16,&sys_status.RemainedLicense,8);
          // memcpy(sendbuff+4,&sys_status.TotalTime,2);

          resn = write(clients[n],sendbuff, 1024);
          if (resn == -1)
          {
             //printf("Trans Error! ....  %d \n",bytes_read);
          }
          else
          {
             //printf("Transfered Status to client. .................\n");
          }

       }
       else if (mesg[0] == '*')
       {
          memcpy(sendbuff+0, &net_cmds->iLicenseStatus, 1);
          resn = write(clients[n],sendbuff, 1024);
       }
       else if (mesg[0] == '[')
       {

          memcpy(sendbuff, machine_cfg, sizeof(MachineConfig));
          memcpy(sendbuff+128, matrial_cfg, sizeof(MaterialConfig)*MAXMATERIALS);
          memcpy(sendbuff+1024, motion_cfg, sizeof(MotionConfig)*MAXMOTIONS);

          resn = write(clients[n], sendbuff, 1024);
          resn = write(clients[n], sendbuff+1024, 1024);
          resn = write(clients[n], sendbuff+2048, 1024);

          printf("Settings transfered to client.....  \n");
       }
       else if (mesg[0] == '}')
       {
          // printf("****** test\n");
          // cout<< "***************** update configs"<<endl;
          resn = recv(clients[n], rcvbuff, 1024, 0);
          resn = recv(clients[n], rcvbuff+1024, 1024, 0);
          for(int i=0; i<MAXMOTIONS; i++) {
            cout<< motion_cfg[i].Name<<endl;
          }
          memcpy(matrial_cfg,rcvbuff+128,sizeof(MaterialConfig)*MAXMATERIALS);
          memcpy(motion_cfg,rcvbuff+1024,sizeof(MotionConfig)*MAXMOTIONS);

          FILE *file = fopen("Configs/mtrlconfig.bin","wb");
          fwrite(matrial_cfg,1,sizeof(MaterialConfig)*MAXMATERIALS,file);
          fclose(file);

          file = fopen("Configs/motnconfig.bin","wb");
          fwrite(motion_cfg,1,sizeof(MotionConfig)*MAXMOTIONS,file);
          fclose(file);

       }
       else if (mesg[0] == 'k')
       {

          recv(clients[n], rcvbuff, 16, 0);
          memcpy(net_cmds->iRequestedCode,rcvbuff,8);
          memcpy(net_cmds->iLicenseKey,rcvbuff+8,8);

          if (Activate())
             net_cmds->iRenewLicense = 1;
       }

    }

    //Closing SOCKET
    shutdown (clients[n], SHUT_RDWR);       //All further send and recieve operations are DISABLED...
    close(clients[n]);
    clients[n]=-1;
}

int NetWork::networkMessage(int n, int rcvd, char mesg[], spdlog::logger *logger2)
{

    cout<< "networkMessage size:" << rcvd;
    network_messages::NetServerCommands netCmd;
    netCmd.ParseFromArray(mesg, rcvd);
//    qDebug() << "NetWork : networkMessage : packetcode : " << netCmd.packetcode();
    switch (netCmd.packetcode()) {
    case network_messages::NetServerCommands::PacketType::NetServerCommands_PacketType_Material:
        return materialCMDPacket(n, netCmd.materialconfig());
        break;
    case network_messages::NetServerCommands::PacketType::NetServerCommands_PacketType_Motion:
        return motionCMDPacket(n, netCmd.motionconfig());
        break;
    case network_messages::NetServerCommands::PacketType::NetServerCommands_PacketType_Job:{
//        qDebug() << "NetWork : networkMessage : Job";
        return jobCMDPacket(n, netCmd.job3d());
        break;
    }
    case network_messages::NetServerCommands::PacketType::NetServerCommands_PacketType_Print:
        return printCMDPacket(n, netCmd);
        break;
    case network_messages::NetServerCommands::PacketType::NetServerCommands_PacketType_Projector:
        return calibrateCMDPacket(n, netCmd);
        break;
    case network_messages::NetServerCommands::PacketType::NetServerCommands_PacketType_Config:
        return machineConfigCMDPacket(n, netCmd.machineconf());
        break;
    case network_messages::NetServerCommands::PacketType::NetServerCommands_PacketType_ManualMV:
        return mMVCMDPacket(n, netCmd);
        break;
    case network_messages::NetServerCommands::PacketType::NetServerCommands_PacketType_GetState:
        return getStateCMDPacket(n, netCmd);
        break;
    default:
        logger->warn("Wrong netWork message code: {0:d}", netCmd.packetcode());
        return WrongPacketCode;
        break;
    }

}

void NetWork::request_handler(int clientfd)
{
    char mesg[2048];
    int rcvd;

    rcvd = recv(clientfd, mesg, 2048, 0);

    printf ("respond() %s\r\n", mesg);

    if (rcvd<0)   // receive error
    {
       LogInstance::Instance().error("recv() error");
    } else if (rcvd==0)   // receive socket closed
    {
        LogInstance::Instance().warn("Client disconnected upexpectedly.");
    } else {
       int resState =  networkMessage(clientfd, rcvd, mesg, logger);
       if(resState == HoldConnection) {
           return;
       }
    }
    close(clientfd);
}

int NetWork::materialCMDPacket(int clientfd, network_messages::MaterialConfig materialCmd)
{

   MaterialSchema mSchema;
   if(materialCmd.packetcode() == network_messages::MaterialConfig::PacketType::MaterialConfig_PacketType_Get) {
      logger->info("network_messages::MaterialConfig::PacketType::MaterialConfig_PacketType_Get");
      MaterialConfig mTemp;
      if(db->findMaterialById(mSchema.getSqlFindById(materialCmd.rowid()), &mTemp)) {
          sendMaterial(&mTemp, clientfd);
      } else {
          sendNotFound(clientfd);
      }
   } else if(materialCmd.packetcode() == network_messages::MaterialConfig::PacketType::MaterialConfig_PacketType_GetALL) {
       logger->info("network_messages::MaterialConfig::PacketType::MaterialConfig_PacketType_GetALL");
       vector<MaterialConfig> *mConfV = new vector<MaterialConfig>();
       if(db->findAllMaterial(mSchema.getSqlFindAll(), mConfV)) {
           sendAllMaterial(mConfV, clientfd);
       } else {
           sendNotFound(clientfd);
       }
    } else if(materialCmd.packetcode() == network_messages::MaterialConfig::PacketType::MaterialConfig_PacketType_Add) {
      logger->info("network_messages::MaterialConfig::PacketType::MaterialConfig_PacketType_Add");
      mSchema.setMaterialPacket(materialCmd);
      if( db->insert(mSchema.getSqlInsertCommand()) ) {
          sendDoneMsg(clientfd);
      } else {
          sendErrorMsg(clientfd, "");
      }
   } else if(materialCmd.packetcode() == network_messages::MaterialConfig::PacketType::MaterialConfig_PacketType_Edit) {
       logger->info("network_messages::MaterialConfig::PacketType::MaterialConfig_PacketType_Edit");
       mSchema.setMaterialPacket(materialCmd);
       if( db->update(mSchema.getSqlUpdateCommand(materialCmd.rowid())) ) {
           sendDoneMsg(clientfd);
       } else {
           sendErrorMsg(clientfd, "");
       }
   } else if(materialCmd.packetcode() == network_messages::MaterialConfig::PacketType::MaterialConfig_PacketType_Delete) {
       logger->info("network_messages::MaterialConfig::PacketType::MaterialConfig_PacketType_Delete id: {0:d}", materialCmd.rowid());
       if( db->remove(mSchema.getSqlRemoveCommand(materialCmd.rowid())) ) {
           sendDoneMsg(clientfd);
       } else {
           sendErrorMsg(clientfd, "");
       }
   } else {
       return WrongSubPacketCode;
   }

   return 0;
}

void NetWork::sendMaterial(MaterialConfig *mConf, int clientfd)
{
    network_messages::NetClientRes netMsg;
    netMsg.set_packetcode(network_messages::NetClientRes::PacketType::NetClientRes_PacketType_Founded);
    network_messages::MaterialConfig *mMsg = netMsg.add_materials();
    mMsg->set_rowid(mConf->id);
    mMsg->set_name(mConf->Name);
    mMsg->set_intensity(mConf->Intensity);
    mMsg->set_burninlayers(mConf->BurnInLayers);
    mMsg->set_burnintensity(mConf->BurnIntensity);
    mMsg->set_burnincuretime(mConf->BurnInCureTime);
    mMsg->set_layerthickness(mConf->LayerThickness);
    mMsg->set_normalcuretime(mConf->NormalCureTime);
    size_t size = netMsg.ByteSizeLong();
    char *mBuf = new char[size];
    netMsg.SerializeToArray(mBuf, size);
    int resn = writeSocket(clientfd, mBuf, size);
    if (resn == -1){
       spdlog::error("sendMaterial can not send");
    } else{
       logger->info("sendMaterial successfully");
    }
    delete mMsg;
    delete[] mBuf;
}

void NetWork::sendAllMaterial(vector<MaterialConfig> *mConfV, int clientfd)
{
    network_messages::NetClientRes netMsg;
    netMsg.set_packetcode(network_messages::NetClientRes::PacketType::NetClientRes_PacketType_Founded);
    for(int i=0; i<mConfV->size(); i++) {
        network_messages::MaterialConfig *mMsg = netMsg.add_materials();
        MaterialConfig mConf = mConfV->at(i);
        mMsg->set_rowid(mConf.id);
        mMsg->set_name(mConf.Name);
        mMsg->set_intensity(mConf.Intensity);
        mMsg->set_burninlayers(mConf.BurnInLayers);
        mMsg->set_burnintensity(mConf.BurnIntensity);
        mMsg->set_burnincuretime(mConf.BurnInCureTime);
        mMsg->set_layerthickness(mConf.LayerThickness);
        mMsg->set_normalcuretime(mConf.NormalCureTime);
    }
    size_t size = netMsg.ByteSizeLong();
    char *mBuf = new char[size];
    netMsg.SerializeToArray(mBuf, size);
    int resn = writeSocket(clientfd, mBuf, size);
    if (resn == -1){
       spdlog::error("sendAllMaterial can not send");
    } else{
       logger->info("sendAllMaterial successfully");
    }
    delete[] mBuf;
}

int NetWork::motionCMDPacket(int clientfd, network_messages::MotionConfig motionCmd)
{
    MotionSchema mSchema;
    if(motionCmd.packetcode() == network_messages::MotionConfig::PacketType::MotionConfig_PacketType_Get) {
       logger->info("network_messages::MotionConfig::PacketType::MotionConfig_PacketType_Get");
       MotionConfig mTemp;
       if(db->findMotionById(mSchema.getSqlFindById(motionCmd.rowid()), &mTemp)) {
           sendMotion(&mTemp, clientfd);
       } else {
           sendNotFound(clientfd);
       }
    } else if(motionCmd.packetcode() == network_messages::MotionConfig::PacketType::MotionConfig_PacketType_GetALL) {
        logger->info("network_messages::MotionConfig::PacketType::MotionConfig_PacketType_GetALL");
        vector<MotionConfig> *mConfV = new vector<MotionConfig>();
        if(db->findAllMotion(mSchema.getSqlFindAll(), mConfV)) {
            sendAllMotion(mConfV, clientfd);
        } else {
            sendNotFound(clientfd);
        }
     } else if(motionCmd.packetcode() == network_messages::MotionConfig::PacketType::MotionConfig_PacketType_Add) {
       logger->info("network_messages::MotionConfig::PacketType::MotionConfig_PacketType_Add");
       mSchema.setMotionPacket(motionCmd);
       logger->info("*********db->insert(mSchema.getSqlInsertCommand():"+mSchema.getSqlInsertCommand());
       if( db->insert(mSchema.getSqlInsertCommand()) ) {
           sendDoneMsg(clientfd);
       } else {
           sendErrorMsg(clientfd, "");
       }
    } else if(motionCmd.packetcode() == network_messages::MotionConfig::PacketType::MotionConfig_PacketType_Edit) {
        logger->info("network_messages::MotionConfig::PacketType::MotionConfig_PacketType_Edit");
        mSchema.setMotionPacket(motionCmd);
        if( db->update(mSchema.getSqlUpdateCommand(motionCmd.rowid())) ) {
            sendDoneMsg(clientfd);
        } else {
            sendErrorMsg(clientfd, "");
        }
    } else if(motionCmd.packetcode() == network_messages::MotionConfig::PacketType::MotionConfig_PacketType_Delete) {
        logger->info("network_messages::MotionConfig::PacketType::MotionConfig_PacketType_Delete id : {0:d}", motionCmd.rowid());
        if( db->remove(mSchema.getSqlRemoveCommand(motionCmd.rowid())) ) {
            sendDoneMsg(clientfd);
        } else {
            sendErrorMsg(clientfd, "");
        }
    } else {
        return WrongSubPacketCode;
    }
    return 0;
}

void NetWork::sendMotion(MotionConfig *mConf, int clientfd)
{
    network_messages::NetClientRes netMsg;
    netMsg.set_packetcode(network_messages::NetClientRes::PacketType::NetClientRes_PacketType_Founded);
    network_messages::MotionConfig *mMsg = netMsg.add_motions();
    mMsg->set_rowid(mConf->id);
    mMsg->set_name(mConf->Name);
    mMsg->add_layer_settle(mConf->Layer_Settle[0]);
    mMsg->add_layer_settle(mConf->Layer_Settle[1]);
    mMsg->add_layer_breathe(mConf->Layer_Breathe[0]);
    mMsg->add_layer_breathe(mConf->Layer_Breathe[1]);
    mMsg->add_layer_z_lower(mConf->Layer_Z_Lower[0]);
    mMsg->add_layer_z_lower(mConf->Layer_Z_Lower[1]);
    mMsg->add_layer_z_raise(mConf->Layer_Z_Raise[0]);
    mMsg->add_layer_z_raise(mConf->Layer_Z_Raise[1]);
    mMsg->add_layer_overlift(mConf->Layer_Overlift[0]);
    mMsg->add_layer_overlift(mConf->Layer_Overlift[1]);
    mMsg->add_layer_tilt_lower(mConf->Layer_Tilt_Lower[0]);
    mMsg->add_layer_tilt_lower(mConf->Layer_Tilt_Lower[1]);
    mMsg->add_layer_tilt_raise(mConf->Layer_Tilt_Raise[0]);
    mMsg->add_layer_tilt_raise(mConf->Layer_Tilt_Raise[1]);
    mMsg->set_base_layer_settle(mConf->Base_Layer_settle);
    mMsg->add_layer_tilt_percent(mConf->Layer_Tilt_Percent[0]);
    mMsg->add_layer_tilt_percent(mConf->Layer_Tilt_Percent[1]);
    mMsg->set_cut_off_layers(mConf->Cut_Off_Layers);
    mMsg->set_final_overlift(mConf->Final_OverLift);
    size_t size = netMsg.ByteSizeLong();
    char *mBuf = new char[size];
    netMsg.SerializeToArray(mBuf, size);
    int resn = writeSocket(clientfd, mBuf, size);
    if (resn == -1){
       spdlog::error("sendMotion can not send");
    } else{
       logger->info("sendMotion successfully");
    }
    delete mMsg;
    delete[] mBuf;
}

void NetWork::sendAllMotion(vector<MotionConfig> *mConfV, int clientfd)
{
    network_messages::NetClientRes netMsg;
    netMsg.set_packetcode(network_messages::NetClientRes::PacketType::NetClientRes_PacketType_Founded);
    for(int i=0; i<mConfV->size(); i++) {
        network_messages::MotionConfig *mMsg = netMsg.add_motions();
        MotionConfig mConf = mConfV->at(i);
        mMsg->set_rowid(mConf.id);
        mMsg->set_name(mConf.Name);
        mMsg->add_layer_settle(mConf.Layer_Settle[0]);
        mMsg->add_layer_settle(mConf.Layer_Settle[1]);
        mMsg->add_layer_breathe(mConf.Layer_Breathe[0]);
        mMsg->add_layer_breathe(mConf.Layer_Breathe[1]);
        mMsg->add_layer_z_lower(mConf.Layer_Z_Lower[0]);
        mMsg->add_layer_z_lower(mConf.Layer_Z_Lower[1]);
        mMsg->add_layer_z_raise(mConf.Layer_Z_Raise[0]);
        mMsg->add_layer_z_raise(mConf.Layer_Z_Raise[1]);
        mMsg->add_layer_overlift(mConf.Layer_Overlift[0]);
        mMsg->add_layer_overlift(mConf.Layer_Overlift[1]);
        mMsg->add_layer_tilt_lower(mConf.Layer_Tilt_Lower[0]);
        mMsg->add_layer_tilt_lower(mConf.Layer_Tilt_Lower[1]);
        mMsg->add_layer_tilt_raise(mConf.Layer_Tilt_Raise[0]);
        mMsg->add_layer_tilt_raise(mConf.Layer_Tilt_Raise[1]);
        mMsg->set_base_layer_settle(mConf.Base_Layer_settle);
        mMsg->add_layer_tilt_percent(mConf.Layer_Tilt_Percent[0]);
        mMsg->add_layer_tilt_percent(mConf.Layer_Tilt_Percent[1]);
        mMsg->set_cut_off_layers(mConf.Cut_Off_Layers);
        mMsg->set_final_overlift(mConf.Final_OverLift);
    }
    size_t size = netMsg.ByteSizeLong();
    char *mBuf = new char[size];
    netMsg.SerializeToArray(mBuf, size);
    int resn = writeSocket(clientfd, mBuf, size);
    if (resn == -1){
       spdlog::error("sendAllMotion can not send");
    } else{
       logger->info("sendAllMotion successfully");
    }
    delete[] mBuf;
}

QByteArray NetWork::fileChecksum(QString fileName, QCryptographicHash::Algorithm hashAlgorithm)
{
    QFile f(fileName);
//    qDebug() << "hash length of Md5 : " << QCryptographicHash::hashLength(hashAlgorithm);
    if (f.open(QFile::ReadOnly)) {
        QCryptographicHash hash(hashAlgorithm);
        if (hash.addData(&f)) {
//            qDebug() << hash.result();
            return hash.result();
        }
    }
//    qDebug() << QByteArray();
    return QByteArray();
}

int NetWork::jobCMDPacket(int clientfd, network_messages::Job3D jobCmd)
{
//    qDebug() << "NetWork : jobCMDPacket : packet code : " << jobCmd.packetcode();
    JobSchema jSchema;
    if(jobCmd.packetcode() == network_messages::Job3D::PacketType::Job3D_PacketType_Get){
        logger->info("network_messages::Job3D::PacketType::Job3D_PacketType_Get");
        __Job3D jTemp;

        if(db->findJobById(jSchema.getSqlFindById(jobCmd.rowid()), &jTemp)){
            sendJob(&jTemp, clientfd);
        }
        else{
            sendNotFound(clientfd);
        }

    }
    else if(jobCmd.packetcode() == network_messages::Job3D::PacketType::Job3D_PacketType_GetALL){
        logger->info("network_messages::Job3D::PacketType::Job3D_PacketType_GetALL");
        vector<__Job3D> *job3DV = new vector<__Job3D>();

        if(db->findAllJob(jSchema.getSqlFindAll(), job3DV)){
            sendAllJob(job3DV, clientfd);
        }
        else{
            sendNotFound(clientfd);
        }
    }
    else if(jobCmd.packetcode() == network_messages::Job3D::PacketType::Job3D_PacketType_Add){
        qDebug() << "NetWork : jobCMDPacket : Job3D_PacketType_Add";
        logger->info("network_messages::Job3D::PacketType::Job3D_PacketType_Add name:"+jobCmd.name());
        jSchema.setJob3DPacket(jobCmd);

        jSchemaCurrent = jSchema;
        currentJobName = QString::fromStdString(jobCmd.name());

        QStorageInfo storage = QStorageInfo::root();
        storage.refresh();
        int freesize = storage.bytesAvailable()/1000/1000 ;
        //       qDebug()<< << "/" << storage.bytesTotal()/1000/1000 << "MB";
        logger->info("Filse size: {0:d}, Free memory: {1:d}", jobCmd.size(), freesize );
        if(freesize < ((jobCmd.size()/1000000)+1000)){ // Assistant::getFreeMemorySpaceSizeToMB("./")
            logger->warn("Not enough memory size:{0:d}", freesize);
            sendErrorMsg(clientfd, "Not enough memory");
            return -1;
        }
        // check file exist
        if (Assistant::isFileExists("./Jobs/"+jobCmd.name()+".slc")  ){ //QFile::exists(QString::fromStdString("./Jobs/"+jobCmd.name()+".slc")
            logger->info("File exist");
            if(!QFile::remove(QString::fromStdString("./Jobs/"+jobCmd.name()+".slc")) ){
               logger->warn("Can not remove file");
            }
        }
        else{
           logger->warn("Job file does not exist path: ./Jobs/"+jobCmd.name()+".slc");
        }

        QFile file(QString::fromStdString("./Jobs/"+jobCmd.name()+".slc") ) ;
        if(file.open(QIODevice::WriteOnly)){
            sendDoneMsg(clientfd);
            logger->info("Job3D_PacketType_Add file "+jobCmd.name()+" open successfully");
            int rcvd = 1;
            char mesg[1024];
            while(rcvd > 0){
                rcvd = recv(clientfd, mesg, 1024, 0);
                file.write(mesg, rcvd);
            }
            file.waitForBytesWritten(3000);
            file.close();
        }
        else{
            logger->error("Job3D_PacketType_Add file "+jobCmd.name()+" can not open");
            sendErrorMsg(clientfd, "");
            return -1;
        }

        QByteArray myChecksum =  fileChecksum(QString::fromStdString("./Jobs/"+jobCmd.name()+".slc"), QCryptographicHash::Algorithm::Md5);
        qDebug() << "NetWork : jobCMDPacket : myChecksum : " << myChecksum;
        sendMd5(clientfd, myChecksum);
    }

    else if(jobCmd.packetcode() == network_messages::Job3D::PacketType::Job3D_PacketType_CheckFile){
//        qDebug() << "NetWork : jobCMDPacket : CheckFile";
        if(jobCmd.md5()){
            qDebug() << "NetWork : jobCMDPacket : Md5 success : add file to db";
            if( db->insert(jSchemaCurrent.getSqlInsertCommand()) ) {
                sendDoneMsg(clientfd);
            }
            else{
                logger->error("data base error");
                sendErrorMsg(clientfd, "data base error");
            }
        }
        else{
            qDebug() << "NetWork : jobCMDPacket : Md5 failed : delete file ";
            if( !QFile::remove("./Jobs/"+currentJobName+".slc") ){
               logger->warn("Can not remove file");
            }
        }

    }

     else if(jobCmd.packetcode() == network_messages::Job3D::PacketType::Job3D_PacketType_Edit) {
        logger->info("network_messages::Job3D::PacketType::Job3D_PacketType_Edit");
        jSchema.setJob3DPacket(jobCmd);
        if( db->update(jSchema.getSqlUpdateCommand(jobCmd.rowid())) ) {
            sendDoneMsg(clientfd);
        } else {
            sendErrorMsg(clientfd, "");
        }
    } else if(jobCmd.packetcode() == network_messages::Job3D::PacketType::Job3D_PacketType_Delete) {
        logger->info("network_messages::Job3D::PacketType::Job3D_PacketType_Delete id:{0:d}", jobCmd.rowid());
        if ( Assistant::isFileExists("./Jobs/"+jobCmd.name()+".slc") ) //QFile::exists(QString::fromStdString("./Jobs/"+jobCmd.name()+".slc") )
        {
            if(!QFile::remove(QString::fromStdString("./Jobs/"+jobCmd.name()+".slc")) ) {
                logger->warn("Can not remove file");
            }
        } else {
            logger->warn("Job file does not exist path: ./Jobs/"+jobCmd.name()+".slc");
        }
        if( db->remove(jSchema.getSqlRemoveCommand(jobCmd.rowid())) ) {
            sendDoneMsg(clientfd);
        } else {
            sendErrorMsg(clientfd, "");
        }
    } else {
        return WrongSubPacketCode;
    }

    return 0;
}

void NetWork::sendJob(__Job3D *mConf, int clientfd)
{
    network_messages::NetClientRes netMsg;
    netMsg.set_packetcode(network_messages::NetClientRes::PacketType::NetClientRes_PacketType_Founded);
    network_messages::Job3D *mMsg = netMsg.add_jobs();
    mMsg->set_rowid(mConf->id);
    mMsg->set_name(mConf->Name);
    mMsg->set_size(mConf->Size);
    size_t size = netMsg.ByteSizeLong();
    char *mBuf = new char[size];
    netMsg.SerializeToArray(mBuf, size);
    int resn = writeSocket(clientfd, mBuf, size);
    if (resn == -1){
       spdlog::error("sendJob can not send");
    } else{
       logger->info("sendJob successfully");
    }
    delete mMsg;
    delete[] mBuf;
}

void NetWork::sendAllJob(vector<__Job3D> *jobV, int clientfd)
{
    network_messages::NetClientRes netMsg;
    netMsg.set_packetcode(network_messages::NetClientRes::PacketType::NetClientRes_PacketType_Founded);
    for(int i=0; i<jobV->size(); i++) {
        network_messages::Job3D *mMsg = netMsg.add_jobs();
        __Job3D job = jobV->at(i);
        mMsg->set_rowid(job.id);
        mMsg->set_name(job.Name);
        mMsg->set_size(job.Size);
    }
    size_t size = netMsg.ByteSizeLong();
    char *mBuf = new char[size];
    netMsg.SerializeToArray(mBuf, size);
    int resn = writeSocket(clientfd, mBuf, size);
    if (resn == -1){
       spdlog::error("sendAllJob can not send");
    } else{
       logger->info("sendAllJob successfully");
    }
    delete[] mBuf;
}

int NetWork::printCMDPacket(int clientfd, network_messages::NetServerCommands printCmd)
{
    if(printCmd.iprintstate() == network_messages::NetServerCommands::PrintState::NetServerCommands_PrintState_StopPrint) {
           logger->info("network_messages::NetServerCommands::PrintState::NetServerCommands_PrintState_StopPrint");
           net_cmds->iPrintState = 12;
           sendDoneMsg(clientfd);
        } else if(printCmd.iprintstate() == network_messages::NetServerCommands::PrintState::NetServerCommands_PrintState_StartPrint) {
            logger->info("network_messages::NetServerCommands::PrintState::NetServerCommands_PrintState_StartPrint");
            logger->info("networkMessage materialid: {0:d}, motionid : {1:d}, jobid : {2:d}", printCmd.materialid(), printCmd.motionid(), printCmd.jobid());
            if(net_cmds->iMachineStatus == 0) //  && net_cmds->iLicenseStatus ==1
            {
                MaterialSchema materialSchema;
                MotionSchema motionSchema;
                JobSchema jobSchema;
                __Job3D job;
                MotionConfig motionConfig;
                MaterialConfig materialConfig;

                if(!db->findJobById(jobSchema.getSqlFindById(printCmd.jobid()), &job)) {
                    cout<< "printStart can not find job, jobId:"<< printCmd.jobid()<<endl;
                    sendErrorMsg(clientfd, "can not get Job");
                    return 0;
                }
                this_thread::sleep_for(std::chrono::milliseconds(50));
                if(!db->findMaterialById(materialSchema.getSqlFindById(printCmd.materialid()), &materialConfig)) {
                    cout<< "printStart can not find Material, materialId:"<< printCmd.materialid()<<endl;
                    sendErrorMsg(clientfd, "can not get Material");
                    return 0;
                }
                this_thread::sleep_for(std::chrono::milliseconds(50));
                if(!db->findMotionById(motionSchema.getSqlFindById(printCmd.motionid()), &motionConfig)) {
                    cout<< "printStart can not find Motion, motionId:"<< printCmd.motionid()<<endl;
                    sendErrorMsg(clientfd, "can not get Motion");
                    return 0;
                }



               net_cmds->iMaterial =  printCmd.materialid();
               net_cmds->iMotion = printCmd.motionid();
               net_cmds->iJobFile = printCmd.jobid();
               net_cmds->materialConfig = materialConfig;
               net_cmds->motionConfig = motionConfig;
               net_cmds->job = job;
               printf("Start Print Message ! ...... [Mtrl:%d] [Motion:%d] \n",net_cmds->iMaterial,net_cmds->iMotion);
               sendDoneMsg(clientfd);
               clientsfd->push_back(clientfd);
//               *backEndClientfd = clientfd;
               net_cmds->iPrintState = 11;
               return HoldConnection;
            } else {
                spdlog::error("networkMessage License: {0:d}, clientfd : {1:d}, iMachineStatus : {2:d}", net_cmds->iLicenseStatus, clientfd, net_cmds->iMachineStatus);
                sendErrorMsg(clientfd, "incorrect machineStatus or license Status");
            }
         } else if(printCmd.iprintstate() == network_messages::NetServerCommands::PrintState::NetServerCommands_PrintState_PausePrint) {
            logger->info("network_messages::NetServerCommands::PrintState::NetServerCommands_PrintState_PausePrint");
            net_cmds->iPrintState = 13;
            printf("Pause Print Message ! .......\n");
            sendDoneMsg(clientfd);
         } else if(printCmd.iprintstate() == network_messages::NetServerCommands::PrintState::NetServerCommands_PrintState_ZeroPirint) {
            logger->info("network_messages::NetServerCommands::PrintState::NetServerCommands_PrintState_ZeroPirint ");
         } else {
            sendErrorMsg(clientfd, "printCMDPacket wrong packet code");
            return WrongSubPacketCode;
        }
        return 0;

}

int NetWork::getStateCMDPacket(int clientfd, network_messages::NetServerCommands stateCmd)
{
//    logger->info("network_messages::NetServerCommands::PacketType::NetServerCommands_PacketType_GetState");
    if(net_cmds->iMachineStatus == 1) {
          sendStateMsg(clientfd, network_messages::NetClientRes::PacketType::NetClientRes_PacketType_Progress);
          this_thread::sleep_for(std::chrono::milliseconds(300)); // for client set up socket
          clientsfd->push_back(clientfd);
           return HoldConnection;
     } else {
//        logger->info("Ready state");
        sendStateMsg(clientfd, network_messages::NetClientRes::PacketType::NetClientRes_PacketType_Ready);
     }
    return 0;
}

int NetWork::calibrateCMDPacket(int clientfd, network_messages::NetServerCommands calibCmd)
{
    switch (calibCmd.icalibrstate()) {
    case network_messages::NetServerCommands::ProjectorCalibrate::NetServerCommands_ProjectorCalibrate_StartCalibrate:
        logger->info("network_messages::NetServerCommands::ProjectorCalibrate::NetServerCommands_ProjectorCalibrate_StartCalibrate");
        net_cmds->iCalibrState = 7;
        sendDoneMsg(clientfd);
        break;
    case network_messages::NetServerCommands::ProjectorCalibrate::NetServerCommands_ProjectorCalibrate_FinishCalibrate:
        logger->info("network_messages::NetServerCommands::ProjectorCalibrate::NetServerCommands_ProjectorCalibrate_FinishCalibrate");
        net_cmds->iCalibrState = 8;
        sendDoneMsg(clientfd);
        break;
    case network_messages::NetServerCommands::ProjectorCalibrate::NetServerCommands_ProjectorCalibrate_GoHomeCalibrate:
        logger->info("network_messages::NetServerCommands::ProjectorCalibrate::NetServerCommands_ProjectorCalibrate_GoHomeCalibrate");
        net_cmds->iCalibrState = 0xffff11;
        sendDoneMsg(clientfd);
        break;
    case network_messages::NetServerCommands::ProjectorCalibrate::NetServerCommands_ProjectorCalibrate_PositionCalibrate:
        logger->info("network_messages::NetServerCommands::ProjectorCalibrate::NetServerCommands_ProjectorCalibrate_PositionCalibrate");
        net_cmds->iCalibrState = 0xffff21;
        net_cmds->iGoPos = calibCmd.igopos();
        printf("Position Message ! ...... [%d] \n",net_cmds->iGoPos);
        sendDoneMsg(clientfd);
        break;

    case network_messages::NetServerCommands::ProjectorCalibrate::NetServerCommands_ProjectorCalibrate_MaterialLevel:
        logger->info("network_messages::NetServerCommands::ProjectorCalibrate::NetServerCommands_ProjectorCalibrate_MaterialFill");
        net_cmds->iCalibrState = 14;
        net_cmds->fmateriallevelmm = calibCmd.fmateriallevelmm();
        printf("material level Message ! ...... [%d] \n",net_cmds->fmateriallevelmm);
        sendDoneMsg(clientfd);
        break;
    case network_messages::NetServerCommands::ProjectorCalibrate::NetServerCommands_ProjectorCalibrate_VacuumFill:
        logger->info("network_messages::NetServerCommands::ProjectorCalibrate::NetServerCommands_ProjectorCalibrate_VacuumFill");
        net_cmds->iCalibrState = 15;
        net_cmds->ffillvacuumsec = calibCmd.ffillvacuumsec();
        printf("FillVacuum Message ! ...... [%f] \n",net_cmds->ffillvacuumsec);
        sendDoneMsg(clientfd);
        break;
    case network_messages::NetServerCommands::ProjectorCalibrate::NetServerCommands_ProjectorCalibrate_GetSensor:
        logger->info("network_messages::NetServerCommands::ProjectorCalibrate::NetServerCommands_ProjectorCalibrate_GetSensor");
        net_cmds->sensorVal = -1;
        net_cmds->iCalibrState = 16;
        printf("GetSensor Message ! ...... [%f] \n",net_cmds->iGoPos);

        while(net_cmds->sensorVal == -1){
            usleep(1000);
        }
        sendSensorVal(clientfd,net_cmds->sensorVal);
        break;

    case network_messages::NetServerCommands::ProjectorCalibrate::NetServerCommands_ProjectorCalibrate_LEDIntensityCalibrate:
        logger->info("network_messages::NetServerCommands::ProjectorCalibrate::NetServerCommands_ProjectorCalibrate_LEDIntensityCalibrate");
        net_cmds->iCalibrState = 0xffff91;
        net_cmds->iGoPos = calibCmd.igopos();
        printf("LED Intensity Message ! ...... [%d] \n",net_cmds->iGoPos);
        sendDoneMsg(clientfd);
        break;
    case network_messages::NetServerCommands::ProjectorCalibrate::NetServerCommands_ProjectorCalibrate_MaterialTestCalibrate:
        logger->info("network_messages::NetServerCommands::ProjectorCalibrate::NetServerCommands_ProjectorCalibrate_MaterialTestCalibrate");
        net_cmds->iCalibrState = 0xffff81;
        net_cmds->iGoPos = calibCmd.igopos();
        net_cmds->iMatPat = calibCmd.imatpat();
        sendDoneMsg(clientfd);
        break;
    case network_messages::NetServerCommands::ProjectorCalibrate::NetServerCommands_ProjectorCalibrate_ProjectorOffCalibrate:
        logger->info("network_messages::NetServerCommands::ProjectorCalibrate::NetServerCommands_ProjectorCalibrate_ProjectorOffCalibrate");
        net_cmds->iCalibrState = 9;
        sendDoneMsg(clientfd);
        break;
    case network_messages::NetServerCommands::ProjectorCalibrate::NetServerCommands_ProjectorCalibrate_LEDTurnOn:
        logger->info("network_messages::NetServerCommands::ProjectorCalibrate::NetServerCommands_ProjectorCalibrate_LEDTurnOn");
        net_cmds->iCalibrState = 11;//mesg[2]+10;
        sendDoneMsg(clientfd);
        break;
    case network_messages::NetServerCommands::ProjectorCalibrate::NetServerCommands_ProjectorCalibrate_LEDTurnOff:
        logger->info("network_messages::NetServerCommands::ProjectorCalibrate::NetServerCommands_ProjectorCalibrate_LEDTurnOff");
        net_cmds->iCalibrState = 12;
        sendDoneMsg(clientfd);
        break;
    case network_messages::NetServerCommands::ProjectorCalibrate::NetServerCommands_ProjectorCalibrate_ShowPattern:
        logger->info("network_messages::NetServerCommands::ProjectorCalibrate::NetServerCommands_ProjectorCalibrate_ShowPattern");
        net_cmds->iCalibrState = 13;
        net_cmds->iMatPat = calibCmd.imatpat();
        sendDoneMsg(clientfd);
        break;
    case network_messages::NetServerCommands::ProjectorCalibrate::NetServerCommands_ProjectorCalibrate_EjectUpCalibrate:
        logger->info("network_messages::NetServerCommands::ProjectorCalibrate::NetServerCommands_ProjectorCalibrate_EjectUpCalibrate");
        net_cmds->iCalibrState = 0xffff31;
        sendDoneMsg(clientfd);
        break;
    case network_messages::NetServerCommands::ProjectorCalibrate::NetServerCommands_ProjectorCalibrate_EjectDownCalibrate:
        logger->info("network_messages::NetServerCommands::ProjectorCalibrate::NetServerCommands_ProjectorCalibrate_EjectDownCalibrate");
        net_cmds->iCalibrState = 0xffff32;
        sendDoneMsg(clientfd);
        break;
    case network_messages::NetServerCommands::ProjectorCalibrate::NetServerCommands_ProjectorCalibrate_ZeroCalibrate:
        logger->info("network_messages::NetServerCommands::ProjectorCalibrate::NetServerCommands_ProjectorCalibrate_ZeroCalibrate");
        sendDoneMsg(clientfd);
        break;
    default:
        spdlog::warn("Wrong netWork message calibCmd.icalibrstate(): {0:d}", calibCmd.icalibrstate());
        sendErrorMsg(clientfd, "wrong packet code");
        return WrongPacketCode;
        break;
    }
    return 0;
}

int NetWork::machineConfigCMDPacket(int clientfd, network_messages::MachineConfig mCmd)
{
    MachineConfigSchema mSchema;
    switch (mCmd.packetcode()) {
    case network_messages::MachineConfig::PacketType::MachineConfig_PacketType_Get: {
        logger->info("network_messages::MachineConfig::PacketType::MachineConfig_PacketType_Get");
        MachineConfig mTemp;
        if(db->findMachineConfigById(mSchema.getSqlFindById(mCmd.rowid()), &mTemp)) {
            sendMachineConf(&mTemp, clientfd);
        } else {
            sendNotFound(clientfd);
        }
        break;
    }
    case network_messages::MachineConfig::PacketType::MachineConfig_PacketType_GetALL: {
        logger->info("network_messages::MachineConfig::PacketType::MachineConfig_PacketType_GetALL");
        vector<MachineConfig> *mConf = new vector<MachineConfig>();
        if(db->findAllMachineConfig(mSchema.getSqlFindAll(), mConf)) {
            sendAllMachineConf(mConf, clientfd);
        } else {
            sendNotFound(clientfd);
        }
        break;
    }
    case network_messages::MachineConfig::PacketType::MachineConfig_PacketType_Add: {
        logger->info("network_messages::MachineConfig::PacketType::MachineConfig_PacketType_Add");
        mSchema.setMachinePacket(mCmd);
        if( db->insert(mSchema.getSqlInsertCommand()) ) {
            sendDoneMsg(clientfd);
        } else {
            sendErrorMsg(clientfd, "");
        }
        break;
    }
    case network_messages::MachineConfig::PacketType::MachineConfig_PacketType_Edit: {
        logger->info("network_messages::MachineConfig::PacketType::MachineConfig_PacketType_Edit");
        mSchema.setMachinePacket(mCmd);   
        if( db->update(mSchema.getSqlUpdateCommand(mCmd.rowid())) ) {
            sendDoneMsg(clientfd);
        } else {
            sendErrorMsg(clientfd, "");
        }
        break;
    }
    case network_messages::MachineConfig::PacketType::MachineConfig_PacketType_Delete: {
        logger->info("network_messages::MachineConfig::PacketType::MachineConfig_PacketType_Delete");
        if( db->remove(mSchema.getSqlRemoveCommand(mCmd.rowid())) ) {
            sendDoneMsg(clientfd);
        } else {
            sendErrorMsg(clientfd, "");
        }
        break;
    }
    case network_messages::MachineConfig::PacketType::MachineConfig_PacketType_SET: {
        logger->info("network_messages::MachineConfig::PacketType::MachineConfig_PacketType_SET");

        if( db->findMachineConfigById(mSchema.getSqlFindByModelCode(mCmd.modelcode()), machine_cfg) ) {
            net_cmds->iMachineConfig = 1;
            sendDoneMsg(clientfd);
        } else {
            sendErrorMsg(clientfd, "");
        }
        break;
    }
    default:
        spdlog::warn("Wrong netWork message mCmd.packetcode(): {0:d}", mCmd.packetcode());
        sendErrorMsg(clientfd, "WrongPacketCode");
        return WrongPacketCode;
        break;
    }
    return 0;
}

void NetWork::sendMachineConf(MachineConfig *mConf, int clientfd)
{
   network_messages::NetClientRes netMsg;
   netMsg.set_packetcode(network_messages::NetClientRes::PacketType::NetClientRes_PacketType_Founded);
   network_messages::MachineConfig *mMsg = netMsg.add_confs();
   mMsg->set_rowid(mConf->id);
   mMsg->set_haserm(mConf->HasErm);
   mMsg->set_hasdoor(mConf->HasDoor);
   mMsg->set_version(mConf->Version);
   mMsg->set_machineno(mConf->MachineNo);
   mMsg->set_modelcode(mConf->ModelCode);
   mMsg->set_subversion(mConf->SubVersion);
   mMsg->set_needlicense(mConf->NeedLicense);
   mMsg->set_printerunit(mConf->PrinterUnit);
   mMsg->set_zupperlimit(mConf->ZUpperLimit);
   mMsg->set_maxintensity(mConf->MaxIntensity);
   mMsg->set_minintensity(mConf->MinIntensity);

   mMsg->set_maxintensitysensor(mConf->MaxIntensitySensor);
   mMsg->set_minintensitysensor(mConf->MinIntensitySensor);

   mMsg->set_gprojectwidth(mConf->gProjectWidth);
   mMsg->set_buptdownconfig(mConf->BUpTDownConfig);
   mMsg->set_noofmaskpoints(mConf->NoOfMaskPoints);
   mMsg->set_gprojectheight(mConf->gProjectHeight);
   mMsg->set_projectorprotocol(mConf->ProjectorProtocol);

   mMsg->set_hasplunger(mConf->HasPlunger);
   mMsg->set_tdownzhomepos(mConf->TDownZHomePos);
   mMsg->set_vacuumtimer(mConf->vacuumTimer);
   mMsg->set_sensorsetpointvacuum(mConf->SensorSetPointVacuum);
   mMsg->set_sensorsetpoint(mConf->SensorSetPoint);
   mMsg->set_sensorthreshold(mConf->SensorThreshold);
   mMsg->set_xshift(mConf->XShift);
   mMsg->set_yshift(mConf->YShift);

   size_t size = netMsg.ByteSizeLong();
   char *mBuf = new char[size];
   netMsg.SerializeToArray(mBuf, size);
   int resn = writeSocket(clientfd, mBuf, size);
   if (resn == -1){
      spdlog::error("sendMachineConf can not send");
   } else{
      logger->info("sendMachineConf successfully");
   }
   delete mMsg;
   delete[] mBuf;
}

void NetWork::sendAllMachineConf(vector<MachineConfig> *mConfV, int clientfd)
{
   network_messages::NetClientRes netMsg;
   netMsg.set_packetcode(network_messages::NetClientRes::PacketType::NetClientRes_PacketType_Founded);
   for(int i=0; i<mConfV->size(); i++) {
       network_messages::MachineConfig *mMsg = netMsg.add_confs();
       MachineConfig mConf = mConfV->at(i);
       mMsg->set_rowid(mConf.id);
       mMsg->set_haserm(mConf.HasErm);
       mMsg->set_hasdoor(mConf.HasDoor);
       mMsg->set_version(mConf.Version);
       mMsg->set_machineno(mConf.MachineNo);
       mMsg->set_modelcode(mConf.ModelCode);
       mMsg->set_subversion(mConf.SubVersion);
       mMsg->set_needlicense(mConf.NeedLicense);
       mMsg->set_printerunit(mConf.PrinterUnit);
       mMsg->set_zupperlimit(mConf.ZUpperLimit);
       mMsg->set_maxintensity(mConf.MaxIntensity);
       mMsg->set_minintensity(mConf.MinIntensity);

       mMsg->set_maxintensitysensor(mConf.MaxIntensitySensor);
       mMsg->set_minintensitysensor(mConf.MinIntensitySensor);

       mMsg->set_gprojectwidth(mConf.gProjectWidth);
       mMsg->set_buptdownconfig(mConf.BUpTDownConfig);
       mMsg->set_noofmaskpoints(mConf.NoOfMaskPoints);
       mMsg->set_gprojectheight(mConf.gProjectHeight);
       mMsg->set_projectorprotocol(mConf.ProjectorProtocol);

       mMsg->set_hasplunger(mConf.HasPlunger);
       mMsg->set_tdownzhomepos(mConf.TDownZHomePos);
       mMsg->set_vacuumtimer(mConf.vacuumTimer);
       mMsg->set_sensorsetpointvacuum(mConf.SensorSetPointVacuum);
       mMsg->set_sensorsetpoint(mConf.SensorSetPoint);
       mMsg->set_sensorthreshold(mConf.SensorThreshold);
       mMsg->set_xshift(mConf.XShift);
       mMsg->set_yshift(mConf.YShift);

       qDebug()<< "sendall TDownZHomePos ::::::" <<mConf.TDownZHomePos;

   }
   size_t size = netMsg.ByteSizeLong();
   char *mBuf = new char[size];
   netMsg.SerializeToArray(mBuf, size);
   int resn = writeSocket(clientfd, mBuf, size);
   if (resn == -1){
      spdlog::error("sendAllMachineConf can not send");
   } else{
      logger->info("sendAllMachineConf successfully");
   }
   delete[] mBuf;

}

int NetWork::mMVCMDPacket(int clientfd, network_messages::NetServerCommands MVCmd)
{
    logger->info("network_messages::NetServerCommands::PacketType::NetServerCommands_PacketType_ManualMV : {0:d}", MVCmd.imanualmv());
    net_cmds->iManualMV = MVCmd.imanualmv();
    sendDoneMsg(clientfd);
    return 0;
}

void NetWork::sendNotFound(int clientfd)
{
  network_messages::NetClientRes netMsg;
  netMsg.set_packetcode(network_messages::NetClientRes::PacketType::NetClientRes_PacketType_NotFound);
  size_t size = netMsg.ByteSizeLong();
  char *mBuf = new char[size];
  netMsg.SerializeToArray(mBuf, size);
  int resn = writeSocket(clientfd, mBuf, size);
  if (resn == -1){
     spdlog::error("sendNotFound can not send");
  } else{
     logger->info("sendNotFound successfully");
  }
  delete[] mBuf;
}

void NetWork::sendDoneMsg(int clientfd)
{
    network_messages::NetClientRes netMsg;
    netMsg.set_packetcode(network_messages::NetClientRes::PacketType::NetClientRes_PacketType_Done);
    size_t size = netMsg.ByteSizeLong();
    char *mBuf = new char[size];
    netMsg.SerializeToArray(mBuf, size);
    int resn = writeSocket(clientfd, mBuf, size);
    if (resn == -1){
       spdlog::error("sendDoneMsg can not send");
    } else{
       logger->info("sendDoneMsg successfully");
    }
    delete[] mBuf;
}

void NetWork::sendSensorVal(int clientfd,float val)
{
    network_messages::NetClientRes netMsg;
    netMsg.set_packetcode(network_messages::NetClientRes::PacketType::NetClientRes_PacketType_ReadVal);
    netMsg.set_sensorval(val);
    size_t size = netMsg.ByteSizeLong();
    char *mBuf = new char[size];
    netMsg.SerializeToArray(mBuf, size);
    int resn = writeSocket(clientfd, mBuf, size);
    if (resn == -1){
       spdlog::error("can not send SensorVal");
    } else{
       logger->info("SensorVal sent successfully");
    }
    delete[] mBuf;
}

void NetWork::sendErrorMsg(int clientfd, string err)
{
    network_messages::NetClientRes netMsg;
    netMsg.set_packetcode(network_messages::NetClientRes::PacketType::NetClientRes_PacketType_Error);
    netMsg.set_errormesg(err);
    size_t size = netMsg.ByteSizeLong();
    char *mBuf = new char[size];
    netMsg.SerializeToArray(mBuf, size);
    int resn = writeSocket(clientfd, mBuf, size);
    if (resn == -1){
       spdlog::error("sendErrorMsg can not send");
    } else{
       logger->info("sendErrorMsg successfully");
    }
    delete[] mBuf;
}

void NetWork::sendStateMsg(int clientfd, google::protobuf::uint32 state)
{
    network_messages::NetClientRes netMsg;
    netMsg.set_packetcode(state);
    size_t size = netMsg.ByteSizeLong();
    char *mBuf = new char[size];
    netMsg.SerializeToArray(mBuf, size);
    int resn = writeSocket(clientfd, mBuf, size);
    if (resn == -1){
       logger->error("sendStateMsg can not send");
    } else{
       logger->info("sendStateMsg successfully");
    }
    delete[] mBuf;
}

int NetWork::writeSocket(int clientfd, char *mBuf, int size)
{
    int sendCount = 0;
    while (sendCount < size) {
      int resn = write(clientfd, mBuf+sendCount, 1024);
      if(resn < 0) {
          return resn;
      } else {
          sendCount = sendCount + resn;
      }
    }
    return sendCount;
}

void NetWork::sendMd5(int clientfd, QByteArray Md5)
{
    network_messages::NetClientRes Md5Msg;
    Md5Msg.set_packetcode(network_messages::NetClientRes::PacketType::NetClientRes_PacketType_CheckFile);
    Md5Msg.set_md5(Md5.data(),Md5.length());
    size_t size = Md5Msg.ByteSizeLong();
//    qDebug() <<"NetWork : sendMd5 : size message : " << size;
    char *mBuf = new char[size];
    Md5Msg.SerializeToArray(mBuf, size);
    int resn = writeSocket(clientfd, mBuf, size);
    if (resn == -1){
       spdlog::error("sendMd5 can not send");
    } else{
       logger->info("sendMd5 successfully");
    }
    delete[] mBuf;
}
