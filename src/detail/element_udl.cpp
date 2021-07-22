#include "terminalpp/element.hpp"
#include "terminalpp/character_set.hpp"
#include "terminalpp/ansi/charset.hpp"
#include <boost/spirit/include/qi.hpp>

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

element parse_element(gsl::cstring_span &text)
{
    auto first = text.cbegin();
    auto last = text.cend();

    element elem;

    auto const uint3_3_p = qi::uint_parser<unsigned char, 10, 3, 3>();
    auto const character_code_p = qi::lit('C') >> (uint3_3_p | qi::attr((unsigned char)(' ')));
    auto const extended_character_set_p = qi::lit('c') >> qi::lit('%') >> qi::char_;
    auto const character_set_p = qi::lit('c') >> qi::char_;
    auto const intensity_p = qi::lit('i') >> qi::char_;
    auto const polarity_p = qi::lit('p') >> qi::char_;

    auto expression = qi::rule<gsl::cstring_span::const_iterator, element()>{};

    expression = 
        (qi::lit('\\') >> 
          -( character_code_p[modify_element(elem)]
           | extended_character_set_p[modify_extended_charset(elem)] >> expression
           | character_set_p[modify_charset(elem)] >> expression
           | intensity_p[modify_intensity(elem)] >> expression
           | polarity_p[modify_polarity(elem)] >> expression
           | (qi::char_[modify_element(elem)])
           )
        )
      | (qi::char_[modify_element(elem)]);

    qi::parse(first, last, expression);

    return elem;
}

}}
