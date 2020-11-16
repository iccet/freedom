#ifndef FREEDOM_BAD_XML_H
#define FREEDOM_BAD_XML_H
#include <exception>

namespace Freedom {
    class BadXml : public std::exception
    {
        virtual const char* what() const throw()
        {
            return "Invalid xml syntax.";
        }
    } bad_xml;
}

#endif //FREEDOM_BAD_XML_H
