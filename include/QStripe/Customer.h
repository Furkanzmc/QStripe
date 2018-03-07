#pragma once
#include <QObject>

namespace QStripe
{

class Customer : public QObject
{
    Q_OBJECT

    Q_PROPERTY(QString customerID READ customerID NOTIFY customerIDChanged)

public:
    explicit Customer(QObject *parent = nullptr);

    /**
     * @brief Returns the customer ID. The customerID property cannot be changed from the outside. If you want to copy another customer objects, use the
     * `Customer::set()` method.
     * @return QString
     */
    QString customerID() const;

signals:
    /**
     * @brief Emitted when customer ID changes.
     */
    void customerIDChanged();

private:
    static const QString FIELD_ID;
    static const QString FIELD_OBJECT;
    static const QString FIELD_DEFAULT_SOURCE;

    static const QString FIELD_SHIPPING;
    static const QString FIELD_SOURCES;
    static const QString FIELD_DATA;

    static const QString FIELD_HAS_MORE;
    static const QString FIELD_TOTAL_COUNT;
    static const QString FIELD_URL;

    static const QString VALUE_LIST;
    static const QString VALUE_CUSTOMER;
    QString m_CustomerID;
};

}
