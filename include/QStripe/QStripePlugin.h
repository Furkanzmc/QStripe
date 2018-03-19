#pragma once
#include <QQmlExtensionPlugin>

class QStripePlugin : public QQmlExtensionPlugin
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID "QStripe")

public:
    explicit QStripePlugin(QObject *parent = nullptr);

    static void registerQStripe(const char *uri = "QStripe");
    void registerTypes(const char *uri);
};
