#pragma once
// Qt
#include <QObject>
// QStripe
#include "Address.h"

namespace QStripe
{

class ShippingInformation : public QObject
{
    Q_OBJECT

    Q_PROPERTY(QString name READ name WRITE setName NOTIFY nameChanged)
    Q_PROPERTY(QString phone READ phone WRITE setPhone NOTIFY phoneChanged)
    Q_PROPERTY(QStripe::Address *address READ address WRITE setAddress NOTIFY addressChanged)

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

    /**
     * @brief Set the address to the given address.
     * @param name
     */
    void setAddress(Address *addr);

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
    Q_INVOKABLE void set(ShippingInformation *other);

    /**
     * @brief Resets every property to its default state. When the clearing is complete, `cleared()` signal will be emitted.
     * The changes in the properties does NOT emit the related signals.
     */
    Q_INVOKABLE void clear();

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

    /**
     * @brief Emitted after the instance has been cleared.
     */
    void cleared();

private:
    QString m_Name, m_Phone;
    Address m_Address;
};

}
