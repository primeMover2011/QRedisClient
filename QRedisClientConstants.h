#ifndef QREDISCLIENTCONSTANTS_H
#define QREDISCLIENTCONSTANTS_H
//
#include <QString>
#include <QVector>
#include <QHash>
#include <QMap>
#include <QSet>
//
class QRedisProtocolToken;

typedef QVector<QRedisProtocolToken>    QRedisTokenList;
typedef QVector<QString>                QRedisList;
typedef QHash<QString, QString>         QRedisHash;
typedef QMap<qint64, QString>           QRedisSortedSet;
typedef QSet<QString>                   QRedisSet;

static QByteArray const kCRLF = QByteArrayLiteral("\r\n");

enum QRedisType
{
    TYPE_UNKNOWN        = 100,
    TYPE_INT            = 101,
    TYPE_STRING         = 102,
    TYPE_LIST           = 103,
    TYPE_SET            = 104,
    TYPE_SORTED_SET     = 105,
    TYPE_ARRAY_REPLY    = 106
};

enum QRedisTokenType
{
    TKN_TYPE_INT    = (int)QRedisType::TYPE_INT,
    TKN_TYPE_STRING = (int)QRedisType::TYPE_STRING,
    TKN_TYPE_ARRAY,
    TKN_TYPE_BYTES,
    TKN_TYPE_ERROR,
    TKN_TYPE_UNKNOWN
};






#endif // QREDISCLIENTCONSTANTS_H
