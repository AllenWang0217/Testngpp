
#ifndef __TESTNGPPST_TESTCASE_SANDBOX_RESULT_REPORTER_H
#define __TESTNGPPST_TESTCASE_SANDBOX_RESULT_REPORTER_H

#include <testngppst/testngppst.h>
#include <testngppst/listener/TestCaseResultCollector.h>

TESTNGPPST_NS_START

struct TestCaseSandboxResultReporterImpl;
struct WrittableChannel;

struct TestCaseSandboxResultReporter
   : public TestCaseResultCollector
{
   TestCaseSandboxResultReporter(WrittableChannel* channel);
   ~TestCaseSandboxResultReporter();

   void addCaseInfo(const TestCaseInfoReader*, const Info&);
   void addCaseWarning(const TestCaseInfoReader*, const Warning&);
   void addCaseCrash(const TestCaseInfoReader*) {}
   void addCaseSkipped(const TestCaseInfoReader*) {}
   void addCaseError(const TestCaseInfoReader*, const std::string&); 
   void addCaseFailure(const TestCaseInfoReader*, const AssertionFailure&);

   void startTestCase(const TestCaseInfoReader*); 
   void endTestCase(const TestCaseInfoReader*, unsigned int, unsigned int);

private:
   TestCaseSandboxResultReporterImpl* This;
};

TESTNGPPST_NS_END

#endif

