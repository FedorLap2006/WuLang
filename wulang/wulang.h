#pragma once

#include <string>

#include <fstream>
#include <vector>

#include <unordered_map>
#include <regex>
#include <cctype>
#include <iostream>
#include <cstring>
#include <boost/variant.hpp>
/*

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



*/
#define MAX_ID_LEN 256

namespace WuLang {
  namespace Core {
    namespace Lexer {
      struct Token {
        struct Type {
          enum tokentype {
            tid,
            trw,
            top,
            tes,
            tnum,
          };
          enum rwident {
            GOTO,
            PRINT,
          };
          enum opident {
            LBRACKET,
            RBRACKET,
          };
          /*enum esident {
            NEWLINE,
            TAB,
          };*/
        };
        Type::tokentype type;
        boost::variant<Type::rwident, Type::opident, std::string, char, int> value;
        Type::rwident rwValue() {
          return boost::get< Type::rwident >(value);
        }
        Type::opident opValue() {
          return boost::get< Type::opident >(value);
        }
        std::string idValue() {
          return boost::get< std::string >(value);
        }
        char esValue() {
          return boost::get< char >(value);
        }
        int numValue() {
          return boost::get< int >(value);
        }
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
      typedef std::unordered_map<std::string, Token::Type::opident> opmap_type;
      typedef std::vector<Token> tokarr_type;

      rwmap_type defaultrwdb_ = {
#define rde(name,id) {name,Token::Type::rwident::id}
        rde("goto",GOTO),
        rde("print",PRINT)
#undef rde

      };

      opmap_type defaultopdb_ = {
#define opde(name,id) {name,Token::Type::opident::id}
        opde("(",LBRACKET),
        opde(")",RBRACKET)
#undef opde

      };



      class LexerInstance {
      private:
        std::unordered_map<std::string, Token::Type::rwident> rwdb;
        std::unordered_map<std::string, Token::Type::opident> opdb;
        std::vector<Token> last_tokdata;
        std::istream &input;
      public:
        LexerInstance(rwmap_type rwmap, opmap_type opmap, std::istream& stream) : rwdb(rwmap), opdb(opmap), input(stream) {
        }
        LexerInstance() : LexerInstance(defaultrwdb_, defaultopdb_, std::cin) {

        }
        LexerInstance(std::istream& stream) : LexerInstance(defaultrwdb_, defaultopdb_, stream) {}
        LexerInstance(rwmap_type rwmap) : LexerInstance(rwmap, defaultopdb_, std::cin) {

        }
        LexerInstance(opmap_type opmap) : LexerInstance(defaultrwdb_, opmap, std::cin) {

        }
        LexerInstance(rwmap_type rwmap, std::istream& stream) : LexerInstance(rwmap, defaultopdb_, stream) {

        }
        LexerInstance(opmap_type opmap, std::istream& stream) : LexerInstance(defaultrwdb_, opmap, stream) {

        }


        tokarr_type lexString(std::string str, bool tokds = false) {
          std::string curts;
          tokarr_type tokarr;
          for (auto &it : str) {
            if ((std::isalpha(it) && curts.size() == 0) || ((std::isalpha(it) || std::isdigit(it)) && curts.size() > 0)) {
              curts += it;
            }
            if (!(std::isalpha(it) || std::isdigit(it)) && curts.size() > 0) {
              Token ptok;
              rwmap_type mrwr = Utils::find_rw(rwdb, curts);

              if (mrwr.size() == 0) {
                ptok.type = Token::Type::tid;
                ptok.value = curts;
                tokarr.push_back(ptok);
              }
              else if (mrwr.size() >= 1) {
                ptok.value = mrwr.at(curts);
                ptok.type = Token::Type::tokentype::trw;
                tokarr.push_back(ptok);
              }
              curts = "";
            }
            if (std::ispunct(it)) {
              std::string key;
              key.push_back(it);
              //std::cout << "AHAHAH: " << opdb.count(key) << " UHUHUH: " << key << std::endl;
              if (opdb.count(key) != 0) {
                Token t;
                t.type = Token::Type::top;
                t.value = opdb.at(key);
                tokarr.push_back(t);
              }
            }
            
            
            if (std::isdigit(it) && curts.size() == 0) {
              Token t;
              t.type = Token::Type::tnum;
              t.value = (int)(it - '0');
              tokarr.push_back(t);
            }


            if (std::iscntrl(it) || std::isblank(it)) {
              Token tok;
              tok.type = Token::Type::tes;
              tok.value = it;
              tokarr.push_back(tok);
              continue;
            }


          }
          if (curts.size() > 0) {
            Token ptok;
            rwmap_type mrwr = Utils::find_rw(rwdb, curts);

            if (mrwr.size() == 0) {
              ptok.type = Token::Type::tid;
              ptok.value = curts;
              tokarr.push_back(ptok);
            }
            else if (mrwr.size() >= 1) {
              ptok.value = mrwr.at(curts);
              ptok.type = Token::Type::tokentype::trw;
              tokarr.push_back(ptok);
            }
          }

          if (tokds) last_tokdata = tokarr;
          return tokarr;
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
          std::cout << "lex dump(" << ldata.size() << ")" << std::endl;
          for (auto& it : ldata) {
            switch (it.type)
            {
            case Token::Type::tokentype::tid:
              std::cout << "TID: ";
              std::cout << boost::get<std::string>(it.value);
              break;

            case Token::Type::tokentype::tes:
              std::cout << "TES: ";
              std::cout << (int)boost::get<char>(it.value);
              break;

            case Token::Type::tokentype::trw:
              std::cout << "TRW: ";
              switch (boost::get<Token::Type::rwident>(it.value)) {
              case Token::Type::rwident::GOTO:
                std::cout << "goto";
                break;
              case Token::Type::rwident::PRINT:
                std::cout << "print";
                break;
              }
              break;
            case Token::Type::tokentype::top:
              std::cout << "TOP: ";
              switch (boost::get<Token::Type::opident>(it.value)) {
              case Token::Type::opident::LBRACKET:
                std::cout << "(";
                break;
              case Token::Type::opident::RBRACKET:
                std::cout << ")";
                break;
              }
              break;
            case Token::Type::tokentype::tnum:
              std::cout << "TNUM: ";
              std::cout << boost::get<int>(it.value);

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

    namespace Parser {

    }

  }
}