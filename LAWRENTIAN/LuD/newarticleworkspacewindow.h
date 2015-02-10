#ifndef NEWARTICLEWORKSPACEWINDOW_H
#define NEWARTICLEWORKSPACEWINDOW_H

#include "article.h"
#include "articleworkspace.h"

#include <QDialog>

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

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

private:
    Ui::newArticleWorkspaceWindow *ui;
    Article *newArticle;
    articleWorkspace *parentArticleWorkspaceWidget;

};

#endif // NEWARTICLEWORKSPACEWINDOW_H
