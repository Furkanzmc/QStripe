#include "QStripe/PaymentSource.h"

namespace QStripe
{

PaymentSource::PaymentSource(QObject *parent)
    : QObject(parent)
    , m_SourceID("")
{

}

QString PaymentSource::sourceID() const
{
    return m_SourceID;
}

void PaymentSource::setSourceID(const QString &id)
{
    const bool changed = id != m_SourceID;
    if (changed) {
        m_SourceID = id;
        emit sourceIDChanged();
    }
}

}
