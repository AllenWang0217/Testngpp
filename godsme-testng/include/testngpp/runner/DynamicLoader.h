#ifndef __TESTNGPP_DYNAMIC_LOADER_H
#define __TESTNGPP_DYNAMIC_LOADER_H

#include <testngpp/runner/TestLoader.h>
#include <testngpp/utils/StringList.h>

TESTNGPP_NS_START

////////////////////////////////////////////////////
struct DynamicLoader : TestLoader
{
   explicit DynamicLoader(const StringList& suites);
   ~DynamicLoader();

   unsigned int getNumOfSuites() const;
   TestSuiteLoader* getSuiteLoader(unsigned int index);

private:
   StringList suites;   
};

////////////////////////////////////////////////////

TESTNGPP_NS_END

#endif

