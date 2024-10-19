#ifndef LIMITS_HPP
#define LIMITS_HPP

#include <limits>

int minIntVal = std::numeric_limits<int>::lowest() + 1;
int maxIntVal = std::numeric_limits<int>::max() - 1;

long minLongVal = std::numeric_limits<long>::lowest() + 1;
long maxLongVal = std::numeric_limits<long>::max() - 1;

#endif
