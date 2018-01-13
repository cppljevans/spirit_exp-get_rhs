//Purpose:
//  Show that the rule_definition::parse_no_xform is needed.
//=================================  
//#define BOOST_SPIRIT_X3_DEBUG
//#define SHOW_PARSE_NO_XFORM_NEED
#define USE_DEFINE
#define TRACE_RULE_DEFINITION_PARSE_F
#define TRACE_RULE_PARSE_F
#if 0 \
 || defined(TRACE_RULE_DEFINITION_PARSE_F) \
 || defined(TRACE_RULE_PARSE_F) \
 || 0
 
#define USE_TRACE_SCOPE
#endif 
#ifdef USE_TRACE_SCOPE
#include "../type_name.hpp"  
#include "../trace_scope.hpp"  
#endif
#include <boost/config/warning_disable.hpp>
#include <boost/spirit/home/x3.hpp>
#include <boost/fusion/include/adapt_struct.hpp>
#ifndef TRACE_PARSES
  #define TRACE_PARSES 1
#endif
#if TRACE_PARSES
  #include <boost/spirit/home/x3/support/traits/print_attribute.hpp>
#endif

#include <iostream>

namespace wccs_parser {

namespace x3 = boost::spirit::x3;
namespace ascii = x3::ascii;

using x3::ulong_;
using x3::lexeme;

//--- Ast structures

struct AstChannel {
     std::string label;
     bool complement;
};

struct AstAction {
     AstChannel channel;
     uint32_t weight;
};

} // End namespace

BOOST_FUSION_ADAPT_STRUCT(wccs_parser::AstChannel, label, complement)
BOOST_FUSION_ADAPT_STRUCT(wccs_parser::AstAction, channel, weight)

namespace wccs_parser {

template <typename T, typename ID> auto rule = [](const char* name = typeid(T).name()) {
     return x3::rule<ID, T> {name};
};
template <typename T, typename ID> auto as = [](auto p) { return rule<T,ID>() = p; };

//--- Rules

auto label   = as<std::string,struct labelRule>(x3::lexeme[+(ascii::alnum)]);
auto channel_rhs = label >> x3::matches['!'];
#ifdef USE_DEFINE
auto channel = rule<AstChannel,struct channelRule>();
auto channel_def=channel=channel_rhs;
BOOST_SPIRIT_DEFINE(channel)
#else
auto channel = as<AstChannel,struct channelRule>(channel_rhs);
#endif//USE_DEFINE
auto action  = as<AstAction,struct actionRule>('<' >> channel >> ',' >> x3::ulong_ >> 
  '>');
auto root_expr_v = action;
using root_attr_t = AstAction;

} //End namespace

int main() {
#ifdef USE_TRACE_SCOPE
      boost::iostreams::indent_scoped_ostreambuf<char>
  indent_outbuf(std::cout,2);
#endif

     std::string strs[]=
     { "<label0!,0>"
     //, "<label1,1>"
     };
     bool all_ok=true;
     for(std::string str : strs)
     {
         namespace x3=wccs_parser::x3;
         
         wccs_parser::root_attr_t root_attr_v;
         auto iter = str.begin();
         auto end = str.end();
         bool r = 
           parse
           ( iter
           , end
           , wccs_parser::root_expr_v
           , root_attr_v
           );
         all_ok=all_ok && r;
       #if TRACE_PARSES
         if (r)
         {
             std::cout << str << std::endl << std::endl << " Parses OK: " << std::endl;
             x3::traits::print_attribute(std::cout,root_attr_v);
             std::cout << "\n-------------------------\n";
         }
         else
         {
             std::cout << "Parsing failed\n";
             std::cout << "-------------------------\n";
         }

         if (iter != end) std::cout << "Partial match" << std::endl;
       #endif
     }
   #if TRACE_PARSES
     std::cout<<"all_ok="<<all_ok<<"\n";
   #endif
     return !all_ok;
}
