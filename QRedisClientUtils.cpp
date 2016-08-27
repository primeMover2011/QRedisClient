#include "QRedisClientUtils.h"
//
#include "QRedisClientConstants.h"
#include <QDebug>

QRedisClientUtils::QRedisClientUtils()
{

}

QByteArray QRedisClientUtils::flatten(const QVector<QString>& strings)
{
    QByteArray bytes;


    qint32 bLen = strings.length();

    for (qint32 i = 0; i < bLen; i++)
    {
        const QString &cStr = strings.at(i);
        bytes.append(cStr);
        if ((i + 1) != bLen)
        {
            bytes.append(QChar::Space);
        }
    }

    return bytes;
}

QByteArray QRedisClientUtils::makeBulkString(const QByteArray& data)
{
    QByteArray bytes;

    bytes.append(QByteArrayLiteral("$"))
            .append(QByteArray::number(data.length()))
            .append(kCRLF)
            .append(data)
            .append(kCRLF);

    return bytes;
}

QByteArray QRedisClientUtils::toArrayOfBulkStrings(const QVector<QByteArray> &data)
{
    QByteArray bytes = QByteArrayLiteral("*");
    bytes.append(QByteArray::number(data.length())).append(kCRLF);

    for (const QByteArray &cData : data)
    {
        bytes.append(QRedisClientUtils::makeBulkString(cData));
    }

    return bytes;
}
