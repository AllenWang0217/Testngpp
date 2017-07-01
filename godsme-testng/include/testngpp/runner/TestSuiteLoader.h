#ifndef __TESTNGPP_TEST_SUITE_LOADER_H
#define __TESTNGPP_TEST_SUITE_LOADER_H

#include <testngpp/testngpp.h>
#include <string>

TESTNGPP_NS_START

struct TestSuiteDesc;

////////////////////////////////////////////////////
struct TestSuiteLoader
{
   virtual TestSuiteDesc* load() = 0;
   virtual void unload() = 0;
   virtual const std::string& getSuitePath() const = 0;

   virtual ~TestSuiteLoader() {}
};

////////////////////////////////////////////////////

TESTNGPP_NS_END

#endif

