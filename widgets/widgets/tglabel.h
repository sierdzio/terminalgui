#pragma once

#include <widgets/tgwidget.h>

namespace Tg {
class Label : public Widget
{
    Q_OBJECT

    Q_PROPERTY(QString text READ text WRITE setText NOTIFY textChanged)

public:
    Label(Widget *parent);
    Label(Screen *screen);
    Label(const QString &text = QString(), Widget *parent = nullptr);
    Label(const QString &text = QString(), Screen *screen = nullptr);

    QString text() const;

    std::string drawPixel(const QPoint &pixel) const override;

signals:
    void textChanged(const QString &text) const;

public slots:
    void setText(const QString &text, const bool expand = true);

protected:
    void init() override;

    int reservedCharactersCount() const;
    void setReservedCharactersCount(int reservedCharactersCount);
    virtual QChar reservedCharacter(const int index) const;

private slots:
    void layoutText();

private:
    // How many chars are reserved by widget to draw special controls
    // (like checkbox or radio button control)
    int _reservedCharactersCount = 0;
    QString _text;
    QStringList _laidOutTextCache;
};
}
