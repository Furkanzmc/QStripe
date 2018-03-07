TARGET = qstripe_test

QT += testlib qml quick network

SOURCES += \
    TestQStripe.cpp \
    CustomerTests.cpp \
    AddressTests.cpp \
    ShippingInformationTests.cpp

HEADERS += \
    TestQStripe.h \
    CustomerTests.h \
    AddressTests.h \
    ShippingInformationTests.h

include(../qstripe.pri)
