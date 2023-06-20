#include <iostream>

#include "Point.h"
#include "Source.h"
#include "System.h"
#include "FormatSystem.h"

using std::cout;
using std::endl;

int main() {

    auto pdef = ygse::Point(0.1, 0.1, "def");
    auto p11 = ygse::Point(0.15, 0.5, "p11");
    auto p12 = ygse::Point(0.14, 0.2, "p12");
    auto p13 = ygse::Point(0.13, 0.2, "p13");
    auto p14 = ygse::Point(0.14, 0.1, "p14");
    auto p21 = ygse::Point(0.15, 0.2, "p21");
    auto p22 = ygse::Point(0.11, 0.4, "p22");
    auto p23 = ygse::Point(0.12, 0.5, "p23");
    auto p24 = ygse::Point(0.14, 0.1, "p24");
    auto p31 = ygse::Point(0.12, 0.1, "p31");
    auto p32 = ygse::Point(0.12, 0.2, "p32");
    auto p33 = ygse::Point(0.13, 0.5, "p33");
    auto p34 = ygse::Point(0.14, 0.5, "p34");
    auto p41 = ygse::Point(0.13, 0.8, "p41");
    auto p42 = ygse::Point(0.12, 0.1, "p42");

    auto s1 = ygse::Source("s1", 4, true);
    auto s2 = ygse::Source("s2", 4, true);
    auto s3 = ygse::Source("s3", 4, true);
    auto s4 = ygse::Source("s4", 2, true);

    auto sst = ygse::System("Proton", "C1", 4);

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

    auto f = ygse::FormatSystem();
    f.SetFormat("%.3f");
    f.LoadSystem(0, sst);
    f.LoadSystem(1, sst);
    f.LoadSystem(2, sst);
    f.LoadSystem(3, sst);
    f.LoadSystem(4, sst);
    f.LoadSystem(5, sst);
    f.LoadSystem(6, sst);
    f.LoadSystem(7, sst);
    f.LoadSystem(8, sst);

    f.Print("text.txt");
    return 0;
}
