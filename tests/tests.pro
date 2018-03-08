TARGET = qstripe_test

QT += testlib qml quick network

SOURCES += \
    TestQStripe.cpp \
    CustomerTests.cpp \
    AddressTests.cpp \
    ShippingInformationTests.cpp \
    CardTests.cpp

HEADERS += \
    TestQStripe.h \
    CustomerTests.h \
    AddressTests.h \
    ShippingInformationTests.h \
    CardTests.h

include(../qstripe.pri)