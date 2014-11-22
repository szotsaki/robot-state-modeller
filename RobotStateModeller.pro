#-------------------------------------------------
#
# Project created by QtCreator 2014-11-22T14:10:47
#
#-------------------------------------------------

QT       += core gui widgets network printsupport

QMAKE_CXXFLAGS += -std=c++11

TARGET = RobotStateModeller
TEMPLATE = app


SOURCES += main.cpp\
    DataCommandOnly.cpp \
    DataContainer.cpp \
    Monitor.cpp \
    Network.cpp \
    MainWindow.cpp \
    Data.cpp \
    Command.cpp \
    DataStateOnly.cpp \
    State.cpp \
    QCustomPlot.cpp

HEADERS  += \
    Command.h \
    Data.h \
    DataCommandOnly.h \
    DataContainer.h \
    DataInterface.h \
    DataStateOnly.h \
    Monitor.h \
    Network.h \
    progress_t.h \
    State.h \
    MainWindow.h \
    dataID_t.h \
    QCustomPlot.h

FORMS    += \
    MainWindow.ui
