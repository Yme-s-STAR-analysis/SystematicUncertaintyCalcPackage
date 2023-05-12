#include "Point.h"

using ygse::Point;

Point::Point() :value(-999), error(-999) {
    /* ... */
}

Point::Point(double val, double err, const char* label) :value(val), error(err), tag(label){
    /* ... */
}

void Point::SetValue(double val) {
    value = val;
}

void Point::SetError(double val) {
    error = val;
}

void Point::SetTag(const char* label) {
    tag = label;
}

double Point::val() {
    return value;
}

double Point::GetValue() {
    return value;
}

double Point::err() {
    return error;
}

double Point::GetError() {
    return error;
}

const char* & Point::GetTag() {
    return tag;
}