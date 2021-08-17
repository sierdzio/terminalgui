#pragma once

#include <QString>
#include <QList>

class Item
{
public:
    Item(const QString &title, Item *parent = nullptr);

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

    bool isList() const override;
    bool isAction() const override;

    Items items() const;

private:
    Items _items;
};

class ActionItem : public Item
{
    ActionItem(const QString &title, Item *parent = nullptr);

    virtual bool trigger();

    bool isList() const override;
    bool isAction() const override;
};
