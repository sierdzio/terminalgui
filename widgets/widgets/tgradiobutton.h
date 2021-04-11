#pragma once

#include <widgets/tgbutton.h>

#include <QPointer>
#include <QSharedPointer>

namespace Tg {
class RadioButton;
class ExclusiveGroup : public QObject
{
    Q_OBJECT

public:
    ExclusiveGroup();

    void registerRadioButton(RadioButton *radioButton);
    void deRegisterRadioButton(RadioButton *radioButton);

protected slots:
    void onRadioButtonCheckedChanged(const bool checked);

private:
    QList<QPointer<RadioButton>> _members;
};

using ExclusiveGroupPointer = QSharedPointer<ExclusiveGroup>;

class RadioButton : public Button
{
    Q_OBJECT

    Q_PROPERTY(bool checked READ checked WRITE setChecked NOTIFY checkedChanged)
    Q_PROPERTY(bool autoExclusive READ autoExclusive WRITE setAutoExclusive NOTIFY autoExclusiveChanged)

public:
    RadioButton(Widget *parent);
    RadioButton(Screen *screen);
    RadioButton(const QString &text = QString(), Widget *parent = nullptr);
    RadioButton(const QString &text = QString(), Screen *screen = nullptr);

    void toggleState();
    bool checked() const;

    bool autoExclusive() const;
    ExclusiveGroupPointer exclusiveGroup() const;

public slots:
    void setChecked(const bool checked);
    void setAutoExclusive(const bool autoExclusive);

signals:
    void checkedChanged(const bool checked) const;
    void autoExclusiveChanged(const bool autoExclusive) const;

protected:
    void init() override;
    bool consumeKeyboardBuffer(const QString &keyboardBuffer) override;
    QString radioButtonText() const;

private:
    void prepareAutoExclusiveGroup();

    bool _checked = true;
    bool _autoExclusive = true;
    ExclusiveGroupPointer _group;
};
}
