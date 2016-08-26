#ifndef QREDISCLIENTERROR_H
#define QREDISCLIENTERROR_H
//
#include <QString>

class QRedisClientError
{
    friend class QRedisProtocolToken;

public:
    enum Code
    {
        ERR_NONE,
        ERR_WRONGTYPE,
        ERR_UNKNOWN
    };

    static QRedisClientError noError();

    QRedisClientError();

    QString string() const;
    QRedisClientError::Code code() const;

private:
    QString m_string;
    QRedisClientError::Code m_code = QRedisClientError::Code::ERR_UNKNOWN;

    void setErrorCode(const QByteArray &errorCodeString);


};

#endif // QREDISCLIENTERROR_H
