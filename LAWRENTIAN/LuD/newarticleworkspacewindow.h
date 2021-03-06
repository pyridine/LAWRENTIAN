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

    void init(LoginCredentials* login = new LoginCredentials(), articleWorkspace *myParent = 0);
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

    void on_delete_pushButton_clicked();

    void on_issueDateEdit_userDateChanged(const QDate &date);

    void on_setCurrentIssueButton_clicked();

private:
    void handlePermissions();
    typedef QVector<QCheckBox*> cb_vec_t;

    void updateWriterList(int section, int currentWriter);
    void updatePhotographerList(int currentPhotographer);
    void setupSectionComboBox(int section);
    void closeMe(); //closes window, updates parent.
    void updatePhotoDB(); //This should only be called upon "submit"!!

    int getSelectedWriterLuid();
    int getSelectedPhotographerLuid();
    int getSelectedSectionID();
    int getSelectedSectionPermissionToken();

    NewArticleWorkspaceWindowDBC* dbController;

    LoginCredentials* loginCred;
    Article* myArticle;
    Ui::newArticleWorkspaceWindow *ui;
    cb_vec_t cb_vec;
    QStringList img_paths;
    QVBoxLayout *vert_layout;
    string getfName(QString str);
    std::string getNameColon(const std::string& s);
    //What are these for?
    std::string COPY;
    std::string IMAGE;
    //Used to display section names in combobox.
    std::string NEWZ;
    std::string FEATZ;
    std::string OPEDZ;
    std::string ARTSENTZ;
    std::string VARIEZ;
    std::string SPORTZ;

    articleWorkspace *parentArticleWorkspaceWidget;
};

#endif // NEWARTICLEWORKSPACEWINDOW_H
