#include <QtTest/QtTest>
#include <QSignalSpy>
#include "TestQStripe.h"
// QStripe
#include "QStripe/Address.h"
#include "QStripe/ShippingInformation.h"
#include "QStripe/Utils.h"

using namespace QStripe;

QVariantMap TestQStripe::getAddressData() const
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

QVariantMap TestQStripe::getShippingInformationData() const
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

void TestQStripe::testAddressEquals()
{
    Address a1;
    Address a2;
    QCOMPARE(a1, a2);

    a1.setCity("Toronto");
    a2.setCity("Toronto");
    QCOMPARE(a1, a2);
}

void TestQStripe::testAddressNotEquals()
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

void TestQStripe::testAddressChangeSignals()
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

void TestQStripe::testAddressFromJson()
{
    const QVariantMap data = getAddressData();

    Address *addr = Address::fromJson(Utils::toJsonString(data));

    QCOMPARE(addr->country(), data[Address::FIELD_COUNTRY].toString());
    QCOMPARE(addr->state(), data[Address::FIELD_STATE].toString());
    QCOMPARE(addr->city(), data[Address::FIELD_CITY].toString());

    QCOMPARE(addr->lineOne(), data[Address::FIELD_LINE_1].toString());
    QCOMPARE(addr->lineTwo(), data[Address::FIELD_LINE_2].toString());
    QCOMPARE(addr->postalCode(), data[Address::FIELD_POSTAL_CODE].toString());
}

void TestQStripe::testAddressSet()
{
    Address a1;
    a1.setCity("Toronto");
    Address a2;
    a2.set(a1);

    QVERIFY(a1 == a2);
}

void TestQStripe::testAddressJsonString()
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

void TestQStripe::testAddressJson()
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

void TestQStripe::testShippingInformationFromJson()
{
    QVariantMap addressData = getAddressData();

    const QVariantMap data = getShippingInformationData();

    ShippingInformation *si = ShippingInformation::fromJson(Utils::toJsonString(data));

    QCOMPARE(si->name(), data[ShippingInformation::FIELD_NAME].toString());
    QCOMPARE(si->phone(), data[ShippingInformation::FIELD_PHONE].toString());
    QVERIFY((*si->address()) == *Address::fromJson(Utils::toJsonString(addressData)));
}

void TestQStripe::testShippingInformationJson()
{
    QVariantMap data = getShippingInformationData();
    data[ShippingInformation::FIELD_NAME] = "";
    data[ShippingInformation::FIELD_PHONE] = "";

    ShippingInformation si;
    si.setAddress(Address::fromJson(Utils::toJsonString(getAddressData())));

    QCOMPARE(Utils::toJsonString(si.json()), Utils::toJsonString(data));
}

void TestQStripe::testShippingInformationJsonString()
{
    QVariantMap data = getShippingInformationData();
    data[ShippingInformation::FIELD_NAME] = "";
    data[ShippingInformation::FIELD_PHONE] = "";

    ShippingInformation si;
    si.setAddress(Address::fromJson(Utils::toJsonString(getAddressData())));

    QCOMPARE(si.jsonString(), Utils::toJsonString(data));
}

void TestQStripe::testShippingInformationSet()
{
    ShippingInformation si1, si2;
    si1.setName("Furkan Uzumcu");
    si1.setPhone("1234123123");

    si2.set(si1);

    QCOMPARE(si1.name(), si2.name());
    QCOMPARE(si1.phone(), si2.phone());
}

void TestQStripe::testShippingInformationSetAddress()
{
    Address *addr = Address::fromJson(Utils::toJsonString(getAddressData()));
    ShippingInformation si;
    si.setAddress(addr);

    QVERIFY((*addr) == (*si.address()));
}

QTEST_MAIN(TestQStripe)
#include "TestQStripe.moc"
