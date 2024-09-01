#include <iostream>
#include <mutex>
#include <algorithm>

using namespace std;

class Date
{
public:
    int value;
    mutex mtx;

    Date(int v) : value(v) {}
};

void swap_with_lock(Date& a, Date& b)
{
    unique_lock<mutex> lockA(a.mtx, defer_lock);
    unique_lock<mutex> lockB(b.mtx, defer_lock);
    lock(lockA, lockB);

    swap(a.value, b.value);
}

void swap_with_scoped_lock(Date& a, Date& b)
{
    scoped_lock lock(a.mtx, b.mtx);

    swap(a.value, b.value);
}

void swap_with_unique_lock(Date& a, Date& b)
{
    unique_lock<mutex> lockA(a.mtx, defer_lock);
    unique_lock<mutex> lockB(b.mtx, defer_lock);
    lock(lockA, lockB); 

    swap(a.value, b.value);
}

int main()
{
    std::cout << "Hello World!\n";


    Date data1(10);
    Date data2(20);

    cout << "Before swap:" << endl;
    cout << "Data1: " << data1.value << ", Data2: " << data2.value << endl;

    swap_with_lock(data1, data2);

    swap_with_unique_lock(data1, data2);

    swap_with_scoped_lock(data1, data2);

    cout << "After swap:" << endl;
    cout << "Data1: " << data1.value << ", Data2: " << data2.value << endl;

}

