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

namespace Ui {
class PhotoPoolWindow;
}

class PhotoPoolWindow : public QDialog
{
    Q_OBJECT

public:
    explicit PhotoPoolWindow(QWidget *parent = 0);
    ~PhotoPoolWindow();
    void init(Client *c);

private slots:
    void on_section_comboBox_currentIndexChanged(int index);

    void on_fromIssueDate_comboBox_activated(int index);

    void on_toIssueDate_comboBox_activated(int index);

    void on_allArt_pushButton_clicked();

    void on_article_listWidget_itemDoubleClicked(QListWidgetItem *item);

private:
    Ui::PhotoPoolWindow *ui;
    PhotoPoolWindowDBC *dbController;
    QGraphicsScene* scene;
    QDir temp_dir;

    void drawArtsOnListView();
    void drawImages(const std::string& issueDate, const std::string& section, const std::string& title);
    QPointF addImage(const std::string& fNameExt, const QPointF pos);
    void initializeTransfer();
};

#endif // PHOTOPOOLWINDOW_H
