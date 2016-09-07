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
    bool operator != (const QRedisClientRequest &other) const;

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
    QRedisClientRequest& blpop(const QVector<QString>& keys, qint64 timeout);
    QRedisClientRequest& brpop(const QString& key, qint64 timeout);
    QRedisClientRequest& brpop(const QVector<QString>& keys, qint64 timeout);
    QRedisClientRequest& rpop(const QString& key);
    QRedisClientRequest& rpoplpush(const QString& source, const QString &dest);
    QRedisClientRequest& rpush(const QString& key, const QString& value);
    QRedisClientRequest& rpush(const QString& key, const QVector<QString>& values);
    QRedisClientRequest& rpushx(const QString& key, const QString& value);

    // Scripts
    QRedisClientRequest& eval(const QByteArray &script,
                              const QVector<QString> &keys = QVector<QString>(),
                              const QVector<QString> &args = QVector<QString>());


    QRedisClientRequest& evalSha(const QByteArray &sha1,
                                 const QVector<QByteArray> &keys = QVector<QByteArray>(),
                                 const QVector<QByteArray> &args = QVector<QByteArray>());





    QRedisClientRequest& scriptLoad(const QByteArray &script);


    // Server
    QRedisClientRequest& time();
    QRedisClientRequest& clientSetName(const QString &name);

    QByteArray serialize();
    qint64 byteLength() const;

private:
    // iVars
    QVector<QByteArray> m_commandList;
    qint64 m_byteLength = 0;
    bool m_isInternal = false;

    // Getters
    QVector<QByteArray> commandList() const;
    bool isInternal() const;
    QRedisClientRequest& setIsInternal(bool isInternal);

    // Internal DB Methods
    QRedisClientRequest& select(quint8 dbIndex);




};

#endif // QREDISCLIENTREQUEST_H
