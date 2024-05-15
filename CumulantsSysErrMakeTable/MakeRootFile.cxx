#include <iostream>
#include <string>
#include <fstream>

#include "TFile.h"
#include "TString.h"
#include "TGraphErrors.h"

#include "Point.h"
#include "Source.h"
#include "System.h"

#include "GraphLoader.h"

using std::cout;
using std::endl;

using ygse::Point;
using ygse::Source;
using ygse::System;

int main(int argc, char** argv) {

    /*
        Args:
        :folder path: a string, the path to the root files (root path)
        // :rapidity index: a string (indeed an integer), 1 to 7
        :scan tag: a string, liek y0p5, pt1p4 etc.
        :out dir: a string, path to save the out put root file
        :withX: 0 for RefMult3 and 1 for RefMult3X
        :npart: a string, the file name of mean Npart text
    */

    TGraphErrors* tgs[3][14];
    const char* particle_names[3] = {
        "Netp", "Pro", "Pbar"
    };
    const char* ctags[7] = {
        "C1", "C2", "C3", "C4", "R21", "R32", "R42"
    };
    const char* ktags[7] = {
        "k1", "k2", "k3", "k4", "k21", "k31", "k41"
    };

    // init. and set name for tgrapherrors
    for (int i=0; i<3; i++) {
        for (int j=0; j<7; j++) {
            tgs[i][j] = new TGraphErrors(9);
            tgs[i][j]->SetName(Form("%s_%s", particle_names[i], ctags[j]));
        }
        if (i == 0) {
            continue;
        }
        for (int j=0; j<7; j++) {
            tgs[i][j+7] = new TGraphErrors(9);
            tgs[i][j+7]->SetName(Form("%s_%s", particle_names[i], ktags[j]));
        }
    }

    GraphLoader* gl = new GraphLoader(argv[1]);
    const char* scan_tag = argv[2];
    const char* out_dir = argv[3];
    bool withX = (bool)atoi(argv[4]);


    const int nCent = 9;
    const int nSource = 5;
    const int nCut = 4;

    double nPart[nCent] = { // default value
        339, 289, 226, 160, 110, 72, 45, 26, 14
    };
    const char* Npart_fn = argv[5];
    // if (std::strtmp(Npart_fn, "none")) { 
    if (argc == 6) { // read Npart
        std::ifstream Npart_f;
        Npart_f.open(Npart_fn);
        std::string strtmp;
        int cnt = 0;
        while (std::getline(Npart_f, strtmp)) {
            nPart[cnt] = atof(strtmp.c_str());
            cnt += 1;
        }
    }
    Point pdef[nCent];
    Point pvrd[nSource][nCut][nCent];
    Source source[nSource][nCent];
    System system[nCent];

    const char* source_tags[nSource] = { // for source names
        "nHitsFit", "DCA", "$n\\sigma$", "$m^2$", "$\\epsilon$" // , "Mult."
    };
    const char* cut_tags[nSource][nCut] = { // for cut names
        {"15", "18", "22", "25"}, 
        {"0.8", "0.9", "1.1", "1.2"}, 
        {"1.6", "1.8", "2.2", "2.5"}, 
        {"(0.50,1.10)", "(0.55,1.15)", "(0.65,1.25)", "(0.70,1.30)"},
        {"$\\times0.98$", "$\\times1.02$", "None", "None"},
        // {"+1", "-1", "None", "None"},
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

    for (int ipart=0; ipart<3; ipart++) {
        for (int icum=0; icum<7; icum++) {
            for (int i=0; i<nCent; i++) {
                system[i] = System(particle_names[ipart], ctags[icum], nSource);
                pdef[i] = Point();
                pdef[i].SetTag(ctags[icum]);
                gl->GetPoint("default", scan_tag, particle_names[ipart], ctags[icum], i, &pdef[i], withX);
                for (int j=0; j<nSource; j++) {
                    source[j][i] = Source(source_tags[j], nCuts4Source[j], true);
                    source[j][i].SetDefault(pdef[i]);
                    for (int k=0; k<nCuts4Source[j]; k++) {
                        pvrd[j][k][i] = Point();
                        pvrd[j][k][i].SetTag(cut_tags[j][k]);
                        gl->GetPoint(cut_tags4file[j][k], scan_tag, particle_names[ipart], ctags[icum], i, &pvrd[j][k][i], withX);
                        source[j][i].AddVaried(pvrd[j][k][i]);
                    }
                    system[i].AddSource(source[j][i]);
                }
                tgs[ipart][icum]->SetPointX(i, nPart[i]);
                tgs[ipart][icum]->SetPointY(i, pdef[i].GetValue());
                tgs[ipart][icum]->SetPointError(i, 0.0, system[i].GetSigma());
            }
        }
        if (ipart == 0) {
            continue;
        }
        for (int icf=0; icf<7; icf++) {
            for (int i=0; i<nCent; i++) {
                system[i] = System(particle_names[ipart], ktags[icf], nSource);
                pdef[i] = Point();
                pdef[i].SetTag(ktags[icf]);
                gl->GetPoint("default", scan_tag, particle_names[ipart], ktags[icf], i, &pdef[i], withX);
                for (int j=0; j<nSource; j++) {
                    source[j][i] = Source(source_tags[j], nCuts4Source[j], true);
                    source[j][i].SetDefault(pdef[i]);
                    for (int k=0; k<nCuts4Source[j]; k++) {
                        pvrd[j][k][i] = Point();
                        pvrd[j][k][i].SetTag(cut_tags[j][k]);
                        gl->GetPoint(cut_tags4file[j][k], scan_tag, particle_names[ipart], ktags[icf], i, &pvrd[j][k][i], withX);
                        source[j][i].AddVaried(pvrd[j][k][i]);
                    }
                    system[i].AddSource(source[j][i]);
                }
                tgs[ipart][icf+7]->SetPointX(i, nPart[i]);
                tgs[ipart][icf+7]->SetPointY(i, pdef[i].GetValue());
                tgs[ipart][icf+7]->SetPointError(i, 0.0, system[i].GetSigma());
            }
        }
    }

    TFile* fout;
    if (withX) {
        fout = new TFile(Form("%s/%sX.root", out_dir, scan_tag), "recreate");
    } else {
        fout = new TFile(Form("%s/%s.root", out_dir, scan_tag), "recreate");
    }
    fout->cd();
    for (int i=0; i<3; i++) {
        for (int j=0; j<7; j++) {
            tgs[i][j]->Write();
        }
        if (i == 0) {
            continue;
        }
        for (int j=0; j<7; j++) {
            tgs[i][j+7]->Write();
        }
    }
    fout->Close();

    return 0;
}
