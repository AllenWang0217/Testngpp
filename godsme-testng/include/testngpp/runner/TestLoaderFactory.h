#ifndef __TESTNGPP_TEST_LOADER_FACTORY_H
#define __TESTNGPP_TEST_LOADER_FACTORY_H

#include <testngpp/testngpp.h>

TESTNGPP_NS_START

struct TestLoader;
struct StringList;

TestLoader* createTestLoader(const StringList& suites);

TESTNGPP_NS_END

#endif

