#ifndef __TESTNGPP_DYNAMIC_SUITE_LOADER_H
#define __TESTNGPP_DYNAMIC_SUITE_LOADER_H

#include <testngpp/runner/TestSuiteLoader.h>
#include <string>

TESTNGPP_NS_START

struct TestSuiteDesc;
struct SuiteFileLoader;

////////////////////////////////////////////////////
struct DynamicSuiteLoader : TestSuiteLoader
{
   DynamicSuiteLoader(const std::string& path);
   ~DynamicSuiteLoader();

   const std::string& getSuitePath() const;
   TestSuiteDesc* load();
   void unload();

private:
   const std::string path;
   SuiteFileLoader* loader;
};

////////////////////////////////////////////////////

TESTNGPP_NS_END

#endif

