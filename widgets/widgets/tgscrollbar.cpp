#include "tgscrollbar.h"

Tg::ScrollBar::ScrollBar(Tg::Widget *parent) : Tg::Widget(parent)
{
    init();
}

Tg::ScrollBar::ScrollBar(Tg::Screen *screen) : Tg::Widget(screen)
{
    init();
}

QString Tg::ScrollBar::drawPixel(const QPoint &pixel) const
{
    if (isBorder(pixel)) {
        return drawBorderPixel(pixel);
    }

    int pixelIndex = 0;
    int length = 0;

    if (orientation() == Qt::Orientation::Horizontal) {
        pixelIndex = pixel.x();
        length = size().width();
    } else {
        pixelIndex = pixel.y();
        length = size().height();
    }

    return linearPixel(pixelIndex, length);
}

Qt::Orientation Tg::ScrollBar::orientation() const
{
    return _orientation;
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

QChar Tg::ScrollBar::sliderCharacter() const
{
    if (_sliderCharacter.isNull()) {
        return style()->sliderCharacter;
    } else {
        return _sliderCharacter;
    }
}

Terminal::Color Tg::ScrollBar::sliderColor() const
{
    if (_sliderColor.isEmpty()) {
        return style()->sliderColor;
    } else {
        return _sliderColor;
    }
}

Terminal::Color Tg::ScrollBar::sliderBackgroundColor() const
{
    if (_sliderBackgroundColor.isEmpty()) {
        return style()->sliderBackgroundColor;
    } else {
        return _sliderBackgroundColor;
    }
}

Terminal::Color Tg::ScrollBar::sliderActiveColor() const
{
    if (_sliderActiveColor.isEmpty()) {
        return style()->sliderActiveColor;
    } else {
        return _sliderActiveColor;
    }
}

QChar Tg::ScrollBar::backwardArrowUpCharacter() const
{
    if (_backwardArrowUpCharacter.isNull()) {
        return style()->backwardArrowUpCharacter;
    } else {
        return _backwardArrowUpCharacter;
    }
}

QChar Tg::ScrollBar::backwardArrowLeftCharacter() const
{
    if (_backwardArrowLeftCharacter.isNull()) {
        return style()->backwardArrowLeftCharacter;
    } else {
        return _backwardArrowLeftCharacter;
    }
}

Terminal::Color Tg::ScrollBar::backwardArrowColor() const
{
    if (_backwardArrowColor.isEmpty()) {
        return style()->backwardArrowColor;
    } else {
        return _backwardArrowColor;
    }
}

Terminal::Color Tg::ScrollBar::backwardArrowActiveColor() const
{
    if (_backwardArrowActiveColor.isEmpty()) {
        return style()->backwardArrowActiveColor;
    } else {
        return _backwardArrowActiveColor;
    }
}

Terminal::Color Tg::ScrollBar::backwardArrowInactiveColor() const
{
    if (_backwardArrowInactiveColor.isEmpty()) {
        return style()->backwardArrowInactiveColor;
    } else {
        return _backwardArrowInactiveColor;
    }
}

Terminal::Color Tg::ScrollBar::backwardArrowBackgroundColor() const
{
    if (_backwardArrowBackgroundColor.isEmpty()) {
        return style()->backwardArrowBackgroundColor;
    } else {
        return _backwardArrowBackgroundColor;
    }
}

Terminal::Color Tg::ScrollBar::backwardArrowActiveBackgroundColor() const
{
    if (_backwardArrowActiveBackgroundColor.isEmpty()) {
        return style()->backwardArrowActiveBackgroundColor;
    } else {
        return _backwardArrowActiveBackgroundColor;
    }
}

Terminal::Color Tg::ScrollBar::backwardArrowInactiveBackgroundColor() const
{
    if (_backwardArrowInactiveBackgroundColor.isEmpty()) {
        return style()->backwardArrowInactiveBackgroundColor;
    } else {
        return _backwardArrowInactiveBackgroundColor;
    }
}

QChar Tg::ScrollBar::forwardArrowDownCharacter() const
{
    if (_forwardArrowDownCharacter.isNull()) {
        return style()->forwardArrowDownCharacter;
    } else {
        return _forwardArrowDownCharacter;
    }
}

QChar Tg::ScrollBar::forwardArrowRightCharacter() const
{
    if (_forwardArrowRightCharacter.isNull()) {
        return style()->forwardArrowRightCharacter;
    } else {
        return _forwardArrowRightCharacter;
    }
}

Terminal::Color Tg::ScrollBar::forwardArrowColor() const
{
    if (_forwardArrowColor.isEmpty()) {
        return style()->forwardArrowColor;
    } else {
        return _forwardArrowColor;
    }
}

Terminal::Color Tg::ScrollBar::forwardArrowActiveColor() const
{
    if (_forwardArrowActiveColor.isEmpty()) {
        return style()->forwardArrowActiveColor;
    } else {
        return _forwardArrowActiveColor;
    }
}

Terminal::Color Tg::ScrollBar::forwardArrowInactiveColor() const
{
    if (_forwardArrowInactiveColor.isEmpty()) {
        return style()->forwardArrowInactiveColor;
    } else {
        return _forwardArrowInactiveColor;
    }
}

Terminal::Color Tg::ScrollBar::forwardArrowBackgroundColor() const
{
    if (_forwardArrowBackgroundColor.isEmpty()) {
        return style()->forwardArrowBackgroundColor;
    } else {
        return _forwardArrowBackgroundColor;
    }
}

Terminal::Color Tg::ScrollBar::forwardArrowActiveBackgroundColor() const
{
    if (_forwardArrowActiveBackgroundColor.isEmpty()) {
        return style()->forwardArrowActiveBackgroundColor;
    } else {
        return _forwardArrowActiveBackgroundColor;
    }
}

Terminal::Color Tg::ScrollBar::forwardArrowInactiveBackgroundColor() const
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

void Tg::ScrollBar::setSliderPosition(const int sliderPosition)
{
    if (_sliderPosition == sliderPosition)
        return;

    _sliderPosition = sliderPosition;
    emit sliderPositionChanged(_sliderPosition);
}

void Tg::ScrollBar::setSliderCharacter(const QChar &sliderCharacter)
{
    if (_sliderCharacter == sliderCharacter)
        return;

    _sliderCharacter = sliderCharacter;
    emit sliderCharacterChanged(_sliderCharacter);
}

void Tg::ScrollBar::setSliderColor(const Terminal::Color &sliderColor)
{
    if (_sliderColor == sliderColor)
        return;

    _sliderColor = sliderColor;
    emit sliderColorChanged(_sliderColor);
}

void Tg::ScrollBar::setSliderBackgroundColor(const Terminal::Color &sliderBackgroundColor)
{
    if (_sliderBackgroundColor == sliderBackgroundColor)
        return;

    _sliderBackgroundColor = sliderBackgroundColor;
    emit sliderBackgroundColorChanged(_sliderBackgroundColor);
}

void Tg::ScrollBar::setSliderActiveColor(const Terminal::Color &sliderActiveColor)
{
    if (_sliderActiveColor == sliderActiveColor)
        return;

    _sliderActiveColor = sliderActiveColor;
    emit sliderActiveColorChanged(_sliderActiveColor);
}

void Tg::ScrollBar::setBackwardArrowUpCharacter(const QChar &backwardArrowUpCharacter)
{
    if (_backwardArrowUpCharacter == backwardArrowUpCharacter)
        return;

    _backwardArrowUpCharacter = backwardArrowUpCharacter;
    emit backwardArrowUpCharacterChanged(_backwardArrowUpCharacter);
}

void Tg::ScrollBar::setBackwardArrowLeftCharacter(const QChar &backwardArrowLeftCharacter)
{
    if (_backwardArrowLeftCharacter == backwardArrowLeftCharacter)
        return;

    _backwardArrowLeftCharacter = backwardArrowLeftCharacter;
    emit backwardArrowLeftCharacterChanged(_backwardArrowLeftCharacter);
}

void Tg::ScrollBar::setBackwardArrowColor(const Terminal::Color &backwardArrowColor)
{
    if (_backwardArrowColor == backwardArrowColor)
        return;

    _backwardArrowColor = backwardArrowColor;
    emit backwardArrowColorChanged(_backwardArrowColor);
}

void Tg::ScrollBar::setBackwardArrowActiveColor(const Terminal::Color &backwardArrowActiveColor)
{
    if (_backwardArrowActiveColor == backwardArrowActiveColor)
        return;

    _backwardArrowActiveColor = backwardArrowActiveColor;
    emit backwardArrowActiveColorChanged(_backwardArrowActiveColor);
}

void Tg::ScrollBar::setBackwardArrowInactiveColor(const Terminal::Color &backwardArrowInactiveColor)
{
    if (_backwardArrowInactiveColor == backwardArrowInactiveColor)
        return;

    _backwardArrowInactiveColor = backwardArrowInactiveColor;
    emit backwardArrowInactiveColorChanged(_backwardArrowInactiveColor);
}

void Tg::ScrollBar::setBackwardArrowBackgroundColor(const Terminal::Color &backwardArrowBackgroundColor)
{
    if (_backwardArrowBackgroundColor == backwardArrowBackgroundColor)
        return;

    _backwardArrowBackgroundColor = backwardArrowBackgroundColor;
    emit backwardArrowColorBackgroundChanged(_backwardArrowBackgroundColor);
}

void Tg::ScrollBar::setBackwardArrowActiveBackgroundColor(const Terminal::Color &backwardArrowActiveBackgroundColor)
{
    if (_backwardArrowActiveBackgroundColor == backwardArrowActiveBackgroundColor)
        return;

    _backwardArrowActiveBackgroundColor = backwardArrowActiveBackgroundColor;
    emit backwardArrowActiveColorBackgroundChanged(_backwardArrowActiveBackgroundColor);
}

void Tg::ScrollBar::setBackwardArrowInactiveBackgroundColor(const Terminal::Color &backwardArrowInactiveBackgroundColor)
{
    if (_backwardArrowInactiveBackgroundColor == backwardArrowInactiveBackgroundColor)
        return;

    _backwardArrowInactiveBackgroundColor = backwardArrowInactiveBackgroundColor;
    emit backwardArrowInactiveColorBackgroundChanged(_backwardArrowInactiveBackgroundColor);
}

void Tg::ScrollBar::setForwardArrowDownCharacter(const QChar &forwardArrowDownCharacter)
{
    if (_forwardArrowDownCharacter == forwardArrowDownCharacter)
        return;

    _forwardArrowDownCharacter = forwardArrowDownCharacter;
    emit forwardArrowDownCharacterChanged(_forwardArrowDownCharacter);
}

void Tg::ScrollBar::setForwardArrowRightCharacter(const QChar &forwardArrowRightCharacter)
{
    if (_forwardArrowRightCharacter == forwardArrowRightCharacter)
        return;

    _forwardArrowRightCharacter = forwardArrowRightCharacter;
    emit forwardArrowRightCharacterChanged(_forwardArrowRightCharacter);
}

void Tg::ScrollBar::setForwardArrowColor(const Terminal::Color &forwardArrowColor)
{
    if (_forwardArrowColor == forwardArrowColor)
        return;

    _forwardArrowColor = forwardArrowColor;
    emit forwardArrowColorChanged(_forwardArrowColor);
}

void Tg::ScrollBar::setForwardArrowActiveColor(const Terminal::Color &forwardArrowActiveColor)
{
    if (_forwardArrowActiveColor == forwardArrowActiveColor)
        return;

    _forwardArrowActiveColor = forwardArrowActiveColor;
    emit forwardArrowActiveColorChanged(_forwardArrowActiveColor);
}

void Tg::ScrollBar::setForwardArrowInactiveColor(const Terminal::Color &forwardArrowInactiveColor)
{
    if (_forwardArrowInactiveColor == forwardArrowInactiveColor)
        return;

    _forwardArrowInactiveColor = forwardArrowInactiveColor;
    emit forwardArrowInactiveColorChanged(_forwardArrowInactiveColor);
}

void Tg::ScrollBar::setForwardArrowBackgroundColor(const Terminal::Color &forwardArrowBackgroundColor)
{
    if (_forwardArrowBackgroundColor == forwardArrowBackgroundColor)
        return;

    _forwardArrowBackgroundColor = forwardArrowBackgroundColor;
    emit forwardArrowColorBackgroundChanged(_forwardArrowBackgroundColor);
}

void Tg::ScrollBar::setForwardArrowActiveBackgroundColor(const Terminal::Color &forwardArrowActiveBackgroundColor)
{
    if (_forwardArrowActiveBackgroundColor == forwardArrowActiveBackgroundColor)
        return;

    _forwardArrowActiveBackgroundColor = forwardArrowActiveBackgroundColor;
    emit forwardArrowActiveColorBackgroundChanged(_forwardArrowActiveBackgroundColor);
}

void Tg::ScrollBar::setForwardArrowInactiveBackgroundColor(const Terminal::Color &forwardArrowInactiveBackgroundColor)
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
}

void Tg::ScrollBar::consumeKeyboardBuffer(const QString &keyboardBuffer)
{
     if (keyboardBuffer.contains(Terminal::Key::up)
             || keyboardBuffer.contains(Terminal::Key::left)) {
         setSliderPosition(sliderPosition() - 1);
         emit backwardArrowClicked();
     }

     if (keyboardBuffer.contains(Terminal::Key::down)
             || keyboardBuffer.contains(Terminal::Key::right)) {
         setSliderPosition(sliderPosition() + 1);
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
            result.append(Terminal::Color::code(
                              backwardArrowActiveColor(), backwardArrowActiveBackgroundColor()
                              ));
        } else {
            result.append(Terminal::Color::code(
                              backwardArrowColor(), backwardArrowBackgroundColor()
                              ));
        }

        if (orientation() == Qt::Orientation::Horizontal) {
            result.append(backwardArrowLeftCharacter());
        } else {
            result.append(backwardArrowUpCharacter());
        }

        return result;
    //} else if (pixel == ((sliderPosition() + 1) * length / maximum())) {
    } else if (pixel == (sliderPosition() + 1)) {
        // Draw slider
        if (_sliderPressTimer.isActive()) {
            result.append(Terminal::Color::code(
                              sliderActiveColor(), sliderBackgroundColor()
                              ));
        } else {
            result.append(Terminal::Color::code(
                              sliderColor(), sliderBackgroundColor()
                              ));
        }

        result.append(sliderCharacter());

        return result;
    } else if (pixel == length - 1) {
        // Draw second arrow
        // TODO: handle all the color madness ;-) Active, normal, inactive colors
        if (_forwardArrowPressTimer.isActive()) {
            result.append(Terminal::Color::code(
                              forwardArrowActiveColor(), forwardArrowActiveBackgroundColor()
                              ));
        } else {
            result.append(Terminal::Color::code(
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

    result.append(Terminal::Color::code(
                      textColor(), backgroundColor()
                      ));

    result.append(backgroundCharacter());

    return result;
}
