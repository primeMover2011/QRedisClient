#include "QRedisClientReply.h"
//
#include <QDebug>
//

QRedisClientReply::QRedisClientReply()
{

}

QRedisClientReply::QRedisClientReply(const QRedisClientRequest &request) :
    m_request(request)
{

}

QString QRedisClientReply::toString() const
{
    return this->m_tokens.first().toString();
}

QByteArray QRedisClientReply::toBytes() const
{
    return this->m_tokens.first().toBytes();
}

bool QRedisClientReply::toBool() const
{
    return this->m_tokens.first().toBool();
}

qint64 QRedisClientReply::toInt64() const
{
    return this->m_tokens.first().toInt64();
}

QRedisClientError QRedisClientReply::toError() const
{
    return this->m_tokens.first().toError();
}

void QRedisClientReply::addToken(const QRedisProtocolToken& token)
{
    this->m_tokens.append(token);
    if (this->m_tokens.length() >= 2)
    {
        this->m_dataType = DataType::TYPE_ARRAY_REPLY;
    }
}

QRedisClientError QRedisClientReply::error() const
{
    return m_error;
}

bool QRedisClientReply::success() const
{
    Q_ASSERT(this->m_tokens.length() == 1);
    return this->m_tokens.first().toSuccess();
}

QRedisClientReply::DataType QRedisClientReply::dataType() const
{
    return m_dataType;
}

QRedisClientRequest QRedisClientReply::request() const
{
    return m_request;
}

QVector<QRedisProtocolToken> QRedisClientReply::tokens() const
{
    return m_tokens;
}

bool QRedisClientReply::isComplete() const
{
    return (request().commandList().length() == this->m_tokens.length());
}
