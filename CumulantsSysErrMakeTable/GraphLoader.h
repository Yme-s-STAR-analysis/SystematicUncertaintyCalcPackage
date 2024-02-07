#include "TFile.h"
#include "TGraphErrors.h"

#include "Point.h"

class GraphLoader {

    private:
        TGraphErrors* tg;
        TFile* tf;
        const char* path;
        
    public:
        GraphLoader(const char* folder) :path(folder) {
            /* ... */
        }
        ~GraphLoader() {}

        void GetPoint(const char*, const char*, const char*, const char*, int, ygse::Point*, bool);
};