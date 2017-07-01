#ifndef __TESTNGPP_STATIC_SUITE_LOADER_H
#define __TESTNGPP_STATIC_SUITE_LOADER_H

#include <testngpp/runner/TestSuiteLoader.h>
#include <string>

TESTNGPP_NS_START

struct TestSuiteDesc;
struct SuiteFileLoader;

////////////////////////////////////////////////////
struct StaticSuiteLoader : TestSuiteLoader
{
   StaticSuiteLoader();
   ~StaticSuiteLoader();

   const std::string& getSuitePath() const;
   TestSuiteDesc* load();
   void unload();
};

////////////////////////////////////////////////////

TESTNGPP_NS_END

#endif

