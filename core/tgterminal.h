#pragma once

#include <QPoint>
#include <QSize>
#include <QString>
#include <QObject>

namespace Tg {
/*!
 * \brief Cross-platform representation of terminal window.
 *
 * Contains some basic APIs used by Widget and its subclasses. This class is
 * internal, there should be no need to use it in user code.
 *
 * \todo Further refactor the API to be more Qt-like. We don't need getChar(),
 * for example, the class could hold keyboard buffer locally and notify Screen
 * when needed via a signal.
 */
class Terminal : public QObject
{
    Q_OBJECT

    /*!
     * Size of the terminal window.
     */
    Q_PROPERTY(QSize size READ size NOTIFY sizeChanged)

public:
    /*!
     * Constructs a new Terminal object as a child of \a parent object.
     * Typically it is parented under Screen.
     */
    Terminal(QObject *parent = nullptr);

    /*!
     * Makes terminal go boom!
     */
    ~Terminal();

    /*!
     * Returns Singleton Terminal instance.
     *
     * \note This is a WIP. Terminal will either become a full singleton,
     * or multiple instances will be allowed.
     */
    static Terminal *globalTerminal();

    /*!
     * Reads the underlying terminal window size and returns it.
     */
    QSize terminalWindowSize() const;

    /*!
     * Returns current size of the Terminal.
     */
    QSize size() const;

    /*!
     * Resizes Terminal instance to \a newSize.
     *
     * \note This is not fully implemented or tested.
     */
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
    static const int standardInputIndex = 0;
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
}

