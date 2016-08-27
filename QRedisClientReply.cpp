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

    return this->m_tokens.first().toSuccess();
}

QRedisType QRedisClientReply::type() const
{
    return m_type;
}

QRedisClientRequest QRedisClientReply::request() const
{
    return m_request;
}

QVector<QRedisProtocolToken> QRedisClientReply::tokens() const
{
    return m_tokens;
}

const QRedisProtocolToken& QRedisClientReply::firstToken() const
{
    Q_ASSERT(!this->m_tokens.isEmpty());
    return this->m_tokens.first();
}

bool QRedisClientReply::isComplete() const
{
    return (request().commandList().length() == this->m_tokens.length());
}
