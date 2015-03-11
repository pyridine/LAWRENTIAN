#ifndef QGITEM_H
#define QGITEM_H

#include <QDialog>
#include <QGraphicsPixmapItem>
#include <QPixmap>
#include <QHoverEvent>

class GItem : public QDialog, public QGraphicsPixmapItem
{
    Q_OBJECT
public:
    explicit GItem(QGraphicsPixmapItem *parent = 0);
    explicit GItem(const QPixmap& pixmap, QGraphicsPixmapItem *parent = 0);

    ~GItem();


protected: signals:
    void hoverEnterEvent(QGraphicsSceneHoverEvent * event);
    void hoverLeaveEvent(QGraphicsSceneHoverEvent * event);
    void mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event);
//public slots:
};

#endif // QGITEM_H
