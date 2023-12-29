#include <iostream>
#include <uv.h>
using namespace std;

int
main()
{
    char * version;
    version = (char *)uv_version_string();
    cout << "libuv version is " << version << endl;
    return 0;
}
