#pragma once
#include <QObject>

namespace QStripe
{

class Customer : public QObject
{
    Q_OBJECT
public:
    explicit Customer(QObject *parent = nullptr);

signals:

public slots:
};

}
