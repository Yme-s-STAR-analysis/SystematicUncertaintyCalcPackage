#include <iostream>
#include "Point.h"
#include "Source.h"

using std::cout;
using std::endl;

int main () {

    auto pdef = ygse::Point(0.1, 0.1, "def");
    auto p1 = ygse::Point(0.2, 0.3, "p1"); // large stat err -> will not pass barlow check
    auto p2 = ygse::Point(0.2, 0.1, "p2"); // smaller stat err -> will pass barlow check
    
    auto s1 = ygse::Source("s1", 1, false); // no barlow check
    auto s2 = ygse::Source("s2", 1, false); // no barlow check
    auto s3 = ygse::Source("s3", 1, true); // barlow check
    auto s4 = ygse::Source("s4", 1, true); // barlow check
    auto s5 = ygse::Source("s5", 2, false);
    auto s6 = ygse::Source("s6", 2, true);

    s1.SetDefault(pdef);
    s2.SetDefault(pdef);
    s3.SetDefault(pdef);
    s4.SetDefault(pdef);
    s5.SetDefault(pdef);
    s6.SetDefault(pdef);

    s1.AddVaried(p1);
    s2.AddVaried(p2);
    s3.AddVaried(p1);
    s4.AddVaried(p2);
    s5.AddVaried(p1);
    s5.AddVaried(p2);
    s6.AddVaried(p1);
    s6.AddVaried(p2);

    cout << s1.GetTag() << " " << s1.GetSigma() << " - " << s1.GetSysErrTag(0) << endl;
    cout << s2.GetTag() << " " << s2.GetSigma() << " - " << s2.GetSysErrTag(0) << endl;
    cout << s3.GetTag() << " " << s3.GetSigma() << " - " << s3.GetSysErrTag(0) << endl;
    cout << s4.GetTag() << " " << s4.GetSigma() << " - " << s4.GetSysErrTag(0) << endl;
    cout << s5.GetTag() << " " << s5.GetSigma() << " - " << s5.GetSysErrTag(0) << endl;
    cout << s6.GetTag() << " " << s6.GetSigma() << " - " << s6.GetSysErrTag(0) << endl;
    cout << s6.GetTag() << " " << s6.GetSigma() << " - " << s6.GetSysErrTag(1) << endl;
    cout << s6.GetTag() << " " << s6.GetSigma() << " - " << s6.GetSysErrTag(2) << endl;

    return 0;
}