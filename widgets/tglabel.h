#pragma once

#include <widgets/tgwidget.h>

class TgLabel : public TgWidget
{
    Q_OBJECT

    Q_PROPERTY(QString text READ text WRITE setText NOTIFY textChanged)

public:
    TgLabel(const QString &text = QString(), QObject *parent = nullptr);

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

