#pragma once

#include <QObject>
#include <QPointer>
#include <QList>
#include <QSize>
#include <QRect>
#include <QTimer>

#include "utils/tghelpers.h"
#include "styles/tgstyle.h"

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
    void onNeedsRedraw(const Tg::RedrawType type, const Widget *widget);
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
    QList<QRect> _redrawRegions;
    QSize _size;

    QList<WidgetPointer> _widgets;
    WidgetPointer _activeFocusWidget;
    StylePointer _style;
};
}
