#pragma once
#include <QVariantMap>

namespace QStripe
{

class Utils
{
public:
    explicit Utils();

    /**
     * @brief Converts the given QVariantMap to QString.
     * @param data
     * @return QString
     */
    static QString toJsonString(const QVariantMap &data);

    /**
     * @brief Converts the given data to variant map.
     * @param data
     * @return QVariantMap
     */
    static QVariantMap toVariantMap(const QString &data);
};

}
