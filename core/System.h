#ifndef __SYSTEM_CLASS_SYSERR__
#define __SYSTEM_CLASS_SYSERR__

#include "Point.h"
#include "Source.h"

namespace ygse {

    class System {
        private:
            int n;
            int i;
            Source sources[10];
            double sys_err_arr[10]; // uncertainty from each SOURCE
            const char* tag1; 
            const char* tag2; 
            double Sigma; // final systematical uncertainty
            bool cache;

        public:
            System();
            System(const char*, int);
            System(const char*, const char*, int);
            ~System() {}

            const char* ivd_str = "invalid"; // invalid tag
            void AddSource(Source);
            double GetSigma();
            int GetN();
            int GetN(int);
            const char* & GetTag();
            const char* & GetTag1();
            const char* & GetTag2();
            double GetSysErrValue(int);
            const char* & GetSysErrTag(int);
            double GetSysErrValue(int, int);
            double GetSysErrRawValue(int, int);
            bool IsCutPassedBarlowCheck(int, int);
            const char* & GetSysErrTag(int, int);
            double GetDefaultValue();
            double GetDefaultError();
    };

}


#endif