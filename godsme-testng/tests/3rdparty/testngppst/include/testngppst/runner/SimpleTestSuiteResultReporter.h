
#ifndef __TESTNGPPST_SIMPLE_TEST_SUITE_RESULT_REPORTER_H
#define __TESTNGPPST_SIMPLE_TEST_SUITE_RESULT_REPORTER_H

#include <testngppst/testngppst.h>

#include <testngppst/listener/TestSuiteListener.h>
#include <testngppst/listener/TestSuiteResultReporter.h>

TESTNGPPST_NS_START

struct TestCaseResultReporter;
struct SimpleTestSuiteResultReporterImpl;

struct SimpleTestSuiteResultReporter
   : public TestSuiteResultReporter
   , public TestSuiteListener
{
	SimpleTestSuiteResultReporter(TestCaseResultReporter*);
	~SimpleTestSuiteResultReporter();

   ////////////////////////////////////////////////////////////
   int getNumberOfTestCases(TestSuiteInfoReader*) const;
   int getNumberOfSuccessfulTestCases(TestSuiteInfoReader*) const;
   int getNumberOfUnsuccessfulTestCases(TestSuiteInfoReader*) const;
   int getNumberOfFailedTestCases(TestSuiteInfoReader*) const;
   int getNumberOfErrorTestCases(TestSuiteInfoReader*) const;
   int getNumberOfSkippedTestCases(TestSuiteInfoReader*) const;
   int getNumberOfCrashedTestCases(TestSuiteInfoReader*) const;

   int getNumberOfFixtures(TestSuiteInfoReader*) const;
   int getNumberOfFixtureErrors(TestSuiteInfoReader*) const;
   int getNumberOfFixtureFailures(TestSuiteInfoReader*) const;

   int getNumberOfSuiteErrors(TestSuiteInfoReader*) const;

   ////////////////////////////////////////////////////////////
   void addCaseError(const TestCaseInfoReader*, const std::string&);
   void addCaseCrash(const TestCaseInfoReader*);
   void addCaseSkipped(const TestCaseInfoReader*);
   void addCaseFailure(const TestCaseInfoReader*, const AssertionFailure&);

   void startTestCase(const TestCaseInfoReader*);
   void endTestCase(const TestCaseInfoReader*, unsigned int, unsigned int);

   void startTestFixture(TestFixtureInfoReader*);
   void endTestFixture(TestFixtureInfoReader*);
   void addFixtureError(TestFixtureInfoReader*, const std::string&);
   void addFixtureFailure(TestFixtureInfoReader*, const AssertionFailure&);

   void startTestSuite(TestSuiteInfoReader*);
   void endTestSuite(TestSuiteInfoReader*);
   void addSuiteError(TestSuiteInfoReader*, const std::string&);

private:
   SimpleTestSuiteResultReporterImpl* This;

};

TESTNGPPST_NS_END

#endif

