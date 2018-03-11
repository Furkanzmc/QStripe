#include "QStripe/Customer.h"
// Qt
#include <QUrlQuery>
// QStripe
#include "QStripe/Utils.h"
#include "QStripe/Stripe.h"

namespace QStripe
{

const QString Customer::FIELD_ID = "id";
const QString Customer::FIELD_OBJECT = "object";
const QString Customer::FIELD_DEFAULT_SOURCE = "default_source";

const QString Customer::FIELD_SHIPPING = "shipping";
const QString Customer::FIELD_SOURCES = "sources";
const QString Customer::FIELD_EMAIL = "email";

const QString Customer::FIELD_DESCRIPTION = "description";
const QString Customer::FIELD_CURRENCY = "currency";
const QString Customer::FIELD_METADATA = "metadata";

const QString Customer::FIELD_DELETED = "deleted";

Customer::Customer(QObject *parent)
    : QObject(parent)
    , m_CustomerID("")
    , m_DefaultSource("")
    , m_Email("")
    , m_Description("")
    , m_Currency("")
    , m_Metadata()
    , m_ShippingInformation()
    , m_IsDeleted(false)
    , m_NetworkUtils()
    , m_Error()
    , m_Cards()
{
}

QString Customer::customerID() const
{
    return m_CustomerID;
}

QString Customer::defaultSource() const
{
    return m_DefaultSource;
}

void Customer::setDefaultSource(const QString &source)
{
    const bool changed = m_DefaultSource != source;
    if (changed) {
        m_DefaultSource = source;
        emit defaultSourceChanged();
    }
}

QString Customer::email() const
{
    return m_Email;
}

void Customer::setEmail(const QString &email)
{
    const bool changed = m_Email != email;
    if (changed) {
        m_Email = email;
        emit emailChanged();
    }
}

QString Customer::description() const
{
    return m_Description;
}

void Customer::setDescription(const QString &description)
{
    const bool changed = m_Description != description;
    if (changed) {
        m_Description = description;
        emit descriptionChanged();
    }
}

QString Customer::currency() const
{
    return m_Currency;
}

void Customer::setCurrency(const QString &currency)
{
    const bool changed = m_Currency != currency;
    if (changed) {
        m_Currency = currency;
        emit currencyChanged();
    }
}

QVariantMap Customer::metadata() const
{
    return m_Metadata;
}

void Customer::setMetadata(const QVariantMap &metadata)
{
    const bool changed = m_Metadata != metadata;
    if (changed) {
        m_Metadata = metadata;
        emit metadataChanged();
    }
}

ShippingInformation *Customer::shippingInformation()
{
    return &m_ShippingInformation;
}

const ShippingInformation *Customer::shippingInformation() const
{
    return &m_ShippingInformation;
}

bool Customer::deleted() const
{
    return m_IsDeleted;
}

void Customer::setShippingInformation(const ShippingInformation *shippingInformation)
{
    // TODO: Check for content equality instead of memory location.
    const bool changed = m_ShippingInformation.name() != shippingInformation->name() ||
                         m_ShippingInformation.phone() != shippingInformation->phone() ||
                         (*m_ShippingInformation.address()) != (*shippingInformation->address());
    if (changed) {
        m_ShippingInformation.set(shippingInformation);
        emit shippingInformationChanged();
    }
}

QVariantMap Customer::json(bool omitEmpty) const
{
    QVariantMap data;

    if (customerID().length() > 0) {
        data[FIELD_ID] = customerID();
    }

    if ((omitEmpty && m_Currency.length() > 0) || omitEmpty == false) {
        data[FIELD_CURRENCY] = m_Currency;
    }

    if ((omitEmpty && m_DefaultSource.length() > 0) || omitEmpty == false) {
        data[FIELD_DEFAULT_SOURCE] = m_DefaultSource;
    }

    if ((omitEmpty && m_ShippingInformation.phone().length() > 0 && m_ShippingInformation.name().length() > 0) || omitEmpty == false) {
        data[FIELD_SHIPPING] = m_ShippingInformation.json();
    }

    if ((omitEmpty && m_Email.length() > 0) || omitEmpty == false) {
        data[FIELD_EMAIL] = m_Email;
    }

    if ((omitEmpty && m_Description.length() > 0) || omitEmpty == false) {
        data[FIELD_DESCRIPTION] = m_Description;
    }

    for (auto it = m_Metadata.constBegin(); it != m_Metadata.constEnd(); it++) {
        const QString key = FIELD_METADATA + "[" + it.key() + "]";
        const QVariant &value = it.value();

        if (value.type() == QVariant::String) {
            data[key] = value.toString();
        }
        else if (value.type() == QVariant::Int) {
            data[key] = value.toInt();
        }
        else if (value.type() == QVariant::Int) {
            data[key] = value.toInt();
        }
        else if (value.type() == QVariant::Map) {
            qWarning() << "Do not put Map in metadata.";
        }
    }

    return data;
}

QString Customer::jsonString(bool omitEmpty) const
{
    return Utils::toJsonString(json(omitEmpty));
}

Customer *Customer::fromJson(const QVariantMap &data)
{
    Customer *customer = new Customer();

    if (data.contains(FIELD_CURRENCY)) {
        customer->setCurrency(data[FIELD_CURRENCY].toString());
    }

    if (data.contains(FIELD_ID)) {
        customer->setCustomerID(data[FIELD_ID].toString());
    }

    if (data.contains(FIELD_DEFAULT_SOURCE)) {
        customer->setDefaultSource(data[FIELD_DEFAULT_SOURCE].toString());
    }

    if (data.contains(FIELD_SHIPPING)) {
        ShippingInformation *shipping = ShippingInformation::fromJson(data[FIELD_SHIPPING].toMap());
        customer->setShippingInformation(shipping);
        shipping->deleteLater();
    }

    if (data.contains(FIELD_EMAIL)) {
        customer->setEmail(data[FIELD_EMAIL].toString());
    }

    if (data.contains(FIELD_DESCRIPTION)) {
        customer->setDescription(data[FIELD_DESCRIPTION].toString());
    }

    if (data.contains(FIELD_METADATA)) {
        customer->setMetadata(data[FIELD_METADATA].toMap());
    }

    if (data.contains(FIELD_DELETED)) {
        customer->setDeleted(data[FIELD_DELETED].toBool());
    }

    return customer;
}

Customer *Customer::fromString(const QString &dataStr)
{
    return fromJson(Utils::toVariantMap(dataStr));
}

void Customer::set(const Customer *other)
{
    Q_ASSERT(other != nullptr);

    setCustomerID(other->customerID());
    setDefaultSource(other->defaultSource());
    setEmail(other->email());

    setDescription(other->description());
    setCurrency(other->currency());
    setMetadata(other->metadata());

    setShippingInformation(other->shippingInformation());
}

bool Customer::create()
{
    if (m_CustomerID.length() > 0) {
        return false;
    }

    auto callback = [this](const Response & response) {
        QVariantMap data = Utils::toVariantMap(response.data);
        if (response.httpStatus == NetworkUtils::HttpStatusCodes::HTTP_200) {
            Customer *customer = fromJson(data);
            set(customer);
            customer->deleteLater();
            emit created();
        }
        else {
            qDebug() << "[ERROR] Error occurred while creating the customer.";
            m_Error.set(data, response.httpStatus, response.networkError);
            emit errorOccurred(&m_Error);
        }
    };

    m_NetworkUtils.setHeader("Authorization", "Bearer " + Stripe::secretKey());
    if (Stripe::apiVersion().length() > 0) {
        m_NetworkUtils.setHeader("Stripe-Version", Stripe::apiVersion());
    }

    QVariantMap data = json();
    // currency and default_source should be removed.
    data.remove(FIELD_CURRENCY);
    if (m_DefaultSource.length() == 0) {
        data.remove(FIELD_DEFAULT_SOURCE);
    }

    m_NetworkUtils.sendPost(getURL(), data, callback);
    return true;
}

bool Customer::update()
{
    if (m_CustomerID.length() == 0) {
        return false;
    }

    auto callback = [this](const Response & response) {
        QVariantMap data = Utils::toVariantMap(response.data);
        if (response.httpStatus == NetworkUtils::HttpStatusCodes::HTTP_200) {
            Customer *customer = fromJson(data);
            set(customer);
            customer->deleteLater();
            emit updated();
        }
        else {
            qDebug() << "[ERROR] Error occurred while updating the customer.";
            m_Error.set(data, response.httpStatus, response.networkError);
            emit errorOccurred(&m_Error);
        }
    };

    m_NetworkUtils.setHeader("Authorization", "Bearer " + Stripe::secretKey());
    if (Stripe::apiVersion().length() > 0) {
        m_NetworkUtils.setHeader("Stripe-Version", Stripe::apiVersion());
    }

    QVariantMap data = json();
    // currency and default_source should be removed.
    data.remove(FIELD_CURRENCY);
    data.remove(FIELD_ID);
    if (m_DefaultSource.length() == 0) {
        data.remove(FIELD_DEFAULT_SOURCE);
    }

    m_NetworkUtils.sendPost(getURL(m_CustomerID), data, callback);
    return true;
}

bool Customer::deleteCustomer()
{
    if (m_CustomerID.length() == 0) {
        return false;
    }

    auto callback = [this](const Response & response) {
        QVariantMap data = Utils::toVariantMap(response.data);
        if (response.httpStatus == NetworkUtils::HttpStatusCodes::HTTP_200) {
            m_CustomerID = "";
            emit customerDeleted();
        }
        else {
            qDebug() << "[ERROR] Error occurred while deleting the customer.";
            m_Error.set(data, response.httpStatus, response.networkError);
            emit errorOccurred(&m_Error);
        }
    };

    m_NetworkUtils.setHeader("Authorization", "Bearer " + Stripe::secretKey());
    if (Stripe::apiVersion().length() > 0) {
        m_NetworkUtils.setHeader("Stripe-Version", Stripe::apiVersion());
    }

    m_NetworkUtils.sendDelete(getURL(m_CustomerID), callback);
    return true;
}

void Customer::clear()
{
    m_CustomerID.clear();
    m_DefaultSource.clear();
    m_Email.clear();

    m_Description.clear();
    m_Currency.clear();
    m_Metadata.clear();

    m_ShippingInformation.clear();
    emit cleared();
}

QQmlListProperty<Card> Customer::cards()
{
    return QQmlListProperty<Card>(this, this, &Customer::appendCard, &Customer::cardCount, &Customer::card, &Customer::clearCards);
}

void Customer::appendCard(Card *customer)
{
    m_Cards.append(customer);
}

int Customer::cardCount() const
{
    return m_Cards.count();
}

Card *Customer::card(int index) const
{
    return m_Cards.at(index);
}

void Customer::clearCards()
{
    return m_Cards.clear();
}

const Error *Customer::lastError() const
{
    return &m_Error;
}

QString Customer::getURL(const QString &customerID)
{
    return "https://api.stripe.com/v1/customers" + (customerID.length() > 0 ? "/" + customerID : "");
}

void Customer::setCustomerID(const QString &id)
{
    const bool changed = m_CustomerID != id;
    if (changed) {
        m_CustomerID = id;
        emit customerIDChanged();
    }
}

void Customer::setDeleted(bool deleted)
{
    m_IsDeleted = deleted;
}

void Customer::appendCard(QQmlListProperty<Card> *list, Card *card)
{
    reinterpret_cast<Customer *>(list->data)->appendCard(card);
}

int Customer::cardCount(QQmlListProperty<Card> *list)
{
    return reinterpret_cast<Customer *>(list->data)->cardCount();
}

Card *Customer::card(QQmlListProperty<Card> *list, int index)
{
    return reinterpret_cast<Customer *>(list->data)->card(index);
}

void Customer::clearCards(QQmlListProperty<Card> *list)
{
    reinterpret_cast<Customer *>(list->data)->clearCards();
}

}
