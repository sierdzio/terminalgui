#pragma once

#include <tgcolor.h>

#include <QAbstractListModel>

namespace Tg {
struct CheckableString {
    Qt::CheckState checkState = Qt::CheckState::Unchecked;
    QString string;
    Color color;
};

using CheckableStringList = QList<CheckableString>;

class CheckableStringListModel : public QAbstractListModel
{
    Q_OBJECT

public:
    CheckableStringListModel(const QStringList &data, QObject *parent = nullptr);
    CheckableStringListModel(const CheckableStringList &data, QObject *parent = nullptr);

    Qt::ItemFlags flags(const QModelIndex &index) const override;
    int rowCount(const QModelIndex &parent) const override;
    QVariant data(const QModelIndex &index, int role) const override;
    bool setData(const QModelIndex &index, const QVariant &value, int role) override;

private:
    CheckableStringList _data;
};
}
