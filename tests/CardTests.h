#pragma once
#include <QObject>

class CardTests : public QObject
{
    Q_OBJECT
public:
    explicit CardTests(QObject *parent = nullptr);

private:
    QVariantMap getAddressData() const;
    QVariantMap getCardData() const;

private slots:
    void testSignals();
    void testFromJson();
    void testJsonStr();

    void testJson();
    void testSet();
};
