#include <QDebug>
#include <fstream>

#include "xml.hpp"
#include "exceptions.hpp"

namespace Freedom
{
    void skip_whitespace(std::string_view::iterator &i)
    {
        while (isspace(*i)) i++;
    }

    std::string take_word(std::string_view::iterator &i)
    {
        auto begin = i;
        while (isgraph(*i) && *i != Xml::Token::Eq && *i != Xml::Token::Prolog && *i != Xml::Token::Close) i++;
        return std::string(begin, i);
    }

    std::string take_value(std::string_view::iterator &i)
    {
        auto v = *i++;
        if(v != Xml::Token::DoubleQuote && v != Xml::Token::Quote) throw BadXml();
        auto begin = i;
        while (*++i != v);
        return std::string(begin, i++);
    }

    Attr<std::string> take_attribute(std::string_view::iterator &i)
    {
        std::string name = take_word(i);
        skip_whitespace(i);
        if(*i++ != Xml::Token::Eq) throw bad_xml;
        skip_whitespace(i);
        std::string value = take_value(i);

        qDebug() << "Attribute" << name.c_str() << value.c_str();
        return std::make_pair(name, value);
    }

    BasicAttrs take_attributes(std::string_view::iterator &i, Xml::Token break_token)
    {
        BasicAttrs attrs;
        while (*i != break_token) {
            skip_whitespace(i);
            auto attr = take_attribute(i);
            attrs.push_back(attr);
        }
        return attrs;
    }

    BasicPrologNode Xml::Lexer::take_prolog_node(std::string_view::iterator &i)
    {
        std::string name = take_word(i);
        qDebug() << "Prolog" << name.c_str();
        BasicAttrs attrs = take_attributes(i, Token::Prolog);

        if(*++i != Token::Close) throw bad_xml;
        i++;
        return BasicPrologNode(name, attrs);
    }

    BasicPrologNode Xml::Lexer::take_data_node(std::string_view::iterator &i)
    {
        std::string name = take_word(i);
        qDebug() << "Data" << name.c_str();
        BasicAttrs attrs = take_attributes(i, Token::Close);
        skip_whitespace(i);
        if(*i++ != Token::Close) throw bad_xml;
        auto root = BasicPrologNode(name, attrs);
        i = parse(i, &root);

        return root;
    }

    BasicPrologNode Xml::Lexer::take_node(std::string_view::iterator &i)
    {
        if (*i == Token::Prolog) return take_prolog_node(++i);
        else take_data_node(i);
    }

    std::string_view::iterator
    Xml::Lexer::parse(std::string_view s, BasicPrologNode *root)
    {
        char token;
        auto begin = s.begin();
        auto end = s.end();
        BasicPrologNodes nodes;

        skip_whitespace(begin);
        while (begin != end && (token = *begin++) != Token::Close)
        {
            if(token == Token::Open)
            {
                if (*begin == Token::Break) {
                    auto i = begin;
                    auto name = take_word(++i);
                    if (name != root->name) throw bad_xml;
                    skip_whitespace(i);
                    begin = ++i;
                }
                else nodes.push_back(take_node(begin));
            }

            skip_whitespace(begin);
        }
        return begin;
    }

    void
    Xml::Lexer::parse(std::ifstream &s)
    {

    }

    void
    Xml::parse(std::ifstream &fin) throw()
    {
        std::string line;
        Lexer lexer;
        Parser parser;
        if (fin.is_open())
        {

        }
    }

} // namespace Freedom
