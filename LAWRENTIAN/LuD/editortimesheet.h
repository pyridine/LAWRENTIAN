#ifndef EDITORTIMESHEET_H
#define EDITORTIMESHEET_H


class editorTimesheet
{
public:
    editorTimesheet();
    ~editorTimesheet();

    int getEditorId() const;
    void setEditorId(int editorId);

    int getHours() const;
    void setHours(int hours);

private:
    int editorId;
    int hours;
};

#endif // EDITORTIMESHEET_H
