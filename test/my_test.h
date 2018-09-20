#ifndef MY_TEST_H
#define MY_TEST_H

#include <stdexcept>
#include <vector>
#include <iostream>

#include <util.h>

/**
 * @brief custom error class
 */
class AssertionFailedException : public std::runtime_error {
  public:
    explicit AssertionFailedException(const std::string& what)
        : std::runtime_error(what)
    {
    }
};

/**
 * Custom assertion which throws exception to be caught by test framework
 */
#define ASSERT(x)                                       \
do {                                                    \
    if (!LIKELY(x)) {                                   \
        throw AssertionFailedException("Condition \""#x"\" violated");\
    }                                                   \
} while(false)

#define ASSERT_EQ(x, y) ASSERT((x) == (y))

#define ASSERT_DBL_EQ(x, y) ASSERT(Util::IsZero((x) - (y)))

/**
 * Declaration of TestSuite interface.
 *
 * Ugly, to be refactored
 */
#define TEST_SUITE(SUITE_NAME)                          \
namespace MyTestSuite_##SUITE_NAME {                    \
    class TestBase;                                     \
    class TestRunner;                                   \
                                                        \
    class TestSet {                                     \
        friend class TestRunner;                        \
      private:                                          \
        std::vector<TestBase*> Tests;                   \
                                                        \
      private:                                          \
        TestSet() = default;                            \
                                                        \
      private:                                          \
        static TestSet Instance;                        \
                                                        \
      public:                                           \
        static void AddTest(TestBase* test) {           \
            TestSet::Instance.Tests.push_back(test);    \
        }                                               \
    };                                                  \
                                                        \
    TestSet TestSet::Instance;                          \
                                                        \
    class TestBase {                                    \
        friend class TestSet;                           \
        friend class TestRunner;                        \
      protected:                                        \
        explicit TestBase(std::string test)             \
            : TestName(std::move(test))                 \
        {                                               \
            try {                                       \
                TestSet::AddTest(this);                 \
            } catch(const std::exception& e) {          \
                std::cout << "Unable to add test \"" << test << "\": " << e.what(); \
            }                                           \
        }                                               \
                                                        \
      protected:                                        \
        virtual void Run() = 0;                         \
                                                        \
      private:                                          \
        int RunTest() {                                 \
            try {                                       \
                Run();                                  \
                return 1;                               \
            } catch (const AssertionFailedException& exception) { \
                std::cout << "Test \"" << TestName << "\" failed: " << exception.what() << std::endl; \
                return 0;                               \
            }                                           \
        }                                               \
      private:                                          \
        std::string TestName;                           \
    };                                                  \
                                                        \
    class TestRunner {                                  \
      public:                                           \
        static void RunTests() {                        \
            std::cout << "=====================" << std::endl << "Test Suite \""#SUITE_NAME"\" run" << std::endl; \
            size_t successfulTests = 0;                 \
            size_t totalTests = TestSet::Instance.Tests.size(); \
            for (auto* test : TestSet::Instance.Tests) { \
                successfulTests += test->RunTest();     \
            }                                           \
                                                        \
            std::cout << "Testing finished: " << successfulTests << " passed; " \
                                              << totalTests - successfulTests << " failed; " \
                                              << totalTests << " total" << std::endl; \
            std::cout << "=====================" << std::endl; \
        }                                               \
    };                                                  \
}                                                       \
                                                        \
using MyTestSuite_##SUITE_NAME::TestRunner;             \
                                                        \
namespace MyTestSuite_##SUITE_NAME

#define TEST_CASE(CASE_NAME)                            \
class MyTestCase_##CASE_NAME : private TestBase {       \
  private:                                              \
    explicit MyTestCase_##CASE_NAME() : TestBase(#CASE_NAME) {} \
  private:                                              \
    void Run() override final;                          \
                                                        \
  private:                                              \
    static MyTestCase_##CASE_NAME Instance;             \
};                                                      \
                                                        \
MyTestCase_##CASE_NAME MyTestCase_##CASE_NAME::Instance;\
                                                        \
void MyTestCase_##CASE_NAME::Run()

#endif /// MY_TEST_H
