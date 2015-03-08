#include "diff.h"

JDiff::JDiff()
{

}

JDiff::~JDiff()
{

}

string JDiff::makeDiff(string a, string b,string DEL,string ADD){
    int mode_equal = 0;
    int mode_insert = 1;
    int mode_delete = 2;
    int mode = mode_equal;

    string diffResult = "";

    diff_match_patch<string> differ;
    diff_match_patch<string>::Diffs diffs =  differ.diff_main(a,b);
    diff_match_patch<string>::Diffs::iterator diffIt = diffs.begin();

    while(diffIt != diffs.end()){
        diff_match_patch<string>::Diff diff = *diffIt;
        switch(diff.operation){
        case(diff_match_patch<string>::D_Operation::D_DELETE):
            if(mode == mode_insert) diffResult += ADD;
            diffResult+=DEL;
            diffResult+=diff.text;
            mode = mode_delete;
            break;
        case(diff_match_patch<string>::D_Operation::D_INSERT):
            if(mode == mode_delete) diffResult += DEL;
            diffResult+=ADD;
            diffResult+=diff.text;
            mode = mode_insert;
            break;
        case(diff_match_patch<string>::D_Operation::D_EQUAL):
            if(mode == mode_insert) diffResult += ADD;
            if(mode == mode_delete) diffResult += DEL;
            diffResult+=diff.text;
            mode = mode_equal;
            break;
        }
        ++diffIt;
    }
    return diffResult;
}

void JDiff::doExample(){

    cout<<"Diffing Test:"<<endl;
    string a = "Once upon a time, there was a brook by a glorious castle.";
    cout << "string 1: "<<a<<endl;
    string b = "Once upon a midsummer night, there was a stoplight by an office building.";
    cout << "string 2: "<<b<<endl;
    cout << "Diff: "<<makeDiff(a,b,"|ADD|","|DEL|")<<endl;
    cout << "I am indebted to: Neil Fraser, Mike Slemmer, and Sergey Nozhenko, three gentlemen posessive of the utmost excellence in industry."<<endl;
}
