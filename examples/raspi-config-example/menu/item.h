#pragma once

#include <QString>
#include <QList>

class Item
{
public:
    Item(const QString &title, Item *parent = nullptr);
    virtual ~Item();

    Item *parent() const;

    virtual bool isList() const;
    virtual bool isAction() const;

private:
    const QString _title;
    Item *_parent = nullptr;
};

using Items = QList<Item*>;

class ListItem : public Item
{
    ListItem(const QString &title, Item *parent = nullptr);
    virtual ~ListItem();

    bool isList() const override;
    bool isAction() const override;

    Items items() const;

    friend class ActionItem;

protected:
    void addItem(Item *item);

private:
    Items _items;
};

class ActionItem : public Item
{
    ActionItem(const QString &title, ListItem *parent = nullptr);
    virtual ~ActionItem();

    virtual bool trigger();

    bool isList() const override;
    bool isAction() const override;
};
