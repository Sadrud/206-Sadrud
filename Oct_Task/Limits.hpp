#include <limits>

#ifndef LIMITS_HPP
#define LIMITS_HPP

int minIntVal = std::numeric_limits<int>::lowest();
int maxIntVal = std::numeric_limits<int>::max();

long minLongVal = std::numeric_limits<long>::lowest();
long maxLongVal = std::numeric_limits<long>::max();

#endif
