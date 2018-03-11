TARGET = qstripe_test

QT += testlib qml quick network

SOURCES += \
    TestQStripe.cpp \
    CustomerTests.cpp \
    AddressTests.cpp \
    ShippingInformationTests.cpp \
    CardTests.cpp \
    TokenTests.cpp \
    ErrorTests.cpp \
    StripeTests.cpp

HEADERS += \
    TestQStripe.h \
    CustomerTests.h \
    AddressTests.h \
    ShippingInformationTests.h \
    CardTests.h \
    TokenTests.h \
    ErrorTests.h \
    StripeTests.h

include(../qstripe.pri)

PUBLIC_KEY = $$(STRIPE_PUBLIC_KEY)
SECRET_KEY = $$(STRIPE_SECRET_KEY)

isEmpty(PUBLIC_KEY) {
    message("[QStripe:tests] STRIPE_PUBLIC_KEY environment variable is not set. Cannot run the API request tests.")
}

isEmpty(SECRET_KEY) {
    message("[QStripe:tests] STRIPE_SECRET_KEY environment variable is not set. Cannot run the API request tests.")
}

DEFINES += STRIPE_SECRET_KEY=$$SECRET_KEY
DEFINES += STRIPE_PUBLIC_KEY=$$PUBLIC_KEY
