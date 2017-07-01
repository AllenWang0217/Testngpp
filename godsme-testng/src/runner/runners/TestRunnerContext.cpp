
#include <vector>

#include <testngpp/comm/ExceptionKeywords.h>

#include <testngpp/listener/TestResultCollector.h>

#include <testngpp/runner/TagsFilters.h>
#include <testngpp/runner/TestFilter.h>
#include <testngpp/runner/TestSuiteContext.h>
#include <testngpp/runner/TestRunnerContext.h>
#include <testngpp/runner/TestLoader.h>
#include <testngpp/runner/TestSuiteLoader.h>

TESTNGPP_NS_START

/////////////////////////////////////////////////////////////////
struct TestRunnerContextImpl
{
   TestRunnerContextImpl
      ( TestLoader*
      , TestResultCollector* collector
      , TagsFilters* tagsFilter
      , const TestFilter* filter);

   ~TestRunnerContextImpl();

private:

   void
   loadSuite
      ( TestSuiteLoader*
      , TestResultCollector* collector
      , TagsFilters* tagsFilter
      , const TestFilter* filter);

   void
   loadSuites
      ( TestLoader*
      , TestResultCollector* collector
      , TagsFilters* tagsFilter
      , const TestFilter* filter);

   void
   unloadSuites();

public:

   std::vector<TestSuiteContext*> suites;
};

/////////////////////////////////////////////////////////////////
TestRunnerContextImpl::
TestRunnerContextImpl
      ( TestLoader* testLoader
      , TestResultCollector* collector
      , TagsFilters* tagsFilter
      , const TestFilter* filter)
{

   loadSuites( testLoader
             , collector
             , tagsFilter
             , filter);
}

/////////////////////////////////////////////////////////////////
TestRunnerContextImpl::
~TestRunnerContextImpl()
{
   unloadSuites();
}

/////////////////////////////////////////////////////////////////
void
TestRunnerContextImpl::
loadSuite
      ( TestSuiteLoader* loader
      , TestResultCollector* collector
      , TagsFilters* tagsFilter
      , const TestFilter* filter)
{
   __TESTNGPP_TRY
   {
      TestSuiteContext* suite = \
         new TestSuiteContext( loader
                             , collector
                             , tagsFilter
                             , filter);

      suites.push_back(suite);
   }
   __TESTNGPP_CATCH_ALL
   {
      delete loader;
   }
   __TESTNGPP_END_TRY
}

/////////////////////////////////////////////////////////////////
void
TestRunnerContextImpl::
loadSuites( TestLoader* testLoader
          , TestResultCollector* collector
          , TagsFilters* tagsFilter
          , const TestFilter* filter)
{
   for(unsigned int i=0; i < testLoader->getNumOfSuites(); i++)
   {
      TestSuiteLoader* loader = testLoader->getSuiteLoader(i);
      loadSuite(loader, collector, tagsFilter, filter);
   }
}

/////////////////////////////////////////////////////////////////
void
TestRunnerContextImpl::
unloadSuites()
{
   for(unsigned int i=0; i<suites.size(); i++)
   {
      delete suites[i];
   }

   suites.clear();
}

/////////////////////////////////////////////////////////////////
TestRunnerContext::
TestRunnerContext
      ( TestLoader* testLoader
      , TestResultCollector* collector
      , TagsFilters* tagsFilter
      , const TestFilter* filter)
      : This( new TestRunnerContextImpl
               ( testLoader
               , collector
               , tagsFilter
               , filter))
{
}

/////////////////////////////////////////////////////////////////
TestRunnerContext::
~TestRunnerContext()
{
   delete This;
}

/////////////////////////////////////////////////////////////////
TestSuiteContext*
TestRunnerContext::
getSuite(unsigned int index) const
{
   if(index >= numberOfSuites())
   {
      return 0;
   }

   return This->suites[index];
}

/////////////////////////////////////////////////////////////////
unsigned int
TestRunnerContext::
numberOfSuites() const
{
   return This->suites.size();
}

/////////////////////////////////////////////////////////////////

TESTNGPP_NS_END

