#include <QtTest>
#include <filesystem>

#include "../../src/xml.cpp"
#include "../../src/abstract_lexer.cpp"
#include "../../src/abstract_parser.cpp"
#include "../../src/common.cpp"

using namespace Freedom;

#define REGULAR_FILE_PATH "regular.xml"
#define LARGE_FILE_PATH "large.xml"
#define COMPRESSED_FILE_PATH "compressed.xml"
#define BEAUTIFIED_FILE_PATH "beautified.xml"

#define QUOTES(arg) #arg
#define XML_DOCUMENT(...) stringify(__VA_ARGS__)

#define XML_RECT                       QUOTES(<rect><x>0</x><y>0</y><width>740</width><height>406</height></rect></node>)
#define INVALID_XML_PROLOG             QUOTES(<? xml version='1.0' encoding="UTF-8"?>)
#define XML_PROLOG                     QUOTES(<?xml version='1.0' encoding="UTF-8"?>)
#define XML_NODE                       QUOTES(<node></node>)
#define XML_NODE_WITH_ATTRS            QUOTES(<node class="QMainWindow" name="MainWindow"><node class="" name=""></node></node>)
#define INVALID_HIERARCHY              QUOTES(<node><inner></node></inner>)

#define INVALID_XML_PROLOG_DOCUMENT    XML_DOCUMENT(INVALID_XML_PROLOG)
#define EMPTY_XML_DOCUMENT             XML_DOCUMENT(XML_PROLOG, XML_NODE)
#define INVALID_XML_HIERARCHY_DOCUMENT XML_DOCUMENT(XML_PROLOG, INVALID_HIERARCHY)
#define NESTED_XML_DOCUMENT            XML_DOCUMENT(XML_PROLOG, XML_RECT, XML_NODE_WITH_ATTRS)

Q_DECLARE_METATYPE(std::string)

class XmlTestCase : public QObject
{
    Q_OBJECT
    std::ifstream _input_file_stream;
    std::ofstream _compressed;
    std::ofstream _beautified;
    Xml::Lexer _lexer;
    Xml::Parser _parser;
    std::filesystem::path _current_path = std::filesystem::current_path();

public:
    XmlTestCase() = default;
    ~XmlTestCase() = default;

private slots:
    void initTestCase();
    void initTestCase_data();
    void init();
    void cleanupTestCase();

    void xml_lexer_test_case();
    void xml_parsing_test_case();
    void xml_compressing_test_case();
    void xml_beautify_test_case();
};


void XmlTestCase::initTestCase() {
    _compressed = std::ofstream(_current_path / COMPRESSED_FILE_PATH);
    _beautified = std::ofstream(_current_path / BEAUTIFIED_FILE_PATH);
}

void XmlTestCase::initTestCase_data() {
    QTest::addColumn<std::string>("path");
    QTest::newRow("regular") << (_current_path / REGULAR_FILE_PATH).string();
    QTest::newRow("large") << (_current_path / LARGE_FILE_PATH).string();
}

void XmlTestCase::init()
{
    QFETCH_GLOBAL(std::string, path);
    _input_file_stream = std::ifstream(path);
}

void XmlTestCase::xml_lexer_test_case()
{
    _lexer.parse(_input_file_stream);
    _lexer.parse(EMPTY_XML_DOCUMENT);
    _lexer.parse(NESTED_XML_DOCUMENT);

    QVERIFY_EXCEPTION_THROWN(_lexer.parse(INVALID_XML_PROLOG_DOCUMENT), BadXml);
    QVERIFY_EXCEPTION_THROWN(_lexer.parse(INVALID_XML_HIERARCHY_DOCUMENT), BadXml);

    QString s;
    QTextStream out(&s);
    out << _lexer;
    qDebug() << s;
}

void XmlTestCase::xml_compressing_test_case()
{
    reopen(_input_file_stream, REGULAR_FILE_PATH, std::ios::in);
}

void XmlTestCase::xml_beautify_test_case()
{
    reopen(_input_file_stream, REGULAR_FILE_PATH, std::ios::in);
}

void XmlTestCase::xml_parsing_test_case()
{
    reopen(_input_file_stream, REGULAR_FILE_PATH, std::ios::in);
    Xml xml;
    xml.parse(_input_file_stream);
}

void XmlTestCase::cleanupTestCase()
{
    _input_file_stream.close();
    _beautified.close();
    _compressed.close();
}

QTEST_APPLESS_MAIN(XmlTestCase)

#include "tst_xmltestcase.moc"
