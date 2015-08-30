TEMPLATE = app
CONFIG += console
CONFIG += c++11
CONFIG -= app_bundle
CONFIG -= qt

LIBS += -lboost_system -lboost_program_options
SOURCES += \
    telnetsession.cpp \
    telnetserver.cpp \
    opoznienia.cpp

HEADERS += \
    telnetsession.h \
    telnetserver.h

