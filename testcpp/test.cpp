#include <iostream>;
#include <time.h> ;
using namespace std;

int main(int argc, char const *argv[])
{
    time_t nowtime;
    nowtime = time(NULL); //获取当前时间
    cout << nowtime << endl;
    return 0;
}
