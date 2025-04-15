QT       += core gui sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    adminwidget.cpp \
    authservice.cpp \
    authwidget.cpp \
    bookingwindow.cpp \
    databaseconnection.cpp \
    main.cpp \
    mainwidget.cpp \
    mainwindow.cpp

HEADERS += \
    adminwidget.h \
    authservice.h \
    authwidget.h \
    bookingwindow.h \
    databaseconnection.h \
    eventtypes.h \
    mainwidget.h \
    mainwindow.h

FORMS += \
    bookingwindow.ui \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
