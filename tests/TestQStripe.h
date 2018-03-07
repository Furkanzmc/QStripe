#include <QtTest/QtTest>
#include <QSignalSpy>

class TestQStripe: public QObject
{
    Q_OBJECT
private:
    QVariantMap getAddressData() const;
    QVariantMap getShippingInformationData() const;

private slots:
    // Begin Address Tests
    void testAddressEquals();
    void testAddressNotEquals();
    void testAddressChangeSignals();

    void testAddressFromJson();
    void testAddressSet();
    void testAddressJsonString();

    void testAddressJson();
    // End Address Tests

    // Begin ShippingInformation Tests
    void testShippingInformationFromJson();
    void testShippingInformationJson();
    void testShippingInformationJsonString();

    void testShippingInformationSet();
    void testShippingInformationSetAddress();
    // End ShippingInformation Tests
};
