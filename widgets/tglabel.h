#pragma once

#include <widgets/tgwidget.h>

namespace Tg {
class Label : public Tg::Widget
{
    Q_OBJECT

    Q_PROPERTY(QString text READ text WRITE setText NOTIFY textChanged)

public:
    Label(const QString &text = QString(), Tg::Widget *parent = nullptr);
    Label(const QString &text = QString(), Tg::Screen *screen = nullptr);

    QString text() const;

    QString drawPixel(const QPoint &pixel) const override;

signals:
    void textChanged(const QString &text) const;

public slots:
    void setText(const QString &text);

private:
    void init();

    QString _text;
};
}
