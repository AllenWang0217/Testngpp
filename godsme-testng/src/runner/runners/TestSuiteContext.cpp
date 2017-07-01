
#include <testngpp/runner/TestSuiteContext.h>
#include <testngpp/comm/ExceptionKeywords.h>
#include <testngpp/utils/InternalError.h>
#include <testngpp/internal/Error.h>
#include <testngpp/internal/TestSuiteDesc.h>
#include <testngpp/listener/TestResultCollector.h>
#include <testngpp/runner/TestSuiteLoader.h>
#include <testngpp/runner/TagsFilters.h>
#include <testngpp/runner/TestFilter.h>
#include <testngpp/runner/TestFixtureContext.h>

#include <vector>


 
TESTNGPP_NS_START
 
/////////////////////////////////////////////////////////////////

struct TestSuiteContextImpl
{
   TestSuiteContextImpl
      ( TestSuiteLoader* loader
      , TestResultCollector* collector
      , TagsFilters* tagsFilter
      , const TestFilter* filter);

   ~TestSuiteContextImpl();

private:

   void load();
   void loadFixtures( TagsFilters* tagsFilter 
                    , const TestFilter* filter);

   void unloadFixtures();

   void clear();


public:
   TestSuiteLoader* suiteLoader; // Y
   TestResultCollector* resultCollector; //X


   std::vector<TestFixtureContext*> fixtures;
   TestSuiteDesc* suite; //X
};

/////////////////////////////////////////////////////////////////
TestSuiteContextImpl::TestSuiteContextImpl
      ( TestSuiteLoader* loader
      , TestResultCollector* collector
      , TagsFilters* tagsFilter
      , const TestFilter* filter)
      : suiteLoader(loader)
      , resultCollector(collector)
	  , suite(0)
{
   __TESTNGPP_TRY
   {
      load();
      loadFixtures(tagsFilter, filter);
   }
   __TESTNGPP_CATCH_ALL
   {
      clear();
      throw;
   }
   __TESTNGPP_END_TRY
}

/////////////////////////////////////////////////////////////////
TestSuiteContextImpl::~TestSuiteContextImpl()
{
   clear();

   delete suiteLoader;
}

/////////////////////////////////////////////////////////////////
void TestSuiteContextImpl::clear()
{
   unloadFixtures();
   suiteLoader->unload();
}

/////////////////////////////////////////////////////////////////
void TestSuiteContextImpl::loadFixtures
   ( TagsFilters* tagsFilter 
   , const TestFilter* filter)
{
   for(unsigned int i=0; i<suite->getNumberOfTestFixtures(); i++)
   {
      TestFixtureDesc* fixture = suite->getTestFixture(i);
      if(filter->isFixtureMatch((const TestFixtureInfoReader*)fixture))
      {
         fixtures.push_back(new TestFixtureContext(fixture, tagsFilter));
      }
   }
}

/////////////////////////////////////////////////////////////////
void
TestSuiteContextImpl::
unloadFixtures()
{
   for(unsigned int i=0; i < fixtures.size(); i++)
   {
      delete fixtures[i];
   }

   fixtures.clear();
}

/////////////////////////////////////////////////////////////////
void
TestSuiteContextImpl::
load()
{
   __TESTNGPP_TRY
   {
      suite = suiteLoader->load();
   }
   __TESTNGPP_CATCH(std::exception& e)
   {
      resultCollector->addError
         ( "test suite \"" + suiteLoader->getSuitePath() + "\" can't be loaded : " + e.what() );
      throw;
   }
   __TESTNGPP_END_TRY
}

/////////////////////////////////////////////////////////////////
TestSuiteDesc* TestSuiteContext::getSuite() const
{
   return This->suite;
}

/////////////////////////////////////////////////////////////////
unsigned int TestSuiteContext::numberOfFixtures() const
{
   return This->fixtures.size();
}

/////////////////////////////////////////////////////////////////
TestFixtureContext* TestSuiteContext::getFixture(unsigned int index) const
{
   if(index >= This->fixtures.size())
   {
      TESTNGPP_INTERNAL_ERROR(2017);
   }

   return This->fixtures[index];
}

/////////////////////////////////////////////////////////////////
TestSuiteContext::TestSuiteContext
      ( TestSuiteLoader* loader
      , TestResultCollector* collector
      , TagsFilters* tagsFilter
      , const TestFilter* filter
      )
      : This( new TestSuiteContextImpl
               ( loader
               , collector
               , tagsFilter
               , filter)
      )
{
}
            
/////////////////////////////////////////////////////////////////
const std::string& TestSuiteContext::getSuitePath() const
{
   return This->suiteLoader->getSuitePath();
}

/////////////////////////////////////////////////////////////////
TestSuiteContext::
~TestSuiteContext()
{
   delete This;
}

/////////////////////////////////////////////////////////////////
TESTNGPP_NS_END

