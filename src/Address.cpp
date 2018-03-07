#include "QStripe/Address.h"
#include "QStripe/Utils.h"

namespace QStripe
{

const QString Address::FIELD_COUNTRY = "country";
const QString Address::FIELD_CITY = "city";
const QString Address::FIELD_LINE_1 = "line1";

const QString Address::FIELD_LINE_2 = "line2";
const QString Address::FIELD_POSTAL_CODE = "postal_code";
const QString Address::FIELD_STATE = "state";

Address::Address(QObject *parent)
    : QObject(parent)
    , m_Country("")
    , m_State("")
    , m_City("")
    , m_LineOne("")
    , m_LineTwo("")
    , m_PostalCode("")
{

}

bool Address::operator==(const Address &a2) const
{
    bool equals = true;
    equals &= country() == a2.country();
    equals &= state() == a2.state();
    equals &= city() == a2.city();

    equals &= lineOne() == a2.lineOne();
    equals &= lineTwo() == a2.lineTwo();
    equals &= postalCode() == a2.postalCode();

    return equals;
}

bool Address::operator!=(const Address &a2) const
{
    return !(*this == a2);
}

QString Address::country() const
{
    return m_Country;
}

void Address::setCountry(const QString &country)
{
    const bool changed = country != m_Country;
    if (changed) {
        m_Country = country;
        emit countryChanged();
    }
}

QString Address::state() const
{
    return m_State;
}

void Address::setState(const QString &state)
{
    const bool changed = state != m_State;
    if (changed) {
        m_State = state;
        emit stateChanged();
    }
}

QString Address::city() const
{
    return m_City;
}

void Address::setCity(const QString &city)
{
    const bool changed = city != m_City;
    if (changed) {
        m_City = city;
        emit cityChanged();
    }
}

QString Address::lineOne() const
{
    return m_LineOne;
}

void Address::setLineOne(const QString &line)
{
    const bool changed = line != m_LineOne;
    if (changed) {
        m_LineOne = line;
        emit lineOneChanged();
    }
}

QString Address::lineTwo() const
{
    return m_LineTwo;
}

void Address::setLineTwo(const QString &line)
{
    const bool changed = line != m_LineTwo;
    if (changed) {
        m_LineTwo = line;
        emit lineTwoChanged();
    }
}

QString Address::postalCode() const
{
    return m_PostalCode;
}

void Address::setPostalCode(const QString &code)
{
    const bool changed = code != m_PostalCode;
    if (changed) {
        m_PostalCode = code;
        emit postalCodeChanged();
    }
}

QVariantMap Address::json() const
{
    QVariantMap data;
    data[FIELD_COUNTRY] = country();
    data[FIELD_CITY] = city();
    data[FIELD_STATE] = state();

    data[FIELD_LINE_1] = lineOne();
    data[FIELD_LINE_2] = lineTwo();
    data[FIELD_POSTAL_CODE] = postalCode();

    return data;
}

QString Address::jsonString() const
{
    return Utils::toJsonString(json());
}

void Address::set(const Address &other)
{
    this->setCountry(other.country());
    this->setState(other.state());
    this->setCity(other.city());

    this->setLineOne(other.lineOne());
    this->setLineTwo(other.lineTwo());
    this->setPostalCode(other.postalCode());
}

Address *Address::fromJson(const QString &dataStr)
{
    const QVariantMap data = Utils::toVariantMap(dataStr);

    Address *address = new Address();
    if (data.contains(FIELD_COUNTRY)) {
        address->setCountry(data[FIELD_COUNTRY].toString());
    }

    if (data.contains(FIELD_CITY)) {
        address->setCity(data[FIELD_CITY].toString());
    }

    if (data.contains(FIELD_STATE)) {
        address->setState(data[FIELD_STATE].toString());
    }

    if (data.contains(FIELD_LINE_1)) {
        address->setLineOne(data[FIELD_LINE_1].toString());
    }

    if (data.contains(FIELD_LINE_2)) {
        address->setLineTwo(data[FIELD_LINE_2].toString());
    }

    if (data.contains(FIELD_POSTAL_CODE)) {
        address->setPostalCode(data[FIELD_POSTAL_CODE].toString());
    }

    return address;
}

}
