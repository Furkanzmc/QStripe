#pragma once
#include <QObject>

namespace QStripe
{

class Card : public QObject
{
    Q_OBJECT

public:
    explicit Card(QObject *parent = nullptr);

signals:

public slots:
};

}
