#include <iostream>
#include "Point.h"
#include "Source.h"
#include "System.h"

using std::cout;
using std::endl;

int main () {

    auto pdef = ygse::Point(0.1, 0.1, "def");
    auto p11 = ygse::Point(0.15, 0.1, "p11");
    auto p12 = ygse::Point(0.14, 0.1, "p12");
    auto p13 = ygse::Point(0.13, 0.1, "p13");
    auto p14 = ygse::Point(0.14, 0.1, "p14");
    auto p21 = ygse::Point(0.15, 0.1, "p21");
    auto p22 = ygse::Point(0.11, 0.1, "p22");
    auto p23 = ygse::Point(0.12, 0.1, "p23");
    auto p24 = ygse::Point(0.14, 0.1, "p24");
    auto p31 = ygse::Point(0.12, 0.1, "p31");
    auto p32 = ygse::Point(0.12, 0.1, "p32");
    auto p33 = ygse::Point(0.13, 0.1, "p33");
    auto p34 = ygse::Point(0.14, 0.1, "p34");
    auto p41 = ygse::Point(0.13, 0.1, "p41");
    auto p42 = ygse::Point(0.12, 0.1, "p42");

    auto s1 = ygse::Source("s1", 4, false);
    auto s2 = ygse::Source("s2", 4, false);
    auto s3 = ygse::Source("s3", 4, false);
    auto s4 = ygse::Source("s4", 2, false);

    auto sst = ygse::System("system", 4);

    s1.SetDefault(pdef);
    s2.SetDefault(pdef);
    s3.SetDefault(pdef);
    s4.SetDefault(pdef);

    s1.AddVaried(p11);
    s1.AddVaried(p12);
    s1.AddVaried(p13);
    s1.AddVaried(p14);
    s2.AddVaried(p21);
    s2.AddVaried(p22);
    s2.AddVaried(p23);
    s2.AddVaried(p24);
    s3.AddVaried(p31);
    s3.AddVaried(p32);
    s3.AddVaried(p33);
    s3.AddVaried(p34);
    s4.AddVaried(p41);
    s4.AddVaried(p42);

    sst.AddSource(s1);
    sst.AddSource(s2);
    sst.AddSource(s3);
    sst.AddSource(s4);

    cout << "Total uncertainty: " << sst.GetSigma() << endl; 
    for (int i=0; i<4; i++) {
        cout << "Source " << i << ", total uncertainty: " << sst.GetSysErrValue(i) << ", source tag: " << sst.GetSysErrTag(i) << "." << endl;
        int nj = sst.GetN(i);
        for (int j=0; j<nj; j++) {
            cout << "Source " << i << ", cut " << j << ", uncertainty: " << sst.GetSysErrValue(i, j) << ", cut tag: " << sst.GetSysErrTag(i, j) << "." << endl;
        }
    }

    return 0;
}