#pragma once

#include <widgets/tgwidget.h>

#include <QChar>
#include <QString>
#include <QTimer>

namespace Tg {
class ScrollBar : public Widget
{
    Q_OBJECT

    Q_PROPERTY(Qt::Orientation orientation READ orientation WRITE setOrientation NOTIFY orientationChanged)

    // Slider
    Q_PROPERTY(int minimum READ minimum WRITE setMinimum NOTIFY minimumChanged)
    Q_PROPERTY(int maximum READ maximum WRITE setMaximum NOTIFY maximumChanged)
    Q_PROPERTY(QChar sliderCharacter READ sliderCharacter WRITE setSliderCharacter NOTIFY sliderCharacterChanged)
    Q_PROPERTY(Terminal::Color sliderColor READ sliderColor WRITE setSliderColor NOTIFY sliderColorChanged)
    Q_PROPERTY(Terminal::Color sliderActiveColor READ sliderActiveColor WRITE setSliderActiveColor NOTIFY sliderActiveColorChanged)
    Q_PROPERTY(Terminal::Color sliderInactiveColor READ sliderInactiveColor WRITE setSliderInactiveColor NOTIFY sliderInactiveColorChanged)

    Q_PROPERTY(Terminal::Color sliderBackgroundColor READ sliderBackgroundColor WRITE setSliderBackgroundColor NOTIFY sliderBackgroundColorChanged)
    Q_PROPERTY(Terminal::Color sliderActiveBackgroundColor READ sliderActiveBackgroundColor WRITE setSliderActiveBackgroundColor NOTIFY sliderActiveBackgroundColorChanged)
    Q_PROPERTY(Terminal::Color sliderInactiveBackgroundColor READ sliderInactiveBackgroundColor WRITE setSliderInactiveBackgroundColor NOTIFY sliderInactiveBackgroundColorChanged)

    // Backward arrow (up or left)
    Q_PROPERTY(QChar backwardArrowUpCharacter READ backwardArrowUpCharacter WRITE setBackwardArrowUpCharacter NOTIFY backwardArrowUpCharacterChanged)
    Q_PROPERTY(QChar backwardArrowLeftCharacter READ backwardArrowLeftCharacter WRITE setBackwardArrowLeftCharacter NOTIFY backwardArrowLeftCharacterChanged)

    Q_PROPERTY(Terminal::Color backwardArrowColor READ backwardArrowColor WRITE setBackwardArrowColor NOTIFY backwardArrowColorChanged)
    Q_PROPERTY(Terminal::Color backwardArrowActiveColor READ backwardArrowActiveColor WRITE setBackwardArrowActiveColor NOTIFY backwardArrowActiveColorChanged)
    Q_PROPERTY(Terminal::Color backwardArrowInactiveColor READ backwardArrowInactiveColor WRITE setBackwardArrowInactiveColor NOTIFY backwardArrowInactiveColorChanged)

    Q_PROPERTY(Terminal::Color backwardArrowBackgroundColor READ backwardArrowBackgroundColor WRITE setBackwardArrowBackgroundColor NOTIFY backwardArrowColorBackgroundChanged)
    Q_PROPERTY(Terminal::Color backwardArrowActiveBackgroundColor READ backwardArrowActiveBackgroundColor WRITE setBackwardArrowActiveBackgroundColor NOTIFY backwardArrowActiveColorBackgroundChanged)
    Q_PROPERTY(Terminal::Color backwardArrowInactiveBackgroundColor READ backwardArrowInactiveBackgroundColor WRITE setBackwardArrowInactiveBackgroundColor NOTIFY backwardArrowInactiveColorBackgroundChanged)

    // Forward arrow (down or right)
    Q_PROPERTY(QChar forwardArrowDownCharacter READ forwardArrowDownCharacter WRITE setForwardArrowDownCharacter NOTIFY forwardArrowDownCharacterChanged)
    Q_PROPERTY(QChar forwardArrowRightCharacter READ forwardArrowRightCharacter WRITE setForwardArrowRightCharacter NOTIFY forwardArrowRightCharacterChanged)

    Q_PROPERTY(Terminal::Color forwardArrowColor READ forwardArrowColor WRITE setForwardArrowColor NOTIFY forwardArrowColorChanged)
    Q_PROPERTY(Terminal::Color forwardArrowActiveColor READ forwardArrowActiveColor WRITE setForwardArrowActiveColor NOTIFY forwardArrowActiveColorChanged)
    Q_PROPERTY(Terminal::Color forwardArrowInactiveColor READ forwardArrowInactiveColor WRITE setForwardArrowInactiveColor NOTIFY forwardArrowInactiveColorChanged)

    Q_PROPERTY(Terminal::Color forwardArrowBackgroundColor READ forwardArrowBackgroundColor WRITE setForwardArrowBackgroundColor NOTIFY forwardArrowColorBackgroundChanged)
    Q_PROPERTY(Terminal::Color forwardArrowActiveBackgroundColor READ forwardArrowActiveBackgroundColor WRITE setForwardArrowActiveBackgroundColor NOTIFY forwardArrowActiveColorBackgroundChanged)
    Q_PROPERTY(Terminal::Color forwardArrowInactiveBackgroundColor READ forwardArrowInactiveBackgroundColor WRITE setForwardArrowInactiveBackgroundColor NOTIFY forwardArrowInactiveColorBackgroundChanged)


public:
    ScrollBar(Widget *parent);
    ScrollBar(Screen *screen);

    QString drawPixel(const QPoint &pixel) const override;

    Qt::Orientation orientation() const;

    int minimum() const;
    int maximum() const;
    int sliderPosition() const;
    QChar sliderCharacter() const;
    Terminal::Color sliderColor() const;
    Terminal::Color sliderActiveColor() const;
    Terminal::Color sliderInactiveColor() const;
    Terminal::Color sliderBackgroundColor() const;
    Terminal::Color sliderActiveBackgroundColor() const;
    Terminal::Color sliderInactiveBackgroundColor() const;

    QChar backwardArrowUpCharacter() const;
    QChar backwardArrowLeftCharacter() const;
    Terminal::Color backwardArrowColor() const;
    Terminal::Color backwardArrowActiveColor() const;
    Terminal::Color backwardArrowInactiveColor() const;
    Terminal::Color backwardArrowBackgroundColor() const;
    Terminal::Color backwardArrowActiveBackgroundColor() const;
    Terminal::Color backwardArrowInactiveBackgroundColor() const;

    QChar forwardArrowDownCharacter() const;
    QChar forwardArrowRightCharacter() const;
    Terminal::Color forwardArrowColor() const;
    Terminal::Color forwardArrowActiveColor() const;
    Terminal::Color forwardArrowInactiveColor() const;
    Terminal::Color forwardArrowBackgroundColor() const;
    Terminal::Color forwardArrowActiveBackgroundColor() const;
    Terminal::Color forwardArrowInactiveBackgroundColor() const;

public slots:
    void setOrientation(const Qt::Orientation orientation);

    void setMinimum(const int minimum);
    void setMaximum(const int maximum);
    void setSliderPosition(const int sliderPosition);
    void setSliderCharacter(const QChar &sliderCharacter);
    void setSliderColor(const Terminal::Color &sliderColor);
    void setSliderActiveColor(const Terminal::Color &sliderActiveColor);
    void setSliderInactiveColor(const Terminal::Color &sliderInactiveColor);
    void setSliderBackgroundColor(const Terminal::Color &sliderBackgroundColor);
    void setSliderActiveBackgroundColor(const Terminal::Color &sliderActiveBackgroundColor);
    void setSliderInactiveBackgroundColor(const Terminal::Color &sliderInactiveBackgroundColor);

    void setBackwardArrowUpCharacter(const QChar &backwardArrowUpCharacter);
    void setBackwardArrowLeftCharacter(const QChar &backwardArrowLeftCharacter);
    void setBackwardArrowColor(const Terminal::Color &backwardArrowColor);
    void setBackwardArrowActiveColor(const Terminal::Color &backwardArrowActiveColor);
    void setBackwardArrowInactiveColor(const Terminal::Color &backwardArrowInactiveColor);
    void setBackwardArrowBackgroundColor(const Terminal::Color &backwardArrowBackgroundColor);
    void setBackwardArrowActiveBackgroundColor(const Terminal::Color &backwardArrowActiveBackgroundColor);
    void setBackwardArrowInactiveBackgroundColor(const Terminal::Color &backwardArrowInactiveBackgroundColor);

    void setForwardArrowDownCharacter(const QChar &forwardArrowDownCharacter);
    void setForwardArrowRightCharacter(const QChar &forwardArrowRightCharacter);
    void setForwardArrowColor(const Terminal::Color &forwardArrowColor);
    void setForwardArrowActiveColor(const Terminal::Color &forwardArrowActiveColor);
    void setForwardArrowInactiveColor(const Terminal::Color &forwardArrowInactiveColor);
    void setForwardArrowBackgroundColor(const Terminal::Color &forwardArrowBackgroundColor);
    void setForwardArrowActiveBackgroundColor(const Terminal::Color &forwardArrowActiveBackgroundColor);
    void setForwardArrowInactiveBackgroundColor(const Terminal::Color &forwardArrowInactiveBackgroundColor);

signals:
    void backwardArrowClicked() const;
    void forwardArrowClicked() const;

    void orientationChanged(const Qt::Orientation orientation) const;

    void minimumChanged(const int minimum) const;
    void maximumChanged(const int maximum) const;
    void sliderPositionChanged(const int sliderPosition) const;
    void sliderCharacterChanged(const QChar &sliderCharacter) const;
    void sliderColorChanged(const Terminal::Color  &sliderColor) const;
    void sliderActiveColorChanged(const Terminal::Color  &sliderActiveColor) const;
    void sliderInactiveColorChanged(const Terminal::Color &sliderInactiveColor) const;
    void sliderBackgroundColorChanged(const Terminal::Color  &sliderBackgroundColor) const;
    void sliderActiveBackgroundColorChanged(const Terminal::Color &sliderActiveBackgroundColor) const;
    void sliderInactiveBackgroundColorChanged(const Terminal::Color &sliderInactiveBackgroundColor) const;

    void backwardArrowUpCharacterChanged(const QChar &backwardArrowUpCharacter) const;
    void backwardArrowLeftCharacterChanged(const QChar &backwardArrowLeftCharacter) const;
    void backwardArrowColorChanged(const Terminal::Color  &backwardArrowColor) const;
    void backwardArrowActiveColorChanged(const Terminal::Color  &backwardArrowActiveColor) const;
    void backwardArrowInactiveColorChanged(const Terminal::Color  &backwardArrowInactiveColor) const;
    void backwardArrowColorBackgroundChanged(const Terminal::Color  &backwardArrowBackgroundColor) const;
    void backwardArrowActiveColorBackgroundChanged(const Terminal::Color  &backwardArrowActiveBackgroundColor) const;
    void backwardArrowInactiveColorBackgroundChanged(const Terminal::Color  &backwardArrowInactiveBackgroundColor) const;

    void forwardArrowDownCharacterChanged(const QChar &forwardArrowDownCharacter) const;
    void forwardArrowRightCharacterChanged(const QChar &forwardArrowRightCharacter) const;
    void forwardArrowColorChanged(const Terminal::Color  &forwardArrowColor) const;
    void forwardArrowActiveColorChanged(const Terminal::Color  &forwardArrowActiveColor) const;
    void forwardArrowInactiveColorChanged(const Terminal::Color  &forwardArrowInactiveColor) const;
    void forwardArrowColorBackgroundChanged(const Terminal::Color  &forwardArrowBackgroundColor) const;
    void forwardArrowActiveColorBackgroundChanged(const Terminal::Color  &forwardArrowActiveBackgroundColor) const;
    void forwardArrowInactiveColorBackgroundChanged(const Terminal::Color  &forwardArrowInactiveBackgroundColor) const;

protected slots:
    void enforceProperSize();

protected:
    void init() override;
    void consumeKeyboardBuffer(const QString &keyboardBuffer) override;
    QString linearPixel(const int pixel, const int length) const;

private:
    Qt::Orientation _orientation = Qt::Orientation::Vertical;

    int _minimum = 0;
    int _maximum = 100;
    int _sliderPosition = 3;
    QChar _sliderCharacter;
    Terminal::Color _sliderColor = Terminal::Color::Predefined::Empty;
    Terminal::Color _sliderActiveColor = Terminal::Color::Predefined::Empty;
    Terminal::Color _sliderInactiveColor = Terminal::Color::Predefined::Empty;
    Terminal::Color _sliderBackgroundColor = Terminal::Color::Predefined::Empty;
    Terminal::Color _sliderActiveBackgroundColor = Terminal::Color::Predefined::Empty;
    Terminal::Color _sliderInactiveBackgroundColor = Terminal::Color::Predefined::Empty;
    QTimer _sliderPressTimer;

    QChar _backwardArrowUpCharacter;
    QChar _backwardArrowLeftCharacter;
    Terminal::Color _backwardArrowColor = Terminal::Color::Predefined::Empty;
    Terminal::Color _backwardArrowActiveColor = Terminal::Color::Predefined::Empty;
    Terminal::Color _backwardArrowInactiveColor = Terminal::Color::Predefined::Empty;
    Terminal::Color _backwardArrowBackgroundColor = Terminal::Color::Predefined::Empty;
    Terminal::Color _backwardArrowActiveBackgroundColor = Terminal::Color::Predefined::Empty;
    Terminal::Color _backwardArrowInactiveBackgroundColor = Terminal::Color::Predefined::Empty;
    QTimer _backwardArrowPressTimer;

    QChar _forwardArrowDownCharacter;
    QChar _forwardArrowRightCharacter;
    Terminal::Color _forwardArrowColor = Terminal::Color::Predefined::Empty;
    Terminal::Color _forwardArrowActiveColor = Terminal::Color::Predefined::Empty;
    Terminal::Color _forwardArrowInactiveColor = Terminal::Color::Predefined::Empty;
    Terminal::Color _forwardArrowBackgroundColor = Terminal::Color::Predefined::Empty;
    Terminal::Color _forwardArrowActiveBackgroundColor = Terminal::Color::Predefined::Empty;
    Terminal::Color _forwardArrowInactiveBackgroundColor = Terminal::Color::Predefined::Empty;
    QTimer _forwardArrowPressTimer;
};
}
