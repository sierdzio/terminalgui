#include "mainwindow.h"

#include <tgkey.h>

#include <widgets/tglabel.h>
#include <widgets/tgbutton.h>
#include <widgets/tglistview.h>
#include <widgets/tgpopup.h>

#include <QCoreApplication>
#include <QStringListModel>

MainWindow::MainWindow(Tg::Screen *screen) : Tg::Widget(screen)
{
    setAcceptsFocus(true);
    setTitle(QObject::tr("Raspberry Pi Configuration Tool (raspi-config-tg)"));
    setLayoutType(Tg::Layout::Type::Column);
    setBackgroundColor(Tg::Color::Predefined::Gray);

    _listView = new Tg::ListView(this);
    _listView->setModel(new QStringListModel(_mainMenuLabels.values(), _listView));
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

        switch (_currentMenuItem) {
        case MenuItem::Root:
            quit();
            break;
        case MenuItem::SystemOptions:
        case MenuItem::DisplayOptions:
        case MenuItem::InterfaceOptions:
        case MenuItem::PerformanceOptions:
        case MenuItem::LocalisationOptions:
        case MenuItem::AdvancedOptions:
            _listView->setModel(new QStringListModel(_mainMenuLabels.values(), _listView));
            _currentMenuItem = MenuItem::Root;
            break;
        case MenuItem::Update:
        case MenuItem::About:
            break;
        default:
            break;
        };

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

    const int row = index.row();
    if (_currentMenuItem == MenuItem::Root) {
        if (row >= _mainMenuLabels.size()) {
            return;
        }

        const MenuItem selected = MenuItem(int(_currentMenuItem) + row + 1);

        _currentMenuItem = selected;
        auto oldModel = _listView->model();

        switch (selected) {
        case MenuItem::SystemOptions:
            _listView->setModel(new QStringListModel(_systemOptionsLabels.values(), _listView));
            break;
        case MenuItem::DisplayOptions:
            _listView->setModel(new QStringListModel(_displayOptionsLabels.values(), _listView));
            break;
        case MenuItem::InterfaceOptions:
            _listView->setModel(new QStringListModel(_interfaceOptionsLabels.values(), _listView));
            break;
        case MenuItem::PerformanceOptions:
            _listView->setModel(new QStringListModel(_performanceOptionsLabels.values(), _listView));
            break;
        case MenuItem::LocalisationOptions:
            _listView->setModel(new QStringListModel(_localisationOptionsLabels.values(), _listView));
            break;
        case MenuItem::AdvancedOptions:
            _listView->setModel(new QStringListModel(_advancedOptionsLabels.values(), _listView));
            break;
        case MenuItem::Update:
            _currentMenuItem = MenuItem::Root;
            showPopup(tr("Update will be performed!"));
            emit update();
            break;
        case MenuItem::About:
            _currentMenuItem = MenuItem::Root;
            showPopup(_aboutText);
            break;
        default: return;
        }

        if (_listView->model() != oldModel) {
            oldModel->deleteLater();
        }
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

int MainWindow::spacerHeight() const
{
    return size().height() - 2 - _listView->size().height()
            - _finishButton->size().height();
}

void MainWindow::showPopup(const QString &message) const
{
    auto *popup = new Tg::Popup(QSize(55, 9), screen());
    popup->setLayoutType(Tg::Layout::Type::Column);
    auto label = new Tg::Label(message, popup);
    label->setSize(QSize(53, 6));
    auto ok = new Tg::Button(tr("OK"), popup);
    popup->show();
    ok->setActiveFocus();

    CHECK(connect(ok, &Tg::Button::clicked,
                  popup, &Tg::Widget::hide));
    CHECK(connect(ok, &Tg::Button::clicked,
                  popup, &Tg::Widget::deleteLater));
}

uint qHash(const MainWindow::MenuItem item)
{
    return qHash(int(item));
}
