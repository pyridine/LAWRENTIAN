#ifndef JDIFF_H
#define JDIFF_H

#include "diff_match_patch.h"
#include <string>
#include <iostream>
using namespace std;

class JDiff
{
public:
    JDiff();
    ~JDiff();
    static string makeDiff(string a, string b);
    string doExample();
private:
    static string insertBreaks(string diffHTML);
};

#endif // DIFF_H
