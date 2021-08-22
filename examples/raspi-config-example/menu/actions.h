#pragma once

#include "item.h"

class AboutItem : public ActionItem
{
public:
    AboutItem(ListItem *parent = nullptr);
    bool trigger(Tg::Widget *displayWidget) const override;
};

class UpdateItem : public ActionItem
{
public:
    UpdateItem(ListItem *parent = nullptr);
    bool trigger(Tg::Widget *displayWidget) const override;
};
