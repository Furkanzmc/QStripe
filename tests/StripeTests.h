#pragma once
#include <QObject>

class StripeTests : public QObject
{
    Q_OBJECT
public:
    explicit StripeTests(QString customerID, QString cardID, QObject *parent = nullptr);

private slots:
    void testFetchCustomer();
    void testFetchCard();

private:
    QString m_CustomerID, m_CardID;
};
