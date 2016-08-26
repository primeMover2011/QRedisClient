#ifndef QREDISCLIENTREQUEST_H
#define QREDISCLIENTREQUEST_H
//
#include <QByteArray>
#include <QString>
#include <QVector>

class QRedisClientRequest
{
    friend class QRedisClientReply;
    friend class QRedisClient;
public:
    QRedisClientRequest();

    // Operators
    bool operator == (const QRedisClientRequest &other) const;


    // List
    QRedisClientRequest& llen(const QString& key);
    QRedisClientRequest& lindex(const QString& key, qint64 index);
    QRedisClientRequest& linsert(const QString& key, bool before, const QString &pivot, const QString &value);
    QRedisClientRequest& lpop(const QString& key);
    QRedisClientRequest& lpush(const QString& key, const QString &value);
    QRedisClientRequest& lpushx(const QString& key, const QString &value);
    QRedisClientRequest& lrange(const QString& key, qint64 start, qint64 stop);
    QRedisClientRequest& lrem(const QString& key, qint64 count, const QString &value);
    QRedisClientRequest& lrem(const QString& key, qint64 count, qint64 value);
    QRedisClientRequest& lset(const QString& key, qint64 index, const QString &value);
    QRedisClientRequest& ltrim(const QString& key, qint64 start, qint64 stop);

    QRedisClientRequest& blpop(const QString& key, qint64 timeout);
    QRedisClientRequest& blpop(const QStringList& keys, qint64 timeout);
    QRedisClientRequest& brpop(const QString& key, qint64 timeout);
    QRedisClientRequest& brpop(const QStringList& keys, qint64 timeout);
    QRedisClientRequest& rpop(const QString& key);
    QRedisClientRequest& rpoplpush(const QString& source, const QString &dest);
    QRedisClientRequest& rpush(const QString& key, const QString& value);
    QRedisClientRequest& rpush(const QString& key, const QStringList& values);
    QRedisClientRequest& rpushx(const QString& key, const QString& value);

    QByteArray serialize();
    qint64 length() const;

private:
    QVector<QString> m_commandList;
    qint64 m_length = 0;
    QVector<QString> commandList() const;



};

#endif // QREDISCLIENTREQUEST_H
