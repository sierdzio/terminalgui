#include <QCoreApplication>
#include <QDebug>

#include <widgets/tgscreen.h>

int main(int argc, char *argv[])
{
    QCoreApplication app(argc, argv);

    TgScreen screen;

    qDebug() << "Terminal size is:" << screen.size().width()
             << screen.size().height();

    return app.exec();
}
