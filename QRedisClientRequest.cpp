#include "QRedisClientRequest.h"
//
#include <QDebug>

static QByteArray const kCRLF = QByteArrayLiteral("\r\n");

QRedisClientRequest::QRedisClientRequest()
{

}

bool QRedisClientRequest::operator ==(const QRedisClientRequest& other) const
{
    if (this->m_commandList != other.m_commandList) { return false; }

    return true;
}

QRedisClientRequest& QRedisClientRequest::llen(const QString& key)
{
    QString cmd = QStringLiteral("LLEN %0");
    this->m_commandList.append(cmd.arg(key));
    return *this;
}

QRedisClientRequest&QRedisClientRequest::lindex(const QString &key, qint64 index)
{
    QString cmd = QStringLiteral("LINDEX %0 %1");
    this->m_commandList.append(cmd.arg(key).arg(index));
    return *this;
}

QRedisClientRequest&QRedisClientRequest::linsert(const QString& key, bool before, const QString& pivot, const QString& value)
{
    QString pos = (before) ? QStringLiteral("BEFORE") : QStringLiteral("AFTER");

    QString cmd = QStringLiteral("LINSERT %0 %1 %2 %3");
    this->m_commandList.append(cmd.arg(key).arg(pos).arg(pivot).arg(value));
    return *this;
}

QRedisClientRequest&QRedisClientRequest::lpop(const QString& key)
{
    QString cmd = QStringLiteral("LPOP %0");
    this->m_commandList.append(cmd.arg(key));
    return *this;
}

QRedisClientRequest&QRedisClientRequest::lpush(const QString& key, const QString& value)
{
    QString cmd = QStringLiteral("LPUSH %0 %1");
    this->m_commandList.append(cmd.arg(key).arg(value));
    return *this;
}

QRedisClientRequest&QRedisClientRequest::lpushx(const QString& key, const QString& value)
{
    QString cmd = QStringLiteral("LPUSHX %0 %1");
    this->m_commandList.append(cmd.arg(key).arg(value));
    return *this;
}

QRedisClientRequest&QRedisClientRequest::lrange(const QString& key, qint64 start, qint64 stop)
{
    QString cmd = QStringLiteral("LRANGE %0 %1");
    this->m_commandList.append(cmd.arg(key).arg(start).arg(stop));
    return *this;
}

QRedisClientRequest&QRedisClientRequest::lrem(const QString& key, qint64 count, const QString& value)
{
    QString cmd = QStringLiteral("LREM %0 %1 %3");
    this->m_commandList.append(cmd.arg(key).arg(count).arg(value));
    return *this;
}

QRedisClientRequest&QRedisClientRequest::lrem(const QString& key, qint64 count, qint64 value)
{
    return this->lrem(key, count, QString::number(value));
}

QRedisClientRequest&QRedisClientRequest::lset(const QString& key, qint64 index, const QString& value)
{
    QString cmd = QStringLiteral("LSET %0 %1 %3");
    this->m_commandList.append(cmd.arg(key).arg(index).arg(value));
    return *this;
}

QRedisClientRequest&QRedisClientRequest::ltrim(const QString& key, qint64 start, qint64 stop)
{
    QString cmd = QStringLiteral("LTRIM %0 %1 %3");
    this->m_commandList.append(cmd.arg(key).arg(start).arg(stop));
    return *this;
}

QRedisClientRequest&QRedisClientRequest::blpop(const QString& key, qint64 timeout)
{
    QString cmd = QStringLiteral("BLPOP %0 %1");
    this->m_commandList.append(cmd.arg(key).arg(timeout));
    return *this;
}

QRedisClientRequest&QRedisClientRequest::blpop(const QStringList& keys, qint64 timeout)
{
    QString cmd = QStringLiteral("BLPOP");

    for (int i = 0; i < keys.length(); i++)
    {
        cmd.append(QStringLiteral(" ") + keys.at(i));
    }

    cmd.append(QStringLiteral(" ") + QString::number(timeout));

    this->m_commandList.append(cmd);
    return *this;
}

QRedisClientRequest&QRedisClientRequest::brpop(const QString& key, qint64 timeout)
{
    QString cmd = QStringLiteral("BRPOP %0 %1");
    this->m_commandList.append(cmd.arg(key).arg(timeout));
    return *this;
}

QRedisClientRequest&QRedisClientRequest::brpop(const QStringList& keys, qint64 timeout)
{
    QString cmd = QStringLiteral("BRPOP");

    for (int i = 0; i < keys.length(); i++)
    {
        cmd.append(QStringLiteral(" ") + keys.at(i));
    }

    cmd.append(QStringLiteral(" ") + QString::number(timeout));

    this->m_commandList.append(cmd);
    return *this;
}

QRedisClientRequest&QRedisClientRequest::rpop(const QString& key)
{
    QString cmd = QStringLiteral("RPOP %0");
    this->m_commandList.append(cmd.arg(key));
    return *this;
}

QRedisClientRequest& QRedisClientRequest::rpoplpush(const QString& source, const QString& dest)
{
    QString cmd = QStringLiteral("RPOPLPUSH %0 %1");
    this->m_commandList.append(cmd.arg(source).arg(dest));
    return *this;
}

QRedisClientRequest& QRedisClientRequest::rpush(const QString& key, const QString &value)
{
    QString cmd = QStringLiteral("RPUSH %0 %1");
    this->m_commandList.append(cmd.arg(key).arg(value));
    return *this;
}

QRedisClientRequest&QRedisClientRequest::rpush(const QString& key, const QStringList& values)
{
    QString cmd = QStringLiteral("RPUSH %0");
    cmd = cmd.arg(key);

    for (int i = 0; i < values.length(); i++)
    {
        cmd.append(QStringLiteral(" ") + values.at(i));
    }

    this->m_commandList.append(cmd);
    return *this;
}

QRedisClientRequest&QRedisClientRequest::rpushx(const QString& key, const QString& value)
{
    QString cmd = QStringLiteral("RPUSHX %0 %1");
    this->m_commandList.append(cmd.arg(key).arg(value));
    return *this;
}

QByteArray QRedisClientRequest::serialize()
{
    QByteArray bytes;

    // *2\r\n
    //    $4\r\nLLEN\r\n
    //    $6\r\nmylist\r\n
    qint64 cmdLength = this->m_commandList.length();

    Q_ASSERT(cmdLength > 0);

    for (int i = 0; i < cmdLength; i++)
    {
        QString cString = this->m_commandList.at(i);
        QVector<QStringRef> sep = cString.splitRef(QChar::Space);

        bytes.append("*");
        bytes.append(QByteArray::number(sep.length()));
        bytes.append(kCRLF);

        for (int j = 0; j < sep.length(); j++)
        {
            QStringRef cSep = sep.at(j);
            bytes.append("$");
            bytes.append(QByteArray::number(cSep.length()));
            bytes.append(kCRLF);
            bytes.append(cSep.toString());
            bytes.append(kCRLF);
        }
    }

    this->m_length = bytes.length();
    return bytes;
}

QVector<QString> QRedisClientRequest::commandList() const
{
    return m_commandList;
}

qint64 QRedisClientRequest::length() const
{
    return m_length;
}
