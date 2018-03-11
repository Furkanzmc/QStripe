#pragma once
#include <QObject>
#include <QDateTime>
#include <QVariantMap>

namespace QStripe
{

/**
 * @brief Token is a read-only class and it can only be created using `QStripe::Card::createToken()`. The token will always be attached to a Card so it does
 * not have the `card()` property.
 * The properties does not have a related changed signals.
 */
class Token : public QObject
{
    Q_OBJECT

    Q_PROPERTY(QVariantMap bankAccount READ bankAccount CONSTANT)
    Q_PROPERTY(QDateTime created READ created CONSTANT)

    Q_PROPERTY(QString tokenID READ tokenID CONSTANT)
    Q_PROPERTY(Type type READ type CONSTANT)
    Q_PROPERTY(bool liveMode READ liveMode CONSTANT)

    Q_PROPERTY(bool used READ used CONSTANT)
    Q_PROPERTY(QVariantMap json READ json CONSTANT)
    Q_PROPERTY(QString jsonString READ jsonString CONSTANT)

public:
    static const QString FIELD_BANK_ACCOUNT;
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
     * @brief Returns the token type.
     * @return
     */
    Type type() const;

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

    /**
     * @brief Returns a token instance from json. The parent of the token instance is not set. So you will be responsible for its destruction.
     * This function is invokable from QML.
     * @param data
     * @return Token *
     */
    Q_INVOKABLE static Token *fromJson(const QVariantMap &data);

    /**
     * @brief Parses the json string and returns a corresponding Token object. Internally, it calls `Token::fromJson()`. This function is invokable from QML.
     * @param data
     * @return Token *
     */
    Q_INVOKABLE static Token *fromString(const QString &data);

    /**
     * @brief Returns the json representation of this instance. This function is invokable from QML.
     * @return QVariantMap
     */
    QVariantMap json() const;

    /**
     * @brief Returns a json string from this instance.
     * @return QString
     */
    QString jsonString() const;

private:
    // FIXME: Create a seperate class for BankAccount.
    QVariantMap m_BankAccount;
    QDateTime m_Created;
    QString m_TokenID;

    Type m_Type;
    bool m_IsLiveMode;
    bool m_IsUsed;
};

}
