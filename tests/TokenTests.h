#pragma once
#include <QObject>

class TokenTests : public QObject
{
    Q_OBJECT

public:
    explicit TokenTests(QObject *parent = nullptr);

private:
    QVariantMap getTokenData() const;

private slots:
    void testFromJson();
    void testJson();
    void testJsonString();
};
