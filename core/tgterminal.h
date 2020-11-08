#pragma once

#include <QPoint>
#include <QSize>
#include <QString>
#include <QObject>

namespace Tg {
class Terminal : public QObject
{
    Q_OBJECT

    Q_PROPERTY(QSize size READ size NOTIFY sizeChanged)

public:
    Terminal(QObject *parent = nullptr);
    static Terminal *globalTerminal();

    QSize updateSize();
    QSize size() const;
    void setSize(const QSize &newSize);
    static QPoint currentPosition();

    /*!
     * Returns number of characters available in keyboard buffer.
     */
    static int keyboardBufferSize();
    static int getChar();

signals:
    void sizeChanged(const QSize &size) const;

private:
    void registerSignalHandler();

    static Terminal *_globalTerminal;
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

