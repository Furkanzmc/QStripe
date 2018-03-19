#include "QStripe/QStripePlugin.h"
#include <QtQml/qqml.h>
#include <QCoreApplication>
// QStripe
#include "QStripe/Address.h"
#include "QStripe/Card.h"
#include "QStripe/Customer.h"
#include "QStripe/Error.h"
#include "QStripe/PaymentSource.h"
#include "QStripe/ShippingInformation.h"
#include "QStripe/Stripe.h"
#include "QStripe/Token.h"

#include <QDebug>

using namespace QStripe;

QStripePlugin::QStripePlugin(QObject *parent)
    : QQmlExtensionPlugin(parent)
{

}

void QStripePlugin::registerQStripe(const char *uri)
{
    Q_ASSERT(uri == "QStripe");

    qmlRegisterType<Address>(uri, 1, 0, "Address");
    qmlRegisterType<Card>(uri, 1, 0, "Card");
    qmlRegisterType<Customer>(uri, 1, 0, "Customer");

    qmlRegisterType<Error>(uri, 1, 0, "Error");
    qmlRegisterType<PaymentSource>(uri, 1, 0, "PaymentSource");
    qmlRegisterType<ShippingInformation>(uri, 1, 0, "ShippingInformation");

    qmlRegisterType<Stripe>(uri, 1, 0, "Stripe");
    qmlRegisterType<Token>(uri, 1, 0, "Token");
}

void QStripePlugin::registerTypes(const char *uri)
{
    Q_ASSERT(uri == "QStripe");

    registerQStripe(uri);
}

static void startupFunction()
{
    QStripePlugin::registerQStripe();
}

Q_COREAPP_STARTUP_FUNCTION(startupFunction)
