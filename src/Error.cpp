#include "QStripe/Error.h"
// Qt
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

QString Error::declineCodeDescription(bool omitSensitive) const
{
    QString description = "";
    if (m_DeclineCode == declineCodeApproveWithId()) {
        description = tr("The payment cannot be authorized.");
    }
    else if (m_DeclineCode == declineCodeCallIssuer()) {
        description = tr("The card has been declined for an unknown reason.");
    }
    else if (m_DeclineCode == declineCodeCardNotSupported()) {
        description = tr("The card does not support this type of purchase.");
    }
    else if (m_DeclineCode == declineCodeCardVelocityExceeded()) {
        description = tr("You have exceeded the balance or credit limit available on your card.");
    }
    else if (m_DeclineCode == declineCodeCurrencyNotSupported()) {
        description = tr("The card does not support the specified currency.");
    }
    else if (m_DeclineCode == declineCodeDoNotHonor()) {
        description = tr("The card has been declined for an unknown reason.");
    }
    else if (m_DeclineCode == declineCodeDoNotTryAgain()) {
        description = tr("The card has been declined for an unknown reason.");
    }
    else if (m_DeclineCode == declineCodeDuplicateTransaction()) {
        description = tr("A transaction with identical amount and credit card information was submitted very recently.");
    }
    else if (m_DeclineCode == declineCodeExpiredCard()) {
        description = tr("The card has expired.");
    }
    else if (m_DeclineCode == declineCodeFraudulent()) {
        description = tr("The payment has been declined as Stripe suspects it is fraudulent.");
    }
    else if (m_DeclineCode == declineCodeGenericDecline()) {
        description = tr("The card has been declined for an unknown reason.");
    }
    else if (m_DeclineCode == declineCodeIncorrectNumber()) {
        description = tr("The card number is incorrect.");
    }
    else if (m_DeclineCode == declineCodeIncorrectCvc()) {
        description = tr("The CVC number is incorrect.");
    }
    else if (m_DeclineCode == declineCodeIncorrectPin()) {
        description = tr("The PIN entered is incorrect.");
    }
    else if (m_DeclineCode == declineCodeIncorrectZip()) {
        description = tr("The ZIP/postal code is incorrect.");
    }
    else if (m_DeclineCode == declineCodeInsufficientFunds()) {
        description = tr("The card has insufficient funds to complete the purchase.");
    }
    else if (m_DeclineCode == declineCodeInvalidAccount()) {
        description = tr("The card, or account the card is connected to, is invalid.");
    }
    else if (m_DeclineCode == declineCodeInvalidAmount()) {
        description = tr("The payment amount is invalid, or exceeds the amount that is allowed.");
    }
    else if (m_DeclineCode == declineCodeInvalidCvc()) {
        description = tr("The CVC number is incorrect.");
    }
    else if (m_DeclineCode == declineCodeInvalidExpiryYear()) {
        description = tr("The expiration year invalid.");
    }
    else if (m_DeclineCode == declineCodeInvalidNumber()) {
        description = tr("The card number is incorrect.");
    }
    else if (m_DeclineCode == declineCodeInvalidPin()) {
        description = tr("The PIN entered is incorrect.");
    }
    else if (m_DeclineCode == declineCodeIssuerNotAvailable()) {
        description = tr("The card issuer could not be reached, so the payment could not be authorized.");
    }
    else if (m_DeclineCode == declineCodeLostCard()) {
        if (omitSensitive) {
            description = tr("The card has been declined for an unknown reason.");
        }
        else {
            description = tr("The payment has been declined because the card is reported lost.");
        }
    }
    else if (m_DeclineCode == declineCodeNewAccountInformationAvailable()) {
        description = tr("The card, or account the card is connected to, is invalid.");
    }
    else if (m_DeclineCode == declineCodeNoActionTaken()) {
        description = tr("The card has been declined for an unknown reason.");
    }
    else if (m_DeclineCode == declineCodeNotPermitted()) {
        description = tr("The payment is not permitted.");
    }
    else if (m_DeclineCode == declineCodePickupCard()) {
        if (omitSensitive) {
            description = tr("The card cannot be used to make this payment.");
        }
        else {
            description = tr("The card cannot be used to make this payment (it is possible it has been reported lost or stolen).");
        }
    }
    else if (m_DeclineCode == declineCodePinTryExceeded()) {
        description = tr("The allowable number of PIN tries has been exceeded.");
    }
    else if (m_DeclineCode == declineCodeProcessingError()) {
        description = tr("An error occurred while processing the card.");
    }
    else if (m_DeclineCode == declineCodeReenterTransaction()) {
        description = tr("The payment could not be processed by the issuer for an unknown reason.");
    }
    else if (m_DeclineCode == declineCodeRestrictedCard()) {
        if (omitSensitive) {
            description = tr("The card cannot be used to make this payment");
        }
        else {
            description = tr("The card cannot be used to make this payment (it is possible it has been reported lost or stolen).");
        }
    }
    else if (m_DeclineCode == declineCodeRevocationOfAllAuthorizations()) {
        description = tr("The card has been declined for an unknown reason.");
    }
    else if (m_DeclineCode == declineCodeRevocationOfAuthorization()) {
        description = tr("The card has been declined for an unknown reason.");
    }
    else if (m_DeclineCode == declineCodeSecurityViolation()) {
        description = tr("The card has been declined for an unknown reason.");
    }
    else if (m_DeclineCode == declineCodeServiceNotAllowed()) {
        description = tr("The card has been declined for an unknown reason.");
    }
    else if (m_DeclineCode == declineCodeStolenCard()) {
        if (omitSensitive) {
            description = tr("The payment has been declined.");
        }
        else {
            description = tr("The payment has been declined because the card is reported stolen.");
        }
    }
    else if (m_DeclineCode == declineCodeStopPaymentOrder()) {
        description = tr("The card has been declined for an unknown reason.");
    }
    else if (m_DeclineCode == declineCodeTestmodeDecline()) {
        description = tr("A Stripe test card number was used.");
    }
    else if (m_DeclineCode == declineCodeTransactionNotAllowed()) {
        description = tr("The card has been declined for an unknown reason.");
    }
    else if (m_DeclineCode == declineCodeTryAgainLater()) {
        description = tr("The card has been declined for an unknown reason.");
    }
    else if (m_DeclineCode == declineCodeWithdrawalCountLimitExceeded()) {
        description = tr("The customer has exceeded the balance or credit limit available on their card.");
    }

    return description;
}

QString Error::declineCodeNextSteps(bool omitSensitive) const
{
    QString nextSteps = "";
    if (m_DeclineCode == declineCodeApproveWithId()) {
        nextSteps = tr("The payment should be attempted again. If it still cannot be processed, the customer needs to contact their card issuer.");
    }
    else if (m_DeclineCode == declineCodeCallIssuer()) {
        nextSteps = tr("The customer needs to contact their card issuer for more information.");
    }
    else if (m_DeclineCode == declineCodeCardNotSupported()) {
        nextSteps = tr("The customer needs to contact their card issuer to make sure their card can be used to make this type of purchase.");
    }
    else if (m_DeclineCode == declineCodeCardVelocityExceeded()) {
        nextSteps = tr("The customer should contact their card issuer for more information.");
    }
    else if (m_DeclineCode == declineCodeCurrencyNotSupported()) {
        nextSteps = tr("The customer needs check with the issuer that the card can be used for the type of currency specified.");
    }
    else if (m_DeclineCode == declineCodeDoNotHonor()) {
        nextSteps = tr("The customer needs to contact their card issuer for more information.");
    }
    else if (m_DeclineCode == declineCodeDoNotTryAgain()) {
        nextSteps = tr("The customer should contact their card issuer for more information.");
    }
    else if (m_DeclineCode == declineCodeDuplicateTransaction()) {
        nextSteps = tr("Check to see if a recent payment already exists.");
    }
    else if (m_DeclineCode == declineCodeExpiredCard()) {
        nextSteps = tr("The customer should use another card.");
    }
    else if (m_DeclineCode == declineCodeFraudulent()) {
        nextSteps = tr("The customer needs to contact their card issuer for more information.");
    }
    else if (m_DeclineCode == declineCodeGenericDecline()) {
        nextSteps = tr("The customer needs to contact their card issuer for more information.");
    }
    else if (m_DeclineCode == declineCodeIncorrectNumber()) {
        nextSteps = tr("The customer should try again using the correct card number.");
    }
    else if (m_DeclineCode == declineCodeIncorrectCvc()) {
        nextSteps = tr("The customer should try again using the correct CVC.");
    }
    else if (m_DeclineCode == declineCodeIncorrectPin()) {
        nextSteps = tr("The customer should try again using the correct PIN.");
    }
    else if (m_DeclineCode == declineCodeIncorrectZip()) {
        nextSteps = tr("The customer should try again using the correct billing ZIP/postal code.");
    }
    else if (m_DeclineCode == declineCodeInsufficientFunds()) {
        nextSteps = tr("The customer should use an alternative payment method.");
    }
    else if (m_DeclineCode == declineCodeInvalidAccount()) {
        nextSteps = tr("The customer needs to contact their card issuer to check that the card is working correctly.");
    }
    else if (m_DeclineCode == declineCodeInvalidAmount()) {
        nextSteps = tr("If the amount appears to be correct, the customer needs to check with their card issuer that they can make purchases of that amount.");
    }
    else if (m_DeclineCode == declineCodeInvalidCvc()) {
        nextSteps = tr("The customer should try again using the correct CVC.");
    }
    else if (m_DeclineCode == declineCodeInvalidExpiryYear()) {
        nextSteps = tr("The customer should try again using the correct expiration date.");
    }
    else if (m_DeclineCode == declineCodeInvalidNumber()) {
        nextSteps = tr("The customer should try again using the correct card number.");
    }
    else if (m_DeclineCode == declineCodeInvalidPin()) {
        nextSteps = tr("The customer should try again using the correct PIN.");
    }
    else if (m_DeclineCode == declineCodeIssuerNotAvailable()) {
        nextSteps = tr("The payment should be attempted again. If it still cannot be processed, the customer needs to contact their card issuer.");
    }
    else if (m_DeclineCode == declineCodeLostCard()) {
        if (omitSensitive) {
            nextSteps = tr("The customer needs to contact their card issuer for more information.");
        }
        else {
            nextSteps = tr("The specific reason for the decline should not be reported to the customer. Instead, it needs to be presented as a generic decline.");
        }
    }
    else if (m_DeclineCode == declineCodeNewAccountInformationAvailable()) {
        nextSteps = tr("The customer needs to contact their card issuer for more information.");
    }
    else if (m_DeclineCode == declineCodeNoActionTaken()) {
        nextSteps = tr("The customer should contact their card issuer for more information.");
    }
    else if (m_DeclineCode == declineCodeNotPermitted()) {
        nextSteps = tr("The customer needs to contact their card issuer for more information.");
    }
    else if (m_DeclineCode == declineCodePickupCard()) {
        nextSteps = tr("The customer needs to contact their card issuer for more information.");
    }
    else if (m_DeclineCode == declineCodePinTryExceeded()) {
        nextSteps = tr("The customer must use another card or method of payment.");
    }
    else if (m_DeclineCode == declineCodeProcessingError()) {
        nextSteps = tr("The payment should be attempted again. If it still cannot be processed, try again later.");
    }
    else if (m_DeclineCode == declineCodeReenterTransaction()) {
        nextSteps = tr("The payment should be attempted again. If it still cannot be processed, the customer needs to contact their card issuer.");
    }
    else if (m_DeclineCode == declineCodeRestrictedCard()) {
        nextSteps = tr("The customer needs to contact their card issuer for more information.");
    }
    else if (m_DeclineCode == declineCodeRevocationOfAllAuthorizations()) {
        nextSteps = tr("The customer should contact their card issuer for more information.");
    }
    else if (m_DeclineCode == declineCodeRevocationOfAuthorization()) {
        nextSteps = tr("The customer should contact their card issuer for more information.");
    }
    else if (m_DeclineCode == declineCodeSecurityViolation()) {
        nextSteps = tr("The customer needs to contact their card issuer for more information.");
    }
    else if (m_DeclineCode == declineCodeServiceNotAllowed()) {
        nextSteps = tr("The customer should contact their card issuer for more information.");
    }
    else if (m_DeclineCode == declineCodeStolenCard()) {
        if (omitSensitive) {
            nextSteps = tr("The customer needs to contact their card issuer for more information.");
        }
        else {
            nextSteps = tr("The specific reason for the decline should not be reported to the customer. Instead, it needs to be presented as a generic decline.");
        }

    }
    else if (m_DeclineCode == declineCodeStopPaymentOrder()) {
        nextSteps = tr("The customer should contact their card issuer for more information.");
    }
    else if (m_DeclineCode == declineCodeTestmodeDecline()) {
        nextSteps = tr("A genuine card must be used to make a payment.");
    }
    else if (m_DeclineCode == declineCodeTransactionNotAllowed()) {
        nextSteps = tr("The customer needs to contact their card issuer for more information.");
    }
    else if (m_DeclineCode == declineCodeTryAgainLater()) {
        nextSteps =
            tr("Ask the customer to attempt the payment again. If subsequent payments are declined, the customer should contact their card issuer for more information.");
    }
    else if (m_DeclineCode == declineCodeWithdrawalCountLimitExceeded()) {
        nextSteps = tr("The customer should use an alternative payment method.");
    }

    return nextSteps;
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
        const QString typeString = errorResponse["type"].toString();
        if (typeString == "api_connection_error") {
            m_Type = ErrorType::ErrorApiConnection;
        }
        else if (typeString == "api_error") {
            m_Type = ErrorType::ErrorApi;
        }
        else if (typeString == "authentication_error") {
            m_Type = ErrorType::ErrorAuthentication;
        }
        else if (typeString == "card_error") {
            m_Type = ErrorType::ErrorCard;
        }
        else if (typeString == "idempotency_error") {
            m_Type = ErrorType::ErrorIdempotency;
        }
        else if (typeString == "invalid_request_error") {
            m_Type = ErrorType::ErrorInvalidRequest;
        }
        else if (typeString == "rate_limit_error") {
            m_Type = ErrorType::ErrorRateLimit;
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
        if (errorResponse["code"].toString() == "invalid_number") {
            m_Code = ErrorCode::CodeInvalidNumber;
        }
        else if (errorResponse["code"].toString() == "invalid_expiry_month") {
            m_Code = ErrorCode::CodeInvalidExpiryMonth;
        }
        else if (errorResponse["code"].toString() == "invalid_expiry_year") {
            m_Code = ErrorCode::CodeInvalidExpiryYear;
        }
        else if (errorResponse["code"].toString() == "invalid_cvc") {
            m_Code = ErrorCode::CodeInvalidCVC;
        }
        else if (errorResponse["code"].toString() == "invalid_swipe_data") {
            m_Code = ErrorCode::CodeInvalidSwipeData;
        }
        else if (errorResponse["code"].toString() == "incorrect_number") {
            m_Code = ErrorCode::CodeIncorrectNumber;
        }
        else if (errorResponse["code"].toString() == "expired_card") {
            m_Code = ErrorCode::CodeExpiredCard;
        }
        else if (errorResponse["code"].toString() == "incorrect_cvc") {
            m_Code = ErrorCode::CodeIncorrectCVC;
        }
        else if (errorResponse["code"].toString() == "incorrect_zip") {
            m_Code = ErrorCode::CodeIncorrectZip;
        }
        else if (errorResponse["code"].toString() == "card_declined") {
            m_Code = ErrorCode::CodeCardDeclined;
        }
        else if (errorResponse["code"].toString() == "missing") {
            m_Code = ErrorCode::CodeMissing;
        }
        else if (errorResponse["code"].toString() == "processing_error") {
            m_Code = ErrorCode::CodeProcessingError;
        }
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
