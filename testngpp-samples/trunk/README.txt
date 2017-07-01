1. Open the solution file "win32-projects\MyProject\MyProject.sln" in Visual Studio 2009

2. Set the debugging "Command Line" of the project "MyProjectTest" as:

 $(SolutionDir)..\..\testngpp\bin\testngpp-runner.exe
 
3. Set the debugging "Command Arguments" of the project "MyProjectTest" as:

 $(OutDir)\$(TargetName) -L"$(SolutionDir)..\..\testngpp\testngpp\listener" -l"testngppstdoutlistener -c"
 
 You can modify the command arguments. For instance:
 
 $(OutDir)\$(TargetName) -L"$(SolutionDir)..\..\testngpp\testngpp\listener" -l"testngppstdoutlistener -c" -s
 
 "-s" means running test in sandbox mode. Or,
 
 $(OutDir)\$(TargetName) -L"$(SolutionDir)..\..\testngpp\testngpp\listener" -l"testngppstdoutlistener -c" -l"testngppstdoutxmllistener result.xml"
 
 to a new listener "xml listener", the test result will be written to file "result.xml". Or,
 
 $(OutDir)\$(TargetName) -L"$(SolutionDir)..\..\testngpp\testngpp\listener" -l"testngppstdoutlistener -c -v"
 
 to change the TestNG++ Stdout Listener to verbose mode.
 
 About the options of testngpp-runner, testngppstdoutlistener and testngppstdoutxmllistener, please read the TestNG++ user manual.
 
4. Set the project "MyProjectTest" as "Startup Project"

5. Press "CTL + F5" to build and run tests.

6. You can try to add new tests, new test files