#pragma once
#include <QObject>
// QStripe
#include "ShippingInformation.h"
#include "QStripe/NetworkUtils.h"
#include "QStripe/Error.h"

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
    ShippingInformation *shippingInformation();
    const ShippingInformation *shippingInformation() const;

    /**
     * @brief Sett shipping information.
     * @param shippingInformation
     */
    void setShippingInformation(const ShippingInformation *shippingInformation);

    /**
     * @brief Returns a json representation of this object. If the customerID is empty, it omits that field.
     * @return QVariantMap
     */
    QVariantMap json() const;

    /**
     * @brief Returns a json string.
     * @return QString
     */
    QString jsonString() const;

    /**
     * @brief Returns a Customer instance from the given data.
     * @param dataStr
     * @return Customer *
     */
    Q_INVOKABLE static Customer *fromJson(const QVariantMap &data);

    /**
     * @brief Returns a Customer instance from the given dataStr.
     * @param dataStr
     * @return Customer *
     */
    Q_INVOKABLE static Customer *fromString(const QString &dataStr);

    /**
     * @brief Copies the contents of other to this instance.
     * @param other
     */
    Q_INVOKABLE void set(const Customer *other);

    /**
     * @brief If this instance does not have an assosicated customer ID, you can create a new customer. When the customer is created, the customer ID of this
     * instance will change accordingly. If the customer instance does not have a valid ID, you can create the customer and this function will return true.
     * If the instance already has a customer ID, this will return false and do nothing. When the customer is created, `created()` signal will be emitted.
     * @return bool
     */
    bool create();

    /**
     * @brief If the customer instance has an ID, this method will send the current details of the instance and update the remote. If there's no customer ID
     * present, this method will return false. When the customer is updated, `updated()` signal will be emitted.
     * @return bool
     */
    bool update();

    /**
     * @brief Returns the last ocurred error.
     * @return const Error *
     */
    const Error *lastError() const;

    /**
     * @brief Returns the customers endpoint full URL.
     * @return QString
     */
    static QString getURL(const QString &customerID = "");

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

    /**
     * @brief Emitted when the customer object is created.
     */
    void created();

    /**
     * @brief Emitted when the customer is updated.
     */
    void updated();

    /**
     * @brief Emitted when a request to Stripe fails.
     * @param error
     */
    void errorOccurred(const Error *error);

private:
    QString m_CustomerID,
            m_DefaultSource,
            m_Email,
            m_Description,
            m_Currency;

    QVariantMap m_Metadata;
    ShippingInformation m_ShippingInformation;
    NetworkUtils m_NetworkUtils;

    Error m_Error;

private:
    /**
     * @brief Customer ID cannot be changed from the outside.
     * @param id
     */
    void setCustomerID(const QString &id);
};

}
