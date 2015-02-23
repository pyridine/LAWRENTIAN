#ifndef NEWARTICLEWORKSPACEWINDOW_H
#define NEWARTICLEWORKSPACEWINDOW_H

#include "article.h"
#include "articleworkspace.h"

#include <QDialog>
#include <QVBoxLayout>
#include <QCheckBox>
#include <QVector>

namespace Ui {
class newArticleWorkspaceWindow;
}

class newArticleWorkspaceWindow : public QDialog
{
    Q_OBJECT

public:
    explicit newArticleWorkspaceWindow(QWidget *parent = 0);
    ~newArticleWorkspaceWindow();

    articleWorkspace *getParentArticleWorkspaceWidget() const;
    void setParentArticleWorkspaceWidget(articleWorkspace *value);
    void setupFields(Article *article);

private slots:
    void on_chooseFile_pushButton_clicked();

    void on_submit_pushButton_clicked();

    void on_addImage_pushButton_clicked();

    void on_delete_pushButton_pressed();

private:
    Article *newArticle;
    Ui::newArticleWorkspaceWindow *ui;
    articleWorkspace *parentArticleWorkspaceWidget;
    QVector<QCheckBox*> cb_vec;
    QStringList img_paths;
    QVBoxLayout *vert_layout;
    QString getfName(QString str);



};

#endif // NEWARTICLEWORKSPACEWINDOW_H
