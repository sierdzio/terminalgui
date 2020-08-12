#pragma once

#include <QObject>
#include <QPointer>
#include <QVector>
#include <QSize>

namespace Tg {
class Widget;

class Screen : public QObject
{
    Q_OBJECT

    // TODO: differentiate between Terminal size and size of screen reserved
    // for application
    Q_PROPERTY(QSize size READ size NOTIFY sizeChanged)

    friend class Widget;

public:
    Screen(QObject *parent = nullptr);
    ~Screen();

    void waitForQuit();

    QSize size() const;

    void registerWidget(Widget *widget);
    void deregisterWidget(Widget *widget);

signals:
    void sizeChanged(const QSize &size) const;

private slots:
    // TODO: make it const?
    void onNeedsRedraw();

private:
    QSize _size;
    QVector<QPointer<Widget>> _widgets;
    QPointer<Widget> _activeFocusWidget;
};
}
