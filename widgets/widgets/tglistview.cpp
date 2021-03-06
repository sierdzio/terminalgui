#include "tglistview.h"
#include "tgcheckbox.h"
#include "styles/tgstyle.h"

#include <QRect>

Tg::ListView::ListView(Tg::Widget *parent) : Tg::ScrollArea(parent)
{
    ListView::init();
}

Tg::ListView::ListView(Tg::Screen *screen) : Tg::ScrollArea(screen)
{
    ListView::init();
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

    const QModelIndex index = model()->index(childPx.y(), 0);
    const Color decoration = model()->data(
                index, Qt::ItemDataRole::DecorationRole).value<Color>();
    int offset = 0;
    if (decoration != Color::Predefined::Empty) {
        if (childPx.x() == 0) {
            QString result = Tg::Color::code(textColor(), decoration);
            result.append(Key::space);
            return result;
        }

        offset = 1;
    }

    Tg::Color background = backgroundColor();

    if (childPx.y() == _currentIndex) {
        background = currentIndexColor();
    } else if (alternatingRowColors() && (childPx.y() % 2)) {
        background = alternativeBackgroundColor();
    }

    QString result = Tg::Color::code(textColor(), background);

    const QString line(getLine(index));
    if (childPx.x() >= (line.length() + offset)) {
        result.append(backgroundCharacter());
        return result;
    }

    result.append(line.at(childPx.x() - offset));
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

    CHECK(connect(_model, &QAbstractItemModel::dataChanged,
                  this, &ListView::schedulePartialRedraw));

    setCurrentIndex(0);
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

Tg::Color Tg::ListView::alternativeBackgroundColor() const
{
    if (_alternativeBackgroundColor.isEmpty()) {
        return style()->alternativeBackgroundColor;
    } else {
        return _alternativeBackgroundColor;
    }
}

qsizetype Tg::ListView::currentIndex() const
{
    return _currentIndex;
}

Tg::Color Tg::ListView::currentIndexColor() const
{
    if (_currentIndexColor.isEmpty()) {
        return style()->currentIndexColor;
    } else {
        return _currentIndexColor;
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

void Tg::ListView::setAlternativeBackgroundColor(const Tg::Color &alternativeBackgroundColor)
{
    if (_alternativeBackgroundColor == alternativeBackgroundColor)
        return;

    _alternativeBackgroundColor = alternativeBackgroundColor;
    emit alternativeBackgroundColorChanged(_alternativeBackgroundColor);
}

void Tg::ListView::setCurrentIndex(const qsizetype currentIndex)
{
    if (_currentIndex == currentIndex)
        return;

    _currentIndex = currentIndex;
    emit currentIndexChanged(_currentIndex);
}

void Tg::ListView::setCurrentIndexColor(const Tg::Color &currentIndexColor)
{
    if (_currentIndexColor == currentIndexColor)
        return;

    _currentIndexColor = currentIndexColor;
    emit currentIndexColorChanged(_currentIndexColor);
}

void Tg::ListView::init()
{
    ScrollArea::init();

    CHECK(connect(this, &ListView::wrapRowsChanged,
                  this, &ListView::schedulePartialRedraw));
    CHECK(connect(this, &ListView::modelChanged,
                  this, &ListView::schedulePartialRedraw));
    CHECK(connect(this, &ListView::alternatingRowColorsChanged,
                  this, &ListView::schedulePartialRedraw));
    CHECK(connect(this, &ListView::alternativeBackgroundColorChanged,
                  this, &ListView::schedulePartialRedraw));
    CHECK(connect(this, &ListView::currentIndexChanged,
                  this, &ListView::schedulePartialRedraw));
    CHECK(connect(this, &ListView::currentIndexColorChanged,
                  this, &ListView::schedulePartialRedraw));
}

bool Tg::ListView::consumeKeyboardBuffer(const QString &keyboardBuffer)
{
    if (keyboardBuffer.contains(Tg::Key::right)
            || keyboardBuffer.contains(Tg::Key::left)) {
        return ScrollArea::consumeKeyboardBuffer(keyboardBuffer);
    }

    if (keyboardBuffer.contains(Tg::Key::down)) {
        if ((currentIndex() + 1) < model()->rowCount()) {
            setCurrentIndex(currentIndex() + 1);
        }

        const int currentY = contentsPosition().y();
        const int hiddenLength = std::abs(currentY);
        const int contentsHeight = scrollableArea().height();
        if (currentIndex() >= (hiddenLength + contentsHeight)) {
            QPoint pos = contentsPosition();
            pos.setY(currentY - 1);
            setContentsPosition(pos);
        }

        return true;
    }

    if (keyboardBuffer.contains(Tg::Key::up)) {
        if (currentIndex() > 0) {
            setCurrentIndex(currentIndex() - 1);
        }

        const int currentY = contentsPosition().y();
        if (currentY < 0) {
            const int hiddenLength = std::abs(currentY);
            if (currentIndex() < hiddenLength) {
                QPoint pos = contentsPosition();
                pos.setY(currentY + 1);
                setContentsPosition(pos);
            }
        }

        return true;
    }

    const bool select = keyboardBuffer.contains(Tg::Key::space);
    const bool push = keyboardBuffer.contains(Tg::Key::enter)
            || keyboardBuffer.contains(Tg::Key::ret);

    if (select || push) {
        const QModelIndex index = model()->index(currentIndex(), 0);

        if (select && model()->flags(index).testFlag(Qt::ItemFlag::ItemIsUserCheckable)) {
            const Qt::CheckState state = model()->data(index, Qt::ItemDataRole::CheckStateRole)
                    .value<Qt::CheckState>();
            Qt::CheckState newState;
            if (state == Qt::CheckState::Unchecked) {
                newState = Qt::CheckState::Checked;
            } else {
                newState = Qt::CheckState::Unchecked;
            }
            model()->setData(index, newState, Qt::ItemDataRole::CheckStateRole);
            return true;
        } else {
            emit indexPressed(index);
            return true;
        }
    }

    return false;
}

QString Tg::ListView::getLine(const int row) const
{
    return getLine(model()->index(row, 0));
}

QString Tg::ListView::getLine(const QModelIndex index) const
{
    const Qt::ItemFlags flags = model()->flags(index);

    QString result;

    if (flags.testFlag(Qt::ItemFlag::ItemIsUserCheckable)) {
        const auto state = Qt::CheckState(
                    model()->data(index, Qt::ItemDataRole::CheckStateRole).toInt());
        result.append(CheckBox::checkBoxText(state, style()));
    }

    /*
     * TODO: also handle:
     * - ItemIsSelectable
     */

    result.append(model()->data(index, Qt::ItemDataRole::DisplayRole).toString());
    return result;
}

void Tg::ListView::updateChildrenDimensions()
{
    const int oldWidth = _childrenWidth;
    const int oldHeight = _childrenHeight;
    qsizetype longestRowInView = 0;

    _childrenWidth = 0;
    _childrenHeight = 0;
    setContentsPosition(QPoint(0, 0));

    if (_model.isNull()) {
        return;
    }

    const QRect widgetSize = scrollableArea();

    for (int i = 0; i < widgetSize.height(); ++i) {
        const QModelIndex index(model()->index(i, 0));
        const QString line(getLine(index));
        const Color decoration = model()->data(
                    index, Qt::ItemDataRole::DecorationRole).value<Color>();
        int offset = 0;
        if (decoration != Color::Predefined::Empty) {
            offset = 1;
        }

        longestRowInView = std::max(longestRowInView,
                                    qsizetype(line.length() + offset));
        // TODO: wrap support
    }

    _childrenWidth = longestRowInView;
    _childrenHeight = model()->rowCount();

    if (oldWidth != _childrenWidth || oldHeight != _childrenHeight) {
        updateScrollBarStates();
    }
}
