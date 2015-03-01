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
    void initDB(Client* c);
    void setupFields(Article *article);


private slots:
    void on_chooseFile_pushButton_clicked();

    void on_submit_pushButton_clicked();

    void on_addImage_pushButton_clicked();

    void on_delete_pushButton_pressed();

    void on_copyHistory_pushButton_clicked();

    void on_sectionComboBox_currentIndexChanged(const QString &arg1);

    void on_deleteAWS_pushButton_clicked();

private:
    typedef QVector<QCheckBox*> cb_vec_t;

    void updateWriterList(int section, int currentWriter);
    void updatePhotographerList(int currentPhotographer);
    void setupSectionComboBox(int section);
    void closeMe(); //closes window, updates parent.


    int getSelectedWriterLuid();
    int getSelectedPhotographerLuid();
    int getSelectedSectionID();
    int getSelectedSectionPermissionToken();

    NewArticleWorkspaceWindowDBC* dbController;


    Article* myArticle;
    Ui::newArticleWorkspaceWindow *ui;
    articleWorkspace *parentArticleWorkspaceWidget;
    cb_vec_t cb_vec;
    QStringList img_paths;
    QVBoxLayout *vert_layout;
    QString getfName(QString str);
    std::string getNameColon(const std::string& s);
    std::string getNameExt(const std::string& s);
    std::string getExt(const std::string& s);
    //Used to display section names in combobox.
    std::string NEWZ;
    std::string FEATZ;
    std::string OPEDZ;
    std::string ARTSENTZ;
    std::string VARIEZ;
    std::string SPORTZ;
};

#endif // NEWARTICLEWORKSPACEWINDOW_H
