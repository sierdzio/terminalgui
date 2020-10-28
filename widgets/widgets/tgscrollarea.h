#pragma once

#include <widgets/tgwidget.h>

#include <QPointer>

namespace Tg {
class ScrollBar;

class ScrollArea : public Widget
{
    Q_OBJECT

    Q_PROPERTY(QPoint contentsPosition READ contentsPosition WRITE setContentsPosition NOTIFY contentsPositionChanged)

public:
    enum class ScrollBarPolicy {
        AlwaysShow,
        ShowWhenNeeded,
        NeverShow
    };
    Q_ENUM(ScrollBarPolicy)

    ScrollArea(Widget *parent);
    ScrollArea(Screen *screen);

    QString drawPixel(const QPoint &pixel) const override;

    QPoint contentsPosition() const;

public slots:
    void setContentsPosition(const QPoint &contentsPosition);

signals:
    void contentsPositionChanged(const QPoint &contentsPosition) const;

protected:
    void init() override;
    void consumeKeyboardBuffer(const QString &keyboardBuffer) override;

    QPoint childPixel(const QPoint &pixel) const;

    int childrenWidth() const;
    int childrenHeight() const;

    void updateScrollBarStates();

protected slots:
    void updateChildrenDimensions();
    void connectChild(Widget *child);

private:
    QPointer<ScrollBar> _verticalScrollBar;
    ScrollBarPolicy _verticalScrollBarPolicy = ScrollBarPolicy::ShowWhenNeeded;
    QPointer<ScrollBar> _horizontalScrollBar;
    ScrollBarPolicy _horizontalScrollBarPolicy = ScrollBarPolicy::ShowWhenNeeded;

    QPoint _contentsPosition;
    int _childrenWidth = 0;
    int _childrenHeight = 0;
};
}
