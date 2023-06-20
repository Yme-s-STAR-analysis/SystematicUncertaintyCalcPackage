#include "TMath.h"

#include "Point.h"
#include "Source.h"
#include "System.h"

using ygse::Point;
using ygse::Source;
using ygse::System;

System::System() :n(5), i(0), Sigma(0), cache(false){
    /* ... */
}

System::System(const char* label, int n) :n(n), i(0), Sigma(0), cache(false), tag1(label), tag2(label){
    /* ... */
}
System::System(const char* label1, const char* label2, int n) :n(n), i(0), Sigma(0), cache(false), tag1(label1), tag2(label2){
    /* ... */
}

void System::AddSource(Source s) {
    if (i < n) {
        sources[i] = s;
        i ++;
    }
}

double System::GetSigma() {
    if (!cache) {
        cache = true;

        Sigma = 0.0;
        for (int ii=0; ii<n; ii++) {
            sys_err_arr[ii] = sources[ii].GetSigma();
            Sigma += TMath::Power(sources[ii].GetSigma(), 2);
        }

        Sigma = TMath::Sqrt(Sigma);
    }
    return Sigma;
}

int System::GetN() {
    return n;
}

int System::GetN(int i) {
    return sources[i].GetN();
}

const char* & System::GetTag() {
    return tag1;
}

const char* & System::GetTag1() {
    return tag1;
}

const char* & System::GetTag2() {
    return tag2;
}

double System::GetSysErrValue(int i) {
    /* 
        The Sigma from source i.
    */

    if (!cache) { // make sure that the errors from each source and cut are calculated
        GetSigma();
    } 
    if (i < n) {
        return sys_err_arr[i];
    } else {
        return -1;
    }
}

const char* & System::GetSysErrTag(int i) {
    /*
        The tag of source i.
    */
    if (i < n) {
        return sources[i].GetTag();
    } else {
        return ivd_str;
    }
}

double System::GetSysErrValue(int i, int j) {
    /* 
        The Sigma from source i.
    */
    if (i >= n) {
        return -1;
    } else if (j >= sources[i].GetN()) {
        return -1;
    } else {
        return sources[i].GetSysErrValue(j);
    }
}

double System::GetSysErrRawValue(int i, int j) {
    /* 
        The Sigma from source i, not consider barlow check.
    */
    if (i >= n) {
        return -1;
    } else if (j >= sources[i].GetN()) {
        return -1;
    } else {
        return sources[i].GetSysErrRawValue(j);
    }
}

bool System::IsCutPassedBarlowCheck(int i, int j) {
    /*
        Get if a cut passed Barlow Check.
    */
    if (i >= n) {
        return -1;
    } else if (j >= sources[i].GetN()) {
        return -1;
    } else {
        return sources[i].IsCutPassedBarlowCheck(j);
    }
}

const char* & System::GetSysErrTag(int i, int j) {
    /*
        The tag of source i, cut j.
    */
    if (!cache) { // make sure that the errors from each source and cut are calculated
        GetSigma();
    } 
    if (i >= n) {
        return ivd_str;
    } else if (j >= sources[i].GetN()) {
        return ivd_str;
    } else {
        return sources[i].GetSysErrTag(j);
    }
}

double System::GetDefaultValue() {
    return sources[0].GetDefaultValue();
}

double System::GetDefaultError() {
    return sources[0].GetDefaultError();
}