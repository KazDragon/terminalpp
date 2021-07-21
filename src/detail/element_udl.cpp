#include "terminalpp/element.hpp"
#include <boost/spirit/include/qi.hpp>

namespace terminalpp {
namespace detail {

namespace qi = boost::spirit::qi;

struct modify_element
{
    modify_element(element& elem)
      : elem_(elem)
    {
    }

    void operator()(char ch) const
    {
        printf("assign char %c\n", ch);
        elem_.glyph_.character_ = static_cast<byte>(ch);
    }

    void operator()(unsigned char ch) const
    {
        printf("assign uchar %ch\n", char(ch));
        elem_.glyph_.character_ = static_cast<byte>(ch);        
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

    qi::parse(
        first, 
        last,
        (qi::lit('\\') >> 
          -( character_code_p[modify_element(elem)]
           | (qi::char_[modify_element(elem)])
           )
        )
      | (qi::char_[modify_element(elem)])
    );

    return elem;
}

}}
