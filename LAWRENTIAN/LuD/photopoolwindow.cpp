#include "photopoolwindow.h"
#include "ui_photopoolwindow.h"
#include "photopoolwindowdbc.h"
#include "Sender.h"
#include <iostream>
#include <QVariant>
#include <QListWidgetItem>
#include <QImage>
#include <QPixmap>
#include <QGraphicsScene>
#include <QGraphicsPixmapItem>
#include <QGraphicsItem>
#include "gitem.h"
#include <QtTest/QTest>
#include <QGraphicsSceneMouseEvent>

int WIDEST_EDGE_RES = 2500;

PhotoPoolWindow::PhotoPoolWindow(QGraphicsPixmapItem *parent) :
    GItem(parent),
    ui(new Ui::PhotoPoolWindow)
{ 
    ui->setupUi(this);
    temp_dir.setPath(QDir::currentPath() + QString::fromStdString("/temp"));
    scene = new QGraphicsScene;
    scene->setParent(this);
    ui->photoPool_graphicsView->setAlignment(Qt::AlignLeft | Qt::AlignTop);
    tView = new QGraphicsView;
    tScene = new QGraphicsScene;


}

PhotoPoolWindow::~PhotoPoolWindow()
{
    cout << "photopool destructor called" << endl;
    delete ui;
}

void PhotoPoolWindow::init(Client *c)
{
    using namespace std;

    dbController = new PhotoPoolWindowDBC(c);
    vector<PhotoPoolWindowDBC::Sec_t> all_sections = dbController->getSections();
    vector<PhotoPoolWindowDBC::Sec_t>::const_iterator iter = all_sections.begin();

    while(iter != all_sections.end())
    {
        int index = iter - all_sections.begin();
        QVariant secId(iter->first);
        QString secName(QString::fromStdString(iter->second));

        ui->section_comboBox->insertItem(index, secName);
        ui->section_comboBox->setItemData(index, secId);

        iter++;
    }

    QStringList allIssueDates = dbController->getIssueDates();
    ui->fromIssueDate_comboBox->addItems(allIssueDates);
    ui->toIssueDate_comboBox->addItems(allIssueDates);

    drawArtsOnListView();
}

void PhotoPoolWindow::on_section_comboBox_currentIndexChanged(int index)
{
    drawArtsOnListView();
}

void PhotoPoolWindow::on_fromIssueDate_comboBox_activated(int index)
{
    drawArtsOnListView();
}

void PhotoPoolWindow::on_toIssueDate_comboBox_activated(int index)
{
    drawArtsOnListView();
}



void PhotoPoolWindow::drawArtsOnListView()
{
    int secID = ui->section_comboBox->currentData().toInt();
    QString fromDate = ui->fromIssueDate_comboBox->currentText();
    QString toDate = ui->toIssueDate_comboBox->currentText();

    QStringList filteredArticles = dbController->getArtsFromSec(secID, fromDate, toDate);
    ui->article_listWidget->clear();
    ui->article_listWidget->addItems(filteredArticles);
}

void PhotoPoolWindow::drawImages(const string &issueDate, const string &section, const string &title)
{
    using namespace FileSystem;
    using namespace std;

    initializeTransfer();
    Sender sndr = Sender(0);
    StrSeq imgNames = sndr.getImageList(issueDate, section, title);

    StrSeq::const_iterator iter = imgNames.begin();
    QPointF pos = QPointF(15,1);

    while(iter != imgNames.end())
    {
        string fNameExt = *iter + fs::extIMAGE;
        string imgPath = temp_dir.path().toStdString() + "/" + fNameExt;
        sndr.requestImage(issueDate, section, title, *iter, imgPath);
        pos = addImage(imgPath, pos, 60, 60, 15, 15);
        iter++;
    }
//    iter = imgNames.begin();
//    while(iter != imgNames.end())
//    {
//        string fNameExt = *iter + fs::extIMAGE;
//        string imgPath = temp_dir.path().toStdString() + "/" + fNameExt;
//        pos = addImage(imgPath, pos);
//        iter++;
//    }
    ui->photoPool_graphicsView->setScene(scene);

//    ui->photoPool_graphicsView->fitInView(scene->itemsBoundingRect() ,Qt::KeepAspectRatio);
    cout << "done" << endl;

}

QPointF PhotoPoolWindow::addImage(const string& imgPath, const QPointF pos, int xWidth, int yHeight, int xGap, int yGap)
{
    using namespace std;

    QString img_path;
    QPixmap *pixmap = new QPixmap(img_path);
    GItem* pItem = new GItem;

    img_path = QString::fromStdString(imgPath);

    int count = 0;
    while(pixmap->isNull() && count < 10)
    {

        pixmap->load(img_path);
        count++;
    } // wait .3 secs for file download to complete.

    if(count >= 10)
        cout << "Loop limit exeeded." << endl;

    if(!pixmap->isNull())
    {
        cout << "Not null" << endl;

        pItem->setPixmap( pixmap->scaled(xWidth,yHeight));
        pItem->QGraphicsItem::update(0, 0, xWidth, yHeight);

        pItem->setData(0,QVariant(img_path));
        pItem->setPos(pos);

        pItem->setFlags(QGraphicsPixmapItem::ItemIsSelectable);
        pItem->QGraphicsItem::setCursor(Qt::PointingHandCursor);

        connect(pItem, SIGNAL(hoverEnterEvent(QGraphicsSceneHoverEvent*)), this, SLOT(hoverEnterEvent(QGraphicsSceneHoverEvent*)));
        connect(pItem, SIGNAL(hoverLeaveEvent(QGraphicsSceneHoverEvent*)), this, SLOT(hoverLeaveEvent(QGraphicsSceneHoverEvent*)));
        connect(pItem, SIGNAL(mouseDoubleClickEvent(QGraphicsSceneMouseEvent*)), this, SLOT(doubleClickImg(QGraphicsSceneMouseEvent*)));

        scene->addItem(pItem);

        int gv_width = ui->photoPool_graphicsView->width();

        int dx =  xWidth + xGap;
        int dy =  yHeight + yGap;

        int x = (pos.x() + dx) > gv_width ? xGap : pos.x() + dx;
        int y = (pos.x() + dx) > gv_width ? pos.y() + dy : pos.y();

        cout << "x " << x << "y " << y << endl;

        return QPointF(x,y);
    }
    cout << "Null, don't upload" << endl;
    return pos;
    //    QString img_path = QString::fromStdString(imgPath);

    //    QImage img = QImage(img_path);
    //    img.scaledToHeight(96);

    //    QGraphicsPixmapItem *pItem = new QGraphicsPixmapItem(QPixmap::fromImage(img));
    //    pItem->setData(0,QVariant(img_path));
    //    pItem->setPos(pos);
    //    scene->addItem(pItem->topLevelItem());
    //    int width = ui->photoPool_graphicsView->width();

    //    int x = (pos.x() + 84) > width ? 0 : width + 20;
    //    int y = (pos.x() + 84) > width ? y + 68 : y;

    //    return QPointF(x,y);
}

void PhotoPoolWindow::initializeTransfer()
{
    temp_dir.removeRecursively();
    temp_dir.mkdir(temp_dir.path());

    if(scene)
        scene->clear();
}

void PhotoPoolWindow::on_allArt_pushButton_clicked()
{
    int secID = ui->section_comboBox->currentData().toInt();
    QStringList allArts = dbController->getArtsFromSec(secID);

    ui->article_listWidget->clear();
    ui->article_listWidget->addItems(allArts);
}

void PhotoPoolWindow::on_article_listWidget_itemDoubleClicked(QListWidgetItem *item)
{
    using namespace std;

    string title = item->text().toStdString();
    string section = ui->section_comboBox->currentText().toStdString();
    QString QIssueDate = QString::fromStdString(dbController->getIssueDateOfArt(item->text()));
    string issueDate = QDate::fromString(QIssueDate,df::dbFormat).toString(df::srvrFormat).toStdString();

    drawImages(issueDate, section, title);

}


void PhotoPoolWindow::hoverEnterEvent(QGraphicsSceneHoverEvent *e)
{
    int w = 160 * 2/3;
    int h = 120 * 2/3;

    //using namespace std;
    QString path = ui->photoPool_graphicsView->itemAt(e->scenePos().toPoint())->data(0).toString();
    if(path.isEmpty())
        cout << "empty" << endl;
    if(path.isEmpty())
        path = ui->photoPool_graphicsView->itemAt(e->scenePos().toPoint() + QPoint(10,10))->data(0).toString();
    if(path.isEmpty())
        path = ui->photoPool_graphicsView->itemAt(e->scenePos().toPoint() + QPoint(-10,10))->data(0).toString();
    if(path.isEmpty())
        path = ui->photoPool_graphicsView->itemAt(e->scenePos().toPoint() + QPoint(10,-10))->data(0).toString();
    if(path.isEmpty())
        path = ui->photoPool_graphicsView->itemAt(e->scenePos().toPoint() + QPoint(-10,-10))->data(0).toString();


    cout << path.toStdString() << endl;
    QPixmap pixmap(path);

    pixmap = pixmap.scaledToWidth(w);
    if(pixmap.height() > h)
        pixmap = pixmap.scaledToHeight(h);

    tScene->clear();
    tScene->addPixmap(pixmap);

    tView->setScene(tScene);
    tView->adjustSize();
    tView->move(QCursor::pos() - QPoint(0,pixmap.height()));
    tView->show();
}

void PhotoPoolWindow::hoverLeaveEvent(QGraphicsSceneHoverEvent *e)
{
    using namespace std;
    tScene->clear();
    tView->close();
    cout << "left" << endl;
}

void PhotoPoolWindow::doubleClickImg(QGraphicsSceneMouseEvent *e)
{
    using namespace std;
    cout << ui->photoPool_graphicsView->itemAt(e->scenePos().toPoint())->data(0).toString().toStdString() << endl;
}

//void QGraphicsItem::hoverEnterEvent(QGraphicsSceneHoverEvent *event)
//{
//    cout << " hover" << endl;
//}
