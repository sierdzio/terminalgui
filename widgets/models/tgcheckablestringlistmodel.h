#pragma once

#include <QAbstractListModel>

struct CheckableString {
    Qt::CheckState checkState;
    QString string;
};

using CheckableStringList = QList<CheckableString>;

class CheckableStringListModel : public QAbstractListModel
{
    Q_OBJECT

public:
    CheckableStringListModel(const QStringList &data, QObject *parent = nullptr);
    CheckableStringListModel(const CheckableStringList &data, QObject *parent = nullptr);

private:
    CheckableStringList _data;
};

