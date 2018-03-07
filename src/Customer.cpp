#include "QStripe/Customer.h"

namespace QStripe
{

const QString Customer::FIELD_ID = "id";
const QString Customer::FIELD_OBJECT = "object";
const QString Customer::FIELD_DEFAULT_SOURCE = "default_source";
const QString Customer::FIELD_SHIPPING = "shipping";
const QString Customer::FIELD_SOURCES = "sources";
const QString Customer::FIELD_DATA = "data";
const QString Customer::FIELD_HAS_MORE = "has_more";
const QString Customer::FIELD_TOTAL_COUNT = "total_count";
const QString Customer::FIELD_URL = "url";
const QString Customer::VALUE_LIST = "list";
const QString Customer::VALUE_CUSTOMER = "customer";

Customer::Customer(QObject *parent)
    : QObject(parent)
    , m_CustomerID("")
{

}

QString Customer::customerID() const
{
    return m_CustomerID;
}

}
