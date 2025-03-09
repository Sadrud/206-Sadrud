

#include "test_core.hpp"

size_t TestSuite::numFailedTests = 0;
size_t TestSuite::totalNumTests = 0;
std::mutex TestSuite::statsMutex;

