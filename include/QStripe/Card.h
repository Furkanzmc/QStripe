#pragma once
#include <QObject>
#include <QVector>

namespace QStripe
{

class Card : public QObject
{
    Q_OBJECT

public:
    static const QString FIELD_OBJECT;
    static const QString FIELD_ADDRESS_CITY;
    static const QString FIELD_ADDRESS_COUNTRY;

    static const QString FIELD_ADDRESS_LINE1;
    static const QString FIELD_ADDRESS_LINE1_CHECK;
    static const QString FIELD_ADDRESS_LINE2;

    static const QString FIELD_ADDRESS_STATE;
    static const QString FIELD_ADDRESS_ZIP;
    static const QString FIELD_ADDRESS_ZIP_CHECK;

    static const QString FIELD_BRAND;
    static const QString FIELD_COUNTRY;
    static const QString FIELD_CURRENCY;

    static const QString FIELD_CUSTOMER;
    static const QString FIELD_CVC_CHECK;
    static const QString FIELD_EXP_MONTH;

    static const QString FIELD_EXP_YEAR;
    static const QString FIELD_FINGERPRINT;
    static const QString FIELD_FUNDING;

    static const QString FIELD_NAME;
    static const QString FIELD_LAST4;
    static const QString FIELD_ID;

    static const QString FIELD_TOKENIZATION_METHOD;

    enum CardBrand {
        AmericanExpress,
        Discover,
        JCB,
        DinersClub,
        Visa,
        MasterCard,
        Unknown
    };

    enum FundingType {
        FundingCredit,
        FundingDebit,
        FundingPrePaid,
        FundingUnknown
    };

public:
    explicit Card(QObject *parent = nullptr);

private:
    /**
     * @brief Returns the card number prefixes for the brand.
     * Card number prefixes are based on http://en.wikipedia.org/wiki/Bank_card_number#Issuer_identification_number_.28IIN.29
     * @return QVector<QString>
     */
    QVector<QString> prefixes(CardBrand brand) const;

    /**
     * @brief Returns the max card number length based on the brand.
     * @param brand
     * @return int
     */
    int maxCardNumberLenght(CardBrand brand) const;

    /**
     * @brief Returns the name of the brand.
     * @param brand
     * @return QString
     */
    QString cardBrandName(CardBrand brand) const;

    /**
     * @brief Returns the CardBrand enum from the name.
     * @param name
     * @return CardBrand
     */
    CardBrand cardBrandType(const QString &name);

    /**
     * @brief Returns the string representation of the funding type.
     * @param type
     * @return QString
     */
    QString fundingTypeString(FundingType type) const;

    /**
     * @brief Returns the FundingType enum for the given name.
     * @param name
     * @return FundingType
     */
    FundingType fundingType(const QString &name) const;
};

}
