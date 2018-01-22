#include "literal_def.hpp"
#include "parser_config.hpp"

namespace parser {
    namespace x3 = boost::spirit::x3;

    BOOST_SPIRIT_INSTANTIATE(
        string_literal_type,
        iterator_type,
        context_type
    );
}

