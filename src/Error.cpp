#include "QStripe/Error.h"
// QStripe
#include "QStripe/NetworkUtils.h"
// Qt
#include <QDebug>
#include <QNetworkReply>

namespace QStripe
{

Error::Error(QObject *parent)
    : QObject(parent)
    , m_ChargeID("")
    , m_Message("")
    , m_DeclineCode("")
    , m_Param("")
    , m_Code(CodeNone)
    , m_Type(ErrorNone)
    , m_HttpStatus(-1)
    , m_NetworkError(-1)
    , m_RawError()
{

}

QString Error::chargeID() const
{
    return m_ChargeID;
}

QString Error::message() const
{
    return m_Message;
}

QString Error::declineCode() const
{
    return m_DeclineCode;
}

QString Error::param() const
{
    return m_Param;
}

Error::ErrorCode Error::code() const
{
    return m_Code;
}

Error::ErrorType Error::type() const
{
    return m_Type;
}

int Error::httpStatus() const
{
    return m_HttpStatus;
}

int Error::networkErrorCode() const
{
    return m_NetworkError;
}

QString Error::declineCodeDescription(QString declineCode, bool omitSensitive) const
{
    if (declineCode.isEmpty()) {
        declineCode = m_DeclineCode;
    }

    QString description = "";
    if (declineCode == declineCodeApproveWithId()) {
        description = tr("The payment cannot be authorized.");
    }
    else if (declineCode == declineCodeCallIssuer()) {
        description = tr("The card has been declined for an unknown reason.");
    }
    else if (declineCode == declineCodeCardNotSupported()) {
        description = tr("The card does not support this type of purchase.");
    }
    else if (declineCode == declineCodeCardVelocityExceeded()) {
        description = tr("You have exceeded the balance or credit limit available on your card.");
    }
    else if (declineCode == declineCodeCurrencyNotSupported()) {
        description = tr("The card does not support the specified currency.");
    }
    else if (declineCode == declineCodeDoNotHonor()) {
        description = tr("The card has been declined for an unknown reason.");
    }
    else if (declineCode == declineCodeDoNotTryAgain()) {
        description = tr("The card has been declined for an unknown reason.");
    }
    else if (declineCode == declineCodeDuplicateTransaction()) {
        description = tr("A transaction with identical amount and credit card information was submitted very recently.");
    }
    else if (declineCode == declineCodeExpiredCard()) {
        description = tr("The card has expired.");
    }
    else if (declineCode == declineCodeFraudulent()) {
        description = tr("The payment has been declined as Stripe suspects it is fraudulent.");
    }
    else if (declineCode == declineCodeGenericDecline()) {
        description = tr("The card has been declined for an unknown reason.");
    }
    else if (declineCode == declineCodeIncorrectNumber()) {
        description = tr("The card number is incorrect.");
    }
    else if (declineCode == declineCodeIncorrectCvc()) {
        description = tr("The CVC number is incorrect.");
    }
    else if (declineCode == declineCodeIncorrectPin()) {
        description = tr("The PIN entered is incorrect.");
    }
    else if (declineCode == declineCodeIncorrectZip()) {
        description = tr("The ZIP/postal code is incorrect.");
    }
    else if (declineCode == declineCodeInsufficientFunds()) {
        description = tr("The card has insufficient funds to complete the purchase.");
    }
    else if (declineCode == declineCodeInvalidAccount()) {
        description = tr("The card, or account the card is connected to, is invalid.");
    }
    else if (declineCode == declineCodeInvalidAmount()) {
        description = tr("The payment amount is invalid, or exceeds the amount that is allowed.");
    }
    else if (declineCode == declineCodeInvalidCvc()) {
        description = tr("The CVC number is incorrect.");
    }
    else if (declineCode == declineCodeInvalidExpiryYear()) {
        description = tr("The expiration year invalid.");
    }
    else if (declineCode == declineCodeInvalidNumber()) {
        description = tr("The card number is incorrect.");
    }
    else if (declineCode == declineCodeInvalidPin()) {
        description = tr("The PIN entered is incorrect.");
    }
    else if (declineCode == declineCodeIssuerNotAvailable()) {
        description = tr("The card issuer could not be reached, so the payment could not be authorized.");
    }
    else if (declineCode == declineCodeLostCard()) {
        if (omitSensitive) {
            description = tr("The card has been declined for an unknown reason.");
        }
        else {
            description = tr("The payment has been declined because the card is reported lost.");
        }
    }
    else if (declineCode == declineCodeNewAccountInformationAvailable()) {
        description = tr("The card, or account the card is connected to, is invalid.");
    }
    else if (declineCode == declineCodeNoActionTaken()) {
        description = tr("The card has been declined for an unknown reason.");
    }
    else if (declineCode == declineCodeNotPermitted()) {
        description = tr("The payment is not permitted.");
    }
    else if (declineCode == declineCodePickupCard()) {
        if (omitSensitive) {
            description = tr("The card cannot be used to make this payment.");
        }
        else {
            description = tr("The card cannot be used to make this payment (it is possible it has been reported lost or stolen).");
        }
    }
    else if (declineCode == declineCodePinTryExceeded()) {
        description = tr("The allowable number of PIN tries has been exceeded.");
    }
    else if (declineCode == declineCodeProcessingError()) {
        description = tr("An error occurred while processing the card.");
    }
    else if (declineCode == declineCodeReenterTransaction()) {
        description = tr("The payment could not be processed by the issuer for an unknown reason.");
    }
    else if (declineCode == declineCodeRestrictedCard()) {
        if (omitSensitive) {
            description = tr("The card cannot be used to make this payment");
        }
        else {
            description = tr("The card cannot be used to make this payment (it is possible it has been reported lost or stolen).");
        }
    }
    else if (declineCode == declineCodeRevocationOfAllAuthorizations()) {
        description = tr("The card has been declined for an unknown reason.");
    }
    else if (declineCode == declineCodeRevocationOfAuthorization()) {
        description = tr("The card has been declined for an unknown reason.");
    }
    else if (declineCode == declineCodeSecurityViolation()) {
        description = tr("The card has been declined for an unknown reason.");
    }
    else if (declineCode == declineCodeServiceNotAllowed()) {
        description = tr("The card has been declined for an unknown reason.");
    }
    else if (declineCode == declineCodeStolenCard()) {
        if (omitSensitive) {
            description = tr("The payment has been declined.");
        }
        else {
            description = tr("The payment has been declined because the card is reported stolen.");
        }
    }
    else if (declineCode == declineCodeStopPaymentOrder()) {
        description = tr("The card has been declined for an unknown reason.");
    }
    else if (declineCode == declineCodeTestmodeDecline()) {
        description = tr("A Stripe test card number was used.");
    }
    else if (declineCode == declineCodeTransactionNotAllowed()) {
        description = tr("The card has been declined for an unknown reason.");
    }
    else if (declineCode == declineCodeTryAgainLater()) {
        description = tr("The card has been declined for an unknown reason.");
    }
    else if (declineCode == declineCodeWithdrawalCountLimitExceeded()) {
        description = tr("The customer has exceeded the balance or credit limit available on their card.");
    }
    else {
        qDebug() << "[WARNING] Cannot find a description for the given decline code: " << declineCode;
    }

    return description;
}

QString Error::declineCodeNextSteps(QString declineCode, bool omitSensitive) const
{
    if (declineCode.isEmpty()) {
        declineCode = m_DeclineCode;
    }

    QString nextSteps = "";
    if (declineCode == declineCodeApproveWithId()) {
        nextSteps = tr("The payment should be attempted again. If it still cannot be processed, the customer needs to contact their card issuer.");
    }
    else if (declineCode == declineCodeCallIssuer()) {
        nextSteps = tr("The customer needs to contact their card issuer for more information.");
    }
    else if (declineCode == declineCodeCardNotSupported()) {
        nextSteps = tr("The customer needs to contact their card issuer to make sure their card can be used to make this type of purchase.");
    }
    else if (declineCode == declineCodeCardVelocityExceeded()) {
        nextSteps = tr("The customer should contact their card issuer for more information.");
    }
    else if (declineCode == declineCodeCurrencyNotSupported()) {
        nextSteps = tr("The customer needs check with the issuer that the card can be used for the type of currency specified.");
    }
    else if (declineCode == declineCodeDoNotHonor()) {
        nextSteps = tr("The customer needs to contact their card issuer for more information.");
    }
    else if (declineCode == declineCodeDoNotTryAgain()) {
        nextSteps = tr("The customer should contact their card issuer for more information.");
    }
    else if (declineCode == declineCodeDuplicateTransaction()) {
        nextSteps = tr("Check to see if a recent payment already exists.");
    }
    else if (declineCode == declineCodeExpiredCard()) {
        nextSteps = tr("The customer should use another card.");
    }
    else if (declineCode == declineCodeFraudulent()) {
        nextSteps = tr("The customer needs to contact their card issuer for more information.");
    }
    else if (declineCode == declineCodeGenericDecline()) {
        nextSteps = tr("The customer needs to contact their card issuer for more information.");
    }
    else if (declineCode == declineCodeIncorrectNumber()) {
        nextSteps = tr("The customer should try again using the correct card number.");
    }
    else if (declineCode == declineCodeIncorrectCvc()) {
        nextSteps = tr("The customer should try again using the correct CVC.");
    }
    else if (declineCode == declineCodeIncorrectPin()) {
        nextSteps = tr("The customer should try again using the correct PIN.");
    }
    else if (declineCode == declineCodeIncorrectZip()) {
        nextSteps = tr("The customer should try again using the correct billing ZIP/postal code.");
    }
    else if (declineCode == declineCodeInsufficientFunds()) {
        nextSteps = tr("The customer should use an alternative payment method.");
    }
    else if (declineCode == declineCodeInvalidAccount()) {
        nextSteps = tr("The customer needs to contact their card issuer to check that the card is working correctly.");
    }
    else if (declineCode == declineCodeInvalidAmount()) {
        nextSteps = tr("If the amount appears to be correct, the customer needs to check with their card issuer that they can make purchases of that amount.");
    }
    else if (declineCode == declineCodeInvalidCvc()) {
        nextSteps = tr("The customer should try again using the correct CVC.");
    }
    else if (declineCode == declineCodeInvalidExpiryYear()) {
        nextSteps = tr("The customer should try again using the correct expiration date.");
    }
    else if (declineCode == declineCodeInvalidNumber()) {
        nextSteps = tr("The customer should try again using the correct card number.");
    }
    else if (declineCode == declineCodeInvalidPin()) {
        nextSteps = tr("The customer should try again using the correct PIN.");
    }
    else if (declineCode == declineCodeIssuerNotAvailable()) {
        nextSteps = tr("The payment should be attempted again. If it still cannot be processed, the customer needs to contact their card issuer.");
    }
    else if (declineCode == declineCodeLostCard()) {
        if (omitSensitive) {
            nextSteps = tr("The customer needs to contact their card issuer for more information.");
        }
        else {
            nextSteps = tr("The specific reason for the decline should not be reported to the customer. Instead, it needs to be presented as a generic decline.");
        }
    }
    else if (declineCode == declineCodeNewAccountInformationAvailable()) {
        nextSteps = tr("The customer needs to contact their card issuer for more information.");
    }
    else if (declineCode == declineCodeNoActionTaken()) {
        nextSteps = tr("The customer should contact their card issuer for more information.");
    }
    else if (declineCode == declineCodeNotPermitted()) {
        nextSteps = tr("The customer needs to contact their card issuer for more information.");
    }
    else if (declineCode == declineCodePickupCard()) {
        nextSteps = tr("The customer needs to contact their card issuer for more information.");
    }
    else if (declineCode == declineCodePinTryExceeded()) {
        nextSteps = tr("The customer must use another card or method of payment.");
    }
    else if (declineCode == declineCodeProcessingError()) {
        nextSteps = tr("The payment should be attempted again. If it still cannot be processed, try again later.");
    }
    else if (declineCode == declineCodeReenterTransaction()) {
        nextSteps = tr("The payment should be attempted again. If it still cannot be processed, the customer needs to contact their card issuer.");
    }
    else if (declineCode == declineCodeRestrictedCard()) {
        nextSteps = tr("The customer needs to contact their card issuer for more information.");
    }
    else if (declineCode == declineCodeRevocationOfAllAuthorizations()) {
        nextSteps = tr("The customer should contact their card issuer for more information.");
    }
    else if (declineCode == declineCodeRevocationOfAuthorization()) {
        nextSteps = tr("The customer should contact their card issuer for more information.");
    }
    else if (declineCode == declineCodeSecurityViolation()) {
        nextSteps = tr("The customer needs to contact their card issuer for more information.");
    }
    else if (declineCode == declineCodeServiceNotAllowed()) {
        nextSteps = tr("The customer should contact their card issuer for more information.");
    }
    else if (declineCode == declineCodeStolenCard()) {
        if (omitSensitive) {
            nextSteps = tr("The customer needs to contact their card issuer for more information.");
        }
        else {
            nextSteps = tr("The specific reason for the decline should not be reported to the customer. Instead, it needs to be presented as a generic decline.");
        }

    }
    else if (declineCode == declineCodeStopPaymentOrder()) {
        nextSteps = tr("The customer should contact their card issuer for more information.");
    }
    else if (declineCode == declineCodeTestmodeDecline()) {
        nextSteps = tr("A genuine card must be used to make a payment.");
    }
    else if (declineCode == declineCodeTransactionNotAllowed()) {
        nextSteps = tr("The customer needs to contact their card issuer for more information.");
    }
    else if (declineCode == declineCodeTryAgainLater()) {
        nextSteps =
            tr("Ask the customer to attempt the payment again. If subsequent payments are declined, the customer should contact their card issuer for more information.");
    }
    else if (declineCode == declineCodeWithdrawalCountLimitExceeded()) {
        nextSteps = tr("The customer should use an alternative payment method.");
    }
    else {
        qDebug() << "[WARNING] Cannot find a next step for the given decline code: " << declineCode;
    }

    return nextSteps;
}

Error::ErrorType Error::errorTypeFromString(const QString &typeString) const
{
    ErrorType type = ErrorType::ErrorNone;
    if (typeString == "api_connection_error") {
        type = ErrorType::ErrorApiConnection;
    }
    else if (typeString == "api_error") {
        type = ErrorType::ErrorApi;
    }
    else if (typeString == "authentication_error") {
        type = ErrorType::ErrorAuthentication;
    }
    else if (typeString == "card_error") {
        type = ErrorType::ErrorCard;
    }
    else if (typeString == "idempotency_error") {
        type = ErrorType::ErrorIdempotency;
    }
    else if (typeString == "invalid_request_error") {
        type = ErrorType::ErrorInvalidRequest;
    }
    else if (typeString == "rate_limit_error") {
        type = ErrorType::ErrorRateLimit;
    }

    return type;
}

Error::ErrorCode Error::errorCodeFromString(const QString &codeStr) const
{
    ErrorCode code = ErrorCode::CodeNone;

    if (codeStr == "invalid_number") {
        code = ErrorCode::CodeInvalidNumber;
    }
    else if (codeStr == "invalid_expiry_month") {
        code = ErrorCode::CodeInvalidExpiryMonth;
    }
    else if (codeStr == "invalid_expiry_year") {
        code = ErrorCode::CodeInvalidExpiryYear;
    }
    else if (codeStr == "invalid_cvc") {
        code = ErrorCode::CodeInvalidCVC;
    }
    else if (codeStr == "invalid_swipe_data") {
        code = ErrorCode::CodeInvalidSwipeData;
    }
    else if (codeStr == "incorrect_number") {
        code = ErrorCode::CodeIncorrectNumber;
    }
    else if (codeStr == "expired_card") {
        code = ErrorCode::CodeExpiredCard;
    }
    else if (codeStr == "incorrect_cvc") {
        code = ErrorCode::CodeIncorrectCVC;
    }
    else if (codeStr == "incorrect_zip") {
        code = ErrorCode::CodeIncorrectZip;
    }
    else if (codeStr == "card_declined") {
        code = ErrorCode::CodeCardDeclined;
    }
    else if (codeStr == "missing") {
        code = ErrorCode::CodeMissing;
    }
    else if (codeStr == "processing_error") {
        code = ErrorCode::CodeProcessingError;
    }

    return code;
}

void Error::set(QVariantMap errorResponse, int httpCode, int networkErrorCode)
{
    if (errorResponse.contains("error")) {
        errorResponse = errorResponse["error"].toMap();
    }

    m_RawError = errorResponse;
    if (networkErrorCode == QNetworkReply::ConnectionRefusedError ||
        networkErrorCode == QNetworkReply::RemoteHostClosedError ||
        networkErrorCode == QNetworkReply::HostNotFoundError) {
        m_Type = ErrorType::ErrorApiConnection;
    }
    else if (errorResponse.contains("type")) {
        // Stripe reports authentication with a an invalid request error
        // type.
        if (httpCode == NetworkUtils::HTTP_401) {
            m_Type = ErrorType::ErrorAuthentication;
        }
        else {
            const QString typeString = errorResponse["type"].toString();
            m_Type = errorTypeFromString(typeString);
        }
    }
    else {
        m_Type = ErrorType::ErrorNone;
    }

    if (errorResponse.contains("charge")) {
        m_ChargeID = errorResponse["charge"].toString();
    }
    else {
        m_ChargeID = "";
    }

    if (errorResponse.contains("message")) {
        m_Message = errorResponse["message"].toString();
    }
    else {
        m_Message = "";
    }

    if (errorResponse.contains("code")) {
        const QString codeStr = errorResponse["code"].toString();
        m_Code = errorCodeFromString(codeStr);
    }
    else {
        m_Code = ErrorCode::CodeNone;
    }

    if (errorResponse.contains("decline_code")) {
        m_DeclineCode = errorResponse["decline_code"].toString();
    }
    else {
        m_DeclineCode = "";
    }

    if (errorResponse.contains("param")) {
        m_Param = errorResponse["param"].toString();
    }
    else {
        m_Param = "";
    }

    m_HttpStatus = httpCode;
    m_NetworkError = networkErrorCode;
}

void Error::clear()
{
    m_ChargeID = "";
    m_Message = "";
    m_DeclineCode = "";

    m_Param = "";
    m_Code = CodeNone;
    m_Type = ErrorNone;

    m_HttpStatus = -1;
    m_NetworkError = -1;
    m_RawError.clear();
}

const QVariantMap &Error::rawErrorObject() const
{
    return m_RawError;
}

QString Error::declineCodeApproveWithId() const
{
    return "approve_with_id";
}

QString Error::declineCodeCallIssuer() const
{
    return "call_issuer";
}

QString Error::declineCodeCardNotSupported() const
{
    return "card_not_supported";
}

QString Error::declineCodeCardVelocityExceeded() const
{
    return "card_velocity_exceeded";
}

QString Error::declineCodeCurrencyNotSupported() const
{
    return "currency_not_supported";
}

QString Error::declineCodeDoNotHonor() const
{
    return "do_not_honor";
}

QString Error::declineCodeDoNotTryAgain() const
{
    return "do_not_try_again";
}

QString Error::declineCodeDuplicateTransaction() const
{
    return "duplicate_transaction";
}

QString Error::declineCodeExpiredCard() const
{
    return "expired_card";
}

QString Error::declineCodeFraudulent() const
{
    return "fraudulent";
}

QString Error::declineCodeGenericDecline() const
{
    return "generic_decline";
}

QString Error::declineCodeIncorrectNumber() const
{
    return "incorrect_number";
}

QString Error::declineCodeIncorrectCvc() const
{
    return "incorrect_cvc";
}

QString Error::declineCodeIncorrectPin() const
{
    return "incorrect_pin";
}

QString Error::declineCodeIncorrectZip() const
{
    return "incorrect_zip";
}

QString Error::declineCodeInsufficientFunds() const
{
    return "insufficient_funds";
}

QString Error::declineCodeInvalidAccount() const
{
    return "invalid_account";
}

QString Error::declineCodeInvalidAmount() const
{
    return "invalid_amount";
}

QString Error::declineCodeInvalidCvc() const
{
    return "invalid_cvc";
}

QString Error::declineCodeInvalidExpiryYear() const
{
    return "invalid_expiry_year";
}

QString Error::declineCodeInvalidNumber() const
{
    return "invalid_number";
}

QString Error::declineCodeInvalidPin() const
{
    return "invalid_pin";
}

QString Error::declineCodeIssuerNotAvailable() const
{
    return "issuer_not_available";
}

QString Error::declineCodeLostCard() const
{
    return "lost_card";
}

QString Error::declineCodeNewAccountInformationAvailable() const
{
    return "new_account_information_available";
}

QString Error::declineCodeNoActionTaken() const
{
    return "no_action_taken";
}

QString Error::declineCodeNotPermitted() const
{
    return "not_permitted";
}

QString Error::declineCodePickupCard() const
{
    return "pickup_card";
}

QString Error::declineCodePinTryExceeded() const
{
    return "pin_try_exceeded";
}

QString Error::declineCodeProcessingError() const
{
    return "processing_error";
}

QString Error::declineCodeReenterTransaction() const
{
    return "reenter_transaction";
}

QString Error::declineCodeRestrictedCard() const
{
    return "restricted_card";
}

QString Error::declineCodeRevocationOfAllAuthorizations() const
{
    return "revocation_of_all_authorizations";
}

QString Error::declineCodeRevocationOfAuthorization() const
{
    return "revocation_of_authorization";
}

QString Error::declineCodeSecurityViolation() const
{
    return "security_violation";
}

QString Error::declineCodeServiceNotAllowed() const
{
    return "service_not_allowed";
}

QString Error::declineCodeStolenCard() const
{
    return "stolen_card";
}

QString Error::declineCodeStopPaymentOrder() const
{
    return "stop_payment_order";
}

QString Error::declineCodeTestmodeDecline() const
{
    return "testmode_decline";
}

QString Error::declineCodeTransactionNotAllowed() const
{
    return "transaction_not_allowed";
}

QString Error::declineCodeTryAgainLater() const
{
    return "try_again_later";
}

QString Error::declineCodeWithdrawalCountLimitExceeded() const
{
    return "withdrawal_count_limit_exceeded";
}

}
