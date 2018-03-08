#include "QStripe/Token.h"
#include "QStripe/Utils.h"

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
    , m_Type(TypeUnknown)
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

    if (data.contains(FIELD_CARD)) {
        Card *card = Card::fromJson(Utils::toJsonString(data[FIELD_CARD].toMap()));
        token->m_Card.set(*card);
        card->deleteLater();
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

QVariantMap Token::json() const
{
    QVariantMap data;

    data[FIELD_BANK_ACCOUNT] = m_BankAccount;
    data[FIELD_CARD] = m_Card.json();
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

}
