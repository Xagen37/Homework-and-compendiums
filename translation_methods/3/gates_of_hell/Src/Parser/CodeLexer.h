
// Generated from Code.g4 by ANTLR 4.9.3

#pragma once


#include "antlr4-runtime.h"




class  CodeLexer : public antlr4::Lexer {
public:
  enum {
    T__0 = 1, AND = 2, BREAK = 3, BOOL_TYPE = 4, COMMA = 5, CONTINUE = 6, 
    DEF = 7, COLON = 8, ELIF = 9, ELSE = 10, FALSE = 11, FLOAT_TYPE = 12, 
    FOR = 13, IF = 14, INPUT = 15, INT_TYPE = 16, IN = 17, NOT = 18, OR = 19, 
    PRINT = 20, RANGE = 21, SEMICOL = 22, STRING_TYPE = 23, TRUE = 24, WHILE = 25, 
    LPAR = 26, RPAR = 27, IDENTIFICATOR = 28, COMPARE_OP = 29, INT = 30, 
    NUM = 31, ADD_OP = 32, MUL_OP = 33, STRING = 34, NEW_LINE = 35, TAB = 36, 
    WHITESPACE = 37
  };

  explicit CodeLexer(antlr4::CharStream *input);
  ~CodeLexer();

  virtual std::string getGrammarFileName() const override;
  virtual const std::vector<std::string>& getRuleNames() const override;

  virtual const std::vector<std::string>& getChannelNames() const override;
  virtual const std::vector<std::string>& getModeNames() const override;
  virtual const std::vector<std::string>& getTokenNames() const override; // deprecated, use vocabulary instead
  virtual antlr4::dfa::Vocabulary& getVocabulary() const override;

  virtual const std::vector<uint16_t> getSerializedATN() const override;
  virtual const antlr4::atn::ATN& getATN() const override;

private:
  static std::vector<antlr4::dfa::DFA> _decisionToDFA;
  static antlr4::atn::PredictionContextCache _sharedContextCache;
  static std::vector<std::string> _ruleNames;
  static std::vector<std::string> _tokenNames;
  static std::vector<std::string> _channelNames;
  static std::vector<std::string> _modeNames;

  static std::vector<std::string> _literalNames;
  static std::vector<std::string> _symbolicNames;
  static antlr4::dfa::Vocabulary _vocabulary;
  static antlr4::atn::ATN _atn;
  static std::vector<uint16_t> _serializedATN;


  // Individual action functions triggered by action() above.

  // Individual semantic predicate functions triggered by sempred() above.

  struct Initializer {
    Initializer();
  };
  static Initializer _init;
};

