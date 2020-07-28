#pragma once

#include "consolewidget.h"

#include <QObject>
#include <QTimer>

class ConsoleScreen : public ConsoleWidget
{
    Q_OBJECT

public:
    ConsoleScreen(QObject *parent = nullptr);
    ~ConsoleScreen();

    void show() override;

    void waitForQuit();

signals:
    void end() const;

private slots:
    void checkIfQuit();

private:
    QTimer _timer;
};

