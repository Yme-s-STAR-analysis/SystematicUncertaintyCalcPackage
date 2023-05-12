#ifndef __FSYSTEM_CLASS_SYSERR__
#define __FSYSTEM_CLASS_SYSERR__

#include <fstream>

#include "Point.h"
#include "Source.h"
#include "System.h"

namespace ygse {

    class FormatSystem {
        private:
            static const int nCent = 9;
            ygse::System systems[nCent];
            const char* fmt;

        public: 
            FormatSystem();
            ~FormatSystem() {}

            void LoadSystem(int, ygse::System);
            // void Print();
            void Print(const char*);
            void Print(const char*, const char*, const char*);
            void SetFormat(const char*);
            const char* GetFormattedFloat(double);
    };

}

#endif