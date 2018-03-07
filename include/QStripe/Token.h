#pragma once
#include <QObject>

namespace QStripe
{

class Token : public QObject
{
    Q_OBJECT

public:
    explicit Token(QObject *parent = nullptr);

signals:

public slots:
};

}
