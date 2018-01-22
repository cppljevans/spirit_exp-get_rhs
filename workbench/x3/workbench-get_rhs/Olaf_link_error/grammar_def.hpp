#include "ast.hpp"
#include <boost/spirit/home/x3.hpp>
#ifndef LINKER_ERROR
  #define LINKER_ERROR 1
#endif  
#if LINKER_ERROR
#include "literal.hpp"
#endif

namespace parser {

   namespace x3 = boost::spirit::x3;

    struct factor_class{};
    struct primary_class{};
#if !LINKER_ERROR
    struct string_literal_class{};
#endif

    typedef x3::rule<factor_class, ast::factor> factor_type;
    typedef x3::rule<primary_class, ast::primary> primary_type;
#if !LINKER_ERROR
    typedef x3::rule<string_literal_class, ast::string_literal> string_literal_type;
#endif

    factor_type const factor{ "factor" };
    primary_type const primary{ "primary" };
#if !LINKER_ERROR
    string_literal_type const string_literal{ "string_literal" };
#endif

#if defined(LINKER_ERROR)
    namespace {
        auto const& string_literal = parser_api::string_literal();
    }
#endif

    auto const factor_def = primary;

    auto const primary_def = string_literal;

#if !LINKER_ERROR
    auto const string_literal_def =
        x3::lexeme ['"' >> *x3::char_ >> '"' ]
        ;
#endif

    BOOST_SPIRIT_DEFINE(factor, primary)
#if !LINKER_ERROR
    BOOST_SPIRIT_DEFINE(
            string_literal
    )
#endif
}
