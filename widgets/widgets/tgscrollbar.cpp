#include "tgscrollbar.h"
#include "styles/tgstyle.h"

#include <math.h>

Tg::ScrollBar::ScrollBar(Tg::Widget *parent) : Tg::Widget(parent)
{
    ScrollBar::init();
}

Tg::ScrollBar::ScrollBar(Tg::Screen *screen) : Tg::Widget(screen)
{
    ScrollBar::init();
}

QString Tg::ScrollBar::drawPixel(const QPoint &pixel) const
{
    if (isBorder(pixel)) {
        return drawBorderPixel(pixel);
    }

    int pixelIndex = 0;

    if (orientation() == Qt::Orientation::Horizontal) {
        pixelIndex = pixel.x();
    } else {
        pixelIndex = pixel.y();
    }

    return linearPixel(pixelIndex, length());
}

Qt::Orientation Tg::ScrollBar::orientation() const
{
    return _orientation;
}

int Tg::ScrollBar::length() const
{
    if (orientation() == Qt::Orientation::Horizontal) {
        return size().width();
    } else {
        return size().height();
    }
}

/*!
 * How much to add or remove from value (sliderPosition()) to move the slider
 * by a single pixel (character).
 *
 * \note This method calculates the step each time it is called. If used often,
 * it is better to cache it.
 */
int Tg::ScrollBar::step() const
{
    return int(maximum() / length());
}

int Tg::ScrollBar::minimum() const
{
    return _minimum;
}

int Tg::ScrollBar::maximum() const
{
    return _maximum;
}

int Tg::ScrollBar::sliderPosition() const
{
    return _sliderPosition;
}

QString Tg::ScrollBar::sliderCharacter() const
{
    if (_sliderCharacter.isNull()) {
        return style()->sliderCharacter;
    } else {
        return _sliderCharacter;
    }
}

Tg::Color Tg::ScrollBar::sliderColor() const
{
    if (_sliderColor.isEmpty()) {
        return style()->sliderColor;
    } else {
        return _sliderColor;
    }
}

Tg::Color Tg::ScrollBar::sliderBackgroundColor() const
{
    if (_sliderBackgroundColor.isEmpty()) {
        return style()->sliderBackgroundColor;
    } else {
        return _sliderBackgroundColor;
    }
}

Tg::Color Tg::ScrollBar::sliderActiveBackgroundColor() const
{
    if (_sliderActiveBackgroundColor.isEmpty()) {
        return style()->sliderActiveBackgroundColor;
    } else {
        return _sliderActiveBackgroundColor;
    }
}

Tg::Color Tg::ScrollBar::sliderInactiveBackgroundColor() const
{
    if (_sliderInactiveBackgroundColor.isEmpty()) {
        return style()->sliderInactiveBackgroundColor;
    } else {
        return _sliderInactiveBackgroundColor;
    }
}

Tg::Color Tg::ScrollBar::sliderActiveColor() const
{
    if (_sliderActiveColor.isEmpty()) {
        return style()->sliderActiveColor;
    } else {
        return _sliderActiveColor;
    }
}

Tg::Color Tg::ScrollBar::sliderInactiveColor() const
{
    if (_sliderInactiveColor.isEmpty()) {
        return style()->sliderInactiveColor;
    } else {
        return _sliderInactiveColor;
    }
}

QString Tg::ScrollBar::backwardArrowUpCharacter() const
{
    if (_backwardArrowUpCharacter.isNull()) {
        return style()->backwardArrowUpCharacter;
    } else {
        return _backwardArrowUpCharacter;
    }
}

QString Tg::ScrollBar::backwardArrowLeftCharacter() const
{
    if (_backwardArrowLeftCharacter.isNull()) {
        return style()->backwardArrowLeftCharacter;
    } else {
        return _backwardArrowLeftCharacter;
    }
}

Tg::Color Tg::ScrollBar::backwardArrowColor() const
{
    if (_backwardArrowColor.isEmpty()) {
        return style()->backwardArrowColor;
    } else {
        return _backwardArrowColor;
    }
}

Tg::Color Tg::ScrollBar::backwardArrowActiveColor() const
{
    if (_backwardArrowActiveColor.isEmpty()) {
        return style()->backwardArrowActiveColor;
    } else {
        return _backwardArrowActiveColor;
    }
}

Tg::Color Tg::ScrollBar::backwardArrowInactiveColor() const
{
    if (_backwardArrowInactiveColor.isEmpty()) {
        return style()->backwardArrowInactiveColor;
    } else {
        return _backwardArrowInactiveColor;
    }
}

Tg::Color Tg::ScrollBar::backwardArrowBackgroundColor() const
{
    if (_backwardArrowBackgroundColor.isEmpty()) {
        return style()->backwardArrowBackgroundColor;
    } else {
        return _backwardArrowBackgroundColor;
    }
}

Tg::Color Tg::ScrollBar::backwardArrowActiveBackgroundColor() const
{
    if (_backwardArrowActiveBackgroundColor.isEmpty()) {
        return style()->backwardArrowActiveBackgroundColor;
    } else {
        return _backwardArrowActiveBackgroundColor;
    }
}

Tg::Color Tg::ScrollBar::backwardArrowInactiveBackgroundColor() const
{
    if (_backwardArrowInactiveBackgroundColor.isEmpty()) {
        return style()->backwardArrowInactiveBackgroundColor;
    } else {
        return _backwardArrowInactiveBackgroundColor;
    }
}

QString Tg::ScrollBar::forwardArrowDownCharacter() const
{
    if (_forwardArrowDownCharacter.isNull()) {
        return style()->forwardArrowDownCharacter;
    } else {
        return _forwardArrowDownCharacter;
    }
}

QString Tg::ScrollBar::forwardArrowRightCharacter() const
{
    if (_forwardArrowRightCharacter.isNull()) {
        return style()->forwardArrowRightCharacter;
    } else {
        return _forwardArrowRightCharacter;
    }
}

Tg::Color Tg::ScrollBar::forwardArrowColor() const
{
    if (_forwardArrowColor.isEmpty()) {
        return style()->forwardArrowColor;
    } else {
        return _forwardArrowColor;
    }
}

Tg::Color Tg::ScrollBar::forwardArrowActiveColor() const
{
    if (_forwardArrowActiveColor.isEmpty()) {
        return style()->forwardArrowActiveColor;
    } else {
        return _forwardArrowActiveColor;
    }
}

Tg::Color Tg::ScrollBar::forwardArrowInactiveColor() const
{
    if (_forwardArrowInactiveColor.isEmpty()) {
        return style()->forwardArrowInactiveColor;
    } else {
        return _forwardArrowInactiveColor;
    }
}

Tg::Color Tg::ScrollBar::forwardArrowBackgroundColor() const
{
    if (_forwardArrowBackgroundColor.isEmpty()) {
        return style()->forwardArrowBackgroundColor;
    } else {
        return _forwardArrowBackgroundColor;
    }
}

Tg::Color Tg::ScrollBar::forwardArrowActiveBackgroundColor() const
{
    if (_forwardArrowActiveBackgroundColor.isEmpty()) {
        return style()->forwardArrowActiveBackgroundColor;
    } else {
        return _forwardArrowActiveBackgroundColor;
    }
}

Tg::Color Tg::ScrollBar::forwardArrowInactiveBackgroundColor() const
{
    if (_forwardArrowInactiveBackgroundColor.isEmpty()) {
        return style()->forwardArrowInactiveBackgroundColor;
    } else {
        return _forwardArrowInactiveBackgroundColor;
    }
}

void Tg::ScrollBar::setOrientation(const Qt::Orientation orientation)
{
    if (_orientation == orientation)
        return;

    _orientation = orientation;
    emit orientationChanged(_orientation);
}

void Tg::ScrollBar::setMinimum(const int minimum)
{
    if (_minimum == minimum)
        return;

    _minimum = minimum;
    emit minimumChanged(_minimum);
}

void Tg::ScrollBar::setMaximum(const int maximum)
{
    if (_maximum == maximum)
        return;

    _maximum = maximum;
    emit maximumChanged(_maximum);
}

void Tg::ScrollBar::setValue(const int value)
{
    setSliderPosition(value);
}

void Tg::ScrollBar::setSliderPosition(const int sliderPosition)
{
    if (_sliderPosition == sliderPosition)
        return;

    _sliderPosition = sliderPosition;
    emit sliderPositionChanged(_sliderPosition);
}

void Tg::ScrollBar::setSliderCharacter(const QString &sliderCharacter)
{
    if (_sliderCharacter == sliderCharacter)
        return;

    _sliderCharacter = sliderCharacter;
    emit sliderCharacterChanged(_sliderCharacter);
}

void Tg::ScrollBar::setSliderColor(const Tg::Color &sliderColor)
{
    if (_sliderColor == sliderColor)
        return;

    _sliderColor = sliderColor;
    emit sliderColorChanged(_sliderColor);
}

void Tg::ScrollBar::setSliderBackgroundColor(const Tg::Color &sliderBackgroundColor)
{
    if (_sliderBackgroundColor == sliderBackgroundColor)
        return;

    _sliderBackgroundColor = sliderBackgroundColor;
    emit sliderBackgroundColorChanged(_sliderBackgroundColor);
}

void Tg::ScrollBar::setSliderActiveBackgroundColor(const Tg::Color &sliderActiveBackgroundColor)
{
    if (_sliderActiveBackgroundColor == sliderActiveBackgroundColor)
        return;

    _sliderActiveBackgroundColor = sliderActiveBackgroundColor;
    emit sliderActiveBackgroundColorChanged(_sliderActiveBackgroundColor);
}

void Tg::ScrollBar::setSliderInactiveBackgroundColor(const Tg::Color &sliderInactiveBackgroundColor)
{
    if (_sliderInactiveBackgroundColor == sliderInactiveBackgroundColor)
        return;

    _sliderInactiveBackgroundColor = sliderInactiveBackgroundColor;
    emit sliderInactiveBackgroundColorChanged(_sliderInactiveBackgroundColor);
}

void Tg::ScrollBar::setSliderActiveColor(const Tg::Color &sliderActiveColor)
{
    if (_sliderActiveColor == sliderActiveColor)
        return;

    _sliderActiveColor = sliderActiveColor;
    emit sliderActiveColorChanged(_sliderActiveColor);
}

void Tg::ScrollBar::setSliderInactiveColor(const Tg::Color &sliderInactiveColor)
{
    if (_sliderInactiveColor == sliderInactiveColor)
        return;

    _sliderInactiveColor = sliderInactiveColor;
    emit sliderInactiveColorChanged(_sliderInactiveColor);
}

void Tg::ScrollBar::setBackwardArrowUpCharacter(const QString &backwardArrowUpCharacter)
{
    if (_backwardArrowUpCharacter == backwardArrowUpCharacter)
        return;

    _backwardArrowUpCharacter = backwardArrowUpCharacter;
    emit backwardArrowUpCharacterChanged(_backwardArrowUpCharacter);
}

void Tg::ScrollBar::setBackwardArrowLeftCharacter(const QString &backwardArrowLeftCharacter)
{
    if (_backwardArrowLeftCharacter == backwardArrowLeftCharacter)
        return;

    _backwardArrowLeftCharacter = backwardArrowLeftCharacter;
    emit backwardArrowLeftCharacterChanged(_backwardArrowLeftCharacter);
}

void Tg::ScrollBar::setBackwardArrowColor(const Tg::Color &backwardArrowColor)
{
    if (_backwardArrowColor == backwardArrowColor)
        return;

    _backwardArrowColor = backwardArrowColor;
    emit backwardArrowColorChanged(_backwardArrowColor);
}

void Tg::ScrollBar::setBackwardArrowActiveColor(const Tg::Color &backwardArrowActiveColor)
{
    if (_backwardArrowActiveColor == backwardArrowActiveColor)
        return;

    _backwardArrowActiveColor = backwardArrowActiveColor;
    emit backwardArrowActiveColorChanged(_backwardArrowActiveColor);
}

void Tg::ScrollBar::setBackwardArrowInactiveColor(const Tg::Color &backwardArrowInactiveColor)
{
    if (_backwardArrowInactiveColor == backwardArrowInactiveColor)
        return;

    _backwardArrowInactiveColor = backwardArrowInactiveColor;
    emit backwardArrowInactiveColorChanged(_backwardArrowInactiveColor);
}

void Tg::ScrollBar::setBackwardArrowBackgroundColor(const Tg::Color &backwardArrowBackgroundColor)
{
    if (_backwardArrowBackgroundColor == backwardArrowBackgroundColor)
        return;

    _backwardArrowBackgroundColor = backwardArrowBackgroundColor;
    emit backwardArrowColorBackgroundChanged(_backwardArrowBackgroundColor);
}

void Tg::ScrollBar::setBackwardArrowActiveBackgroundColor(const Tg::Color &backwardArrowActiveBackgroundColor)
{
    if (_backwardArrowActiveBackgroundColor == backwardArrowActiveBackgroundColor)
        return;

    _backwardArrowActiveBackgroundColor = backwardArrowActiveBackgroundColor;
    emit backwardArrowActiveColorBackgroundChanged(_backwardArrowActiveBackgroundColor);
}

void Tg::ScrollBar::setBackwardArrowInactiveBackgroundColor(const Tg::Color &backwardArrowInactiveBackgroundColor)
{
    if (_backwardArrowInactiveBackgroundColor == backwardArrowInactiveBackgroundColor)
        return;

    _backwardArrowInactiveBackgroundColor = backwardArrowInactiveBackgroundColor;
    emit backwardArrowInactiveColorBackgroundChanged(_backwardArrowInactiveBackgroundColor);
}

void Tg::ScrollBar::setForwardArrowDownCharacter(const QString &forwardArrowDownCharacter)
{
    if (_forwardArrowDownCharacter == forwardArrowDownCharacter)
        return;

    _forwardArrowDownCharacter = forwardArrowDownCharacter;
    emit forwardArrowDownCharacterChanged(_forwardArrowDownCharacter);
}

void Tg::ScrollBar::setForwardArrowRightCharacter(const QString &forwardArrowRightCharacter)
{
    if (_forwardArrowRightCharacter == forwardArrowRightCharacter)
        return;

    _forwardArrowRightCharacter = forwardArrowRightCharacter;
    emit forwardArrowRightCharacterChanged(_forwardArrowRightCharacter);
}

void Tg::ScrollBar::setForwardArrowColor(const Tg::Color &forwardArrowColor)
{
    if (_forwardArrowColor == forwardArrowColor)
        return;

    _forwardArrowColor = forwardArrowColor;
    emit forwardArrowColorChanged(_forwardArrowColor);
}

void Tg::ScrollBar::setForwardArrowActiveColor(const Tg::Color &forwardArrowActiveColor)
{
    if (_forwardArrowActiveColor == forwardArrowActiveColor)
        return;

    _forwardArrowActiveColor = forwardArrowActiveColor;
    emit forwardArrowActiveColorChanged(_forwardArrowActiveColor);
}

void Tg::ScrollBar::setForwardArrowInactiveColor(const Tg::Color &forwardArrowInactiveColor)
{
    if (_forwardArrowInactiveColor == forwardArrowInactiveColor)
        return;

    _forwardArrowInactiveColor = forwardArrowInactiveColor;
    emit forwardArrowInactiveColorChanged(_forwardArrowInactiveColor);
}

void Tg::ScrollBar::setForwardArrowBackgroundColor(const Tg::Color &forwardArrowBackgroundColor)
{
    if (_forwardArrowBackgroundColor == forwardArrowBackgroundColor)
        return;

    _forwardArrowBackgroundColor = forwardArrowBackgroundColor;
    emit forwardArrowColorBackgroundChanged(_forwardArrowBackgroundColor);
}

void Tg::ScrollBar::setForwardArrowActiveBackgroundColor(const Tg::Color &forwardArrowActiveBackgroundColor)
{
    if (_forwardArrowActiveBackgroundColor == forwardArrowActiveBackgroundColor)
        return;

    _forwardArrowActiveBackgroundColor = forwardArrowActiveBackgroundColor;
    emit forwardArrowActiveColorBackgroundChanged(_forwardArrowActiveBackgroundColor);
}

void Tg::ScrollBar::setForwardArrowInactiveBackgroundColor(const Tg::Color &forwardArrowInactiveBackgroundColor)
{
    if (_forwardArrowInactiveBackgroundColor == forwardArrowInactiveBackgroundColor)
        return;

    _forwardArrowInactiveBackgroundColor = forwardArrowInactiveBackgroundColor;
    emit forwardArrowInactiveColorBackgroundChanged(_forwardArrowInactiveBackgroundColor);
}

void Tg::ScrollBar::enforceProperSize()
{
    // nothing, for now
}

void Tg::ScrollBar::init()
{
    setAcceptsFocus(true);

    Widget::init();

    // TODO: move these connects into setupPressTimer() somehow!
    CHECK(connect(this, &ScrollBar::sliderPositionChanged,
                  &_sliderPressTimer, qOverload<>(&QTimer::start)));
    CHECK(connect(&_sliderPressTimer, &QTimer::timeout,
                  this, &ScrollBar::schedulePartialRedraw));
    setupPressTimer(&_sliderPressTimer);

    // TODO: move these connects into setupPressTimer() somehow!
    CHECK(connect(this, &ScrollBar::backwardArrowClicked,
                  &_backwardArrowPressTimer, qOverload<>(&QTimer::start)));
    CHECK(connect(&_backwardArrowPressTimer, &QTimer::timeout,
                  this, &ScrollBar::schedulePartialRedraw));
    setupPressTimer(&_backwardArrowPressTimer);

    // TODO: move these connects into setupPressTimer() somehow!
    CHECK(connect(this, &ScrollBar::forwardArrowClicked,
                  &_forwardArrowPressTimer, qOverload<>(&QTimer::start)));
    CHECK(connect(&_forwardArrowPressTimer, &QTimer::timeout,
                  this, &ScrollBar::schedulePartialRedraw));
    setupPressTimer(&_forwardArrowPressTimer);

    CHECK(connect(this, &ScrollBar::orientationChanged,
                  this, &ScrollBar::schedulePartialRedraw));
    CHECK(connect(this, &ScrollBar::minimumChanged,
                  this, &ScrollBar::schedulePartialRedraw));
    CHECK(connect(this, &ScrollBar::maximumChanged,
                  this, &ScrollBar::schedulePartialRedraw));
    CHECK(connect(this, &ScrollBar::sliderPositionChanged,
                  this, &ScrollBar::schedulePartialRedraw));
    CHECK(connect(this, &ScrollBar::sliderCharacterChanged,
                  this, &ScrollBar::schedulePartialRedraw));
    CHECK(connect(this, &ScrollBar::sliderColorChanged,
                  this, &ScrollBar::schedulePartialRedraw));
    CHECK(connect(this, &ScrollBar::sliderBackgroundColorChanged,
                  this, &ScrollBar::schedulePartialRedraw));
    CHECK(connect(this, &ScrollBar::sliderActiveColorChanged,
                  this, &ScrollBar::schedulePartialRedraw));
    CHECK(connect(this, &ScrollBar::backwardArrowUpCharacterChanged,
                  this, &ScrollBar::schedulePartialRedraw));
    CHECK(connect(this, &ScrollBar::backwardArrowLeftCharacterChanged,
                  this, &ScrollBar::schedulePartialRedraw));
    CHECK(connect(this, &ScrollBar::backwardArrowColorChanged,
                  this, &ScrollBar::schedulePartialRedraw));
    CHECK(connect(this, &ScrollBar::backwardArrowActiveColorChanged,
                  this, &ScrollBar::schedulePartialRedraw));
    CHECK(connect(this, &ScrollBar::backwardArrowInactiveColorChanged,
                  this, &ScrollBar::schedulePartialRedraw));
    CHECK(connect(this, &ScrollBar::backwardArrowColorBackgroundChanged,
                  this, &ScrollBar::schedulePartialRedraw));
    CHECK(connect(this, &ScrollBar::backwardArrowActiveColorBackgroundChanged,
                  this, &ScrollBar::schedulePartialRedraw));
    CHECK(connect(this, &ScrollBar::backwardArrowInactiveColorBackgroundChanged,
                  this, &ScrollBar::schedulePartialRedraw));
    CHECK(connect(this, &ScrollBar::forwardArrowDownCharacterChanged,
                  this, &ScrollBar::schedulePartialRedraw));
    CHECK(connect(this, &ScrollBar::forwardArrowRightCharacterChanged,
                  this, &ScrollBar::schedulePartialRedraw));
    CHECK(connect(this, &ScrollBar::forwardArrowColorChanged,
                  this, &ScrollBar::schedulePartialRedraw));
    CHECK(connect(this, &ScrollBar::forwardArrowActiveColorChanged,
                  this, &ScrollBar::schedulePartialRedraw));
    CHECK(connect(this, &ScrollBar::forwardArrowInactiveColorChanged,
                  this, &ScrollBar::schedulePartialRedraw));
    CHECK(connect(this, &ScrollBar::forwardArrowColorBackgroundChanged,
                  this, &ScrollBar::schedulePartialRedraw));
    CHECK(connect(this, &ScrollBar::forwardArrowActiveColorBackgroundChanged,
                  this, &ScrollBar::schedulePartialRedraw));
    CHECK(connect(this, &ScrollBar::forwardArrowInactiveColorBackgroundChanged,
                  this, &ScrollBar::schedulePartialRedraw));

    //setBackgroundColor(Tg::Color::Predefined::Gray);
}

void Tg::ScrollBar::consumeKeyboardBuffer(const QString &keyboardBuffer)
{
     if (keyboardBuffer.contains(Tg::Key::up)
             || keyboardBuffer.contains(Tg::Key::left)) {
         const int position = sliderPosition();
         if (position > 0) {
             setSliderPosition(sliderPosition() - step());
         } else {
             emit sliderPositionChanged(position);
         }
         emit backwardArrowClicked();
     }

     if (keyboardBuffer.contains(Tg::Key::down)
             || keyboardBuffer.contains(Tg::Key::right)) {
         const int position = sliderPosition();

         if (position < (length() - 3)) {
             setSliderPosition(sliderPosition() + step());
         } else {
             emit sliderPositionChanged(position);
         }
         emit forwardArrowClicked();
     }
}

QString Tg::ScrollBar::linearPixel(const int pixel, const int length) const
{
    QString result;
    if (pixel == 0) {
        // Draw first arrow
        // TODO: handle all the color madness ;-) Active, normal, inactive colors
        if (_backwardArrowPressTimer.isActive()) {
            result.append(Tg::Color::code(
                              backwardArrowActiveColor(), backwardArrowActiveBackgroundColor()
                              ));
        } else {
            result.append(Tg::Color::code(
                              backwardArrowColor(), backwardArrowBackgroundColor()
                              ));
        }

        if (orientation() == Qt::Orientation::Horizontal) {
            result.append(backwardArrowLeftCharacter());
        } else {
            result.append(backwardArrowUpCharacter());
        }

        return result;
    } else if (pixel == length - 1) {
        // Draw second arrow
        // TODO: handle all the color madness ;-) Active, normal, inactive colors
        if (_forwardArrowPressTimer.isActive()) {
            result.append(Tg::Color::code(
                              forwardArrowActiveColor(), forwardArrowActiveBackgroundColor()
                              ));
        } else {
            result.append(Tg::Color::code(
                              forwardArrowColor(), forwardArrowBackgroundColor()
                              ));
        }

        if (orientation() == Qt::Orientation::Horizontal) {
            result.append(forwardArrowRightCharacter());
        } else {
            result.append(forwardArrowDownCharacter());
        }

        return result;
    }

    const int adjustedLength = length - 2;
    const qreal percentileOfValue = qreal(sliderPosition()) / qreal(maximum());
    const qreal percentileOfLength = percentileOfValue * adjustedLength;
    int position = -1;

    if (percentileOfValue < .1) {
        position = 0;
    } else if (percentileOfValue > .9) {
        position = adjustedLength;
    } else {
        position = std::ceil(percentileOfLength);
    }

    const bool isSlider = ((pixel - 1) == position);
    if (isSlider) {
        // Draw slider
        if (_sliderPressTimer.isActive()) {
            result.append(Tg::Color::code(
                              sliderActiveColor(), sliderActiveBackgroundColor()
                              ));
        } else {
            result.append(Tg::Color::code(
                              sliderColor(), sliderBackgroundColor()
                              ));
        }

        result.append(sliderCharacter());
    } else {
        result.append(Tg::Color::code(
                          textColor(), backgroundColor()
                          ));

        result.append(backgroundCharacter());
    }

    return result;
}
