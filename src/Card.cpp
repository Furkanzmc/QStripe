#include "QStripe/Card.h"

namespace QStripe
{

const QString Card::FIELD_OBJECT = "object";
const QString Card::FIELD_ADDRESS_CITY = "address_city";
const QString Card::FIELD_ADDRESS_COUNTRY = "address_country";

const QString Card::FIELD_ADDRESS_LINE1 = "address_line1";
const QString Card::FIELD_ADDRESS_LINE1_CHECK = "address_line1_check";
const QString Card::FIELD_ADDRESS_LINE2 = "address_line2";

const QString Card::FIELD_ADDRESS_STATE = "address_state";
const QString Card::FIELD_ADDRESS_ZIP = "address_zip";
const QString Card::FIELD_ADDRESS_ZIP_CHECK = "address_zip_check";

const QString Card::FIELD_BRAND = "brand";
const QString Card::FIELD_COUNTRY = "country";
const QString Card::FIELD_CURRENCY = "currency";

const QString Card::FIELD_CUSTOMER = "customer";
const QString Card::FIELD_CVC_CHECK = "cvc_check";
const QString Card::FIELD_EXP_MONTH = "exp_month";

const QString Card::FIELD_EXP_YEAR = "exp_year";
const QString Card::FIELD_FINGERPRINT = "fingerprint";
const QString Card::FIELD_FUNDING = "funding";

const QString Card::FIELD_NAME = "name";
const QString Card::FIELD_LAST4 = "last4";
const QString Card::FIELD_ID = "id";

const QString Card::FIELD_TOKENIZATION_METHOD = "tokenization_method";

Card::Card(QObject *parent)
    : QObject(parent)
{

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

QString Card::cardBrandName(CardBrand brand) const
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

QString Card::fundingTypeString(FundingType type) const
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

Card::FundingType Card::fundingType(const QString &name) const
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

}
