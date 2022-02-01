
// Generated from Code.g4 by ANTLR 4.9.3

#pragma once


#include "antlr4-runtime.h"




class  CodeParser : public antlr4::Parser {
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

  enum {
    RuleFile = 0, RuleExpressions = 1, RuleExpression = 2, RuleMulti_line_expr = 3, 
    RuleMany_one_line_exprs = 4, RuleOne_line_expr = 5, RulePrint = 6, RuleInput = 7, 
    RuleVar_ass = 8, RuleInit = 9, RuleOperation = 10, RuleIf_statement = 11, 
    RuleElif_statement = 12, RuleElse_statement = 13, RuleWhile_statement = 14, 
    RuleFor_statement = 15, RuleRange = 16, RuleAfter_colon = 17, RuleDisj = 18, 
    RuleConj = 19, RuleNegate = 20, RuleComparison = 21, RuleSum_term = 22, 
    RuleMul_term = 23, RuleTerm = 24, RuleAtom = 25, RuleBool_lit = 26
  };

  explicit CodeParser(antlr4::TokenStream *input);
  ~CodeParser();

  virtual std::string getGrammarFileName() const override;
  virtual const antlr4::atn::ATN& getATN() const override { return _atn; };
  virtual const std::vector<std::string>& getTokenNames() const override { return _tokenNames; }; // deprecated: use vocabulary instead.
  virtual const std::vector<std::string>& getRuleNames() const override;
  virtual antlr4::dfa::Vocabulary& getVocabulary() const override;


  class FileContext;
  class ExpressionsContext;
  class ExpressionContext;
  class Multi_line_exprContext;
  class Many_one_line_exprsContext;
  class One_line_exprContext;
  class PrintContext;
  class InputContext;
  class Var_assContext;
  class InitContext;
  class OperationContext;
  class If_statementContext;
  class Elif_statementContext;
  class Else_statementContext;
  class While_statementContext;
  class For_statementContext;
  class RangeContext;
  class After_colonContext;
  class DisjContext;
  class ConjContext;
  class NegateContext;
  class ComparisonContext;
  class Sum_termContext;
  class Mul_termContext;
  class TermContext;
  class AtomContext;
  class Bool_litContext; 

  class  FileContext : public antlr4::ParserRuleContext {
  public:
    FileContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    ExpressionsContext *expressions();
    antlr4::tree::TerminalNode *EOF();


    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  FileContext* file();

  class  ExpressionsContext : public antlr4::ParserRuleContext {
  public:
    ExpressionsContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    std::vector<ExpressionContext *> expression();
    ExpressionContext* expression(size_t i);


    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  ExpressionsContext* expressions();

  class  ExpressionContext : public antlr4::ParserRuleContext {
  public:
    ExpressionContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    Many_one_line_exprsContext *many_one_line_exprs();
    Multi_line_exprContext *multi_line_expr();
    std::vector<antlr4::tree::TerminalNode *> TAB();
    antlr4::tree::TerminalNode* TAB(size_t i);


    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  ExpressionContext* expression();

  class  Multi_line_exprContext : public antlr4::ParserRuleContext {
  public:
    Multi_line_exprContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    If_statementContext *if_statement();
    Elif_statementContext *elif_statement();
    Else_statementContext *else_statement();
    While_statementContext *while_statement();
    For_statementContext *for_statement();


    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  Multi_line_exprContext* multi_line_expr();

  class  Many_one_line_exprsContext : public antlr4::ParserRuleContext {
  public:
    Many_one_line_exprsContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    std::vector<One_line_exprContext *> one_line_expr();
    One_line_exprContext* one_line_expr(size_t i);
    std::vector<antlr4::tree::TerminalNode *> SEMICOL();
    antlr4::tree::TerminalNode* SEMICOL(size_t i);
    antlr4::tree::TerminalNode *NEW_LINE();


    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  Many_one_line_exprsContext* many_one_line_exprs();

  class  One_line_exprContext : public antlr4::ParserRuleContext {
  public:
    One_line_exprContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    Var_assContext *var_ass();
    OperationContext *operation();
    antlr4::tree::TerminalNode *BREAK();
    antlr4::tree::TerminalNode *CONTINUE();
    PrintContext *print();


    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  One_line_exprContext* one_line_expr();

  class  PrintContext : public antlr4::ParserRuleContext {
  public:
    PrintContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *PRINT();
    antlr4::tree::TerminalNode *LPAR();
    std::vector<OperationContext *> operation();
    OperationContext* operation(size_t i);
    antlr4::tree::TerminalNode *RPAR();
    std::vector<antlr4::tree::TerminalNode *> COMMA();
    antlr4::tree::TerminalNode* COMMA(size_t i);


    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  PrintContext* print();

  class  InputContext : public antlr4::ParserRuleContext {
  public:
    InputContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *FLOAT_TYPE();
    std::vector<antlr4::tree::TerminalNode *> LPAR();
    antlr4::tree::TerminalNode* LPAR(size_t i);
    antlr4::tree::TerminalNode *INPUT();
    std::vector<antlr4::tree::TerminalNode *> RPAR();
    antlr4::tree::TerminalNode* RPAR(size_t i);
    antlr4::tree::TerminalNode *INT_TYPE();


    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  InputContext* input();

  class  Var_assContext : public antlr4::ParserRuleContext {
  public:
    Var_assContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    std::vector<antlr4::tree::TerminalNode *> IDENTIFICATOR();
    antlr4::tree::TerminalNode* IDENTIFICATOR(size_t i);
    std::vector<InitContext *> init();
    InitContext* init(size_t i);
    std::vector<antlr4::tree::TerminalNode *> COMMA();
    antlr4::tree::TerminalNode* COMMA(size_t i);


    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  Var_assContext* var_ass();

  class  InitContext : public antlr4::ParserRuleContext {
  public:
    InitContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    OperationContext *operation();
    InputContext *input();


    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  InitContext* init();

  class  OperationContext : public antlr4::ParserRuleContext {
  public:
    OperationContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    DisjContext *disj();


    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  OperationContext* operation();

  class  If_statementContext : public antlr4::ParserRuleContext {
  public:
    CodeParser::OperationContext *cond = nullptr;
    CodeParser::After_colonContext *block = nullptr;
    If_statementContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *IF();
    antlr4::tree::TerminalNode *COLON();
    OperationContext *operation();
    After_colonContext *after_colon();


    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  If_statementContext* if_statement();

  class  Elif_statementContext : public antlr4::ParserRuleContext {
  public:
    CodeParser::OperationContext *cond = nullptr;
    CodeParser::After_colonContext *block = nullptr;
    Elif_statementContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *ELIF();
    antlr4::tree::TerminalNode *COLON();
    OperationContext *operation();
    After_colonContext *after_colon();


    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  Elif_statementContext* elif_statement();

  class  Else_statementContext : public antlr4::ParserRuleContext {
  public:
    CodeParser::After_colonContext *block = nullptr;
    Else_statementContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *ELSE();
    antlr4::tree::TerminalNode *COLON();
    After_colonContext *after_colon();


    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  Else_statementContext* else_statement();

  class  While_statementContext : public antlr4::ParserRuleContext {
  public:
    CodeParser::OperationContext *cond = nullptr;
    CodeParser::After_colonContext *block = nullptr;
    While_statementContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *WHILE();
    antlr4::tree::TerminalNode *COLON();
    OperationContext *operation();
    After_colonContext *after_colon();


    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  While_statementContext* while_statement();

  class  For_statementContext : public antlr4::ParserRuleContext {
  public:
    CodeParser::After_colonContext *block = nullptr;
    For_statementContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *FOR();
    antlr4::tree::TerminalNode *IDENTIFICATOR();
    antlr4::tree::TerminalNode *IN();
    antlr4::tree::TerminalNode *RANGE();
    antlr4::tree::TerminalNode *LPAR();
    RangeContext *range();
    antlr4::tree::TerminalNode *RPAR();
    antlr4::tree::TerminalNode *COLON();
    After_colonContext *after_colon();


    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  For_statementContext* for_statement();

  class  RangeContext : public antlr4::ParserRuleContext {
  public:
    antlr4::Token *to = nullptr;
    antlr4::Token *from = nullptr;
    antlr4::Token *step = nullptr;
    RangeContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    std::vector<antlr4::tree::TerminalNode *> INT();
    antlr4::tree::TerminalNode* INT(size_t i);
    std::vector<antlr4::tree::TerminalNode *> COMMA();
    antlr4::tree::TerminalNode* COMMA(size_t i);


    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  RangeContext* range();

  class  After_colonContext : public antlr4::ParserRuleContext {
  public:
    After_colonContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    Many_one_line_exprsContext *many_one_line_exprs();
    antlr4::tree::TerminalNode *NEW_LINE();
    ExpressionsContext *expressions();


    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  After_colonContext* after_colon();

  class  DisjContext : public antlr4::ParserRuleContext {
  public:
    CodeParser::DisjContext *lhs = nullptr;
    CodeParser::ConjContext *val = nullptr;
    CodeParser::ConjContext *rhs = nullptr;
    DisjContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    ConjContext *conj();
    antlr4::tree::TerminalNode *OR();
    DisjContext *disj();


    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  DisjContext* disj();
  DisjContext* disj(int precedence);
  class  ConjContext : public antlr4::ParserRuleContext {
  public:
    CodeParser::ConjContext *lhs = nullptr;
    CodeParser::NegateContext *val = nullptr;
    CodeParser::NegateContext *rhs = nullptr;
    ConjContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    NegateContext *negate();
    antlr4::tree::TerminalNode *AND();
    ConjContext *conj();


    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  ConjContext* conj();
  ConjContext* conj(int precedence);
  class  NegateContext : public antlr4::ParserRuleContext {
  public:
    antlr4::Token *op = nullptr;
    CodeParser::NegateContext *arg = nullptr;
    CodeParser::ComparisonContext *val = nullptr;
    NegateContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *NOT();
    NegateContext *negate();
    ComparisonContext *comparison();


    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  NegateContext* negate();

  class  ComparisonContext : public antlr4::ParserRuleContext {
  public:
    CodeParser::ComparisonContext *lhs = nullptr;
    CodeParser::Sum_termContext *val = nullptr;
    antlr4::Token *op = nullptr;
    CodeParser::Sum_termContext *rhs = nullptr;
    ComparisonContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    Sum_termContext *sum_term();
    ComparisonContext *comparison();
    antlr4::tree::TerminalNode *COMPARE_OP();


    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  ComparisonContext* comparison();
  ComparisonContext* comparison(int precedence);
  class  Sum_termContext : public antlr4::ParserRuleContext {
  public:
    CodeParser::Sum_termContext *lhs = nullptr;
    CodeParser::Mul_termContext *val = nullptr;
    antlr4::Token *op = nullptr;
    CodeParser::Mul_termContext *rhs = nullptr;
    Sum_termContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    Mul_termContext *mul_term();
    Sum_termContext *sum_term();
    antlr4::tree::TerminalNode *ADD_OP();


    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  Sum_termContext* sum_term();
  Sum_termContext* sum_term(int precedence);
  class  Mul_termContext : public antlr4::ParserRuleContext {
  public:
    CodeParser::Mul_termContext *lhs = nullptr;
    CodeParser::TermContext *val = nullptr;
    antlr4::Token *op = nullptr;
    CodeParser::TermContext *rhs = nullptr;
    Mul_termContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    TermContext *term();
    Mul_termContext *mul_term();
    antlr4::tree::TerminalNode *MUL_OP();


    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  Mul_termContext* mul_term();
  Mul_termContext* mul_term(int precedence);
  class  TermContext : public antlr4::ParserRuleContext {
  public:
    antlr4::Token *op = nullptr;
    CodeParser::TermContext *arg = nullptr;
    CodeParser::AtomContext *val = nullptr;
    TermContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *ADD_OP();
    TermContext *term();
    AtomContext *atom();


    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  TermContext* term();

  class  AtomContext : public antlr4::ParserRuleContext {
  public:
    AtomContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    Bool_litContext *bool_lit();
    antlr4::tree::TerminalNode *IDENTIFICATOR();
    antlr4::tree::TerminalNode *STRING();
    antlr4::tree::TerminalNode *NUM();
    antlr4::tree::TerminalNode *INT();
    antlr4::tree::TerminalNode *LPAR();
    OperationContext *operation();
    antlr4::tree::TerminalNode *RPAR();


    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  AtomContext* atom();

  class  Bool_litContext : public antlr4::ParserRuleContext {
  public:
    Bool_litContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *TRUE();
    antlr4::tree::TerminalNode *FALSE();


    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  Bool_litContext* bool_lit();


  virtual bool sempred(antlr4::RuleContext *_localctx, size_t ruleIndex, size_t predicateIndex) override;
  bool disjSempred(DisjContext *_localctx, size_t predicateIndex);
  bool conjSempred(ConjContext *_localctx, size_t predicateIndex);
  bool comparisonSempred(ComparisonContext *_localctx, size_t predicateIndex);
  bool sum_termSempred(Sum_termContext *_localctx, size_t predicateIndex);
  bool mul_termSempred(Mul_termContext *_localctx, size_t predicateIndex);

private:
  static std::vector<antlr4::dfa::DFA> _decisionToDFA;
  static antlr4::atn::PredictionContextCache _sharedContextCache;
  static std::vector<std::string> _ruleNames;
  static std::vector<std::string> _tokenNames;

  static std::vector<std::string> _literalNames;
  static std::vector<std::string> _symbolicNames;
  static antlr4::dfa::Vocabulary _vocabulary;
  static antlr4::atn::ATN _atn;
  static std::vector<uint16_t> _serializedATN;


  struct Initializer {
    Initializer();
  };
  static Initializer _init;
};

