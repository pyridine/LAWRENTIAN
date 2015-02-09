#include "editortimesheet.h"

editorTimesheet::editorTimesheet()
{

}

editorTimesheet::~editorTimesheet()
{

}
int editorTimesheet::getEditorId() const
{
    return editorId;
}

void editorTimesheet::setEditorId(int editorId)
{
    editorTimesheet::editorId = editorId;
}
int editorTimesheet::getHours() const
{
    return hours;
}

void editorTimesheet::setHours(int hours)
{
    editorTimesheet::hours = hours;
}



