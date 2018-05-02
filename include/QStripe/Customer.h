#pragma once
// Qt
#include <QQmlListProperty>
#include <QObject>
#include <QVector>
// QStripe
#include "ShippingInformation.h"
#include "NetworkUtils.h"
#include "Error.h"
#include "Card.h"

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

    Q_PROPERTY(QStripe::ShippingInformation *shippingInformation READ shippingInformation WRITE setShippingInformation NOTIFY shippingInformationChanged)
    Q_PROPERTY(bool deleted READ deleted CONSTANT)
    Q_PROPERTY(QQmlListProperty<QStripe::Card> cards READ cards)

    Q_CLASSINFO("DefaultProperty", "cards")

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

    static const QString FIELD_DELETED;

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
    const ShippingInformation *shippingInformation() const;
    ShippingInformation *shippingInformation();

    /**
     * @brief This will be true when a deleted Customer is fetched. The defaul value is false and this will NOT be affected by the call of `deleteCustomer()`.
     * @return bool
     */
    bool deleted() const;

    /**
     * @brief Sett shipping information.
     * @param shippingInformation
     */
    void setShippingInformation(ShippingInformation *shippingInformation);

    /**
     * @brief Returns a json representation of this object. If the customerID is empty, it omits that field.
     * @param omitEmpty If set to true, the empty fields will not present in the json.
     * @return QVariantMap
     */
    Q_INVOKABLE QVariantMap json(bool omitEmpty = false) const;

    /**
     * @brief Returns a json string.
     * @param omitEmpty If set to true, the empty fields will not present in the json.
     * @return QString
     */
    Q_INVOKABLE QString jsonString(bool omitEmpty = false) const;

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
    Q_INVOKABLE void set(Customer *other);

    /**
     * @brief If this instance does not have an assosicated customer ID, you can create a new customer. When the customer is created, the customer ID of this
     * instance will change accordingly. If the customer instance does not have a valid ID, you can create the customer and this function will return true.
     * If the instance already has a customer ID, this will return false and do nothing. When the customer is created, `created()` signal will be emitted.
     * @return bool
     */
    Q_INVOKABLE bool create();

    /**
     * @brief If the customer instance has an ID, this method will send the current details of the instance and update the remote. If there's no customer ID
     * present, this method will return false. When the customer is updated, `updated()` signal will be emitted.
     * @return bool
     */
    Q_INVOKABLE bool update();

    /**
     * @brief If the customer instance has an ID, this method will send the current details of the instance and delete the remote. If there's no customer ID
     * present, this method will return false. When the customer is deleted, `customerDeleted()` signal will be emitted. When the customer is deleted, only the
     * customerID will be cleared, so you can use the same instance to create the customer again.
     * @return
     */
    Q_INVOKABLE bool deleteCustomer();

    /**
     * @brief Resets every property to its default state. When the clearing is complete, `cleared()` signal will be emitted.
     * The changes in the properties does NOT emit the related signals.
     */
    Q_INVOKABLE void clear();

    /**
     * @brief Returns the list of customer currently attached to this instance.
     * @return QQmlListProperty<cards>
     */
    QQmlListProperty<Card> cards();

    /**
     * @brief Appends a new customer to the list.
     * @param customer
     */
    void appendCard(Card *card);

    /**
     * @brief Returns the number of customers that belong to this instance.
     * @return int
     */
    int cardCount() const;

    /**
     * @brief Returns the customer.
     * @param index
     * @return Customer
     */
    Card *card(int index) const;

    /**
     * @brief Clears all of the customer instances that belong to this instance.
     */
    void clearCards();

    /**
     * @brief Returns the last ocurred error.
     * @return const Error *
     */
    Error *lastError();

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
     * @brief Emitted when the customer is deleted. Prior to emission of this signal, the contents of the instance will be cleared.
     */
    void customerDeleted();

    /**
     * @brief Emitted when a request to Stripe fails.
     * @param error
     */
    void errorOccurred(Error *error);

    /**
     * @brief Emitted when the instance has been cleared.
     */
    void cleared();

private:
    QString m_CustomerID,
            m_DefaultSource,
            m_Email,
            m_Description,
            m_Currency;

    QVariantMap m_Metadata;
    ShippingInformation m_ShippingInformation;
    bool m_IsDeleted;

    NetworkUtils m_NetworkUtils;
    Error m_Error;
    QVector<Card *> m_Cards;

private:
    /**
     * @brief Customer ID cannot be changed from the outside.
     * @param id
     */
    void setCustomerID(const QString &id);

    /**
     * @brief Deleted property can only be changed internally.
     * @param deleted
     */
    void setDeleted(bool deleted);

    /**
     * @brief Append function for QQmlListProperty.
     * @param list
     * @param card
     */
    static void appendCard(QQmlListProperty<Card> *list, Card *card);

    /**
     * @brief Count function for QQmlListProperty.
     * @param list
     * @return
     */
    static int cardCount(QQmlListProperty<Card> *list);

    /**
     * @brief At function for QQmlListProperty.
     * @param list
     * @param index
     * @return
     */
    static Card *card(QQmlListProperty<Card> *list, int index);

    /**
     * @brief Clear function for QQmlListProperty.
     * @param list
     */
    static void clearCards(QQmlListProperty<Card> *list);
};

}
