
#ifndef __TESTNGPP_SUITE_FILE_LOADER_FACTORY_H
#define __TESTNGPP_SUITE_FILE_LOADER_FACTORY_H

#include <testngpp/testngpp.h>

TESTNGPP_NS_START

struct SuiteFileLoader;

struct SuiteFileLoaderFactory
{
   virtual SuiteFileLoader* create() = 0;

   virtual ~SuiteFileLoaderFactory() {}
};

TESTNGPP_NS_END

#endif

