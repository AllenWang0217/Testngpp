
#include <testngpp/runner/DynamicLoader.h>
#include <testngpp/runner/DynamicSuiteLoader.h>

TESTNGPP_NS_START
 
/////////////////////////////////////////////////////////////////
DynamicLoader::DynamicLoader(const StringList& suites)
   : suites(suites)
{

}

/////////////////////////////////////////////////////////////////
DynamicLoader::~DynamicLoader()
{
}

/////////////////////////////////////////////////////////////////
unsigned int DynamicLoader::getNumOfSuites() const
{
    return suites.size();
}

/////////////////////////////////////////////////////////////////
TestSuiteLoader* DynamicLoader::getSuiteLoader(unsigned int index)
{
    if(index >= suites.size()) return 0;

    return new DynamicSuiteLoader(suites.get()[index]);
}

/////////////////////////////////////////////////////////////////
TESTNGPP_NS_END

