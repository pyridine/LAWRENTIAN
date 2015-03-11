#ifndef DOCXTOSTRING_H
#define DOCXTOSTRING_H
#include <string>
#include <sstream>
#include <iostream>

using namespace std;

class DocxmlToString
{
public:
    static string parse(string absoluteDirectory);
    static string unzipDocx(string dir,string docxname); //Returns the full directory of document.xml
private:
    static string fileToText(string dir);
    static string parseDocXML(string xml);
};

#endif // DOCXTOSTRING_H
