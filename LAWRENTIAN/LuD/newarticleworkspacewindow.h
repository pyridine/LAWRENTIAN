#ifndef NEWARTICLEWORKSPACEWINDOW_H
#define NEWARTICLEWORKSPACEWINDOW_H

#include "article.h"
#include "articleworkspace.h"
#include "newarticleworkspacewindowdbc.h"
#include "client.h"

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
    void setupFields();

    void initDB(Client* c);

private slots:
    void on_chooseFile_pushButton_clicked();

    void on_submit_pushButton_clicked();

    void on_addImage_pushButton_clicked();

    void on_delete_pushButton_pressed();

    void on_copyHistory_pushButton_clicked();

    void on_sectionComboBox_currentIndexChanged(const QString &arg1);

private:
    typedef QVector<QCheckBox*> cb_vec_t;

    Article *newArticle;
    Ui::newArticleWorkspaceWindow *ui;
    articleWorkspace *parentArticleWorkspaceWidget;
    cb_vec_t cb_vec;
    QStringList img_paths;
    QVBoxLayout *vert_layout;
    QString getfName(QString str);

    void updateWriterList(int section);
    void updatePhotographerList();
    int getSelectedWriterLuid();

    NewArticleWorkspaceWindowDBC* dbController;

    vector<pair<string, int> *>* currentWriterList;
    vector<pair<string, int> *>* currentPhotographerList;
    std::string getNameColon(const std::string& s);
    std::string getNameExt(const std::string& s);
    std::string COPY;
    std::string IMAGE;
};

#endif // NEWARTICLEWORKSPACEWINDOW_H
