#include "QRedisClient.h"
//
#include <QDebug>
#include "QRedisProtocolToken.h"
#include "QRedisClientUtils.h"
#include <QThread>

QRedisClient::QRedisClient(QObject *parent) : QObject(parent)
{
    // Setup Socket
    QObject::connect(this->m_socket, &QTcpSocket::connected,
                     this, &QRedisClient::handleSocketConnected);

    QObject::connect(this->m_socket, &QTcpSocket::disconnected,
                     this, &QRedisClient::handleSocketDidDisconnect);

    QObject::connect(this->m_socket, &QTcpSocket::readyRead,
                     this, &QRedisClient::handleSocketReadyRead);
}

void QRedisClient::connectToServer(const QHostAddress &address, quint16 port)
{
    this->m_socket->connectToHost(address, port);
}

void QRedisClient::sendRequest(QRedisClientRequest& request)
{
    Q_ASSERT(this->m_socket->isOpen());

    QByteArray requestData = request.serialize();

    Q_ASSERT(requestData.length() > 0);
    this->m_replies.append(request);
    this->m_socket->write(requestData);
    //qDebug() << requestData;
}

QRedisClientRequest QRedisClient::executeScript(const QString& name, const QVector<QByteArray>& args)
{
    for (const QRedisClientScript &cScript : this->m_scripts)
    {
        if (cScript.name() == name)
        {
            QRedisClientRequest req;
            req.evalSha(cScript.sha1(), cScript.keys(), args);
            this->sendRequest(req);
            return req;
        }
    }

    // No script exists with that name.
    Q_ASSERT(false);
    return QRedisClientRequest();
}

void QRedisClient::registerScript(const QRedisClientScript& script)
{
    this->m_scripts.append(script);
}

void QRedisClient::registerScriptsInDirectory(const QDir& dir)
{
    QDir dbScript(dir);
    Q_ASSERT(dbScript.exists());

    dbScript.setNameFilters({"*.lua"});

    for (const QString &cFileName : dbScript.entryList())
    {
        QFile cFile(dbScript.absoluteFilePath(cFileName));
        Q_ASSERT(cFile.open(QFile::ReadOnly));

        QRedisClientScript cScript;
        cScript.setBody(cFile.readAll());
        this->registerScript(cScript);

        qDebug().noquote().nospace()
                << "QRedisClient: Registerd Script \""
                << cScript.name() << "\"";

        cFile.close();
    }
}

void QRedisClient::scanForTokens()
{
    while(true)
    {
        if (this->m_buffer.isEmpty()) { break; }

        QRedisProtocolToken token(this->m_buffer);
        if (!token.isValid()) { break; }

        this->handleDidParseToken(token);

        this->m_buffer.remove(0, token.byteLength());
    }
}

void QRedisClient::setupConnection()
{
    Q_ASSERT(!this->m_isReady);
    Q_ASSERT(this->m_socket->isOpen());

    QRedisClientRequest req;
    req.setIsInternal(true)
            .select(this->m_dbIndex)
            .clientSetName(this->m_name);

    for (const QRedisClientScript &cScript : this->m_scripts)
    {
        req.scriptLoad(cScript.body());
    }

    this->sendRequest(req);
}

// Socket Handlers
void QRedisClient::handleSocketConnected()
{
    this->setupConnection();
}

void QRedisClient::handleSocketDidDisconnect()
{
    this->m_isReady = false;
}

void QRedisClient::handleSocketReadyRead()
{
    while (this->m_socket->bytesAvailable())
    {
        QByteArray data = this->m_socket->read(128);
        //qDebug() << data;
        this->m_buffer.append(data);
    }

    this->scanForTokens();
}

void QRedisClient::handleDidParseToken(const QRedisProtocolToken& token)
{
    Q_ASSERT(!this->m_replies.isEmpty());

    QRedisClientReply &reply = this->m_replies.first();
    reply.addToken(token);

    if (reply.isComplete())
    {
        // Make a copy of the reply.
        QRedisClientReply r(reply);

        // Remove the origional.
        this->m_replies.removeFirst();

        if (!r.request().isInternal())
        {
            emit this->replyFinished(r);
        }
        else
        {
            this->handleInternalReply(r);
        }
    }
}

void QRedisClient::handleInternalReply(QRedisClientReply& reply)
{
    Q_ASSERT(reply.type() == QRedisType::TYPE_ARRAY_REPLY);

    bool didSelectDb   = reply.tokenAtIndex(0).isOk();
    bool didSetName    = reply.tokenAtIndex(1).isOk();
    //
    Q_ASSERT(reply.tokens().length() - 2 >= this->m_scripts.length());

    for (int i = 2; i < reply.tokens().length(); i++)
    {
        QRedisClientScript &cScript = this->m_scripts[i - 2];
        cScript.setSha1(reply.tokens().at(i).toString().toUtf8());
    }

    if (!didSelectDb || !didSetName)
    {
        this->m_isReady = false;
        Q_ASSERT(false);
    }

    this->m_isReady = true;

    emit this->ready();
}

// Getters & Setters
quint8 QRedisClient::dbIndex() const
{
    return m_dbIndex;
}

void QRedisClient::setDbIndex(const quint8& dbIndex)
{
    // No support for changing the connected DB on the fly.
    Q_ASSERT(!this->m_isReady);
    m_dbIndex = dbIndex;
}

bool QRedisClient::isReady() const
{
    return m_isReady;
}

QHostAddress QRedisClient::serverAddress() const
{
    return this->m_socket->peerAddress();
}
