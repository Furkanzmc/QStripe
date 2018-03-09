#include "QStripe/Stripe.h"

namespace QStripe
{

QString Stripe::m_PublishableKey = "";
QString Stripe::m_SecretKey = "";
QString Stripe::m_APIVersion = "";

Stripe::Stripe(QObject *parent)
    : QObject(parent)
    , m_Customers()
    , m_NetworkUtils()
{

}

QString Stripe::publishableKey()
{
    return m_PublishableKey;
}

void Stripe::setPublishableKey(const QString &key)
{
    const bool changed = key != m_PublishableKey;
    if (changed) {
        m_PublishableKey = key;
        emit publishableKeyChanged();
    }
}

QString Stripe::secretKey()
{
    return m_SecretKey;
}

void Stripe::setSecretKey(const QString &key)
{
    const bool changed = key != m_SecretKey;
    if (changed) {
        m_SecretKey = key;
        emit secretKeyChanged();
    }
}

QString Stripe::apiVersion() const
{
    return m_APIVersion;
}

void Stripe::setApiVersion(const QString &version)
{
    const bool changed = version != m_APIVersion;
    if (changed) {
        m_PublishableKey = version;
        emit apiVersionChanged();
    }
}

QQmlListProperty<Customer> Stripe::customers()
{
    return QQmlListProperty<Customer>(this, this, &Stripe::appendCustomer, &Stripe::customerCount, &Stripe::customer, &Stripe::clearCustomers);
}

void Stripe::appendCustomer(Customer *customer)
{
    m_Customers.append(customer);
}

int Stripe::customerCount() const
{
    return m_Customers.count();
}

Customer *Stripe::customer(int index) const
{
    return m_Customers.at(index);
}

void Stripe::clearCustomers()
{
    return m_Customers.clear();
}

void Stripe::updateVersionHeader()
{
    m_NetworkUtils.setHeader("Stripe-Version", m_APIVersion);
}

void Stripe::updatePublishableKeyHeader()
{
    m_NetworkUtils.setHeader("Authorization", "Bearer " + m_PublishableKey);
}

void Stripe::appendCustomer(QQmlListProperty<Customer> *list, Customer *customer)
{
    reinterpret_cast<Stripe *>(list->data)->appendCustomer(customer);
}

int Stripe::customerCount(QQmlListProperty<Customer> *list)
{
    return reinterpret_cast<Stripe *>(list->data)->customerCount();
}

Customer *Stripe::customer(QQmlListProperty<Customer> *list, int index)
{
    return reinterpret_cast<Stripe *>(list->data)->customer(index);
}

void Stripe::clearCustomers(QQmlListProperty<Customer> *list)
{
    reinterpret_cast<Stripe *>(list->data)->clearCustomers();
}

}
