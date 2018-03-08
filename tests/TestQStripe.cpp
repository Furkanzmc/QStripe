#include <QtTest/QtTest>
#include <QSignalSpy>
#include "TestQStripe.h"
#include "CustomerTests.h"
#include "AddressTests.h"
#include "ShippingInformationTests.h"
#include "CardTests.h"
// QStripe
#include "QStripe/PaymentSource.h"
#include "QStripe/Utils.h"

using namespace QStripe;

void TestQStripe::testPaymentSource()
{
    PaymentSource source;
    QSignalSpy spy(&source, &PaymentSource::sourceIDChanged);
    source.setSourceID("pk_sorce_id_awesome");
    QCOMPARE(spy.count(), 1);
}

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    TestQStripe ts;
    AddressTests addressTests;
    ShippingInformationTests shippingTests;
    CustomerTests customerTests;
    CardTests cardTests;

    int status = 0;
    // The order of the tests is important.
    status |= QTest::qExec(&ts, argc, argv);
    status |= QTest::qExec(&addressTests, argc, argv);
    status |= QTest::qExec(&shippingTests, argc, argv);
    status |= QTest::qExec(&customerTests, argc, argv);
    status |= QTest::qExec(&cardTests, argc, argv);

    return status;
}
