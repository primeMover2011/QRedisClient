#ifndef QREDISCLIENTSCRIPT_H
#define QREDISCLIENTSCRIPT_H
//
#include <QString>
#include <QVector>

class QRedisClientScript
{
public:
    QRedisClientScript();

    QVector<QString> arguments() const;
    void setArguments(const QVector<QString>& arguments);

    QVector<QString> keys() const;
    void setKeys(const QVector<QString>& keys);

    QString body() const;
    void setBody(const QString& body);

private:
    QString m_sha1;
    QString m_body;
    QVector<QString> m_arguments;
    QVector<QString> m_keys;

};

#endif // QREDISCLIENTSCRIPT_H
