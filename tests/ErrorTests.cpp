#include "ErrorTests.h"
#include <QtTest/QtTest>
// QStripe
#include "QStripe/Error.h"

using namespace QStripe;

ErrorTests::ErrorTests(QObject *parent)
    : QObject(parent)
{

}

void ErrorTests::testError()
{
    QVariantMap data;
    data["type"] = "api_connection_error";
    data["charge"] = "here_be_charge_id";
    data["message"] = "Because you can't handle the truth!";

    data["code"] = "invalid_number";
    data["decline_code"] = "¯\\_(ツ)_/¯";
    data["param"] = "number";

    Error error;

    error.set(data, 400, 2);

    QCOMPARE(error.type(), Error::ErrorApiConnection);
    QCOMPARE(error.chargeID(), data["charge"].toString());
    QCOMPARE(error.message(), data["message"].toString());

    QCOMPARE(error.code(), Error::CodeInvalidNumber);
    QCOMPARE(error.declineCode(), data["decline_code"].toString());
    QCOMPARE(error.param(), data["param"].toString());

    QCOMPARE(error.httpStatus(), 400);
    QCOMPARE(error.networkErrorCode(), 2);

    data.remove("type");
    error.set(data, 400, 2);
    QCOMPARE(error.type(), Error::ErrorApiConnection);
}
