
#include <testngpp/runner/DynamicSuiteLoader.h>
#include <testngpp/runner/loaders/ModuleSuiteFileLoaderFactory.h>
#include <testngpp/runner/loaders/SuiteFileLoader.h>
#include <testngpp/utils/StringList.h>

TESTNGPP_NS_START
 
/////////////////////////////////////////////////////////////////
DynamicSuiteLoader::DynamicSuiteLoader(const std::string& path)
   : path(path)
   , loader(ModuleSuiteFileLoaderFactory().create())
{

}

/////////////////////////////////////////////////////////////////
DynamicSuiteLoader::~DynamicSuiteLoader()
{
   unload();
   delete loader;
}

/////////////////////////////////////////////////////////////////
TestSuiteDesc* DynamicSuiteLoader::load()
{
   StringList searchingPaths;

   return loader->load(searchingPaths, path, 0);
}

/////////////////////////////////////////////////////////////////
void DynamicSuiteLoader::unload()
{
   loader->unload();
}

/////////////////////////////////////////////////////////////////
const std::string& DynamicSuiteLoader::getSuitePath() const
{
   return path;
}

/////////////////////////////////////////////////////////////////
TESTNGPP_NS_END

