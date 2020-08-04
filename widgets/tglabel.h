#pragma once

#include <widgets/tgwidget.h>

namespace Tg {
class Label : public Tg::Widget
{
    Q_OBJECT

    Q_PROPERTY(QString text READ text WRITE setText NOTIFY textChanged)

public:
    Label(const QString &text = QString(), QObject *parent = nullptr);

    QString text() const;

public slots:
    void setText(const QString &text);

signals:
    void textChanged(const QString &text) const;

protected:
    void draw() override;

private:
    QString _text;
};
}
