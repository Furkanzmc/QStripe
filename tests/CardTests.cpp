#include "CardTests.h"
#include <QtTest/QtTest>
#include <QSignalSpy>
#include <QDate>
// QStripe
#include "QStripe/Card.h"
#include "QStripe/Utils.h"
#include "QStripe/Token.h"

using namespace QStripe;

CardTests::CardTests(QString customerID, QObject *parent)
    : QObject(parent)
    , m_CustomerID(customerID)
    , m_TokenID("")
    , m_Card(nullptr)
    , m_CardID()
{
    QVERIFY2(m_CustomerID.length() > 0, "Customer ID is not set. Card creatin test will not run.");
}

QVariantMap CardTests::getAddressData()
{
    QVariantMap addressData;
    addressData[Card::FIELD_ADDRESS_PREFIX + Address::FIELD_COUNTRY] = "Canada";
    addressData[Card::FIELD_ADDRESS_PREFIX + Address::FIELD_STATE] = "Ontario";
    addressData[Card::FIELD_ADDRESS_PREFIX + Address::FIELD_CITY] = "Toronto";

    addressData[Card::FIELD_ADDRESS_PREFIX + Address::FIELD_LINE_1] = "Line one.";
    addressData[Card::FIELD_ADDRESS_PREFIX + Address::FIELD_LINE_2] = "Line two.";
    addressData[Card::FIELD_ADDRESS_PREFIX + Address::FIELD_POSTAL_CODE] = "M9S U7Y";
    addressData[Card::FIELD_ADDRESS_PREFIX + Address::FIELD_ZIP_CHECK] = "unknown";

    return addressData;
}

QVariantMap CardTests::getCardData()
{
    QVariantMap data;
    data[Card::FIELD_ID] = "id";
    data[Card::FIELD_BRAND] = "American Express";
    data[Card::FIELD_COUNTRY] = "country";

    data[Card::FIELD_CURRENCY] = "cad";
    data[Card::FIELD_CVC_CHECK] = "pass";
    data[Card::FIELD_EXP_MONTH] = 11;

    data[Card::FIELD_EXP_YEAR] = 2023;
    data[Card::FIELD_FINGERPRINT] = "fingerprint";
    data[Card::FIELD_FUNDING] = "debit";

    data[Card::FIELD_NAME] = "Furkan Uzumcu";
    data[Card::FIELD_LAST4] = "last4";
    data[Card::FIELD_TOKENIZATION_METHOD] = "apple_pay";

    QVariantMap metadata;
    metadata["foo"] = "bar";
    data[Card::FIELD_METADATA] = metadata;

    const QVariantMap addressData = getAddressData();
    for (auto it = addressData.constBegin(); it != addressData.constEnd(); it++) {
        data[it.key()] = it.value();
    }

    return data;
}

QString CardTests::getCardID() const
{
    return m_CardID;
}

void CardTests::testSignals()
{
    Card card;

    QSignalSpy spyAddress(&card, &Card::addressChanged);
    Address *addr = Address::fromJson(getAddressData(), Card::FIELD_ADDRESS_PREFIX);
    card.setAddress(addr);
    addr->deleteLater();
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

void CardTests::testFromJson()
{
    const QVariantMap data = getCardData();
    const Card *card = Card::fromJson(data);

    QCOMPARE(card->cardID(), data[Card::FIELD_ID].toString());
    QCOMPARE(card->brandName(), data[Card::FIELD_BRAND].toString());
    QCOMPARE(card->country(), data[Card::FIELD_COUNTRY].toString());

    QCOMPARE(card->currency(), data[Card::FIELD_CURRENCY].toString());
    QCOMPARE(card->cvcCheckName(card->cvcCheck()), data[Card::FIELD_CVC_CHECK].toString());
    QCOMPARE(card->expirationMonth(), data[Card::FIELD_EXP_MONTH].toInt());

    QCOMPARE(card->expirationYear(), data[Card::FIELD_EXP_YEAR].toInt());
    QCOMPARE(card->fingerprint(), data[Card::FIELD_FINGERPRINT].toString());
    QCOMPARE(card->fundingTypeString(card->funding()), data[Card::FIELD_FUNDING].toString());

    QCOMPARE(card->name(), data[Card::FIELD_NAME].toString());
    QCOMPARE(card->lastFourDigits(), data[Card::FIELD_LAST4].toString());
    QCOMPARE(card->tokenizationMethodName(card->tokenizationMethod()), data[Card::FIELD_TOKENIZATION_METHOD].toString());

    QCOMPARE(card->metaData(), data[Card::FIELD_METADATA].toMap());

    Address *addr = Address::fromJson(data, Card::FIELD_ADDRESS_PREFIX);
    QCOMPARE(card->address()->jsonString(Card::FIELD_ADDRESS_PREFIX), addr->jsonString(Card::FIELD_ADDRESS_PREFIX));
    addr->deleteLater();
}

void CardTests::testJsonStr()
{
    QVariantMap data = getCardData();
    Card *card = Card::fromString(Utils::toJsonString(data));

    const QVariantMap metadata = card->metaData();
    for (auto it = metadata.constBegin(); it != metadata.constEnd(); it++) {
        const QString key = Card::FIELD_METADATA + "[" + it.key() + "]";
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

    data.remove(Card::FIELD_METADATA);

    QCOMPARE(card->jsonString(), Utils::toJsonString(data));
    card->deleteLater();
}

void CardTests::testJson()
{
    QVariantMap data = getCardData();
    Card *card = Card::fromJson(data);

    const QVariantMap metadata = card->metaData();
    for (auto it = metadata.constBegin(); it != metadata.constEnd(); it++) {
        const QString key = Card::FIELD_METADATA + "[" + it.key() + "]";
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

    data.remove(Card::FIELD_METADATA);

    QCOMPARE(card->json(), data);
    card->deleteLater();
}

void CardTests::testSet()
{
    Card *c1 = Card::fromJson(getCardData());
    Card c2;
    c2.set(c1);

    QCOMPARE(c2.cardID(), c1->cardID());
    QCOMPARE(c2.brandName(), c1->brandName());
    QCOMPARE(c2.country(), c1->country());

    QCOMPARE(c2.currency(), c1->currency());
    QCOMPARE(c2.expirationMonth(), c1->expirationMonth());
    QCOMPARE(c2.expirationYear(), c1->expirationYear());

    QCOMPARE(c2.fingerprint(), c1->fingerprint());
    QCOMPARE(c2.name(), c1->name());
    QCOMPARE(c2.lastFourDigits(), c1->lastFourDigits());

    QCOMPARE(c2.metaData(), c1->metaData());
    QCOMPARE(c2.fundingTypeString(c2.funding()), c1->fundingTypeString(c1->funding()));
    QCOMPARE(c2.cvcCheckName(c2.cvcCheck()), c1->cvcCheckName(c1->cvcCheck()));

    QCOMPARE(c2.tokenizationMethodName(c2.tokenizationMethod()), c1->tokenizationMethodName(c1->tokenizationMethod()));
    QVERIFY((*c2.address()) == (*c1->address()));

    c1->deleteLater();
}

void CardTests::testCardBrand()
{
    // Card numbers are taken from here: https://www.paypalobjects.com/en_AU/vhelp/paypalmanager_help/credit_card_numbers.htm
    const QString americanExpressOne = "378282246310005";
    const QString americanExpressTwo = "371449635398431";
    const QString americanExpressCorporate = "378734493671000";

    const QString discoverOne = "6011111111111117";
    const QString discoverTwo = "6011000990139424";

    const QString jcbOne = "3530111333300000";
    const QString jcbTwo = "3566002020360505";

    const QString dinersClubOne = "30569309025904";
    const QString dinersClubTwo = "38520000023237";

    const QString visaOne = "4111111111111111";
    const QString visaTwo = "4012888888881881";

    const QString masterCardOne = "5555555555554444";
    const QString masterCardTwo = "5105105105105100";

    Card card;

    card.setCardNumber(americanExpressOne);
    QCOMPARE(card.possibleCardBrand(), Card::AmericanExpress);

    card.setCardNumber(americanExpressTwo);
    QCOMPARE(card.possibleCardBrand(), Card::AmericanExpress);

    card.setCardNumber(americanExpressCorporate);
    QCOMPARE(card.possibleCardBrand(), Card::AmericanExpress);

    card.setCardNumber(discoverOne);
    QCOMPARE(card.possibleCardBrand(), Card::Discover);

    card.setCardNumber(discoverTwo);
    QCOMPARE(card.possibleCardBrand(), Card::Discover);

    card.setCardNumber(jcbOne);
    QCOMPARE(card.possibleCardBrand(), Card::JCB);

    card.setCardNumber(jcbTwo);
    QCOMPARE(card.possibleCardBrand(), Card::JCB);

    card.setCardNumber(dinersClubOne);
    QCOMPARE(card.possibleCardBrand(), Card::DinersClub);

    card.setCardNumber(dinersClubTwo);
    QCOMPARE(card.possibleCardBrand(), Card::DinersClub);

    card.setCardNumber(visaOne);
    QCOMPARE(card.possibleCardBrand(), Card::Visa);

    card.setCardNumber(visaTwo);
    QCOMPARE(card.possibleCardBrand(), Card::Visa);

    card.setCardNumber(masterCardOne);
    QCOMPARE(card.possibleCardBrand(), Card::MasterCard);

    card.setCardNumber(masterCardTwo);
    QCOMPARE(card.possibleCardBrand(), Card::MasterCard);
}

void CardTests::testCardLength()
{
    // Card numbers are taken from here: https://www.paypalobjects.com/en_AU/vhelp/paypalmanager_help/credit_card_numbers.htm
    const QString americanExpressInvalid = "37828";
    const QString americanExpressValid = "371449635398431";
    const QString americanExpressInvalidTwo = "3787344936";

    const QString discoverInvalid = "6011111111";
    const QString discoverValid = "6011000990139424";

    const QString jcbInvalid = "3530111333";
    const QString jcbValid = "3566002020360505";

    const QString dinersClubInvalid = "305693094";
    const QString dinersClubValid = "38520000023237";

    const QString visaInvalid = "4111111111111";
    const QString visaValid = "4012888888881881";

    const QString masterCardInvalid = "555555555555";
    const QString masterCardValid = "5105105105105100";

    Card card;

    card.setCardNumber(americanExpressInvalid);
    QCOMPARE(card.validCardLenght(), false);

    card.setCardNumber(americanExpressValid);
    QCOMPARE(card.validCardLenght(), true);

    card.setCardNumber(americanExpressInvalidTwo);
    QCOMPARE(card.validCardLenght(), false);

    card.setCardNumber(discoverInvalid);
    QCOMPARE(card.validCardLenght(), false);

    card.setCardNumber(discoverValid);
    QCOMPARE(card.validCardLenght(), true);

    card.setCardNumber(jcbInvalid);
    QCOMPARE(card.validCardLenght(), false);

    card.setCardNumber(jcbValid);
    QCOMPARE(card.validCardLenght(), true);

    card.setCardNumber(dinersClubInvalid);
    QCOMPARE(card.validCardLenght(), false);

    card.setCardNumber(dinersClubValid);
    QCOMPARE(card.validCardLenght(), true);

    card.setCardNumber(visaInvalid);
    QCOMPARE(card.validCardLenght(), false);

    card.setCardNumber(visaValid);
    QCOMPARE(card.validCardLenght(), true);

    card.setCardNumber(masterCardInvalid);
    QCOMPARE(card.validCardLenght(), false);

    card.setCardNumber(masterCardValid);
    QCOMPARE(card.validCardLenght(), true);
}

void CardTests::testCardNumberValidation()
{
    // Card numbers are taken from here: https://www.paypalobjects.com/en_AU/vhelp/paypalmanager_help/credit_card_numbers.htm
    const QString americanExpressInvalid = "37828224631000a5";
    const QString americanExpressValid = "371449635398431";
    const QString americanExpressInvalidTwo = "3787344936710022a323220";

    const QString discoverInvalid = "6011111111111112227";
    const QString discoverValid = "6011000990139424";

    const QString jcbInvalid = "3530111333300000222222222";
    const QString jcbValid = "3566002020360505";

    const QString dinersClubInvalid = "305693090259046734343434asdad";
    const QString dinersClubValid = "38520000023237";

    const QString visaInvalid = "4111111112dd23434333441111";
    const QString visaValid = "4012888888881881";

    const QString masterCardInvalid = "555555535644422ffr33355555";
    const QString masterCardValid = "5105105105105100";

    Card card;

    card.setCardNumber(americanExpressInvalid);
    QCOMPARE(card.validCardNumber(), false);

    card.setCardNumber(americanExpressValid);
    QCOMPARE(card.validCardNumber(), true);

    card.setCardNumber(americanExpressInvalidTwo);
    QCOMPARE(card.validCardNumber(), false);

    card.setCardNumber(discoverInvalid);
    QCOMPARE(card.validCardNumber(), false);

    card.setCardNumber(discoverValid);
    QCOMPARE(card.validCardNumber(), true);

    card.setCardNumber(jcbInvalid);
    QCOMPARE(card.validCardNumber(), false);

    card.setCardNumber(jcbValid);
    QCOMPARE(card.validCardNumber(), true);

    card.setCardNumber(dinersClubInvalid);
    QCOMPARE(card.validCardNumber(), false);

    card.setCardNumber(dinersClubValid);
    QCOMPARE(card.validCardNumber(), true);

    card.setCardNumber(visaInvalid);
    QCOMPARE(card.validCardNumber(), false);

    card.setCardNumber(visaValid);
    QCOMPARE(card.validCardNumber(), true);

    card.setCardNumber(masterCardInvalid);
    QCOMPARE(card.validCardNumber(), false);

    card.setCardNumber(masterCardValid);
    QCOMPARE(card.validCardNumber(), true);
}

void CardTests::testValidExpirationMonth()
{
    Card card;
    card.setExpirationMonth(-1);
    QCOMPARE(card.validExpirationMonth(), false);

    card.setExpirationMonth(2001);
    QCOMPARE(card.validExpirationMonth(), false);

    card.setExpirationMonth(13);
    QCOMPARE(card.validExpirationMonth(), false);

    card.setExpirationMonth(12);
    QCOMPARE(card.validExpirationMonth(), true);

    const QDate today = QDate::currentDate();
    card.setExpirationMonth(today.month());
    QCOMPARE(card.validExpirationMonth(), true);
}

void CardTests::testValidExpirationYear()
{
    const QDate today = QDate::currentDate();
    Card card;

    card.setExpirationYear(-1);
    QCOMPARE(card.validExpirationYear(), false);

    card.setExpirationYear(-2039);
    QCOMPARE(card.validExpirationYear(), false);

    card.setExpirationYear(today.year() + 5);
    QCOMPARE(card.validExpirationYear(), true);

    card.setExpirationYear(today.year());
    QCOMPARE(card.validExpirationYear(), true);

    card.setExpirationYear(today.year() - 2);
    QCOMPARE(card.validExpirationYear(), false);

    // This test should be OK for a while.
    card.setExpirationYear(35);
    QCOMPARE(card.validExpirationYear(), true);

    // We definelty passed 2011.
    card.setExpirationYear(11);
    QCOMPARE(card.validExpirationYear(), false);
}

void CardTests::testValidExpirationDate()
{
    const QDate today = QDate::currentDate();
    Card card;

    card.setExpirationYear(-1);
    card.setExpirationMonth(-1);
    QCOMPARE(card.validExpirationDate(), false);

    card.setExpirationMonth(today.month() - 1);
    card.setExpirationYear(today.year() - 1);
    QCOMPARE(card.validExpirationDate(), false);

    card.setExpirationMonth(today.month());
    card.setExpirationYear(today.year());
    QCOMPARE(card.validExpirationDate(), true);

    card.setExpirationMonth(today.month());
    card.setExpirationYear(today.year() - 1);
    QCOMPARE(card.validExpirationDate(), false);

    card.setExpirationMonth(35);
    card.setExpirationYear(11);
    QCOMPARE(card.validExpirationDate(), false);

    card.setExpirationMonth(1);
    card.setExpirationYear(35);
    QCOMPARE(card.validExpirationDate(), true);
}

void CardTests::testValidCVC()
{
    const QString americanExpressOne = "378282246310005";
    const QString discoverOne = "6011111111111117";
    const QString visaOne = "4111111111111111";

    Card card;
    card.setCvc("333");
    card.setCardNumber(americanExpressOne);
    QCOMPARE(card.validCVC(), false);

    card.setCvc("3333");
    QCOMPARE(card.validCVC(), true);

    card.setCvc("3333");
    card.setCardNumber(discoverOne);
    QCOMPARE(card.validCVC(), false);

    card.setCvc("333");
    QCOMPARE(card.validCVC(), true);

    card.setCvc("33");
    card.setCardNumber(visaOne);
    QCOMPARE(card.validCVC(), false);

    card.setCvc("333");
    QCOMPARE(card.validCVC(), true);
}

void CardTests::testCreateToken()
{
    const QDate today = QDate::currentDate();
    QVariantMap data;
    data[Card::FIELD_CURRENCY] = "cad";
    data[Card::FIELD_EXP_MONTH] = today.month();
    data[Card::FIELD_EXP_YEAR] = today.year() + 5;

    data[Card::FIELD_COUNTRY] = "CA";
    data[Card::FIELD_NAME] = "Furkan Uzumcu";

    Card *card = Card::fromJson(data);

    Address *address = card->address();
    address->setCity("Toronto");
    address->setCountry("Canada");

    address->setLineOne("101 Botfield Ave.");

    QCOMPARE(card->createToken(), false);

    card->setCvc("232");
    card->setCardNumber("4242424242424242");
    QCOMPARE(card->createToken(), true);
    QSignalSpy spy(card, &Card::tokenCreated);
    const bool sucess = spy.wait() == true;
    QVERIFY2(sucess, card->lastError()->message().toStdString().c_str());
    if (sucess) {
        m_TokenID = card->token()->tokenID();
    }

    card->setParent(this);
    m_Card = card;
}

void CardTests::testTokenFetch()
{
    QVERIFY2(m_TokenID.length() > 0, "Token ID is not set.");

    if (m_TokenID.length() > 0) {
        Card card;
        card.fetchToken(m_TokenID);
        QSignalSpy spy(&card, &Card::tokenFetched);
        const bool sucess = spy.wait() == true;
        QVERIFY2(sucess, card.lastError()->message().toStdString().c_str());

        const QDate today = QDate::currentDate();
        // The data here should match the one in CardTests::testCreateToken()
        QCOMPARE(card.token()->tokenID(), m_TokenID);
        qInfo() << "CVC Check: " << Card::cvcCheckName(card.cvcCheck());
        QCOMPARE(card.lastFourDigits(), "4242");
        QCOMPARE(card.expirationMonth(), today.month());
        QCOMPARE(card.expirationYear(), today.year() + 5);
    }
}

void CardTests::testCreate()
{
    QVERIFY2(m_Card != nullptr, "m_Card is not set.");

    if (m_Card) {
        QCOMPARE(m_Card->create(), false);
        QCOMPARE(m_Card->create(m_CustomerID), true);

        QSignalSpy spy(m_Card, &Card::created);
        const bool sucess = spy.wait() == true;
        QVERIFY2(sucess, m_Card->lastError()->message().toStdString().c_str());
    }
}

void CardTests::testDelete()
{
    QVERIFY2(m_Card != nullptr, "m_Card is not set.");

    if (m_Card) {
        QCOMPARE(m_Card->deleteCard(), false);
        QCOMPARE(m_Card->deleteCard(m_CustomerID), true);

        QSignalSpy spy(m_Card, &Card::deleted);
        const bool sucess = spy.wait() == true;
        QVERIFY2(sucess, m_Card->lastError()->message().toStdString().c_str());
    }
}
