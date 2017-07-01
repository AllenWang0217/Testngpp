
#include <testngpp/runner/loaders/ModuleSuiteFileLoaderFactory.h>
#include <testngpp/runner/loaders/ModuleSuiteFileLoader.h>
#include <testngpp/runner/loaders/ModuleLoaderFactory.h>

TESTNGPP_NS_START

/////////////////////////////////////////////////////////////////
SuiteFileLoader* 
ModuleSuiteFileLoaderFactory::create()
{
   return new ModuleSuiteFileLoader(ModuleLoaderFactory::create());
}

/////////////////////////////////////////////////////////////////

TESTNGPP_NS_END

