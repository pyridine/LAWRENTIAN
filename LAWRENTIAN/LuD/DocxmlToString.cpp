#include "DocxmlToString.h"
#include <string>
#include <sstream>
#include <iostream>
#include <fstream>
#include <qprocess.h>
#include <QThread>
#include <qstringlist.h>

string DocxmlToString::parse(string absoluteDirectory){
    return parseDocXML(fileToText(absoluteDirectory));
}

string DocxmlToString::fileToText(string dir){
    ifstream document;
    document.open(dir);
    if(document.is_open()){
        stringstream docString;
        string nextLine;
        while(getline(document,nextLine)){
            docString << nextLine;
        }
        document.close();
        return docString.str();
    } else{
        cout << "ERROR!";
        return "ERROR!";
    }

}
string DocxmlToString::parseDocXML(string xml){
    const char* xmlt = xml.c_str();
    stringstream document;

    string begin = "<w:t";
    string newline = "<w:p"; //it is crucial that this is the same length as begin. actually <w:pStyle. okay, so this is shitty...
    char end = '<';
    //We will search for text starting after the end of $begin, and ending before $end.
    //Because we know for a fact that these tags occur way before the end of the document (many multiples of their length before),
    //we don't have to be careful about iterating off the string. Importantly, we also don't ever end with a <w:t>.
    //Actually, we don't have to be careful at all, because we can stop at the first < after <w:t>, and not care about getting
    //off of </w:t> properly!

    int numNewLines = 0; //skip the first one.
    unsigned int it = 0;
    //This search is dumb.
    //Most of the not-text-we-want elements are accessed begin.size() times.
    //But fuck optimization, the documents aren't going to be *huge*.
    while(it < xml.size()-begin.size()){
        //Check to see if we're looking at a begin tag.
        string thisText = "";
        unsigned int getThisText = 0;
        while(getThisText < begin.size()){
            thisText+=xmlt[it];
            ++getThisText;
            ++it;
        }
        if(!thisText.compare(begin)){
            --it;
            //we have entered a begin tag.
            string nextText = "";
            ++it;
            //Look for the end of the tag.
            while(xml[it] != '>'){
                ++it;
            }
            ++it;
            while(xmlt[it] != end){
                nextText+=xmlt[it];
                ++it;
            }
            if(nextText.size()) document<<nextText;
        } else if (!thisText.compare(newline)){
            //We have found a newline tag.
            string ending;
            ending+=xmlt[it];
            ending+=xmlt[it+1];
            ending+=xmlt[it+2];
            ending+=xmlt[it+3];
            if(!ending.compare("Styl")){
                if(numNewLines == 0){
                    numNewLines++;
                }else{
                //it's a new line.
                //WOW THIS CODE IS SHIT.
                document<<"\n";
                }
            }
        }
        else{
            it -= begin.size()-1;
        }
    }
    return document.str();


}

string DocxmlToString::unzipDocx(string dir/*directory of doc*/,string docxname){

       QProcess* proc = new QProcess();

       string directoryOfBatch = "C:/Users/Pyridine/Desktop/junz_gold.bat";

       string docxC = "";
       docxC+=docxname;

       string dirC = "";
       dirC+=dir;


       QStringList args;
       args.append(QString::fromStdString("/C start "+directoryOfBatch+" "+docxC+" end "+dirC+" end "));


       proc->startDetached("cmd",args);
       if(!proc->waitForStarted()){
            cout << "CMD start error.";
       }
       proc->waitForFinished();
       QThread::sleep(1); //Necessary until we find a fix :P
       //proc->close();

       stringstream directoryOfDoc;
       directoryOfDoc << dir << "/" << docxname << "/" << "document.xml";
       return directoryOfDoc.str();
}
