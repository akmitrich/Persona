QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    creationregistry.cpp \
    linkingcontext.cpp \
    main.cpp \
    mainwindow.cpp \
    pcontroller.cpp \
    persona.cpp \
    personalistmodel.cpp \
    prep.cpp \
    prepwidget.cpp \
    selectpersonadialog.cpp \
    selectpersonawidget.cpp \
    smanager.cpp \
    sobject.cpp

HEADERS += \
    creationregistry.h \
    linkingcontext.h \
    mainwindow.h \
    pcontroller.h \
    persona.h \
    personalistmodel.h \
    prep.h \
    prepwidget.h \
    sdecl.h \
    selectpersonadialog.h \
    selectpersonawidget.h \
    smanager.h \
    sobject.h

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
