
#ifndef __TESTNGPP_MODULE_SUITE_FILE_LOADER_H
#define __TESTNGPP_MODULE_SUITE_FILE_LOADER_H

#include <testngpp/runner/loaders/SuiteFileLoader.h>

TESTNGPP_NS_START

struct ModuleLoader;
struct TestSuiteDesc;
struct TestSuiteDescEntryNameGetter;
struct ModuleSuiteFileLoaderImpl;

struct ModuleSuiteFileLoader : public SuiteFileLoader
{
   ModuleSuiteFileLoader(ModuleLoader* loader);
   ~ModuleSuiteFileLoader();

   TestSuiteDesc*
   load( const StringList& searchingPaths
       , const std::string& path
       , TestSuiteDescEntryNameGetter* nameGetter);

   void unload();

private:
   ModuleSuiteFileLoaderImpl* This;
};

TESTNGPP_NS_END

#endif

