#include "QRedisClientScript.h"
//
#include <QDebug>
//
#include "QRedisProtocolToken.h"


QRedisClientScript::QRedisClientScript()
{

}

QByteArray QRedisClientScript::sha1() const
{
    return m_sha1;
}

QByteArray QRedisClientScript::body() const
{
    return m_body;
}

const QVector<QByteArray>& QRedisClientScript::keys() const
{
    return m_keys;
}

QRedisClientScript& QRedisClientScript::setBody(const QByteArray& body)
{
    m_body = body;
    this->parseConfig();
    return *this;
}

QRedisClientScript&QRedisClientScript::addKey(const QByteArray& key)
{
    this->m_keys.append(key);
    return *this;
}

QString QRedisClientScript::name() const
{
    return m_name;
}

void QRedisClientScript::parseConfig()
{
    QByteArray marker = QByteArrayLiteral("--[[QRedisClientScriptConfig");

    qint32 idxStart = this->m_body.indexOf(marker);
    if (idxStart == -1) { return; }

    idxStart += marker.length();

    qint32 idxEnd = this->m_body.mid(idxStart).indexOf(QByteArrayLiteral("--]]"));

    QJsonObject jObj = QJsonDocument::fromJson(this->m_body.mid(idxStart, idxEnd)).object();
    Q_ASSERT(!jObj.isEmpty());

    this->m_name = jObj.value(QStringLiteral("name")).toString();

    for (const QJsonValue &cKey : jObj.value(QStringLiteral("keys")).toArray())
    {
        this->m_keys.append(cKey.toString().toUtf8());
    }
}

void QRedisClientScript::setName(const QString& name)
{
    m_name = name;
}

void QRedisClientScript::setSha1(const QByteArray& sha1)
{
    m_sha1 = sha1;
}


