#pragma once
// std
#include <functional>
// Qt
#include <QNetworkAccessManager>
#include <QNetworkReply>

namespace QStripe
{

struct Response {
    Response(QString _data, unsigned int _httpCode, QNetworkReply::NetworkError error)
        : data(_data)
        , httpStatus(_httpCode)
        , networkError(error)
    {

    }

    QString data;
    unsigned int httpStatus;
    QNetworkReply::NetworkError networkError;
};

using RequestCallback = std::function<void(const Response &)>;

class NetworkUtils : public QObject
{
    Q_OBJECT

public:
    enum HttpStatusCodes {
        HTTP_200 = 200,
        HTTP_400 = 400,
        HTTP_401 = 401,
        HTTP_402 = 402,
        HTTP_404 = 404,
        HTTP_409 = 409,
        HTTP_429 = 429,
        HTTP_500 = 500,
        HTTP_502 = 502,
        HTTP_503 = 503,
        HTTP_504 = 504
    };

public:
    explicit NetworkUtils(QObject *parent = nullptr);
    ~NetworkUtils();

    /**
     * @brief Sends a get request. When the request is finished, the callback is called. If the queryParams parameter is provided, the query parameters are
     * appended to the request.
     * @param url
     * @param queryParams
     * @param callback
     */
    void sendGet(const QString &url, RequestCallback callback, const QVariantMap &queryParams = QVariantMap());

    /**
     * @brief Sends a delete request. When the request is finished, the callback is called.
     * @param url
     * @param callback
     */
    void sendDelete(const QString &url, RequestCallback callback);

    /**
     * @brief Sends a post request. When the request is finished, the callback is called. Stripe expects `application/x-www-form-urlencoded`.
     * @param url
     * @param data
     * @param callback
     */
    void sendPost(const QString &url, const QVariantMap &data, RequestCallback callback);

    /**
     * @brief Sends a put request. When the request is finished, the callback is called.
     * @param url
     * @param data
     * @param callback
     */
    void sendPut(const QString &url, const QVariantMap &data, RequestCallback callback);

    /**
     * @brief Increases m_RequestCount and returns the resulting ID
     * @return
     */
    int getNextrequestID();

    /**
     * @brief When a header is set, it is used for all of the requests. If a header with the same headerName exists, it is overwritten.
     * @param headerName
     * @param headerValue
     */
    void setHeader(const QString &headerName, const QString &headerValue);

    /**
     * @brief Removes the header with the given name.
     * @param headerName
     */
    void removeHeader(const QString &headerName);

private:
    static unsigned int m_RequestCount;

    QNetworkAccessManager m_Network;
    QList<RequestCallback> m_Callbacks;
    QMap<QByteArray, QByteArray> m_Headers;

private:
    void onRequestFinished(QNetworkReply *reply);
    void onReceivedResponse(const Response &response, int threadIndex);

    /**
     * @brief Returns the first nullptr thread index. If none found, returns -1
     * @return int
     */
    int getAvailableIndex();

    void insertCallback(const int &threadIndex, RequestCallback &&callback);

    /**
     * @brief If a token exists, sets the Authorization header of the HTTPRequest
     * @param request
     */
    void setHeaders(QNetworkRequest &request);
};

}
