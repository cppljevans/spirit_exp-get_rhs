#ifndef PARSER_CONFIG_HPP_
#define PARSER_CONFIG_HPP_

#include <boost/spirit/home/x3.hpp>
#include <boost/spirit/home/x3/support/utility/error_reporting.hpp>
#include <boost/spirit/home/x3/support/context.hpp>

namespace parser {
    namespace x3 = boost::spirit::x3;

    template <typename Iterator>
    using error_handler = x3::error_handler<Iterator>;
    using error_handler_tag = x3::error_handler_tag;

    typedef std::string::iterator                 iterator_type;
    typedef error_handler<iterator_type>        error_handler_type;
    typedef x3::phrase_parse_context<
            x3::iso8859_1::space_type>::type            phrase_context_type;
    typedef x3::context<
        error_handler_tag
        , std::reference_wrapper<error_handler_type>// const
        , phrase_context_type
    >                                                   context_type;
}

#endif /* CONFIG_HPP_ */
