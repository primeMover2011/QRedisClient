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
    enum TokenType
    {
        TYPE_STRING,
        TYPE_ERROR,
        TYPE_INT,
        TYPE_BYTES,
        TYPE_ARRAY,
        TYPE_UNKNOWN
    };

    QRedisProtocolToken();
    QRedisProtocolToken(const QByteArray &tokenData);

    // Generic Types
    QString toString() const;
    QByteArray toBytes() const;
    qint64 toInt64() const;
    bool toBool() const;
    bool toSuccess() const;
    QRedisTokenList toTokenList() const;
    QRedisClientError toError() const;

    // Redis Specific Types
    QRedisList toList() const;
    QRedisSortedSet toSortedSet() const;
    QRedisSet toSet() const;
    QRedisHash toHash() const;

    // Convrt to hash, list, sorted set, set,

    bool isNull() const;
    bool isValid() const;
    qint32 byteLength() const;


private:
    // iVars
    QByteArray m_bytes;
    QRedisProtocolToken::TokenType m_type;
    qint32 m_byteLength;
    bool m_isNull = false;
    bool m_isValid = false;

    // Methods
    QRedisProtocolToken::TokenType getType(char firstByte);
    void parse(const QByteArray &tokenData);

    void extractString(const QByteArray &tokenData);
    void extractInt(const QByteArray &tokenData);
    void extractBytes(const QByteArray &tokenData);
    void extractArray(const QByteArray &tokenData);
    void extractError(const QByteArray &tokenData);


};

#endif // QREDISPROTOCOLTOKEN_H
