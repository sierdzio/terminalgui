#pragma once

#include <QPoint>
#include <QSize>
#include <QString>
#include <QObject>

namespace Tg {
// TODO: singleton
class Terminal : public QObject
{
    Q_OBJECT

public:
    Terminal(QObject *parent = nullptr);

    QSize size() const;
    static QPoint currentPosition();

    /*!
     * Returns number of characters available in keyboard buffer.
     */
    static int keyboardBufferSize();
    static int getChar();

private:
    QSize updateSize();

    const QSize _defaultSize = QSize(80, 24);
    QSize _size;
};

class RawTerminalLocker {
public:
    RawTerminalLocker();
    ~RawTerminalLocker();
};

const int standardInputIndex = 0;
}
