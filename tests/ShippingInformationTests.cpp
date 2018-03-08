#include "ShippingInformationTests.h"
#include <QtTest/QtTest>
#include <QSignalSpy>
// QStripe
#include "QStripe/Address.h"
#include "QStripe/ShippingInformation.h"
#include "QStripe/PaymentSource.h"
#include "QStripe/Utils.h"

using namespace QStripe;

ShippingInformationTests::ShippingInformationTests(QObject *parent)
    : QObject(parent)
{

}

QVariantMap ShippingInformationTests::getAddressData() const
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

QVariantMap ShippingInformationTests::getShippingInformationData() const
{
    const QVariantMap addressData = getAddressData();

    QVariantMap data;
    data[ShippingInformation::FIELD_NAME] = "Furkan Uzumcu";
    data[ShippingInformation::FIELD_PHONE] = "+11234123123";
    data[ShippingInformation::FIELD_ADDRESS] = addressData;

    return data;
}

void ShippingInformationTests::testShippingInformationFromJson()
{
    QVariantMap addressData = getAddressData();
    const QVariantMap data = getShippingInformationData();

    ShippingInformation *si = ShippingInformation::fromJson(Utils::toJsonString(data));

    QCOMPARE(si->name(), data[ShippingInformation::FIELD_NAME].toString());
    QCOMPARE(si->phone(), data[ShippingInformation::FIELD_PHONE].toString());
    QVERIFY((*si->address()) == *Address::fromJson(Utils::toJsonString(addressData)));
}

void ShippingInformationTests::testShippingInformationJson()
{
    QVariantMap data = getShippingInformationData();
    data[ShippingInformation::FIELD_NAME] = "";
    data[ShippingInformation::FIELD_PHONE] = "";

    ShippingInformation si;
    si.setAddress(Address::fromJson(Utils::toJsonString(getAddressData())));

    QCOMPARE(Utils::toJsonString(si.json()), Utils::toJsonString(data));
}

void ShippingInformationTests::testShippingInformationJsonString()
{
    QVariantMap data = getShippingInformationData();
    data[ShippingInformation::FIELD_NAME] = "";
    data[ShippingInformation::FIELD_PHONE] = "";

    ShippingInformation si;
    si.setAddress(Address::fromJson(Utils::toJsonString(getAddressData())));

    QCOMPARE(si.jsonString(), Utils::toJsonString(data));
}

void ShippingInformationTests::testShippingInformationSet()
{
    ShippingInformation si1, si2;
    si1.setName("Furkan Uzumcu");
    si1.setPhone("1234123123");

    si2.set(si1);

    QCOMPARE(si1.name(), si2.name());
    QCOMPARE(si1.phone(), si2.phone());
}

void ShippingInformationTests::testShippingInformationSetAddress()
{
    Address *addr = Address::fromJson(Utils::toJsonString(getAddressData()));
    ShippingInformation si;
    si.setAddress(addr);

    QVERIFY((*addr) == (*si.address()));
}
