#include "QRedisClient.h"
//
#include <QDebug>
#include "QRedisProtocolToken.h"

QRedisClient::QRedisClient(QObject *parent) : QObject(parent)
{
    // Setup Socket
    QObject::connect(this->m_socket, &QTcpSocket::connected,
                     this, &QRedisClient::handleSocketConnected);

    QObject::connect(this->m_socket, &QTcpSocket::readyRead,
                     this, &QRedisClient::handleSocketReadyRead);
}

void QRedisClient::connectToServer(const QHostAddress &address, quint16 port)
{
    this->m_socket->connectToHost(address, port);
}

void QRedisClient::sendRequest(QRedisClientRequest& request)
{
    QByteArray requestData = request.serialize();

    Q_ASSERT(requestData.length() > 0);
    this->m_replies.append(request);
    this->m_socket->write(requestData);

    qDebug() << requestData;
}

void QRedisClient::scanForTokens()
{
    while(true)
    {
        QRedisProtocolToken token(this->m_buffer);
        if (!token.isValid()) { break; }

        emit this->didParseToken(token);
        this->handleDidParseToken(token);

        this->m_buffer.remove(0, token.byteLength());

        if (this->m_buffer.isEmpty()) { break; }
    }
}

// Handlers
void QRedisClient::handleSocketConnected()
{
    emit this->connected();
}

void QRedisClient::handleSocketReadyRead()
{
    while (this->m_socket->bytesAvailable())
    {
        this->m_buffer.append(this->m_socket->read(128));
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
        emit this->replyFinished(reply);
    }
}
