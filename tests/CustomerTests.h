#pragma once
#include <QObject>

class CustomerTests : public QObject
{
    Q_OBJECT

public:
    explicit CustomerTests(QObject *parent = nullptr);

private:
    QVariantMap getAddressData() const;
    QVariantMap getShippingInformationData() const;
    QVariantMap getData() const;

private slots:
    void testSignals();
    void testFromJson();
    void testJsonStr();

    void testJson();
    void testSet();
};
