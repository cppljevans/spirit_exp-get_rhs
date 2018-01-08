//Purpose:
//  Test solution to the link problem reported in post:
/*
http://boost.2283326.n4.nabble.com/Linking-error-when-changing-gt-to-gt-gt-tc4689820.html
 */
//    
//===========================================
#include <boost/detail/lightweight_test.hpp>
#include <iostream>
#include "types.hpp"
#include "example.hpp"
#define TRACE_PARSES 1
#ifndef TRACE_PARSES
  #define TRACE_PARSES 0
#endif
#if TRACE_PARSES
  #include <boost/spirit/home/x3/support/traits/print_attribute.hpp>
#endif

template<typename Parser, typename Attribute>
bool test(const std::string& str, Parser&& p, Attribute&& attr)
{
    using iterator_type = std::string::const_iterator;
    iterator_type in = str.begin();
    iterator_type end = str.end();

    bool ret = boost::spirit::x3::phrase_parse(in, end, p, boost::spirit::x3::ascii::space, attr);
  #if TRACE_PARSES
    if (ret)
    {
        std::cout << str << std::endl << std::endl << " Parses OK: " << std::endl;
        boost::spirit::x3::traits::print_attribute(std::cout,attr);
        std::cout << "\n-------------------------\n";
    }
    else
    {
        std::cout << "Parsing failed\n";
        std::cout << "-------------------------\n";
    }

    if (in != end) std::cout << "Partial match" << std::endl;
  #endif
    ret &= (in == end);
    return ret;
}

int main()
{
    client::ast::VariableDec attr;
    bool result=test("var foo : foo<bar, baz<bahama>> ;", client::var_dec() , attr);
    BOOST_TEST(result);
    return boost::report_errors();
}
