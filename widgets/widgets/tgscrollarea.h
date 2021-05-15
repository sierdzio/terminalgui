#pragma once

#include <widgets/tgwidget.h>

#include <QPointer>

namespace Tg {
class ScrollBar;

class ScrollArea : public Widget
{
    Q_OBJECT

    Q_PROPERTY(QPoint contentsPosition READ contentsPosition WRITE setContentsPosition NOTIFY contentsPositionChanged)

    friend class ListView;

public:
    enum class ScrollBarPolicy {
        AlwaysShow,
        ShowWhenNeeded,
        NeverShow
    };
    Q_ENUM(ScrollBarPolicy)

    ScrollArea(Widget *parent);
    ScrollArea(Screen *screen);

    QPoint contentsPosition() const;

    ScrollBarPolicy verticalScrollBarPolicy() const;
    void setVerticalScrollBarPolicy(const ScrollBarPolicy newVerticalScrollBarPolicy);

    ScrollBarPolicy horizontalScrollBarPolicy() const;
    void setHorizontalScrollBarPolicy(const ScrollBarPolicy newHorizontalScrollBarPolicy);

public slots:
    void setContentsPosition(const QPoint &contentsPosition);

signals:
    void contentsPositionChanged(const QPoint &contentsPosition) const;
    void verticalScrollBarPolicyChanged(const ScrollBarPolicy newPolicy) const;
    void horizontalScrollBarPolicyChanged(const ScrollBarPolicy newPolicy) const;

protected:
    void init() override;
    bool consumeKeyboardBuffer(const QString &keyboardBuffer) override;
    QString drawPixel(const QPoint &pixel) const override;
    virtual QString drawAreaContents(const QPoint &pixel) const;

    QPoint childPixel(const QPoint &pixel) const;

    int childrenWidth() const;
    int childrenHeight() const;
    QRect scrollableArea() const;

    void updateScrollBarStates();
    void updateScrollBarPositions();

    int _childrenWidth = 0;
    int _childrenHeight = 0;

protected slots:
    virtual void updateChildrenDimensions();
    void connectChild(Widget *child);

private:
    QPointer<ScrollBar> _verticalScrollBar;
    ScrollBarPolicy _verticalScrollBarPolicy = ScrollBarPolicy::ShowWhenNeeded;
    QPointer<ScrollBar> _horizontalScrollBar;
    ScrollBarPolicy _horizontalScrollBarPolicy = ScrollBarPolicy::ShowWhenNeeded;

    QPoint _contentsPosition;
};
}
