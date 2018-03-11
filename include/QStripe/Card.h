#pragma once
#include <QObject>
#include <QVector>
// QStripe
#include "Address.h"

namespace QStripe
{

class Card : public QObject
{
    Q_OBJECT

    Q_PROPERTY(QString cardID READ cardID NOTIFY cardIDChanged)
    Q_PROPERTY(QString city READ city WRITE setCity NOTIFY cityChanged)
    Q_PROPERTY(Address *address READ address WRITE setAddress NOTIFY addressChanged)

    Q_PROPERTY(CardBrand brand READ brand WRITE setBrand NOTIFY brandChanged)
    Q_PROPERTY(QString country READ country WRITE setCountry NOTIFY countryChanged)
    Q_PROPERTY(QString currency READ currency WRITE setCurrency NOTIFY currencyChanged)

    Q_PROPERTY(CVCCheck cvcCheck READ cvcCheck WRITE setCVCCheck NOTIFY cvcCheckChanged)
    Q_PROPERTY(int expirationMonth READ expirationMonth WRITE setExpirationMonth NOTIFY expirationMonthChanged)
    Q_PROPERTY(int expirationYear READ expirationYear WRITE setExpirationYear NOTIFY expirationYearChanged)

    Q_PROPERTY(QString fingerprint READ fingerprint WRITE setFingerprint NOTIFY fingerprintChanged)
    Q_PROPERTY(FundingType funding READ funding WRITE setFunding NOTIFY fundingChanged)
    Q_PROPERTY(QString name READ name WRITE setName NOTIFY nameChanged)

    Q_PROPERTY(QString lastFourDigits READ lastFourDigits WRITE setLastFourDigits NOTIFY lastFourDigitsChanged)
    Q_PROPERTY(TokenizationMethod tokenizationMethod READ tokenizationMethod WRITE setTokenizationMethod NOTIFY tokenizationMethodChanged)
    Q_PROPERTY(QVariantMap metaData READ metaData WRITE setMetaData NOTIFY metaDataChanged)

    Q_PROPERTY(QString cardNumber READ cardNumber WRITE setCardNumber NOTIFY cardNumberChanged)
    Q_PROPERTY(QVariantMap json READ json CONSTANT)
    Q_PROPERTY(QString jsonString READ jsonString CONSTANT)

    Q_PROPERTY(QString cvc READ cvc WRITE setCvc NOTIFY cvcChanged)
    Q_PROPERTY(QString brandName READ brandName CONSTANT)
    Q_PROPERTY(CardBrand possibleCardBrand READ possibleCardBrand CONSTANT)

    Q_PROPERTY(bool validCardLenght READ validCardLenght CONSTANT)
    Q_PROPERTY(bool validCardNumber READ validCardNumber CONSTANT)

public:
    static const QString FIELD_ID;
    static const QString FIELD_OBJECT;
    static const QString FIELD_ADDRESS_CITY;

    static const QString FIELD_ADDRESS_PREFIX;
    static const QString FIELD_BRAND;
    static const QString FIELD_COUNTRY;

    static const QString FIELD_CURRENCY;
    static const QString FIELD_CVC_CHECK;
    static const QString FIELD_EXP_MONTH;

    static const QString FIELD_EXP_YEAR;
    static const QString FIELD_FINGERPRINT;
    static const QString FIELD_FUNDING;

    static const QString FIELD_NAME;
    static const QString FIELD_LAST4;
    static const QString FIELD_TOKENIZATION_METHOD;

    static const QString FIELD_METADATA;
    static const QString FIELD_SOURCE;

    enum CardBrand {
        AmericanExpress,
        Discover,
        JCB,
        DinersClub,
        Visa,
        MasterCard,
        Unknown
    };
    Q_ENUM(CardBrand);

    enum FundingType {
        FundingCredit,
        FundingDebit,
        FundingPrePaid,
        FundingUnknown
    };
    Q_ENUM(FundingType);

    enum CVCCheck {
        CVCCheckPass,
        CVCCheckFail,
        CVCCheckUnavailable,
        CVCCheckUnchecked,
        CVCCheckUnknown
    };
    Q_ENUM(CVCCheck);

    enum TokenizationMethod {
        ApplePay,
        GooglePay,
        TokenizationUnknown
    };
    Q_ENUM(TokenizationMethod);

public:
    explicit Card(QObject *parent = nullptr);

    /**
     * @brief The default value is empty string.
     * @return QString
     */
    QString cardID() const;

    /**
     * @brief Returns the city.
     * @return QString
     */
    QString city() const;

    /**
     * @brief Set city name.
     * @param ct
     */
    void setCity(const QString &ct);

    /**
     * @brief Returns the current address object.
     * @return Address*
     */
    Address *address();
    const Address *address() const;

    /**
     * @brief Sett the current address. The object is copied.
     * @param addr
     */
    void setAddress(const Address *addr);

    /**
     * @brief Returns the card brand.
     * @return CardBrand
     */
    CardBrand brand() const;

    /**
     * @brief Returns the brand name of the current brand.
     * @return QString
     */
    QString brandName() const;

    /**
     * @brief Set the card brand. But note that this value will change when you set the card number.
     * @param cardBrand
     */
    void setBrand(const CardBrand &cardBrand);

    /**
     * @brief Returns the country.
     * @return  QString
     */
    QString country() const;

    /**
     * @brief Set the country.
     * @param country
     */
    void setCountry(const QString &country);

    /**
     * @brief Returns the 3 digit currency.
     * @return QString
     */
    QString currency() const;

    /**
     * @brief Sets the 3 digit currency.
     * @param currency
     */
    void setCurrency(const QString &currency);

    /**
     * @brief Returns the cvc check status. CVCCheck can only be set internally.
     * @return CVCCheck
     */
    CVCCheck cvcCheck() const;

    /**
     * @brief Returns the expiration month.
     * @return int
     */
    int expirationMonth() const;

    /**
     * @brief Set the expiration month. This cannot be bigger than 12.
     * @param month
     */
    void setExpirationMonth(int month);

    /**
     * @brief Returns the expiration year. This can be a 2 digit or a 4 digit number.
     * @return int
     */
    int expirationYear() const;

    /**
     * @brief Set the expiration yer. This can be a 2 digit or a 4 digit number.
     * @param year
     */
    void setExpirationYear(int year);

    /**
     * @brief Returns the fingerprint.
     * @return QString
     */
    QString fingerprint() const;

    /**
     * @brief Set the fingerprint.
     * @param fingerprint
     */
    void setFingerprint(const QString &fingerprint);

    /**
     * @brief Returns the funding type.
     * @return FundingType
     */
    FundingType funding() const;

    /**
     * @brief Set funding type.
     * @param type
     */
    void setFunding(const FundingType &type);

    /**
     * @brief Returns the cardholder name.
     * @return QString
     */
    QString name() const;

    /**
     * @brief Set the cardholder name.
     * @param name
     */
    void setName(const QString &name);

    /**
     * @brief Returns the last four digits. Last four digits can be saved in a PCI compliant way.
     * @return QString
     */
    QString lastFourDigits() const;

    /**
     * @brief Set the last four digits. This value change when you set a valid card number.
     * @param lastDigits
     */
    void setLastFourDigits(const QString &lastDigits);

    /**
     * @brief Returns the tokenization method.
     * @return TokenizationMethod
     */
    TokenizationMethod tokenizationMethod() const;

    /**
     * @brief Set tokenization method.
     * @param method
     */
    void setTokenizationMethod(const TokenizationMethod &method);

    /**
     * @brief Returns the metadata.
     * @return QVariantMap
     */
    QVariantMap metaData() const;

    /**
     * @brief Set the metadata.
     * @param data
     */
    void setMetaData(const QVariantMap &data);

    /**
     * @brief Returns the card number. If this card instance was created from JSON, this string will be empty since this information is not saved on Stripe.
     * @return QString
     */
    QString cardNumber() const;

    /**
     * @brief Set card number. This will also cause the last four digits to be changed as well. The card brand will also be reset based on the new number.
     * @param number
     */
    void setCardNumber(const QString &number);

    /**
     * @brief Returns the CVC number. This will not be present in the json representation.
     * @return QString
     */
    QString cvc() const;

    /**
     * @brief Sets the CVC number.
     * @param cvcNumber
     */
    void setCvc(const QString &cvcNumber);

    /**
     * @brief Returns the json representation of this instance. This will not include the CVC number or the card number.
     * To create a token, use `QStripe::Stripe::createToken()`
     * @return QVariantMap
     */
    QVariantMap json() const;

    /**
     * @brief Returns the json representation of this instance in string.
     * @return QString
     */
    QString jsonString() const;

    /**
     * @brief Returns the possible card brand based on the card number. This method will be automatically called whenever the card number changes to a valid
     * one. The check can be done If the card number contains at least 4 characters.
     * @return CardBrand
     */
    CardBrand possibleCardBrand() const;

    /**
     * @brief Returns true If the card number length is valid for the current card brand. If the card brand is unknown, it will return false.
     * @return bool
     */
    bool validCardLenght() const;

    /**
     * @brief Validates the card number based on the Luhn Algorithm and the length of the card number.
     * @return bool
     */
    bool validCardNumber() const;

    /**
     * @brief Expiration date can be between 1 and 12. Otherwise this will return false.
     * @return bool
     */
    bool validExpirationMonth() const;

    /**
     * @brief Expiration date can be between 1 and 12. Otherwise this will return false.
     * @return bool
     */
    bool validExpirationYear() const;

    /**
     * @brief Validates both the month and year of expiration. The year should not be in the past.
     * as well.
     * @return bool
     */
    bool validExpirationDate() const;

    /**
     * @brief Validates the CVC number. The CVC number must be of enough length and a postive number.
     * @return bool
     */
    bool validCVC() const;

    /**
     * @brief Returns true If all of the details of the card is valid.
     * @return bool
     */
    bool validCard() const;

    /**
     * @brief Copies the contents of other to this instance.
     * @param other
     */
    Q_INVOKABLE void set(const Card &other);

    /**
     * @brief Returns the name of the brand.
     * @param brand
     * @return QString
     */
    static QString cardBrandName(CardBrand brand);

    /**
     * @brief Returns the CardBrand enum from the name.
     * @param name
     * @return CardBrand
     */
    static CardBrand cardBrandType(const QString &name);

    /**
     * @brief Returns the string representation of the funding type.
     * @param type
     * @return QString
     */
    static QString fundingTypeString(FundingType type);

    /**
     * @brief Returns the FundingType enum for the given name.
     * @param name
     * @return FundingType
     */
    static FundingType fundingType(const QString &name);

    /**
     * @brief Returns the CVCCheck type from the name.
     * @param name
     * @return CVCCheck
     */
    static CVCCheck cvcCheckType(const QString &name);

    /**
     * @brief Returns the name of the cvc check type.
     * @param type
     * @return QString
     */
    static QString cvcCheckName(CVCCheck type);

    /**
     * @brief Returns the tokenization type from its string representation.
     * @param name
     * @return TokenizationMethod
     */
    static TokenizationMethod tokenizationMethodType(const QString &name);

    /**
     * @brief Returns the string representation of the tokenization method.
     * @param method
     * @return QString
     */
    static QString tokenizationMethodName(TokenizationMethod method);

    /**
     * @brief Returns a Card instance from the json string.
     * @param data
     * @return Card*
     */
    Q_INVOKABLE static Card *fromJson(const QVariantMap &data);

    /**
     * @brief Returns a Card instance from the json string.
     * @param dataStr
     * @return Card*
     */
    Q_INVOKABLE static Card *fromString(const QString &dataStr);

    /**
     * @brief The token ID created for the card. This will be automatically set when you create the card. Thus the set method for this property is private.
     * @return QString
     */
    QString source() const;

signals:
    /**
     * @brief Emitted when the card ID changes.
     */
    void cardIDChanged();

    /**
     * @brief Emitted when the city changes.
     */
    void cityChanged();

    /**
     * @brief Emitted when the address changes.
     */
    void addressChanged();

    /**
     * @brief Emitted when the brand changes.
     */
    void brandChanged();

    /**
     * @brief Emitted when the country changes.
     */
    void countryChanged();

    /**
     * @brief Emitted when the currency changes.
     */
    void currencyChanged();

    /**
     * @brief Emitted when the cvc check changes.
     */
    void cvcCheckChanged();

    /**
     * @brief Emitted when the expiration month changes.
     */
    void expirationMonthChanged();

    /**
     * @brief Emitted when the expiration year changes.
     */
    void expirationYearChanged();

    /**
     * @brief Emitted when the fingerprint changes.
     */
    void fingerprintChanged();

    /**
     * @brief Emitted when the funding changes.
     */
    void fundingChanged();

    /**
     * @brief Emitted when the cardholder name changes.
     */
    void nameChanged();

    /**
     * @brief Emitted when the last four digits changes. This will be also emitted when a valid card number is set.
     */
    void lastFourDigitsChanged();

    /**
     * @brief Emitted when the tokenization method changes.
     */
    void tokenizationMethodChanged();

    /**
     * @brief Emitted when the metadata changes.
     */
    void metaDataChanged();

    /**
     * @brief Emitted when the card number changes.
     */
    void cardNumberChanged();

    /**
     * @brief Emitted when the CVC number changes.
     */
    void cvcChanged();

private:
    QString m_CardID;
    QString m_City;
    Address m_Address;

    CardBrand m_Brand;
    // This is the two letter country code that this card belongs to.
    QString m_Country;
    QString m_Currency;

    CVCCheck m_CVCCheck;
    int m_ExpirationMonth;
    // This can be a 2 digit or 4 digit number.
    int m_ExpirationYear;

    QString m_Fingerprint;
    FundingType m_FundingType;
    QString m_Name;

    QString m_LastFourDigits;
    TokenizationMethod m_TokenizationMethod;
    QVariantMap m_MetaData;

    QString m_CardNumber;
    QString m_CVC;
    QString m_Source;

private:
    /**
     * @brief Card ID can only be changed internally.
     * @param id
     */
    void setCardID(const QString &id);

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
     * @brief Returns the maximum CVC number length for the given brand.
     * @param brand
     * @return int
     */
    int maxCVCLenght(CardBrand brand) const;

    /**
     * @brief Set cvc check.
     * @param check
     */
    void setCVCCheck(CVCCheck check);

    /**
     * @brief This is connected to the cardNumberChanged() signal. And it udates the brand.
     */
    void updateCardBrand();

    /**
     * @brief Set the source ID for this card. This will be set when the credit card is created.
     * @param src
     */
    void setSource(const QString &src);
};

}
