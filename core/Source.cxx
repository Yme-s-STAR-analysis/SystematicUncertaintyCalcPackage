#include "TMath.h"

#include "Point.h"
#include "Source.h"

using ygse::Point;
using ygse::Source;

Source::Source() :n(4), i(0), Sigma(-999), cache(false) {
    /* ... */
}

Source::Source(const char* label, int n, bool barlow) :tag(label), n(n), barlow(barlow), i(0), Sigma(-999), cache(false) {
    /* ... */
}

void Source::AddVaried(Point p) {
    if (i < n) {
        pvrd[i] = p;
        i ++;
    }
}

void Source::SetDefault(Point p) {
    pdef = p;
}

double Source::GetSigma() {
    if (!cache) {
        cache = true;

        double vdiff2;
        double ediff2;
        double gamma;

        Sigma = 0.0;
        int n_pass = n; // v2.8 new: the formula is changed
        for (int ii=0; ii<n; ii++) {
            vdiff2 = TMath::Power(pdef.val() - pvrd[ii].val(), 2);
            ediff2 = fabs(TMath::Power(pdef.err(), 2) - TMath::Power(pvrd[ii].err(), 2)); // 2.0: fix this mistake
            if (barlow) {
                gamma = vdiff2 > ediff2 ? vdiff2 - ediff2 : 0.0;
                pass_barlow[ii] = gamma > 0;
                sys_err_raw_arr[ii] = pvrd[ii].val() - pdef.val();
                sys_err_arr[ii] = pass_barlow[ii] ? sys_err_raw_arr[ii] : 0.0;
                Sigma += gamma;
                if (gamma <=0 ) { n_pass -= 1; }
            } else {
                sys_err_raw_arr[ii] = pvrd[ii].val() - pdef.val();
                sys_err_arr[ii] = sys_err_raw_arr[ii];
                pass_barlow[ii] = true;
                Sigma += vdiff2;
            }
        }
        
        n_pass = n_pass == 0 ? 1 : n_pass;
        Sigma = TMath::Sqrt(Sigma*1.0 / n_pass);
        
    }
    return Sigma;
}

int Source::GetN() {
    return n;
}

const char* & Source::GetTag() {
    return tag;
}

double Source::GetSysErrValue(int i) {
    return i < n ? sys_err_arr[i] : -1;
}

double Source::GetSysErrRawValue(int i) {
    return i < n ? sys_err_raw_arr[i] : -1;
}

bool Source::IsCutPassedBarlowCheck(int i) {
    return i < n ? pass_barlow[i] : false;

}

const char* & Source::GetSysErrTag(int i) {
    return i < n ? pvrd[i].GetTag() : ivd_str;
}

double Source::GetDefaultValue() {
    return pdef.GetValue();
}

double Source::GetDefaultError() {
    return pdef.GetError();
}
