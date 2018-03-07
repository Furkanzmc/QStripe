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
    $$PWD/include/QStripe/NetworkUtils.h

SOURCES += \
    $$PWD/src/Token.cpp \
    $$PWD/src/Card.cpp \
    $$PWD/src/Customer.cpp \
    $$PWD/src/Utils.cpp \
    $$PWD/src/Stripe.cpp \
    $$PWD/src/NetworkUtils.cpp

OTHER_FILES += $$PWD/README.md
