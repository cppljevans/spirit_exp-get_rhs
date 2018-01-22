#ifndef PARSER_LITERAL_DEF_HPP_
#define PARSER_LITERAL_DEF_HPP_

#include "literal.hpp"

namespace parser {

    namespace x3 = boost::spirit::x3;

    string_literal_type const string_literal { "string_literal" };

    auto const string_literal_def =
        x3::lexeme ['"' >> *x3::char_ >> '"' ];

    BOOST_SPIRIT_DEFINE(
        string_literal
    )
}

namespace parser_api {
    parser::string_literal_type const& string_literal()
    {
        return parser::string_literal;
    }
}

#endif /* PARSER_LITERAL_DEF_HPP_ */
