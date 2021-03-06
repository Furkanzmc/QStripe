#include "StripeTests.h"
#include <QtTest/QtTest>
#include <QSignalSpy>
#include <QDebug>
// QStripe
#include "QStripe/Customer.h"
#include "QStripe/Stripe.h"
#include "QStripe/Utils.h"

using namespace QStripe;

StripeTests::StripeTests(QString customerID, QString cardID, QObject *parent)
    : QObject(parent)
    , m_CustomerID(customerID)
    , m_CardID(cardID)
{

}

void StripeTests::testFetchCustomer()
{
    if (m_CustomerID.length() == 0) {
        qWarning() << "Customer ID does not exist. Skipping customer fetch test.";
        return;
    }

    Stripe stripe;
    QCOMPARE(stripe.fetchCustomer(""), false);

    QCOMPARE(stripe.fetchCustomer(m_CustomerID), true);

    QSignalSpy spyUpdated(&stripe, &Stripe::customerFetched);
    QVERIFY2(spyUpdated.wait() == true, stripe.lastError()->message().toStdString().c_str());
    QList<QVariant> list = spyUpdated.takeFirst();
    if (list.size() > 0) {
        QObject *obj = qvariant_cast<QObject *>(list.at(0));
        Customer *customer = qobject_cast<Customer *>(obj);
        QCOMPARE(customer->customerID(), m_CustomerID);
        QCOMPARE(customer->deleted(), false);
    }
}

void StripeTests::testFetchCard()
{
    if (m_CardID.length() == 0) {
        qWarning() << "Card ID does not exist. Skipping customer fetch test.";
        return;
    }

    Stripe stripe;
    QCOMPARE(stripe.fetchCard(m_CustomerID, ""), false);

    // FIXME: The card ID does not exist because we delete it in CardTests. Create another card for the fetch test.
    QCOMPARE(stripe.fetchCard(m_CustomerID, m_CardID), true);

    QSignalSpy spyUpdated(&stripe, &Stripe::errorOccurred);
    QCOMPARE(spyUpdated.wait(), true);
//    QList<QVariant> list = spyUpdated.takeFirst();
//    if (list.size() > 0) {
//        QObject *obj = qvariant_cast<QObject *>(list.at(0));
//        Card *card = qobject_cast<Card *>(obj);
//        QCOMPARE(card->cardID(), m_CardID);
//    }
}
