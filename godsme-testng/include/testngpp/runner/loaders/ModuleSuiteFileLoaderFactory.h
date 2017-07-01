
#ifndef __TESTNGPP_MODULE_SUITE_FILE_LOADER_FACTORY_H
#define __TESTNGPP_MODULE_SUITE_FILE_LOADER_FACTORY_H

#include <testngpp/testngpp.h>

#include <testngpp/runner/loaders/SuiteFileLoaderFactory.h>

TESTNGPP_NS_START

struct ModuleSuiteFileLoaderFactory
   : public SuiteFileLoaderFactory
{
   SuiteFileLoader* create();
};

TESTNGPP_NS_END

#endif

