
#ifndef SERIAL
#define SERIAL
struct carData{
    double xAcceleration;
    double yAcceleration;
    char cardinal;
    char interCardinal;
};

struct controllerData{
    bool left;
    bool right;
    bool forward;
    bool reverse;
    bool horn;
};
#endif