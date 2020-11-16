#ifndef JSON_HPP
#define JSON_HPP

#include "freedom_global.hpp"
#include "common.hpp"
#include "abstract_lexer.hpp"
#include "abstract_dom.hpp"
#include "abstract_parser.hpp"

namespace Freedom
{
    class FREEDOM_EXPORT Json : AbstractDom
    {
    public:
        Json() = default;
        ~Json() = default;

        class Lexer : public AbstractLexer
        {
        public:
            NON_COPY_AND_MOVE_CLASS_DECL(Lexer)
        };

        class Parser : AbstractParser
        {
        public:
            NON_COPY_AND_MOVE_CLASS_DECL(Parser)
        };
    };

} // namespace Freedom

#endif // JSON_HPP
