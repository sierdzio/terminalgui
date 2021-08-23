#include "item.h"

#include <tgscreen.h>
#include <widgets/tgpopup.h>
#include <widgets/tglabel.h>
#include <widgets/tgbutton.h>

#include <QObject>
#include <QProcess>

#include <QDebug>

Item::Item(const QString &title, Item *parent) : _title(title), _parent(parent)
{
}

Item::~Item()
{
}

Item *Item::parent() const
{
    return _parent;
}

bool Item::hasParent() const
{
    return _parent != nullptr;
}

QString Item::title() const
{
    return _title;
}

bool Item::isList() const
{
    return false;
}

bool Item::isAction() const
{
    return false;
}

void Item::setParent(Item *item)
{
    _parent = item;
}

ListItem::ListItem(const QString &title, Item *parent)
    : Item(title, parent)
{
}

ListItem::ListItem(const QString &title, const Items &children, Item *parent)
    : Item(title, parent), _items(children)
{
    for (Item *item : qAsConst(_items)) {
        item->setParent(this);
    }
}

ListItem::~ListItem()
{
    qDeleteAll(_items);
}

bool ListItem::isList() const
{
    return true;
}

bool ListItem::isAction() const
{
    return false;
}

Items ListItem::items() const
{
    return _items;
}

QStringList ListItem::listTitles() const
{
    QStringList result;

    for (auto item : qAsConst(_items)) {
        result.append(item->title());
    }

    return result;
}

void ListItem::addItem(Item *item)
{
    // TODO: check for duplicates!
    _items.append(item);
}

ActionItem::ActionItem(const QString &title, ListItem *parent)
    : Item(title, parent)
{
    if (parent) {
        parent->addItem(this);
    }
}

ActionItem::~ActionItem()
{
}

bool ActionItem::trigger(Tg::Widget *displayWidget) const
{
    qDebug() << "Base ActionItem::trigger()" << displayWidget;

    return true;
}

bool ActionItem::isList() const
{
    return false;
}

bool ActionItem::isAction() const
{
    return true;
}

void ActionItem::showPopup(Tg::Widget *parent, const QString &message) const
{
    auto *popup = new Tg::Popup(QSize(55, 9), parent->screen());
    popup->setLayoutType(Tg::Layout::Type::Column);
    auto label = new Tg::Label(message, popup);
    label->setSize(QSize(53, 6));
    auto ok = new Tg::Button(QObject::tr("OK"), popup);
    popup->show();
    ok->setActiveFocus();

    CHECK(QObject::connect(ok, &Tg::Button::clicked,
                           popup, &Tg::Widget::hide));
    CHECK(QObject::connect(ok, &Tg::Button::clicked,
                           popup, &Tg::Widget::deleteLater));
}

void ActionItem::runProcess(Tg::Widget *parent, const QString &question, const QString &program, const QStringList &arguments) const
{
    const auto isConfirmed = "isConfirmed";

    auto process = new QProcess;
    process->setProgram(program);
    process->setArguments(arguments);
    process->setWorkingDirectory("/");
    process->setProperty(isConfirmed, false);

    auto *popup = new Tg::Popup(parent->size(), parent->screen());
    popup->setLayoutType(Tg::Layout::Type::Column);
    auto label = new Tg::Label(question, popup);
    label->setSize(QSize(popup->size().width() - 2, popup->size().height() - 4));
    auto ok = new Tg::Button(QObject::tr("OK"), popup);
    auto cancel = new Tg::Button(QObject::tr("Cancel"), popup);

    auto onReadyReadError = [=]() {
        label->setText(label->text() + "\n" + process->readAllStandardError());
    };

    auto onReadyReadOutput = [=]() {
        label->setText(label->text() + "\n" + process->readAllStandardOutput());
    };

    auto onOk = [=]() {
        if (process->property(isConfirmed).toBool()) {
            if (process->state() == QProcess::ProcessState::NotRunning) {
                popup->hide();
                popup->deleteLater();
                process->deleteLater();
                return;
            } else {
                return;
            }
        }

        process->setProperty(isConfirmed, true);
        label->clear();
        process->start();
    };

    CHECK(QObject::connect(ok, &Tg::Button::clicked,
                           popup, onOk));

    CHECK(QObject::connect(cancel, &Tg::Button::clicked,
                           popup, &Tg::Widget::hide));
    CHECK(QObject::connect(cancel, &Tg::Button::clicked,
                           popup, &Tg::Widget::deleteLater));
    CHECK(QObject::connect(cancel, &Tg::Button::clicked,
                           process, &QProcess::deleteLater));

    CHECK(QObject::connect(process, &QProcess::readyReadStandardError,
                           label, onReadyReadError));
    CHECK(QObject::connect(process, &QProcess::readyReadStandardOutput,
                           label, onReadyReadOutput));

    popup->show();
    ok->setActiveFocus();
}
