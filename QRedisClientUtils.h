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

    static QByteArray flatten(const QVector<QString> &strings);
    static QByteArray makeBulkString(const QByteArray &data);
    static QByteArray toArrayOfBulkStrings(const QVector<QByteArray> &data);



};

#endif // QREDISCLIENTUTILS_H
