#define BOOST_ERROR_CODE_HEADER_ONLY
#include "../trace_scope.hpp"
#include "../type_name.hpp"
#include "grammar_def.hpp"
#include "parser_config.hpp"
#include <iostream>

int main()
{
    namespace x3 = boost::spirit::x3;

    ast::factor  attr;

    std::string input{ "a * b" };
    parser::iterator_type iter = input.begin();
    parser::iterator_type end = input.end();

    parser::error_handler_type error_handler(iter, end, std::cerr);

    auto const parser =
        x3::with<x3::error_handler_tag>(std::ref(error_handler))
        [
              parser::factor
        ];

    bool success = x3::phrase_parse(iter, end, parser, x3::iso8859_1::space, attr);
    std::cout<<"success="<<success<<"\n";
    return 0;
}
