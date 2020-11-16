#include <QtTest>
#include <filesystem>

#include "../../src/abstract_lexer.cpp"
#include "../../src/json.cpp"
#include "../../src/common.hpp"

using namespace Freedom;

#define REGULAR_FILE_PATH "regular.Json"
#define COMPRESSED_FILE_PATH "compressed.Json"
#define BEAUTIFIED_FILE_PATH "large.Json"
#define LARGE_FILE_PATH "beautified.Json"

Q_DECLARE_METATYPE(std::string)

class JsonTestCase : public QObject
{
    Q_OBJECT
    std::ifstream _input_file_stream;
    std::ofstream _compressed;
    std::ofstream _beautified;
    Json::Lexer _lexer;
    Json::Parser _parser;
    std::filesystem::path _current_path = std::filesystem::current_path();

public:
    JsonTestCase() = default;
    ~JsonTestCase() = default;

private slots:
    void initTestCase();
    void initTestCase_data();
    void init();
    void cleanupTestCase();

    void jsonLexerTestCase();
    void jsonParsingTestCase();
    void jsonCompressingTestCase();
    void jsonBeautifyTestCase();
};

void JsonTestCase::initTestCase() {
    _compressed = std::ofstream(_current_path / COMPRESSED_FILE_PATH);
    _beautified = std::ofstream(_current_path / BEAUTIFIED_FILE_PATH);
}

void JsonTestCase::initTestCase_data() {
    QTest::addColumn<std::string>("path");
    QTest::newRow("regular") << (_current_path / REGULAR_FILE_PATH).string();
    QTest::newRow("large") << (_current_path / LARGE_FILE_PATH).string();
}

void JsonTestCase::init()
{
    QFETCH_GLOBAL(std::string, path);
    _input_file_stream = std::ifstream(path);
}

void JsonTestCase::jsonLexerTestCase()
{
    _lexer.parse_text(_input_file_stream);

    QString s;
    QTextStream out(&s);
    out << _lexer;
    qDebug() << s;
}

void JsonTestCase::jsonCompressingTestCase()
{
    reopen(_input_file_stream, REGULAR_FILE_PATH, std::ios::in);
    Json().compress();
}

void JsonTestCase::jsonBeautifyTestCase()
{
    reopen(_input_file_stream, COMPRESSED_FILE_PATH, std::ios::in);
    Json().beautify();
}

void JsonTestCase::jsonParsingTestCase()
{
}

void JsonTestCase::cleanupTestCase()
{
    _input_file_stream.close();
    _beautified.close();
    _compressed.close();
}

QTEST_APPLESS_MAIN(JsonTestCase)

#include "tst_jsontestcase.moc"
