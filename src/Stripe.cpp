#include "QStripe/Stripe.h"
// QStripe
#include "QStripe/Customer.h"
#include "QStripe/Utils.h"

namespace QStripe
{

QString Stripe::m_PublishableKey = "";
QString Stripe::m_SecretKey = "";
QString Stripe::m_APIVersion = "";

Stripe::Stripe(QObject *parent)
    : QObject(parent)
    , m_NetworkUtils()
    , m_Error()
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
    }
}

QString Stripe::apiVersion()
{
    return m_APIVersion;
}

void Stripe::setApiVersion(const QString &version)
{
    const bool changed = version != m_APIVersion;
    if (changed) {
        m_PublishableKey = version;
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

bool Stripe::fetchCustomer(const QString &customerID)
{
    if (customerID.length() == 0) {
        return false;
    }

    m_NetworkUtils.setHeader("Authorization", "Bearer " + Stripe::secretKey());
    if (Stripe::apiVersion().length() > 0) {
        m_NetworkUtils.setHeader("Stripe-Version", Stripe::apiVersion());
    }

    auto callback = [this](const Response & response) {
        QVariantMap data = Utils::toVariantMap(response.data);
        if (response.httpStatus == NetworkUtils::HttpStatusCodes::HTTP_200) {
            Customer *customer = Customer::fromJson(data);
            customer->setParent(this);
            emit customerFetched(customer);
        }
        else {
            qDebug() << "[ERROR] Error occurred while fetching the customer.";
            m_Error.set(data, response.httpStatus, response.networkError);
            emit errorOccurred(&m_Error);
        }
    };

    m_NetworkUtils.sendGet(Customer::getURL(customerID), callback);
    return true;
}

bool Stripe::fetchCard(const QString &customerID, const QString &cardID)
{
    if (cardID.length() == 0) {
        return false;
    }

    if (customerID.length() == 0) {
        return false;
    }

    m_NetworkUtils.setHeader("Authorization", "Bearer " + Stripe::secretKey());
    if (Stripe::apiVersion().length() > 0) {
        m_NetworkUtils.setHeader("Stripe-Version", Stripe::apiVersion());
    }

    auto callback = [this](const Response & response) {
        QVariantMap data = Utils::toVariantMap(response.data);
        if (response.httpStatus == NetworkUtils::HttpStatusCodes::HTTP_200) {
            Card *card = Card::fromJson(data);
            card->setParent(this);
            emit cardFetched(card);
        }
        else {
            qDebug() << "[ERROR] Error occurred while fetching the card.";
            m_Error.set(data, response.httpStatus, response.networkError);
            emit errorOccurred(&m_Error);
        }
    };

    m_NetworkUtils.sendGet(Card::getURL(customerID, cardID), callback);
    return true;
}

const Error *Stripe::lastError() const
{
    return &m_Error;
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
