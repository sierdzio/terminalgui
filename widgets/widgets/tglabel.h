#pragma once

#include <widgets/tgwidget.h>
#include <utils/tgtext.h>

namespace Tg {
class Label : public Widget
{
    Q_OBJECT

    Q_PROPERTY(QString text READ text WRITE setText NOTIFY textChanged)
    Q_PROPERTY(bool highlighted READ highlighted WRITE setHighlighted NOTIFY highlightedChanged)

public:
    Label(Widget *parent);
    Label(Screen *screen);
    Label(const QString &text = QString(), Widget *parent = nullptr);
    Label(const QString &text = QString(), Screen *screen = nullptr);

    QString text() const;

    bool highlighted() const;

    Text::Wrap wrapMode() const;
    void setWrapMode(const Text::Wrap newWrapMode);

signals:
    void textChanged(const QString &text) const;
    void highlightedChanged(const bool highlighted) const;

public slots:
    void setText(const QString &text, const bool expand = false);
    void setHighlighted(const bool highlighted);

protected:
    void init() override;
    QString drawPixel(const QPoint &pixel) const override;

    int reservedCharactersCount() const;
    QString reservedText() const;
    void setReservedText(const QString &reserved);

private slots:
    void layoutText();

private:
    struct TextLayout {
        QStringList text;
        SizeOvershoot overshoot = Overshoot::None;
    };

    TextLayout generateTextLayout(const QSize &size, const QString &text) const;

    bool _highlighted = false;
    Text::Wrap _wrapMode = Text::Wrap::Words;

    QString _text;
    QString _reservedText;
    QStringList _laidOutTextCache;
};
}
