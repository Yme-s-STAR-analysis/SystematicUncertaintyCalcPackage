#include "TFile.h"
#include "TString.h"
#include "TGraphErrors.h"

#include "Point.h"
#include "GraphLoader.h"

using ygse::Point;

void GraphLoader::GetPoint(const char* cut_tag, const char* file_tag, const char* particle_tag, const char* var_tag, int cent, Point* p) {
    // a quick template
    // cut_tag: dca0p8
    // file_tag: y5
    // particle_tag: Netp
    // var_tag: C1
    // cent: 0
    tf = new TFile(Form("%s/%s.coll/%s.vz0.root", path, cut_tag, file_tag));
    tf->GetObject(Form("%s_%s", particle_tag, var_tag), tg);
    p->SetValue(tg->GetPointY(cent));
    p->SetError(tg->GetErrorY(cent));
    tf->Close();
}