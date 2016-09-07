#ifndef QREDISCLIENTUTILS_H
#define QREDISCLIENTUTILS_H
//
#include <QString>
#include <QVector>
#include <QStringList>
#include <QByteArray>

class QRedisClientUtils
{
public:
    QRedisClientUtils();

    // TODO: It seems silly to have two seperate methods for this.
    static QString flattenStr(const QVector<QString>& strings, bool spaced = true);
    static QByteArray flatten(const QVector<QByteArray>& strings, bool spaced = true);

    static QByteArray makeBulkString(const QByteArray &data);
    static QByteArray toArrayOfBulkStrings(const QVector<QByteArray> &data);
    static QByteArray toArrayOfBulkStrings(const QVector<QString> &strings);
};

#endif // QREDISCLIENTUTILS_H
