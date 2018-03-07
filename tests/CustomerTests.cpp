#include "CustomerTests.h"
#include <QtTest/QtTest>
#include <QSignalSpy>
// QStripe
#include "QStripe/Customer.h"
#include "QStripe/Utils.h"

using namespace QStripe;

CustomerTests::CustomerTests(QObject *parent)
    : QObject(parent)
{

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

    return addressData;
}

QVariantMap CustomerTests::getShippingInformationData() const
{
    QVariantMap addressData;
    addressData[Address::FIELD_COUNTRY] = "Canada";
    addressData[Address::FIELD_STATE] = "Ontario";
    addressData[Address::FIELD_CITY] = "Toronto";

    addressData[Address::FIELD_LINE_1] = "Line one.";
    addressData[Address::FIELD_LINE_2] = "Line two.";
    addressData[Address::FIELD_POSTAL_CODE] = "M9S U7Y";

    QVariantMap data;
    data[ShippingInformation::FIELD_NAME] = "Furkan Uzumcu";
    data[ShippingInformation::FIELD_PHONE] = "+11234123123";
    data[ShippingInformation::FIELD_ADDRESS] = addressData;

    return data;
}

QVariantMap CustomerTests::getData() const
{
    QVariantMap data;
    data[Customer::FIELD_CURRENCY] = "cad";
    data[Customer::FIELD_DEFAULT_SOURCE] = "source";
    data[Customer::FIELD_SHIPPING] = getShippingInformationData();

    data[Customer::FIELD_EMAIL] = "foo@bar.com";
    data[Customer::FIELD_DESCRIPTION] = "Here be descriton.";

    QVariantMap meta;
    meta["meta"] = "data";
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

    const Customer *customer = Customer::fromJson(Utils::toJsonString(data));

    QCOMPARE(customer->currency(), data[Customer::FIELD_CURRENCY].toString());
    QCOMPARE(customer->defaultSource(), data[Customer::FIELD_DEFAULT_SOURCE].toString());
    QCOMPARE(customer->shippingInformation()->json(), shippingData);

    QCOMPARE(customer->email(), data[Customer::FIELD_EMAIL].toString());
    QCOMPARE(customer->description(), data[Customer::FIELD_DESCRIPTION].toString());
    QCOMPARE(customer->metadata(), data[Customer::FIELD_METADATA].toMap());
}

void CustomerTests::testJsonStr()
{
    const QVariantMap data = getData();
    const Customer *customer = Customer::fromJson(Utils::toJsonString(data));

    QCOMPARE(customer->jsonStr(), Utils::toJsonString(data));
}

void CustomerTests::testJson()
{
    const QVariantMap data = getData();
    const Customer *customer = Customer::fromJson(Utils::toJsonString(data));

    QCOMPARE(customer->json(), data);
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
