#ifndef QREDISCLIENTSCRIPT_H
#define QREDISCLIENTSCRIPT_H
//
#include <QString>
#include <QVector>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>

class QRedisClientScript
{
    friend class QRedisClient;
public:
    QRedisClientScript();

    // Getters
    QByteArray sha1() const;
    QByteArray body() const;
    const QVector<QByteArray>& keys() const;

    // Setters
    QRedisClientScript& setBody(const QByteArray& body);

    // Methods
    QRedisClientScript& addKey(const QByteArray &key);

    QString name() const;
    void setName(const QString& name);

private:
    // iVars
    QByteArray m_sha1;
    QByteArray m_body;
    QVector<QByteArray> m_arguments;
    QVector<QByteArray> m_keys;
    QString m_name;

    void setSha1(const QByteArray& sha1);
    void setArguments(const QVector<QByteArray>& arguments);
    void parseConfig();

};

#endif // QREDISCLIENTSCRIPT_H
