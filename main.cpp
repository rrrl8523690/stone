#include <iostream>
#include <fstream>
#include "ds/Array.hpp"
#include "ds/String.hpp"
#include "stone/Message.hpp"
#include "ds/ArrayUnitTest.hpp"
#include "ds/StringUnitTest.hpp"
#include "stone/Interpreter.hpp"
#include "stone/MapEnv.hpp"
#include "ds/MapUnitTest.hpp"
#include "stone/Lexer.hpp"
#include "stone/Parser.hpp"
#include "stone/ASTPrinter.hpp"
#include "stone/Data.hpp"


void dsUnitTest() {
    ArrayUnitTest::run();
    StringUnitTest::run();

}

void stoneTest() {
    using namespace stone;
    using namespace ds;
    std::fstream inputFileStream("test.stone", std::ios::in);
    String<> code;
    char ch;
    while ((ch = inputFileStream.get()) != EOF) {
        code.append(ch);
    }
    std::cerr << code << std::endl;
    Lexer *lexer = new Lexer(&code);
    Token *token;
    String<> descriptor[] = {"Id", "Keyword", "Str", "Num", "Err", "Op", "Sym",};
    uint lastLineNumber = 1;
    while ((token = lexer->read())) {
        if (lastLineNumber != token->lineNumber())
            std::cerr << std::endl;
        std::cerr << "(" << descriptor[token->type()] << ", " << token->string() << ", " << token->lineNumber() << ", "
                  << token->kth() << ")" << " ";
        //if (token->type() == Token::OP) {
        //if (((OpToken*)token)->getOperator(2))
        //std::cerr << ((OpToken*)token)->getOperator(2)->type() << std::endl;
        //}
        lastLineNumber = token->lineNumber();
    }

    // parse
    cerr << endl << endl;
    lexer = new Lexer(&code);
    MsgHandler *msgHandler = new MsgPrinter(std::cerr);
    Parser *parser = new Parser(lexer, msgHandler);
    AST *ast = parser->parse();
    cerr << endl;
    ASTVisitor *visitor = new ASTPrinter(std::cerr);
    if (!ast)cerr << "null ast" << endl;
    ast->accept(visitor);
    cerr << endl;

    // interpret
    //shared_ptr<Env> env(new MapEnv(nullptr, nullptr));
    Interpreter *interpreter = new Interpreter();
    ast->accept(interpreter);
}

int main() {
    using namespace std;
//    ArrayUnitTest::run();
//    StringUnitTest::run();
    //MapUnitTest::run();
    stoneTest();
    //stoneParserTest();
    //visitorTest();
    //stoneLexerTest();
    //test();
    return 0;
}