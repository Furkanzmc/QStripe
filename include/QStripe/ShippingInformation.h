#pragma once
#include <QObject>
// Stripe
#include "Address.h"

namespace QStripe
{

class ShippingInformation : public QObject
{
    Q_OBJECT

    Q_PROPERTY(QString name READ name WRITE setName NOTIFY nameChanged)
    Q_PROPERTY(QString phone READ phone WRITE setPhone NOTIFY phoneChanged)
    Q_PROPERTY(Address *address READ address WRITE setAddress NOTIFY addressChanged)

public:
    static const QString FIELD_ADDRESS;
    static const QString FIELD_NAME;
    static const QString FIELD_PHONE;

public:
    explicit ShippingInformation(QObject *parent = nullptr);

    /**
     * @brief Returns name.
     * @return QString
     */
    QString name() const;

    /**
     * @brief Set the name to the given name.
     * @param name
     */
    void setName(const QString &name);

    /**
     * @brief Returns phone.
     * @return QString
     */
    QString phone() const;

    /**
     * @brief Set the phone to the given phone.
     * @param phone
     */
    void setPhone(const QString &phone);

    /**
     * @brief Returns address.
     * @return Address
     */
    Address *address();
    const Address *address() const;

    /**
     * @brief Set the address to the given address.
     * @param name
     */
    void setAddress(const Address *addr);

    /**
     * @brief Returns the QVariantMap representation of the current object.
     * @return QVariantMap
     */
    QVariantMap json() const;

    /**
     * @brief Returns the json string that represents the current object. Empty fields will have empty strings.
     * @return QString
     */
    QString jsonString() const;

    /**
     * @brief Copy another address to this one. This will copy the address.
     * @param other
     */
    Q_INVOKABLE void set(const ShippingInformation *other);

    /**
     * @brief Returns an ShippingInformation instance from a json representation. If the json data cannot be parsed, returns an ShippingInformation
     * Address instance.
     * @param data
     * @return Address
     */
    static ShippingInformation *fromJson(const QVariantMap &data);

    /**
     * @brief Returns an ShippingInformation instance from a json string.
     * Address instance.
     * @param dataStr
     * @return Address
     */
    static ShippingInformation *fromString(const QString &dataStr);

signals:
    /**
     * @brief Emitted when name property changes.
     */
    void nameChanged();

    /**
     * @brief Emitted when phone property changes.
     */
    void phoneChanged();

    /**
     * @brief Emitted when address property changes.
     */
    void addressChanged();

private:
    QString m_Name, m_Phone;
    Address m_Address;
};

}
