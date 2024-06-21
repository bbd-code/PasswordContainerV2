QT       += core gui sql


greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0





LIBS+= C:/curl-8.4.0_6-win64-mingw/lib/libcurl.a
LIBS+= C:/curl-8.4.0_6-win64-mingw/lib/libcurl.dll.a

INCLUDEPATH+=C:/curl-8.4.0_6-win64-mingw/include



SOURCES += \
    addservicewindow.cpp \
    changeservicewindow.cpp \
    emailsender.cpp \
    inputvalidation.cpp \
    main.cpp \
    mainwindow.cpp \
    serviceform.cpp \
    serviceswindow.cpp \
    settingssaver.cpp \
    sqlrequster.cpp \
    user.cpp

HEADERS += \
    QueryResult.h \
    addservicewindow.h \
    changeservicewindow.h \
    emailsender.h \
    inputvalidation.h \
    mainwindow.h \
    serviceform.h \
    serviceswindow.h \
    settingssaver.h \
    sqlrequster.h \
    user.h

FORMS += \
    addservicewindow.ui \
    changeservicewindow.ui \
    mainwindow.ui \
    serviceform.ui \
    serviceswindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    res.qrc \
    res2.qrc



