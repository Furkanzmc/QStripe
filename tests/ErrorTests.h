#pragma once
#include <QObject>

class ErrorTests : public QObject
{
    Q_OBJECT
public:
    explicit ErrorTests(QObject *parent = nullptr);

private slots:
    void testError();
};
