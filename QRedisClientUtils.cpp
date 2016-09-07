#include "QRedisClientUtils.h"
//
#include "QRedisClientConstants.h"
#include <QDebug>

QRedisClientUtils::QRedisClientUtils()
{

}

QString QRedisClientUtils::flattenStr(const QVector<QString>& strings, bool spaced)
{
    QString str;

    qint32 strLen = strings.length();

    for (qint32 i = 0; i < strLen; i++)
    {
        str.append(strings.at(i));
        if ((i + 1) != strLen && spaced) { str.append(QChar::Space); }
    }

    return str;
}

QByteArray QRedisClientUtils::flatten(const QVector<QByteArray>& strings, bool spaced)
{
    QByteArray bytes;

    qint32 strLen = strings.length();

    for (qint32 i = 0; i < strLen; i++)
    {
        bytes.append(strings.at(i));
        if ((i + 1) != strLen && spaced) { bytes.append(QChar::Space); }
    }

    return bytes;
}

QByteArray QRedisClientUtils::makeBulkString(const QByteArray& data)
{
    QByteArray bytes = QByteArrayLiteral("$");
    bytes.append(QByteArray::number(data.length()))
            .append(kCRLF)
            .append(data)
            .append(kCRLF);

    return bytes;
}

QByteArray QRedisClientUtils::toArrayOfBulkStrings(const QVector<QByteArray> &data)
{
    QByteArray bytes = QByteArrayLiteral("*");
    bytes.append(QByteArray::number(data.length())) .append(kCRLF);

    for (const QByteArray &cData : data)
    {
        bytes.append(QRedisClientUtils::makeBulkString(cData));
    }

    return bytes;
}

QByteArray QRedisClientUtils::toArrayOfBulkStrings(const QVector<QString> &strings)
{
    QByteArray bytes = QByteArrayLiteral("*");
    bytes.append(QByteArray::number(strings.length())) .append(kCRLF);

    for (const QString &cString : strings)
    {
        bytes.append(QRedisClientUtils::makeBulkString(cString.toUtf8()));
    }

    return bytes;
}
