#include "QStripe/Card.h"

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
{

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
    m_City = ct;
}

Address *Card::address()
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

void Card::setBrand(const CardBrand &cardBrand)
{
    m_Brand = cardBrand;
}

QString Card::country() const
{
    return m_Country;
}

void Card::setCountry(const QString &country)
{
    m_Country = country;
}

QString Card::currency() const
{
    return m_Currency;
}

void Card::setCurrency(const QString &currency)
{
    m_Currency = currency;
}

Card::CVCCheck Card::cvcCheck() const
{
    return m_CVCCheck;
}

void Card::setCVCCheck(CVCCheck check)
{
    m_CVCCheck = check;
}

unsigned int Card::expirationMonth() const
{
    return m_ExpirationMonth;
}

void Card::setExpirationMonth(unsigned int month)
{
    m_ExpirationMonth = month;
}

unsigned int Card::expirationYear() const
{
    return m_ExpirationYear;
}

void Card::setExpirationYear(unsigned int year)
{
    m_ExpirationYear = year;
}

QString Card::fingerprint() const
{
    return m_Fingerprint;
}

void Card::setFingerprint(const QString &fingerprint)
{
    m_Fingerprint = fingerprint;
}

Card::FundingType Card::funding() const
{
    return m_FundingType;
}

void Card::setFunding(const FundingType &type)
{
    m_FundingType = type;
}

QString Card::name() const
{
    return m_Name;
}

void Card::setName(const QString &name)
{
    m_Name = name;
}

QString Card::lastFourDigits() const
{
    return m_LastFourDigits;
}

void Card::setLastFourDigits(const QString &lastDigits)
{
    m_LastFourDigits = lastDigits;
}

Card::TokenizationMethod Card::tokenizationMethod() const
{
    return m_TokenizationMethod;
}

void Card::setTokenizationMethod(const TokenizationMethod &method)
{
    m_TokenizationMethod = method;
}

QVariantMap Card::metaData() const
{
    return m_MetaData;
}

void Card::setMetaData(const QVariantMap &data)
{
    m_MetaData = data;
}

QString Card::cardNumber() const
{
    return m_CardNumber;
}

void Card::setCardNumber(const QString &number)
{
    m_CardNumber = number;
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

}
