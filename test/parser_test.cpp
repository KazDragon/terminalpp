#include "terminalpp/detail/parser.hpp"
#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>

class parser_test : public CppUnit::TestFixture
{
public :
    CPPUNIT_TEST_SUITE(parser_test);
        CPPUNIT_TEST(parse_empty_string_yields_nothing);
        CPPUNIT_TEST(parse_character_yields_virtual_key);
        CPPUNIT_TEST(parse_command_yields_command);
        CPPUNIT_TEST(parse_command_with_arguments_yields_command_with_arguments);
        CPPUNIT_TEST(parse_meta_command_yields_meta_command);
        CPPUNIT_TEST(parse_mouse_command_yields_mouse_report);
        CPPUNIT_TEST(parse_non_mouse_similar_command_yields_command);
        CPPUNIT_TEST(parse_partial_command_yields_nothing);
        CPPUNIT_TEST(parse_partial_mouse_command_yields_nothing);
        /*
        TODO list
        parse upper case character yields shift modifier
        -- all above for both 7- and 8- bit.
        */
        CPPUNIT_TEST(parse_8bit_ind_command_yields_ind_command);
        CPPUNIT_TEST(parse_8bit_nel_command_yields_nel_command);
        CPPUNIT_TEST(parse_8bit_hts_command_yields_hts_command);
        CPPUNIT_TEST(parse_8bit_ri_command_yields_ri_command);
        CPPUNIT_TEST(parse_8bit_ss2_command_yields_ss2_command);
        CPPUNIT_TEST(parse_8bit_ss3_command_yields_ss3_command);
        CPPUNIT_TEST(parse_8bit_dcs_command_yields_dcs_command);
        CPPUNIT_TEST(parse_8bit_spa_command_yields_spa_command);
        CPPUNIT_TEST(parse_8bit_epa_command_yields_epa_command);
        CPPUNIT_TEST(parse_8bit_sos_command_yields_sos_command);
        CPPUNIT_TEST(parse_8bit_decid_command_yields_decid_command);
        CPPUNIT_TEST(parse_8bit_csi_command_yields_csi_command);
        CPPUNIT_TEST(parse_8bit_st_command_yields_st_command);
        CPPUNIT_TEST(parse_8bit_osc_command_yields_osc_command);
        CPPUNIT_TEST(parse_8bit_pm_command_yields_pm_command);
        CPPUNIT_TEST(parse_8bit_apc_command_yields_apc_command);
    CPPUNIT_TEST_SUITE_END();

private :
    void parse_empty_string_yields_nothing();
    void parse_character_yields_virtual_key();
    void parse_command_yields_command();
    void parse_command_with_arguments_yields_command_with_arguments();
    void parse_meta_command_yields_meta_command();
    void parse_mouse_command_yields_mouse_report();
    void parse_non_mouse_similar_command_yields_command();
    void parse_partial_command_yields_nothing();
    void parse_partial_mouse_command_yields_nothing();

    void parse_8bit_ind_command_yields_ind_command();
    void parse_8bit_nel_command_yields_nel_command();
    void parse_8bit_hts_command_yields_hts_command();
    void parse_8bit_ri_command_yields_ri_command();
    void parse_8bit_ss2_command_yields_ss2_command();
    void parse_8bit_ss3_command_yields_ss3_command();
    void parse_8bit_dcs_command_yields_dcs_command();
    void parse_8bit_spa_command_yields_spa_command();
    void parse_8bit_epa_command_yields_epa_command();
    void parse_8bit_sos_command_yields_sos_command();
    void parse_8bit_decid_command_yields_decid_command();
    void parse_8bit_csi_command_yields_csi_command();
    void parse_8bit_st_command_yields_st_command();
    void parse_8bit_osc_command_yields_osc_command();
    void parse_8bit_pm_command_yields_pm_command();
    void parse_8bit_apc_command_yields_apc_command();
};

CPPUNIT_TEST_SUITE_REGISTRATION(parser_test);

void parser_test::parse_empty_string_yields_nothing()
{
    std::string input = "";
    auto begin = input.begin();
    auto end = input.end();

    auto result = terminalpp::detail::parse(begin, end);

    CPPUNIT_ASSERT_EQUAL(size_t{0}, result.size());
    CPPUNIT_ASSERT(begin == end);
}

void parser_test::parse_character_yields_virtual_key()
{
    std::string input = "z";
    auto begin = input.begin();
    auto end = input.end();

    auto expected = std::vector<terminalpp::token>{
        terminalpp::virtual_key {
            terminalpp::VK_LOWERCASE_Z,
            0,
            { input[0] }
        }
    };

    auto result = terminalpp::detail::parse(begin, end);

    CPPUNIT_ASSERT_EQUAL(expected.size(), result.size());
    CPPUNIT_ASSERT_EQUAL(
        boost::get<terminalpp::virtual_key>(expected[0]),
        boost::get<terminalpp::virtual_key>(result[0]));
    CPPUNIT_ASSERT(begin == end);
}

void parser_test::parse_command_yields_command()
{
    std::string input = "\x1B[H";
    auto begin = input.begin();
    auto end = input.end();

    auto expected = std::vector<terminalpp::token>{
        terminalpp::ansi::control_sequence {
            '[',
            'H',
            false,
            { 0 }
        }
    };

    auto result = terminalpp::detail::parse(begin, end);

    CPPUNIT_ASSERT_EQUAL(expected.size(), result.size());
    CPPUNIT_ASSERT_EQUAL(
        boost::get<terminalpp::ansi::control_sequence>(expected[0]),
        boost::get<terminalpp::ansi::control_sequence>(result[0]));
    CPPUNIT_ASSERT(begin == end);
}

void parser_test::parse_command_with_arguments_yields_command_with_arguments()
{
    std::string input = "\x1B[22;33H";
    auto begin = input.begin();
    auto end = input.end();

    auto expected = std::vector<terminalpp::token> {
        terminalpp::ansi::control_sequence {
            '[',
            'H',
            false,
            { 22, 33 }
        }
    };

    auto result = terminalpp::detail::parse(begin, end);

    CPPUNIT_ASSERT_EQUAL(expected.size(), result.size());
    CPPUNIT_ASSERT_EQUAL(
        boost::get<terminalpp::ansi::control_sequence>(expected[0]),
        boost::get<terminalpp::ansi::control_sequence>(result[0]));
    CPPUNIT_ASSERT(begin == end);
}

void parser_test::parse_meta_command_yields_meta_command()
{
    std::string input = "\x1B\x1B[A";
    auto begin = input.begin();
    auto end = input.end();

    auto expected = std::vector<terminalpp::token> {
        terminalpp::ansi::control_sequence {
            '[',
            'A',
            true,
            { 0 }
        }
    };

    auto result = terminalpp::detail::parse(begin, end);

    CPPUNIT_ASSERT_EQUAL(expected.size(), result.size());
    CPPUNIT_ASSERT_EQUAL(
        boost::get<terminalpp::ansi::control_sequence>(expected[0]),
        boost::get<terminalpp::ansi::control_sequence>(result[0]));
    CPPUNIT_ASSERT(begin == end);
}

void parser_test::parse_mouse_command_yields_mouse_report()
{
    std::string input = "\x1B[M @B";
    auto begin = input.begin();
    auto end = input.end();

    auto expected = std::vector<terminalpp::token> {
        terminalpp::ansi::mouse::report {
            terminalpp::ansi::mouse::report::LEFT_BUTTON_DOWN,
            32,
            34
        }
    };

    auto result = terminalpp::detail::parse(begin, end);

    CPPUNIT_ASSERT_EQUAL(expected.size(), result.size());
    CPPUNIT_ASSERT_EQUAL(
        boost::get<terminalpp::ansi::mouse::report>(expected[0]),
        boost::get<terminalpp::ansi::mouse::report>(result[0]));
    CPPUNIT_ASSERT(begin == end);
}

void parser_test::parse_non_mouse_similar_command_yields_command()
{
    std::string input = "\x1B?M";
    auto begin = input.begin();
    auto end = input.end();

    auto expected = std::vector<terminalpp::token> {
        terminalpp::ansi::control_sequence {
            '?',
            'M',
            false,
            { 0 }
        }
    };

    auto result = terminalpp::detail::parse(begin, end);

    CPPUNIT_ASSERT_EQUAL(expected.size(), result.size());
    CPPUNIT_ASSERT_EQUAL(
        boost::get<terminalpp::ansi::control_sequence>(expected[0]),
        boost::get<terminalpp::ansi::control_sequence>(result[0]));
    CPPUNIT_ASSERT(begin == end);
}

void parser_test::parse_partial_command_yields_nothing()
{
    std::string input = "\x1B[";
    auto begin = input.begin();
    auto end = input.end();

    auto result = terminalpp::detail::parse(begin, end);

    CPPUNIT_ASSERT_EQUAL(size_t{0}, result.size());
    CPPUNIT_ASSERT(begin == input.begin());
}

void parser_test::parse_partial_mouse_command_yields_nothing()
{
    std::string input = "\x1B[M";
    auto begin = input.begin();
    auto end = input.end();

    auto result = terminalpp::detail::parse(begin, end);

    CPPUNIT_ASSERT_EQUAL(size_t{0}, result.size());
    CPPUNIT_ASSERT(begin == input.begin());
}

static void test_matching_7_and_8_bit_commands(
    std::string const &command7,
    std::string const &command8)
{
    auto begin7 = command7.begin();
    auto end7   = command7.end();

    auto begin8 = command8.begin();
    auto end8   = command8.end();

    auto result7 = terminalpp::detail::parse(begin7, end7);
    auto result8 = terminalpp::detail::parse(begin8, end8);

    CPPUNIT_ASSERT(begin7 == end7);
    CPPUNIT_ASSERT(begin8 == end8);

    CPPUNIT_ASSERT_EQUAL(result7.size(), result8.size());

    CPPUNIT_ASSERT_EQUAL(
        boost::get<terminalpp::ansi::control_sequence>(result7[0]),
        boost::get<terminalpp::ansi::control_sequence>(result8[0]));
}

void parser_test::parse_8bit_ind_command_yields_ind_command()
{
    //test_matching_7_and_8_bit_commands("\x1B[2H", "\x9B""2H");
}

void parser_test::parse_8bit_nel_command_yields_nel_command()
{
    //test_matching_7_and_8_bit_commands("\x1B[2H", "\x9B""2H");
}

void parser_test::parse_8bit_hts_command_yields_hts_command()
{
    //test_matching_7_and_8_bit_commands("\x1B[2H", "\x9B""2H");
}

void parser_test::parse_8bit_ri_command_yields_ri_command()
{
    //test_matching_7_and_8_bit_commands("\x1B[2H", "\x9B""2H");
}

void parser_test::parse_8bit_ss2_command_yields_ss2_command()
{
    //test_matching_7_and_8_bit_commands("\x1B[2H", "\x9B""2H");
}

void parser_test::parse_8bit_ss3_command_yields_ss3_command()
{
    //test_matching_7_and_8_bit_commands("\x1B[2H", "\x9B""2H");
}

void parser_test::parse_8bit_dcs_command_yields_dcs_command()
{
    //test_matching_7_and_8_bit_commands("\x1B[2H", "\x9B""2H");
}

void parser_test::parse_8bit_spa_command_yields_spa_command()
{
    //test_matching_7_and_8_bit_commands("\x1B[2H", "\x9B""2H");
}

void parser_test::parse_8bit_epa_command_yields_epa_command()
{
    //test_matching_7_and_8_bit_commands("\x1B[2H", "\x9B""2H");
}

void parser_test::parse_8bit_sos_command_yields_sos_command()
{
    //test_matching_7_and_8_bit_commands("\x1B[2H", "\x9B""2H");
}

void parser_test::parse_8bit_decid_command_yields_decid_command()
{
    //test_matching_7_and_8_bit_commands("\x1B[2H", "\x9B""2H");
}

void parser_test::parse_8bit_csi_command_yields_csi_command()
{
    test_matching_7_and_8_bit_commands("\x1B[2H", "\x9B""2H");
}

void parser_test::parse_8bit_st_command_yields_st_command()
{
    //test_matching_7_and_8_bit_commands("\x1B[2H", "\x9B""2H");
}

void parser_test::parse_8bit_osc_command_yields_osc_command()
{
    test_matching_7_and_8_bit_commands("\x1B]2H", "\x9D""2H");
}

void parser_test::parse_8bit_pm_command_yields_pm_command()
{
    //test_matching_7_and_8_bit_commands("\x1B[2H", "\x9B""2H");
}

void parser_test::parse_8bit_apc_command_yields_apc_command()
{
    //test_matching_7_and_8_bit_commands("\x1B[2H", "\x9B""2H");
}
