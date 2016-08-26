#ifndef QREDISCLIENT_H
#define QREDISCLIENT_H
//
#include <QObject>
//
#include <QTcpSocket>
//
#include "QRedisClientRequest.h"
#include "QRedisClientReply.h"
#include "QRedisClientConstants.h"
//
class QRedisProtocolToken;
//

class QRedisClient : public QObject
{
    Q_OBJECT
public:
    explicit QRedisClient(QObject *parent = 0);

    void connectToServer(const QHostAddress &address, quint16 port = 6379);

    void sendRequest(QRedisClientRequest& request);


private:
    // iVars
    QTcpSocket *m_socket = new QTcpSocket(this);
    QByteArray m_buffer;
    QVector<QRedisClientReply> m_replies;

    void scanForTokens();


private slots:
    void handleSocketConnected();
    void handleSocketReadyRead();

signals:
    void connected();
    void replyFinished(const QRedisClientReply reply);
    void didParseToken(const QRedisProtocolToken &token);


public slots:
    void handleDidParseToken(const QRedisProtocolToken &token);




};

#endif // QREDISCLIENT_H
