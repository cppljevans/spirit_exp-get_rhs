#ifndef PARSER_LITERAL_HPP_
#define PARSER_LITERAL_HPP_
#include "../trace_scope.hpp"
#include "../type_name.hpp"

#include "ast.hpp"
#include <boost/spirit/home/x3.hpp>

namespace parser {

    namespace x3 = boost::spirit::x3;

    struct string_literal_class;
    typedef x3::rule<string_literal_class, ast::string_literal> string_literal_type;

    BOOST_SPIRIT_DECLARE(string_literal_type);
}

namespace parser_api {
    parser::string_literal_type const& string_literal();
}

#endif /* PARSER_LITERAL_HPP_ */
