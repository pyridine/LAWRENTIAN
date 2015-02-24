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

    void on_copyHistory_pushButton_clicked();

private:
    typedef QVector<QCheckBox*> cb_vec_t;

    Article *newArticle;
    Ui::newArticleWorkspaceWindow *ui;
    articleWorkspace *parentArticleWorkspaceWidget;
    cb_vec_t cb_vec;
    QStringList img_paths;
    QVBoxLayout *vert_layout;
    QString getfName(QString str);
    std::string getNameExt(const std::string& s);
    std::string COPY;
    std::string IMAGE;
};

#endif // NEWARTICLEWORKSPACEWINDOW_H
