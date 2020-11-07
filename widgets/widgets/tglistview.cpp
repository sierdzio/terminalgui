#include "tglistview.h"
#include "styles/tgstyle.h"

#include <QRect>
#include <QAbstractItemModel>

Tg::ListView::ListView(Tg::Widget *parent) : Tg::ScrollArea(parent)
{
    init();
}

Tg::ListView::ListView(Tg::Screen *screen) : Tg::ScrollArea(screen)
{
    init();
}

QString Tg::ListView::drawAreaContents(const QPoint &pixel) const
{
    if (model() == nullptr) {
        return {};
    }

    const QPoint childPx = childPixel(pixel);
    const int rowCount = model()->rowCount();

    if (childPx.y() >= rowCount) {
        return {};
    }

    const Terminal::Color background = (alternatingRowColors() && (childPx.y() % 2))?
                alternativeBackgroundColor() : backgroundColor();
    QString result = Terminal::Color::code(textColor(), background);

    const QString line(getLine(childPx.y()));
    if (childPx.x() >= line.length()) {
        result.append(backgroundCharacter());
        return result;
    }

    result.append(line.at(childPx.x()));
    return result;
}

QAbstractItemModel *Tg::ListView::model() const
{
    return _model;
}

void Tg::ListView::setModel(QAbstractItemModel *model)
{
    if (_model == model) {
        return;
    }

    _model = model;
    updateChildrenDimensions();

    emit modelChanged(model);
}

bool Tg::ListView::wrapRows() const
{
    return _wrapRows;
}

bool Tg::ListView::alternatingRowColors() const
{
    return _alternatingRowColors;
}

Terminal::Color Tg::ListView::alternativeBackgroundColor() const
{
    if (_alternativeBackgroundColor.isEmpty()) {
        return style()->alternativeBackgroundColor;
    } else {
        return _alternativeBackgroundColor;
    }
}

void Tg::ListView::setWrapRows(const bool wrapRows)
{
    if (_wrapRows == wrapRows)
        return;

    _wrapRows = wrapRows;
    emit wrapRowsChanged(_wrapRows);
}

void Tg::ListView::setAlternatingRowColors(const bool alternatingRowColors)
{
    if (_alternatingRowColors == alternatingRowColors)
        return;

    _alternatingRowColors = alternatingRowColors;
    emit alternatingRowColorsChanged(_alternatingRowColors);
}

void Tg::ListView::setAlternativeBackgroundColor(const Terminal::Color &alternativeBackgroundColor)
{
    if (_alternativeBackgroundColor == alternativeBackgroundColor)
        return;

    _alternativeBackgroundColor = alternativeBackgroundColor;
    emit alternativeBackgroundColorChanged(_alternativeBackgroundColor);
}

void Tg::ListView::init()
{
    ScrollArea::init();

    CHECK(connect(this, &ListView::wrapRowsChanged,
                  this, &ListView::schedulePartialRedraw));
    CHECK(connect(this, &ListView::modelChanged,
                  this, &ListView::schedulePartialRedraw));
}

void Tg::ListView::consumeKeyboardBuffer(const QString &keyboardBuffer)
{
    ScrollArea::consumeKeyboardBuffer(keyboardBuffer);
}

QString Tg::ListView::getLine(const int y) const
{
    const QModelIndex index = model()->index(y, 0);
    return model()->data(index, Qt::ItemDataRole::DisplayRole).toString();
}

void Tg::ListView::updateChildrenDimensions()
{
    const int oldWidth = _childrenWidth;
    const int oldHeight = _childrenHeight;
    int longestRowInView = 0;

    _childrenWidth = 0;
    _childrenHeight = 0;
    setContentsPosition(QPoint(0, 0));

    if (_model.isNull()) {
        return;
    }

    const QRect widgetSize = scrollableArea();

    for (int i = 0; i < widgetSize.height(); ++i) {
        const QString line(getLine(i));
        longestRowInView = std::max(longestRowInView, line.length());
        // TODO: wrap support
    }

    _childrenWidth = longestRowInView;
    _childrenHeight = model()->rowCount();

    if (oldWidth != _childrenWidth || oldHeight != _childrenHeight) {
        updateScrollBarStates();
    }
}
