#include "diff.h"
#include "copyhistorywindow.h" //there's a static function here I'm calling. Not good form.

JDiff::JDiff()
{

}

JDiff::~JDiff()
{

}


queue<string>* JDiff::makeHTMLDiff_Q(queue<string> newSQ,queue<string> oldSQ){
    //string a and b must be of the s
    queue<string>* final = new queue<string>();

    final->push(JDiff::GET_HTML_DOC_HEADER());

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
            final->push(JDiff::makeHTMLDiff_Line("",olds));
            oldSQ.pop();
        }
    }


    final->push(JDiff::GET_HTML_DOC_ENDER());


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
    diffResult += GET_HTML_LINE_HEADER();

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
    diffResult += JDiff::GET_HTML_LINE_ENDER();
    return diffResult;
}

string JDiff::makeHTML(string s){
    string htmld="";
    htmld+=JDiff::GET_HTML_DOC_HEADER();

    queue<string>* htmlq = splitStringToQueue(s);

    while(0 < htmlq->size()){
        string nextLine = "";
        nextLine += GET_HTML_LINE_HEADER();
        nextLine += htmlq->front();
        htmlq->pop();
        nextLine += GET_HTML_LINE_ENDER();
        htmld += nextLine;
    }
    return htmld;

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

string JDiff::GET_HTML_LINE_HEADER(){
    return "<span style=\" font-size:10.5pt;\">";
}

string JDiff::GET_HTML_LINE_ENDER(){
    return "</span></p><br/>";
}

string JDiff::GET_HTML_DOC_HEADER(){
    return "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\"><html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">p, li { white-space: pre-wrap; }</style></head><body style=\" font-family:'MS Shell Dlg 2'; font-size:8.25pt; font-weight:400; font-style:normal;\">";
}


string JDiff::GET_HTML_DOC_ENDER(){
    return "</p></body></html>";
}

std::queue<std::string>* JDiff::splitStringToQueue(std::string s){
    queue<string>* splot = new queue<string>;
//    //first, we find the index of the first nontrivial character.
//    int i = 0;
//    while(s[i] == '\n'){
//        ++i;
//    }
//    ++i;
    unsigned int i = 0;
    unsigned int j = 0;
    //i is iterator. j keeps track of where new line begins.
    while(i < s.size()){
        if(s[i] == '\n'){
            splot->push(s.substr(j,i));
            j = i+1;
        }
        ++i;
    }
    splot->push(s.substr(j,s.size())); //Push the final string
    return splot;
}

