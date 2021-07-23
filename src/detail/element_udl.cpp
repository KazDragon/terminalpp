#include "terminalpp/element.hpp"
#include "terminalpp/character_set.hpp"
#include "terminalpp/ansi/charset.hpp"
#include <boost/spirit/include/qi.hpp>
#include <tuple>

namespace terminalpp {
namespace detail {

namespace qi = boost::spirit::qi;

struct modify_element
{
    modify_element(element &elem)
      : elem_(elem)
    {
    }

    void operator()(char ch) const
    {
        elem_.glyph_.character_ = static_cast<byte>(ch);
    }

    element &elem_;
};

struct modify_charset
{
    modify_charset(element &elem)
      : elem_(elem)
    {
    }

    void operator()(char ch) const
    {
        byte const charset_code[] = { static_cast<byte>(ch) };
        auto const charset = lookup_character_set(charset_code);

        if (charset)
        {
            elem_.glyph_.charset_ = *charset;
        }
    }

    element &elem_;
};

struct modify_extended_charset
{
    modify_extended_charset(element &elem)
      : elem_(elem)
    {
    }

    void operator()(char ch) const
    {
        byte const charset_code[] = { ansi::charset_extender, static_cast<byte>(ch) };
        auto const charset = lookup_character_set(charset_code);

        if (charset)
        {
            elem_.glyph_.charset_ = *charset;
        }
    }

    element &elem_;
};

struct modify_intensity
{
    modify_intensity(element &elem)
      : elem_(elem)
    {
    }

    void operator()(char ch) const
    {
        switch(ch)
        {
            case '>':
                elem_.attribute_.intensity_ = graphics::intensity::bold;
                break;

            case '<':
                elem_.attribute_.intensity_ = graphics::intensity::faint;
                break;

            default:
                elem_.attribute_.intensity_ = graphics::intensity::normal;
                break;
        }
    }

    element &elem_;
};

struct modify_polarity
{
    modify_polarity(element &elem)
      : elem_(elem)
    {
    }

    void operator()(char ch) const
    {
        switch(ch)
        {
            case '+':
                elem_.attribute_.polarity_ = graphics::polarity::positive;
                break;

            case '-':
                elem_.attribute_.polarity_ = graphics::polarity::negative;
                break;

            default:
                elem_.attribute_.polarity_ = graphics::polarity::positive;
                break;
        }
    }

    element &elem_;
};

struct modify_underlining
{
    modify_underlining(element &elem)
      : elem_(elem)
    {
    }

    void operator()(char ch) const
    {
        switch(ch)
        {
            case '+':
                elem_.attribute_.underlining_ = graphics::underlining::underlined;
                break;

            case '-':
                elem_.attribute_.underlining_ = graphics::underlining::not_underlined;
                break;

            default:
                elem_.attribute_.underlining_ = graphics::underlining::not_underlined;
                break;
        }
    }

    element &elem_;
};

struct modify_foreground_low_colour
{
    modify_foreground_low_colour(element &elem)
      : elem_(elem)
    {
    }

    void operator()(unsigned char col) const
    {
        elem_.attribute_.foreground_colour_ = low_colour(
            static_cast<terminalpp::graphics::colour>(col));
    }

    element &elem_;
};

struct modify_foreground_high_colour
{
    modify_foreground_high_colour(element &elem)
      : elem_(elem)
    {
    }

    void operator()(boost::fusion::vector<
        unsigned char, unsigned char, unsigned char> col) const
    {
        elem_.attribute_.foreground_colour_ = high_colour(
            boost::fusion::at<boost::mpl::int_<0>>(col),
            boost::fusion::at<boost::mpl::int_<1>>(col),
            boost::fusion::at<boost::mpl::int_<2>>(col));
    }

    element &elem_;
};

struct modify_foreground_greyscale_colour
{
    modify_foreground_greyscale_colour(element &elem)
      : elem_(elem)
    {
    }

    void operator()(unsigned char col) const
    {
        elem_.attribute_.foreground_colour_ = greyscale_colour(col);
    }

    element &elem_;
};


struct modify_background_low_colour
{
    modify_background_low_colour(element &elem)
      : elem_(elem)
    {
    }

    void operator()(unsigned char col) const
    {
        elem_.attribute_.background_colour_ = low_colour(
            static_cast<terminalpp::graphics::colour>(col));
    }

    element &elem_;
};

struct modify_background_high_colour
{
    modify_background_high_colour(element &elem)
      : elem_(elem)
    {
    }

    void operator()(boost::fusion::vector<
        unsigned char, unsigned char, unsigned char> col) const
    {
        elem_.attribute_.background_colour_ = high_colour(
            boost::fusion::at<boost::mpl::int_<0>>(col),
            boost::fusion::at<boost::mpl::int_<1>>(col),
            boost::fusion::at<boost::mpl::int_<2>>(col));
    }

    element &elem_;
};

struct modify_background_greyscale_colour
{
    modify_background_greyscale_colour(element &elem)
      : elem_(elem)
    {
    }

    void operator()(unsigned char col) const
    {
        elem_.attribute_.background_colour_ = greyscale_colour(col);
    }

    element &elem_;
};

struct modify_unicode_element
{
    modify_unicode_element(element &elem)
      : elem_(elem)
    {
    }

    void operator()(unsigned short value) const
    {
        static constexpr long const maxima[] = {
            0x00007F,
            0x0007FF,
            0x00FFFF,
            0x10FFFF
        };

        byte text[4] = {0};

        // At the moment, we can only convert up to 0xFFFF hex, since we only have
        // three spots in ucharacter_ to play with.  As an arbitrary decision,
        // anything above that will come out as a ? character.  Otherwise,
        // we will UTF-8 encode the value as appropriate into the ucharacter_
        // array.
        if (value <= maxima[0])
        {
            text[0] = byte(value & 0x7F);
            text[1] = 0;
            text[2] = 0;
        }
        else if (value <= maxima[1])
        {
            text[0] = byte(0b11000000 | (value >> 6));
            text[1] = byte(0b10000000 | (value & 0b00111111));
            text[2] = 0;
        }
        else if (value <= maxima[2])
        {
            text[0] = byte(0b11100000 | (value >> 12));
            text[1] = byte(0b10000000 | ((value >> 6) & 0b00111111));
            text[2] = byte(0b10000000 | (value & 0b00111111));
        }
        else
        {
            // Too high to encode right now.
            text[0] = byte('?');
            text[1] = 0;
        }

        elem_.glyph_ = terminalpp::glyph(text);
    }

    element &elem_;
};

element parse_element(gsl::cstring_span &text)
{
    auto const uint1_1_p = qi::uint_parser<unsigned char, 10, 1, 1>();
    auto const uint2_2_p = qi::uint_parser<unsigned char, 10, 2, 2>();
    auto const uint3_3_p = qi::uint_parser<unsigned char, 10, 3, 3>();
    auto const uint4_4_p = qi::uint_parser<unsigned short, 16, 4, 4>();

    auto const character_code_p = qi::lit('C') >> (uint3_3_p | qi::attr((unsigned char)(' ')));
    auto const extended_character_set_p = qi::lit('c') >> qi::lit('%') >> qi::char_;
    auto const character_set_p = qi::lit('c') >> qi::char_;
    auto const intensity_p = qi::lit('i') >> qi::char_;
    auto const polarity_p = qi::lit('p') >> qi::char_;
    auto const underlining_p = qi::lit('u') >> qi::char_;
    auto const foreground_low_colour = qi::lit('[') >> uint1_1_p;
    auto const foreground_high_colour = qi::lit('<') >> uint1_1_p >> uint1_1_p >> uint1_1_p;
    auto const foreground_greyscale_colour = qi::lit('{') >> uint2_2_p;
    auto const background_low_colour = qi::lit(']') >> uint1_1_p;
    auto const background_high_colour = qi::lit('>') >> uint1_1_p >> uint1_1_p >> uint1_1_p;
    auto const background_greyscale_colour = qi::lit('}') >> uint2_2_p;
    auto const unicode_p = qi::lit('U') >> (uint4_4_p | qi::attr((unsigned short)(' ')));

    auto expression = qi::rule<gsl::cstring_span::const_iterator, element()>{};

    element elem;

    expression = 
        (qi::lit('\\') >> 
          -( character_code_p[modify_element(elem)]
           | extended_character_set_p[modify_extended_charset(elem)] >> expression
           | character_set_p[modify_charset(elem)] >> expression
           | intensity_p[modify_intensity(elem)] >> expression
           | polarity_p[modify_polarity(elem)] >> expression
           | underlining_p[modify_underlining(elem)] >> expression
           | foreground_low_colour[modify_foreground_low_colour(elem)] >> expression
           | foreground_high_colour[modify_foreground_high_colour(elem)] >> expression
           | foreground_greyscale_colour[modify_foreground_greyscale_colour(elem)] >> expression
           | background_low_colour[modify_background_low_colour(elem)] >> expression
           | background_high_colour[modify_background_high_colour(elem)] >> expression
           | background_greyscale_colour[modify_background_greyscale_colour(elem)] >> expression
           | unicode_p[modify_unicode_element(elem)]
           | (qi::char_[modify_element(elem)])
           )
        )
      | (qi::char_[modify_element(elem)]);

    auto first = text.cbegin();
    auto last = text.cend();

    qi::parse(first, last, expression);

    return elem;
}

}}
