//Purpose:
//  Generate grammar for benchmark.
//
#include <iostream>
#include <fstream>
#include <iomanip>
struct osi//indented out stream.
{
private:
  std::ostream& _os;
  int _indent;//current indentation.
  static unsigned const margin=2;
public:
  osi(std::ostream& os):_os(os),_indent(0){}
  std::ostream& os(){ return _os;}
  std::ostream& operator()(){ _os<<std::setw(_indent)<<""; return _os;
    }
  std::ostream& operator++(){ _indent+=margin; return _os;}
  std::ostream& operator--(){ _indent-=margin; return _os;}
};
struct osb
  //indented out stream block.
  //CTOR indents
  //DTOR dedents
{
private:
  osi& _os;
public:
  osb(osi& os):_os(os)
  { ++_os;}
  ~osb()
  { --_os;}
};
#include <string>

#define DEFAULT_NUM_RULES 11
std::string r_(int ndx_rule)
{
  return std::string("r_")+std::to_string(ndx_rule);
}
std::string d_(int ndx_rule)
{
  return r_(ndx_rule)+std::string("_def");
}
enum rref_enum
{ rul
, def
};
template< rref_enum Rref>
std::string r_lhs(int ndx_rule)
{
  return std::string("r_")+std::to_string(ndx_rule);
}
template<>
std::string r_lhs<def>(int ndx_rule)
{
  return std::string("auto const ")+d_(ndx_rule)+"="+r_(ndx_rule);
}
template< rref_enum Rref>
std::string r_rhs(int ndx_rule)
{
  return std::string("r_")+std::to_string(ndx_rule);
}
template<>
std::string r_rhs< def>(int ndx_rule)
{
  return d_(ndx_rule);
}
std::string op(int ndx_rule)
{
  return std::string("string_(\"")+std::to_string(ndx_rule)+"\")";
}
template< rref_enum Rref>
std::string rhs(int ndx_rule,int num_rules)
{
  if(ndx_rule)
      return r_rhs<Rref>(ndx_rule-1)+">>*("+op(ndx_rule)+">>"+r_rhs<Rref>(ndx_rule-1)+")";
  else
    return "char_('_')|char_('[')>>"+r_(num_rules-1)+">>char_(']')";
}
void rule_decls( osi&gfi, int num_rules)
{
  for(int i_rule=0; i_rule<num_rules; ++i_rule)
    gfi()<<"rule_b<id<"<<i_rule<<">> const "<<r_(i_rule)<<";\n";
}
int main(int argc, char *argv[])
{
  int num_rules=DEFAULT_NUM_RULES;
#if 0
  std::cout<<":argc="<<argc<<"\n";
  for(int i_arg; i_arg<argc; ++i_arg)
    std::cout<<"argv["<<i_arg<<"]="<<argv[i_arg]<<"\n";
#endif    
  if(argc>1) num_rules=std::stoi(argv[1]);
  std::cout<<argv[0]<<":num_rules="<<num_rules<<"\n";
  int i_rule;
  std::ofstream gf;
  gf.open("gram_file.hpp");
  {
    osi gfi(gf);
    osb gfb(gfi);
    gfi()<<"#if RULE2RHS_WHICH != RULE2RHS_GET_RHS_CRTP\n";
    { osb gfb(gfi);
      rule_decls( gfi, num_rules);
    }
    gfi()<<"#endif//RULE2RHS_WHICH != RULE2RHS_GET_RHS_CRTP\n";
    gfi()<<"#if USE_RHS_DEF"<<"\n";
    { osb gfb(gfi);
      for(i_rule=0;i_rule<num_rules; ++i_rule)
        gfi()<<r_lhs<def>(i_rule)+"="+rhs<def>(i_rule,num_rules)+";\n";
      gfi()<<"auto const& start="<<d_(num_rules-1)<<";\n";
      gfi()<<"#if RULE2RHS_WHICH == RULE2RHS_CTX_MI_REC\n";
      { osb gfb(gfi);
        gfi()<<"auto const& ctx=make_defs\n";
        gfi()<<"( "<<d_(num_rules-1)<<"\n";
        gfi()<<");"<<"\n";
      }
      gfi()<<"#else\n";
      { osb gfb(gfi);
        gfi()<<"auto const& ctx=empty_context();\n";
        gfi()<<"#if RULE2RHS_WHICH == RULE2RHS_GET_RHS_REC\n";
        { osb gfb(gfi);
          gfi()<<"BOOST_SPIRIT_DEFINE\n";
          gfi()<<"( "<<d_(num_rules-1)<<"\n";
          gfi()<<");"<<"\n";
        }
        gfi()<<"#endif\n";
        }
      gfi()<<"#endif //RULE2RHS_WHICH == RULE2RHS_CTX_MI_REC\n";
    }
    gfi()<<"#elif RULE2RHS_WHICH != RULE2RHS_GET_RHS_CRTP\n";
    { osb gfb(gfi);
      for(i_rule=0;i_rule<num_rules; ++i_rule)
        gfi()<<r_lhs<def>(i_rule)+"="+rhs<rul>(i_rule,num_rules)+";\n";
      gfi()<<"auto const& start="<<d_(num_rules-1)<<";\n";
      gfi()<<"#if RULE2RHS_WHICH == RULE2RHS_CTX_MI_ALL\n";
      { osb gfb(gfi);
        gfi()<<"auto const& ctx=make_defs\n";
        for(i_rule=num_rules-1; i_rule>=0; --i_rule)
        {
          if(i_rule==num_rules-1)
            gfi()<<"( ";
          else
            gfi()<<", ";  
          gfi.os()<<d_(i_rule)<<"\n";
        }
        gfi()<<");"<<"\n";
      }
      gfi()<<"#else\n";
      { osb gfb(gfi);
        gfi()<<"auto const& ctx=empty_context();\n";
        gfi()<<"#if RULE2RHS_WHICH == RULE2RHS_GET_RHS_ALL\n";
        { osb gfb(gfi);
          gfi()<<"BOOST_SPIRIT_DEFINE\n";
          for(i_rule=num_rules-1; i_rule>=0; --i_rule)
          {
            if(i_rule==num_rules-1)
              gfi()<<"( ";
            else
              gfi()<<", ";  
            gfi.os()<<d_(i_rule)<<"\n";
          }
          gfi()<<");"<<"\n";
        }
        gfi()<<"#endif\n";
      }
      gfi()<<"#endif //RULE2RHS_WHICH == RULE2RHS_CTX_MI_ALL\n";
    }
    gfi()<<"#else//RULE2RHS_GET_RHS_CRTP\n";
    { osb gfb(gfi);
      gfi()<<"struct gram_deriv: gram_base<gram_deriv>\n";
      gfi()<<"{\n";
      { osb gfb(gfi);
        rule_decls( gfi, num_rules);
        gfi()<<"BOOST_SPIRIT_GET_RHS\n";
        gfi()<<"( ";
        { 
          for(i_rule=0; i_rule<num_rules; ++i_rule)
          { 
            if(i_rule>0) 
            { 
              gfi()<<", ";
            }
            {
              osb gfb(gfi);
              gfi.os()<<"( ";
              gfi.os()<<r_lhs<rul>(i_rule)<<"="<<rhs<rul>(i_rule,num_rules)<<"\n";
              gfi()<<")\n";
            }
          }
        }
        gfi()<<")\n";
      }
      gfi()<<"};\n";
      gfi()<<"gram_deriv g;\n";
      gfi()<<"auto const& start=g.get_rhs(id<"<<num_rules-1<<">{});\n";
      gfi()<<"auto const& ctx = empty_context();\n";
    }
    gfi()<<"#endif//end:USE_RHS_DEF\n";
  }
  gf.close();
  return 0;
}
