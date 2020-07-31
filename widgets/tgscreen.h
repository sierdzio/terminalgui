#pragma once

#include <QObject>
#include <QTimer>
#include <QSize>

class TgScreen : public QObject
{
    Q_OBJECT

    Q_PROPERTY(QSize size READ size NOTIFY sizeChanged)

public:
    TgScreen(QObject *parent = nullptr);
    ~TgScreen();

    void waitForQuit();

    QSize size() const;

signals:
    void end() const;
    void sizeChanged(const QSize &size) const;

private slots:
    void checkIfQuit();

private:
    QTimer _timer;
    QSize _size;
};

