#include "diff.h"

JDiff::JDiff()
{

}

JDiff::~JDiff()
{

}

string JDiff::makeDiff(string a, string b){
    int mode_equal = 0;
    int mode_insert = 1;
    int mode_delete = 2;
    int mode = mode_equal;


     string DEL = "<font color='red'>";
     string NORMAL = "<font color='black'>";
     string ADD = "<font color='green'>";
     string STARTSTRIKE = "<s>";
     string ENDSTRIKE = "</s>";
     string END = "</font>";


    string diffResult = "";

    diff_match_patch<string> differ;
    diff_match_patch<string>::Diffs diffs =  differ.diff_main(a,b);
    diff_match_patch<string>::Diffs::iterator diffIt = diffs.begin();

    while(diffIt != diffs.end()){
        diff_match_patch<string>::Diff diff = *diffIt;
        switch(diff.operation){
        case(diff_match_patch<string>::D_Operation::D_DELETE):
            diffResult += END;
            diffResult += STARTSTRIKE;
            diffResult+=DEL;
            diffResult+=diff.text;
            mode = mode_delete;
            break;
        case(diff_match_patch<string>::D_Operation::D_INSERT):
            diffResult += ENDSTRIKE;
            diffResult += END;
            diffResult+=ADD;
            diffResult+=diff.text;
            mode = mode_insert;
            break;
        case(diff_match_patch<string>::D_Operation::D_EQUAL):
            diffResult += ENDSTRIKE;
            diffResult += END;
            diffResult += NORMAL;
            diffResult+=diff.text;
            mode = mode_equal;
            break;
        }
        ++diffIt;
    }
    string ender = "</body>";
    diffResult += ender;
    return insertBreaks(diffResult);
}

string JDiff::insertBreaks(string diffHTML){
    for(int i = 0; i < diffHTML.size(); i++){
        if(diffHTML[i] == '\"'){
            diffHTML.insert(i,"<br/>");
            i+=4;
        }
        ++i;
    }
    return diffHTML;
}

string JDiff::doExample(){

    cout<<"Diffing Test:"<<endl;
    string a = "Once upon a time, there was a\n brook by a glorious castle.";
    cout << "string 1: "<<a<<endl;
    string b = "Once upon a midsummer night,\n there was a stoplight by an office building.";
    cout << "string 2: "<<b<<endl;
    cout << "Diff: "<<makeDiff(a,b)<<endl;
    //cout << "I am indebted to: Neil Fraser, Mike Slemmer, and Sergey Nozhenko, three gentlemen posessive of the utmost excellence in industry."<<endl;

    return makeDiff(a,b);

}


