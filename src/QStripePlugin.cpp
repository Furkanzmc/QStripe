#include "QStripe/QStripePlugin.h"
// Qt
#include <QtQml/qqml.h>
#include <QCoreApplication>
// QStripe
#include "QStripe/Card.h"
#include "QStripe/Error.h"
#include "QStripe/Token.h"
#include "QStripe/Stripe.h"
#include "QStripe/Address.h"
#include "QStripe/Customer.h"
#include "QStripe/PaymentSource.h"
#include "QStripe/ShippingInformation.h"

QStripePlugin::QStripePlugin(QObject *parent)
    : QQmlExtensionPlugin(parent)
{

}

void QStripePlugin::registerQStripe(const char *uri)
{
    Q_ASSERT(QString(uri) == QString("QStripe"));

    qmlRegisterType<QStripe::Address>(uri, QSTRIPE_VER_MAJOR, QSTRIPE_VER_MINOR, "Address");
    qmlRegisterType<QStripe::Card>(uri, QSTRIPE_VER_MAJOR, QSTRIPE_VER_MINOR, "Card");
    qmlRegisterType<QStripe::Customer>(uri, QSTRIPE_VER_MAJOR, QSTRIPE_VER_MINOR, "Customer");

    qmlRegisterType<QStripe::Error>(uri, QSTRIPE_VER_MAJOR, QSTRIPE_VER_MINOR, "Error");
    qmlRegisterType<QStripe::PaymentSource>(uri, QSTRIPE_VER_MAJOR, QSTRIPE_VER_MINOR, "PaymentSource");
    qmlRegisterType<QStripe::ShippingInformation>(uri, QSTRIPE_VER_MAJOR, QSTRIPE_VER_MINOR, "ShippingInformation");

    qmlRegisterType<QStripe::Stripe>(uri, QSTRIPE_VER_MAJOR, QSTRIPE_VER_MINOR, "Stripe");
    qmlRegisterType<QStripe::Token>(uri, QSTRIPE_VER_MAJOR, QSTRIPE_VER_MINOR, "Token");
}

void QStripePlugin::registerTypes(const char *uri)
{
    registerQStripe(uri);
}

#if QSTRIPE_AUTO_REGISTER
static void startupFunction()
{
    QStripePlugin::registerQStripe();
}

Q_COREAPP_STARTUP_FUNCTION(startupFunction)
#endif // QSTRIPE_AUTO_REGISTER
