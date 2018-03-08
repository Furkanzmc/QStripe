#pragma once
#include <QObject>
// QStripe
#include "ShippingInformation.h"

namespace QStripe
{

class Customer : public QObject
{
    Q_OBJECT

    Q_PROPERTY(QString customerID READ customerID NOTIFY customerIDChanged)
    Q_PROPERTY(QString defaultSource READ defaultSource WRITE setDefaultSource NOTIFY defaultSourceChanged)
    Q_PROPERTY(QString email READ email WRITE setEmail NOTIFY emailChanged)

    Q_PROPERTY(QString description READ description WRITE setDescription NOTIFY descriptionChanged)
    Q_PROPERTY(QString currency READ currency WRITE setCurrency NOTIFY currencyChanged)
    Q_PROPERTY(QVariantMap metadata READ metadata WRITE setMetadata NOTIFY metadataChanged)

    Q_PROPERTY(ShippingInformation *shippingInformation READ shippingInformation WRITE setShippingInformation NOTIFY shippingInformationChanged)

public:
    static const QString FIELD_ID;
    static const QString FIELD_OBJECT;
    static const QString FIELD_DEFAULT_SOURCE;

    static const QString FIELD_SHIPPING;
    static const QString FIELD_SOURCES;
    static const QString FIELD_EMAIL;

    static const QString FIELD_DESCRIPTION;
    static const QString FIELD_CURRENCY;
    static const QString FIELD_METADATA;

public:
    explicit Customer(QObject *parent = nullptr);

    /**
     * @brief Returns the customer ID. The customerID property cannot be changed from the outside. If you want to copy another customer objects, use the
     * `Customer::set()` method. The default value is empty string. It cannot be set from the outside.
     * @return QString
     */
    QString customerID() const;

    /**
     * @brief Returns the default source for this customer. The default value is empty string.
     * @return QString
     */
    QString defaultSource() const;

    /**
     * @brief Set the default customer.
     * @param source
     */
    void setDefaultSource(const QString &source);

    /**
     * @brief Return the email of the current customer. The default value is empty string.
     * @return QString
     */
    QString email() const;

    /**
     * @brief Set the email.
     * @param email
     */
    void setEmail(const QString &email);

    /**
     * @brief Returns the description for this customer. The default value is empty string.
     * @return QString
     */
    QString description() const;

    /**
     * @brief Set the description.
     * @param description
     */
    void setDescription(const QString &description);

    /**
     * @brief Returns the currency. The default value is empty string.
     * @return QString
     */
    QString currency() const;

    /**
     * @brief Set currency.
     * @param currency
     */
    void setCurrency(const QString &currency);

    /**
     * @brief Returns the metadata set for this customer. Metadata is used to store custom informormation on a customer.
     * @return QVariantMap
     */
    QVariantMap metadata() const;

    /**
     * @brief Set metadata.
     * @param metadata
     */
    void setMetadata(const QVariantMap &metadata);

    /**
     * @brief Returns the shipping information, The defaul is an empty shipping information.
     * @return ShippingInformation
     */
    ShippingInformation *shippingInformation() const;

    /**
     * @brief Sett shipping information.
     * @param shippingInformation
     */
    void setShippingInformation(ShippingInformation *shippingInformation);

    /**
     * @brief Returns a json representation of this object. If the customerID is empty, it omits that field.
     * @return QVariantMap
     */
    QVariantMap json() const;

    /**
     * @brief Returns a json string.
     * @return QString
     */
    QString jsonStr() const;

    /**
     * @brief Returns a Customer instance from the given dataStr.
     * @param dataStr
     * @return Customer *
     */
    static Customer *fromJson(const QString &dataStr);

    /**
     * @brief Copies the contents of other to this instance.
     * @param other
     */
    Q_INVOKABLE void set(const Customer *other);

signals:
    /**
     * @brief Emitted when customer ID changes.
     */
    void customerIDChanged();

    /**
     * @brief Emitted when default source changes.
     */
    void defaultSourceChanged();

    /**
     * @brief Emitted when email changes.
     */
    void emailChanged();

    /**
     * @brief Emitted when description changes.
     */
    void descriptionChanged();

    /**
     * @brief Emitted when currency changes.
     */
    void currencyChanged();

    /**
     * @brief Emitted when metadata changes.
     */
    void metadataChanged();

    /**
     * @brief Emitted when shipping changes.
     */
    void shippingInformationChanged();

private:
    QString m_CustomerID,
            m_DefaultSource,
            m_Email,
            m_Description,
            m_Currency;

    QVariantMap m_Metadata;
    ShippingInformation *m_ShippingInformation;

private:
    /**
     * @brief Customer ID cannot be changed from the outside.
     * @param id
     */
    void setCustomerID(const QString &id);
};

}
