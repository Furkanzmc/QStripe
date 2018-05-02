#include "QStripe/QStripePlugin.h"
// Qt
#include <QtQml/qqml.h>
#include <QCoreApplication>
// QStripe
#include "QStripe/ShippingInformation.h"
#include "QStripe/PaymentSource.h"
#include "QStripe/Customer.h"
#include "QStripe/Address.h"
#include "QStripe/Stripe.h"
#include "QStripe/Error.h"
#include "QStripe/Token.h"
#include "QStripe/Card.h"

QStripePlugin::QStripePlugin(QObject *parent)
    : QQmlExtensionPlugin(parent)
{

}

void QStripePlugin::registerQStripe(const char *uri)
{
    Q_ASSERT(QString(uri) == QString("QStripe"));

    qmlRegisterType<QStripe::Address>(uri, 1, 0, "Address");
    qmlRegisterType<QStripe::Card>(uri, 1, 0, "Card");
    qmlRegisterType<QStripe::Customer>(uri, 1, 0, "Customer");

    qmlRegisterType<QStripe::Error>(uri, 1, 0, "Error");
    qmlRegisterType<QStripe::PaymentSource>(uri, 1, 0, "PaymentSource");
    qmlRegisterType<QStripe::ShippingInformation>(uri, 1, 0, "ShippingInformation");

    qmlRegisterType<QStripe::Stripe>(uri, 1, 0, "Stripe");
    qmlRegisterType<QStripe::Token>(uri, 1, 0, "Token");
}

void QStripePlugin::registerTypes(const char *uri)
{
    Q_ASSERT(QString(uri) == QString("QStripe"));

    registerQStripe(uri);
}

static void startupFunction()
{
    QStripePlugin::registerQStripe();
}

Q_COREAPP_STARTUP_FUNCTION(startupFunction)
