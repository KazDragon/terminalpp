#include <cppunit/BriefTestProgressListener.h>
#include <cppunit/TestResult.h>
#include <cppunit/TestResultCollector.h>
#include <cppunit/TestRunner.h>
#include <cppunit/extensions/TestFactoryRegistry.h>
#include <cppunit/ui/text/TextTestRunner.h>
#include <cstdlib>

int main()
{
    CppUnit::TestResult controller;

    CppUnit::TestResultCollector result;
    controller.addListener( &result );

    CppUnit::BriefTestProgressListener progressListener;
    controller.addListener( &progressListener );

    CppUnit::TestRunner runner;
    runner.addTest(CppUnit::TestFactoryRegistry::getRegistry().makeTest());

    runner.run(controller);

    return result.wasSuccessful() ? EXIT_SUCCESS : EXIT_FAILURE;
}
