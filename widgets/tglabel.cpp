#include "tglabel.h"

#include "textstream.h"
#include <backend/backend.h>

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
        TextStream stream(stdout);

        if (position().x() > 0) {
            //qDebug() << "Capabilities:" << stream.device()->isSequential()
            //         << stream.device()->isOpen() << stream.device()->isReadable()
            //         << stream.device()->isWritable();

            for (int i = 0; i < position().x(); ++i) {
                stream << Commands::forward;
            }
        }

        stream << Terminal::colorCode(textColor());
        stream << text();
        stream << Colors::end;
    }
}
