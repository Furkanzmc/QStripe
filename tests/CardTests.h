#pragma once
#include <QObject>

class CardTests : public QObject
{
    Q_OBJECT
public:
    explicit CardTests(QObject *parent = nullptr);

    static QVariantMap getAddressData();
    static QVariantMap getCardData();

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

private:
    QString m_TokenID;
};
