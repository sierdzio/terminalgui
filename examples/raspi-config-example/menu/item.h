#pragma once

#include <QList>
#include <QString>
#include <QStringList>

namespace Tg {
class Widget;
}

class Item
{
public:
    Item(const QString &title, Item *parent = nullptr);
    virtual ~Item();

    Item *parent() const;
    bool hasParent() const;

    QString title() const;

    virtual bool isList() const;
    virtual bool isAction() const;

    friend class ListItem;

protected:
    void setParent(Item *item);

private:
    const QString _title;
    Item *_parent = nullptr;
};

using Items = QList<Item*>;

class ListItem : public Item
{
public:
    ListItem(const QString &title, Item *parent = nullptr);
    ListItem(const QString &title, const Items &children, Item *parent = nullptr);
    virtual ~ListItem();

    bool isList() const override;
    bool isAction() const override;

    Items items() const;
    // Consider returning built-in, static QStringListModel!
    QStringList listTitles() const;

    friend class ActionItem;

protected:
    void addItem(Item *item);

private:
    Items _items;
};

class ActionItem : public Item
{
public:
    ActionItem(const QString &title, ListItem *parent = nullptr);
    virtual ~ActionItem();

    virtual bool trigger(Tg::Widget *displayWidget) const;

    bool isList() const override;
    bool isAction() const override;

protected:
    void showPopup(Tg::Widget *parent, const QString &message) const;
};
