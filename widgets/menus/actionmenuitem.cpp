#include "actionmenuitem.h"
#include "listmenuitem.h"

#include <widgets/tgpopup.h>
#include <widgets/tglabel.h>
#include <widgets/tgbutton.h>
#include <widgets/tgscrollarea.h>

#include <QObject>
#include <QProcess>

#include <QDebug>

Tg::ActionMenuItem::ActionMenuItem(const QString &title, ListMenuItem *parent)
    : MenuItem(title, parent)
{
    if (parent) {
        parent->addItem(this);
    }
}

Tg::ActionMenuItem::~ActionMenuItem()
{
}

bool Tg::ActionMenuItem::trigger(Tg::Widget *displayWidget) const
{
    qDebug() << "Base ActionItem::trigger()" << displayWidget;

    return true;
}

bool Tg::ActionMenuItem::isList() const
{
    return false;
}

bool Tg::ActionMenuItem::isAction() const
{
    return true;
}

void Tg::ActionMenuItem::showPopup(Tg::Widget *parent,
                                   const QString &message) const
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

void Tg::ActionMenuItem::runProcess(Tg::Widget *parent, const QString &question,
                                    const QString &program,
                                    const QStringList &arguments) const
{
    const auto isConfirmed = "isConfirmed";

    auto process = new QProcess;
    process->setProgram(program);
    process->setArguments(arguments);
    process->setWorkingDirectory("/");
    process->setProperty(isConfirmed, false);

    auto *popup = new Tg::Popup(parent->size(), parent->screen());
    popup->setLayoutType(Tg::Layout::Type::Column);

    auto scrollArea = new Tg::ScrollArea(popup);
    scrollArea->setSize(QSize(popup->size().width() - 2,
                              popup->size().height() - 4));

    auto label = new Tg::Label(question, scrollArea);
    label->setSize(QSize(scrollArea->size().width(), scrollArea->size().height()));

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

void Tg::ActionMenuItem::runScript(Tg::Widget *parent, const QString &question,
                                   const QString &script) const
{
    runProcess(parent, question, "/bin/bash", { "-c", script });
}
