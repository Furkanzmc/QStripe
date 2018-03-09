#include "QStripe/Customer.h"
#include "QStripe/Utils.h"
#include "QDebug"

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

Customer::Customer(QObject *parent)
    : QObject(parent)
    , m_CustomerID("")
    , m_DefaultSource("")
    , m_Email("")
    , m_Description("")
    , m_Currency("")
    , m_Metadata()
    , m_ShippingInformation()
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

QVariantMap Customer::json() const
{
    QVariantMap data;

    if (customerID().length() > 0) {
        data[FIELD_ID] = customerID();
    }

    data[FIELD_CURRENCY] = currency();
    data[FIELD_DEFAULT_SOURCE] = defaultSource();

    data[FIELD_SHIPPING] = m_ShippingInformation.json();
    data[FIELD_EMAIL] = email();
    data[FIELD_DESCRIPTION] = description();

    data[FIELD_CURRENCY] = currency();
    data[FIELD_METADATA] = metadata();

    return data;
}

QString Customer::jsonString() const
{
    return Utils::toJsonString(json());
}

Customer *Customer::fromJson(const QVariantMap &data)
{
    Customer *customer = new Customer();

    if (data.contains(FIELD_CURRENCY)) {
        customer->setCurrency(data[FIELD_CURRENCY].toString());
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

void Customer::setCustomerID(const QString &id)
{
    const bool changed = m_CustomerID != id;
    if (changed) {
        m_CustomerID = id;
        emit customerIDChanged();
    }
}

}
