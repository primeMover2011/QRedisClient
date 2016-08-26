#include "QRedisClientError.h"

QRedisClientError::QRedisClientError()
{

}

QRedisClientError QRedisClientError::noError()
{
    QRedisClientError error;
    error.m_code = Code::ERR_NONE;
    return error;
}

QString QRedisClientError::string() const
{
    return m_string;
}

QRedisClientError::Code QRedisClientError::code() const
{
    return m_code;
}

void QRedisClientError::setErrorCode(const QByteArray &errorCodeString)
{
    if (errorCodeString == QByteArrayLiteral("ERR"))
    {
        this->m_code = Code::ERR_UNKNOWN;
        return;
    }

    if (errorCodeString == QByteArrayLiteral("WRONGTYPE"))
    {
        this->m_code = Code::ERR_WRONGTYPE;
        return;
    }
}


