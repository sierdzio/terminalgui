#include "tglabel.h"

#include <QTextStream>

TgLabel::TgLabel(const QString &text, QObject *parent) : TgWidget(parent)
{
    setText(text);
}

QString TgLabel::text() const
{
    return _text;
}

void TgLabel::setText(const QString &text)
{
    if (_text == text)
        return;

    _text = text;

    QSize current(size());
    if (current.width() != _text.length()) {
        current.setWidth(text.length());
        setSize(current);
    }

    emit textChanged(_text);
}

void TgLabel::draw()
{
    if (visible()) {
        QTextStream stream(stdout);
        stream << text();
    }
}
