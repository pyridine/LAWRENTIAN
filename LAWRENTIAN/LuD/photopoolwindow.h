#ifndef PHOTOPOOLWINDOW_H
#define PHOTOPOOLWINDOW_H

#include <QDialog>
#include "photopoolwindowdbc.h"
#include "logincredentials.h"
#include "client.h"
#include <QListWidgetItem>
#include <QGraphicsScene>
#include <QDir>
#include <QPointF>
#include "gitem.h"

namespace Ui {
class PhotoPoolWindow;
}

class PhotoPoolWindow : public GItem
{
    Q_OBJECT

public:
    explicit PhotoPoolWindow(QGraphicsPixmapItem *parent = 0);
    ~PhotoPoolWindow();
    void init(Client *c);

private slots:
    void on_section_comboBox_currentIndexChanged(int index);

    void on_fromIssueDate_comboBox_activated(int index);

    void on_toIssueDate_comboBox_activated(int index);

    void on_allArt_pushButton_clicked();

    void on_article_listWidget_itemDoubleClicked(QListWidgetItem *item);

    virtual void hoverEnterEvent(QGraphicsSceneHoverEvent *e);
    virtual void hoverLeaveEvent(QGraphicsSceneHoverEvent *e);

    void doubleClickImg(QGraphicsSceneMouseEvent* e);

private:
    Ui::PhotoPoolWindow *ui;
    PhotoPoolWindowDBC *dbController;
    QGraphicsScene* scene;
    QDir temp_dir;
    QGraphicsView *tView;
    QGraphicsScene *tScene;

    void drawArtsOnListView();
    void drawImages(const std::string& issueDate, const std::string& section, const std::string& title);
    QPointF addImage(const std::string& fNameExt, const QPointF pos, int xWidth, int yHeight, int xGap, int yGap);
    void initializeTransfer();
};

#endif // PHOTOPOOLWINDOW_H
