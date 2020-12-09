#pragma once

#include <widgets/tgscrollarea.h>

#include <QPointer>
#include <QModelIndex>
#include <QAbstractItemModel>

namespace Tg {
class ListView : public ScrollArea
{
    Q_OBJECT

    Q_PROPERTY(bool wrapRows READ wrapRows WRITE setWrapRows NOTIFY wrapRowsChanged)
    Q_PROPERTY(bool alternatingRowColors READ alternatingRowColors WRITE setAlternatingRowColors NOTIFY alternatingRowColorsChanged)
    Q_PROPERTY(Tg::Color alternativeBackgroundColor READ alternativeBackgroundColor WRITE setAlternativeBackgroundColor NOTIFY alternativeBackgroundColorChanged)
    Q_PROPERTY(qsizetype currentIndex READ currentIndex WRITE setCurrentIndex NOTIFY currentIndexChanged)
    Q_PROPERTY(Tg::Color currentIndexColor READ currentIndexColor WRITE setCurrentIndexColor NOTIFY currentIndexColorChanged)
    Q_PROPERTY(QAbstractItemModel* model READ model WRITE setModel NOTIFY modelChanged)

public:
    ListView(Widget *parent);
    ListView(Screen *screen);

    QAbstractItemModel *model() const;
    void setModel(QAbstractItemModel *model);

    bool wrapRows() const;
    bool alternatingRowColors() const;
    Tg::Color alternativeBackgroundColor() const;

    qsizetype currentIndex() const;
    Tg::Color currentIndexColor() const;

public slots:
    void setWrapRows(const bool wrapRows);
    void setAlternatingRowColors(const bool alternatingRowColors);
    void setAlternativeBackgroundColor(const Tg::Color &alternativeBackgroundColor);
    void setCurrentIndex(const qsizetype currentIndex);
    void setCurrentIndexColor(const Tg::Color &currentIndexColor);

signals:
    void wrapRowsChanged(const bool wrapRows) const;
    void alternatingRowColorsChanged(const bool alternatingRowColors) const;
    void modelChanged(QAbstractItemModel* model) const;
    void alternativeBackgroundColorChanged(const Tg::Color &alternativeBackgroundColor) const;
    void currentIndexChanged(const qsizetype currentIndex) const;
    void currentIndexColorChanged(const Tg::Color &currentIndexColor) const;

protected:
    void init() override;
    void consumeKeyboardBuffer(const QString &keyboardBuffer) override;
    QString drawAreaContents(const QPoint &pixel) const override;

    QString getLine(const int row) const;
    QString getLine(const QModelIndex index) const;

protected slots:
    void updateChildrenDimensions() override;

private:
    QPointer<QAbstractItemModel> _model;
    bool _wrapRows = false;
    bool _alternatingRowColors = false;
    Tg::Color _alternativeBackgroundColor;
    Tg::Color _currentIndexColor;
    qsizetype _currentIndex = 0;
};
}
