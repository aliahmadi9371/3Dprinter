QT += quick
QT += qml
QT += opengl
QT += quickcontrols2
QT += network
QT += svg


#QT += charts
#QT += serialport

CONFIG += c++11
CONFIG += disable-desktop
static {
    QT += svg
    QTPLUGIN += qtvirtualkeyboardplugin
}
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
#        ImageView.cpp \
        assistant.cpp \
        backend.cpp \
    fileitemslist.cpp \
    fileitemsmodel.cpp \
        joblist.cpp \
        jobmodel.cpp \
    jsonstoring.cpp \
        machineconfiglist.cpp \
        machineconfigmodel.cpp \
        main.cpp \
        materialconfiglist.cpp \
        materialconfigmodel.cpp \
        message.pb.cc \
        motionconfiglist.cpp \
        motionconfigmodel.cpp \
#        slcread.cpp \
    sendfile.cpp \
        uimessages.cpp

RESOURCES += qml.qrc

# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH =

# Additional import path used to resolve QML modules just for Qt Quick Designer
QML_DESIGNER_IMPORT_PATH =

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

HEADERS += \
#    ImageView.h \
    FileItem.h \
    GeneralData.h \
    Job.h \
    assistant.h \
    backend.h \
    fileitemslist.h \
    fileitemsmodel.h \
    joblist.h \
    jobmodel.h \
#    lib/png.h \
    jsonstoring.h \
    machineconfig.h \
    machineconfiglist.h \
    machineconfigmodel.h \
    materialconfig.h \
    materialconfiglist.h \
    materialconfigmodel.h \
    message.pb.h \
    motionconfig.h \
    motionconfiglist.h \
    motionconfigmodel.h \
#    sdlg.h \
#    slcread.h \
    sendfile.h \
    uimessages.h


unix:!macx: LIBS += -L"/usr/local/lib/" -lprotobuf

#unix:!macx: LIBS += -L$$PWD/lib/ -lSDLimage

INCLUDEPATH += $$PWD/.
DEPENDPATH += $$PWD/.

#unix:!macx: PRE_TARGETDEPS += $$PWD/lib/libSDLimage.a

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../vcpkg/installed/x64-windows/lib/ -llibprotobuf
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../vcpkg/installed/x64-windows/lib/ -llibprotobufd

INCLUDEPATH += $$PWD/../vcpkg/installed/x64-windows/include
DEPENDPATH += $$PWD/../vcpkg/installed/x64-windows/include


win32:RC_ICONS += 3DDreams.ico


