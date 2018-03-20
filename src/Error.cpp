#include "QStripe/Error.h"

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

void Error::set(QVariantMap errorResponse, int httpCode, int networkErrorCode)
{
    if (errorResponse.contains("error")) {
        errorResponse = errorResponse["error"].toMap();
    }

    m_RawError = errorResponse;
    if (errorResponse.contains("type")) {
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
