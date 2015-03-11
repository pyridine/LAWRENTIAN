#include "diff.h"

JDiff::JDiff()
{

}

JDiff::~JDiff()
{

}


queue<string>* JDiff::makeHTMLDiff_Q(queue<string> newSQ,queue<string> oldSQ){
    //string a and b must be of the s
    queue<string>* final = new queue<string>();

    string head = "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\"><html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">p, li { white-space: pre-wrap; }</style></head><body style=\" font-family:'MS Shell Dlg 2'; font-size:8.25pt; font-weight:400; font-style:normal;\">";
    final->push(head);

    //Copypaste is a coding error!! Oh well.
    if(newSQ.size() > oldSQ.size()){
        //More new than old
        for(int i = 0; i < oldSQ.size(); i++){
            string news = newSQ.front();
            string olds = oldSQ.front();
            final->push(JDiff::makeHTMLDiff_Line(news,olds));
            newSQ.pop();
            oldSQ.pop();
        }
        for(int i = 0; i < newSQ.size(); i++){
            string news = newSQ.front();
            final->push(JDiff::makeHTMLDiff_Line(news,""));
            newSQ.pop();
        }
    } else{
        //More (or equal) old than new
        for(int i = 0; i < newSQ.size(); i++){
            string news = newSQ.front();
            string olds = oldSQ.front();
            final->push(JDiff::makeHTMLDiff_Line(news,olds));
            newSQ.pop();
            oldSQ.pop();
        }
        for(int i = 0; i < oldSQ.size(); i++){
            string olds = oldSQ.front();
            final->push(JDiff::makeHTMLDiff_Line(olds,""));
            oldSQ.pop();
        }
    }

    string end = "</p></body></html>";
    final->push(end);


    return final;
}

/**
 * This is only to be used with makeHTMLDiff__Q.
 * If you just need one line, call Q with queues of size one.
 */
string JDiff::makeHTMLDiff_Line(string newS, string oldS){
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
    string head = "<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-size:11pt;\">";

    diff_match_patch<string> differ;
    diff_match_patch<string>::Diffs diffs =  differ.diff_main(newS,oldS);
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
    string ender = "</span></p><br/>";
    diffResult += ender;
    return diffResult;
}

void JDiff::doExample(){

    cout<<"Diffing Test:"<<endl;
    string a = "Once upon a time.";
    cout << "string 1: "<<a<<endl;
    string b = "Once upon a gripe.";
    cout << "string 2: "<<b<<endl;
    cout << "Diff: "<<makeHTMLDiff_Line(a,b)<<endl;
    //cout << "I am indebted to: Neil Fraser, Mike Slemmer,
    //and Sergey Nozhenko, three gentlemen posessive of the utmost
    //excellence in industry."<<endl;
}


