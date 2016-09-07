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

bool QRedisClientReply::operator == (const QRedisClientReply& other) const
{
    if (this->m_request != other.m_request) { return false; };
    if (this->m_success != other.m_success) { return false; }
    if (this->m_type != other.m_type)       { return false; }

    return true;
}

bool QRedisClientReply::operator !=(const QRedisClientReply& other) const
{
    return (*this == other);
}

void QRedisClientReply::addToken(const QRedisProtocolToken& token)
{
    this->m_tokens.append(token);
    if (this->m_tokens.length() >= 2)
    {
        this->m_type = QRedisType::TYPE_ARRAY_REPLY;
    }
}

QRedisClientError QRedisClientReply::error() const
{
    return m_error;
}

bool QRedisClientReply::success() const
{
    Q_ASSERT(this->m_tokens.length() == 1);
    Q_ASSERT(this->m_type != QRedisType::TYPE_ARRAY_REPLY);

    return (this->m_tokens.first().toString() == QStringLiteral("OK"));
}

QRedisType QRedisClientReply::type() const
{
    return m_type;
}

QRedisClientRequest QRedisClientReply::request() const
{
    return m_request;
}

QVector<QRedisProtocolToken>& QRedisClientReply::tokens()
{
    return m_tokens;
}

const QRedisProtocolToken& QRedisClientReply::firstToken() const
{
    Q_ASSERT(!this->m_tokens.isEmpty());
    return this->m_tokens.first();
}

const QRedisProtocolToken&QRedisClientReply::tokenAtIndex(quint32 index) const
{
    return this->m_tokens.at(index);
}

bool QRedisClientReply::isComplete() const
{
    return (request().commandList().length() == this->m_tokens.length());
}
