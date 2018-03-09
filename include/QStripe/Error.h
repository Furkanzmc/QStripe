#pragma once
#include <QObject>
#include <QVariantMap>

namespace QStripe
{

class Error : public QObject
{
    Q_OBJECT

    Q_PROPERTY(QString chargeID READ chargeID CONSTANT)
    Q_PROPERTY(QString message READ message CONSTANT)
    Q_PROPERTY(QString declineCode READ declineCode CONSTANT)

    Q_PROPERTY(QString param READ param CONSTANT)
    Q_PROPERTY(ErrorCode code READ code CONSTANT)
    Q_PROPERTY(ErrorType type READ type CONSTANT)

    Q_PROPERTY(int httpStatus READ httpStatus CONSTANT)
    Q_PROPERTY(int networkErrorCode READ networkErrorCode CONSTANT)

public:
    enum ErrorType {
        ErrorApiConnection, // Failure to connect to Stripe's API.
        ErrorApi, // API errors cover any other type of problem (e.g., a temporary problem with Stripe's servers) and are extremely uncommon.
        ErrorAuthentication, // Failure to properly authenticate yourself in the request.
        ErrorCard, /** Card errors are the most common type of error you should expect to handle.
                       They result when the user enters a card that can't be charged for some reason.
                   **/
        ErrorIdempotency, /** Idempotency errors occur when an Idempotency-Key is re-used on a request
                              that does not match the API endpoint and parameters of the first.
                          **/
        ErrorInvalidRequest, // Invalid request errors arise when your request has invalid parameters.
        ErrorRateLimit, // Too many requests hit the API too quickly.
        ErrorValidation, /** Errors triggered by our client-side libraries when failing to validate fields
                            (e.g., when a card number or expiration date is invalid or incomplete).
                        **/
        ErrorNone // This is the default value
    };
    Q_ENUM(ErrorType);

    enum ErrorCode {
        CodeInvalidNumber, // The card number is not a valid credit card number.
        CodeInvalidExpiryMonth, // The card's expiration month is invalid.
        CodeInvalidExpiryYear, // The card's expiration year is invalid.
        CodeInvalidCVC, // The card's security code is invalid.
        CodeInvalidSwipeData, // The card's swipe data is invalid.
        CodeIncorrectNumber, // The card number is incorrect.
        CodeExpiredCard, // The card has expired.
        CodeIncorrectCVC, // The card's security code is incorrect.
        CodeIncorrectZip, // The card's zip code failed validation.
        CodeCardDeclined, // The card was declined.
        CodeMissing, // There is no card on a customer that is being charged.
        CodeProcessingError, // An error occurred while processing the card.
        CodeNone, // This is the default value.
    };
    Q_ENUM(ErrorCode);

public:
    explicit Error(QObject *parent = nullptr);

    /**
     * @brief The ID of the failed charge.
     * @return QString
     */
    QString chargeID() const;

    /**
     * @brief A human-readable message providing more details about the error. For card errors, these messages can be shown to your users.
     * @return QString
     */
    QString message() const;

    /**
     * @brief For card errors resulting from a card issuer decline, a short string indicating the card issuer's reason for the decline if they provide one.
     * @return QString
     */
    QString declineCode() const;

    /**
     * @brief The parameter the error relates to if the error is parameter-specific. You can use this to display a message near the correct
     * form field, for example.
     * @return
     */
    QString param() const;

    /**
     * @brief For card errors, a short string from among those listed on the right describing the kind of card error that occurred.
     * @return ErrorCode
     */
    ErrorCode code() const;

    /**
     * @brief The type of error returned.
     * @return ErrorType
     */
    ErrorType type() const;

    /**
     * @brief The HTTP status returned from the response.
     * @return int
     */
    int httpStatus() const;

    /**
     * @brief This is the QNetworkReply::NetworkError from the response.
     * @return int
     */
    int networkErrorCode() const;

    /**
     * @brief Changes the contents of this instance based on the errorResponse. If any field does not exist for some reason, the default values are set.
     * @param errorResponse
     */
    void set(const QVariantMap &errorResponse, int httpCode = -1, int networkErrorCode = -1);

private:
    QString m_ChargeID,
            m_Message,
            m_DeclineCode,
            m_Param;

    ErrorCode m_Code;
    ErrorType m_Type;
    int m_HttpStatus, m_NetworkError;
};

}
