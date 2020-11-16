#include <QTextStream>
#include <fstream>

#include "abstract_lexer.hpp"

namespace Freedom {

    void
    AbstractLexer::parse(std::ifstream &fin)
    {
        std::string line;
        while (getline(fin, line)) parse(line);
    }

    template<class TStream>
    TStream &operator<<(TStream &out,
                        const AbstractLexer &lexer)
    {
        for(const auto i : lexer._lexemes) out << i << " | ";
        return out;
    }

    template<>
    QTextStream &operator<<(QTextStream &out,
                            const AbstractLexer &lexer)
    {
        for(const auto i : lexer._lexemes) out << i.c_str() << " | ";
        return out;
    }

} // namespace Freedom
