QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    main.cpp \
    mainwindow.cpp

HEADERS += \
    mainwindow.h

FORMS += \
    mainwindow.ui

INCLUDEPATH += /usr/local/include
LIBS += /usr/local/lib/libMsnhnet.so\
/usr/lib/loongarch64-linux-gnu/libopencv_core.so\
/usr/lib/loongarch64-linux-gnu/libopencv_imgproc.so\
/usr/lib/loongarch64-linux-gnu/libopencv_imgcodecs.so\
/usr/lib/loongarch64-linux-gnu/libopencv_highgui.so

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
