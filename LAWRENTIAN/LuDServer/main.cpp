#include "Receiver.h"
#include <direct.h>
#include <string>

using namespace std;

int main()
{
    Receiver rcvr = Receiver();
    // Receiver rcvr = Receiver(0,"C:/Programs"); // "C:Programs is root directory of server"
    return 0;
}

// For same computer communication.

//int main(int argc, char *argv[])
//{
//    Receiver rcvr = Receiver("default -p 10000");
//    return 0;
//}
