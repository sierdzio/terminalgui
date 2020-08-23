#pragma once

#include <widgets/tglabel.h>

namespace Tg {
class LineEdit : public Label
{
    Q_OBJECT

    Q_PROPERTY(QString placeholderText READ placeholderText WRITE setPlaceholderText NOTIFY placeholderTextChanged)

public:
    LineEdit(Widget *parent);
    LineEdit(Screen *screen);
    LineEdit(const QString &placeholderText = QString(), Widget *parent = nullptr);
    LineEdit(const QString &placeholderText = QString(), Screen *screen = nullptr);

    QString placeholderText() const;

public slots:
    void setPlaceholderText(const QString &placeholderText);

signals:
    void placeholderTextChanged(const QString &placeholderText) const;

protected:
    void init() override;
    void consumeKeyboardBuffer(const QByteArray &keyboardBuffer) override;

    void displayPlaceholderText();

private:
    QString _placeholderText;
    QString _realText;
};
}
