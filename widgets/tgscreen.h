#pragma once

#include <QObject>
#include <QPointer>
#include <QVector>
#include <QSize>
#include <QTimer>

#include "tghelpers.h"
#include "tgstyle.h"

namespace Tg {
class Screen : public QObject
{
    Q_OBJECT

    // TODO: differentiate between Terminal size and size of screen reserved
    // for application
    Q_PROPERTY(QSize size READ size NOTIFY sizeChanged)

public:
    Screen(QObject *parent = nullptr);
    ~Screen();

    void waitForQuit();

    QSize size() const;

    void registerWidget(Widget *widget);
    void deregisterWidget(Widget *widget);

    StylePointer style() const;

public slots:
    void onNeedsRedraw();
    void moveFocusToPreviousWidget();
    void moveFocusToNextWidget();

signals:
    void sizeChanged(const QSize &size) const;

private slots:
    void redrawImmediately() const;
    void checkKeyboard();

private:
    void compressRedraws();

    QTimer _keyboardTimer;
    QTimer _redrawTimer;
    QSize _size;

    QVector<WidgetPointer> _widgets;
    WidgetPointer _activeFocusWidget;
    StylePointer _style;
};
}
