#include <limits>

#ifndef LIMITS_HPP
#define LIMITS_HPP

inline int minIntVal = std::numeric_limits<int>::lowest();
inline int maxIntVal = std::numeric_limits<int>::max();

inline long minLongVal = std::numeric_limits<long>::lowest();
inline long maxLongVal = std::numeric_limits<long>::max();

#endif
