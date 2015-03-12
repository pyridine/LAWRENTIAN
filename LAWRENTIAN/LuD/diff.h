#ifndef JDIFF_H
#define JDIFF_H

#include "diff_match_patch.h"
#include <string>
#include <iostream>
#include <utility>
#include <queue>
using namespace std;

class JDiff
{
public:
    JDiff();
    ~JDiff();
    static queue<string> *makeHTMLDiff_Q(queue<string> newSQ, queue<string> oldS);
    static string makeHTML(string s);
    void doExample();
    static std::queue<std::string>* splitStringToQueue(std::string s);

private:
    static string GET_HTML_LINE_HEADER();
    static string GET_HTML_LINE_ENDER();
    static string GET_HTML_DOC_HEADER();
    static string GET_HTML_DOC_ENDER();
    static string makeHTMLDiff_Line(string newS, string oldS);
};

#endif // DIFF_H
