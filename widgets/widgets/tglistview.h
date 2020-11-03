#pragma once

#include <widgets/tgscrollarea.h>

#include <QPointer>

class QAbstractItemModel;

namespace Tg {
class ListView : public ScrollArea
{
    Q_OBJECT

public:
    ListView(Widget *parent);
    ListView(Screen *screen);

    QAbstractItemModel *model() const;
    void setModel(QAbstractItemModel *model);

protected:
    void init() override;
    void consumeKeyboardBuffer(const QString &keyboardBuffer) override;

private:
    QPointer<QAbstractItemModel> _model;
};
}
