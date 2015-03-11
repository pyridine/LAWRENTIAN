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
    void doExample();
private:
    static string makeHTMLDiff_Line(string newS, string oldS);
};

#endif // DIFF_H
