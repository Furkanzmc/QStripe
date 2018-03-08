#pragma once
#include <QObject>
#include <QDateTime>
// QStripe
#include "Card.h"

namespace QStripe
{

/**
 * @brief Token is a read-only class and it can only be created using `QStripe::Stripe::createToken()`.
 * The properties does not have a related changed signals.
 */
class Token : public QObject
{
    Q_OBJECT

    Q_PROPERTY(QVariantMap bankAccount READ bankAccount CONSTANT)
    Q_PROPERTY(const Card *card READ card CONSTANT)
    Q_PROPERTY(QDateTime created READ created CONSTANT)

    Q_PROPERTY(QString tokenID READ tokenID CONSTANT)
    Q_PROPERTY(bool liveMode READ liveMode CONSTANT)
    Q_PROPERTY(bool used READ used CONSTANT)

public:
    static const QString FIELD_BANK_ACCOUNT;
    static const QString FIELD_CARD;
    static const QString FIELD_CREATED;

    static const QString FIELD_ID;
    static const QString FIELD_LIVEMODE;
    static const QString FIELD_TYPE;

    static const QString FIELD_USED;

    enum Type {
        TypeBankAccount,
        TypeCard,
        TypePII,
        TypeAccount,
        TypeUnknown // This does not exist in the API.
    };
    Q_ENUM(Type);

public:
    explicit Token(QObject *parent = nullptr);

    /**
     * @brief Returns the card that belongs to this token.
     * @return const Card *
     */
    const Card *card() const;

    /**
     * @brief Returns the bank account. In the future release this will be a class of its own.
     * @return QVariantMap
     */
    QVariantMap bankAccount() const;

    /**
     * @brief Returns the created time in UTC format.
     * @note When Qt converts the QDateTime to Date object, the timezone information is lost. (See https://bugreports.qt.io/browse/QTBUG-25262)
     * @return
     */
    QDateTime created() const;

    /**
     * @brief Returns the token ID.
     * @return QString
     */
    QString tokenID() const;

    /**
     * @brief Flag indicating whether the object exists in live mode or test mode.
     * @return bool
     */
    bool liveMode() const;

    /**
     * @brief Whether this token has already been used (tokens can be used only once).
     * @return bool
     */
    bool used() const;

    /**
     * @brief Returns the string representation of the given Type.
     * @param type
     * @return QString
     */
    static QString typeName(Type type);

    /**
     * @brief Returns the type from its string representation.
     * @param name
     * @return Type
     */
    static Type typeEnum(const QString &name);

private:
    // FIXME: Create a seperate class for BankAccount.
    QVariantMap m_BankAccount;
    Card m_Card;
    QDateTime m_Created;

    QString m_TokenID;
    bool m_IsLiveMode;
    bool m_IsUsed;
};

}
