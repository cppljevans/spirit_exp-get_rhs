#ifndef AST_HPP_
#define AST_HPP_

#include <boost/spirit/home/x3/support/ast/variant.hpp>
#include <string>

#include <boost/fusion/include/adapt_struct.hpp>

namespace ast {
    namespace x3 = boost::spirit::x3;

    struct string_literal {
        std::string literal;
    };

    using primary = x3::variant<string_literal>;
    using factor = x3::variant<primary>;
}

BOOST_FUSION_ADAPT_STRUCT(ast::string_literal,
    literal
)

#endif // AST_HPP_
