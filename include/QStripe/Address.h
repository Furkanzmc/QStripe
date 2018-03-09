#pragma once
#include <QObject>
#include <QVariantMap>

namespace QStripe
{

class Address : public QObject
{
    Q_OBJECT

    Q_PROPERTY(QString country READ country WRITE setCountry NOTIFY countryChanged)
    Q_PROPERTY(QString state READ state WRITE setState NOTIFY stateChanged)
    Q_PROPERTY(QString city READ city WRITE setCity NOTIFY cityChanged)

    Q_PROPERTY(QString lineOne READ lineOne WRITE setLineOne NOTIFY lineOneChanged)
    Q_PROPERTY(QString lineTwo READ lineTwo WRITE setLineTwo NOTIFY lineTwoChanged)
    Q_PROPERTY(QString postalCode READ postalCode WRITE setPostalCode NOTIFY postalCodeChanged)

    Q_PROPERTY(QVariantMap json READ json CONSTANT)
    Q_PROPERTY(QString jsonString READ jsonString CONSTANT)

public:
    // 2 Character Country Code
    static const QString FIELD_COUNTRY;
    static const QString FIELD_CITY;
    static const QString FIELD_STATE;

    static const QString FIELD_LINE_1;
    static const QString FIELD_LINE_2;
    static const QString FIELD_POSTAL_CODE;

    static const QString FIELD_ZIP_CHECK;

    enum ZipCheck {
        ZipCheckPass,
        ZipCheckFail,
        ZipCheckUnavailable,
        ZipCheckUnchecked,
        ZipCheckUnknown
    };
    Q_ENUM(ZipCheck);

public:
    explicit Address(QObject *parent = nullptr);

    /**
     * @brief Returns true If the two is identical.
     * @param a1
     * @param a2
     * @return bool
     */
    bool operator==(const Address &a2) const;

    /**
     * @brief Returns false If the two is identical.
     * @param a1
     * @param a2
     * @return bool
     */
    bool operator!=(const Address &a2) const;

    /**
     * @brief Returns the country name.
     * @return QString
     */
    QString country() const;

    /**
     * @brief Set the country to the given value.
     * @param country
     */
    void setCountry(const QString &country);

    /**
     * @brief Returns the state name.
     * @return QString
     */
    QString state() const;

    /**
     * @brief Set the state to the given value.
     * @param state
     */
    void setState(const QString &state);

    /**
     * @brief Returns the city name.
     * @return QString
     */
    QString city() const;

    /**
     * @brief Set the city to the given value.
     * @param city
     */
    void setCity(const QString &city);

    /**
     * @brief Returns the line one address.
     * @return QString
     */
    QString lineOne() const;

    /**
     * @brief Set the line one to the given value.
     * @param line
     */
    void setLineOne(const QString &line);

    /**
     * @brief Returns the line two address.
     * @return QString
     */
    QString lineTwo() const;

    /**
     * @brief Set the line two to the given value.
     * @param line
     */
    void setLineTwo(const QString &line);

    /**
     * @brief Returns the postal code.
     * @return QString
     */
    QString postalCode() const;

    /**
     * @brief Set the postal code to the given value.
     * @param code
     */
    void setPostalCode(const QString &code);

    /**
     * @brief Returns the postal code check status of this address if it exists.
     * @return ZipCheck
     */
    ZipCheck zipCheck() const;

    /**
     * @brief Sets the zip check.
     * @param check
     */
    void setZipCheck(const ZipCheck &check);

    /**
     * @brief Returns the QVariantMap representation of the current object.
     * @param prefix This is useful when you are adding the address to a card or customer. The prefix is prepended to the key of each item.
     * @return QVariantMap
     */
    QVariantMap json(const QString &prefix = "") const;

    /**
     * @brief Returns the json string that represents the current object. Empty fields will have empty strings.
     * @param prefix See documentation for Address::json()
     * @return QString
     */
    QString jsonString(const QString &prefix = "") const;

    /**
     * @brief Copy another address to this one.
     * @param other
     */
    Q_INVOKABLE void set(const Address *other);

    /**
     * @brief Returns an Address instance from a json representation. If the json data cannot be parsed, returns an empty Address instance.
     * @param prefix This is usefull If you are creating an address from the output of a, say, Customer object that has the `address_` prefix
     * for address fields.
     * @param data
     * @return Address
     */
    Q_INVOKABLE static Address *fromJson(const QVariantMap &data, const QString &prefix = "");

    /**
     * @brief Returns an Address instance from a json string. See Address::json().
     * @param prefix See Address::json()
     * @param dataStr
     * @return Address
     */
    Q_INVOKABLE static Address *fromString(const QString &dataStr, const QString &prefix = "");

    /**
     * @brief Returns teh ZipCheck enum from the name.
     * @param name
     * @return ZipCheck
     */
    static ZipCheck zipCheckType(const QString &name);

    /**
     * @brief Returns the zip check name for the given type. The string representation for ZipCheck::ZipCheckUnknown is `unknown`.
     * @param check
     * @return QString
     */
    static QString zipCheckName(ZipCheck check);

signals:
    /**
     * @brief Emitted when country changes.
     */
    void countryChanged();

    /**
     * @brief Emitted when state changes.
     */
    void stateChanged();

    /**
     * @brief Emitted when city changes.
     */
    void cityChanged();

    /**
     * @brief Emitted when line one changes.
     */
    void lineOneChanged();

    /**
     * @brief Emitted when line two changes.
     */
    void lineTwoChanged();

    /**
     * @brief Emitted when postal code changes.
     */
    void postalCodeChanged();

    /**
     * @brief Emitted when zip check changes.
     */
    void zipCheckChanged();

private:
    QString m_Country,
            m_State,
            m_City,
            m_LineOne,
            m_LineTwo,
            m_PostalCode;
    ZipCheck m_ZipCheck;
};

}
