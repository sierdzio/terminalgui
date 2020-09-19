#pragma once

#include <widgets/tgwidget.h>

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

    QString drawPixel(const QPoint &pixel) const override;

    bool highlighted() const;

signals:
    void textChanged(const QString &text) const;    
    void highlightedChanged(const bool highlighted) const;

public slots:
    void setText(const QString &text, const bool expand = true);    
    void setHighlighted(const bool highlighted);

protected:
    void init() override;

    int reservedCharactersCount() const;
    QString reservedText() const;
    void setReservedText(const QString &reserved);

private slots:
    void layoutText();

private:
    bool _highlighted = false;

    QString _text;
    QString _reservedText;
    QStringList _laidOutTextCache;
};
}
