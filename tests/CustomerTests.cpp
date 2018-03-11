#include "CustomerTests.h"
#include <QtTest/QtTest>
#include <QSignalSpy>
// QStripe
#include "QStripe/Customer.h"
#include "QStripe/Stripe.h"
#include "QStripe/Utils.h"

using namespace QStripe;

#define STRINGIFY_(x) #x
#define STRINGIFY(x) STRINGIFY_(x)

CustomerTests::CustomerTests(QObject *parent)
    : QObject(parent)
    , m_CustomerID("")
    , m_CustomerIDToDelete("")
{

}

QString CustomerTests::getCustomerID() const
{
    return m_CustomerID;
}

QVariantMap CustomerTests::getAddressData() const
{
    QVariantMap addressData;
    addressData[Address::FIELD_COUNTRY] = "Canada";
    addressData[Address::FIELD_STATE] = "Ontario";
    addressData[Address::FIELD_CITY] = "Toronto";

    addressData[Address::FIELD_LINE_1] = "Line one.";
    addressData[Address::FIELD_LINE_2] = "Line two.";
    addressData[Address::FIELD_POSTAL_CODE] = "M9S U7Y";

    addressData[Address::FIELD_ZIP_CHECK] = "unknown";

    return addressData;
}

QVariantMap CustomerTests::getShippingInformationData() const
{
    const QVariantMap addressData = getAddressData();

    QVariantMap data;
    data[ShippingInformation::FIELD_NAME] = "Furkan Uzumcu";
    data[ShippingInformation::FIELD_PHONE] = "+11234123123";
    data[ShippingInformation::FIELD_ADDRESS] = addressData;

    return data;
}

QVariantMap CustomerTests::getData() const
{
    QVariantMap data;
    data[Customer::FIELD_ID] = "customer_id";
    data[Customer::FIELD_CURRENCY] = "cad";
    data[Customer::FIELD_DEFAULT_SOURCE] = "source";
    data[Customer::FIELD_SHIPPING] = getShippingInformationData();

    data[Customer::FIELD_EMAIL] = "foo@bar.com";
    data[Customer::FIELD_DESCRIPTION] = "Here be descriton.";

    QVariantMap meta;
    meta["meta"] = "data";
    meta["first_name"] = "Furkan";
    meta["last_name"] = "Uzumcu";
    data[Customer::FIELD_METADATA] = meta;

    return data;
}

void CustomerTests::testSignals()
{
    Customer customer;

    QSignalSpy spyDefaultSource(&customer, &Customer::defaultSourceChanged);
    customer.setDefaultSource("default_source");
    QCOMPARE(spyDefaultSource.count(), 1);

    QSignalSpy spyEmail(&customer, &Customer::emailChanged);
    customer.setEmail("foo@bar.com");
    QCOMPARE(spyEmail.count(), 1);

    QSignalSpy spyDescription(&customer, &Customer::descriptionChanged);
    customer.setDescription("Foo bar desc");
    QCOMPARE(spyDescription.count(), 1);

    QSignalSpy spyCurrency(&customer, &Customer::currencyChanged);
    customer.setCurrency("cad");
    QCOMPARE(spyCurrency.count(), 1);

    QSignalSpy spyMetadata(&customer, &Customer::metadataChanged);
    QVariantMap metadata;
    metadata["foo"] = "bar";
    customer.setMetadata(metadata);
    QCOMPARE(spyMetadata.count(), 1);

    ShippingInformation shipping;
    shipping.setName("Furkan Uzumcu");

    QSignalSpy spyShipping(&customer, &Customer::shippingInformationChanged);
    customer.setShippingInformation(&shipping);
    QCOMPARE(spyShipping.count(), 1);
}

void CustomerTests::testFromJson()
{
    const QVariantMap data = getData();
    const QVariantMap shippingData = data[Customer::FIELD_SHIPPING].toMap();

    const Customer *customer = Customer::fromJson(data);

    QCOMPARE(customer->currency(), data[Customer::FIELD_CURRENCY].toString());
    QCOMPARE(customer->defaultSource(), data[Customer::FIELD_DEFAULT_SOURCE].toString());
    QCOMPARE(customer->shippingInformation()->json(), shippingData);

    QCOMPARE(customer->email(), data[Customer::FIELD_EMAIL].toString());
    QCOMPARE(customer->description(), data[Customer::FIELD_DESCRIPTION].toString());
    QCOMPARE(customer->metadata(), data[Customer::FIELD_METADATA].toMap());

    QCOMPARE(customer->customerID(), data[Customer::FIELD_ID].toString());
}

void CustomerTests::testJsonStr()
{
    QVariantMap data = getData();
    const Customer *customer = Customer::fromString(Utils::toJsonString(data));

    const QVariantMap metadata = customer->metadata();
    for (auto it = metadata.constBegin(); it != metadata.constEnd(); it++) {
        const QString key = Customer::FIELD_METADATA + "[" + it.key() + "]";
        const QVariant &value = it.value();

        if (value.type() == QVariant::String) {
            data[key] = value.toString();
        }
        else if (value.type() == QVariant::Int) {
            data[key] = value.toInt();
        }
        else if (value.type() == QVariant::Int) {
            data[key] = value.toInt();
        }
        else if (value.type() == QVariant::Map) {
            qWarning() << "Do not put Map in metadata.";
        }
    }

    data.remove(Customer::FIELD_METADATA);

    QCOMPARE(customer->jsonString(), Utils::toJsonString(data));
}

void CustomerTests::testJson()
{
    QVariantMap data = getData();
    Customer *customer = Customer::fromJson(data);

    const QVariantMap metadata = customer->metadata();
    for (auto it = metadata.constBegin(); it != metadata.constEnd(); it++) {
        const QString key = Customer::FIELD_METADATA + "[" + it.key() + "]";
        const QVariant &value = it.value();

        if (value.type() == QVariant::String) {
            data[key] = value.toString();
        }
        else if (value.type() == QVariant::Int) {
            data[key] = value.toInt();
        }
        else if (value.type() == QVariant::Int) {
            data[key] = value.toInt();
        }
        else if (value.type() == QVariant::Map) {
            qWarning() << "Do not put Map in metadata.";
        }
    }

    data.remove(Customer::FIELD_METADATA);
    QCOMPARE(customer->json(), data);

    data.remove(Customer::FIELD_CURRENCY);
    customer->setCurrency("");
    QCOMPARE(customer->json(true), data);
}

void CustomerTests::testSet()
{
    Customer c1;
    Customer c2;

    c1.setDefaultSource("The Air That I Breathe");
    c1.setEmail("the@hollies.com");
    c2.set(&c1);


    QCOMPARE(c1.description(), c2.description());
    QCOMPARE(c1.email(), c2.email());
}

void CustomerTests::testCreateCustomerErrors()
{
    QVariantMap data = getData();
    Customer *customer = Customer::fromJson(data);

    QCOMPARE(customer->create(), false);

    customer->deleteLater();
    data.remove(Customer::FIELD_ID);
    customer = Customer::fromJson(data);
    QCOMPARE(customer->create(), true);

    QSignalSpy spyError(customer, &Customer::errorOccurred);
    QCOMPARE(spyError.wait(), true);

    const Error *error = customer->lastError();
    QCOMPARE(error->type(), Error::ErrorInvalidRequest);
    QCOMPARE(error->httpStatus(), NetworkUtils::HTTP_401);

    customer->deleteLater();
    data.remove(Customer::FIELD_ID);
    customer = Customer::fromJson(data);

    Stripe::setPublishableKey(STRINGIFY(STRIPE_PUBLIC_KEY));
    Stripe::setSecretKey(STRINGIFY(STRIPE_SECRET_KEY));

    QSignalSpy spyCreate(customer, &Customer::errorOccurred);
    QCOMPARE(customer->create(), true);
    QCOMPARE(spyCreate.wait(), true);
    error = customer->lastError();
    QCOMPARE(error->param(), "source");
}

void CustomerTests::testCreateCustomer()
{
    QVariantMap data = getData();
    data.remove(Customer::FIELD_ID);
    data.remove(Customer::FIELD_DEFAULT_SOURCE);
    Customer *customer = Customer::fromJson(data);

    Stripe::setPublishableKey(STRINGIFY(STRIPE_PUBLIC_KEY));
    Stripe::setSecretKey(STRINGIFY(STRIPE_SECRET_KEY));

    QSignalSpy spyCreate(customer, &Customer::created);
    QCOMPARE(customer->create(), true);
    QVERIFY2(spyCreate.wait() == true, customer->lastError()->message().toStdString().c_str());
    QVERIFY(customer->customerID().length() > 0);

    m_CustomerID = customer->customerID();

    data = getData();
    data.remove(Customer::FIELD_ID);
    data.remove(Customer::FIELD_DEFAULT_SOURCE);
    data[Customer::FIELD_EMAIL] = "bar@foo.com";
    customer = Customer::fromJson(data);

    QSignalSpy spyCreateDelete(customer, &Customer::created);
    QCOMPARE(customer->create(), true);
    QVERIFY2(spyCreateDelete.wait() == true, customer->lastError()->message().toStdString().c_str());
    QVERIFY(customer->customerID().length() > 0);

    m_CustomerIDToDelete = customer->customerID();
}

void CustomerTests::testUpdateCustomerErrors()
{
    QVERIFY2(m_CustomerID.length() > 0, "Customer ID doesn't exist. Cannot continue update test.");
    if (m_CustomerID.length() > 0) {
        QVariantMap data = getData();
        data.remove(Customer::FIELD_ID);
        Customer *customer = Customer::fromJson(data);

        QCOMPARE(customer->update(), false);

        customer->deleteLater();
    }
}

void CustomerTests::testUpdateCustomer()
{
    QVERIFY2(m_CustomerID.length() > 0, "Customer ID doesn't exist. Cannot continue update test.");
    if (m_CustomerID.length() > 0) {
        QVariantMap data = getData();
        data[Customer::FIELD_ID] = m_CustomerID;
        data.remove(Customer::FIELD_DEFAULT_SOURCE);

        Customer *customer = Customer::fromJson(data);
        customer->setDescription("Hey description!");
        QVariantMap metadata = customer->metadata();
        metadata["simple"] = "man";
        customer->setMetadata(metadata);
        QCOMPARE(customer->update(), true);

        QSignalSpy spyUpdated(customer, &Customer::updated);
        QVERIFY2(spyUpdated.wait() == true, customer->lastError()->message().toStdString().c_str());
    }
}

void CustomerTests::testDeleteCustomerErrors()
{
    QVERIFY2(m_CustomerIDToDelete.length() > 0, "m_CustomerIDToDelete doesn't exist. Cannot continue delete test.");
    if (m_CustomerIDToDelete.length() > 0) {
        Customer customer;
        QCOMPARE(customer.deleteCustomer(), false);
    }
}

void CustomerTests::testDeleteCustomer()
{
    QVERIFY2(m_CustomerIDToDelete.length() > 0, "m_CustomerIDToDelete doesn't exist. Cannot continue delete test.");
    if (m_CustomerIDToDelete.length() > 0) {
        QVariantMap data;
        data[Customer::FIELD_ID] = m_CustomerIDToDelete;

        Customer *customer = Customer::fromJson(data);
        QCOMPARE(customer->deleteCustomer(), true);

        QSignalSpy spyDelete(customer, &Customer::customerDeleted);
        QVERIFY2(spyDelete.wait() == true, customer->lastError()->message().toStdString().c_str());
    }
}
