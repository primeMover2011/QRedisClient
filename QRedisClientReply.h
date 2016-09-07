#ifndef QREDISCLIENTREPLY_H
#define QREDISCLIENTREPLY_H
//
#include <QByteArray>
#include <QChar>
#include <QString>
#include <QVariant>
//
#include "QRedisClientError.h"
#include "QRedisClientRequest.h"
#include "QRedisProtocolToken.h"
#include "QRedisClientConstants.h"
//
class QRedisClient;

class QRedisClientReply
{
    friend class QRedisClient;
public:
    QRedisClientReply();
    QRedisClientReply(const QRedisClientRequest &request);

    // Operators
    bool operator == (const QRedisClientReply &other) const;
    bool operator != (const QRedisClientReply &other) const;

    QRedisClientError error() const;
    bool success() const;
    QRedisType type() const;

    QRedisClientRequest request() const;

    QVector<QRedisProtocolToken>& tokens();

    const QRedisProtocolToken& firstToken() const;
    const QRedisProtocolToken& tokenAtIndex(quint32 index) const;


private:
    // iVars
    QRedisClientError m_error;
    bool m_success      = false;
    QRedisType m_type   = QRedisType::TYPE_UNKNOWN;
    QRedisClientRequest m_request;
    QVector<QRedisProtocolToken> m_tokens;

    // Methods
    bool isComplete() const;
    void addToken(const QRedisProtocolToken &token);



};

#endif // QREDISCLIENTREPLY_H
