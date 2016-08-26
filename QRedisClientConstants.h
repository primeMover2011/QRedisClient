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

#endif // QREDISCLIENTCONSTANTS_H
