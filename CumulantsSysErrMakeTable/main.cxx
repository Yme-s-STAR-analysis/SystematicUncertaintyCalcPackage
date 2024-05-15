#include <iostream>

#include "TFile.h"
#include "TGraphErrors.h"

#include "Point.h"
#include "Source.h"
#include "System.h"
#include "FormatSystem.h"

#include "GraphLoader.h"

using std::cout;
using std::endl;

using ygse::Point;
using ygse::Source;
using ygse::System;
using ygse::FormatSystem;

int main(int argc, char** argv) {

    /*
        Args:
        :folder path: a string, the path to the root files (root path)
        :rapidity index: a string (indeed an integer), 1 to 7
        :particle tag: Netp, Pro or Pbar
        :var tag: C1 ~ C4, R21 ~ R42, k1 ~ k4, k21 ~ k41, ...
        :table path: to save the LATEX table source codes
        :withX: 0 for RefMult3, 1 for RefMult3X
    */

    GraphLoader* gl = new GraphLoader(argv[1]);
    const char* rapidity_index = argv[2];
    const char* particle_tag = argv[3];
    const char* var_tag = argv[4];
    const char* table_path = argv[5];
    bool withX = (bool)atoi(argv[6]);

    const int nCent = 9;
    const int nSource = 5;
    const int nCut = 4;

    Point pdef[nCent];
    Point pvrd[nSource][nCut][nCent];
    Source source[nSource][nCent];
    System system[nCent];
    FormatSystem fmt;

    const char* source_tags[nSource] = { // for source names
        "nHitsFit", "DCA", "$n\\sigma$", "$m^2$", "$\\epsilon$" // , "Mult."
    };
    const char* cut_tags[nSource][nCut] = { // for cut names
        {"a)15", "b)18", "c)22", "d)25"}, 
        {"a)0.8", "b)0.9", "c)1.1", "d)1.2"}, 
        {"a)1.6", "b)1.8", "c)2.2", "d)2.5"}, 
        {"a)(0.50,1.10)", "b)(0.55,1.15)", "c)(0.65,1.25)", "d)(0.70,1.30)"},
        {"a)$\\times0.98$", "b)$\\times1.02$", "None", "None"},
        // {"a)+1", "b)-1", "None", "None"}
    };
    const char* cut_tags4file[nSource][nCut] = { // for get Graph
        {"nhit15", "nhit18", "nhit22", "nhit25"}, 
        {"dca0p8", "dca0p9", "dca1p1", "dca1p2"}, 
        {"nsig1p6", "nsig1p8", "nsig2p2", "nsig2p5"}, 
        {"mass21", "mass22", "mass23", "mass24"}, 
        {"effm", "effp", "None", "None"},
        // {"multp", "multm", "None", "None"}
    };
    const int nCuts4Source[nSource] = {4, 4, 4, 4, 2}; // set N for sources

    fmt = FormatSystem();
    fmt.SetFormat("%.4f");

    for (int i=0; i<nCent; i++) {
        system[i] = System(particle_tag, var_tag, nSource);
        pdef[i] = Point();
        pdef[i].SetTag(var_tag);
        gl->GetPoint("default", rapidity_index, particle_tag, var_tag, i, &pdef[i], withX);
        for (int j=0; j<nSource; j++) {
            source[j][i] = Source(source_tags[j], nCuts4Source[j], true);
            source[j][i].SetDefault(pdef[i]);
            for (int k=0; k<nCuts4Source[j]; k++) {
                pvrd[j][k][i] = Point();
                pvrd[j][k][i].SetTag(cut_tags[j][k]);
                gl->GetPoint(cut_tags4file[j][k], rapidity_index, particle_tag, var_tag, i, &pvrd[j][k][i], withX);
                source[j][i].AddVaried(pvrd[j][k][i]);
            }
            system[i].AddSource(source[j][i]);
        }
        system[i].GetSigma();
        fmt.LoadSystem(i, system[i]);
    }

    if (withX) {
        fmt.Print(Form("%s/%s_%s_%sX.txt", table_path, particle_tag, var_tag, rapidity_index));
    } else {
        fmt.Print(Form("%s/%s_%s_%s.txt", table_path, particle_tag, var_tag, rapidity_index));
    }
    return 0;
}
