#include "mainwindow.h"

#include <tgkey.h>

#include <widgets/tglabel.h>
#include <widgets/tgbutton.h>
#include <widgets/tglistview.h>

#include <QCoreApplication>
#include <QStringListModel>

MainWindow::MainWindow(Tg::Screen *screen) : Tg::Widget(screen)
{
    setAcceptsFocus(true);
    setTitle(tr("Raspberry Pi Configuration Tool (raspi-config-tg)"));
    setLayoutType(Tg::Layout::Type::Column);
    setBackgroundColor(Tg::Color::Predefined::Gray);

    _listView = new Tg::ListView(this);
    _listView->setModel(new QStringListModel(currentMenu()->listTitles(), _listView));
    _listView->setSize(QSize(1, 6));
    _listView->setHorizontalScrollBarPolicy(Tg::ScrollArea::ScrollBarPolicy::NeverShow);
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
                  this, &MainWindow::quit));
    CHECK(connect(_listView, &Tg::ListView::indexPressed,
                  this, &MainWindow::onIndexPressed));
    CHECK(connect(this, &MainWindow::sizeChanged,
                  this, &MainWindow::updateSpacerHeight));

    updateSpacerHeight();
    show();
}

bool MainWindow::consumeKeyboardBuffer(const QString &keyboardBuffer)
{
    if (keyboardBuffer.contains('q') || keyboardBuffer == Tg::Key::escape) {
        auto oldModel = _listView->model();

        if (_currentMenuItem->hasParent()) {
            _currentMenuItem = _currentMenuItem->parent();
            _listView->setModel(new QStringListModel(currentMenu()->listTitles(), _listView));
        } else {
            quit();
        }

        if (_listView->model() != oldModel) {
            oldModel->deleteLater();
        }

        return true;
    }

    return false;
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

    auto oldModel = _listView->model();

    const int row = index.row();
    const Item *clicked = currentMenu()->items().at(row);

    if (clicked->isList()) {
        const ListItem *newMenu = static_cast<const ListItem *>(clicked);
        _currentMenuItem = newMenu;
        _listView->setModel(new QStringListModel(newMenu->listTitles(), _listView));
    } else if (clicked->isAction()) {
        const ActionItem *action = static_cast<const ActionItem *>(clicked);
        action->trigger(this);
    }

    if (_listView->model() != oldModel) {
        oldModel->deleteLater();
    }
}

void MainWindow::quit()
{
    if (_isDirty) {
        // ... popup with reboot question to user
        return;
    }

    QCoreApplication::instance()->quit();
}

const ListItem *MainWindow::currentMenu() const
{
    return static_cast<const ListItem*>(_currentMenuItem);
}

int MainWindow::spacerHeight() const
{
    return size().height() - 2 - _listView->size().height()
            - _finishButton->size().height();
}
