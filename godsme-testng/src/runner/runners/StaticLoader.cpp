
#include <testngpp/runner/StaticLoader.h>
#include <testngpp/runner/StaticSuiteLoader.h>

TESTNGPP_NS_START
 
/////////////////////////////////////////////////////////////////
unsigned int StaticLoader::getNumOfSuites() const
{
   return 1;
}

/////////////////////////////////////////////////////////////////
TestSuiteLoader* StaticLoader::getSuiteLoader(unsigned int index)
{
    if(index > 0) return 0;
    return new StaticSuiteLoader();
}

/////////////////////////////////////////////////////////////////
TESTNGPP_NS_END

