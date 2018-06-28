#include <QtTest/QtTest>
#include <QSignalSpy>

class TestQStripe: public QObject
{
    Q_OBJECT

private slots:
    void testPaymentSource();
};
