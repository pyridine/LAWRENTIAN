#include "gitem.h"


GItem::GItem(QGraphicsPixmapItem *parent) : QDialog(), QGraphicsPixmapItem(parent)
{
    setAcceptHoverEvents(true);

}

GItem::GItem(const QPixmap & pixmap, QGraphicsPixmapItem *parent): QDialog(),
    QGraphicsPixmapItem(pixmap, parent)
{
    setAcceptHoverEvents(true);

}

GItem::~GItem()
{

}
