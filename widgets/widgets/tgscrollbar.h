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
    Q_PROPERTY(Tg::Color sliderColor READ sliderColor WRITE setSliderColor NOTIFY sliderColorChanged)
    Q_PROPERTY(Tg::Color sliderActiveColor READ sliderActiveColor WRITE setSliderActiveColor NOTIFY sliderActiveColorChanged)
    Q_PROPERTY(Tg::Color sliderInactiveColor READ sliderInactiveColor WRITE setSliderInactiveColor NOTIFY sliderInactiveColorChanged)

    Q_PROPERTY(Tg::Color sliderBackgroundColor READ sliderBackgroundColor WRITE setSliderBackgroundColor NOTIFY sliderBackgroundColorChanged)
    Q_PROPERTY(Tg::Color sliderActiveBackgroundColor READ sliderActiveBackgroundColor WRITE setSliderActiveBackgroundColor NOTIFY sliderActiveBackgroundColorChanged)
    Q_PROPERTY(Tg::Color sliderInactiveBackgroundColor READ sliderInactiveBackgroundColor WRITE setSliderInactiveBackgroundColor NOTIFY sliderInactiveBackgroundColorChanged)

    // Backward arrow (up or left)
    Q_PROPERTY(QChar backwardArrowUpCharacter READ backwardArrowUpCharacter WRITE setBackwardArrowUpCharacter NOTIFY backwardArrowUpCharacterChanged)
    Q_PROPERTY(QChar backwardArrowLeftCharacter READ backwardArrowLeftCharacter WRITE setBackwardArrowLeftCharacter NOTIFY backwardArrowLeftCharacterChanged)

    Q_PROPERTY(Tg::Color backwardArrowColor READ backwardArrowColor WRITE setBackwardArrowColor NOTIFY backwardArrowColorChanged)
    Q_PROPERTY(Tg::Color backwardArrowActiveColor READ backwardArrowActiveColor WRITE setBackwardArrowActiveColor NOTIFY backwardArrowActiveColorChanged)
    Q_PROPERTY(Tg::Color backwardArrowInactiveColor READ backwardArrowInactiveColor WRITE setBackwardArrowInactiveColor NOTIFY backwardArrowInactiveColorChanged)

    Q_PROPERTY(Tg::Color backwardArrowBackgroundColor READ backwardArrowBackgroundColor WRITE setBackwardArrowBackgroundColor NOTIFY backwardArrowColorBackgroundChanged)
    Q_PROPERTY(Tg::Color backwardArrowActiveBackgroundColor READ backwardArrowActiveBackgroundColor WRITE setBackwardArrowActiveBackgroundColor NOTIFY backwardArrowActiveColorBackgroundChanged)
    Q_PROPERTY(Tg::Color backwardArrowInactiveBackgroundColor READ backwardArrowInactiveBackgroundColor WRITE setBackwardArrowInactiveBackgroundColor NOTIFY backwardArrowInactiveColorBackgroundChanged)

    // Forward arrow (down or right)
    Q_PROPERTY(QChar forwardArrowDownCharacter READ forwardArrowDownCharacter WRITE setForwardArrowDownCharacter NOTIFY forwardArrowDownCharacterChanged)
    Q_PROPERTY(QChar forwardArrowRightCharacter READ forwardArrowRightCharacter WRITE setForwardArrowRightCharacter NOTIFY forwardArrowRightCharacterChanged)

    Q_PROPERTY(Tg::Color forwardArrowColor READ forwardArrowColor WRITE setForwardArrowColor NOTIFY forwardArrowColorChanged)
    Q_PROPERTY(Tg::Color forwardArrowActiveColor READ forwardArrowActiveColor WRITE setForwardArrowActiveColor NOTIFY forwardArrowActiveColorChanged)
    Q_PROPERTY(Tg::Color forwardArrowInactiveColor READ forwardArrowInactiveColor WRITE setForwardArrowInactiveColor NOTIFY forwardArrowInactiveColorChanged)

    Q_PROPERTY(Tg::Color forwardArrowBackgroundColor READ forwardArrowBackgroundColor WRITE setForwardArrowBackgroundColor NOTIFY forwardArrowColorBackgroundChanged)
    Q_PROPERTY(Tg::Color forwardArrowActiveBackgroundColor READ forwardArrowActiveBackgroundColor WRITE setForwardArrowActiveBackgroundColor NOTIFY forwardArrowActiveColorBackgroundChanged)
    Q_PROPERTY(Tg::Color forwardArrowInactiveBackgroundColor READ forwardArrowInactiveBackgroundColor WRITE setForwardArrowInactiveBackgroundColor NOTIFY forwardArrowInactiveColorBackgroundChanged)


public:
    ScrollBar(Widget *parent);
    ScrollBar(Screen *screen);

    QString drawPixel(const QPoint &pixel) const override;

    Qt::Orientation orientation() const;

    int length() const;
    int step() const;

    int minimum() const;
    int maximum() const;
    int sliderPosition() const;
    QChar sliderCharacter() const;
    Tg::Color sliderColor() const;
    Tg::Color sliderActiveColor() const;
    Tg::Color sliderInactiveColor() const;
    Tg::Color sliderBackgroundColor() const;
    Tg::Color sliderActiveBackgroundColor() const;
    Tg::Color sliderInactiveBackgroundColor() const;

    QChar backwardArrowUpCharacter() const;
    QChar backwardArrowLeftCharacter() const;
    Tg::Color backwardArrowColor() const;
    Tg::Color backwardArrowActiveColor() const;
    Tg::Color backwardArrowInactiveColor() const;
    Tg::Color backwardArrowBackgroundColor() const;
    Tg::Color backwardArrowActiveBackgroundColor() const;
    Tg::Color backwardArrowInactiveBackgroundColor() const;

    QChar forwardArrowDownCharacter() const;
    QChar forwardArrowRightCharacter() const;
    Tg::Color forwardArrowColor() const;
    Tg::Color forwardArrowActiveColor() const;
    Tg::Color forwardArrowInactiveColor() const;
    Tg::Color forwardArrowBackgroundColor() const;
    Tg::Color forwardArrowActiveBackgroundColor() const;
    Tg::Color forwardArrowInactiveBackgroundColor() const;

public slots:
    void setOrientation(const Qt::Orientation orientation);

    void setMinimum(const int minimum);
    void setMaximum(const int maximum);
    void setValue(const int value);
    void setSliderPosition(const int sliderPosition);
    void setSliderCharacter(const QChar &sliderCharacter);
    void setSliderColor(const Tg::Color &sliderColor);
    void setSliderActiveColor(const Tg::Color &sliderActiveColor);
    void setSliderInactiveColor(const Tg::Color &sliderInactiveColor);
    void setSliderBackgroundColor(const Tg::Color &sliderBackgroundColor);
    void setSliderActiveBackgroundColor(const Tg::Color &sliderActiveBackgroundColor);
    void setSliderInactiveBackgroundColor(const Tg::Color &sliderInactiveBackgroundColor);

    void setBackwardArrowUpCharacter(const QChar &backwardArrowUpCharacter);
    void setBackwardArrowLeftCharacter(const QChar &backwardArrowLeftCharacter);
    void setBackwardArrowColor(const Tg::Color &backwardArrowColor);
    void setBackwardArrowActiveColor(const Tg::Color &backwardArrowActiveColor);
    void setBackwardArrowInactiveColor(const Tg::Color &backwardArrowInactiveColor);
    void setBackwardArrowBackgroundColor(const Tg::Color &backwardArrowBackgroundColor);
    void setBackwardArrowActiveBackgroundColor(const Tg::Color &backwardArrowActiveBackgroundColor);
    void setBackwardArrowInactiveBackgroundColor(const Tg::Color &backwardArrowInactiveBackgroundColor);

    void setForwardArrowDownCharacter(const QChar &forwardArrowDownCharacter);
    void setForwardArrowRightCharacter(const QChar &forwardArrowRightCharacter);
    void setForwardArrowColor(const Tg::Color &forwardArrowColor);
    void setForwardArrowActiveColor(const Tg::Color &forwardArrowActiveColor);
    void setForwardArrowInactiveColor(const Tg::Color &forwardArrowInactiveColor);
    void setForwardArrowBackgroundColor(const Tg::Color &forwardArrowBackgroundColor);
    void setForwardArrowActiveBackgroundColor(const Tg::Color &forwardArrowActiveBackgroundColor);
    void setForwardArrowInactiveBackgroundColor(const Tg::Color &forwardArrowInactiveBackgroundColor);

signals:
    void backwardArrowClicked() const;
    void forwardArrowClicked() const;

    void orientationChanged(const Qt::Orientation orientation) const;

    void minimumChanged(const int minimum) const;
    void maximumChanged(const int maximum) const;
    void sliderPositionChanged(const int sliderPosition) const;
    void sliderCharacterChanged(const QChar &sliderCharacter) const;
    void sliderColorChanged(const Tg::Color  &sliderColor) const;
    void sliderActiveColorChanged(const Tg::Color  &sliderActiveColor) const;
    void sliderInactiveColorChanged(const Tg::Color &sliderInactiveColor) const;
    void sliderBackgroundColorChanged(const Tg::Color  &sliderBackgroundColor) const;
    void sliderActiveBackgroundColorChanged(const Tg::Color &sliderActiveBackgroundColor) const;
    void sliderInactiveBackgroundColorChanged(const Tg::Color &sliderInactiveBackgroundColor) const;

    void backwardArrowUpCharacterChanged(const QChar &backwardArrowUpCharacter) const;
    void backwardArrowLeftCharacterChanged(const QChar &backwardArrowLeftCharacter) const;
    void backwardArrowColorChanged(const Tg::Color  &backwardArrowColor) const;
    void backwardArrowActiveColorChanged(const Tg::Color  &backwardArrowActiveColor) const;
    void backwardArrowInactiveColorChanged(const Tg::Color  &backwardArrowInactiveColor) const;
    void backwardArrowColorBackgroundChanged(const Tg::Color  &backwardArrowBackgroundColor) const;
    void backwardArrowActiveColorBackgroundChanged(const Tg::Color  &backwardArrowActiveBackgroundColor) const;
    void backwardArrowInactiveColorBackgroundChanged(const Tg::Color  &backwardArrowInactiveBackgroundColor) const;

    void forwardArrowDownCharacterChanged(const QChar &forwardArrowDownCharacter) const;
    void forwardArrowRightCharacterChanged(const QChar &forwardArrowRightCharacter) const;
    void forwardArrowColorChanged(const Tg::Color  &forwardArrowColor) const;
    void forwardArrowActiveColorChanged(const Tg::Color  &forwardArrowActiveColor) const;
    void forwardArrowInactiveColorChanged(const Tg::Color  &forwardArrowInactiveColor) const;
    void forwardArrowColorBackgroundChanged(const Tg::Color  &forwardArrowBackgroundColor) const;
    void forwardArrowActiveColorBackgroundChanged(const Tg::Color  &forwardArrowActiveBackgroundColor) const;
    void forwardArrowInactiveColorBackgroundChanged(const Tg::Color  &forwardArrowInactiveBackgroundColor) const;

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
    Tg::Color _sliderColor;
    Tg::Color _sliderActiveColor;
    Tg::Color _sliderInactiveColor;
    Tg::Color _sliderBackgroundColor;
    Tg::Color _sliderActiveBackgroundColor;
    Tg::Color _sliderInactiveBackgroundColor;
    QTimer _sliderPressTimer;

    QChar _backwardArrowUpCharacter;
    QChar _backwardArrowLeftCharacter;
    Tg::Color _backwardArrowColor;
    Tg::Color _backwardArrowActiveColor;
    Tg::Color _backwardArrowInactiveColor;
    Tg::Color _backwardArrowBackgroundColor;
    Tg::Color _backwardArrowActiveBackgroundColor;
    Tg::Color _backwardArrowInactiveBackgroundColor;
    QTimer _backwardArrowPressTimer;

    QChar _forwardArrowDownCharacter;
    QChar _forwardArrowRightCharacter;
    Tg::Color _forwardArrowColor;
    Tg::Color _forwardArrowActiveColor;
    Tg::Color _forwardArrowInactiveColor;
    Tg::Color _forwardArrowBackgroundColor;
    Tg::Color _forwardArrowActiveBackgroundColor;
    Tg::Color _forwardArrowInactiveBackgroundColor;
    QTimer _forwardArrowPressTimer;
};
}
