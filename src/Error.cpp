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
    , m_Type()
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

}
