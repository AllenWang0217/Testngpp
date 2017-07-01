#ifndef __TESTNGPP_TEST_LOADER_H
#define __TESTNGPP_TEST_LOADER_H

#include <testngpp/testngpp.h>

TESTNGPP_NS_START

struct TestSuiteLoader;

////////////////////////////////////////////////////
struct TestLoader
{
   virtual unsigned int getNumOfSuites() const = 0;
   virtual TestSuiteLoader* getSuiteLoader(unsigned int index) = 0;

   virtual ~TestLoader() {}
};

////////////////////////////////////////////////////

TESTNGPP_NS_END

#endif

