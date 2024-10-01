#include <QGuiApplication>
#include <QApplication>
#include <QQmlApplicationEngine>
#include <QQuickStyle>
#include <QQmlContext>
#include <QQuickWindow>
#include <QThread>
#include "backend.h"
#include "sendfile.h"
#include "machineconfigmodel.h"
#include "materialconfigmodel.h"
#include "motionconfigmodel.h"
#include "jobmodel.h"
#include "uimessages.h"
#include "fileitemsmodel.h"

int main(int argc, char *argv[])
{
    qputenv("QT_IM_MODULE", QByteArray("freevirtualkeyboard"));
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QString machineNumber = "PD67001019821004";
    QApplication app(argc, argv);
    app.setOrganizationName("Karnojam");
    app.setOrganizationDomain("Karnojam");
    QQmlApplicationEngine engine;
    QQuickStyle::setStyle("Material");

    UIMessages *uiMessages = new UIMessages();
    BackEnd *backend = new BackEnd();
    backend->setUIMessages(uiMessages);
    MachineConfigModel *machineConfigModel = new MachineConfigModel();
    machineConfigModel->setUIMessages(uiMessages);
    MaterialConfigModel *materialConfigModel = new MaterialConfigModel();
    materialConfigModel->setUIMessages(uiMessages);
    MotionConfigModel *motionConfigModel = new MotionConfigModel();
    motionConfigModel->setUIMessages(uiMessages);
    JobModel *jobModel = new JobModel();
    jobModel->setUIMessages(uiMessages);
    backend->materialConfigModel = materialConfigModel;
    backend->motionConfigModel = motionConfigModel;
    backend->jobModel = jobModel;
    backend->machineConfigModel = machineConfigModel;


    backend->lcd = false;
    backend->topDown = true;
    backend->bShowConfig = true;


    
    if (backend->lcd)
    {
//        app.setOverrideCursor(QCursor(Qt::BlankCursor));
    }

    FileItemsModel *fileItemModel = new FileItemsModel();

    QThread *uploadFileTHread = new QThread();
    SendFile *sendFile = new SendFile();
    backend->sendFile = sendFile;
    sendFile->moveToThread(uploadFileTHread);
    uploadFileTHread->start();


//    QObject::connect(fileItemModel, SIGNAL(fileSelected(QString)), &backend, SLOT(selectedFile(QString)));
    QObject::connect(sendFile, SIGNAL(sendFileCompleted()), jobModel, SLOT(sendFileDone()) );
    QObject::connect(sendFile, SIGNAL(sendFileError(QString)), jobModel, SLOT(sendFileError(QString)) );
    QObject::connect(jobModel, SIGNAL(sendFile(QString)), sendFile, SLOT(sendFile(QString)) );

    QObject::connect(sendFile, SIGNAL(SendPrecentage(int)), jobModel, SLOT(GetPrecentage(int)) );
    QObject::connect(sendFile, SIGNAL(SendTrueFile(bool)), jobModel, SLOT(onSendTrueFile(bool)) );

//    backend->machineConfigModel = machineConfigModel;
    engine.rootContext()->setContextProperty(QStringLiteral("FileItemsModel"), fileItemModel);
    engine.rootContext()->setContextProperty(QStringLiteral("BackEnd"), backend);
    engine.rootContext()->setContextProperty(QStringLiteral("MaterialConfigModel"), materialConfigModel);
    engine.rootContext()->setContextProperty(QStringLiteral("MotionConfigModel"), motionConfigModel);
    engine.rootContext()->setContextProperty(QStringLiteral("MachineConfigModel"), machineConfigModel);
    engine.rootContext()->setContextProperty(QStringLiteral("JobModel"), jobModel);
    engine.rootContext()->setContextProperty(QStringLiteral("UIMessages"), uiMessages);
//    if(backend->connectToThis("192.168.1.134", "7002")) {
//    if(backend->connectToThis("127.0.0.1", "7002")) {
//        qDebug()<< "connect to server successfully";
//    } else {
//        qDebug()<< "Could not connect to server";
//    }

    const QUrl url(QStringLiteral("qrc:/main.qml"));

    QObject::connect(&engine, &QQmlApplicationEngine::quit, &QGuiApplication::quit);

    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
                     &app, [url](QObject *obj, const QUrl &objUrl) {
        if (!obj && url == objUrl)
            QCoreApplication::exit(-1);
    }, Qt::QueuedConnection);
    engine.load(url);

    return app.exec();
}
