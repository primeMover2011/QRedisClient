#ifndef QREDISCLIENT_H
#define QREDISCLIENT_H
//
#include <QObject>
//
#include <QTcpSocket>
#include <QHash>
#include <QVector>
#include <QString>
#include <QDir>
#include <QHostAddress>
//
#include "QRedisClientRequest.h"
#include "QRedisClientReply.h"
#include "QRedisClientConstants.h"
#include "QRedisClientScript.h"
#include "QRedisProtocolToken.h"

class QRedisClient : public QObject
{
    Q_OBJECT
public:
    explicit QRedisClient(QObject *parent = 0);

    void connectToServer(const QHostAddress &address, quint16 port = 6379);
    void registerScript(const QRedisClientScript &script);
    void registerScriptsInDirectory(const QDir &dir);

    void sendRequest(QRedisClientRequest& request);
    QRedisClientRequest executeScript(const QString &script,
                                      const QVector<QByteArray> &args = QVector<QByteArray>());

    quint8 dbIndex() const;
    void setDbIndex(const quint8& dbIndex);

    bool isReady() const;
    QHostAddress serverAddress() const;

private:
    // iVars
    QTcpSocket *m_socket = new QTcpSocket(this);
    QByteArray m_buffer;
    QVector<QRedisClientReply> m_replies;
    quint8 m_dbIndex = 0;
    bool m_isReady = false;
    QString m_name = QStringLiteral("QRedisClient_1");
    QVector<QRedisClientScript> m_scripts;

    // Methods
    void scanForTokens();
    void setupConnection();

private slots:
    void handleSocketConnected();
    void handleSocketReadyRead();
    void handleSocketDidDisconnect();

signals:
    void ready();
    void replyFinished(const QRedisClientReply reply);

private slots:
    void handleDidParseToken(const QRedisProtocolToken &token);
    void handleInternalReply(QRedisClientReply& reply);




};

#endif // QREDISCLIENT_H
