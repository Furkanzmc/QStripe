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
};
