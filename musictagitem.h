#ifndef MUSICTAGITEM_H
#define MUSICTAGITEM_H
#include <QList>


class MusicTagItem
{
public:
    explicit MusicTagItem(const QList<QVariant> &data, MusicTagItem *parentItem = 0);
    ~MusicTagItem();

    void appendChild(MusicTagItem *child);

    MusicTagItem *child(int row);
    int childCount() const;
    int columnCount() const;
    QVariant data(int column) const;
    int row() const;
    MusicTagItem *parentItem();

private:
    QList<MusicTagItem*> m_childItems;
    QList<QVariant> m_itemData;
    MusicTagItem *m_parentItem;
};

#endif // MUSICTAGITEM_H
