#pragma once
#include <QObject>

class AddressTests : public QObject
{
    Q_OBJECT
public:
    explicit AddressTests(QObject *parent = nullptr);

private:
    QVariantMap getAddressData() const;

private slots:
    void testAddressEquals();
    void testAddressNotEquals();
    void testAddressChangeSignals();

    void testAddressFromJson();
    void testAddressSet();
    void testAddressJsonString();

    void testAddressJson();
};
