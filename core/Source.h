#ifndef __SOURCE_CLASS_SYSERR__
#define __SOURCE_CLASS_SYSERR__

#include "Point.h"

namespace ygse {

    class Source {
        private:
            bool barlow;
            int n;
            int i;
            Point pdef; // default points
            Point pvrd[10]; // varied points
            double sys_err_raw_arr[10]; // uncertainty from each CUT, will not set barlow check not passed values as 0
            double sys_err_arr[10]; // uncertainty from each CUT
            bool pass_barlow[10]; // record if the cut passed barlow check, will be true if passed
            const char* tag;
            double Sigma;
            bool cache;

        public:
            Source();
            Source(const char*, int, bool);
            ~Source() {}

            const char* ivd_str = "invalid"; // invalid tag
            void AddVaried(Point);
            void SetDefault(Point);
            double GetSigma();
            int GetN();
            const char* & GetTag();
            double GetSysErrValue(int);
            double GetSysErrRawValue(int);
            bool IsCutPassedBarlowCheck(int);
            const char* & GetSysErrTag(int);
            double GetDefaultValue();
            double GetDefaultError();
    };

}


#endif