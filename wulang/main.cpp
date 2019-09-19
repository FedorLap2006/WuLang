#include "wulang.h"

//namespace Lexer {
//  Lex::Lex()
//  {
//    Token tok;
//  }
//
//  void Lex::lexString(std::string string)
//  {
//    if (!string.size()) return;
//    char* curchar = &string[0];
//
//    while (curchar != &string[string.size() - 1]) {
//    }
//  }
//
//  void Lex::lexFile(std::string filename)
//  {
//  }
//}
/*
#pragma once

#include <string>

#include <fstream>
#include <vector>

#include <unordered_map>
#include <regex>
#include <cctype>
#include <iostream>

/\*

pack wulang

@info: {
  author: @FedorLap2006 (github)
}

type test: {
  field:int
}


@template<int,int>
func testFunc<100,100>(targ:test) {
}



func main() {
  var tvar:test = {100} // {field:100} // {"field": 100}
  var tvar:*test = &tvar
}



*\/
namespace WuLang {
  namespace Core {
    namespace Lexer {
      struct Token {
        struct Type {
          enum tokentype {
            tid,
            trw,
            tes,
            tnum,
          };
          enum rwident {
            GOTO,
            PRINT,
          };
        };
        Type::tokentype type;
        union {
          struct {
            Type::rwident ident;
          }rw;
          struct {
            char *ident;
            int ident_len;
          }id;
          struct {
            char ident;
          }es;
          struct {
            int ident;
          }num;
        }value;
      };
      class LexerInstance;
      namespace Utils {
        std::unordered_map<std::string, Token::Type::rwident> find_rw(std::unordered_map<std::string, Token::Type::rwident>& rwm, std::string string) {
          std::unordered_map<std::string, Token::Type::rwident> resm;
          std::regex rgi("^" + string);
          for (auto it : rwm) {
            if (std::regex_match(it.first, rgi)) {
              resm.insert({ it.first,it.second });
            }
          }
          return resm;
        }
      }
      typedef std::unordered_map<std::string, Token::Type::rwident> rwmap_type;
      typedef std::vector<Token> tokarr_type;

      rwmap_type defaultrwdb_ = {
#define rde(name,id) {name,Token::Type::rwident::id}
        rde("goto",GOTO),
        rde("print",PRINT)
#undef rde

      };


      class LexerInstance {
      private:
        std::unordered_map<std::string, Token::Type::rwident> rwdb;
        std::vector<Token> last_tokdata;
        std::istream &input;
      public:
        LexerInstance(rwmap_type rwmap, std::istream& stream) : rwdb(rwmap), input(stream) {
        }
        LexerInstance() : LexerInstance(defaultrwdb_, std::cin) {

        }
        LexerInstance(std::istream& stream) : LexerInstance(defaultrwdb_, stream) {}
        LexerInstance(rwmap_type rwmap) : LexerInstance(rwmap, std::cin) {

        }

        tokarr_type lexString(std::string str, bool tokds = false) {
          std::string curts;
          tokarr_type tokarr;
          for (auto &it : str) {

            if ((std::isalpha(it) && curts.size() == 0) || ((std::isalpha(it) || std::isdigit(it)) && curts.size() > 0)) curts += it;
            if (std::isdigit(it) && curts.size() == 0) {
              Token t;
              t.type = Token::Type::tnum;
              t.value.num.ident = it - '0';
              tokarr.push_back(t);
              continue;
            }
            else if (!std::isalpha(it)) {

              if (curts.size() > 0) {
                Token ptok;
                rwmap_type mrwr = Utils::find_rw(rwdb, curts);

                if (mrwr.size() == 0) {
                  ptok.type = Token::Type::tid;
                  ptok.value.id.ident = (char*)curts.c_str();
                  ptok.value.id.ident_len = curts.size();
                  tokarr.push_back(ptok);
                }
                else if (mrwr.size() >= 1) {
                  ptok.value.rw.ident = mrwr.at(curts);
                  ptok.type = Token::Type::tokentype::trw;
                  tokarr.push_back(ptok);
                }
                curts = "";

              }


            }


            if (std::iscntrl(it)) {
              Token tok;
              tok.type = Token::Type::tes;
              tok.value.es.ident = it;
              tokarr.push_back(tok);
              continue;
            }


          }

          if (tokds) last_tokdata = tokarr;
        }

        tokarr_type lexStream(std::istream &stream) {
          while (!stream.eof()) {
            std::string str;
            std::getline(stream, str);
            lexString(str);
          }

        }
        tokarr_type lexStream() { lexStream(input); }

        tokarr_type lex() { lexStream(); }

        void dumpLexData(std::vector<Token> ldata) {
          for (auto& it : ldata) {
            switch (it.type)
            {
            case Token::Type::tokentype::tid:
              std::cout << "TID: ";
              std::cout << it.value.id.ident;
              break;

            case Token::Type::tokentype::tes:
              std::cout << "TES: ";
              std::cout << (int)it.value.es.ident;
              break;

            case Token::Type::tokentype::trw:
              std::cout << "TRW: ";
              switch (it.value.rw.ident) {
              case Token::Type::rwident::GOTO:
                std::cout << "goto";
                break;
              case Token::Type::rwident::PRINT: {
                std::cout << "print";
                break;
              }


              }
              break;
            case Token::Type::tokentype::tnum:
              std::cout << "TNUM: ";
              std::cout << it.value.num.ident;

            default:
              break;
            }
            std::cout << std::endl;
          }
        }
        void dumpLexData() { dumpLexData(last_tokdata); }
      };

      LexerInstance baselexeri_;
    }

  }
}
*/
using namespace WuLang::Core;
int main() {
  Lexer::LexerInstance lexi;
  std::string lexstr = "goto (aaaaaa)";

  lexi.lexString(lexstr,true);
  lexi.dumpLexData();
}