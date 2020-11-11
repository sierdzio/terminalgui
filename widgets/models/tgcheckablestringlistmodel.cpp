#include "tgcheckablestringlistmodel.h"

Tg::CheckableStringListModel::CheckableStringListModel(
        const QStringList &data, QObject *parent)
    : QAbstractListModel(parent)
{
    for (const QString &string : data) {
        _data.append({ Qt::CheckState::Unchecked, string,
                       Tg::Color::Predefined::Yellow });
    }
}

Tg::CheckableStringListModel::CheckableStringListModel(
        const CheckableStringList &data, QObject *parent)
    : QAbstractListModel(parent), _data(data)
{
}

Qt::ItemFlags Tg::CheckableStringListModel::flags(const QModelIndex &index) const
{
    if (index.isValid() == false) {
        return Qt::ItemFlag::NoItemFlags;
    }

    return Qt::ItemFlag::ItemIsSelectable
            | Qt::ItemFlag::ItemIsEnabled
            | Qt::ItemFlag::ItemIsUserCheckable
            | Qt::ItemFlag::ItemNeverHasChildren;
}

int Tg::CheckableStringListModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent)
    return _data.length();
}

QVariant Tg::CheckableStringListModel::data(const QModelIndex &index, int role) const
{
    if (index.isValid() == false) {
        return {};
    }

    const int row = index.row();
    if (row < 0 || row >= _data.size()) {
        return {};
    }

    switch (role) {
    case Qt::ItemDataRole::CheckStateRole:
        return bool(_data.at(row).checkState);
    case Qt::ItemDataRole::DecorationRole:
    {
        const CheckableString &data = _data.at(row);
        if (data.color.isEmpty()) {
            return {};
        } else {
            return QVariant::fromValue<Tg::Color>(data.color);
        }
    }
        break;
    case Qt::ItemDataRole::DisplayRole:
        return _data.at(row).string;
    }

    return {};
}

bool Tg::CheckableStringListModel::setData(const QModelIndex &index,
                                           const QVariant &value,
                                           int role)
{
    if (index.isValid() == false) {
        return false;
    }

    const int row = index.row();
    if (row < 0 || row >= _data.size()) {
        return false;
    }

    switch (role) {
    case Qt::ItemDataRole::EditRole:
    {
        CheckableString data = _data.at(row);
        data.string = value.toString();
        _data.replace(row, data);
        emit dataChanged(index, index, { role });
    }
        break;
    case Qt::ItemDataRole::DecorationRole:
    {
        CheckableString data = _data.at(row);
        data.color = value.value<Color>();
        _data.replace(row, data);
        emit dataChanged(index, index, { role });
    }
        break;
    case Qt::ItemDataRole::CheckStateRole:
    {
        CheckableString data = _data.at(row);
        bool ok = false;
        const Qt::CheckState valueState = Qt::CheckState(value.toInt(&ok));

        if (ok == false) {
            return false;
        }

        data.checkState = valueState == Qt::CheckState::PartiallyChecked?
                    Qt::CheckState::Checked : valueState;
        _data.replace(row, data);
        emit dataChanged(index, index, { role });
    }
        break;
    }

    return false;
}
