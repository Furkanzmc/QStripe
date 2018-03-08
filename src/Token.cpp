#include "QStripe/Token.h"

namespace QStripe
{

const QString Token::FIELD_BANK_ACCOUNT = "bank_account";
const QString Token::FIELD_CARD = "card";
const QString Token::FIELD_CREATED = "created";

const QString Token::FIELD_ID = "id";
const QString Token::FIELD_LIVEMODE = "livemode";
const QString Token::FIELD_TYPE = "type";

const QString Token::FIELD_USED = "used";

Token::Token(QObject *parent)
    : QObject(parent)
    , m_BankAccount()
    , m_Card()
    , m_Created()
    , m_TokenID("")
    , m_IsLiveMode(false)
    , m_IsUsed(false)
{

}

const Card *Token::card() const
{
    return &m_Card;
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

bool Token::liveMode() const
{
    return m_IsLiveMode;
}

bool Token::used() const
{
    return m_IsUsed;
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

}
