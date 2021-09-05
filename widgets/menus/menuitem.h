#pragma once

#include <QList>
#include <QString>

namespace Tg {
class Widget;

class MenuItem
{
public:
    MenuItem(const QString &title, MenuItem *parent = nullptr);
    virtual ~MenuItem();

    MenuItem *parent() const;
    bool hasParent() const;

    QString title() const;

    virtual bool isList() const;
    virtual bool isAction() const;

    friend class ListMenuItem;

protected:
    void setParent(MenuItem *item);

private:
    const QString _title;
    MenuItem *_parent = nullptr;
};

using Items = QList<MenuItem*>;
}
