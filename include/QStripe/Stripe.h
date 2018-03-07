#pragma once
#include <QObject>

namespace QStripe
{

class Stripe : public QObject
{
    Q_OBJECT

public:
    explicit Stripe(QObject *parent = nullptr);

signals:

public slots:
};

}
