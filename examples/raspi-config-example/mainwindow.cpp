#include "mainwindow.h"

#include <widgets/tgbutton.h>
#include <widgets/tglistview.h>

#include <QCoreApplication>
#include <QStringListModel>

MainWindow::MainWindow(Tg::Screen *screen) : Tg::Widget(screen)
{
    setTitle(QObject::tr("Raspberry Pi Configuration Tool (raspi-config-tg)"));
    setLayoutType(Tg::Layout::Type::Column);
    setBackgroundColor(Tg::Color::Predefined::Gray);

    _listView = new Tg::ListView(this);
    _listView->setModel(new QStringListModel(_mainMenuLabels.values(), _listView));
    _listView->setSize(QSize(1, 6));
    _listView->show();

    _spacer = new Tg::Widget(this);
    _spacer->setBackgroundColor(Tg::Color::Predefined::Gray);
    _spacer->show();

    _finishButton = new Tg::Button(tr("Finish"), this);
    _finishButton->setTextColor(Tg::Color::Predefined::White);
    _finishButton->setBackgroundColor(Tg::Color::Predefined::Black);
    _finishButton->setSize(QSize(6, 1));
    _finishButton->show();

    CHECK(connect(_finishButton, &Tg::Button::clicked,
                  QCoreApplication::instance(), &QCoreApplication::quit));
    CHECK(connect(_listView, &Tg::ListView::indexPressed,
                  this, &MainWindow::onIndexPressed));
    CHECK(connect(this, &MainWindow::sizeChanged,
                  this, &MainWindow::updateSpacerHeight));

    updateSpacerHeight();
    show();
}

void MainWindow::updateSpacerHeight()
{
    _spacer->setSize(QSize(size().width(), spacerHeight()));
}

void MainWindow::onIndexPressed(const QModelIndex &index)
{
    if (index.isValid() == false) {
        return;
    }

    const int row = index.row();
    if (_currentMenuItem == MenuItem::Root) {

    }
}

int MainWindow::spacerHeight() const
{
    return size().height() - 2 - _listView->size().height() - _finishButton->size().height();
}
