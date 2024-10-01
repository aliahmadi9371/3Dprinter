#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQuickStyle>
#include <QQmlContext>
#include <QQuickWindow>
#include <QApplication>
#include <QThread>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QGraphicsPixmapItem>

#include <iostream>
#include <thread>
#include <mutex>
#include "spdlog/sinks/basic_file_sink.h"
#include "spdlog/sinks/stdout_color_sinks.h"
#include "backend.h"
#include "distancmodule.h"
#include "database.h"
#include "loginstance.h"
#include "framehandler.h"
#include "imageitem.h"

#include <QDateTime>
#include <QDir>
#include <QSettings>

using namespace std;
mutex mutexProtection;

#define LOGSIZE 1024 * 10000
#ifdef QT_DEBUG
   #define LOG_TO_FILE true
#else
  #define LOG_TO_FILE true
#endif

void myMessageOutput(QtMsgType type, const QMessageLogContext &context, const QString &msg)
{
   QHash<QtMsgType,QString> msgLevelHash;
   msgLevelHash[QtDebugMsg] = "Debug";
   msgLevelHash[QtWarningMsg] = "Warning";
   msgLevelHash[QtCriticalMsg] = "Critical";
   msgLevelHash[QtFatalMsg] = "Fatal";
   QByteArray localMsg = msg.toLocal8Bit();
   QDateTime time = QDateTime::currentDateTime();
   QString formattedTime = time.toString("yyyy-MM-dd hh:mm:ss:zzz");
   QString fileName =  QString("logs/Log_%1_.txt")
           .arg(QDate::currentDate().toString("yyyy_MM_dd"));
   QByteArray formattedTimeMsg = formattedTime.toLocal8Bit();
   QString logLevelName = msgLevelHash[type];
   QByteArray logLevelMsg = logLevelName.toLocal8Bit();
   QDir dir;
   if (!dir.exists("logs"))
       dir.mkpath("logs");
   QFile outFileCheck(fileName);
   QString NewFileName = fileName;
   int size = outFileCheck.size();
   int counter = 0 ;
   while ( size > LOGSIZE ){
       counter++;
       NewFileName = fileName+QString::number(counter);
       QFile outFileCheck(NewFileName);
       size = outFileCheck.size();
   }
   if (LOG_TO_FILE) {
       QString txt = QString("%1 %2: %3 (%4,%5)").arg(formattedTime, logLevelName, msg,  context.file, QString::number(context.line));
       QFile outFile(NewFileName);
       outFile.open(QIODevice::WriteOnly | QIODevice::Append);
       QTextStream ts(&outFile);
       ts << txt << endl;
       outFile.close();
   } else {
       fprintf(stderr, "%s %s: %s (%s:%u, %s)\n", formattedTimeMsg.constData(), logLevelMsg.constData(), localMsg.constData(), context.file, context.line, context.function);
       fflush(stderr);
   }
   if (type == QtFatalMsg)
       abort();
}


int main(int argc, char *argv[])
{
    QSettings setting("config.ini",QSettings::IniFormat);
    bool bDebug = setting.value("App_Config/debug_to_file",false).toBool();
    qDebug() << "Debug to file: " << bDebug;
    if(bDebug)
        qInstallMessageHandler(myMessageOutput);

    qDebug() << "====================================";
    qDebug() << "main: main: Start Server Application";
    qDebug() << "====================================";


    signal(SIGPIPE, SIG_IGN);
    bool TopDown = true;
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

    QGuiApplication app(argc, argv);
    qmlRegisterType<ImageItem>("myextension", 1, 0, "ImageItem");

    auto console_sink = std::make_shared<spdlog::sinks::stdout_color_sink_mt>();
    auto file_sink = std::make_shared<spdlog::sinks::basic_file_sink_mt>("logs.txt");
    spdlog::logger logger("console and file", { console_sink, file_sink });

    spdlog::flush_on(spdlog::level::info);

//    LogInstance::Instance().info("Version 2.3.1.1");
    logger.info("Version 2.3.1.1");

    DataBase db{"dataBase"};
    BackEnd *backEnd = new BackEnd();
    backEnd->setLogger(&logger);
    backEnd->setMutex(&mutexProtection);
    backEnd->setDataBase(&db);

    NetWork *netWork = new NetWork();
    netWork->setLogger(&logger);
    netWork->setDataBase(&db);

    netWork->matrial_cfg = backEnd->matrial_cfg;
    netWork->motion_cfg = backEnd->motion_cfg;
    netWork->machine_cfg = backEnd->machine_cfg;
    netWork->setBackEndfd(&backEnd->clientsfd);
    netWork->setMutex(&mutexProtection);

//    if(argc>1)
//    {
//        qDebug() << "main: main: main argc > 1";
//        cout<< "main argc>1"<<endl;
//        if ((argv[1][0]=='-')&&(argv[1][1]=='d'))
            backEnd->bDebugMode = 1;
        //printf("Greetings, %d\n",(int)bDebugMode);
//    }

    netWork->netInit(&backEnd->net_cmds);
    thread th(&NetWork::pynetMain, netWork);
    th.detach();


//    DistancModule *dModule = new DistancModule();

//    backEnd->ArduinoPort = dModule->availablePortByVID(9025);
//    dModule->DistanceModulePort = dModule->availablePortByVID(1155);


//    QThread *backendThread = new QThread();
//    backEnd->moveToThread(backendThread);
//    backEnd->start();

    thread th2(&BackEnd::start, backEnd);
    th2.detach();


//    QObject::connect(dModule, SIGNAL(moduleDistanceData(float)), backEnd, SLOT(moduleDistanceData(float)) );
//    if (backEnd->machine_cfg->BUpTDownConfig)
    if(TopDown)
    {

//            thread th3(&DistancModule::readData, dModule);
//            th3.detach();

//            QThread *dModuleThread = new QThread();
//            dModule->moveToThread(dModuleThread);
//            dModule->readData();

//            backEnd->dModuleData = &dModule->distance;
    }



    QQmlApplicationEngine engine;

    engine.rootContext()->setContextProperty(QStringLiteral("BackEnd"), backEnd);


    const QUrl url(QStringLiteral("qrc:/main.qml"));
    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
                     &app, [url](QObject *obj, const QUrl &objUrl) {
        if (!obj && url == objUrl)
            QCoreApplication::exit(-1);
    }, Qt::QueuedConnection);
    engine.load(url);

    app.setOverrideCursor( QCursor( Qt::BlankCursor ));
    return app.exec();
}
