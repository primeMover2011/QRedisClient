#include "QRedisClientScript.h"
//
#include "QRedisProtocolToken.h"

QRedisClientScript::QRedisClientScript()
{

}


QVector<QString> QRedisClientScript::arguments() const
{
    return m_arguments;
}

void QRedisClientScript::setArguments(const QVector<QString>& arguments)
{
    m_arguments = arguments;
}

QVector<QString> QRedisClientScript::keys() const
{
    return m_keys;
}

void QRedisClientScript::setKeys(const QVector<QString>& keys)
{
    m_keys = keys;
}

QString QRedisClientScript::body() const
{
    return m_body;
}

void QRedisClientScript::setBody(const QString& body)
{
    m_body = body;
}
