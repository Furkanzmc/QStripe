!contains(CONFIG, c++11) {
    CONFIG += c++11
}

!contains(QT, network) {
    QT += network
}

INCLUDEPATH += $$PWD/include

HEADERS += \
    $$PWD/include/QStripe/Token.h \
    $$PWD/include/QStripe/Card.h \
    $$PWD/include/QStripe/Customer.h \
    $$PWD/include/QStripe/Utils.h \
    $$PWD/include/QStripe/Stripe.h \
    $$PWD/include/QStripe/NetworkUtils.h \
    $$PWD/include/QStripe/Address.h \
    $$PWD/include/QStripe/ShippingInformation.h \
    $$PWD/include/QStripe/PaymentSource.h \
    $$PWD/include/QStripe/Error.h

SOURCES += \
    $$PWD/src/Token.cpp \
    $$PWD/src/Card.cpp \
    $$PWD/src/Customer.cpp \
    $$PWD/src/Utils.cpp \
    $$PWD/src/Stripe.cpp \
    $$PWD/src/NetworkUtils.cpp \
    $$PWD/src/Address.cpp \
    $$PWD/src/ShippingInformation.cpp \
    $$PWD/src/PaymentSource.cpp \
    $$PWD/src/Error.cpp

OTHER_FILES += $$PWD/README.md
