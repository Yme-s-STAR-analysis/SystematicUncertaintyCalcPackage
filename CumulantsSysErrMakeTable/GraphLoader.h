#include "TFile.h"
#include "TGraphErrors.h"

#include "Point.h"

class GraphLoader {

    private:
        TGraphErrors* tg;
        TFile* tf;
        const char* path;
        double x; // point x (<Npart> value)
        
    public:
        GraphLoader(const char* folder) :path(folder) {
            x = 0.0;
        }
        ~GraphLoader() {}

        void GetPoint(const char*, const char*, const char*, const char*, int, ygse::Point*, bool);
        double GetX() { return x; }
};