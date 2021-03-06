#include "QRedisClientRequest.h"
//
#include <QDebug>
//
#include "QRedisClientConstants.h"
#include "QRedisClientUtils.h"

QRedisClientRequest::QRedisClientRequest()
{

}

bool QRedisClientRequest::operator == (const QRedisClientRequest& other) const
{
    if (this->m_commandList != other.m_commandList) { return false; }
    if (this->m_byteLength != other.m_byteLength)   { return false; }
    if (this->m_isInternal != other.m_isInternal)   { return false; }

    return true;
}

bool QRedisClientRequest::operator != (const QRedisClientRequest& other) const
{
    return !(*this == other);
}

QRedisClientRequest& QRedisClientRequest::llen(const QString& key)
{
    this->m_commandList.append(QRedisClientUtils::toArrayOfBulkStrings(QVector<QByteArray> {
                                                                           QByteArrayLiteral("LLEN"),
                                                                           key.toUtf8()
                                                                       }));

    return *this;
}

QRedisClientRequest&QRedisClientRequest::lindex(const QString &key, qint64 index)
{
    this->m_commandList.append(QRedisClientUtils::toArrayOfBulkStrings(QVector<QByteArray> {
                                                                           QByteArrayLiteral("LINDEX"),
                                                                           key.toUtf8(),
                                                                           QByteArray::number(index),
                                                                       }));
    return *this;
}

QRedisClientRequest&QRedisClientRequest::linsert(const QString& key, bool before, const QString& pivot, const QString& value)
{
    this->m_commandList.append(QRedisClientUtils::toArrayOfBulkStrings(QVector<QByteArray> {
                                                                           QByteArrayLiteral("LINSERT"),
                                                                           key.toUtf8(),
                                                                           (before) ? QByteArrayLiteral("BEFORE") : QByteArrayLiteral("AFTER"),
                                                                           pivot.toUtf8(),
                                                                           value.toUtf8()
                                                                       }));
    return *this;
}

QRedisClientRequest&QRedisClientRequest::lpop(const QString& key)
{
    this->m_commandList.append(QRedisClientUtils::toArrayOfBulkStrings(QVector<QByteArray> {
                                                                           QByteArrayLiteral("LPOP"),
                                                                           key.toUtf8()
                                                                       }));
    return *this;
}

QRedisClientRequest&QRedisClientRequest::lpush(const QString& key, const QString& value)
{
    this->m_commandList.append(QRedisClientUtils::toArrayOfBulkStrings(QVector<QByteArray> {
                                                                           QByteArrayLiteral("LPUSH"),
                                                                           key.toUtf8(),
                                                                           value.toUtf8()
                                                                       }));

    return *this;
}

QRedisClientRequest&QRedisClientRequest::lpushx(const QString& key, const QString& value)
{
    this->m_commandList.append(QRedisClientUtils::toArrayOfBulkStrings(QVector<QByteArray> {
                                                                           QByteArrayLiteral("LPUSHX"),
                                                                           key.toUtf8(),
                                                                           value.toUtf8()
                                                                       }));
    return *this;
}

QRedisClientRequest&QRedisClientRequest::lrange(const QString& key, qint64 start, qint64 stop)
{
    this->m_commandList.append(QRedisClientUtils::toArrayOfBulkStrings(QVector<QByteArray> {
                                                                           QByteArrayLiteral("LRANGE"),
                                                                           key.toUtf8(),
                                                                           QByteArray::number(start),
                                                                           QByteArray::number(stop)
                                                                       }));
    return *this;
}

QRedisClientRequest&QRedisClientRequest::lrem(const QString& key, qint64 count, const QString& value)
{
    this->m_commandList.append(QRedisClientUtils::toArrayOfBulkStrings(QVector<QByteArray> {
                                                                           QByteArrayLiteral("LREM"),
                                                                           key.toUtf8(),
                                                                           QByteArray::number(count),
                                                                           value.toUtf8()
                                                                       }));
    return *this;
}

QRedisClientRequest&QRedisClientRequest::lrem(const QString& key, qint64 count, qint64 value)
{
    return this->lrem(key, count, QString::number(value));
}

QRedisClientRequest&QRedisClientRequest::lset(const QString& key, qint64 index, const QString& value)
{
    this->m_commandList.append(QRedisClientUtils::toArrayOfBulkStrings(QVector<QByteArray> {
                                                                           QByteArrayLiteral("LSET"),
                                                                           key.toUtf8(),
                                                                           QByteArray::number(index),
                                                                           value.toUtf8()
                                                                       }));
    return *this;
}

QRedisClientRequest&QRedisClientRequest::ltrim(const QString& key, qint64 start, qint64 stop)
{
    this->m_commandList.append(QRedisClientUtils::toArrayOfBulkStrings(QVector<QByteArray> {
                                                                           QByteArrayLiteral("LTRIM"),
                                                                           key.toUtf8(),
                                                                           QByteArray::number(start),
                                                                           QByteArray::number(stop)
                                                                       }));
    return *this;
}

QRedisClientRequest&QRedisClientRequest::blpop(const QString& key, qint64 timeout)
{
    this->m_commandList.append(QRedisClientUtils::toArrayOfBulkStrings(QVector<QByteArray> {
                                                                           QByteArrayLiteral("BLPOP"),
                                                                           key.toUtf8(),
                                                                           QByteArray::number(timeout)
                                                                       }));
    return *this;
}

QRedisClientRequest&QRedisClientRequest::blpop(const QVector<QString>& keys, qint64 timeout)
{
    this->m_commandList.append(QRedisClientUtils::toArrayOfBulkStrings(QVector<QByteArray> {
                                                                           QByteArrayLiteral("BLPOP"),
                                                                           QRedisClientUtils::flattenStr(keys).toUtf8(),
                                                                           QByteArray::number(timeout)
                                                                       }));
    return *this;
}

QRedisClientRequest&QRedisClientRequest::brpop(const QString& key, qint64 timeout)
{
    this->m_commandList.append(QRedisClientUtils::toArrayOfBulkStrings(QVector<QByteArray> {
                                                                           QByteArrayLiteral("BRPOP"),
                                                                           key.toUtf8(),
                                                                           QByteArray::number(timeout)
                                                                       }));
    return *this;
}

QRedisClientRequest&QRedisClientRequest::brpop(const QVector<QString>& keys, qint64 timeout)
{
    this->m_commandList.append(QRedisClientUtils::toArrayOfBulkStrings(QVector<QByteArray> {
                                                                           QByteArrayLiteral("BRPOP"),
                                                                           QRedisClientUtils::flattenStr(keys).toUtf8(),
                                                                           QByteArray::number(timeout)
                                                                       }));
    return *this;
}

QRedisClientRequest&QRedisClientRequest::rpop(const QString& key)
{
    this->m_commandList.append(QRedisClientUtils::toArrayOfBulkStrings(QVector<QByteArray> {
                                                                           QByteArrayLiteral("RPOP"),
                                                                           key.toUtf8()
                                                                       }));
    return *this;
}

QRedisClientRequest& QRedisClientRequest::rpoplpush(const QString& source, const QString& dest)
{
    this->m_commandList.append(QRedisClientUtils::toArrayOfBulkStrings(QVector<QByteArray> {
                                                                           QByteArrayLiteral("RPOPLPUSH"),
                                                                           source.toUtf8(),
                                                                           dest.toUtf8()
                                                                       }));
    return *this;
}

QRedisClientRequest& QRedisClientRequest::rpush(const QString& key, const QString &value)
{
    this->m_commandList.append(QRedisClientUtils::toArrayOfBulkStrings(QVector<QByteArray> {
                                                                           QByteArrayLiteral("RPUSH"),
                                                                           key.toUtf8(),
                                                                           value.toUtf8()
                                                                       }));
    return *this;
}

QRedisClientRequest& QRedisClientRequest::rpush(const QString& key, const QVector<QString>& values)
{
    this->m_commandList.append(QRedisClientUtils::toArrayOfBulkStrings(QVector<QByteArray> {
                                                                           QByteArrayLiteral("RPUSH"),
                                                                           key.toUtf8(),
                                                                           QRedisClientUtils::flattenStr(values).toUtf8()
                                                                       }));
    return *this;
}

QRedisClientRequest& QRedisClientRequest::rpushx(const QString& key, const QString& value)
{
    this->m_commandList.append(QRedisClientUtils::toArrayOfBulkStrings(QVector<QByteArray> {
                                                                           QByteArrayLiteral("RPUSHX"),
                                                                           key.toUtf8(),
                                                                           value.toUtf8()
                                                                       }));
    return *this;
}

QRedisClientRequest&QRedisClientRequest::eval(const QByteArray& script, const QVector<QString>& keys, const QVector<QString>& args)
{
    Q_ASSERT(!script.isEmpty());

    QVector<QByteArray> cmd
    {
        QByteArrayLiteral("EVAL"),
        script,
        QByteArray::number(keys.length())
    };

    for (const QString &cKey : keys) { cmd.append(cKey.toUtf8()); }
    for (const QString &cArg : args) { cmd.append(cArg.toUtf8()); }

    this->m_commandList.append(QRedisClientUtils::toArrayOfBulkStrings(cmd));
    return *this;
}

QRedisClientRequest&QRedisClientRequest::evalSha(const QByteArray& sha1, const QVector<QByteArray>& keys, const QVector<QByteArray>& args)
{
    //EVALSHA sha1 numkeys key [key ...] arg [arg ...]

    QVector<QByteArray> cmd
    {
        QByteArrayLiteral("EVALSHA"),
        sha1,
        QByteArray::number(keys.length())
    };

    for (const QString &cKey : keys) { cmd.append(cKey.toUtf8()); }
    for (const QString &cArg : args) { cmd.append(cArg.toUtf8()); }

    this->m_commandList.append(QRedisClientUtils::toArrayOfBulkStrings(cmd));
    return *this;
}

QRedisClientRequest&QRedisClientRequest::scriptLoad(const QByteArray& script)
{
    this->m_commandList.append(QRedisClientUtils::toArrayOfBulkStrings(QVector<QByteArray>
    {
        QByteArrayLiteral("SCRIPT"),
        QByteArrayLiteral("LOAD"),
        script
    }));

    return *this;
}

QRedisClientRequest& QRedisClientRequest::time()
{
    this->m_commandList.append(QRedisClientUtils::toArrayOfBulkStrings(QVector<QByteArray> {
                                                                           QByteArrayLiteral("TIME")
                                                                       }));

    return *this;
}

QRedisClientRequest&QRedisClientRequest::clientSetName(const QString& name)
{
    this->m_commandList.append(QRedisClientUtils::toArrayOfBulkStrings(QVector<QByteArray> {
                                                                           QByteArrayLiteral("CLIENT"),
                                                                           QByteArrayLiteral("SETNAME"),
                                                                           name.toUtf8()
                                                                       }));

    return *this;
}

QRedisClientRequest& QRedisClientRequest::select(quint8 dbIndex)
{
    this->m_commandList.append(QRedisClientUtils::toArrayOfBulkStrings(QVector<QByteArray> {
                                                                           QByteArrayLiteral("SELECT"),
                                                                           QByteArray::number(dbIndex)
                                                                       }));
    return *this;
}

//QRedisClientRequest&QRedisClientRequest::eval(const QString& script, const QVector<QString>& keys, const QVector<QString>& args)
//{
//    QString keyArgs;

//    if (!keys.isEmpty())
//    {
//        for (int i = 0; i < keys.length(); i++)
//        {
//            const QString &cString = keys.at(i);
//            keyArgs.append(cString);

//            if (i + 1 != keys.length())
//            {
//                keyArgs.append(" ");
//            }
//        }
//    }

//    if (!args.isEmpty())
//    {
//        keyArgs.append(" ");
//        for (int i = 0; i < args.length(); i++)
//        {
//            const QString &cArg = args.at(i);
//            keyArgs.append(cArg);

//            if (i + 1 != args.length())
//            {
//                keyArgs.append(" ");
//            }
//        }
//    }



//    // EVAL script numkeys key [key ...] arg [arg ...]

////    QByteArray bytes;
////    bytes.append("*5\r\n");
////    bytes.append("$4\r\nEVAL\r\n");
////    bytes.append("$14\r\nreturn KEYS[1]\r\n");
////    bytes.append("$1\r\n2\r\n");
////    bytes.append("$4\r\nkey1\r\n");
////    bytes.append("$4\r\narg1\r\n");

//    // EVAL script numkeys key [key ...] arg [arg ...]
//    QString cmd = QStringLiteral("EVAL \"%0\" %1 %2");
//    cmd = cmd.arg(script).arg(keys.length()).arg(keyArgs);

//    qDebug() << cmd.trimmed();

//    this->m_commandList.append(cmd.trimmed());
//    return *this;
//}

QByteArray QRedisClientRequest::serialize()
{
    QByteArray bytes = QRedisClientUtils::flatten(this->m_commandList, false);
    this->m_byteLength = bytes.length();
    return bytes;
}

QVector<QByteArray> QRedisClientRequest::commandList() const
{
    return m_commandList;
}

QRedisClientRequest& QRedisClientRequest::setIsInternal(bool isInternal)
{
    m_isInternal = isInternal;
    return *this;
}

bool QRedisClientRequest::isInternal() const
{
    return m_isInternal;
}

qint64 QRedisClientRequest::byteLength() const
{
    return m_byteLength;
}
