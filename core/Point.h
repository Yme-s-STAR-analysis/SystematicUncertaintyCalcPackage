#ifndef __POINT_CLASS_SYSERR__
#define __POINT_CLASS_SYSERR__

namespace ygse {

    class Point {
        private:
            double value;
            double error;
            const char* tag;

        public:
            Point();
            Point(double, double, const char*);
            ~Point() {}

            // setters
            void SetValue(double);
            void SetError(double);
            void SetTag(const char*);
            double val();
            double err();
            double GetValue();
            double GetError();
            const char* & GetTag();
    };

}

#endif
