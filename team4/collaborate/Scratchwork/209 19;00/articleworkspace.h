#ifndef ARTICLEWORKSPACE_H
#define ARTICLEWORKSPACE_H

#include "article.h"

#include <QWidget>

namespace Ui {
class articleWorkspace;
}

class articleWorkspace : public QWidget
{
    Q_OBJECT

public:
    explicit articleWorkspace(QWidget *parent = 0);
    ~articleWorkspace();
    void initArticle(Article *article);
    void addArticleButton(Article *article);

    Article *getNewArticle() const;
    void setNewArticle(Article *value);

private slots:
    void on_pushButton_clicked();

private:
    Ui::articleWorkspace *ui;
    Article *newArticle;
};

#endif // ARTICLEWORKSPACE_H
