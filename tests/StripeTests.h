#pragma once
#include <QObject>

class StripeTests : public QObject
{
    Q_OBJECT
public:
    explicit StripeTests(QString customerID, QObject *parent = nullptr);

private slots:
    void testFetchCustomer();

private:
    QString m_CustomerID;
};
