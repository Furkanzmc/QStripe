#pragma once
#include <QObject>
#include <QQmlListProperty>
#include <QVector>
// Stripe
#include "Customer.h"
#include "NetworkUtils.h"

namespace QStripe
{

class Stripe : public QObject
{
    Q_OBJECT

    Q_PROPERTY(QString publishableKey READ publishableKey WRITE setPublishableKey NOTIFY publishableKeyChanged)
    Q_PROPERTY(QString secretKey READ secretKey WRITE setSecretKey NOTIFY secretKeyChanged)
    Q_PROPERTY(QString apiVersion READ apiVersion WRITE setApiVersion NOTIFY apiVersionChanged)

    Q_PROPERTY(QQmlListProperty<Customer> customers READ customers)

public:
    explicit Stripe(QObject *parent = nullptr);

    /**
     * @brief Returns the publishable key.
     * @return QString
     */
    QString publishableKey() const;

    /**
     * @brief Sets the current publishable key. This change does not effect the currently running requests. But any request after this change will use this key.
     * @param key
     */
    void setPublishableKey(const QString &key);

    /**
     * @brief Returns the secret key.
     * @return
     */
    QString secretKey() const;

    /**
     * @brief Sets the current secret key. This change does not effect the currently running requests. But any request after this change will use this key.
     * @param key
     */
    void setSecretKey(const QString &key);

    /**
     * @brief The current API version. The default value is empty and uses the latest API version.
     * @return QString
     */
    QString apiVersion() const;

    /**
     * @brief Sets the current api version to the given one. This change does not effect the currently running requests. But any request after this change will
     * use this key.
     * @param version
     */
    void setApiVersion(const QString &version);

    /**
     * @brief Returns the list of customer currently attached to this instance.
     * @return QQmlListProperty<Customer>
     */
    QQmlListProperty<Customer> customers();

    /**
     * @brief Appends a new customer to the list.
     * @param customer
     */
    void appendCustomer(Customer *customer);

    /**
     * @brief Returns the number of customers that belong to this instance.
     * @return int
     */
    int customerCount() const;

    /**
     * @brief Returns the customer.
     * @param index
     * @return Customer
     */
    Customer *customer(int index) const;

    /**
     * @brief Clears all of the customer instances that belong to this instance.
     */
    void clearCustomers();

signals:
    /**
     * @brief Emitted when the `publishableKey` property changes.
     */
    void publishableKeyChanged();

    /**
     * @brief Emitted when the `secretKey` property changes.
     */
    void secretKeyChanged();

    /**
     * @brief Emitted when the `apiVersion` property changes.
     */
    void apiVersionChanged();

private:
    QString m_PublishableKey,
            m_SecretKey,
            m_APIVersion;
    QVector<Customer *> m_Customers;
    NetworkUtils m_NetworkUtils;

private:
    /**
     * @brief This is connected to the apiVersionChanged() signal. When the API version changes, the header will also change.
     */
    void updateVersionHeader();

    /**
     * @brief This is connected to the publishableKeyChanged() signal. When the publishable key changes, the header will also change.
     */
    void updatePublishableKeyHeader();

    /**
     * @brief Append function for QQmlListProperty.
     * @param list
     * @param customer
     */
    static void appendCustomer(QQmlListProperty<Customer> *list, Customer *customer);

    /**
     * @brief Count function for QQmlListProperty.
     * @param list
     * @return
     */
    static int customerCount(QQmlListProperty<Customer> *list);

    /**
     * @brief At function for QQmlListProperty.
     * @param list
     * @param index
     * @return
     */
    static Customer *customer(QQmlListProperty<Customer> *list, int index);

    /**
     * @brief Clear function for QQmlListProperty.
     * @param list
     */
    static void clearCustomers(QQmlListProperty<Customer> *list);
};

}
