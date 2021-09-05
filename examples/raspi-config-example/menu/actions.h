#pragma once

#include <menus/actionmenuitem.h>

namespace Tg {
class Widget;
class ListMenuItem;
}

class AboutItem : public Tg::ActionMenuItem
{
public:
    AboutItem(Tg::ListMenuItem *parent = nullptr);
    bool trigger(Tg::Widget *displayWidget) const override;
};

class UpdateItem : public Tg::ActionMenuItem
{
public:
    UpdateItem(Tg::ListMenuItem *parent = nullptr);
    bool trigger(Tg::Widget *displayWidget) const override;
};

class ProcessTestItem : public Tg::ActionMenuItem
{
public:
    ProcessTestItem(Tg::ListMenuItem *parent = nullptr);
    bool trigger(Tg::Widget *displayWidget) const override;
};
