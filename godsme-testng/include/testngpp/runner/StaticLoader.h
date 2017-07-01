#ifndef __TESTNGPP_STATIC_LOADER_H
#define __TESTNGPP_STATIC_LOADER_H

#include <testngpp/runner/TestLoader.h>

TESTNGPP_NS_START

////////////////////////////////////////////////////
struct StaticLoader : TestLoader
{
   unsigned int getNumOfSuites() const;
   TestSuiteLoader* getSuiteLoader(unsigned int index);
};

////////////////////////////////////////////////////

TESTNGPP_NS_END

#endif

