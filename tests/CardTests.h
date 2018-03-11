#pragma once
#include <QObject>

namespace QStripe
{
class Card;
}

class CardTests : public QObject
{
    Q_OBJECT
public:
    explicit CardTests(QString customerID, QObject *parent = nullptr);

    static QVariantMap getAddressData();
    static QVariantMap getCardData();

    QString getCardID() const;

private slots:
    void testSignals();
    void testFromJson();
    void testJsonStr();

    void testJson();
    void testSet();
    void testCardBrand();

    void testCardLength();
    void testCardNumberValidation();
    void testValidExpirationMonth();

    void testValidExpirationYear();
    void testValidExpirationDate();
    void testValidCVC();

    void testCreateToken();
    void testTokenFetch();
    void testCreate();

    void testDelete();

private:
    QString m_CustomerID,
            m_TokenID,
            m_CardID;
    // The card that the token ID belongs to.
    QStripe::Card *m_Card;
};
