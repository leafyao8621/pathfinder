#include <math.h>
#include "util.h"

double calc_dist(double lon1, double lat1, double lon2, double lat2) {
    lon1 = 0.01745329252 * lon1;
    lat1 = 0.01745329252 * lat1;
    lon2 = 0.01745329252 * lon2;
    lat2 = 0.01745329252 * lat2;
    double latcos1 = cos(lat1);
    double x1 = latcos1 * cos(lon1);
    double y1 = latcos1 * sin(lon1);
    double z1 = sin(lat1);
    double latcos2 = cos(lat2);
    double x2 = latcos2 * cos(lon2);
    double y2 = latcos2 * sin(lon2);
    double z2 = sin(lat2);
    double x = x1 - x2;
    double y = y1 - y2;
    double z = z1 - z2;
    double sl = x * x + y * y + z * z;
    printf("%lf\n", lat1);
    return acos((2 - sl) / 2) * 6378;
}
