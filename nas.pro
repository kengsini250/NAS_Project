QT       += core gui network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    FileFormat.cpp \
    http/http.cpp \
    http/httpdownload.cpp \
    main.cpp \
    mainwindow.cpp \
    newuser/newuser.cpp \
    presenter.cpp \
    setting/setting.cpp \
    ssh/SSH.cpp \
    ssh/shell.cpp

HEADERS += \
    FileFormat.h \
    http/HTTP.h \
    http/httpdownload.h \
    mainwindow.h \
    newuser/newuser.h \
    presenter.h \
    setting/setting.h \
    ssh/SSH.h \
    ssh/shell.h

FORMS += \
    mainwindow.ui \
    newuser/newuser.ui \
    setting/setting.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    pic.qrc
