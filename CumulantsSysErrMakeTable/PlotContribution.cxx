#include <iostream>

#include "TFile.h"
#include "TGraphErrors.h"
#include "TH1F.h"
#include "TCanvas.h"
#include "TPad.h"
#include "TLatex.h"
#include "TLegend.h"
#include "TMath.h"
#include "TPie.h"
#include "TStyle.h"

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
        :rapidity index: a string (indeed an integer), 1 to 7
        :particle tag: Netp, Pro or Pbar
        :var tag: C1 ~ C4, R21 ~ R42, k1 ~ k4, k21 ~ k41, ...
        :cent tag: centrality index, 0 to 8
        :save path: to save the contribution plots
        :withX: 0 for RefMult3, 1 for RefMult3X
    */

    GraphLoader* gl = new GraphLoader(argv[1]);
    const char* rapidity_index = argv[2];
    const char* particle_tag = argv[3];
    const int var_idx = atoi(argv[4]);
    const char* cent_tag = argv[5];
    const char* save_path = argv[6];
    bool withX = (bool)atoi(argv[7]);

    const int nSource = 5;
    const int nCut = 4;
    const int nCent = 9;

    Point pdef;
    Point pvrd[nSource][nCut];
    Source source[nSource];
    System system;

    const char* cent_titles[nCent] = {
        "0~5%", 
        "5~10%", 
        "10~20%", 
        "20~30%", 
        "30~40%", 
        "40~50%", 
        "50~60%", 
        "60~70%", 
        "70~80%"
    };

    const char* var_tags[14] = {
        "C1", "C2", "C3", "C4", "R21", "R32", "R42", 
        "k1", "k2", "k3", "k4", "k21", "k31", "k41"
    };
    const char* var_titles[14] = {
        "C_{1}", "C_{2}", "C_{3}", "C_{4}", "C_{2}/C_{1}", "C_{3}/C_{2}", "C_{4}/C_{2}", 
        "#kappa_{1}", "#kappa_{2}", "#kappa_{3}", "#kappa_{4}", "#kappa_{2}/#kappa_{1}", "#kappa_{3}/#kappa_{1}", "#kappa_{4}/#kappa_{1}"
    };
    const char* var_tag = var_tags[var_idx];
    const char* var_title = var_titles[var_idx];

    int cent_idx = std::atoi(cent_tag);
    if (cent_idx < 0 || cent_idx > 8) {
        std::cout << "[ERROR] Centrality Index should be 0 to 8 but got " << cent_idx << ".\n";
        return -1;
    }

    const char* source_tags[nSource] = { // for source names
        "nHitsFit", "DCA", "n#sigma", "m^{2}", "#epsilon" // , "Mult."
    };
    const char* cut_tags[nSource][nCut] = { // for cut names
        {"a)15", "b)18", "c)22", "d)25"}, 
        {"a)0.8", "b)0.9", "c)1.1", "d)1.2"}, 
        {"a)1.6", "b)1.8", "c)2.2", "d)2.5"}, 
        {"a)(0.50,1.10)", "b)(0.55,1.15)", "c)(0.65,1.25)", "d)(0.70,1.30)"},
        {"a)$\\times0.98$", "b)$\\times1.02$", "None", "None"},
        // {"a)+1", "b)-1", "None", "None"},
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
    int pieColors[nSource] = {
        kRed, kGreen, kBlue, kGray, kMagenta, kCyan
    }; // colors for pie chart

    system = System(particle_tag, var_tag, nSource);
    pdef = Point();
    pdef.SetTag(var_tag);
    gl->GetPoint("default", rapidity_index, particle_tag, var_tag, cent_idx, &pdef, withX);
    for (int j=0; j<nSource; j++) {
        source[j] = Source(source_tags[j], nCuts4Source[j], true);
        source[j].SetDefault(pdef);
        for (int k=0; k<nCuts4Source[j]; k++) {
            pvrd[j][k] = Point();
            pvrd[j][k].SetTag(cut_tags[j][k]);
            gl->GetPoint(cut_tags4file[j][k], rapidity_index, particle_tag, var_tag, cent_idx, &pvrd[j][k], withX);
            source[j].AddVaried(pvrd[j][k]);
        }
        system.AddSource(source[j]);
    }

    double tot_err;
    double source_err[nSource] = {0.0};
    double source_err_quad[nSource] = {0.0};
    tot_err = system.GetSigma();
    for (int i=0; i<nSource; i++) {
        double tmp = system.GetSysErrValue(i);
        source_err[i] = tmp / tot_err;
        source_err_quad[i] = TMath::Power(source_err[i], 2);
    }
    std::cout << "[LOG] Total systematic uncertainty: " << tot_err << std::endl;
    for (int i=0; i<nSource; i++) {
        std::cout << "[LOG] Source [" << source_tags[i] << "] has its error as: " << system.GetSysErrValue(i) << " and fraction: " << source_err[i] << ", quadrature fraction: " << source_err_quad[i] << std::endl;
    }

    TCanvas* c = new TCanvas();
    TPad* pad1 = new TPad("pad1", "", 0.02, 0.02, 0.98, 0.94);
    TPad* pad2 = new TPad("pad2", "", 0.02, 0.02, 0.98, 0.94);
    TPad* pad3 = new TPad("pad3", "", 0.02, 0.02, 0.98, 0.94);
    TLatex* lat = new TLatex();
    lat->SetTextColor(1);
    lat->SetTextFont(64);
    lat->SetTextSize(24);
    lat->SetTextAlign(11);

    // plot style 1: histogram, normal
    c->cd();
    gStyle->SetOptStat(0);
    pad1->Draw();
    lat->DrawLatexNDC(0.02, 0.92, "#frac{#sigma_{sys. source}}{#sigma_{sys. total}}#times 100");
    lat->DrawLatexNDC(0.75, 0.92, Form("%s %s %s", cent_titles[cent_idx], particle_tag, var_title));
    TH1F* h1Normal = new TH1F(
        "h1Normal", "",
        nSource, -0.5, nSource-0.5
    );
    h1Normal->GetYaxis()->SetRangeUser(0.0, 103.0);
    for (int i=0; i<nSource; i++) {
        h1Normal->GetXaxis()->SetBinLabel(i+1, source_tags[i]);
        h1Normal->SetBinContent(i+1, source_err[i]*100);
    }
    h1Normal->SetLineColor(1);
    h1Normal->SetFillStyle(3375);
    h1Normal->SetFillColor(41);
    h1Normal->GetXaxis()->SetLabelFont(64);
    h1Normal->GetXaxis()->SetLabelSize(24);
    pad1->cd();
    h1Normal->Draw("hist");
    if (withX) {
        c->Print(Form("%s/%s_%s_%s_hist1X.pdf", save_path, particle_tag, var_tag, rapidity_index));
    } else {
        c->Print(Form("%s/%s_%s_%s_hist1.pdf", save_path, particle_tag, var_tag, rapidity_index));
    }

    // plot style 2: histogram, quadrature
    c->Clear();
    c->cd();
    pad2->Draw();
    lat->DrawLatexNDC(0.02, 0.92, "#frac{#sigma_{sys. source}^{2}}{#sigma_{sys. total}^{2}}#times 100");
    lat->DrawLatexNDC(0.75, 0.92, Form("%s %s %s", cent_titles[cent_idx], particle_tag, var_title));
    TH1F* h1Quad = new TH1F(
        "h1Quad", "",
        nSource, -0.5, nSource-0.5
    );
    h1Quad->GetYaxis()->SetRangeUser(0.0, 103.0);
    for (int i=0; i<nSource; i++) {
        h1Quad->GetXaxis()->SetBinLabel(i+1, source_tags[i]);
        h1Quad->SetBinContent(i+1, source_err_quad[i]*100);
    }
    h1Quad->SetLineColor(1);
    h1Quad->SetFillStyle(3375);
    h1Quad->SetFillColor(41);
    h1Quad->GetXaxis()->SetLabelFont(64);
    h1Quad->GetXaxis()->SetLabelSize(24);
    pad2->cd();
    h1Quad->Draw("hist");
    if (withX) {
        c->Print(Form("%s/%s_%s_%s_hist2X.pdf", save_path, particle_tag, var_tag, rapidity_index));
    } else {
        c->Print(Form("%s/%s_%s_%s_hist2.pdf", save_path, particle_tag, var_tag, rapidity_index));
    }

    // plot style 3: pie chart
    c->Clear();
    c->cd();
    pad3->Draw();
    lat->DrawLatexNDC(0.02, 0.92, "#frac{#sigma_{sys. source}^{2}}{#sigma_{sys. total}^{2}}#times 100");
    lat->DrawLatexNDC(0.75, 0.92, Form("%s %s %s", cent_titles[cent_idx], particle_tag, var_title));
    pad3->cd();

    TPie* pie = new TPie(
        // "pie", Form("%s %s %s", cent_titles[cent_idx], particle_tag, var_tag),
        "pie", "",
        nSource, source_err_quad, pieColors
    );
    // pie->SetY(0.32);
    // pie->SetLabelsOffset(-0.1);
    pie->SetLabels(source_tags);
    pie->SetCircle(0.5, 0.45, 0.3);
    // pie->SetLabelFormat("%perc");
    pie->SetLabelFormat("");
    for (int i=0; i<nSource; i++) {
        pie->SetEntryLineColor(i, 1);
        // if (source_err_quad[i] > 1.0 / nSource) { // greater than average
            // pie->SetEntryRadiusOffset(i, 0.05);
            // pie->SetEntryLineColor(i, 1);
            // pie->SetEntryLineWidth(i, 3);
        // }
    }
    // pie->Draw("3d t nol");
    pie->Draw("rsc");
    TLegend *pieleg = pie->MakeLegend();
    pieleg->SetY1(0.56);
    pieleg->SetY2(0.86);
    if (withX) {
        c->Print(Form("%s/%s_%s_%s_pie.pdf", save_path, particle_tag, var_tag, rapidity_index));
    } else {
        c->Print(Form("%s/%s_%s_%s_pie.pdf", save_path, particle_tag, var_tag, rapidity_index));
    }
    return 0;
}
