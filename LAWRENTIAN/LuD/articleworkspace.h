#ifndef ARTICLEWORKSPACE_H
#define ARTICLEWORKSPACE_H

#include "article.h"

#include <QWidget>
#include <QString>
#include <string>

using namespace std;

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
    int x;
    int y;

    Article *getNewArticle() const;
    void setNewArticle(Article *value);
    bool workspaceExists(string articleTitle);

private slots:
    void on_pushButton_clicked();
    void handleButton();

private:
    Ui::articleWorkspace *ui;
    vector<Article *> articleVector;
};

#endif // ARTICLEWORKSPACE_H
