#include "idea.h"

idea::idea()
{

}

idea::~idea()
{

}

string idea::getTitle()
{
    return idea::title;
}

void idea::setTitle(string title)
{
    idea::title = title;
}

string idea::getDescription()
{
    return idea::description;
}

void idea::setDescription(string description)
{
    idea::description = description;
}

string idea::getExpirationDate()
{
    return idea::expirationDate;
}

void idea::setExpirationDate(string expirationDate)
{
    idea::expirationDate = expirationDate;
}

string idea::getSection()
{
    return idea::section;
}

void idea::setSection(string section)
{
    idea::section = section;
}

