#include "AddressTests.h"
#include <QtTest/QtTest>
#include <QSignalSpy>
// QStripe
#include "QStripe/Address.h"
#include "QStripe/Utils.h"

using namespace QStripe;

AddressTests::AddressTests(QObject *parent)
    : QObject(parent)
{

}

QVariantMap AddressTests::getAddressData() const
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

void AddressTests::testAddressEquals()
{
    Address a1;
    Address a2;
    QCOMPARE(a1, a2);

    a1.setCity("Toronto");
    a2.setCity("Toronto");
    QCOMPARE(a1, a2);
}

void AddressTests::testAddressNotEquals()
{
    Address a1;
    Address a2;
    a2.setCountry("Canada");
    QVERIFY(a1 != a2);

    a1.setCity("Toronto");
    a2.setCity("Toronto");
    a2.setCountry("Canada");
    QVERIFY(a1 != a2);
}

void AddressTests::testAddressChangeSignals()
{
    Address address;

    QSignalSpy spyCountry(&address, &Address::countryChanged);
    address.setCountry("Canada");
    QCOMPARE(spyCountry.count(), 1);

    QSignalSpy spyState(&address, &Address::stateChanged);
    address.setState("Ontario");
    QCOMPARE(spyState.count(), 1);

    QSignalSpy spyCity(&address, &Address::cityChanged);
    address.setCity("Toronto");
    QCOMPARE(spyCity.count(), 1);

    QSignalSpy spyLineOne(&address, &Address::lineOneChanged);
    address.setLineOne("Some where.");
    QCOMPARE(spyLineOne.count(), 1);

    QSignalSpy spyLineTwo(&address, &Address::lineTwoChanged);
    address.setLineTwo("Some other place.");
    QCOMPARE(spyLineTwo.count(), 1);

    QSignalSpy spyPostalCode(&address, &Address::postalCodeChanged);
    address.setPostalCode("M9S 9YE");
    QCOMPARE(spyPostalCode.count(), 1);
}

void AddressTests::testAddressFromJson()
{
    const QVariantMap data = getAddressData();

    Address *addr = Address::fromJson(data);

    QCOMPARE(addr->country(), data[Address::FIELD_COUNTRY].toString());
    QCOMPARE(addr->state(), data[Address::FIELD_STATE].toString());
    QCOMPARE(addr->city(), data[Address::FIELD_CITY].toString());

    QCOMPARE(addr->lineOne(), data[Address::FIELD_LINE_1].toString());
    QCOMPARE(addr->lineTwo(), data[Address::FIELD_LINE_2].toString());
    QCOMPARE(addr->postalCode(), data[Address::FIELD_POSTAL_CODE].toString());
}

void AddressTests::testAddressSet()
{
    Address a1;
    a1.setCity("Toronto");
    Address a2;
    a2.set(a1);

    QVERIFY(a1 == a2);
}

void AddressTests::testAddressJsonString()
{
    QVariantMap data = getAddressData();
    data[Address::FIELD_STATE] = "";
    data[Address::FIELD_LINE_1] = "";
    data[Address::FIELD_LINE_2] = "";
    data[Address::FIELD_POSTAL_CODE] = "";

    Address a1;
    a1.setCountry("Canada");
    a1.setCity("Toronto");

    QCOMPARE(a1.jsonString(), Utils::toJsonString(data));
}

void AddressTests::testAddressJson()
{
    QVariantMap data = getAddressData();
    data[Address::FIELD_STATE] = "";
    data[Address::FIELD_LINE_1] = "";
    data[Address::FIELD_LINE_2] = "";
    data[Address::FIELD_POSTAL_CODE] = "";

    Address a1;
    a1.setCountry("Canada");
    a1.setCity("Toronto");

    QCOMPARE(Utils::toJsonString(a1.json()), Utils::toJsonString(data));
}
