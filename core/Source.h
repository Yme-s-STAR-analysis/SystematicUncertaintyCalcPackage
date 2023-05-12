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
            double sys_err_arr[10]; // uncertainty from each CUT
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
            const char* & GetSysErrTag(int);
            double GetDefaultValue();
            double GetDefaultError();
    };

}


#endif