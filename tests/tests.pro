TARGET = qstripe_test

QT += testlib qml quick network

USE_DEFAULT_STYLE = 1

include(../qstripe.pri)

SOURCES += \
    TestQStripe.cpp

HEADERS += \
    TestQStripe.h
