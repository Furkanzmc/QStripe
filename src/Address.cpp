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

const QString Address::FIELD_ZIP_CHECK = "zip_check";

Address::Address(QObject *parent)
    : QObject(parent)
    , m_Country("")
    , m_State("")
    , m_City("")
    , m_LineOne("")
    , m_LineTwo("")
    , m_PostalCode("")
    , m_ZipCheck(ZipCheck::ZipCheckUnknown)
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

    equals &= zipCheck() == a2.zipCheck();

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

Address::ZipCheck Address::zipCheck() const
{
    return m_ZipCheck;
}

void Address::setZipCheck(const ZipCheck &check)
{
    const bool changed = check != m_ZipCheck;
    if (changed) {
        m_ZipCheck = check;
        emit zipCheckChanged();
    }
}

QVariantMap Address::json(const QString &prefix) const
{
    QVariantMap data;
    data[prefix + FIELD_COUNTRY] = country();
    data[prefix + FIELD_CITY] = city();
    data[prefix + FIELD_STATE] = state();

    data[prefix + FIELD_LINE_1] = lineOne();
    data[prefix + FIELD_LINE_2] = lineTwo();
    data[prefix + FIELD_POSTAL_CODE] = postalCode();
    data[prefix + FIELD_ZIP_CHECK] = zipCheckName(m_ZipCheck);

    return data;
}

QString Address::jsonString(const QString &prefix) const
{
    return Utils::toJsonString(json(prefix));
}

void Address::set(const Address *other)
{
    this->setCountry(other->country());
    this->setState(other->state());
    this->setCity(other->city());

    this->setLineOne(other->lineOne());
    this->setLineTwo(other->lineTwo());
    this->setPostalCode(other->postalCode());
}

void Address::clear()
{
    m_Country.clear();
    m_State.clear();
    m_City.clear();

    m_LineOne.clear();
    m_LineTwo.clear();
    m_PostalCode.clear();

    m_ZipCheck = ZipCheck::ZipCheckUnknown;
    emit cleared();
}

Address *Address::fromJson(const QVariantMap &data, const QString &prefix)
{
    Address *address = new Address();
    if (data.contains(prefix + FIELD_COUNTRY)) {
        address->setCountry(data[prefix + FIELD_COUNTRY].toString());
    }

    if (data.contains(prefix + FIELD_CITY)) {
        address->setCity(data[prefix + FIELD_CITY].toString());
    }

    if (data.contains(prefix + FIELD_STATE)) {
        address->setState(data[prefix + FIELD_STATE].toString());
    }

    if (data.contains(prefix + FIELD_LINE_1)) {
        address->setLineOne(data[prefix + FIELD_LINE_1].toString());
    }

    if (data.contains(prefix + FIELD_LINE_2)) {
        address->setLineTwo(data[prefix + FIELD_LINE_2].toString());
    }

    if (data.contains(prefix + FIELD_POSTAL_CODE)) {
        address->setPostalCode(data[prefix + FIELD_POSTAL_CODE].toString());
    }

    if (data.contains(prefix + FIELD_ZIP_CHECK)) {
        address->setZipCheck(address->zipCheckType(data[prefix + FIELD_ZIP_CHECK].toString()));
    }

    return address;
}

Address *Address::fromString(const QString &dataStr, const QString &prefix)
{
    return fromJson(Utils::toVariantMap(dataStr), prefix);
}

Address::ZipCheck Address::zipCheckType(const QString &name)
{
    ZipCheck check = ZipCheck::ZipCheckUnknown;
    if (name == "pass") {
        check = ZipCheck::ZipCheckPass;
    }
    else if (name == "fail") {
        check = ZipCheck::ZipCheckFail;
    }
    else if (name == "unchecked") {
        check = ZipCheck::ZipCheckUnchecked;
    }
    else if (name == "unavailable") {
        check = ZipCheck::ZipCheckUnavailable;
    }

    return check;
}

QString Address::zipCheckName(ZipCheck check)
{
    QString name = "unknown";
    if (check == ZipCheck::ZipCheckPass) {
        name = "pass";
    }
    else if (check == ZipCheck::ZipCheckFail) {
        name = "fail";
    }
    else if (check == ZipCheck::ZipCheckUnchecked) {
        name = "unchecked";
    }
    else if (check == ZipCheck::ZipCheckUnavailable) {
        name = "unavailable";
    }

    return name;
}

}
