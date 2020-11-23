#ifndef ABSTRACTLEXER_HPP
#define ABSTRACTLEXER_HPP

#include <QtGlobal>

#include "freedom_global.hpp"
#include "common.hpp"
#include "xml.hpp"

namespace Freedom
{
    using String = std::string;
    template<class T>
    using Attribute = std::pair<std::string, T>;

    template<class ... Args>
    using Attributes = std::vector<std::variant<Attribute<Args> ...>>;

    using BasicAttrs = Attributes<uint64_t, std::string>;

    template<class ... Args>
    struct BaseNode {
        std::string name;
        Attributes<Args ...> attrs;

        BaseNode(std::string _name) : name(_name) { }
        BaseNode(std::string _name, Attributes<Args ...> _attrs)
                : attrs {_attrs}
                , name(_name) { }
        virtual ~BaseNode() = default;
    };

    template<class ... Args> struct Node;

    template<class ... Args>
    using Nodes = std::vector<BaseNode<Args ...>>;

    template<class ... Args>
    struct Node : public BaseNode<Args ...> {
        using Base = BaseNode<Args ...>;

        String value;
        Nodes<Args ...> nodes;

        Node(std::string _name) : Base(_name) { }
        Node(std::string _name, Attributes<Args ...> _attrs)
                : Base(_name, _attrs) { }
    };

    using PrologNode = BaseNode<uint64_t, std::string>;
    using PrologNodes = std::vector<PrologNode>;

    using DataNode = Node<uint64_t, std::string>;
    using DataNodes = std::vector<DataNode>;


    class FREEDOM_EXPORT AbstractLexer
    {
    public:
        NON_COPY_AND_MOVE_CLASS_DECL(AbstractLexer)
        virtual std::string_view::iterator parse(std::string_view s, PrologNode *root=nullptr) = 0;
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
