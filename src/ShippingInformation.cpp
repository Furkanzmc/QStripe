#include "QStripe/ShippingInformation.h"
#include "QStripe/Utils.h"

namespace QStripe
{

const QString ShippingInformation::FIELD_ADDRESS = "address";
const QString ShippingInformation::FIELD_NAME = "name";
const QString ShippingInformation::FIELD_PHONE = "phone";

ShippingInformation::ShippingInformation(QObject *parent)
    : QObject(parent)
    , m_Name("")
    , m_Phone("")
    , m_Address(new Address(this))
{

}

QString ShippingInformation::name() const
{
    return m_Name;
}

void ShippingInformation::setName(const QString &name)
{
    const bool changed = name != m_Name;
    if (changed) {
        m_Name = name;
        emit nameChanged();
    }
}

QString ShippingInformation::phone() const
{
    return m_Phone;
}

void ShippingInformation::setPhone(const QString &phone)
{
    const bool changed = phone != m_Phone;
    if (changed) {
        m_Phone = phone;
        emit phoneChanged();
    }
}

Address *ShippingInformation::address()
{
    return m_Address;
}

void ShippingInformation::setAddress(Address *addr)
{
    const bool changed = addr != m_Address;
    if (changed) {
        m_Address = addr;
        emit addressChanged();
    }
}

QVariantMap ShippingInformation::json() const
{
    QVariantMap data;
    data[FIELD_ADDRESS] = m_Address != nullptr ? m_Address->json() : QVariant::fromValue(nullptr);
    data[FIELD_NAME] = name();
    data[FIELD_PHONE] = phone();

    return data;
}

QString ShippingInformation::jsonString() const
{
    return Utils::toJsonString(json());
}

void ShippingInformation::set(ShippingInformation &other)
{
    setName(other.name());
    setPhone(other.phone());
    if (other.address()) {
        if (m_Address == nullptr) {
            m_Address = new Address(this);
        }

        m_Address->set(*other.address());
    }
}

ShippingInformation *ShippingInformation::fromJson(const QString &dataStr)
{
    const QVariantMap data = Utils::toVariantMap(dataStr);
    ShippingInformation *shipping = new ShippingInformation();

    if (data.contains(FIELD_ADDRESS)) {
        Address *addr = new Address();
        addr->set(*Address::fromJson(Utils::toJsonString(data[FIELD_ADDRESS].toMap())));
        shipping->setAddress(addr);
    }

    if (data.contains(FIELD_NAME)) {
        shipping->setName(data[FIELD_NAME].toString());
    }

    if (data.contains(FIELD_PHONE)) {
        shipping->setPhone(data[FIELD_PHONE].toString());
    }

    return shipping;
}

}
