#pragma once
#include <QObject>

class ShippingInformationTests : public QObject
{
    Q_OBJECT
public:
    explicit ShippingInformationTests(QObject *parent = nullptr);

private:
    QVariantMap getAddressData() const;
    QVariantMap getShippingInformationData() const;

private slots:
    void testShippingInformationFromJson();
    void testShippingInformationJson();
    void testShippingInformationJsonString();

    void testShippingInformationSet();
    void testShippingInformationSetAddress();
};
