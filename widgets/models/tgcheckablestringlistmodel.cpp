#include "tgcheckablestringlistmodel.h"

CheckableStringListModel::CheckableStringListModel(
        const QStringList &data, QObject *parent)
    : QAbstractListModel(parent)
{
    for (const QString &string : data) {
        _data.append({ Qt::CheckState::Unchecked, string });
    }
}

CheckableStringListModel::CheckableStringListModel(
        const CheckableStringList &data, QObject *parent)
    : QAbstractListModel(parent), _data(data)
{
}
