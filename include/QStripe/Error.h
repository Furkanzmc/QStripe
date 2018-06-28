#pragma once
// Qt
#include <QVariantMap>
#include <QObject>

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

    // Since decline codes are strings, define a property for each one here.
    Q_PROPERTY(QString DeclineCodeApproveWithId READ declineCodeApproveWithId CONSTANT)
    Q_PROPERTY(QString DeclineCodeCallIssuer READ declineCodeCallIssuer CONSTANT)
    Q_PROPERTY(QString DeclineCodeCardNotSupported READ declineCodeCardNotSupported CONSTANT)
    Q_PROPERTY(QString DeclineCodeCardVelocityExceeded READ declineCodeCardVelocityExceeded CONSTANT)
    Q_PROPERTY(QString DeclineCodeCurrencyNotSupported READ declineCodeCurrencyNotSupported CONSTANT)
    Q_PROPERTY(QString DeclineCodeDoNotHonor READ declineCodeDoNotHonor CONSTANT)
    Q_PROPERTY(QString DeclineCodeDoNotTryAgain READ declineCodeDoNotTryAgain CONSTANT)
    Q_PROPERTY(QString DeclineCodeDuplicateTransaction READ declineCodeDuplicateTransaction CONSTANT)
    Q_PROPERTY(QString DeclineCodeExpiredCard READ declineCodeExpiredCard CONSTANT)
    Q_PROPERTY(QString DeclineCodeFraudulent READ declineCodeFraudulent CONSTANT)
    Q_PROPERTY(QString DeclineCodeGenericDecline READ declineCodeGenericDecline CONSTANT)
    Q_PROPERTY(QString DeclineCodeIncorrectNumber READ declineCodeIncorrectNumber CONSTANT)
    Q_PROPERTY(QString DeclineCodeIncorrectCvc READ declineCodeIncorrectCvc CONSTANT)
    Q_PROPERTY(QString DeclineCodeIncorrectPin READ declineCodeIncorrectPin CONSTANT)
    Q_PROPERTY(QString DeclineCodeIncorrectZip READ declineCodeIncorrectZip CONSTANT)
    Q_PROPERTY(QString DeclineCodeInsufficientFunds READ declineCodeInsufficientFunds CONSTANT)
    Q_PROPERTY(QString DeclineCodeInvalidAccount READ declineCodeInvalidAccount CONSTANT)
    Q_PROPERTY(QString DeclineCodeInvalidAmount READ declineCodeInvalidAmount CONSTANT)
    Q_PROPERTY(QString DeclineCodeInvalidCvc READ declineCodeInvalidCvc CONSTANT)
    Q_PROPERTY(QString DeclineCodeInvalidExpiryYear READ declineCodeInvalidExpiryYear CONSTANT)
    Q_PROPERTY(QString DeclineCodeInvalidNumber READ declineCodeInvalidNumber CONSTANT)
    Q_PROPERTY(QString DeclineCodeInvalidPin READ declineCodeInvalidPin CONSTANT)
    Q_PROPERTY(QString DeclineCodeIssuerNotAvailable READ declineCodeIssuerNotAvailable CONSTANT)
    Q_PROPERTY(QString DeclineCodeLostCard READ declineCodeLostCard CONSTANT)
    Q_PROPERTY(QString DeclineCodeNewAccountInformationAvailable READ declineCodeNewAccountInformationAvailable CONSTANT)
    Q_PROPERTY(QString DeclineCodeNoActionTaken READ declineCodeNoActionTaken CONSTANT)
    Q_PROPERTY(QString DeclineCodeNotPermitted READ declineCodeNotPermitted CONSTANT)
    Q_PROPERTY(QString DeclineCodePickupCard READ declineCodePickupCard CONSTANT)
    Q_PROPERTY(QString DeclineCodePinTryExceeded READ declineCodePinTryExceeded CONSTANT)
    Q_PROPERTY(QString DeclineCodeProcessingError READ declineCodeProcessingError CONSTANT)
    Q_PROPERTY(QString DeclineCodeReenterTransaction READ declineCodeReenterTransaction CONSTANT)
    Q_PROPERTY(QString DeclineCodeRestrictedCard READ declineCodeRestrictedCard CONSTANT)
    Q_PROPERTY(QString DeclineCodeRevocationOfAllAuthorizations READ declineCodeRevocationOfAllAuthorizations CONSTANT)
    Q_PROPERTY(QString DeclineCodeRevocationOfAuthorization READ declineCodeRevocationOfAuthorization CONSTANT)
    Q_PROPERTY(QString DeclineCodeSecurityViolation READ declineCodeSecurityViolation CONSTANT)
    Q_PROPERTY(QString DeclineCodeServiceNotAllowed READ declineCodeServiceNotAllowed CONSTANT)
    Q_PROPERTY(QString DeclineCodeStolenCard READ declineCodeStolenCard CONSTANT)
    Q_PROPERTY(QString DeclineCodeStopPaymentOrder READ declineCodeStopPaymentOrder CONSTANT)
    Q_PROPERTY(QString DeclineCodeTestmodeDecline READ declineCodeTestmodeDecline CONSTANT)
    Q_PROPERTY(QString DeclineCodeTransactionNotAllowed READ declineCodeTransactionNotAllowed CONSTANT)
    Q_PROPERTY(QString DeclineCodeTryAgainLater READ declineCodeTryAgainLater CONSTANT)
    Q_PROPERTY(QString DeclineCodeWithdrawalCountLimitExceeded READ declineCodeWithdrawalCountLimitExceeded CONSTANT)

public:
    enum ErrorType {
        ErrorApiConnection = 0, // Failure to connect to Stripe's API.
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
        CodeInvalidNumber = 0, // The card number is not a valid credit card number.
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
        CodeNone // This is the default value.
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
     * @brief Returns the decline code description from here: https://stripe.com/docs/declines/codes
     * All the descriptions are translateable. This message is assumed to be customer facing, so the decline code titles for stolen cards are replaced with
     * the title of the generic error. If you want to get the actual title, set the @param omitSensitive parameter to false.
     * @param omitSensitive When set to true, the title for the following decline codes will be replaced with the generic error code title.
     *     - pickup_card
     *     - restricted_card
     *     - stolen_card
     * @param declineCode
     * @return QString
     */
    Q_INVOKABLE QString declineCodeDescription(QString declineCode = "", bool omitSensitive = true) const;

    /**
     * @brief Returns the decline code next steps from here: https://stripe.com/docs/declines/codes
     * The returned value is translateable. This message is assumed to be customer facing, so the decline code titles for stolen cards are replaced with
     * the title of the generic error. If you want to get the actual next step description, set the @param omitSensitive parameter to false.
     * @param omitSensitive When set to true, the title for the following decline codes will be replaced with the generic error code title.
     *     - pickup_card
     *     - restricted_card
     *     - stolen_card
     * @param declineCode
     * @return QString
     */
    Q_INVOKABLE QString declineCodeNextSteps(QString declineCode = "", bool omitSensitive = true) const;

    /**
     * @brief Converts the string to the associated ErrorType.
     * @param typeString
     * @return ErrorType
     *
     * This method is invokable from QML.
     */
    Q_INVOKABLE ErrorType errorTypeFromString(const QString &typeString) const;

    /**
     * @brief Converts the string to the associated ErrorCode.
     * @param codeStr
     * @return ErrorCode
     *
     * This method is invokable from QML.
     */
    Q_INVOKABLE ErrorCode errorCodeFromString(const QString &codeStr) const;

    /**
     * @brief Changes the contents of this instance based on the errorResponse. If any field does not exist for some reason, the default values are set.
     * @param errorResponse
     */
    void set(QVariantMap errorResponse, int httpCode = -1, int networkErrorCode = -1);

    /**
     * @brief Resets the properties to the default.
     */
    void clear();

    /**
     * @brief Returns the JSON object that was used to construct this Error.
     * @return QVariantMap
     */
    const QVariantMap &rawErrorObject() const;

    // Define the decline code getters.

    QString declineCodeApproveWithId() const;
    QString declineCodeCallIssuer() const;
    QString declineCodeCardNotSupported() const;

    QString declineCodeCardVelocityExceeded() const;
    QString declineCodeCurrencyNotSupported() const;
    QString declineCodeDoNotHonor() const;

    QString declineCodeDoNotTryAgain() const;
    QString declineCodeDuplicateTransaction() const;
    QString declineCodeExpiredCard() const;

    QString declineCodeFraudulent() const;
    QString declineCodeGenericDecline() const;
    QString declineCodeIncorrectNumber() const;

    QString declineCodeIncorrectCvc() const;
    QString declineCodeIncorrectPin() const;
    QString declineCodeIncorrectZip() const;

    QString declineCodeInsufficientFunds() const;
    QString declineCodeInvalidAccount() const;
    QString declineCodeInvalidAmount() const;

    QString declineCodeInvalidCvc() const;
    QString declineCodeInvalidExpiryYear() const;
    QString declineCodeInvalidNumber() const;

    QString declineCodeInvalidPin() const;
    QString declineCodeIssuerNotAvailable() const;
    QString declineCodeLostCard() const;

    QString declineCodeNewAccountInformationAvailable() const;
    QString declineCodeNoActionTaken() const;
    QString declineCodeNotPermitted() const;

    QString declineCodePickupCard() const;
    QString declineCodePinTryExceeded() const;
    QString declineCodeProcessingError() const;

    QString declineCodeReenterTransaction() const;
    QString declineCodeRestrictedCard() const;
    QString declineCodeRevocationOfAllAuthorizations() const;

    QString declineCodeRevocationOfAuthorization() const;
    QString declineCodeSecurityViolation() const;
    QString declineCodeServiceNotAllowed() const;

    QString declineCodeStolenCard() const;
    QString declineCodeStopPaymentOrder() const;
    QString declineCodeTestmodeDecline() const;

    QString declineCodeTransactionNotAllowed() const;
    QString declineCodeTryAgainLater() const;
    QString declineCodeWithdrawalCountLimitExceeded() const;

private:
    QString m_ChargeID,
            m_Message,
            m_DeclineCode,
            m_Param;

    ErrorCode m_Code;
    ErrorType m_Type;
    int m_HttpStatus, m_NetworkError;

    QVariantMap m_RawError;
};

}
