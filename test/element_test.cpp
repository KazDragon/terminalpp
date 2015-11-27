#include "terminalpp/element.hpp"
#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>

class element_test : public CppUnit::TestFixture
{
public :
    CPPUNIT_TEST_SUITE(element_test);
        CPPUNIT_TEST(can_implicitly_construct_element_from_glyph);
        CPPUNIT_TEST(can_implicitly_construct_element_from_char);
        CPPUNIT_TEST(can_aggregate_initialize_from_glyph);
        CPPUNIT_TEST(can_aggregate_initialize_from_char);
    CPPUNIT_TEST_SUITE_END();
    
private :
    void can_implicitly_construct_element_from_glyph();
    void can_implicitly_construct_element_from_char();
    void can_aggregate_initialize_from_glyph();
    void can_aggregate_initialize_from_char();
};

CPPUNIT_TEST_SUITE_REGISTRATION(element_test);

void element_test::can_implicitly_construct_element_from_glyph()
{
    auto elem = [](terminalpp::element const &elem)
    {
        return elem;
    }(terminalpp::glyph('x'));
    
    CPPUNIT_ASSERT_EQUAL('x', elem.glyph_.character_);
}

void element_test::can_implicitly_construct_element_from_char()
{
    auto elem = [](terminalpp::element const &elem)
    {
        return elem;
    }('x');
    
    CPPUNIT_ASSERT_EQUAL('x', elem.glyph_.character_);
}

void element_test::can_aggregate_initialize_from_glyph()
{
    auto elem = [](terminalpp::element const &elem)
    {
        return elem;
    }({terminalpp::glyph('x')});
    
    CPPUNIT_ASSERT_EQUAL('x', elem.glyph_.character_);
}

void element_test::can_aggregate_initialize_from_char()
{
    auto elem = [](terminalpp::element const &elem)
    {
        return elem;
    }({'x'});
    
    CPPUNIT_ASSERT_EQUAL('x', elem.glyph_.character_);
}
