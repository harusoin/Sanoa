#include "musictagitem.h"

MusicTagItem::MusicTagItem(const QList<QVariant> &data, MusicTagItem *parentItem)
{
    m_parentItem = parentItem;
    m_itemData = data;
}

MusicTagItem::~TreeItem()
{
    qDeleteAll(m_childItems);
}

void MusicTagItem::appendChild(MusicTagItem *child)
{
    m_childItems.append(child);
}

MusicTagItem *MusicTagItem::child(int row)
{
    return m_childItems.value(row);
}

int MusicTagItem::childCount() const
{
    return m_childItems.count();
}

int MusicTagItem::row() const
{
    if (m_parentItem)
        return m_parentItem->m_childItems.indexOf(const_cast<MusicTagItem*>(this));

    return 0;
}

int MusicTagItem::columnCount() const
{
    return m_itemData.count();
}

QVariant MusicTagItem::data(int column) const
{
    return m_itemData.value(column);
}

MusicTagItem *MusicTagItem::parentItem()
{
    return m_parentItem;
}
