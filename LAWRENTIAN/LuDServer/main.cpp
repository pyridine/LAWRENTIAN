#include <windows.h>
#include <string>
#include <vector>
#include <stack>
#include <iostream>
#include <cstring>
#include <io.h>
#include <iostream>
#include <stdio.h>
#include <Windows.h>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

std::string fixPath(const wstring& p)
{
    string path( p.begin(), p.end() );
    string::iterator iter = path.begin();
    for(iter; iter != path.end(); iter++)
    {
        if(*iter == '\\')
            *iter = '/';
    }
    return path;
}

std::string fixPath(const string& p)
{
    string path = p;
    string::iterator iter = path.begin();
    for(iter; iter != path.end(); iter++)
    {
        if(*iter == '\\')
            *iter = '/';
    }
    return path;
}


bool ListFiles(wstring path, wstring mask, vector<wstring>& files) {
    HANDLE hFind = INVALID_HANDLE_VALUE;
    WIN32_FIND_DATA ffd;
    wstring spec;
    stack<wstring> directories;

    directories.push(path);
    files.clear();

    while (!directories.empty()) {
        path = directories.top();
        spec = path + L"\\" + mask;
        directories.pop();

        hFind = FindFirstFile(spec.c_str(), &ffd);
        if (hFind == INVALID_HANDLE_VALUE)  {
            return false;
        }

        do {
            if (wcscmp(ffd.cFileName, L".") != 0 &&
                    wcscmp(ffd.cFileName, L"..") != 0) {
                if (ffd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) {
                    directories.push(path + L"\\" + ffd.cFileName);
                }
                else {
                    files.push_back(path + L"\\" + ffd.cFileName);
                }
            }
        } while (FindNextFile(hFind, &ffd) != 0);

        if (GetLastError() != ERROR_NO_MORE_FILES) {
            FindClose(hFind);
            return false;
        }

        FindClose(hFind);
        hFind = INVALID_HANDLE_VALUE;
    }

    return true;
}

void getFolders(const std::vector<std::wstring> vec, std::vector<std::string>& out,
           const std::string& main_path)
{
    using namespace std;

    vector<wstring>::const_iterator iter = vec.begin();
    while(iter != vec.end())
    {
        wstring temp = *iter;
        string dir(temp.begin(), temp.end());
        while(!main_path.compare(dir))
        {
            if(!dir.size())
                return;

            dir = fixPath(dir);

            string::const_iterator it = dir.end() - 1;
            for(it; it != dir.begin(); it--)
            {
                if (*it == '/')
                    break;
            }
            if(it == dir.begin())
                return;

            dir.resize(it - dir.begin());

            vector<string>::const_iterator i = std::find(out.begin(),out.end(),dir);
            if(!main_path.compare(dir) && i == out.end())
                out.push_back(dir);
        }

        iter++;
    }

    return;
}

int main(int argc, char* argv[])
{
    vector<wstring> files;
    vector<string> folders;

    string path = "C:\\Users\\Briggs 419 Server\\Dropbox\\Issue\\First\\Second\\Image";
    wstring wPath(path.begin(), path.end());
    wcout << wPath << endl;

    if (ListFiles(wPath, L"*.", files)) {
        vector<wstring>::iterator it = files.begin();
        cout << files.size() << endl;
        for (it; it != files.end(); ++it)
        {
            //            remove(fixPath(it->c_str()).c_str());
            wcout << it->c_str() << endl;
        }

        getFolders(files,folders,path);
        vector<string>::iterator iter = folders.begin();
        for (iter; iter != folders.end(); iter++)
        {
            cout << *iter << endl;
        }

    }
    return 0;
}
