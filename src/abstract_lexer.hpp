#ifndef ABSTRACTLEXER_HPP
#define ABSTRACTLEXER_HPP

#include <QtGlobal>

#include "freedom_global.hpp"
#include "common.hpp"
#include "xml.hpp"

namespace Freedom
{
    template<class T>
    using Attr = std::pair<std::string, T>;

    template<class ... Args>
    using Attrs = std::vector<std::variant<Attr<Args> ...>>;

    template<class ... Args>
    struct PrologNode {
        std::string name;
        Attrs<Args ...> attrs;

        PrologNode(std::string _name) : name(_name) { }
        PrologNode(std::string _name, Attrs<Args ...> _attrs)
                : attrs {_attrs}
                , name(_name) { }
    };

    template<class ... Args> struct Node;

    template<class ... Args>
    using Nodes = std::vector<Node<Args ...>>;

    template<class ... Args>
    struct Node : public PrologNode<Args ...> {
        using Base = PrologNode<Args ...>;

        Nodes<Args ...> nodes;

        Node(std::string _name) : Base(_name) { }
        Node(std::string _name, Attrs<Args ...> _attrs, Nodes<Args ...> _nodes)
                : Base(_name, _attrs)
                , nodes(_nodes) { }
    };

    using BasicAttrs = Attrs<uint64_t, std::string>;
    using BasicPrologNode = PrologNode<uint64_t, std::string>;
    using BasicPrologNodes = std::vector<BasicPrologNode>;

    class FREEDOM_EXPORT AbstractLexer
    {
    public:
        NON_COPY_AND_MOVE_CLASS_DECL(AbstractLexer)
        virtual std::string_view::iterator parse(std::string_view s, BasicPrologNode *root=nullptr) = 0;
        virtual void parse(std::ifstream &);

        template<class TStream>
        friend
        TStream &
        operator<<(TStream &,
                   const AbstractLexer&);

    protected:
        std::vector<std::string> _lexemes;
    };

    template<class TStream>
    TStream &operator<<(TStream &out,
                        const AbstractLexer &lexer);

    template<>
    QTextStream &operator<<(QTextStream &out,
                            const AbstractLexer &lexer);

} // namespace Freedom

#endif // ABSTRACTLEXER_HPP
