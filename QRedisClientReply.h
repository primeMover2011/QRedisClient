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

    enum DataType
    {
        TYPE_STRING,
        TYPE_INT,
        TYPE_LIST,
        TYPE_HASH,
        TYPE_SET,
        TYPE_ARRAY_REPLY,
        TYPE_SORTED_SET,
        TYPE_BYTES,
        TYPE_ERROR,
        TYPE_UNKNOWN
    };

    // How are you handling List vs Set vs SortedSet vs hash?????

    QString toString() const;
    QByteArray toBytes() const;
    qint64 toInt64() const;
    bool toBool() const;
    QRedisClientError toError() const;

    QRedisClientError error() const;
    bool success() const;
    DataType dataType() const;

    QRedisClientRequest request() const;

    QVector<QRedisProtocolToken> tokens() const;

private:
    QRedisClientError m_error;
    bool m_success = false;
    DataType m_dataType = TYPE_UNKNOWN;
    QRedisClientRequest m_request;
    QVector<QRedisProtocolToken> m_tokens;
    bool isComplete() const;
    void addToken(const QRedisProtocolToken &token);



};

#endif // QREDISCLIENTREPLY_H
