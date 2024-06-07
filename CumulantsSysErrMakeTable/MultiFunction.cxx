#include <iostream>

#include "TFile.h"
#include "TH1F.h"
#include "TCanvas.h"
#include "TLatex.h"
#include "TLegend.h"
#include "TMath.h"
#include "TLine.h"
#include "TBox.h"
#include "TGraphErrors.h"
#include "TStyle.h"

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

bool IsPassedBarlow(Point pdef, Point pvrd);

int main(int argc, char** argv) {

    /*
        Argument list:
        :path: path to raw root files
        :with X: 1 or 0 (RefMult3X or RefMult3)
        :scan tag: like y0p5, pt0p8 etc., default: y0p5
        :folder path (LATEX code): the path to store the LATEX source codes, default: ../table
        :folder path (ROOT file): the path to store the ROOT files, default: ../output
        :folder path (Contribution plot): the path to store the contribution plots, default: ../cplot
        :folder path (Barlow plot): the path to store the Barlow check plots, default: ../barlow
    */

    GraphLoader* gl = new GraphLoader(argv[1]);
    bool withX = (bool)atoi(argv[2]);
    const char* scan_tag = argv[3];
    const char* table_path = argv[4];
    const char* root_path = argv[5];
    const char* cplot_path = argv[6];
    const char* barlow_path = argv[7];

    cout << "[LOG] Systematic Uncertainty One-click System" << endl;
    cout << "[LOG] Configurations are listed below: " << endl;
    cout << "[LOG]  - Root files will be read from: " << argv[1] << endl;
    if (withX) { cout << "[LOG]  - RefMult3X is used" << endl; }
    else { cout << "[LOG]  - RefMult3 is used" << endl; }
    cout << "[LOG]  - Acceptance scan tag: " << scan_tag << endl;
    cout << "[LOG]  - LATEX code will be stored at: " << table_path << endl;
    cout << "[LOG]  - ROOT file will be stored at: " << root_path << endl;
    cout << "[LOG]  - Contribution plot will be stored at: " << cplot_path << endl;
    cout << "[LOG]  - Barlow check plot will be stored at: " << barlow_path << endl;

    const int nCent = 9;
    const int nSource = 5;
    const int nCut = 4;

    Point pdef[nCent];
    Point pvrd[nSource][nCut][nCent];
    Source source[nSource][nCent];
    System system[nCent];
    FormatSystem fmt;

    const char* source_tags[nSource] = { // for source names
        "nHitsFit", "DCA", "$n\\sigma$", "$m^2$", "$\\epsilon$"
    };
    const char* source_tags_contr[nSource] = { // x-label of contribution plot
        "nHitsFit", "DCA", "n#sigma", "m^{2}", "#epsilon" // , "Mult."
    };
    const char* cut_tags[nSource][nCut] = { // for cut names
        {"a)15", "b)18", "c)22", "d)25"}, 
        {"a)0.8", "b)0.9", "c)1.1", "d)1.2"}, 
        {"a)1.6", "b)1.8", "c)2.2", "d)2.5"}, 
        {"a)(0.50,1.10)", "b)(0.55,1.15)", "c)(0.65,1.25)", "d)(0.70,1.30)"},
        {"a)$\\times0.98$", "b)$\\times1.02$", "None", "None"}
    };
    const char* cut_tags4file[nSource][nCut] = { // for get Graph
        {"nhit15", "nhit18", "nhit22", "nhit25"}, 
        {"dca0p8", "dca0p9", "dca1p1", "dca1p2"}, 
        {"nsig1p6", "nsig1p8", "nsig2p2", "nsig2p5"}, 
        {"mass21", "mass22", "mass23", "mass24"}, 
        {"effm", "effp", "None", "None"}
    };
    const int nCuts4Source[nSource] = {4, 4, 4, 4, 2}; // set N for sources
    const int nValidCuts = 19; // should be equal to sum of nCuts4Source plus 1
    const char* cut_labels[nValidCuts] = { // x labels of Barlow check plot
        "Default", 
        "nHitsFit > 15", "nHitsFit > 18", "nHistFit > 22", "nHisFit > 25", 
        "DCA < 0.8", "DCA < 0.9", "DCA < 1.1", "DCA < 1.2", 
        "|n#sigma-#delta| < 1.6", "|n#sigma-#delta| < 1.8", "|n#sigma-#delta| < 2.2", "|n#sigma-#delta| < 2.5", 
        "m^{2}#in(0.50,1.10)", "m^{2}#in(0.55,1.15)", "m^{2}#in(0.65,1.25)", "m^{2}#in(0.70,1.30)", 
        "#epsilon#times0.98", "#epsilon#times1.02"
    };

    const char* cent_titles[nCent] = {
        "0~5%", "5~10%", "10~20%", "20~30%", "30~40%", "40~50%", "50~60%", "60~70%", "70~80%"
    };

    const int nQuantityNetp = 11;
    const int nQuantityNetpExtend = 4;
    const char* quantity_tags_netp[nQuantityNetp + nQuantityNetpExtend] = {
        "C1", "C2", "C3", "C4", "R21", "R31", "R32", "R42", "ppb", "R2s", "R3s", // all
        "C5", "C6", "R51", "R62" // extend
    };
    const char* quantity_titles_netp[nQuantityNetp + nQuantityNetpExtend] = {
        "C_{1}", "C_{2}", "C_{3}", "C_{4}",
        "C_{2}/C_{1}", "C_{3}/C_{1}", "C_{3}/C_{2}", "C_{4}/C_{2}", 
        "<p+#bar{p}>", "C_{2}/<p+#bar{p}>", "C_{3}/<p+#bar{p}>", // all
        "C_{5}", "C_{6}", "C_{5}/C_{1}", "C_{6}/C_{2}" // extend
    };
    const char* quantity_titles_table_netp[nQuantityNetp + nQuantityNetpExtend] = {
        "$C_{1}$", "$C_{2}$", "$C_{3}$", "$C_{4}$",
        "$C_{2}/C_{1}$", "$C_{3}/C_{1}$", "$C_{3}/C_{2}$", "$C_{4}/C_{2}$", 
        "$\\left<p+\\bar{p}$\\right>", "$C_{2}/\\left<p+\\bar{p}\\right>$", "$C_{3}/\\left<p+\\bar{p}\\right>$", // all
        "$C_{5}$", "$C_{6}$", "$C_{5}/C_{1}$", "$C_{6}/C_{2}$" // extend
    };

    const int nQuantity = 15;
    const int nQuantityExtend = 8;
    const char* quantity_tags[nQuantity + nQuantityExtend] = {
        "C1", "C2", "C3", "C4", "R21", "R31", "R32", "R42",
        "k1", "k2", "k3", "k4", "k21", "k31", "k41", // all
        "C5", "C6", "k5", "k6", "R51", "R62", "k51", "k61" // extend
    };
    const char* quantity_titles[nQuantity + nQuantityExtend] = {
        "C_{1}", "C_{2}", "C_{3}", "C_{4}",
        "C_{2}/C_{1}", "C_{3}/C_{1}", "C_{3}/C_{2}", "C_{4}/C_{2}", 
        "#kappa_{1}", "#kappa_{2}", "#kappa_{3}", "#kappa_{4}", 
        "#kappa_{2}/#kappa_{1}", "#kappa_{3}/#kappa_{1}", "#kappa_{4}/#kappa_{1}", // all
        "C_{5}", "C_{6}", "#kappa_{5}", "#kappa_{6}", 
        "C_{5}/C_{1}", "C_{6}/C_{2}",  "#kappa_{5}/#kappa_{1}", "#kappa_{6}/#kappa_{1}" // extend
    };
    const char* quantity_table_titles[nQuantity + nQuantityExtend] = {
        "$C_{1}$", "$C_{2}$", "$C_{3}$", "$C_{4}$",
        "$C_{2}/C_{1}$", "$C_{3}/C_{1}$", "$C_{3}/C_{2}$", "$C_{4}/C_{2}$", 
        "$\\kappa_{1}$", "$\\kappa_{2}$", "$\\kappa_{3}$", "$\\kappa_{4}$", 
        "$\\kappa_{2}/\\kappa_{1}$", "$\\kappa_{3}/\\kappa_{1}$", "$\\kappa_{4}/\\kappa_{1}$", // all
        "$C_{5}$", "$C_{6}$", "$\\kappa_{5}$", "$\\kappa_{6}$", 
        "$C_{5}/C_{1}$", "$C_{6}/C_{2}$",  "$\\kappa_{5}/\\kappa_{1}$", "$\\kappa_{6}/\\kappa_{1}" // extend
    };

    // ============= Initialization
    // for LATEX code
    cout << "[LOG] Initializing LATEX code generator";
    fmt = FormatSystem();
    fmt.SetFormat("%.4f");
    cout << " -> Done." << endl;

    // for ROOT file
    cout << "[LOG] Initializing ROOT file generator";
    TGraphErrors* tgs_netp[nQuantityNetp+nQuantityNetpExtend];
    for (int iQuantity = 0; iQuantity < nQuantityNetp+nQuantityNetpExtend; iQuantity++) {
        tgs_netp[iQuantity] = new TGraphErrors(9);
        tgs_netp[iQuantity]->SetName(Form("Netp_%s", quantity_tags_netp[iQuantity]));
    }
    cout << " <Netp> ";
    const char* ppbar[2] = {"Pro", "Pbar"};
    const char* ppbar_title[2] = {"Proton", "Antiproton"};
    TGraphErrors* tgs[2][nQuantity+nQuantityExtend];
    for (int iQuantity = 0; iQuantity < nQuantity+nQuantityExtend; iQuantity++) {
        for (int ippbar = 0; ippbar < 2; ippbar++) {
            tgs[ippbar][iQuantity] = new TGraphErrors(nCent);
            tgs[ippbar][iQuantity]->SetName(Form("%s_%s", ppbar[ippbar], quantity_tags[iQuantity]));
        }
    }
    cout << " <Pro> <Pbar> ";
    cout << " -> Done." << endl;

    // for contribution plot
    cout << "[LOG] Initializing contribution plot generator";
    double tot_err = 0.0;
    double source_err[nSource] = { 0.0 };
    double source_err_quad[nSource] = { 0.0 };
    TCanvas* c_cplot = new TCanvas();
    TLatex* lat = new TLatex();
    lat->SetTextColor(1);
    lat->SetTextFont(64);
    lat->SetTextSize(24);
    lat->SetTextAlign(11);
    TH1F* h1Contr = new TH1F(
        "h1Contr", "",
        nSource, -0.5, nSource-0.5
    );
    h1Contr->GetYaxis()->SetRangeUser(0.0, 103.0);
    h1Contr->SetLineColor(1);
    h1Contr->SetFillStyle(3375);
    h1Contr->SetFillColor(41);
    h1Contr->GetXaxis()->SetLabelFont(64);
    h1Contr->GetXaxis()->SetLabelSize(24);
    cout << " -> Done." << endl;

    // for Barlow check plot
    cout << "[LOG] Initializing Barlow check plot generator";
    double bl_values[nValidCuts];
    double bl_errors[nValidCuts]; // statistic error for each cut
    bool bl_pass[nValidCuts];
    // new feature: the limitation of changed obserserbal to pass barlow check
    // assume that the std. dev. of this point is fixed, and default case is fixed, so we can get the critical lower and upper limit of this systematic varied point to pass barlow check
    // mathematically, should be: O_def +- \sqrt((\sigma_def^2 - \sigma_vrd^2))
    double bl_barlow_err[nValidCuts]; 
    
    const int ms_passed = 20;
    const int ms_failed = 24;
    const int mc_passed = 1;
    const int mc_failed = 2;
    const int band_color = 4;

    for (int iCut = 0; iCut < nValidCuts; iCut++) {
        bl_values[iCut] = 0.0;
        bl_errors[iCut] = 0.0;
        bl_pass[iCut] = false;
        bl_barlow_err[iCut] = 0.0;
    }

    TGraphErrors* tgp = new TGraphErrors(); // passed
    TGraphErrors* tgf = new TGraphErrors(); // failed
    TBox* tbx = new TBox(); // barlow limit
    TLine* tline = new TLine(); // barlow limit
    tbx->SetFillColorAlpha(band_color, 0.4);
    tline->SetLineColor(band_color);

    tgp->SetMarkerColor(mc_passed);
    tgf->SetMarkerColor(mc_failed);
    tgp->SetLineColor(mc_passed);
    tgf->SetLineColor(mc_failed);
    tgp->SetMarkerStyle(ms_passed);
    tgf->SetMarkerStyle(ms_failed);

    TCanvas* c_barlow = new TCanvas();
    TLatex* latb = new TLatex();
    TLegend* leg = new TLegend(0.65, 0.75, 0.85, 0.9);
    leg->AddEntry(tgp, "Passed Barlow Check");
    leg->AddEntry(tgf, "Failed to pass Barlow Check");
    cout << " -> Done." << endl;


    // ============= main
    double nPart[9] = { 0.0 };
    // Net-proton

    for (int iQuantity = 0; iQuantity < nQuantityNetp + nQuantityNetpExtend; iQuantity++) {
        const char* netp = "Netp";
        const char* netp_title = "Net-proton";
        for (int iCent = 0; iCent < nCent; iCent++) {
            system[iCent] = System(netp_title, quantity_titles_table_netp[iQuantity], nSource);
            pdef[iCent] = Point();
            pdef[iCent].SetTag(quantity_tags_netp[iQuantity]);
            gl->GetPoint("default", scan_tag, netp, quantity_tags_netp[iQuantity], iCent, &pdef[iCent], withX);
            int iBarlowPoint = 0;
            bl_values[iBarlowPoint] = pdef[iCent].GetValue();
            bl_errors[iBarlowPoint] = pdef[iCent].GetError();
            bl_pass[iBarlowPoint] = true;
            iBarlowPoint += 1;
            for (int iSource = 0; iSource < nSource; iSource++) {
                source[iSource][iCent] = Source(source_tags[iSource], nCuts4Source[iSource], true);
                source[iSource][iCent].SetDefault(pdef[iCent]);
                for (int iCut = 0; iCut < nCuts4Source[iSource]; iCut++) {
                    pvrd[iSource][iCut][iCent] = Point();
                    pvrd[iSource][iCut][iCent].SetTag(cut_tags[iSource][iCut]);
                    gl->GetPoint(cut_tags4file[iSource][iCut], scan_tag, netp, quantity_tags_netp[iQuantity], iCent, &pvrd[iSource][iCut][iCent], withX);
                    if (nPart[iCent] == 0.0) { nPart[iCent] = gl->GetX(); } // only set <Npart> for the first time we try to get it
                    source[iSource][iCent].AddVaried(pvrd[iSource][iCut][iCent]);

                    // check Barlow test
                    if (iCent == 0) {
                        bl_values[iBarlowPoint] = pvrd[iSource][iCut][iCent].GetValue();
                        bl_errors[iBarlowPoint] = pvrd[iSource][iCut][iCent].GetError();
                        bl_barlow_err[iBarlowPoint] = TMath::Sqrt(fabs(TMath::Power(pvrd[iSource][iCut][iCent].err(), 2) - TMath::Power(pdef[iCent].err(), 2)));
                        bl_pass[iBarlowPoint] = IsPassedBarlow(pdef[iCent], pvrd[iSource][iCut][iCent]);
                        iBarlowPoint += 1;
                    }
                }
                system[iCent].AddSource(source[iSource][iCent]);
            }

            // make graph
            tgs_netp[iQuantity]->SetPointX(iCent, nPart[iCent]);
            tgs_netp[iQuantity]->SetPointY(iCent, pdef[iCent].GetValue());
            tgs_netp[iQuantity]->SetPointError(iCent, 0.0, system[iCent].GetSigma());

            // make LATEX
            fmt.LoadSystem(iCent, system[iCent]);

            // contribution plot
            if (iCent == 0 || iCent == 1 || iCent == 8) {
                tot_err = system[iCent].GetSigma();
                for (int iSource = 0; iSource < nSource; iSource++) {
                    double tmp = system[iCent].GetSysErrValue(iSource);
                    source_err[iSource] = tmp / tot_err;
                    source_err_quad[iSource] = TMath::Power(source_err[iSource], 2);
                }
                c_cplot->Clear();
                c_cplot->cd();
                gStyle->SetOptStat(0);
                for (int iSource = 0; iSource < nSource; iSource++) {
                    h1Contr->GetXaxis()->SetBinLabel(iSource+1, source_tags_contr[iSource]);
                    h1Contr->SetBinContent(iSource+1, source_err[iSource]*100);
                }
                h1Contr->Draw("hist");
                lat->DrawLatexNDC(0.02, 0.92, "#frac{#sigma_{sys. source}}{#sigma_{sys. total}}#times 100");
                lat->DrawLatexNDC(0.55, 0.92, Form("%s %s %s", cent_titles[iCent], netp_title, quantity_titles_netp[iQuantity]));
                if (withX) {
                    c_cplot->Print(Form("%s/Contr_%s_%s_%s_cent%dX.pdf", cplot_path, netp, quantity_tags_netp[iQuantity], scan_tag, iCent));
                } else {
                    c_cplot->Print(Form("%s/Contr_%s_%s_%s_cent%d.pdf", cplot_path, netp, quantity_tags_netp[iQuantity], scan_tag, iCent));
                }
            }

            // Barlow check plot, only do most central
            if (iCent == 0) {
                int n_passed = 0;
                int n_failed = 0;
                for (int iCut = 0; iCut < nValidCuts; iCut++) {
                    if (bl_pass[iCut]) {
                        n_passed ++;
                    } else {
                        n_failed ++;
                    }
                }

                tgp->Set(n_passed);
                tgf->Set(n_failed);

                int i_passed = 0;
                int i_failed = 0;
                for (int iCut = 0; iCut < nValidCuts; iCut++) {
                    if (bl_pass[iCut]) {
                        tgp->SetPoint(i_passed, iCut, bl_values[iCut]);
                        tgp->SetPointError(i_passed, 0.0, bl_errors[iCut]);
                        i_passed ++;
                    } else {
                        tgf->SetPoint(i_failed, iCut, bl_values[iCut]);
                        tgf->SetPointError(i_failed, 0.0, bl_errors[iCut]);
                        i_failed ++;
                    }
                }
                // get the limitation of y axis
                double vmax = -999;
                double vmin = 999;
                for (int iCut = 0; iCut < nValidCuts; iCut++) {
                    double vhigh = bl_values[iCut] + bl_errors[iCut];
                    vmax = vhigh > vmax ? vhigh : vmax;
                    double vlow = bl_values[iCut] - bl_errors[iCut];
                    vmin = vlow < vmin ? vlow : vmin;
                }
                const double y_range_fac = 2.5;
                double dist = vmax - vmin;
                double vmean = 0.5 * (vmax + vmin);
                vmax = vmean + y_range_fac * dist/2;
                vmin = vmean - y_range_fac * dist/2;

                c_barlow->Clear();
                c_barlow->cd();
                gStyle->SetOptStat(0);
                gPad->SetBottomMargin(0.2);
                TH1F* frame = (TH1F*)gPad->DrawFrame(-1, vmin, nValidCuts, vmax);

                // set x label
                for (int iCut = 0; iCut < nValidCuts; iCut++) {
                    frame->GetXaxis()->SetBinLabel(frame->FindBin(iCut), cut_labels[iCut]);
                    lat->DrawLatexNDC(0.15, 0.85, quantity_titles_netp[iQuantity]);
                    lat->DrawLatexNDC(0.15, 0.75, netp_title);
                    lat->DrawLatexNDC(0.35, 0.85, cent_titles[iCent]);
                }

                // plot barlow limit boxes
                for (int iCut = 0; iCut < nValidCuts; iCut++) {
                    tline->DrawLine(iCut-0.3, pdef[iCent].val(), iCut+0.3, pdef[iCent].val());
                    tbx->DrawBox(iCut-0.3, pdef[iCent].val() - bl_errors[iCut], iCut+0.3, pdef[iCent].val() + bl_errors[iCut]);
                }

                leg->Draw("same");
                tgp->Draw("epsame");
                tgf->Draw("epsame");

                if (withX) {
                    c_barlow->Print(Form("%s/Barlow_%s_%s_%s_cent%dX.pdf", barlow_path, netp, quantity_tags_netp[iQuantity], scan_tag, iCent));
                } else {
                    c_barlow->Print(Form("%s/Barlow_%s_%s_%s_cent%d.pdf", barlow_path, netp, quantity_tags_netp[iQuantity], scan_tag, iCent));
                }
            }

        }
        // save LATEX code
        if (withX) {
            fmt.Print(Form("%s/%s_%s_%sX.txt", table_path, netp, quantity_tags_netp[iQuantity], scan_tag));
        } else {
            fmt.Print(Form("%s/%s_%s_%s.txt", table_path, netp, quantity_tags_netp[iQuantity], scan_tag));
        }
    }

    // Proton and antiproton
    for (int iPart = 0; iPart < 2; iPart++) {
        for (int iQuantity = 0; iQuantity < nQuantity + nQuantityExtend; iQuantity++) {
            const char* part = ppbar[iPart];
            const char* part_title = ppbar_title[iPart];
            for (int iCent = 0; iCent < nCent; iCent++) {
                system[iCent] = System(part_title, quantity_table_titles[iQuantity], nSource);
                pdef[iCent] = Point();
                pdef[iCent].SetTag(quantity_tags[iQuantity]);
                gl->GetPoint("default", scan_tag, part, quantity_tags[iQuantity], iCent, &pdef[iCent], withX);
                int iBarlowPoint = 0;
                bl_values[iBarlowPoint] = pdef[iCent].GetValue();
                bl_errors[iBarlowPoint] = pdef[iCent].GetError();
                bl_pass[iBarlowPoint] = true;
                iBarlowPoint += 1;
                for (int iSource = 0; iSource < nSource; iSource++) {
                    source[iSource][iCent] = Source(source_tags[iSource], nCuts4Source[iSource], true);
                    source[iSource][iCent].SetDefault(pdef[iCent]);
                    for (int iCut = 0; iCut < nCuts4Source[iSource]; iCut++) {
                        pvrd[iSource][iCut][iCent] = Point();
                        pvrd[iSource][iCut][iCent].SetTag(cut_tags[iSource][iCut]);
                        gl->GetPoint(cut_tags4file[iSource][iCut], scan_tag, part, quantity_tags[iQuantity], iCent, &pvrd[iSource][iCut][iCent], withX);
                        if (nPart[iCent] == 0.0) { nPart[iCent] = gl->GetX(); } // only set <Npart> for the first time we try to get it
                        source[iSource][iCent].AddVaried(pvrd[iSource][iCut][iCent]);

                        // check Barlow test
                        if (iCent == 0) {
                            bl_values[iBarlowPoint] = pvrd[iSource][iCut][iCent].GetValue();
                            bl_errors[iBarlowPoint] = pvrd[iSource][iCut][iCent].GetError();
                            bl_barlow_err[iBarlowPoint] = TMath::Sqrt(fabs(TMath::Power(pvrd[iSource][iCut][iCent].err(), 2) - TMath::Power(pdef[iCent].err(), 2)));
                            bl_pass[iBarlowPoint] = IsPassedBarlow(pdef[iCent], pvrd[iSource][iCut][iCent]);
                            iBarlowPoint += 1;
                        }
                    }
                    system[iCent].AddSource(source[iSource][iCent]);
                }

                // make graph
                tgs[iPart][iQuantity]->SetPointX(iCent, nPart[iCent]);
                tgs[iPart][iQuantity]->SetPointY(iCent, pdef[iCent].GetValue());
                tgs[iPart][iQuantity]->SetPointError(iCent, 0.0, system[iCent].GetSigma());

                // make LATEX
                fmt.LoadSystem(iCent, system[iCent]);

                // contribution plot
                if (iCent == 0 || iCent == 1 || iCent == 8) {
                    tot_err = system[iCent].GetSigma();
                    for (int iSource = 0; iSource < nSource; iSource++) {
                        double tmp = system[iCent].GetSysErrValue(iSource);
                        source_err[iSource] = tmp / tot_err;
                        source_err_quad[iSource] = TMath::Power(source_err[iSource], 2);
                    }
                    c_cplot->Clear();
                    c_cplot->cd();
                    gStyle->SetOptStat(0);
                    for (int iSource = 0; iSource < nSource; iSource++) {
                        h1Contr->GetXaxis()->SetBinLabel(iSource+1, source_tags_contr[iSource]);
                        h1Contr->SetBinContent(iSource+1, source_err[iSource]*100);
                    }
                    h1Contr->Draw("hist");
                    lat->DrawLatexNDC(0.02, 0.92, "#frac{#sigma_{sys. source}}{#sigma_{sys. total}}#times 100");
                    lat->DrawLatexNDC(0.55, 0.92, Form("%s %s %s", cent_titles[iCent], part_title, quantity_titles_netp[iQuantity]));
                    if (withX) {
                        c_cplot->Print(Form("%s/Contr_%s_%s_%s_cent%dX.pdf", cplot_path, part, quantity_tags[iQuantity], scan_tag, iCent));
                    } else {
                        c_cplot->Print(Form("%s/Contr_%s_%s_%s_cent%d.pdf", cplot_path, part, quantity_tags[iQuantity], scan_tag, iCent));
                    }
                }

                // Barlow check plot, only do most central
                if (iCent == 0) {
                    int n_passed = 0;
                    int n_failed = 0;
                    for (int iCut = 0; iCut < nValidCuts; iCut++) {
                        if (bl_pass[iCut]) {
                            n_passed ++;
                        } else {
                            n_failed ++;
                        }
                    }

                    tgp->Set(n_passed);
                    tgf->Set(n_failed);

                    int i_passed = 0;
                    int i_failed = 0;
                    for (int iCut = 0; iCut < nValidCuts; iCut++) {
                        if (bl_pass[iCut]) {
                            tgp->SetPoint(i_passed, iCut, bl_values[iCut]);
                            tgp->SetPointError(i_passed, 0.0, bl_errors[iCut]);
                            i_passed ++;
                        } else {
                            tgf->SetPoint(i_failed, iCut, bl_values[iCut]);
                            tgf->SetPointError(i_failed, 0.0, bl_errors[iCut]);
                            i_failed ++;
                        }
                    }
                    // get the limitation of y axis
                    double vmax = -999;
                    double vmin = 999;
                    for (int iCut = 0; iCut < nValidCuts; iCut++) {
                        double vhigh = bl_values[iCut] + bl_errors[iCut];
                        vmax = vhigh > vmax ? vhigh : vmax;
                        double vlow = bl_values[iCut] - bl_errors[iCut];
                        vmin = vlow < vmin ? vlow : vmin;
                    }
                    const double y_range_fac = 2.5;
                    double dist = vmax - vmin;
                    double vmean = 0.5 * (vmax + vmin);
                    vmax = vmean + y_range_fac * dist/2;
                    vmin = vmean - y_range_fac * dist/2;

                    c_barlow->Clear();
                    c_barlow->cd();
                    gStyle->SetOptStat(0);
                    gPad->SetBottomMargin(0.2);
                    TH1F* frame = (TH1F*)gPad->DrawFrame(-1, vmin, nValidCuts, vmax);

                    // set x label
                    for (int iCut = 0; iCut < nValidCuts; iCut++) {
                        frame->GetXaxis()->SetBinLabel(frame->FindBin(iCut), cut_labels[iCut]);
                        lat->DrawLatexNDC(0.15, 0.85, quantity_titles[iQuantity]);
                        lat->DrawLatexNDC(0.15, 0.75, part_title);
                        lat->DrawLatexNDC(0.35, 0.85, cent_titles[iCent]);
                    }

                    // plot barlow limit boxes
                    for (int iCut = 0; iCut < nValidCuts; iCut++) {
                        tline->DrawLine(iCut-0.3, pdef[iCent].val(), iCut+0.3, pdef[iCent].val());
                        tbx->DrawBox(iCut-0.3, pdef[iCent].val() - bl_errors[iCut], iCut+0.3, pdef[iCent].val() + bl_errors[iCut]);
                    }

                    leg->Draw("same");
                    tgp->Draw("epsame");
                    tgf->Draw("epsame");

                    if (withX) {
                        c_barlow->Print(Form("%s/Barlow_%s_%s_%s_cent%dX.pdf", barlow_path, part, quantity_tags[iQuantity], scan_tag, iCent));
                    } else {
                        c_barlow->Print(Form("%s/Barlow_%s_%s_%s_cent%d.pdf", barlow_path, part, quantity_tags[iQuantity], scan_tag, iCent));
                    }
                }

            }
            // save LATEX code
            if (withX) {
                fmt.Print(Form("%s/%s_%s_%sX.txt", table_path, part, quantity_tags[iQuantity], scan_tag));
            } else {
                fmt.Print(Form("%s/%s_%s_%s.txt", table_path, part, quantity_tags[iQuantity], scan_tag));
            }
        }
    }

    // save ROOT file
    TFile* fout;
    if (withX) {
        fout = new TFile(Form("%s/%sX.root", root_path, scan_tag), "recreate");
    } else {
        fout = new TFile(Form("%s/%s.root", root_path, scan_tag), "recreate");
    }
    fout->cd();
    for (int iQuantity = 0; iQuantity < nQuantityNetp+nQuantityNetpExtend; iQuantity++) {
        tgs_netp[iQuantity]->Write();
    }
    for (int iQuantity = 0; iQuantity < nQuantity+nQuantityExtend; iQuantity++) {
        tgs[0][iQuantity]->Write();
    }
    for (int iQuantity = 0; iQuantity < nQuantity+nQuantityExtend; iQuantity++) {
        tgs[1][iQuantity]->Write();
    }
    fout->Close();
    return 0;
}

bool IsPassedBarlow(Point pdef, Point pvrd) {
    double vdiff2 = TMath::Power(pdef.GetValue() - pvrd.GetValue(), 2);
    double ediff2 = fabs(TMath::Power(pdef.GetError(), 2) - TMath::Power(pvrd.GetError(), 2)); 
    return vdiff2 > ediff2;
}