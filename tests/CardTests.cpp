#include "CardTests.h"
#include <QtTest/QtTest>
#include <QSignalSpy>
// QStripe
#include "QStripe/Card.h"
#include "QStripe/Utils.h"

using namespace QStripe;

CardTests::CardTests(QObject *parent)
    : QObject(parent)
{

}

QVariantMap CardTests::getAddressData() const
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

void CardTests::testSignals()
{
    Card card;

    QSignalSpy spyCity(&card, &Card::cityChanged);
    card.setCity("Toronto");
    QCOMPARE(spyCity.count(), 1);

    QSignalSpy spyAddress(&card, &Card::addressChanged);
    card.setAddress(Address::fromJson(Utils::toJsonString(getAddressData())));
    QCOMPARE(spyAddress.count(), 1);

    QSignalSpy spyBrand(&card, &Card::brandChanged);
    card.setBrand(Card::CardBrand::AmericanExpress);
    QCOMPARE(spyBrand.count(), 1);

    QSignalSpy spyCountry(&card, &Card::countryChanged);
    card.setCountry("Canada");
    QCOMPARE(spyCountry.count(), 1);

    QSignalSpy spyCurrency(&card, &Card::currencyChanged);
    card.setCurrency("cad");
    QCOMPARE(spyCurrency.count(), 1);

    QSignalSpy spyCVCCheck(&card, &Card::cvcCheckChanged);
    card.setCVCCheck(Card::CVCCheckPass);
    QCOMPARE(spyCVCCheck.count(), 1);

    QSignalSpy spyExpMonth(&card, &Card::expirationMonthChanged);
    card.setExpirationMonth(1);
    QCOMPARE(spyExpMonth.count(), 1);

    QSignalSpy spyExpYear(&card, &Card::expirationYearChanged);
    card.setExpirationYear(1);
    QCOMPARE(spyExpYear.count(), 1);

    QSignalSpy spyFingerprint(&card, &Card::fingerprintChanged);
    card.setFingerprint("fingerprint");
    QCOMPARE(spyFingerprint.count(), 1);

    QSignalSpy spyFunding(&card, &Card::fundingChanged);
    card.setFunding(Card::FundingCredit);
    QCOMPARE(spyFunding.count(), 1);

    QSignalSpy spyName(&card, &Card::nameChanged);
    card.setName("Furkan Uzumcu");
    QCOMPARE(spyName.count(), 1);

    QSignalSpy spyLastDigits(&card, &Card::lastFourDigitsChanged);
    card.setLastFourDigits("4242");
    QCOMPARE(spyLastDigits.count(), 1);

    QSignalSpy spyTokenization(&card, &Card::tokenizationMethodChanged);
    card.setTokenizationMethod(Card::TokenizationMethod::ApplePay);
    QCOMPARE(spyTokenization.count(), 1);

    QSignalSpy spyMetaData(&card, &Card::metaDataChanged);
    QVariantMap data;
    data["foo"] = "bar";
    card.setMetaData(data);
    QCOMPARE(spyMetaData.count(), 1);

    QSignalSpy spyNumber(&card, &Card::cardNumberChanged);
    card.setCardNumber("4242424242424242");
    QCOMPARE(spyNumber.count(), 1);
}
