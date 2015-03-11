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
    string makeDiff(string a, string b,string DEL,string ADD);
    void doExample();
};

#endif // DIFF_H
