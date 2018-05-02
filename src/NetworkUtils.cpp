#include "QStripe/NetworkUtils.h"
// Qt
#include <QNetworkRequest>
#include <QMimeDatabase>
#include <QNetworkReply>
#include <QHttpPart>
#include <QUrlQuery>
#include <QFile>
// QStripe
#include "QStripe/Utils.h"

namespace QStripe
{

unsigned int NetworkUtils::m_RequestCount = 0;

NetworkUtils::NetworkUtils(QObject *parent)
    : QObject(parent)
{
    connect(&m_Network, &QNetworkAccessManager::finished, this, &NetworkUtils::onRequestFinished);
    setHeader("Content-Type", "application/x-www-form-urlencoded");
}

NetworkUtils::~NetworkUtils()
{

}

void NetworkUtils::sendGet(const QString &url, RequestCallback callback, const QVariantMap &queryParams)
{
    const int availableIndex = getAvailableIndex();
    const unsigned int threadIndex = availableIndex == -1 ? m_Callbacks.size() : availableIndex;
    QUrl qurl = QUrl(url);

    if (queryParams.size() > 0) {
        QUrlQuery query;
        for (auto it = queryParams.constBegin(); it != queryParams.constEnd(); it++) {
            query.addQueryItem(it.key(), it.value().toString());
        }

        qurl.setQuery(query);
    }

    QNetworkRequest request(qurl);
    setHeaders(request);
    QNetworkReply *reply = m_Network.get(request);

    reply->setObjectName(QString::number(threadIndex));
    insertCallback(threadIndex, std::move(callback));
}

void NetworkUtils::sendDelete(const QString &url, RequestCallback callback)
{
    const int availableIndex = getAvailableIndex();
    const unsigned int threadIndex = availableIndex == -1 ? m_Callbacks.size() : availableIndex;
    const QUrl qurl = QUrl(url);
    QNetworkRequest request(qurl);
    setHeaders(request);
    QNetworkReply *reply = m_Network.deleteResource(request);

    reply->setObjectName(QString::number(threadIndex));
    insertCallback(threadIndex, std::move(callback));
}

void NetworkUtils::sendPost(const QString &url, const QVariantMap &data, RequestCallback callback)
{
    const int availableIndex = getAvailableIndex();
    const unsigned int threadIndex = availableIndex == -1 ? m_Callbacks.size() : availableIndex;
    const QUrl qurl = QUrl(url);
    QNetworkRequest request(qurl);
    setHeaders(request);

    QUrlQuery query;
    for (auto it = data.constBegin(); it != data.constEnd(); it++) {
        QString value = "";
        if (it.value().type() == QVariant::String) {
            value = it.value().toString();
        }
        else if (it.value().type() == QVariant::Map) {
            value = Utils::toJsonString(it.value().toMap());
        }
        else if (it.value().type() == QVariant::Int) {
            value = QString::number(it.value().toInt());
        }

        query.addQueryItem(it.key(), it.value().toString());
    }

    const QByteArray postData = query.toString().toUtf8();
    request.setHeader(QNetworkRequest::KnownHeaders::ContentLengthHeader, postData.size());
    QNetworkReply *reply = m_Network.post(request, postData);

    reply->setObjectName(QString::number(threadIndex));
    insertCallback(threadIndex, std::move(callback));
}

void NetworkUtils::sendPut(const QString &url, const QVariantMap &data, RequestCallback callback)
{
    const int availableIndex = getAvailableIndex();
    const unsigned int threadIndex = availableIndex == -1 ? m_Callbacks.size() : availableIndex;
    const QUrl qurl = QUrl(url);
    QNetworkRequest request(qurl);
    setHeaders(request);

    QUrlQuery query;
    for (auto it = data.constBegin(); it != data.constEnd(); it++) {
        QString value = "";
        if (it.value().type() == QVariant::String) {
            value = it.value().toString();
        }
        else if (it.value().type() == QVariant::Map) {
            value = Utils::toJsonString(it.value().toMap());
        }
        else if (it.value().type() == QVariant::Int) {
            value = QString::number(it.value().toInt());
        }

        query.addQueryItem(it.key(), it.value().toString());
    }
    const QByteArray putData = query.toString().toUtf8();
    request.setHeader(QNetworkRequest::KnownHeaders::ContentLengthHeader, putData.size());

    QNetworkReply *reply = m_Network.put(request, putData);

    reply->setObjectName(QString::number(threadIndex));
    insertCallback(threadIndex, std::move(callback));
}

int NetworkUtils::getNextrequestID()
{
    m_RequestCount++;
    return m_RequestCount;
}

void NetworkUtils::setHeader(const QString &headerName, const QString &headerValue)
{
    m_Headers[headerName.toUtf8()] = headerValue.toUtf8();
}

void NetworkUtils::removeHeader(const QString &headerName)
{
    m_Headers.remove(headerName.toUtf8());
}

void NetworkUtils::onReceivedResponse(const Response &response, int threadIndex)
{
    if (threadIndex >= m_Callbacks.size()) {
        return;
    }

    RequestCallback &callback = m_Callbacks[threadIndex];
    if (callback) {
        callback(response);
    }

    m_Callbacks[threadIndex] = nullptr;
}

int NetworkUtils::getAvailableIndex()
{
    auto foundIt = std::find_if(m_Callbacks.begin(), m_Callbacks.end(), [](std::function<void(const Response &)> cb) {
        return cb == nullptr;
    });

    if (foundIt == m_Callbacks.end()) {
        return -1;
    }

    return std::distance(m_Callbacks.begin(), foundIt);
}

void NetworkUtils::insertCallback(const int &threadIndex, RequestCallback &&callback)
{
    if (threadIndex < m_Callbacks.size()) {
        m_Callbacks[threadIndex] = callback;
    }
    else {
        m_Callbacks.push_back(callback);
    }
}

void NetworkUtils::setHeaders(QNetworkRequest &request)
{
    for (auto it = m_Headers.constBegin(); it != m_Headers.constEnd(); it++) {
        request.setRawHeader(it.key(), it.value());
    }
}

void NetworkUtils::onRequestFinished(QNetworkReply *reply)
{
    const Response response(reply->readAll(), reply->attribute(QNetworkRequest::HttpStatusCodeAttribute).toInt(), reply->error());
    bool intConversionOk = false;
    int callbackIndex = reply->objectName().toInt(&intConversionOk);
    if (intConversionOk == false) {
        callbackIndex = -1;
    }

    onReceivedResponse(response, callbackIndex);
}

}
