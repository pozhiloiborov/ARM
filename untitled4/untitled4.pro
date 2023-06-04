QT       += core gui printsupport
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    completed.cpp \
    currentzakaz.cpp \
    main.cpp \
    mainwindow.cpp \
    mainww.cpp \
    qcustomplot.cpp \
    zakazi.cpp

HEADERS += \
    completed.h \
    currentzakaz.h \
    mainwindow.h \
    mainww.h \
    qcustomplot.h \
    zakaz.h \
    zakazi.h

FORMS += \
    completed.ui \
    currentzakaz.ui \
    mainwindow.ui \
    mainww.ui \
    zakazi.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    resources.qrc
