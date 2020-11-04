#pragma once

#include <widgets/tgscrollarea.h>

#include <QPointer>

class QAbstractItemModel;

namespace Tg {
class ListView : public ScrollArea
{
    Q_OBJECT

    Q_PROPERTY(bool wrapRows READ wrapRows WRITE setWrapRows NOTIFY wrapRowsChanged)

public:
    ListView(Widget *parent);
    ListView(Screen *screen);

    QString drawAreaContents(const QPoint &pixel) const override;

    QAbstractItemModel *model() const;
    void setModel(QAbstractItemModel *model);

    bool wrapRows() const;

public slots:
    void setWrapRows(const bool wrapRows);

signals:
    void wrapRowsChanged(const bool wrapRows) const;

protected:
    void init() override;
    void consumeKeyboardBuffer(const QString &keyboardBuffer) override;

private:
    QPointer<QAbstractItemModel> _model;
    bool _wrapRows = false;
};
}
