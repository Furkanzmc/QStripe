#include <QtTest/QtTest>
#include <QSignalSpy>
// Tests
#include "ShippingInformationTests.h"
#include "CustomerTests.h"
#include "AddressTests.h"
#include "TestQStripe.h"
#include "TokenTests.h"
#include "ErrorTests.h"
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
    TokenTests tokenTests;
    ErrorTests errorTests;

    int status = 0;
    // The order of the tests is important.
    status |= QTest::qExec(&ts, argc, argv);
    status |= QTest::qExec(&addressTests, argc, argv);
    status |= QTest::qExec(&shippingTests, argc, argv);
    status |= QTest::qExec(&customerTests, argc, argv);
    status |= QTest::qExec(&cardTests, argc, argv);
    status |= QTest::qExec(&tokenTests, argc, argv);
    status |= QTest::qExec(&errorTests, argc, argv);

    return status;
}
