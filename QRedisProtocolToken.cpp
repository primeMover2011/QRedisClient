#include "QRedisProtocolToken.h"
//
#include <QDebug>
//
#include "QRedisClientError.h"

QRedisProtocolToken::QRedisProtocolToken()
{

}

QRedisProtocolToken::QRedisProtocolToken(const QByteArray &tokenData)
{
    Q_ASSERT(!tokenData.isEmpty());
    this->m_type = this->getType(tokenData[0]);
    this->parse(tokenData);
}

void QRedisProtocolToken::parse(const QByteArray &tokenData)
{
    switch (this->m_type)
    {
        case QRedisTokenType::TKN_TYPE_STRING:
            this->extractString(tokenData);
            return;
        case QRedisTokenType::TKN_TYPE_INT:
            this->extractInt(tokenData);
            return;
        case QRedisTokenType::TKN_TYPE_BYTES:
            this->extractBytes(tokenData);
            return;
        case QRedisTokenType::TKN_TYPE_ARRAY:
            this->extractArray(tokenData);
            return;
        case QRedisTokenType::TKN_TYPE_ERROR:
            this->extractError(tokenData);
            return;
        default:
            break;
    }
}

void QRedisProtocolToken::extractString(const QByteArray &tokenData)
{
    // Example:
    // "+OK\r\n"
    qint32 idxLf = tokenData.indexOf(QChar::LineFeed);

    if (idxLf == -1) { return; }

    if (this->m_bytes == QByteArrayLiteral("$0\r\n\r\n"))
    {
        this->m_isNull = true;
    }

    this->m_bytes = tokenData.mid(1, idxLf - 2);
    this->m_byteLength = idxLf + 1;

    if (tokenData.length() >= this->m_byteLength) { this->m_isValid = true; }
}

void QRedisProtocolToken::extractInt(const QByteArray &tokenData)
{
    // Example:
    // ":1000\r\n"
    qint32 idxLf = tokenData.indexOf(QChar::LineFeed);
    if (idxLf == -1) { return; }

    this->m_bytes = tokenData.mid(1, idxLf - 2);
    this->m_byteLength = idxLf + 1;

    if (tokenData.length() >= this->m_byteLength) { this->m_isValid = true; }
}

void QRedisProtocolToken::extractBytes(const QByteArray &tokenData)
{
    // Example:
    // "$6\r\nfoobar\r\n"

    qint32 idxCr = tokenData.indexOf(QChar::LineFeed);
    if (idxCr == -1) { return; }

    bool canConvert = false;
    qint32 byteLength = tokenData.mid(1, idxCr - 2).toLongLong(&canConvert);
    Q_ASSERT(canConvert);

    if (byteLength == -1 && tokenData.left(5) == QByteArrayLiteral("$-1\r\n"))
    {
        this->m_isNull  = true;
        this->m_byteLength  = 5;
        if (tokenData.length() >= this->m_byteLength) { this->m_isValid = true; }
        return;
    }

    this->m_bytes = tokenData.mid(idxCr + 1, byteLength);
    this->m_byteLength = 1 +               // $
                         2 +               // \r\n
                         (idxCr - 2) +     // Number of bytes of the length number
                         byteLength +      // Number of bytes
                         2;                // \r\n

    if (tokenData.length() >= this->m_byteLength) { this->m_isValid = true; }
}

void QRedisProtocolToken::extractArray(const QByteArray &tokenData)
{
    qint32 ifxLf = tokenData.indexOf(QChar::LineFeed);

    bool canConvert = false;
    qint64 elementCount = tokenData.mid(1, ifxLf - 2).toLongLong(&canConvert);
    Q_ASSERT(canConvert);

    if (elementCount == 0 && tokenData.left(4) == QByteArrayLiteral("*0\r\n"))
    {
        this->m_isNull  = true;
        this->m_byteLength  = 4;
        if (tokenData.length() >= this->m_byteLength) { this->m_isValid = true; }
        return;
    }

    qint32 readPos = 1 +            // *
                     (ifxLf - 2) +  // Length of element length;
                     2;             // \r\n

    for (int i = 0; i < elementCount; i++)
    {
        QRedisProtocolToken cToken = QRedisProtocolToken(tokenData.mid(readPos));
        Q_ASSERT(cToken.isValid());

        qint32 tknLength = cToken.byteLength();
        readPos += tknLength;
    }

    this->m_byteLength  = readPos;
    this->m_bytes       = tokenData.left(readPos);

    if (tokenData.length() >= this->m_byteLength) { this->m_isValid = true; }
}

void QRedisProtocolToken::extractError(const QByteArray &tokenData)
{
    // Example:
    // "-Error message\r\n"

    qint32 idxSpace = tokenData.indexOf(QChar::Space);
    qint32 idxCr    = tokenData.indexOf(QChar::CarriageReturn);

    this->m_bytes.append(tokenData.mid(1, idxSpace - 1))
            .append('^')
            .append(tokenData.mid(idxSpace +1, idxCr - idxSpace  -1));

    this->m_byteLength = idxCr + 2;

    if (tokenData.length() >= this->m_byteLength) { this->m_isValid = true; }
}

QString QRedisProtocolToken::toString() const
{
    return QString(this->m_bytes);
}

QByteArray QRedisProtocolToken::toBytes() const
{
    return this->m_bytes;
}

qint64 QRedisProtocolToken::toInt64() const
{
    Q_ASSERT(!this->m_bytes.isEmpty());

    bool canConvert = false;
    qint64 num = this->m_bytes.toLongLong(&canConvert);
    Q_ASSERT(canConvert);

    return num;
}

bool QRedisProtocolToken::toBool() const
{
    return static_cast<bool>(this->toInt64());
}

QRedisTokenList QRedisProtocolToken::toTokenList() const
{
    Q_ASSERT(this->m_type == QRedisTokenType::TKN_TYPE_ARRAY);
    Q_ASSERT(!this->m_bytes.isEmpty());

    qint32 idxCr = m_bytes.indexOf(QChar::LineFeed);

    bool canConvert = false;
    qint64 elementCount = this->m_bytes.mid(1, idxCr - 2).toLongLong(&canConvert);
    Q_ASSERT(canConvert);

    qint32 readPos = 1 +            // *
                     (idxCr - 2) +  // Length of element length;
                     2;

    QRedisTokenList tokens;

    for (int i = 0; i < elementCount; i++)
    {
        QRedisProtocolToken cToken = QRedisProtocolToken(this->m_bytes.mid(readPos));
        qint32 tknLength = cToken.byteLength();
        readPos += tknLength;
        tokens.append(cToken);
    }

    return tokens;
}

QRedisClientError QRedisProtocolToken::toError() const
{
    QRedisClientError error;
    qint32 idxSep = this->m_bytes.indexOf('^');
    error.m_string = this->m_bytes.mid(idxSep + 1);
    error.setErrorCode(this->m_bytes.left(idxSep));
    return error;
}

QRedisList QRedisProtocolToken::toList() const
{
    Q_ASSERT(this->m_type == QRedisTokenType::TKN_TYPE_ARRAY);

    QRedisTokenList tokenList = this->toTokenList();
    QRedisList list;

    for (const QRedisProtocolToken &cToken : tokenList)
    {
        list.append(cToken.toString());
    }

    return list;
}

QRedisSortedSet QRedisProtocolToken::toSortedSet() const
{
    Q_ASSERT(this->m_type == QRedisTokenType::TKN_TYPE_ARRAY);
    QRedisTokenList tokenList = this->toTokenList();

    qint32 tokenListLength = tokenList.length();

    // We must have an even number of tokens in the list
    // else we can't make a sorted set (QMap) out of it :)
    Q_ASSERT(tokenListLength % 2 == 0);

    QRedisSortedSet sSet;

    QRedisTokenList::const_iterator itr;
    for (itr = tokenList.begin(); itr != tokenList.end(); itr = itr + 2)
    {
        sSet.insert(itr->toInt64(), (itr + 1)->toString());
    }

    return sSet;
}

QRedisSet QRedisProtocolToken::toSet() const
{
    Q_ASSERT(this->m_type == QRedisTokenType::TKN_TYPE_ARRAY);
    QRedisTokenList tokenList = this->toTokenList();

    QRedisSet set;

    for (const QRedisProtocolToken &cToken : tokenList)
    {
        set.insert(cToken.toString());
    }

    return set;
}

QRedisHash QRedisProtocolToken::toHash() const
{
    Q_ASSERT(this->m_type == QRedisTokenType::TKN_TYPE_ARRAY);
    QRedisTokenList tokenList = this->toTokenList();

    qint32 tokenListLength = tokenList.length();

    // We must have an even number of tokens in the list
    // else we can't make a hash out of it :)
    Q_ASSERT(tokenListLength % 2 == 0);

    QRedisHash hash;

    QRedisTokenList::const_iterator itr;
    for (itr = tokenList.begin(); itr != tokenList.end(); itr = itr + 2)
    {
        hash.insert(itr->toString(), (itr + 1)->toString());
    }

    return hash;
}

bool QRedisProtocolToken::isOk() const
{
    return (this->m_bytes == QStringLiteral("OK"));
}

// Methods
QRedisTokenType QRedisProtocolToken::getType(char firstByte)
{
    switch (firstByte)
    {
        case '+':
            return QRedisTokenType::TKN_TYPE_STRING;
        case '-':
            return QRedisTokenType::TKN_TYPE_ERROR;
        case ':':
            return QRedisTokenType::TKN_TYPE_INT;
        case '$':
            return QRedisTokenType::TKN_TYPE_BYTES;
        case '*':
            return QRedisTokenType::TKN_TYPE_ARRAY;
        default:
            Q_ASSERT("Shouldn't have gotten here!");
            return QRedisTokenType::TKN_TYPE_UNKNOWN;
    }
}

// Getters
qint32 QRedisProtocolToken::byteLength() const
{
    return m_byteLength;
}

QRedisTokenType QRedisProtocolToken::type() const
{
    return this->m_type;
}

bool QRedisProtocolToken::isNull() const
{
    return m_isNull;
}

bool QRedisProtocolToken::isValid() const
{
    return m_isValid;
}
