#include "TokenTests.h"
#include "CardTests.h"
#include <QtTest/QtTest>
// QStripe
#include "QStripe/Token.h"
#include "QStripe/Utils.h"

using namespace QStripe;

TokenTests::TokenTests(QObject *parent)
    : QObject(parent)
{

}

QVariantMap TokenTests::getTokenData() const
{
    QVariantMap data;

    // FIXME: When the BankAccount becomes a class of its own, replace this.
    data[Token::FIELD_BANK_ACCOUNT] = QVariantMap();
    QVariantMap cardData = CardTests::getCardData();
    /**
     * Note: Removing the metadata field here because when we use the `Card::json()`, the metadata is merged into the object as metadata[key], which causes
     * the test to fail becuase we are not comparing it to the merged kind of data in `testJson()` and `testJsonString()`.
     */
    cardData.remove(Card::FIELD_METADATA);
    data[Token::FIELD_CARD] = cardData;
    data[Token::FIELD_CREATED] = 1513192868;

    data[Token::FIELD_ID] = "tok_1BYfmyC1pSuA14ZwtBWBGpml";
    data[Token::FIELD_LIVEMODE] = false;
    data[Token::FIELD_TYPE] = Token::typeName(Token::TypeCard);

    data[Token::FIELD_USED] = false;

    return data;
}

void TokenTests::testFromJson()
{
    const QVariantMap data = getTokenData();
    const Token *token = Token::fromJson(data);

    QCOMPARE(token->bankAccount(), data[Token::FIELD_BANK_ACCOUNT].toMap());
    QCOMPARE(token->card()->json(), data[Token::FIELD_CARD].toMap());
    QCOMPARE(token->created(), QDateTime::fromSecsSinceEpoch(data[Token::FIELD_CREATED].toInt()));

    QCOMPARE(token->tokenID(), data[Token::FIELD_ID].toString());
    QCOMPARE(token->liveMode(), data[Token::FIELD_LIVEMODE].toBool());
    QCOMPARE(token->type(), Token::typeEnum(data[Token::FIELD_TYPE].toString()));

    QCOMPARE(token->used(), data[Token::FIELD_USED].toBool());
}

void TokenTests::testJson()
{
    const QVariantMap data = getTokenData();
    const Token *token = Token::fromJson(data);

    QCOMPARE(token->json(), data);
}

void TokenTests::testJsonString()
{
    const QVariantMap data = getTokenData();
    const Token *token = Token::fromJson(data);

    QCOMPARE(token->jsonString(), Utils::toJsonString(data));
}
