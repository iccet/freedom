#ifndef XML_HPP
#define XML_HPP

#include "freedom_global.hpp"

#include "common.hpp"
#include "abstract_dom.hpp"
#include "abstract_lexer.hpp"
#include "abstract_parser.hpp"

#include <vector>
#include <variant>

namespace Freedom {

    class FREEDOM_EXPORT Xml : public AbstractDom {
    public:

        Xml() = default;
        ~Xml() = default;

        enum Token {
            Open = '<',
            Close = '>',
            Break = '/',
            Prolog = '?',
            Eq = '=',
            DoubleQuote = '"',
            Quote = '\'',
        };

        void parse(std::ifstream &fin) throw();

        class Lexer : public AbstractLexer {
        public:
            NON_COPY_AND_MOVE_CLASS_DECL(Lexer)
            virtual void parse(std::ifstream &s);
            virtual std::string_view::iterator parse(std::string_view s, BasicPrologNode *root=nullptr);

            BasicPrologNode take_prolog_node(std::string_view::iterator &);
            BasicPrologNode take_data_node(std::string_view::iterator &);
            BasicPrologNode take_node(std::string_view::iterator &i);
        };

        class Parser : AbstractParser {
        public:
            NON_COPY_AND_MOVE_CLASS_DECL(Parser)
        };
    };

} // namespace Freedom

#endif // XML_HPP
