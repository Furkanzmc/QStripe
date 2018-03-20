#include "QStripe/Token.h"
#include "QStripe/Utils.h"

namespace QStripe
{

const QString Token::FIELD_BANK_ACCOUNT = "bank_account";
const QString Token::FIELD_CREATED = "created";

const QString Token::FIELD_ID = "id";
const QString Token::FIELD_LIVEMODE = "livemode";
const QString Token::FIELD_TYPE = "type";

const QString Token::FIELD_USED = "used";

Token::Token(QObject *parent)
    : QObject(parent)
    , m_BankAccount()
    , m_Created()
    , m_TokenID("")
    , m_Type(TypeUnknown)
    , m_IsLiveMode(false)
    , m_IsUsed(false)
{

}

QVariantMap Token::bankAccount() const
{
    return m_BankAccount;
}

QDateTime Token::created() const
{
    return m_Created;
}

QString Token::tokenID() const
{
    return m_TokenID;
}

Token::Type Token::type() const
{
    return m_Type;
}

bool Token::liveMode() const
{
    return m_IsLiveMode;
}

bool Token::used() const
{
    return m_IsUsed;
}

void Token::clear()
{
    m_BankAccount.clear();
    m_Created = QDateTime();
    m_TokenID = "";

    m_Type = TypeUnknown;
    m_IsLiveMode = false;
    m_IsUsed = false;
}

QString Token::typeName(Type type)
{
    QString name = "unknown";

    if (type == Type::TypeBankAccount) {
        name = "bank_account";
    }
    else if (type == Type::TypeCard) {
        name = "card";
    }
    else if (type == Type::TypePII) {
        name = "pii";
    }
    else if (type == Type::TypeAccount) {
        name = "account";
    }

    return name;
}

Token::Type Token::typeEnum(const QString &name)
{
    Type type = Type::TypeUnknown;

    if (name == "bank_account") {
        type = Type::TypeBankAccount;
    }
    else if (name == "card") {
        type = Type::TypeCard;
    }
    else if (name == "pii") {
        type = Type::TypePII;
    }
    else if (name == "account") {
        type = Type::TypeAccount;
    }

    return type;
}

Token *Token::fromJson(const QVariantMap &data)
{
    Token *token = new Token();

    if (data.contains(FIELD_BANK_ACCOUNT)) {
        token->m_BankAccount = data[FIELD_BANK_ACCOUNT].toMap();
    }

    if (data.contains(FIELD_CREATED)) {
        token->m_Created = QDateTime::fromSecsSinceEpoch(data[FIELD_CREATED].toInt());
    }

    if (data.contains(FIELD_ID)) {
        token->m_TokenID = data[FIELD_ID].toString();
    }

    if (data.contains(FIELD_LIVEMODE)) {
        token->m_IsLiveMode = data[FIELD_LIVEMODE].toBool();
    }

    if (data.contains(FIELD_TYPE)) {
        token->m_Type = typeEnum(data[FIELD_TYPE].toString());
    }

    if (data.contains(FIELD_USED)) {
        token->m_IsUsed = data[FIELD_USED].toBool();
    }

    return token;
}

Token *Token::fromString(const QString &data)
{
    return fromJson(Utils::toVariantMap(data));
}

QString Token::getURL(const QString &tokenID)
{
    return "https://api.stripe.com/v1/tokens" + (tokenID.length() > 0 ? "/" + tokenID : "");
}

QVariantMap Token::json() const
{
    QVariantMap data;

    data[FIELD_BANK_ACCOUNT] = m_BankAccount;
    data[FIELD_CREATED] = m_Created.toSecsSinceEpoch();

    data[FIELD_ID] = m_TokenID;
    data[FIELD_LIVEMODE] = m_IsLiveMode;
    data[FIELD_TYPE] = typeName(m_Type);

    data[FIELD_USED] = m_IsUsed;

    return data;
}

QString Token::jsonString() const
{
    return Utils::toJsonString(json());
}

void Token::set(const Token *other)
{
    if (other) {
        m_BankAccount = other->bankAccount();
        m_Created = other->created();
        m_TokenID = other->tokenID();

        m_IsLiveMode = other->liveMode();
        m_Type = other->type();
        m_IsUsed = other->used();
    }
}

}
