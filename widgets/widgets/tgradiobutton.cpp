#include "tgradiobutton.h"

Tg::ExclusiveGroup::ExclusiveGroup() : QObject(nullptr)
{
}

void Tg::ExclusiveGroup::registerRadioButton(Tg::RadioButton *radioButton)
{
    bool hasOneChecked = false;
    for (const auto &member : qAsConst(_members)) {
        if (member.isNull()) {
            continue;
        }

        if (member->checked()) {
            hasOneChecked = true;
            break;
        }
    }

    _members.append(radioButton);

    if (hasOneChecked) {
        radioButton->setChecked(false);
    } else {
        radioButton->setChecked(true);
    }

    CHECK(connect(radioButton, &RadioButton::checkedChanged,
                  this, &ExclusiveGroup::onRadioButtonCheckedChanged));
}

void Tg::ExclusiveGroup::deRegisterRadioButton(Tg::RadioButton *radioButton)
{
    _members.removeOne(radioButton);
}

void Tg::ExclusiveGroup::onRadioButtonCheckedChanged(const bool checked)
{
    if (checked == false) {
        return;
    }

    RadioButton *current = qobject_cast<RadioButton*>(sender());
    if (current == nullptr) {
        return;
    }

    for (const auto &member : qAsConst(_members)) {
        if (member.isNull() || member == current) {
            continue;
        }

        member->setChecked(false);
    }
}

Tg::RadioButton::RadioButton(Tg::Widget *parent) : Tg::Button(parent)
{
    init();
}

Tg::RadioButton::RadioButton(Tg::Screen *screen) : Tg::Button(screen)
{
    init();
}

Tg::RadioButton::RadioButton(const QString &text, Tg::Widget *parent) : Tg::Button(text, parent)
{
    init();
}

Tg::RadioButton::RadioButton(const QString &text, Tg::Screen *screen) : Tg::Button(text, screen)
{
    init();
}

void Tg::RadioButton::toggleState()
{
    setChecked(true);
}

bool Tg::RadioButton::checked() const
{
    return _checked;
}

bool Tg::RadioButton::autoExclusive() const
{
    return _autoExclusive;
}

Tg::ExclusiveGroupPointer Tg::RadioButton::exclusiveGroup() const
{
    return _group;
}

void Tg::RadioButton::setChecked(const bool checked)
{
    if (highlighted() != checked) {
        setHighlighted(checked);
    }

    if (_checked == checked)
        return;

    _checked = checked;
    emit checkedChanged(_checked);

    setReservedText(radioButtonText());
}

void Tg::RadioButton::setAutoExclusive(const bool autoExclusive)
{
    if (_autoExclusive == autoExclusive)
        return;

    _autoExclusive = autoExclusive;
    emit autoExclusiveChanged(_autoExclusive);

    if (autoExclusive) {
        prepareAutoExclusiveGroup();
    } else {
        // TODO: remove this object from auto exclusive group
    }
}

void Tg::RadioButton::init()
{
    setReservedText(radioButtonText());
    prepareAutoExclusiveGroup();
    setHighlighted(checked());

    Button::init();

    CHECK(connect(this, &RadioButton::clicked,
                  this, &RadioButton::toggleState));
}

void Tg::RadioButton::consumeKeyboardBuffer(const QString &keyboardBuffer)
{
    if (keyboardBuffer.contains(Terminal::Key::space)) {
        setTextColor(pressedTextColor());
        setBackgroundColor(pressedBackgroundColor());
        emit clicked();
        return;
    }

    Button::consumeKeyboardBuffer(keyboardBuffer);
}

QString Tg::RadioButton::radioButtonText() const
{
    if (checked()) {
        return style()->radioButtonChecked;
    } else {
        return style()->radioButtonUnChecked;
    }
}

void Tg::RadioButton::prepareAutoExclusiveGroup()
{
    // Standalone widget cannot be auto exclusive
    if (parentWidget() == nullptr) {
        return;
    }

    // Look for other radio buttons (siblings only)
    QList<QPointer<RadioButton>> members;
    for (auto widget : parentWidget()->children()) {
        auto radioButton = qobject_cast<RadioButton*>(widget);
        if (radioButton && radioButton->autoExclusive()) {
            if (radioButton->exclusiveGroup().isNull()) {
                members.append(radioButton);
            } else {
                _group = radioButton->exclusiveGroup();
                _group->registerRadioButton(this);
                return;
            }
        }
    }

    _group = ExclusiveGroupPointer::create();
    for (const auto &member : qAsConst(members)) {
        _group->registerRadioButton(member);
    }
}
