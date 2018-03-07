#include "QStripe/Utils.h"
#include <QJsonDocument>
#include <QJsonObject>

namespace QStripe
{

Utils::Utils()
{

}

QString Utils::toJsonString(const QVariantMap &data)
{
    const QJsonObject &obj = QJsonObject::fromVariantMap(data);
    QJsonDocument doc;
    doc.setObject(obj);
    return doc.toJson(QJsonDocument::JsonFormat::Compact);
}

QVariantMap Utils::toVariantMap(const QString &data)
{
    QVariantMap map;
    const QJsonDocument doc = QJsonDocument::fromJson(data.toUtf8());
    if (doc.isNull() == false) {
        map = doc.object().toVariantMap();
    }

    return map;
}

}
