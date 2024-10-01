QT += quick
QT += serialport
QT += sql
QT += qml
QT += opengl
QT += quickcontrols2
QT += network
QT += svg

CONFIG += thread

LIBS += -ldl

CONFIG += c++11

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Refer to the documentation for the
# deprecated API to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
        Arduino.cpp \
        ProjectorCOMM.cpp \
        ProjectorRS232.cpp \
        assistant.cpp \
        backend.cpp \
        database.cpp \
        distancmodule.cpp \
        framehandler.cpp \
        imageitem.cpp \
        jobschema.cpp \
        jsonstoring.cpp \
        lib/sqlite3.c \
        loginstance.cpp \
        machineconfigschema.cpp \
        main.cpp \
        materialschema.cpp \
        message.pb.cc \
        motionschema.cpp \
        movementboard.cpp \
        myutility.cpp \
        pyNet.cpp \
        schema.cpp \
        serialport.cpp \
        slcread.cpp

#        Configs/confsave.cpp

HEADERS += \
    Arduino.h \
    Configs/Configs.h \
    CyUSBSerial.h \
    GeneralData.h \
    Job.h \
    ProjectorCOMM.h \
    ProjectorRS232.h \
    assistant.h \
    backend.h \
    database.h \
    distancmodule.h \
    framehandler.h \
    imageitem.h \
    jobschema.h \
    jsonstoring.h \
    lib/sqlite3.h \
    lib/sqlite3ext.h \
    loginstance.h \
    machineconfig.h \
    machineconfigschema.h \
    materialconfig.h \
    materialschema.h \
    message.pb.h \
    motionconfig.h \
    motionschema.h \
    movementboard.h \
    myutility.h \
    pyNet.h \
    schema.h \
    serialport.h \
    slcread.h



#LIBS += $$PWD/lib/mode.o
#LIBS += -L"/usr/include/drm" -ldrm

LIBS += -L"/usr/local/lib/libhidapi-libusb" -lhidapi-libusb
LIBS += -L"/usr/local/lib/" -lcyusbserial
LIBS += -L"/usr/local/lib/" -lprotobuf
#LIBS += -L$$PWD/lib/ -lSDLimage
#LIBS += -L"/usr/local/lib/" -lSDL2



DISTFILES += \
    lib/libspdlog.a


RESOURCES += qml.qrc

# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH =

# Additional import path used to resolve QML modules just for Qt Quick Designer
QML_DESIGNER_IMPORT_PATH =

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
