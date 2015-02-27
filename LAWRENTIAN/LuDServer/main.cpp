#include <string>
#include <iostream>
#include <vector>
#include "FileSystemI.h"

std::string extractFolderName(const std::string &s)
{
    using namespace std;
    string ret;
    string::const_iterator it, iter = s.end() - 1;
    while(*iter != '/')
    {
        if(iter == s.begin())
            return ret;
        iter--;
    }
    iter--;
    it = iter;
    while(*it != '/')
    {
        if(it == s.begin())
            return ret;
        it--;
    }
    it++;
    return s.substr(it-s.begin(),iter-it +1);
}

int main()
{
    using namespace std;

    FileSystemI fs = FileSystemI();

    cout << 1 << endl;
    FileSystemI::StrSeq vs = fs.getImageList("Sports","Fencing Team New Champions");
    cout << 2 << endl;
    vector<string>::const_iterator iter = vs.begin();
    cout << 3 << endl;
    while (iter != vs.end())
    {
        cout << *iter << endl;
        iter++;
    }

    return 0;
}
