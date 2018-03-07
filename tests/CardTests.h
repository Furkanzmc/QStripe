#pragma once
#include <QObject>

class CardTests : public QObject
{
    Q_OBJECT
public:
    explicit CardTests(QObject *parent = nullptr);

private:
    QVariantMap getAddressData() const;

private slots:
    void testSignals();
};
