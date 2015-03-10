#ifndef DOCXTOSTRING_H
#define DOCXTOSTRING_H
#include <string>
#include <sstream>
#include <iostream>

using namespace std;

class DocxmlToString
{
public:
    DocxmlToString();
    ~DocxmlToString();

    static string parse(string absoluteDirectory);
private:
    static string fileToText(string dir);
    static string parseDocXML(string xml);
};

#endif // DOCXTOSTRING_H
