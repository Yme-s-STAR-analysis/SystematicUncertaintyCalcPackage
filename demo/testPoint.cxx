#include <iostream>
#include "Point.h"

using std::cout;
using std::endl;

int main () {

    cout << "Test 1" << endl;
    auto p1 = ygse::Point();
    p1.SetValue(0.1);
    p1.SetError(0.1);
    p1.SetTag("tag1");
    cout << "Value: " << p1.val() << endl;
    cout << "Error: " << p1.err() << endl;
    cout << "Tag: " << p1.GetTag() << endl;
    cout << "Test 2" << endl;
    auto p2 = ygse::Point(0.2, 0.2, "tag2");
    cout << "Value: " << p2.GetValue() << endl;
    cout << "Error: " << p2.GetError() << endl;
    cout << "Tag: " << p2.GetTag() << endl;
    auto p3 = ygse::Point();
    cout << "Value: " << p3.GetValue() << endl;
    cout << "Error: " << p3.GetError() << endl;
    // cout << "Tag: " << p3.GetTag() << endl;

    return 0;
}