#include "QStripe/Card.h"
#include "QStripe/Utils.h"

namespace QStripe
{

const QString Card::FIELD_ID = "id";
const QString Card::FIELD_OBJECT = "object";
const QString Card::FIELD_ADDRESS_CITY = "address_city";

const QString Card::FIELD_ADDRESS_PREFIX = "address_";
const QString Card::FIELD_BRAND = "brand";
const QString Card::FIELD_COUNTRY = "country";

const QString Card::FIELD_CURRENCY = "currency";
const QString Card::FIELD_CVC_CHECK = "cvc_check";

const QString Card::FIELD_EXP_MONTH = "exp_month";
const QString Card::FIELD_EXP_YEAR = "exp_year";
const QString Card::FIELD_FINGERPRINT = "fingerprint";

const QString Card::FIELD_FUNDING = "funding";
const QString Card::FIELD_NAME = "name";
const QString Card::FIELD_LAST4 = "last4";

const QString Card::FIELD_TOKENIZATION_METHOD = "tokenization_method";
const QString Card::FIELD_METADATA = "metadata";

Card::Card(QObject *parent)
    : QObject(parent)
    , m_CardID("")
    , m_City("")
    , m_Address()
    , m_Brand(CardBrand::Unknown)
    , m_Country("")
    , m_Currency("")
    , m_CVCCheck(CVCCheck::CVCCheckUnknown)
    , m_ExpirationMonth(0)
    , m_ExpirationYear(0)
    , m_Fingerprint("")
    , m_FundingType(FundingType::FundingUnknown)
    , m_Name("")
    , m_LastFourDigits("")
    , m_TokenizationMethod(TokenizationMethod::TokenizationUnknown)
    , m_MetaData()
    , m_CardNumber("")
    , m_CVC("")
{
    connect(this, &Card::cardNumberChanged, this, &Card::updateCardBrand);
}

QString Card::cardID() const
{
    return m_CardID;
}

QString Card::city() const
{
    return m_City;
}

void Card::setCity(const QString &ct)
{
    const bool changed = m_City != ct;
    if (changed) {
        m_City = ct;
        emit cityChanged();
    }
}

Address *Card::address()
{
    return &m_Address;
}

const Address *Card::address() const
{
    return &m_Address;
}

void Card::setAddress(const Address *addr)
{
    const bool changed = m_Address != (*addr);
    if (changed) {
        m_Address.set(*addr);
        emit addressChanged();
    }
}

Card::CardBrand Card::brand() const
{
    return m_Brand;
}

QString Card::brandName() const
{
    return cardBrandName(brand());
}

void Card::setBrand(const CardBrand &cardBrand)
{
    const bool changed = m_Brand != cardBrand;
    if (changed) {
        m_Brand = cardBrand;
        emit brandChanged();
    }
}

QString Card::country() const
{
    return m_Country;
}

void Card::setCountry(const QString &country)
{
    const bool changed = m_Country != country;
    if (changed) {
        m_Country = country;
        emit countryChanged();
    }
}

QString Card::currency() const
{
    return m_Currency;
}

void Card::setCurrency(const QString &currency)
{
    const bool changed = m_Currency != currency;
    if (changed) {
        m_Currency = currency;
        emit currencyChanged();
    }
}

Card::CVCCheck Card::cvcCheck() const
{
    return m_CVCCheck;
}

int Card::expirationMonth() const
{
    return m_ExpirationMonth;
}

void Card::setExpirationMonth(int month)
{
    const bool changed = m_ExpirationMonth != month;
    if (changed) {
        m_ExpirationMonth = month;
        emit expirationMonthChanged();
    }
}

int Card::expirationYear() const
{
    return m_ExpirationYear;
}

void Card::setExpirationYear(int year)
{
    const bool changed = m_ExpirationYear != year;
    if (changed) {
        m_ExpirationYear = year;
        emit expirationYearChanged();
    }
}

QString Card::fingerprint() const
{
    return m_Fingerprint;
}

void Card::setFingerprint(const QString &fingerprint)
{
    const bool changed = m_Fingerprint != fingerprint;
    if (changed) {
        m_Fingerprint = fingerprint;
        emit fingerprintChanged();
    }
}

Card::FundingType Card::funding() const
{
    return m_FundingType;
}

void Card::setFunding(const FundingType &type)
{
    const bool changed = m_FundingType != type;
    if (changed) {
        m_FundingType = type;
        emit fundingChanged();
    }
}

QString Card::name() const
{
    return m_Name;
}

void Card::setName(const QString &name)
{
    const bool changed = m_Name != name;
    if (changed) {
        m_Name = name;
        emit nameChanged();
    }
}

QString Card::lastFourDigits() const
{
    return m_LastFourDigits;
}

void Card::setLastFourDigits(const QString &lastDigits)
{
    const bool changed = m_LastFourDigits != lastDigits;
    if (changed) {
        m_LastFourDigits = lastDigits;
        emit lastFourDigitsChanged();
    }
}

Card::TokenizationMethod Card::tokenizationMethod() const
{
    return m_TokenizationMethod;
}

void Card::setTokenizationMethod(const TokenizationMethod &method)
{
    const bool changed = m_TokenizationMethod != method;
    if (changed) {
        m_TokenizationMethod = method;
        emit tokenizationMethodChanged();
    }
}

QVariantMap Card::metaData() const
{
    return m_MetaData;
}

void Card::setMetaData(const QVariantMap &data)
{
    const bool changed = m_MetaData != data;
    if (changed) {
        m_MetaData = data;
        emit metaDataChanged();
    }
}

QString Card::cardNumber() const
{
    return m_CardNumber;
}

void Card::setCardNumber(const QString &number)
{
    const bool changed = m_CardNumber != number;
    if (changed) {
        m_CardNumber = number;
        emit cardNumberChanged();
    }
}

QString Card::cvc() const
{
    return m_CVC;
}

void Card::setCvc(const QString &cvcNumber)
{
    const bool changed = m_CVC != cvcNumber;
    if (changed) {
        m_CVC = cvcNumber;
        emit cvcChanged();
    }
}

QVariantMap Card::json() const
{
    QVariantMap data;

    data[FIELD_ID] = cardID();
    data[FIELD_ADDRESS_CITY] = city();
    data[FIELD_BRAND] = cardBrandName(brand());

    data[FIELD_COUNTRY] = country();
    data[FIELD_CURRENCY] = currency();
    data[FIELD_CVC_CHECK] = cvcCheckName(cvcCheck());

    data[FIELD_EXP_MONTH] = expirationMonth();
    data[FIELD_EXP_YEAR] = expirationYear();
    data[FIELD_FINGERPRINT] = fingerprint();

    data[FIELD_FUNDING] = fundingTypeString(funding());
    data[FIELD_NAME] = name();
    data[FIELD_LAST4] = lastFourDigits();

    data[FIELD_TOKENIZATION_METHOD] = tokenizationMethodName(tokenizationMethod());
    data[FIELD_METADATA] = metaData();

    const QVariantMap addressData = m_Address.json(FIELD_ADDRESS_PREFIX);
    for (auto it = addressData.constBegin(); it != addressData.constEnd(); it++) {
        data[it.key()] = it.value();
    }

    return data;
}

QString Card::jsonString() const
{
    return Utils::toJsonString(json());
}

Card::CardBrand Card::possibleCardBrand() const
{
    CardBrand cardType = CardBrand::Unknown;
    QString number = m_CardNumber;
    number.remove("\\s|-");
    if (number.length() < 4) {
        return cardType;
    }

    auto hasPrefix = [&number](const QVector<QString> &prefix) {
        bool has = false;
        for (const QString &str : prefix) {
            if (number.startsWith(str)) {
                has = true;
                break;
            }
        }

        return has;
    };

    if (hasPrefix(prefixes(CardBrand::AmericanExpress))) {
        cardType = CardBrand::AmericanExpress;
    }
    else if (hasPrefix(prefixes(CardBrand::Discover))) {
        cardType = CardBrand::Discover;
    }
    else if (hasPrefix(prefixes(CardBrand::JCB))) {
        cardType = CardBrand::JCB;
    }
    else if (hasPrefix(prefixes(CardBrand::DinersClub))) {
        cardType = CardBrand::DinersClub;
    }
    else if (hasPrefix(prefixes(CardBrand::Visa))) {
        cardType = CardBrand::Visa;
    }
    else if (hasPrefix(prefixes(CardBrand::MasterCard))) {
        cardType = CardBrand::MasterCard;
    }

    return cardType;
}

void Card::set(const Card &other)
{
    setCardID(other.cardID());
    setCardNumber(other.cardNumber());
    setCvc(other.cvc());

    setCVCCheck(other.cvcCheck());
    setCity(other.city());
    setCountry(other.country());

    setCurrency(other.currency());
    setExpirationMonth(other.expirationMonth());
    setExpirationYear(other.expirationYear());

    setAddress(other.address());
    setFunding(other.funding());
    setName(other.name());

    setFingerprint(other.fingerprint());
    setLastFourDigits(other.lastFourDigits());
    setMetaData(other.metaData());

    setTokenizationMethod(other.tokenizationMethod());
    setBrand(other.brand());
}

QString Card::cardBrandName(CardBrand brand)
{
    QString name;
    if (brand == CardBrand::AmericanExpress) {
        name = "American Express";
    }
    else if (brand == CardBrand::Discover) {
        name = "Discover";
    }
    else if (brand == CardBrand::JCB) {
        name = "JCB";
    }
    else if (brand == CardBrand::DinersClub) {
        name = "Diners Club";
    }
    else if (brand == CardBrand::Visa) {
        name = "Visa";
    }
    else if (brand == CardBrand::MasterCard) {
        name = "MasterCard";
    }
    else if (brand == CardBrand::Unknown) {
        name = "Unknown";
    }

    return name;
}

Card::CardBrand Card::cardBrandType(const QString &name)
{
    CardBrand brand;
    if (name == "American Express") {
        brand = CardBrand::AmericanExpress;
    }
    else if (name == "Discover") {
        brand = CardBrand::Discover;
    }
    else if (name == "JCB") {
        brand = CardBrand::JCB;
    }
    else if (name == "Diners Club") {
        brand = CardBrand::DinersClub;
    }
    else if (name == "Visa") {
        brand = CardBrand::Visa;
    }
    else if (name == "MasterCard") {
        brand = CardBrand::MasterCard;
    }
    else {
        brand = CardBrand::Unknown;
    }

    return brand;
}

QString Card::fundingTypeString(FundingType type)
{
    QString name;
    if (type == FundingType::FundingCredit) {
        name = "credit";
    }
    else if (type == FundingType::FundingDebit) {
        name = "debit";
    }
    else if (type == FundingType::FundingPrePaid) {
        name = "prepaid";
    }
    else if (type == FundingType::FundingUnknown) {
        name = "unknown";
    }

    return name;
}

Card::FundingType Card::fundingType(const QString &name)
{
    FundingType type;
    if (name == "credit") {
        type = FundingType::FundingCredit;
    }
    else if (name == "debit") {
        type = FundingType::FundingDebit;
    }
    else if (name == "prepaid") {
        type = FundingType::FundingPrePaid;
    }
    else {
        type = FundingType::FundingUnknown;
    }

    return type;
}

Card::CVCCheck Card::cvcCheckType(const QString &name)
{
    CVCCheck type = CVCCheck::CVCCheckUnknown;
    if (name == "pass") {
        type = CVCCheck::CVCCheckPass;
    }
    else if (name == "fail") {
        type = CVCCheck::CVCCheckFail;
    }
    else if (name == "unavailable") {
        type = CVCCheck::CVCCheckUnavailable;
    }
    else if (name == "unchecked") {
        type = CVCCheck::CVCCheckUnchecked;
    }

    return type;
}

Card::TokenizationMethod Card::tokenizationMethodType(const QString &name)
{
    TokenizationMethod method = TokenizationUnknown;
    if (name == "apple_pay") {
        method = ApplePay;
    }
    else if (name == "android_pay") {
        method = GooglePay;
    }

    return method;
}

QString Card::tokenizationMethodName(TokenizationMethod method)
{
    QString name = "unknown";
    if (method == ApplePay) {
        name = "apple_pay";
    }
    else if (method == GooglePay) {
        name = "android_pay";
    }

    return name;
}

Card *Card::fromJson(const QVariantMap &data)
{
    Card *card = new Card();

    if (data.contains(FIELD_ADDRESS_CITY)) {
        card->setCity(data[FIELD_ADDRESS_CITY].toString());
    }

    if (data.contains(FIELD_BRAND)) {
        card->setBrand(cardBrandType(data[FIELD_BRAND].toString()));
    }

    if (data.contains(FIELD_COUNTRY)) {
        card->setCountry(data[FIELD_COUNTRY].toString());
    }

    if (data.contains(FIELD_CURRENCY)) {
        card->setCurrency(data[FIELD_CURRENCY].toString());
    }

    if (data.contains(FIELD_CVC_CHECK)) {
        card->setCVCCheck(cvcCheckType(data[FIELD_CVC_CHECK].toString()));
    }

    if (data.contains(FIELD_EXP_MONTH)) {
        card->setExpirationMonth(data[FIELD_EXP_MONTH].toInt());
    }

    if (data.contains(FIELD_EXP_YEAR)) {
        card->setExpirationYear(data[FIELD_EXP_YEAR].toInt());
    }

    if (data.contains(FIELD_FINGERPRINT)) {
        card->setFingerprint(data[FIELD_FINGERPRINT].toString());
    }

    if (data.contains(FIELD_FUNDING)) {
        card->setFunding(fundingType(data[FIELD_FUNDING].toString()));
    }

    if (data.contains(FIELD_ID)) {
        card->setCardID(data[FIELD_ID].toString());
    }

    if (data.contains(FIELD_LAST4)) {
        card->setLastFourDigits(data[FIELD_LAST4].toString());
    }

    if (data.contains(FIELD_METADATA)) {
        card->setMetaData(data[FIELD_METADATA].toMap());
    }

    if (data.contains(FIELD_NAME)) {
        card->setName(data[FIELD_NAME].toString());
    }

    if (data.contains(FIELD_TOKENIZATION_METHOD)) {
        card->setTokenizationMethod(tokenizationMethodType(data[FIELD_TOKENIZATION_METHOD].toString()));
    }

    Address *addr = Address::fromJson(data, FIELD_ADDRESS_PREFIX);
    card->setAddress(addr);
    addr->deleteLater();

    return card;
}

Card *Card::fromString(const QString &dataStr)
{
    return fromJson(Utils::toVariantMap(dataStr));
}

QString Card::cvcCheckName(CVCCheck type)
{
    QString name = "unknown";
    if (type == CVCCheck::CVCCheckPass) {
        name = "pass";
    }
    else if (type == CVCCheck::CVCCheckFail) {
        name = "fail";
    }
    else if (type == CVCCheck::CVCCheckUnavailable) {
        name = "unavailable";
    }
    else if (type == CVCCheck::CVCCheckUnchecked) {
        name = "unchecked";
    }

    return name;
}

void Card::setCardID(const QString &id)
{
    const bool changed = m_CardID != id;
    if (changed) {
        m_CardID = id;
        emit cardIDChanged();
    }
}

QVector<QString> Card::prefixes(CardBrand brand) const
{
    QVector<QString> numberPrefixes;

    if (brand == CardBrand::AmericanExpress) {
        numberPrefixes = QVector<QString> {"34", "37"};
    }
    else if (brand == CardBrand::Discover) {
        numberPrefixes = QVector<QString> {"60", "62", "64", "65"};
    }
    else if (brand == CardBrand::JCB) {
        numberPrefixes = QVector<QString> {"35"};
    }
    else if (brand == CardBrand::DinersClub) {
        numberPrefixes = QVector<QString> {
            "300", "301", "302", "303", "304",
            "305", "309", "36", "38", "39"
        };
    }
    else if (brand == CardBrand::Visa) {
        numberPrefixes = QVector<QString> {"4"};
    }
    else if (brand == CardBrand::MasterCard) {
        numberPrefixes = QVector<QString> {
            "2221", "2222", "2223", "2224",
            "2225", "2226", "2227", "2228",
            "2229", "223", "224", "225",
            "226", "227", "228", "229",
            "23", "24", "25", "26",
            "270", "271", "2720", "50",
            "51", "52", "53", "54",
            "55", "67"
        };
    }

    return numberPrefixes;
}

int Card::maxCardNumberLenght(CardBrand brand) const
{
    // This is the standard one.
    int length = 16;

    if (brand == CardBrand::AmericanExpress) {
        length = 15;
    }
    else if (brand == CardBrand::DinersClub) {
        length = 14;
    }

    return length;
}

void Card::setCVCCheck(CVCCheck check)
{
    const bool changed = m_CVCCheck != check;
    if (changed) {
        m_CVCCheck = check;
        emit cvcCheckChanged();
    }
}

void Card::updateCardBrand()
{
    setBrand(possibleCardBrand());
}

}
