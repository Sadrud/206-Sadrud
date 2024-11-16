#include <limits>

#ifndef LIMITS_HPP
#define LIMITS_HPP

extern int minIntVal = std::numeric_limits<int>::lowest();
extern int maxIntVal = std::numeric_limits<int>::max();

extern long minLongVal = std::numeric_limits<long>::lowest();
extern long maxLongVal = std::numeric_limits<long>::max();

#endif
