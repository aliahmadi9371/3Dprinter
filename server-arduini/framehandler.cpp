#include "framehandler.h"
#include <QDebug>

FrameHandler::FrameHandler(QObject *parent) : QObject(parent)
{
     LoadConfigs();
     SetPixelSize();
}

int FrameHandler::LoadConfigs()
{
//    cout<< "load configs "<<endl;
    qDebug() << "FrameHandler: LoadConfigs: load configs";

    int retval = 0;

    FILE *file = fopen("Configs/machineconfig.bin","rb");
    if (file == NULL)
    {

//        cerr << "error load machine config"<<endl;
        qDebug() << "error->FrameHandler: LoadConfigs: error load machine config";

        retval = 1;
        return retval;
    }
    fread(machine_cfg,1,sizeof(MachineConfigFile2),file);
    fclose(file);
    return 0;
}

void FrameHandler::SetPixelSize()
{
    if (machine_cfg->ModelCode == 2150)
    {
//        cout<<"Pixel Size is 54"<<endl;
        qDebug() << "FrameHandler: SetPixelSize: pixel Size is 54";
        fPixelSize = 54.0*0.001;
    }
    else if (machine_cfg->ModelCode == 1075)
    {

//        cout<<"Pixel Size is 75"<<endl;
        qDebug() << "FrameHandler: SetPixelSize: pixel Size is 75";

        fPixelSize = 75.0*0.001;
    }
    else if (machine_cfg->ModelCode == 2162)
    {

//        cout<<"Pixel Size is 62.5"<<endl;
        qDebug() << "FrameHandler: SetPixelSize: pixel Size is 62.5";

        fPixelSize = 62.5*0.001;
    }
    else if (machine_cfg->ModelCode == 21100)
    {

//        cout<<"Pixel Size is 100"<<endl;
        qDebug() << "FrameHandler: SetPixelSize: pixel Size is 100";

        fPixelSize = 100*0.001;
    }
    else if (machine_cfg->ModelCode == 1280)
    {

//        cout<<"Pixel Size is 80"<<endl;
        qDebug() << "FrameHandler: SetPixelSize: pixel Size is 80";

        fPixelSize = 80.0*0.001;
    }
}

int FrameHandler::ExportSVGToMem(__Job3D *jobinfo, int iSlice, int ImageCX, int ImageCY, float fPixelSize, unsigned int BkgColor, char *OutBuffer, float X_Shift, float Y_Shift)
{
    int aa = 0;
    int jj = 0;
    int size = 0;
    int zz = 0;
    while (aa < MAXPOINTS)
    {
        if (jobinfo->points[aa].Slice == iSlice)
            break;
        aa++;
    }

    zz = sprintf(OutBuffer+size, "<svg width='%d' height='%d'>\r\n", ImageCX, ImageCY);

    size += zz;
    zz = sprintf(OutBuffer+size, "<rect x='0' y='0' width='%d' height='%d' style='fill:#%x;stroke-width:0;' />\r\n", ImageCX, ImageCY, BkgColor);
    size += zz;
    zz = sprintf(OutBuffer+size, "<path d='");
    size += zz;


    jj = 0;
    while (jobinfo->points[aa].Slice == iSlice)
    {
        if (jobinfo->points[aa].VertNum == 0) {
            zz = sprintf(OutBuffer + size, "M%.3f %.3f ", (jobinfo->points[aa].fX*(1.0 / fPixelSize))+X_Shift, (jobinfo->points[aa].fY*(1.0 / fPixelSize))+Y_Shift);
        } else {
            zz = sprintf(OutBuffer + size, "L%.3f %.3f ", (jobinfo->points[aa].fX*(1.0 / fPixelSize))+X_Shift, (jobinfo->points[aa].fY*(1.0 / fPixelSize))+Y_Shift);
        }
        size += zz;
        aa++;
    }


    zz = sprintf(OutBuffer + size, "Z' fill='white' />\r\n");
    size += zz;


    zz = sprintf(OutBuffer + size, "</svg>\r\n");

    size += zz;

    return size;
}

int FrameHandler::ExportBlackSVGToMem(int ImageCX, int ImageCY, unsigned int BkgColor, char *OutBuffer)
{
    int size = 0;
    int zz = 0;


    zz = sprintf(OutBuffer+size, "<svg width='%d' height='%d'>\r\n", ImageCX, ImageCY);

    size += zz;
    zz = sprintf(OutBuffer+size, "<rect x='0' y='0' width='%d' height='%d' style='fill:#%x;stroke-width:0;' />\r\n", ImageCX, ImageCY, BkgColor);
    size += zz;

    zz = sprintf(OutBuffer + size, "</svg>\r\n");
    size += zz;

    return size;
}

void FrameHandler::ChangeFrame(int layerno, bool ShiftImage, __Job3D *jobData, char *tmpImage)
{
    if(jobData==NULL) {

//        cerr<<"ChangeFrame jobData is null, layerno:"<< layerno<<endl;
        qDebug() << "error->FrameHandler: ChangeFrame: ChangeFrame jobData is null , layerno: " << layerno;

        return;
    }
    int X_Shift = 0;
    int Y_Shift = 0;

    if (layerno <0)
    {

//        cout<<"Change frame render black"<<endl;
        qDebug() << "FrameHandler: ChangeFrame: Change frame render black";

        if (machine_cfg->HasErm){
            emit changeImageViewErm("images/black.png", hasermToggle);
            hasermToggle = !hasermToggle;
        } else {
            emit changeImageView("images/black.png");
        }
        emit frameChanged(1);

//        cout <<" ChangeFrame clear screen"<<endl;
        qDebug() << "FrameHandler: ChangeFrame: ChangeFrame clear screen";

    }
    else
    {
        if (ShiftImage)
        {
            if (machine_cfg->ModelCode == 1675){
                X_Shift = 0.5;
                Y_Shift = -0.5;
                // X_Shift = 500;
                // Y_Shift = -500;
            }else{
//                X_Shift = -0.5;
//                Y_Shift = 0.5;
                X_Shift = -500;
                Y_Shift = 500;
            }
        }
         int  jobframelen = ExportSVGToMem(jobData, layerno+2, machine_cfg->gProjectWidth, machine_cfg->gProjectHeight, fPixelSize, 0x000000, tmpImage, X_Shift, Y_Shift); // 144.0 / (float)gProjectWidth

//         cout<<" ChangeFrame jobframelen:" << jobframelen<<endl;
         qDebug() << "FrameHandler: ChangeFrame: ChangeFrame jobframelen: " << jobframelen;


//         cout<<"Change frame render image"<<endl;
         qDebug() << "FrameHandler: ChangeFrame: Change frame render image";

         if (machine_cfg->HasErm){
             string temp = "data:image/svg+xml;utf8,"+ string(tmpImage);
//             emit changeImageViewErm("file:/"+exePath+"/printImage.svg", hasermToggle);
             emit changeImageViewErm(QString::fromStdString(temp), hasermToggle);

             hasermToggle = !hasermToggle;
         } else {
             string temp = "data:image/svg+xml;utf8,"+ string(tmpImage);
             emit changeImageView(QString::fromStdString(temp));
         }
//         // Save, image format based on file extension
//         image.save("./svg-logo-h.png");
         emit frameChanged(jobframelen);
//        sendPrintProgress(tmpImageBuf, jobframelen, layerno, TotalLayers);

//        cout<<"*************************** isPrint:"<<endl;
         qDebug() << "FrameHandler: ChangeFrame: *************************** isPrint";

    }
}
