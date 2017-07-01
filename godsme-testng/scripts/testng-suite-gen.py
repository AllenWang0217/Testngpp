#!/usr/bin/python

import sys

def usage() :
  print "testngpp-suite-gen suite-name"


################################################
suite_getter_template = '''
#include <testngpp/internal/TestSuiteDesc.h>

extern "C" DLL_EXPORT TESTNGPP_NS::TestSuiteDesc* ___testngpp_test_suite_desc_getter() {
   static TESTNGPP_NS::TestSuiteDesc test_suite_desc("%s");
   return &test_suite_desc;
}

'''

def generate(name) :
   file = None

   target = name + ".cc"
   try:
      file = open(target, "w")
   except IOError:
      print >> sys.stderr, "open", target, "failed"
      sys.exit(1)

   lines = suite_getter_template % ( name )
   file.writelines(lines)

   if file != None :
      file.close()
  
##########################################################
if __name__ == "__main__":
   if len(sys.argv) != 2:
      usage()
      sys.exit(1)

   generate(sys.argv[1])
