#pragma once

#include <QPoint>
#include <QSize>
#include <QString>
#include <QObject>

namespace Tg {
/*!
 * \brief Cross-platform representation of terminal window.
 *
 * Contains some basic APIs used by Widget and its subclasses.
 */
class Terminal : public QObject
{
    Q_OBJECT

    Q_PROPERTY(QSize size READ size NOTIFY sizeChanged)

public:
    Terminal(QObject *parent = nullptr);
    ~Terminal();
    static Terminal *globalTerminal();

    QSize updateSize();
    QSize size() const;
    void setSize(const QSize &newSize);

    /*!
     * Returns current position of keyboard cursor.
     *
     * \note Unused.
     */
    static QPoint cursorPosition();

    /*!
     * Returns number of characters available in keyboard buffer.
     *
     * \sa getChar
     */
    static int keyboardBufferSize();

    /*!
     * Retrieves a single character from the keyboard buffer.
     *
     * \sa keyboardBufferSize
     */
    static int getChar();

signals:
    /*!
     * Emitted when terminal window changes size to \a size.
     */
    void sizeChanged(const QSize &size) const;

private:
    void registerSignalHandler();
    void enableMouseTracking();
    void disableMouseTracking();

    static Terminal *_globalTerminal;
    const QSize _defaultSize = QSize(80, 24);
    bool _isMouseReporting = false;
    QSize _size;
};

/*!
 * \brief Simple RAII class - sets proper echo mode in terminal for the duration
 * of application run.
 *
 * When this object is deleted, it restores previous echo mode.
 */
class RawTerminalLocker {
public:
    /*!
     * Disables echo mode in terminal. All key strokes are intercepted by
     * Tg::Terminal instead.
     */
    RawTerminalLocker();

    /*!
     * Enables echo mode in terminal.
     */
    ~RawTerminalLocker();
};

const int standardInputIndex = 0;
}

