#ifndef QREDISPROTOCOLTOKEN_H
#define QREDISPROTOCOLTOKEN_H
//
#include <QString>
#include <QByteArray>
#include <QVector>
//
#include "QRedisClientError.h"
#include "QRedisClientConstants.h"

class QRedisProtocolToken
{
public:
    QRedisProtocolToken();
    QRedisProtocolToken(const QByteArray &tokenData);

    // Generic Types
    QString toString() const;
    QByteArray toBytes() const;
    qint64 toInt64() const;
    bool toBool() const;
    QRedisTokenList toTokenList() const;
    QRedisClientError toError() const;

    // Redis Specific Types
    QRedisList toList() const;
    QRedisSortedSet toSortedSet() const;
    QRedisSet toSet() const;
    QRedisHash toHash() const;

    bool isOk() const;
    bool isNull() const;
    bool isValid() const;
    qint32 byteLength() const;
    QRedisTokenType type() const;

private:
    // iVars
    QByteArray m_bytes;
    QRedisTokenType m_type  = QRedisTokenType::TKN_TYPE_UNKNOWN;
    qint32 m_byteLength     = 0;
    bool m_isNull           = false;
    bool m_isValid          = false;

    // Methods
    QRedisTokenType getType(char firstByte);
    void parse(const QByteArray &tokenData);

    void extractString(const QByteArray &tokenData);
    void extractInt(const QByteArray &tokenData);
    void extractBytes(const QByteArray &tokenData);
    void extractArray(const QByteArray &tokenData);
    void extractError(const QByteArray &tokenData);


};

#endif // QREDISPROTOCOLTOKEN_H
