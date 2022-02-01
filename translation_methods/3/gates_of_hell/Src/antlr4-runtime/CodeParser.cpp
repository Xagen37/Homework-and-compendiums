
// Generated from c:\Users\Sofr1\Documents\GitHub\Antlr4ConanExample\Src\Code.g4 by ANTLR 4.8


#include "CodeVisitor.h"

#include "CodeParser.h"


using namespace antlrcpp;
using namespace antlr4;

CodeParser::CodeParser(TokenStream *input) : Parser(input) {
  _interpreter = new atn::ParserATNSimulator(this, _atn, _decisionToDFA, _sharedContextCache);
}

CodeParser::~CodeParser() {
  delete _interpreter;
}

std::string CodeParser::getGrammarFileName() const {
  return "Code.g4";
}

const std::vector<std::string>& CodeParser::getRuleNames() const {
  return _ruleNames;
}

dfa::Vocabulary& CodeParser::getVocabulary() const {
  return _vocabulary;
}


//----------------- FileContext ------------------------------------------------------------------

CodeParser::FileContext::FileContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

CodeParser::ExpressionsContext* CodeParser::FileContext::expressions() {
  return getRuleContext<CodeParser::ExpressionsContext>(0);
}

tree::TerminalNode* CodeParser::FileContext::EOF() {
  return getToken(CodeParser::EOF, 0);
}


size_t CodeParser::FileContext::getRuleIndex() const {
  return CodeParser::RuleFile;
}


antlrcpp::Any CodeParser::FileContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<CodeVisitor*>(visitor))
    return parserVisitor->visitFile(this);
  else
    return visitor->visitChildren(this);
}

CodeParser::FileContext* CodeParser::file() {
  FileContext *_localctx = _tracker.createInstance<FileContext>(_ctx, getState());
  enterRule(_localctx, 0, CodeParser::RuleFile);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(54);
    expressions();
    setState(55);
    match(CodeParser::EOF);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- ExpressionsContext ------------------------------------------------------------------

CodeParser::ExpressionsContext::ExpressionsContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<CodeParser::ExpressionContext *> CodeParser::ExpressionsContext::expression() {
  return getRuleContexts<CodeParser::ExpressionContext>();
}

CodeParser::ExpressionContext* CodeParser::ExpressionsContext::expression(size_t i) {
  return getRuleContext<CodeParser::ExpressionContext>(i);
}


size_t CodeParser::ExpressionsContext::getRuleIndex() const {
  return CodeParser::RuleExpressions;
}


antlrcpp::Any CodeParser::ExpressionsContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<CodeVisitor*>(visitor))
    return parserVisitor->visitExpressions(this);
  else
    return visitor->visitChildren(this);
}

CodeParser::ExpressionsContext* CodeParser::expressions() {
  ExpressionsContext *_localctx = _tracker.createInstance<ExpressionsContext>(_ctx, getState());
  enterRule(_localctx, 2, CodeParser::RuleExpressions);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    size_t alt;
    enterOuterAlt(_localctx, 1);
    setState(58); 
    _errHandler->sync(this);
    alt = 1;
    do {
      switch (alt) {
        case 1: {
              setState(57);
              expression();
              break;
            }

      default:
        throw NoViableAltException(this);
      }
      setState(60); 
      _errHandler->sync(this);
      alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 0, _ctx);
    } while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- ExpressionContext ------------------------------------------------------------------

CodeParser::ExpressionContext::ExpressionContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

CodeParser::Many_one_line_exprsContext* CodeParser::ExpressionContext::many_one_line_exprs() {
  return getRuleContext<CodeParser::Many_one_line_exprsContext>(0);
}

CodeParser::Multi_line_exprContext* CodeParser::ExpressionContext::multi_line_expr() {
  return getRuleContext<CodeParser::Multi_line_exprContext>(0);
}

std::vector<tree::TerminalNode *> CodeParser::ExpressionContext::TAB() {
  return getTokens(CodeParser::TAB);
}

tree::TerminalNode* CodeParser::ExpressionContext::TAB(size_t i) {
  return getToken(CodeParser::TAB, i);
}


size_t CodeParser::ExpressionContext::getRuleIndex() const {
  return CodeParser::RuleExpression;
}


antlrcpp::Any CodeParser::ExpressionContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<CodeVisitor*>(visitor))
    return parserVisitor->visitExpression(this);
  else
    return visitor->visitChildren(this);
}

CodeParser::ExpressionContext* CodeParser::expression() {
  ExpressionContext *_localctx = _tracker.createInstance<ExpressionContext>(_ctx, getState());
  enterRule(_localctx, 4, CodeParser::RuleExpression);
  size_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(65);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == CodeParser::TAB) {
      setState(62);
      match(CodeParser::TAB);
      setState(67);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
    setState(70);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case CodeParser::BREAK:
      case CodeParser::CONTINUE:
      case CodeParser::FALSE:
      case CodeParser::NOT:
      case CodeParser::PRINT:
      case CodeParser::TRUE:
      case CodeParser::LPAR:
      case CodeParser::IDENTIFICATOR:
      case CodeParser::INT:
      case CodeParser::NUM:
      case CodeParser::ADD_OP:
      case CodeParser::STRING: {
        setState(68);
        many_one_line_exprs();
        break;
      }

      case CodeParser::ELIF:
      case CodeParser::ELSE:
      case CodeParser::FOR:
      case CodeParser::IF:
      case CodeParser::WHILE: {
        setState(69);
        multi_line_expr();
        break;
      }

    default:
      throw NoViableAltException(this);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- Multi_line_exprContext ------------------------------------------------------------------

CodeParser::Multi_line_exprContext::Multi_line_exprContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

CodeParser::If_statementContext* CodeParser::Multi_line_exprContext::if_statement() {
  return getRuleContext<CodeParser::If_statementContext>(0);
}

CodeParser::Elif_statementContext* CodeParser::Multi_line_exprContext::elif_statement() {
  return getRuleContext<CodeParser::Elif_statementContext>(0);
}

CodeParser::Else_statementContext* CodeParser::Multi_line_exprContext::else_statement() {
  return getRuleContext<CodeParser::Else_statementContext>(0);
}

CodeParser::While_statementContext* CodeParser::Multi_line_exprContext::while_statement() {
  return getRuleContext<CodeParser::While_statementContext>(0);
}

CodeParser::For_statementContext* CodeParser::Multi_line_exprContext::for_statement() {
  return getRuleContext<CodeParser::For_statementContext>(0);
}


size_t CodeParser::Multi_line_exprContext::getRuleIndex() const {
  return CodeParser::RuleMulti_line_expr;
}


antlrcpp::Any CodeParser::Multi_line_exprContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<CodeVisitor*>(visitor))
    return parserVisitor->visitMulti_line_expr(this);
  else
    return visitor->visitChildren(this);
}

CodeParser::Multi_line_exprContext* CodeParser::multi_line_expr() {
  Multi_line_exprContext *_localctx = _tracker.createInstance<Multi_line_exprContext>(_ctx, getState());
  enterRule(_localctx, 6, CodeParser::RuleMulti_line_expr);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    setState(77);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case CodeParser::IF: {
        enterOuterAlt(_localctx, 1);
        setState(72);
        if_statement();
        break;
      }

      case CodeParser::ELIF: {
        enterOuterAlt(_localctx, 2);
        setState(73);
        elif_statement();
        break;
      }

      case CodeParser::ELSE: {
        enterOuterAlt(_localctx, 3);
        setState(74);
        else_statement();
        break;
      }

      case CodeParser::WHILE: {
        enterOuterAlt(_localctx, 4);
        setState(75);
        while_statement();
        break;
      }

      case CodeParser::FOR: {
        enterOuterAlt(_localctx, 5);
        setState(76);
        for_statement();
        break;
      }

    default:
      throw NoViableAltException(this);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- Many_one_line_exprsContext ------------------------------------------------------------------

CodeParser::Many_one_line_exprsContext::Many_one_line_exprsContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<CodeParser::One_line_exprContext *> CodeParser::Many_one_line_exprsContext::one_line_expr() {
  return getRuleContexts<CodeParser::One_line_exprContext>();
}

CodeParser::One_line_exprContext* CodeParser::Many_one_line_exprsContext::one_line_expr(size_t i) {
  return getRuleContext<CodeParser::One_line_exprContext>(i);
}

std::vector<tree::TerminalNode *> CodeParser::Many_one_line_exprsContext::SEMICOL() {
  return getTokens(CodeParser::SEMICOL);
}

tree::TerminalNode* CodeParser::Many_one_line_exprsContext::SEMICOL(size_t i) {
  return getToken(CodeParser::SEMICOL, i);
}

tree::TerminalNode* CodeParser::Many_one_line_exprsContext::NEW_LINE() {
  return getToken(CodeParser::NEW_LINE, 0);
}


size_t CodeParser::Many_one_line_exprsContext::getRuleIndex() const {
  return CodeParser::RuleMany_one_line_exprs;
}


antlrcpp::Any CodeParser::Many_one_line_exprsContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<CodeVisitor*>(visitor))
    return parserVisitor->visitMany_one_line_exprs(this);
  else
    return visitor->visitChildren(this);
}

CodeParser::Many_one_line_exprsContext* CodeParser::many_one_line_exprs() {
  Many_one_line_exprsContext *_localctx = _tracker.createInstance<Many_one_line_exprsContext>(_ctx, getState());
  enterRule(_localctx, 8, CodeParser::RuleMany_one_line_exprs);
  size_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    size_t alt;
    enterOuterAlt(_localctx, 1);
    setState(79);
    one_line_expr();
    setState(84);
    _errHandler->sync(this);
    alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 4, _ctx);
    while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
      if (alt == 1) {
        setState(80);
        match(CodeParser::SEMICOL);
        setState(81);
        one_line_expr(); 
      }
      setState(86);
      _errHandler->sync(this);
      alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 4, _ctx);
    }
    setState(88);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == CodeParser::SEMICOL) {
      setState(87);
      match(CodeParser::SEMICOL);
    }
    setState(91);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == CodeParser::NEW_LINE) {
      setState(90);
      match(CodeParser::NEW_LINE);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- One_line_exprContext ------------------------------------------------------------------

CodeParser::One_line_exprContext::One_line_exprContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

CodeParser::Var_assContext* CodeParser::One_line_exprContext::var_ass() {
  return getRuleContext<CodeParser::Var_assContext>(0);
}

CodeParser::OperationContext* CodeParser::One_line_exprContext::operation() {
  return getRuleContext<CodeParser::OperationContext>(0);
}

tree::TerminalNode* CodeParser::One_line_exprContext::BREAK() {
  return getToken(CodeParser::BREAK, 0);
}

tree::TerminalNode* CodeParser::One_line_exprContext::CONTINUE() {
  return getToken(CodeParser::CONTINUE, 0);
}

CodeParser::PrintContext* CodeParser::One_line_exprContext::print() {
  return getRuleContext<CodeParser::PrintContext>(0);
}


size_t CodeParser::One_line_exprContext::getRuleIndex() const {
  return CodeParser::RuleOne_line_expr;
}


antlrcpp::Any CodeParser::One_line_exprContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<CodeVisitor*>(visitor))
    return parserVisitor->visitOne_line_expr(this);
  else
    return visitor->visitChildren(this);
}

CodeParser::One_line_exprContext* CodeParser::one_line_expr() {
  One_line_exprContext *_localctx = _tracker.createInstance<One_line_exprContext>(_ctx, getState());
  enterRule(_localctx, 10, CodeParser::RuleOne_line_expr);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    setState(98);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 7, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(93);
      var_ass();
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(94);
      operation();
      break;
    }

    case 3: {
      enterOuterAlt(_localctx, 3);
      setState(95);
      match(CodeParser::BREAK);
      break;
    }

    case 4: {
      enterOuterAlt(_localctx, 4);
      setState(96);
      match(CodeParser::CONTINUE);
      break;
    }

    case 5: {
      enterOuterAlt(_localctx, 5);
      setState(97);
      print();
      break;
    }

    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- PrintContext ------------------------------------------------------------------

CodeParser::PrintContext::PrintContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* CodeParser::PrintContext::PRINT() {
  return getToken(CodeParser::PRINT, 0);
}

tree::TerminalNode* CodeParser::PrintContext::LPAR() {
  return getToken(CodeParser::LPAR, 0);
}

std::vector<CodeParser::OperationContext *> CodeParser::PrintContext::operation() {
  return getRuleContexts<CodeParser::OperationContext>();
}

CodeParser::OperationContext* CodeParser::PrintContext::operation(size_t i) {
  return getRuleContext<CodeParser::OperationContext>(i);
}

tree::TerminalNode* CodeParser::PrintContext::RPAR() {
  return getToken(CodeParser::RPAR, 0);
}

std::vector<tree::TerminalNode *> CodeParser::PrintContext::COMMA() {
  return getTokens(CodeParser::COMMA);
}

tree::TerminalNode* CodeParser::PrintContext::COMMA(size_t i) {
  return getToken(CodeParser::COMMA, i);
}


size_t CodeParser::PrintContext::getRuleIndex() const {
  return CodeParser::RulePrint;
}


antlrcpp::Any CodeParser::PrintContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<CodeVisitor*>(visitor))
    return parserVisitor->visitPrint(this);
  else
    return visitor->visitChildren(this);
}

CodeParser::PrintContext* CodeParser::print() {
  PrintContext *_localctx = _tracker.createInstance<PrintContext>(_ctx, getState());
  enterRule(_localctx, 12, CodeParser::RulePrint);
  size_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(100);
    match(CodeParser::PRINT);
    setState(101);
    match(CodeParser::LPAR);
    setState(102);
    operation();
    setState(107);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == CodeParser::COMMA) {
      setState(103);
      match(CodeParser::COMMA);
      setState(104);
      operation();
      setState(109);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
    setState(110);
    match(CodeParser::RPAR);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- InputContext ------------------------------------------------------------------

CodeParser::InputContext::InputContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* CodeParser::InputContext::FLOAT_TYPE() {
  return getToken(CodeParser::FLOAT_TYPE, 0);
}

std::vector<tree::TerminalNode *> CodeParser::InputContext::LPAR() {
  return getTokens(CodeParser::LPAR);
}

tree::TerminalNode* CodeParser::InputContext::LPAR(size_t i) {
  return getToken(CodeParser::LPAR, i);
}

tree::TerminalNode* CodeParser::InputContext::INPUT() {
  return getToken(CodeParser::INPUT, 0);
}

std::vector<tree::TerminalNode *> CodeParser::InputContext::RPAR() {
  return getTokens(CodeParser::RPAR);
}

tree::TerminalNode* CodeParser::InputContext::RPAR(size_t i) {
  return getToken(CodeParser::RPAR, i);
}

tree::TerminalNode* CodeParser::InputContext::INT_TYPE() {
  return getToken(CodeParser::INT_TYPE, 0);
}


size_t CodeParser::InputContext::getRuleIndex() const {
  return CodeParser::RuleInput;
}


antlrcpp::Any CodeParser::InputContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<CodeVisitor*>(visitor))
    return parserVisitor->visitInput(this);
  else
    return visitor->visitChildren(this);
}

CodeParser::InputContext* CodeParser::input() {
  InputContext *_localctx = _tracker.createInstance<InputContext>(_ctx, getState());
  enterRule(_localctx, 14, CodeParser::RuleInput);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    setState(127);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case CodeParser::FLOAT_TYPE: {
        enterOuterAlt(_localctx, 1);
        setState(112);
        match(CodeParser::FLOAT_TYPE);
        setState(113);
        match(CodeParser::LPAR);
        setState(114);
        match(CodeParser::INPUT);
        setState(115);
        match(CodeParser::LPAR);
        setState(116);
        match(CodeParser::RPAR);
        setState(117);
        match(CodeParser::RPAR);
        break;
      }

      case CodeParser::INT_TYPE: {
        enterOuterAlt(_localctx, 2);
        setState(118);
        match(CodeParser::INT_TYPE);
        setState(119);
        match(CodeParser::LPAR);
        setState(120);
        match(CodeParser::INPUT);
        setState(121);
        match(CodeParser::LPAR);
        setState(122);
        match(CodeParser::RPAR);
        setState(123);
        match(CodeParser::RPAR);
        break;
      }

      case CodeParser::INPUT: {
        enterOuterAlt(_localctx, 3);
        setState(124);
        match(CodeParser::INPUT);
        setState(125);
        match(CodeParser::LPAR);
        setState(126);
        match(CodeParser::RPAR);
        break;
      }

    default:
      throw NoViableAltException(this);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- Var_assContext ------------------------------------------------------------------

CodeParser::Var_assContext::Var_assContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<tree::TerminalNode *> CodeParser::Var_assContext::IDENTIFICATOR() {
  return getTokens(CodeParser::IDENTIFICATOR);
}

tree::TerminalNode* CodeParser::Var_assContext::IDENTIFICATOR(size_t i) {
  return getToken(CodeParser::IDENTIFICATOR, i);
}

std::vector<CodeParser::InitContext *> CodeParser::Var_assContext::init() {
  return getRuleContexts<CodeParser::InitContext>();
}

CodeParser::InitContext* CodeParser::Var_assContext::init(size_t i) {
  return getRuleContext<CodeParser::InitContext>(i);
}

std::vector<tree::TerminalNode *> CodeParser::Var_assContext::COMMA() {
  return getTokens(CodeParser::COMMA);
}

tree::TerminalNode* CodeParser::Var_assContext::COMMA(size_t i) {
  return getToken(CodeParser::COMMA, i);
}


size_t CodeParser::Var_assContext::getRuleIndex() const {
  return CodeParser::RuleVar_ass;
}


antlrcpp::Any CodeParser::Var_assContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<CodeVisitor*>(visitor))
    return parserVisitor->visitVar_ass(this);
  else
    return visitor->visitChildren(this);
}

CodeParser::Var_assContext* CodeParser::var_ass() {
  Var_assContext *_localctx = _tracker.createInstance<Var_assContext>(_ctx, getState());
  enterRule(_localctx, 16, CodeParser::RuleVar_ass);
  size_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(129);
    match(CodeParser::IDENTIFICATOR);
    setState(134);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == CodeParser::COMMA) {
      setState(130);
      match(CodeParser::COMMA);
      setState(131);
      match(CodeParser::IDENTIFICATOR);
      setState(136);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
    setState(137);
    match(CodeParser::T__0);
    setState(138);
    init();
    setState(143);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == CodeParser::COMMA) {
      setState(139);
      match(CodeParser::COMMA);
      setState(140);
      init();
      setState(145);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- InitContext ------------------------------------------------------------------

CodeParser::InitContext::InitContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

CodeParser::OperationContext* CodeParser::InitContext::operation() {
  return getRuleContext<CodeParser::OperationContext>(0);
}

CodeParser::InputContext* CodeParser::InitContext::input() {
  return getRuleContext<CodeParser::InputContext>(0);
}


size_t CodeParser::InitContext::getRuleIndex() const {
  return CodeParser::RuleInit;
}


antlrcpp::Any CodeParser::InitContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<CodeVisitor*>(visitor))
    return parserVisitor->visitInit(this);
  else
    return visitor->visitChildren(this);
}

CodeParser::InitContext* CodeParser::init() {
  InitContext *_localctx = _tracker.createInstance<InitContext>(_ctx, getState());
  enterRule(_localctx, 18, CodeParser::RuleInit);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    setState(148);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case CodeParser::FALSE:
      case CodeParser::NOT:
      case CodeParser::TRUE:
      case CodeParser::LPAR:
      case CodeParser::IDENTIFICATOR:
      case CodeParser::INT:
      case CodeParser::NUM:
      case CodeParser::ADD_OP:
      case CodeParser::STRING: {
        enterOuterAlt(_localctx, 1);
        setState(146);
        operation();
        break;
      }

      case CodeParser::FLOAT_TYPE:
      case CodeParser::INPUT:
      case CodeParser::INT_TYPE: {
        enterOuterAlt(_localctx, 2);
        setState(147);
        input();
        break;
      }

    default:
      throw NoViableAltException(this);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- OperationContext ------------------------------------------------------------------

CodeParser::OperationContext::OperationContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

CodeParser::DisjContext* CodeParser::OperationContext::disj() {
  return getRuleContext<CodeParser::DisjContext>(0);
}


size_t CodeParser::OperationContext::getRuleIndex() const {
  return CodeParser::RuleOperation;
}


antlrcpp::Any CodeParser::OperationContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<CodeVisitor*>(visitor))
    return parserVisitor->visitOperation(this);
  else
    return visitor->visitChildren(this);
}

CodeParser::OperationContext* CodeParser::operation() {
  OperationContext *_localctx = _tracker.createInstance<OperationContext>(_ctx, getState());
  enterRule(_localctx, 20, CodeParser::RuleOperation);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(150);
    disj(0);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- If_statementContext ------------------------------------------------------------------

CodeParser::If_statementContext::If_statementContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* CodeParser::If_statementContext::IF() {
  return getToken(CodeParser::IF, 0);
}

tree::TerminalNode* CodeParser::If_statementContext::COLON() {
  return getToken(CodeParser::COLON, 0);
}

CodeParser::OperationContext* CodeParser::If_statementContext::operation() {
  return getRuleContext<CodeParser::OperationContext>(0);
}

CodeParser::After_colonContext* CodeParser::If_statementContext::after_colon() {
  return getRuleContext<CodeParser::After_colonContext>(0);
}


size_t CodeParser::If_statementContext::getRuleIndex() const {
  return CodeParser::RuleIf_statement;
}


antlrcpp::Any CodeParser::If_statementContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<CodeVisitor*>(visitor))
    return parserVisitor->visitIf_statement(this);
  else
    return visitor->visitChildren(this);
}

CodeParser::If_statementContext* CodeParser::if_statement() {
  If_statementContext *_localctx = _tracker.createInstance<If_statementContext>(_ctx, getState());
  enterRule(_localctx, 22, CodeParser::RuleIf_statement);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(152);
    match(CodeParser::IF);
    setState(153);
    dynamic_cast<If_statementContext *>(_localctx)->cond = operation();
    setState(154);
    match(CodeParser::COLON);
    setState(155);
    dynamic_cast<If_statementContext *>(_localctx)->block = after_colon();
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- Elif_statementContext ------------------------------------------------------------------

CodeParser::Elif_statementContext::Elif_statementContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* CodeParser::Elif_statementContext::ELIF() {
  return getToken(CodeParser::ELIF, 0);
}

tree::TerminalNode* CodeParser::Elif_statementContext::COLON() {
  return getToken(CodeParser::COLON, 0);
}

CodeParser::OperationContext* CodeParser::Elif_statementContext::operation() {
  return getRuleContext<CodeParser::OperationContext>(0);
}

CodeParser::After_colonContext* CodeParser::Elif_statementContext::after_colon() {
  return getRuleContext<CodeParser::After_colonContext>(0);
}


size_t CodeParser::Elif_statementContext::getRuleIndex() const {
  return CodeParser::RuleElif_statement;
}


antlrcpp::Any CodeParser::Elif_statementContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<CodeVisitor*>(visitor))
    return parserVisitor->visitElif_statement(this);
  else
    return visitor->visitChildren(this);
}

CodeParser::Elif_statementContext* CodeParser::elif_statement() {
  Elif_statementContext *_localctx = _tracker.createInstance<Elif_statementContext>(_ctx, getState());
  enterRule(_localctx, 24, CodeParser::RuleElif_statement);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(157);
    match(CodeParser::ELIF);
    setState(158);
    dynamic_cast<Elif_statementContext *>(_localctx)->cond = operation();
    setState(159);
    match(CodeParser::COLON);
    setState(160);
    dynamic_cast<Elif_statementContext *>(_localctx)->block = after_colon();
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- Else_statementContext ------------------------------------------------------------------

CodeParser::Else_statementContext::Else_statementContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* CodeParser::Else_statementContext::ELSE() {
  return getToken(CodeParser::ELSE, 0);
}

tree::TerminalNode* CodeParser::Else_statementContext::COLON() {
  return getToken(CodeParser::COLON, 0);
}

CodeParser::After_colonContext* CodeParser::Else_statementContext::after_colon() {
  return getRuleContext<CodeParser::After_colonContext>(0);
}


size_t CodeParser::Else_statementContext::getRuleIndex() const {
  return CodeParser::RuleElse_statement;
}


antlrcpp::Any CodeParser::Else_statementContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<CodeVisitor*>(visitor))
    return parserVisitor->visitElse_statement(this);
  else
    return visitor->visitChildren(this);
}

CodeParser::Else_statementContext* CodeParser::else_statement() {
  Else_statementContext *_localctx = _tracker.createInstance<Else_statementContext>(_ctx, getState());
  enterRule(_localctx, 26, CodeParser::RuleElse_statement);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(162);
    match(CodeParser::ELSE);
    setState(163);
    match(CodeParser::COLON);
    setState(164);
    dynamic_cast<Else_statementContext *>(_localctx)->block = after_colon();
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- While_statementContext ------------------------------------------------------------------

CodeParser::While_statementContext::While_statementContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* CodeParser::While_statementContext::WHILE() {
  return getToken(CodeParser::WHILE, 0);
}

tree::TerminalNode* CodeParser::While_statementContext::COLON() {
  return getToken(CodeParser::COLON, 0);
}

CodeParser::OperationContext* CodeParser::While_statementContext::operation() {
  return getRuleContext<CodeParser::OperationContext>(0);
}

CodeParser::After_colonContext* CodeParser::While_statementContext::after_colon() {
  return getRuleContext<CodeParser::After_colonContext>(0);
}


size_t CodeParser::While_statementContext::getRuleIndex() const {
  return CodeParser::RuleWhile_statement;
}


antlrcpp::Any CodeParser::While_statementContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<CodeVisitor*>(visitor))
    return parserVisitor->visitWhile_statement(this);
  else
    return visitor->visitChildren(this);
}

CodeParser::While_statementContext* CodeParser::while_statement() {
  While_statementContext *_localctx = _tracker.createInstance<While_statementContext>(_ctx, getState());
  enterRule(_localctx, 28, CodeParser::RuleWhile_statement);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(166);
    match(CodeParser::WHILE);
    setState(167);
    dynamic_cast<While_statementContext *>(_localctx)->cond = operation();
    setState(168);
    match(CodeParser::COLON);
    setState(169);
    dynamic_cast<While_statementContext *>(_localctx)->block = after_colon();
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- For_statementContext ------------------------------------------------------------------

CodeParser::For_statementContext::For_statementContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* CodeParser::For_statementContext::FOR() {
  return getToken(CodeParser::FOR, 0);
}

tree::TerminalNode* CodeParser::For_statementContext::IDENTIFICATOR() {
  return getToken(CodeParser::IDENTIFICATOR, 0);
}

tree::TerminalNode* CodeParser::For_statementContext::IN() {
  return getToken(CodeParser::IN, 0);
}

tree::TerminalNode* CodeParser::For_statementContext::RANGE() {
  return getToken(CodeParser::RANGE, 0);
}

tree::TerminalNode* CodeParser::For_statementContext::LPAR() {
  return getToken(CodeParser::LPAR, 0);
}

CodeParser::RangeContext* CodeParser::For_statementContext::range() {
  return getRuleContext<CodeParser::RangeContext>(0);
}

tree::TerminalNode* CodeParser::For_statementContext::RPAR() {
  return getToken(CodeParser::RPAR, 0);
}

tree::TerminalNode* CodeParser::For_statementContext::COLON() {
  return getToken(CodeParser::COLON, 0);
}

CodeParser::After_colonContext* CodeParser::For_statementContext::after_colon() {
  return getRuleContext<CodeParser::After_colonContext>(0);
}


size_t CodeParser::For_statementContext::getRuleIndex() const {
  return CodeParser::RuleFor_statement;
}


antlrcpp::Any CodeParser::For_statementContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<CodeVisitor*>(visitor))
    return parserVisitor->visitFor_statement(this);
  else
    return visitor->visitChildren(this);
}

CodeParser::For_statementContext* CodeParser::for_statement() {
  For_statementContext *_localctx = _tracker.createInstance<For_statementContext>(_ctx, getState());
  enterRule(_localctx, 30, CodeParser::RuleFor_statement);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(171);
    match(CodeParser::FOR);
    setState(172);
    match(CodeParser::IDENTIFICATOR);
    setState(173);
    match(CodeParser::IN);
    setState(174);
    match(CodeParser::RANGE);
    setState(175);
    match(CodeParser::LPAR);
    setState(176);
    range();
    setState(177);
    match(CodeParser::RPAR);
    setState(178);
    match(CodeParser::COLON);
    setState(179);
    dynamic_cast<For_statementContext *>(_localctx)->block = after_colon();
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- RangeContext ------------------------------------------------------------------

CodeParser::RangeContext::RangeContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<tree::TerminalNode *> CodeParser::RangeContext::INT() {
  return getTokens(CodeParser::INT);
}

tree::TerminalNode* CodeParser::RangeContext::INT(size_t i) {
  return getToken(CodeParser::INT, i);
}

std::vector<tree::TerminalNode *> CodeParser::RangeContext::COMMA() {
  return getTokens(CodeParser::COMMA);
}

tree::TerminalNode* CodeParser::RangeContext::COMMA(size_t i) {
  return getToken(CodeParser::COMMA, i);
}


size_t CodeParser::RangeContext::getRuleIndex() const {
  return CodeParser::RuleRange;
}


antlrcpp::Any CodeParser::RangeContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<CodeVisitor*>(visitor))
    return parserVisitor->visitRange(this);
  else
    return visitor->visitChildren(this);
}

CodeParser::RangeContext* CodeParser::range() {
  RangeContext *_localctx = _tracker.createInstance<RangeContext>(_ctx, getState());
  enterRule(_localctx, 32, CodeParser::RuleRange);
  size_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    setState(189);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 14, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(181);
      dynamic_cast<RangeContext *>(_localctx)->to = match(CodeParser::INT);
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(182);
      dynamic_cast<RangeContext *>(_localctx)->from = match(CodeParser::INT);
      setState(183);
      match(CodeParser::COMMA);

      setState(184);
      dynamic_cast<RangeContext *>(_localctx)->to = match(CodeParser::INT);
      setState(187);
      _errHandler->sync(this);

      _la = _input->LA(1);
      if (_la == CodeParser::COMMA) {
        setState(185);
        match(CodeParser::COMMA);
        setState(186);
        dynamic_cast<RangeContext *>(_localctx)->step = match(CodeParser::INT);
      }
      break;
    }

    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- After_colonContext ------------------------------------------------------------------

CodeParser::After_colonContext::After_colonContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

CodeParser::Many_one_line_exprsContext* CodeParser::After_colonContext::many_one_line_exprs() {
  return getRuleContext<CodeParser::Many_one_line_exprsContext>(0);
}

tree::TerminalNode* CodeParser::After_colonContext::NEW_LINE() {
  return getToken(CodeParser::NEW_LINE, 0);
}

CodeParser::ExpressionsContext* CodeParser::After_colonContext::expressions() {
  return getRuleContext<CodeParser::ExpressionsContext>(0);
}


size_t CodeParser::After_colonContext::getRuleIndex() const {
  return CodeParser::RuleAfter_colon;
}


antlrcpp::Any CodeParser::After_colonContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<CodeVisitor*>(visitor))
    return parserVisitor->visitAfter_colon(this);
  else
    return visitor->visitChildren(this);
}

CodeParser::After_colonContext* CodeParser::after_colon() {
  After_colonContext *_localctx = _tracker.createInstance<After_colonContext>(_ctx, getState());
  enterRule(_localctx, 34, CodeParser::RuleAfter_colon);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    setState(194);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case CodeParser::BREAK:
      case CodeParser::CONTINUE:
      case CodeParser::FALSE:
      case CodeParser::NOT:
      case CodeParser::PRINT:
      case CodeParser::TRUE:
      case CodeParser::LPAR:
      case CodeParser::IDENTIFICATOR:
      case CodeParser::INT:
      case CodeParser::NUM:
      case CodeParser::ADD_OP:
      case CodeParser::STRING: {
        enterOuterAlt(_localctx, 1);
        setState(191);
        many_one_line_exprs();
        break;
      }

      case CodeParser::NEW_LINE: {
        enterOuterAlt(_localctx, 2);
        setState(192);
        match(CodeParser::NEW_LINE);
        setState(193);
        expressions();
        break;
      }

    default:
      throw NoViableAltException(this);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- DisjContext ------------------------------------------------------------------

CodeParser::DisjContext::DisjContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

CodeParser::ConjContext* CodeParser::DisjContext::conj() {
  return getRuleContext<CodeParser::ConjContext>(0);
}

tree::TerminalNode* CodeParser::DisjContext::OR() {
  return getToken(CodeParser::OR, 0);
}

CodeParser::DisjContext* CodeParser::DisjContext::disj() {
  return getRuleContext<CodeParser::DisjContext>(0);
}


size_t CodeParser::DisjContext::getRuleIndex() const {
  return CodeParser::RuleDisj;
}


antlrcpp::Any CodeParser::DisjContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<CodeVisitor*>(visitor))
    return parserVisitor->visitDisj(this);
  else
    return visitor->visitChildren(this);
}


CodeParser::DisjContext* CodeParser::disj() {
   return disj(0);
}

CodeParser::DisjContext* CodeParser::disj(int precedence) {
  ParserRuleContext *parentContext = _ctx;
  size_t parentState = getState();
  CodeParser::DisjContext *_localctx = _tracker.createInstance<DisjContext>(_ctx, parentState);
  CodeParser::DisjContext *previousContext = _localctx;
  (void)previousContext; // Silence compiler, in case the context is not used by generated code.
  size_t startState = 36;
  enterRecursionRule(_localctx, 36, CodeParser::RuleDisj, precedence);

    

  auto onExit = finally([=] {
    unrollRecursionContexts(parentContext);
  });
  try {
    size_t alt;
    enterOuterAlt(_localctx, 1);
    setState(197);
    dynamic_cast<DisjContext *>(_localctx)->val = conj(0);
    _ctx->stop = _input->LT(-1);
    setState(204);
    _errHandler->sync(this);
    alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 16, _ctx);
    while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
      if (alt == 1) {
        if (!_parseListeners.empty())
          triggerExitRuleEvent();
        previousContext = _localctx;
        _localctx = _tracker.createInstance<DisjContext>(parentContext, parentState);
        _localctx->lhs = previousContext;
        pushNewRecursionContext(_localctx, startState, RuleDisj);
        setState(199);

        if (!(precpred(_ctx, 2))) throw FailedPredicateException(this, "precpred(_ctx, 2)");
        setState(200);
        match(CodeParser::OR);
        setState(201);
        dynamic_cast<DisjContext *>(_localctx)->rhs = conj(0); 
      }
      setState(206);
      _errHandler->sync(this);
      alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 16, _ctx);
    }
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }
  return _localctx;
}

//----------------- ConjContext ------------------------------------------------------------------

CodeParser::ConjContext::ConjContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

CodeParser::NegateContext* CodeParser::ConjContext::negate() {
  return getRuleContext<CodeParser::NegateContext>(0);
}

tree::TerminalNode* CodeParser::ConjContext::AND() {
  return getToken(CodeParser::AND, 0);
}

CodeParser::ConjContext* CodeParser::ConjContext::conj() {
  return getRuleContext<CodeParser::ConjContext>(0);
}


size_t CodeParser::ConjContext::getRuleIndex() const {
  return CodeParser::RuleConj;
}


antlrcpp::Any CodeParser::ConjContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<CodeVisitor*>(visitor))
    return parserVisitor->visitConj(this);
  else
    return visitor->visitChildren(this);
}


CodeParser::ConjContext* CodeParser::conj() {
   return conj(0);
}

CodeParser::ConjContext* CodeParser::conj(int precedence) {
  ParserRuleContext *parentContext = _ctx;
  size_t parentState = getState();
  CodeParser::ConjContext *_localctx = _tracker.createInstance<ConjContext>(_ctx, parentState);
  CodeParser::ConjContext *previousContext = _localctx;
  (void)previousContext; // Silence compiler, in case the context is not used by generated code.
  size_t startState = 38;
  enterRecursionRule(_localctx, 38, CodeParser::RuleConj, precedence);

    

  auto onExit = finally([=] {
    unrollRecursionContexts(parentContext);
  });
  try {
    size_t alt;
    enterOuterAlt(_localctx, 1);
    setState(208);
    dynamic_cast<ConjContext *>(_localctx)->val = negate();
    _ctx->stop = _input->LT(-1);
    setState(215);
    _errHandler->sync(this);
    alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 17, _ctx);
    while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
      if (alt == 1) {
        if (!_parseListeners.empty())
          triggerExitRuleEvent();
        previousContext = _localctx;
        _localctx = _tracker.createInstance<ConjContext>(parentContext, parentState);
        _localctx->lhs = previousContext;
        pushNewRecursionContext(_localctx, startState, RuleConj);
        setState(210);

        if (!(precpred(_ctx, 2))) throw FailedPredicateException(this, "precpred(_ctx, 2)");
        setState(211);
        match(CodeParser::AND);
        setState(212);
        dynamic_cast<ConjContext *>(_localctx)->rhs = negate(); 
      }
      setState(217);
      _errHandler->sync(this);
      alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 17, _ctx);
    }
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }
  return _localctx;
}

//----------------- NegateContext ------------------------------------------------------------------

CodeParser::NegateContext::NegateContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* CodeParser::NegateContext::NOT() {
  return getToken(CodeParser::NOT, 0);
}

CodeParser::NegateContext* CodeParser::NegateContext::negate() {
  return getRuleContext<CodeParser::NegateContext>(0);
}

CodeParser::ComparisonContext* CodeParser::NegateContext::comparison() {
  return getRuleContext<CodeParser::ComparisonContext>(0);
}


size_t CodeParser::NegateContext::getRuleIndex() const {
  return CodeParser::RuleNegate;
}


antlrcpp::Any CodeParser::NegateContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<CodeVisitor*>(visitor))
    return parserVisitor->visitNegate(this);
  else
    return visitor->visitChildren(this);
}

CodeParser::NegateContext* CodeParser::negate() {
  NegateContext *_localctx = _tracker.createInstance<NegateContext>(_ctx, getState());
  enterRule(_localctx, 40, CodeParser::RuleNegate);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    setState(221);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case CodeParser::NOT: {
        enterOuterAlt(_localctx, 1);
        setState(218);
        dynamic_cast<NegateContext *>(_localctx)->op = match(CodeParser::NOT);
        setState(219);
        dynamic_cast<NegateContext *>(_localctx)->arg = negate();
        break;
      }

      case CodeParser::FALSE:
      case CodeParser::TRUE:
      case CodeParser::LPAR:
      case CodeParser::IDENTIFICATOR:
      case CodeParser::INT:
      case CodeParser::NUM:
      case CodeParser::ADD_OP:
      case CodeParser::STRING: {
        enterOuterAlt(_localctx, 2);
        setState(220);
        dynamic_cast<NegateContext *>(_localctx)->val = comparison(0);
        break;
      }

    default:
      throw NoViableAltException(this);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- ComparisonContext ------------------------------------------------------------------

CodeParser::ComparisonContext::ComparisonContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

CodeParser::Sum_termContext* CodeParser::ComparisonContext::sum_term() {
  return getRuleContext<CodeParser::Sum_termContext>(0);
}

CodeParser::ComparisonContext* CodeParser::ComparisonContext::comparison() {
  return getRuleContext<CodeParser::ComparisonContext>(0);
}

tree::TerminalNode* CodeParser::ComparisonContext::COMPARE_OP() {
  return getToken(CodeParser::COMPARE_OP, 0);
}


size_t CodeParser::ComparisonContext::getRuleIndex() const {
  return CodeParser::RuleComparison;
}


antlrcpp::Any CodeParser::ComparisonContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<CodeVisitor*>(visitor))
    return parserVisitor->visitComparison(this);
  else
    return visitor->visitChildren(this);
}


CodeParser::ComparisonContext* CodeParser::comparison() {
   return comparison(0);
}

CodeParser::ComparisonContext* CodeParser::comparison(int precedence) {
  ParserRuleContext *parentContext = _ctx;
  size_t parentState = getState();
  CodeParser::ComparisonContext *_localctx = _tracker.createInstance<ComparisonContext>(_ctx, parentState);
  CodeParser::ComparisonContext *previousContext = _localctx;
  (void)previousContext; // Silence compiler, in case the context is not used by generated code.
  size_t startState = 42;
  enterRecursionRule(_localctx, 42, CodeParser::RuleComparison, precedence);

    

  auto onExit = finally([=] {
    unrollRecursionContexts(parentContext);
  });
  try {
    size_t alt;
    enterOuterAlt(_localctx, 1);
    setState(224);
    dynamic_cast<ComparisonContext *>(_localctx)->val = sum_term(0);
    _ctx->stop = _input->LT(-1);
    setState(231);
    _errHandler->sync(this);
    alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 19, _ctx);
    while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
      if (alt == 1) {
        if (!_parseListeners.empty())
          triggerExitRuleEvent();
        previousContext = _localctx;
        _localctx = _tracker.createInstance<ComparisonContext>(parentContext, parentState);
        _localctx->lhs = previousContext;
        pushNewRecursionContext(_localctx, startState, RuleComparison);
        setState(226);

        if (!(precpred(_ctx, 2))) throw FailedPredicateException(this, "precpred(_ctx, 2)");
        setState(227);
        dynamic_cast<ComparisonContext *>(_localctx)->op = match(CodeParser::COMPARE_OP);
        setState(228);
        dynamic_cast<ComparisonContext *>(_localctx)->rhs = sum_term(0); 
      }
      setState(233);
      _errHandler->sync(this);
      alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 19, _ctx);
    }
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }
  return _localctx;
}

//----------------- Sum_termContext ------------------------------------------------------------------

CodeParser::Sum_termContext::Sum_termContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

CodeParser::Mul_termContext* CodeParser::Sum_termContext::mul_term() {
  return getRuleContext<CodeParser::Mul_termContext>(0);
}

CodeParser::Sum_termContext* CodeParser::Sum_termContext::sum_term() {
  return getRuleContext<CodeParser::Sum_termContext>(0);
}

tree::TerminalNode* CodeParser::Sum_termContext::ADD_OP() {
  return getToken(CodeParser::ADD_OP, 0);
}


size_t CodeParser::Sum_termContext::getRuleIndex() const {
  return CodeParser::RuleSum_term;
}


antlrcpp::Any CodeParser::Sum_termContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<CodeVisitor*>(visitor))
    return parserVisitor->visitSum_term(this);
  else
    return visitor->visitChildren(this);
}


CodeParser::Sum_termContext* CodeParser::sum_term() {
   return sum_term(0);
}

CodeParser::Sum_termContext* CodeParser::sum_term(int precedence) {
  ParserRuleContext *parentContext = _ctx;
  size_t parentState = getState();
  CodeParser::Sum_termContext *_localctx = _tracker.createInstance<Sum_termContext>(_ctx, parentState);
  CodeParser::Sum_termContext *previousContext = _localctx;
  (void)previousContext; // Silence compiler, in case the context is not used by generated code.
  size_t startState = 44;
  enterRecursionRule(_localctx, 44, CodeParser::RuleSum_term, precedence);

    

  auto onExit = finally([=] {
    unrollRecursionContexts(parentContext);
  });
  try {
    size_t alt;
    enterOuterAlt(_localctx, 1);
    setState(235);
    dynamic_cast<Sum_termContext *>(_localctx)->val = mul_term(0);
    _ctx->stop = _input->LT(-1);
    setState(242);
    _errHandler->sync(this);
    alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 20, _ctx);
    while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
      if (alt == 1) {
        if (!_parseListeners.empty())
          triggerExitRuleEvent();
        previousContext = _localctx;
        _localctx = _tracker.createInstance<Sum_termContext>(parentContext, parentState);
        _localctx->lhs = previousContext;
        pushNewRecursionContext(_localctx, startState, RuleSum_term);
        setState(237);

        if (!(precpred(_ctx, 2))) throw FailedPredicateException(this, "precpred(_ctx, 2)");
        setState(238);
        dynamic_cast<Sum_termContext *>(_localctx)->op = match(CodeParser::ADD_OP);
        setState(239);
        dynamic_cast<Sum_termContext *>(_localctx)->rhs = mul_term(0); 
      }
      setState(244);
      _errHandler->sync(this);
      alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 20, _ctx);
    }
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }
  return _localctx;
}

//----------------- Mul_termContext ------------------------------------------------------------------

CodeParser::Mul_termContext::Mul_termContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

CodeParser::TermContext* CodeParser::Mul_termContext::term() {
  return getRuleContext<CodeParser::TermContext>(0);
}

CodeParser::Mul_termContext* CodeParser::Mul_termContext::mul_term() {
  return getRuleContext<CodeParser::Mul_termContext>(0);
}

tree::TerminalNode* CodeParser::Mul_termContext::MUL_OP() {
  return getToken(CodeParser::MUL_OP, 0);
}


size_t CodeParser::Mul_termContext::getRuleIndex() const {
  return CodeParser::RuleMul_term;
}


antlrcpp::Any CodeParser::Mul_termContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<CodeVisitor*>(visitor))
    return parserVisitor->visitMul_term(this);
  else
    return visitor->visitChildren(this);
}


CodeParser::Mul_termContext* CodeParser::mul_term() {
   return mul_term(0);
}

CodeParser::Mul_termContext* CodeParser::mul_term(int precedence) {
  ParserRuleContext *parentContext = _ctx;
  size_t parentState = getState();
  CodeParser::Mul_termContext *_localctx = _tracker.createInstance<Mul_termContext>(_ctx, parentState);
  CodeParser::Mul_termContext *previousContext = _localctx;
  (void)previousContext; // Silence compiler, in case the context is not used by generated code.
  size_t startState = 46;
  enterRecursionRule(_localctx, 46, CodeParser::RuleMul_term, precedence);

    

  auto onExit = finally([=] {
    unrollRecursionContexts(parentContext);
  });
  try {
    size_t alt;
    enterOuterAlt(_localctx, 1);
    setState(246);
    dynamic_cast<Mul_termContext *>(_localctx)->val = term();
    _ctx->stop = _input->LT(-1);
    setState(253);
    _errHandler->sync(this);
    alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 21, _ctx);
    while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
      if (alt == 1) {
        if (!_parseListeners.empty())
          triggerExitRuleEvent();
        previousContext = _localctx;
        _localctx = _tracker.createInstance<Mul_termContext>(parentContext, parentState);
        _localctx->lhs = previousContext;
        pushNewRecursionContext(_localctx, startState, RuleMul_term);
        setState(248);

        if (!(precpred(_ctx, 2))) throw FailedPredicateException(this, "precpred(_ctx, 2)");
        setState(249);
        dynamic_cast<Mul_termContext *>(_localctx)->op = match(CodeParser::MUL_OP);
        setState(250);
        dynamic_cast<Mul_termContext *>(_localctx)->rhs = term(); 
      }
      setState(255);
      _errHandler->sync(this);
      alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 21, _ctx);
    }
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }
  return _localctx;
}

//----------------- TermContext ------------------------------------------------------------------

CodeParser::TermContext::TermContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* CodeParser::TermContext::ADD_OP() {
  return getToken(CodeParser::ADD_OP, 0);
}

CodeParser::TermContext* CodeParser::TermContext::term() {
  return getRuleContext<CodeParser::TermContext>(0);
}

CodeParser::AtomContext* CodeParser::TermContext::atom() {
  return getRuleContext<CodeParser::AtomContext>(0);
}


size_t CodeParser::TermContext::getRuleIndex() const {
  return CodeParser::RuleTerm;
}


antlrcpp::Any CodeParser::TermContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<CodeVisitor*>(visitor))
    return parserVisitor->visitTerm(this);
  else
    return visitor->visitChildren(this);
}

CodeParser::TermContext* CodeParser::term() {
  TermContext *_localctx = _tracker.createInstance<TermContext>(_ctx, getState());
  enterRule(_localctx, 48, CodeParser::RuleTerm);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    setState(259);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case CodeParser::ADD_OP: {
        enterOuterAlt(_localctx, 1);
        setState(256);
        dynamic_cast<TermContext *>(_localctx)->op = match(CodeParser::ADD_OP);
        setState(257);
        dynamic_cast<TermContext *>(_localctx)->arg = term();
        break;
      }

      case CodeParser::FALSE:
      case CodeParser::TRUE:
      case CodeParser::LPAR:
      case CodeParser::IDENTIFICATOR:
      case CodeParser::INT:
      case CodeParser::NUM:
      case CodeParser::STRING: {
        enterOuterAlt(_localctx, 2);
        setState(258);
        dynamic_cast<TermContext *>(_localctx)->val = atom();
        break;
      }

    default:
      throw NoViableAltException(this);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- AtomContext ------------------------------------------------------------------

CodeParser::AtomContext::AtomContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

CodeParser::Bool_litContext* CodeParser::AtomContext::bool_lit() {
  return getRuleContext<CodeParser::Bool_litContext>(0);
}

tree::TerminalNode* CodeParser::AtomContext::IDENTIFICATOR() {
  return getToken(CodeParser::IDENTIFICATOR, 0);
}

tree::TerminalNode* CodeParser::AtomContext::STRING() {
  return getToken(CodeParser::STRING, 0);
}

tree::TerminalNode* CodeParser::AtomContext::NUM() {
  return getToken(CodeParser::NUM, 0);
}

tree::TerminalNode* CodeParser::AtomContext::INT() {
  return getToken(CodeParser::INT, 0);
}

tree::TerminalNode* CodeParser::AtomContext::LPAR() {
  return getToken(CodeParser::LPAR, 0);
}

CodeParser::OperationContext* CodeParser::AtomContext::operation() {
  return getRuleContext<CodeParser::OperationContext>(0);
}

tree::TerminalNode* CodeParser::AtomContext::RPAR() {
  return getToken(CodeParser::RPAR, 0);
}


size_t CodeParser::AtomContext::getRuleIndex() const {
  return CodeParser::RuleAtom;
}


antlrcpp::Any CodeParser::AtomContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<CodeVisitor*>(visitor))
    return parserVisitor->visitAtom(this);
  else
    return visitor->visitChildren(this);
}

CodeParser::AtomContext* CodeParser::atom() {
  AtomContext *_localctx = _tracker.createInstance<AtomContext>(_ctx, getState());
  enterRule(_localctx, 50, CodeParser::RuleAtom);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    setState(270);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case CodeParser::FALSE:
      case CodeParser::TRUE: {
        enterOuterAlt(_localctx, 1);
        setState(261);
        bool_lit();
        break;
      }

      case CodeParser::IDENTIFICATOR: {
        enterOuterAlt(_localctx, 2);
        setState(262);
        match(CodeParser::IDENTIFICATOR);
        break;
      }

      case CodeParser::STRING: {
        enterOuterAlt(_localctx, 3);
        setState(263);
        match(CodeParser::STRING);
        break;
      }

      case CodeParser::NUM: {
        enterOuterAlt(_localctx, 4);
        setState(264);
        match(CodeParser::NUM);
        break;
      }

      case CodeParser::INT: {
        enterOuterAlt(_localctx, 5);
        setState(265);
        match(CodeParser::INT);
        break;
      }

      case CodeParser::LPAR: {
        enterOuterAlt(_localctx, 6);
        setState(266);
        match(CodeParser::LPAR);
        setState(267);
        operation();
        setState(268);
        match(CodeParser::RPAR);
        break;
      }

    default:
      throw NoViableAltException(this);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- Bool_litContext ------------------------------------------------------------------

CodeParser::Bool_litContext::Bool_litContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* CodeParser::Bool_litContext::TRUE() {
  return getToken(CodeParser::TRUE, 0);
}

tree::TerminalNode* CodeParser::Bool_litContext::FALSE() {
  return getToken(CodeParser::FALSE, 0);
}


size_t CodeParser::Bool_litContext::getRuleIndex() const {
  return CodeParser::RuleBool_lit;
}


antlrcpp::Any CodeParser::Bool_litContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<CodeVisitor*>(visitor))
    return parserVisitor->visitBool_lit(this);
  else
    return visitor->visitChildren(this);
}

CodeParser::Bool_litContext* CodeParser::bool_lit() {
  Bool_litContext *_localctx = _tracker.createInstance<Bool_litContext>(_ctx, getState());
  enterRule(_localctx, 52, CodeParser::RuleBool_lit);
  size_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(272);
    _la = _input->LA(1);
    if (!(_la == CodeParser::FALSE

    || _la == CodeParser::TRUE)) {
    _errHandler->recoverInline(this);
    }
    else {
      _errHandler->reportMatch(this);
      consume();
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

bool CodeParser::sempred(RuleContext *context, size_t ruleIndex, size_t predicateIndex) {
  switch (ruleIndex) {
    case 18: return disjSempred(dynamic_cast<DisjContext *>(context), predicateIndex);
    case 19: return conjSempred(dynamic_cast<ConjContext *>(context), predicateIndex);
    case 21: return comparisonSempred(dynamic_cast<ComparisonContext *>(context), predicateIndex);
    case 22: return sum_termSempred(dynamic_cast<Sum_termContext *>(context), predicateIndex);
    case 23: return mul_termSempred(dynamic_cast<Mul_termContext *>(context), predicateIndex);

  default:
    break;
  }
  return true;
}

bool CodeParser::disjSempred(DisjContext *_localctx, size_t predicateIndex) {
  switch (predicateIndex) {
    case 0: return precpred(_ctx, 2);

  default:
    break;
  }
  return true;
}

bool CodeParser::conjSempred(ConjContext *_localctx, size_t predicateIndex) {
  switch (predicateIndex) {
    case 1: return precpred(_ctx, 2);

  default:
    break;
  }
  return true;
}

bool CodeParser::comparisonSempred(ComparisonContext *_localctx, size_t predicateIndex) {
  switch (predicateIndex) {
    case 2: return precpred(_ctx, 2);

  default:
    break;
  }
  return true;
}

bool CodeParser::sum_termSempred(Sum_termContext *_localctx, size_t predicateIndex) {
  switch (predicateIndex) {
    case 3: return precpred(_ctx, 2);

  default:
    break;
  }
  return true;
}

bool CodeParser::mul_termSempred(Mul_termContext *_localctx, size_t predicateIndex) {
  switch (predicateIndex) {
    case 4: return precpred(_ctx, 2);

  default:
    break;
  }
  return true;
}

// Static vars and initialization.
std::vector<dfa::DFA> CodeParser::_decisionToDFA;
atn::PredictionContextCache CodeParser::_sharedContextCache;

// We own the ATN which in turn owns the ATN states.
atn::ATN CodeParser::_atn;
std::vector<uint16_t> CodeParser::_serializedATN;

std::vector<std::string> CodeParser::_ruleNames = {
  "file", "expressions", "expression", "multi_line_expr", "many_one_line_exprs", 
  "one_line_expr", "print", "input", "var_ass", "init", "operation", "if_statement", 
  "elif_statement", "else_statement", "while_statement", "for_statement", 
  "range", "after_colon", "disj", "conj", "negate", "comparison", "sum_term", 
  "mul_term", "term", "atom", "bool_lit"
};

std::vector<std::string> CodeParser::_literalNames = {
  "", "'='", "'and'", "'break'", "'bool'", "','", "'continue'", "'def'", 
  "':'", "'elif'", "'else'", "'False'", "'float'", "'for'", "'if'", "'input'", 
  "'int'", "'in'", "'not'", "'or'", "'print'", "'range'", "';'", "'string'", 
  "'True'", "'while'", "'('", "')'", "", "", "", "", "", "", "", "", "", 
  "' '"
};

std::vector<std::string> CodeParser::_symbolicNames = {
  "", "", "AND", "BREAK", "BOOL_TYPE", "COMMA", "CONTINUE", "DEF", "COLON", 
  "ELIF", "ELSE", "FALSE", "FLOAT_TYPE", "FOR", "IF", "INPUT", "INT_TYPE", 
  "IN", "NOT", "OR", "PRINT", "RANGE", "SEMICOL", "STRING_TYPE", "TRUE", 
  "WHILE", "LPAR", "RPAR", "IDENTIFICATOR", "COMPARE_OP", "INT", "NUM", 
  "ADD_OP", "MUL_OP", "STRING", "NEW_LINE", "TAB", "WHITESPACE"
};

dfa::Vocabulary CodeParser::_vocabulary(_literalNames, _symbolicNames);

std::vector<std::string> CodeParser::_tokenNames;

CodeParser::Initializer::Initializer() {
	for (size_t i = 0; i < _symbolicNames.size(); ++i) {
		std::string name = _vocabulary.getLiteralName(i);
		if (name.empty()) {
			name = _vocabulary.getSymbolicName(i);
		}

		if (name.empty()) {
			_tokenNames.push_back("<INVALID>");
		} else {
      _tokenNames.push_back(name);
    }
	}

  _serializedATN = {
    0x3, 0x608b, 0xa72a, 0x8133, 0xb9ed, 0x417c, 0x3be7, 0x7786, 0x5964, 
    0x3, 0x27, 0x115, 0x4, 0x2, 0x9, 0x2, 0x4, 0x3, 0x9, 0x3, 0x4, 0x4, 
    0x9, 0x4, 0x4, 0x5, 0x9, 0x5, 0x4, 0x6, 0x9, 0x6, 0x4, 0x7, 0x9, 0x7, 
    0x4, 0x8, 0x9, 0x8, 0x4, 0x9, 0x9, 0x9, 0x4, 0xa, 0x9, 0xa, 0x4, 0xb, 
    0x9, 0xb, 0x4, 0xc, 0x9, 0xc, 0x4, 0xd, 0x9, 0xd, 0x4, 0xe, 0x9, 0xe, 
    0x4, 0xf, 0x9, 0xf, 0x4, 0x10, 0x9, 0x10, 0x4, 0x11, 0x9, 0x11, 0x4, 
    0x12, 0x9, 0x12, 0x4, 0x13, 0x9, 0x13, 0x4, 0x14, 0x9, 0x14, 0x4, 0x15, 
    0x9, 0x15, 0x4, 0x16, 0x9, 0x16, 0x4, 0x17, 0x9, 0x17, 0x4, 0x18, 0x9, 
    0x18, 0x4, 0x19, 0x9, 0x19, 0x4, 0x1a, 0x9, 0x1a, 0x4, 0x1b, 0x9, 0x1b, 
    0x4, 0x1c, 0x9, 0x1c, 0x3, 0x2, 0x3, 0x2, 0x3, 0x2, 0x3, 0x3, 0x6, 0x3, 
    0x3d, 0xa, 0x3, 0xd, 0x3, 0xe, 0x3, 0x3e, 0x3, 0x4, 0x7, 0x4, 0x42, 
    0xa, 0x4, 0xc, 0x4, 0xe, 0x4, 0x45, 0xb, 0x4, 0x3, 0x4, 0x3, 0x4, 0x5, 
    0x4, 0x49, 0xa, 0x4, 0x3, 0x5, 0x3, 0x5, 0x3, 0x5, 0x3, 0x5, 0x3, 0x5, 
    0x5, 0x5, 0x50, 0xa, 0x5, 0x3, 0x6, 0x3, 0x6, 0x3, 0x6, 0x7, 0x6, 0x55, 
    0xa, 0x6, 0xc, 0x6, 0xe, 0x6, 0x58, 0xb, 0x6, 0x3, 0x6, 0x5, 0x6, 0x5b, 
    0xa, 0x6, 0x3, 0x6, 0x5, 0x6, 0x5e, 0xa, 0x6, 0x3, 0x7, 0x3, 0x7, 0x3, 
    0x7, 0x3, 0x7, 0x3, 0x7, 0x5, 0x7, 0x65, 0xa, 0x7, 0x3, 0x8, 0x3, 0x8, 
    0x3, 0x8, 0x3, 0x8, 0x3, 0x8, 0x7, 0x8, 0x6c, 0xa, 0x8, 0xc, 0x8, 0xe, 
    0x8, 0x6f, 0xb, 0x8, 0x3, 0x8, 0x3, 0x8, 0x3, 0x9, 0x3, 0x9, 0x3, 0x9, 
    0x3, 0x9, 0x3, 0x9, 0x3, 0x9, 0x3, 0x9, 0x3, 0x9, 0x3, 0x9, 0x3, 0x9, 
    0x3, 0x9, 0x3, 0x9, 0x3, 0x9, 0x3, 0x9, 0x3, 0x9, 0x5, 0x9, 0x82, 0xa, 
    0x9, 0x3, 0xa, 0x3, 0xa, 0x3, 0xa, 0x7, 0xa, 0x87, 0xa, 0xa, 0xc, 0xa, 
    0xe, 0xa, 0x8a, 0xb, 0xa, 0x3, 0xa, 0x3, 0xa, 0x3, 0xa, 0x3, 0xa, 0x7, 
    0xa, 0x90, 0xa, 0xa, 0xc, 0xa, 0xe, 0xa, 0x93, 0xb, 0xa, 0x3, 0xb, 0x3, 
    0xb, 0x5, 0xb, 0x97, 0xa, 0xb, 0x3, 0xc, 0x3, 0xc, 0x3, 0xd, 0x3, 0xd, 
    0x3, 0xd, 0x3, 0xd, 0x3, 0xd, 0x3, 0xe, 0x3, 0xe, 0x3, 0xe, 0x3, 0xe, 
    0x3, 0xe, 0x3, 0xf, 0x3, 0xf, 0x3, 0xf, 0x3, 0xf, 0x3, 0x10, 0x3, 0x10, 
    0x3, 0x10, 0x3, 0x10, 0x3, 0x10, 0x3, 0x11, 0x3, 0x11, 0x3, 0x11, 0x3, 
    0x11, 0x3, 0x11, 0x3, 0x11, 0x3, 0x11, 0x3, 0x11, 0x3, 0x11, 0x3, 0x11, 
    0x3, 0x12, 0x3, 0x12, 0x3, 0x12, 0x3, 0x12, 0x3, 0x12, 0x3, 0x12, 0x5, 
    0x12, 0xbe, 0xa, 0x12, 0x5, 0x12, 0xc0, 0xa, 0x12, 0x3, 0x13, 0x3, 0x13, 
    0x3, 0x13, 0x5, 0x13, 0xc5, 0xa, 0x13, 0x3, 0x14, 0x3, 0x14, 0x3, 0x14, 
    0x3, 0x14, 0x3, 0x14, 0x3, 0x14, 0x7, 0x14, 0xcd, 0xa, 0x14, 0xc, 0x14, 
    0xe, 0x14, 0xd0, 0xb, 0x14, 0x3, 0x15, 0x3, 0x15, 0x3, 0x15, 0x3, 0x15, 
    0x3, 0x15, 0x3, 0x15, 0x7, 0x15, 0xd8, 0xa, 0x15, 0xc, 0x15, 0xe, 0x15, 
    0xdb, 0xb, 0x15, 0x3, 0x16, 0x3, 0x16, 0x3, 0x16, 0x5, 0x16, 0xe0, 0xa, 
    0x16, 0x3, 0x17, 0x3, 0x17, 0x3, 0x17, 0x3, 0x17, 0x3, 0x17, 0x3, 0x17, 
    0x7, 0x17, 0xe8, 0xa, 0x17, 0xc, 0x17, 0xe, 0x17, 0xeb, 0xb, 0x17, 0x3, 
    0x18, 0x3, 0x18, 0x3, 0x18, 0x3, 0x18, 0x3, 0x18, 0x3, 0x18, 0x7, 0x18, 
    0xf3, 0xa, 0x18, 0xc, 0x18, 0xe, 0x18, 0xf6, 0xb, 0x18, 0x3, 0x19, 0x3, 
    0x19, 0x3, 0x19, 0x3, 0x19, 0x3, 0x19, 0x3, 0x19, 0x7, 0x19, 0xfe, 0xa, 
    0x19, 0xc, 0x19, 0xe, 0x19, 0x101, 0xb, 0x19, 0x3, 0x1a, 0x3, 0x1a, 
    0x3, 0x1a, 0x5, 0x1a, 0x106, 0xa, 0x1a, 0x3, 0x1b, 0x3, 0x1b, 0x3, 0x1b, 
    0x3, 0x1b, 0x3, 0x1b, 0x3, 0x1b, 0x3, 0x1b, 0x3, 0x1b, 0x3, 0x1b, 0x5, 
    0x1b, 0x111, 0xa, 0x1b, 0x3, 0x1c, 0x3, 0x1c, 0x3, 0x1c, 0x2, 0x7, 0x26, 
    0x28, 0x2c, 0x2e, 0x30, 0x1d, 0x2, 0x4, 0x6, 0x8, 0xa, 0xc, 0xe, 0x10, 
    0x12, 0x14, 0x16, 0x18, 0x1a, 0x1c, 0x1e, 0x20, 0x22, 0x24, 0x26, 0x28, 
    0x2a, 0x2c, 0x2e, 0x30, 0x32, 0x34, 0x36, 0x2, 0x3, 0x4, 0x2, 0xd, 0xd, 
    0x1a, 0x1a, 0x2, 0x11c, 0x2, 0x38, 0x3, 0x2, 0x2, 0x2, 0x4, 0x3c, 0x3, 
    0x2, 0x2, 0x2, 0x6, 0x43, 0x3, 0x2, 0x2, 0x2, 0x8, 0x4f, 0x3, 0x2, 0x2, 
    0x2, 0xa, 0x51, 0x3, 0x2, 0x2, 0x2, 0xc, 0x64, 0x3, 0x2, 0x2, 0x2, 0xe, 
    0x66, 0x3, 0x2, 0x2, 0x2, 0x10, 0x81, 0x3, 0x2, 0x2, 0x2, 0x12, 0x83, 
    0x3, 0x2, 0x2, 0x2, 0x14, 0x96, 0x3, 0x2, 0x2, 0x2, 0x16, 0x98, 0x3, 
    0x2, 0x2, 0x2, 0x18, 0x9a, 0x3, 0x2, 0x2, 0x2, 0x1a, 0x9f, 0x3, 0x2, 
    0x2, 0x2, 0x1c, 0xa4, 0x3, 0x2, 0x2, 0x2, 0x1e, 0xa8, 0x3, 0x2, 0x2, 
    0x2, 0x20, 0xad, 0x3, 0x2, 0x2, 0x2, 0x22, 0xbf, 0x3, 0x2, 0x2, 0x2, 
    0x24, 0xc4, 0x3, 0x2, 0x2, 0x2, 0x26, 0xc6, 0x3, 0x2, 0x2, 0x2, 0x28, 
    0xd1, 0x3, 0x2, 0x2, 0x2, 0x2a, 0xdf, 0x3, 0x2, 0x2, 0x2, 0x2c, 0xe1, 
    0x3, 0x2, 0x2, 0x2, 0x2e, 0xec, 0x3, 0x2, 0x2, 0x2, 0x30, 0xf7, 0x3, 
    0x2, 0x2, 0x2, 0x32, 0x105, 0x3, 0x2, 0x2, 0x2, 0x34, 0x110, 0x3, 0x2, 
    0x2, 0x2, 0x36, 0x112, 0x3, 0x2, 0x2, 0x2, 0x38, 0x39, 0x5, 0x4, 0x3, 
    0x2, 0x39, 0x3a, 0x7, 0x2, 0x2, 0x3, 0x3a, 0x3, 0x3, 0x2, 0x2, 0x2, 
    0x3b, 0x3d, 0x5, 0x6, 0x4, 0x2, 0x3c, 0x3b, 0x3, 0x2, 0x2, 0x2, 0x3d, 
    0x3e, 0x3, 0x2, 0x2, 0x2, 0x3e, 0x3c, 0x3, 0x2, 0x2, 0x2, 0x3e, 0x3f, 
    0x3, 0x2, 0x2, 0x2, 0x3f, 0x5, 0x3, 0x2, 0x2, 0x2, 0x40, 0x42, 0x7, 
    0x26, 0x2, 0x2, 0x41, 0x40, 0x3, 0x2, 0x2, 0x2, 0x42, 0x45, 0x3, 0x2, 
    0x2, 0x2, 0x43, 0x41, 0x3, 0x2, 0x2, 0x2, 0x43, 0x44, 0x3, 0x2, 0x2, 
    0x2, 0x44, 0x48, 0x3, 0x2, 0x2, 0x2, 0x45, 0x43, 0x3, 0x2, 0x2, 0x2, 
    0x46, 0x49, 0x5, 0xa, 0x6, 0x2, 0x47, 0x49, 0x5, 0x8, 0x5, 0x2, 0x48, 
    0x46, 0x3, 0x2, 0x2, 0x2, 0x48, 0x47, 0x3, 0x2, 0x2, 0x2, 0x49, 0x7, 
    0x3, 0x2, 0x2, 0x2, 0x4a, 0x50, 0x5, 0x18, 0xd, 0x2, 0x4b, 0x50, 0x5, 
    0x1a, 0xe, 0x2, 0x4c, 0x50, 0x5, 0x1c, 0xf, 0x2, 0x4d, 0x50, 0x5, 0x1e, 
    0x10, 0x2, 0x4e, 0x50, 0x5, 0x20, 0x11, 0x2, 0x4f, 0x4a, 0x3, 0x2, 0x2, 
    0x2, 0x4f, 0x4b, 0x3, 0x2, 0x2, 0x2, 0x4f, 0x4c, 0x3, 0x2, 0x2, 0x2, 
    0x4f, 0x4d, 0x3, 0x2, 0x2, 0x2, 0x4f, 0x4e, 0x3, 0x2, 0x2, 0x2, 0x50, 
    0x9, 0x3, 0x2, 0x2, 0x2, 0x51, 0x56, 0x5, 0xc, 0x7, 0x2, 0x52, 0x53, 
    0x7, 0x18, 0x2, 0x2, 0x53, 0x55, 0x5, 0xc, 0x7, 0x2, 0x54, 0x52, 0x3, 
    0x2, 0x2, 0x2, 0x55, 0x58, 0x3, 0x2, 0x2, 0x2, 0x56, 0x54, 0x3, 0x2, 
    0x2, 0x2, 0x56, 0x57, 0x3, 0x2, 0x2, 0x2, 0x57, 0x5a, 0x3, 0x2, 0x2, 
    0x2, 0x58, 0x56, 0x3, 0x2, 0x2, 0x2, 0x59, 0x5b, 0x7, 0x18, 0x2, 0x2, 
    0x5a, 0x59, 0x3, 0x2, 0x2, 0x2, 0x5a, 0x5b, 0x3, 0x2, 0x2, 0x2, 0x5b, 
    0x5d, 0x3, 0x2, 0x2, 0x2, 0x5c, 0x5e, 0x7, 0x25, 0x2, 0x2, 0x5d, 0x5c, 
    0x3, 0x2, 0x2, 0x2, 0x5d, 0x5e, 0x3, 0x2, 0x2, 0x2, 0x5e, 0xb, 0x3, 
    0x2, 0x2, 0x2, 0x5f, 0x65, 0x5, 0x12, 0xa, 0x2, 0x60, 0x65, 0x5, 0x16, 
    0xc, 0x2, 0x61, 0x65, 0x7, 0x5, 0x2, 0x2, 0x62, 0x65, 0x7, 0x8, 0x2, 
    0x2, 0x63, 0x65, 0x5, 0xe, 0x8, 0x2, 0x64, 0x5f, 0x3, 0x2, 0x2, 0x2, 
    0x64, 0x60, 0x3, 0x2, 0x2, 0x2, 0x64, 0x61, 0x3, 0x2, 0x2, 0x2, 0x64, 
    0x62, 0x3, 0x2, 0x2, 0x2, 0x64, 0x63, 0x3, 0x2, 0x2, 0x2, 0x65, 0xd, 
    0x3, 0x2, 0x2, 0x2, 0x66, 0x67, 0x7, 0x16, 0x2, 0x2, 0x67, 0x68, 0x7, 
    0x1c, 0x2, 0x2, 0x68, 0x6d, 0x5, 0x16, 0xc, 0x2, 0x69, 0x6a, 0x7, 0x7, 
    0x2, 0x2, 0x6a, 0x6c, 0x5, 0x16, 0xc, 0x2, 0x6b, 0x69, 0x3, 0x2, 0x2, 
    0x2, 0x6c, 0x6f, 0x3, 0x2, 0x2, 0x2, 0x6d, 0x6b, 0x3, 0x2, 0x2, 0x2, 
    0x6d, 0x6e, 0x3, 0x2, 0x2, 0x2, 0x6e, 0x70, 0x3, 0x2, 0x2, 0x2, 0x6f, 
    0x6d, 0x3, 0x2, 0x2, 0x2, 0x70, 0x71, 0x7, 0x1d, 0x2, 0x2, 0x71, 0xf, 
    0x3, 0x2, 0x2, 0x2, 0x72, 0x73, 0x7, 0xe, 0x2, 0x2, 0x73, 0x74, 0x7, 
    0x1c, 0x2, 0x2, 0x74, 0x75, 0x7, 0x11, 0x2, 0x2, 0x75, 0x76, 0x7, 0x1c, 
    0x2, 0x2, 0x76, 0x77, 0x7, 0x1d, 0x2, 0x2, 0x77, 0x82, 0x7, 0x1d, 0x2, 
    0x2, 0x78, 0x79, 0x7, 0x12, 0x2, 0x2, 0x79, 0x7a, 0x7, 0x1c, 0x2, 0x2, 
    0x7a, 0x7b, 0x7, 0x11, 0x2, 0x2, 0x7b, 0x7c, 0x7, 0x1c, 0x2, 0x2, 0x7c, 
    0x7d, 0x7, 0x1d, 0x2, 0x2, 0x7d, 0x82, 0x7, 0x1d, 0x2, 0x2, 0x7e, 0x7f, 
    0x7, 0x11, 0x2, 0x2, 0x7f, 0x80, 0x7, 0x1c, 0x2, 0x2, 0x80, 0x82, 0x7, 
    0x1d, 0x2, 0x2, 0x81, 0x72, 0x3, 0x2, 0x2, 0x2, 0x81, 0x78, 0x3, 0x2, 
    0x2, 0x2, 0x81, 0x7e, 0x3, 0x2, 0x2, 0x2, 0x82, 0x11, 0x3, 0x2, 0x2, 
    0x2, 0x83, 0x88, 0x7, 0x1e, 0x2, 0x2, 0x84, 0x85, 0x7, 0x7, 0x2, 0x2, 
    0x85, 0x87, 0x7, 0x1e, 0x2, 0x2, 0x86, 0x84, 0x3, 0x2, 0x2, 0x2, 0x87, 
    0x8a, 0x3, 0x2, 0x2, 0x2, 0x88, 0x86, 0x3, 0x2, 0x2, 0x2, 0x88, 0x89, 
    0x3, 0x2, 0x2, 0x2, 0x89, 0x8b, 0x3, 0x2, 0x2, 0x2, 0x8a, 0x88, 0x3, 
    0x2, 0x2, 0x2, 0x8b, 0x8c, 0x7, 0x3, 0x2, 0x2, 0x8c, 0x91, 0x5, 0x14, 
    0xb, 0x2, 0x8d, 0x8e, 0x7, 0x7, 0x2, 0x2, 0x8e, 0x90, 0x5, 0x14, 0xb, 
    0x2, 0x8f, 0x8d, 0x3, 0x2, 0x2, 0x2, 0x90, 0x93, 0x3, 0x2, 0x2, 0x2, 
    0x91, 0x8f, 0x3, 0x2, 0x2, 0x2, 0x91, 0x92, 0x3, 0x2, 0x2, 0x2, 0x92, 
    0x13, 0x3, 0x2, 0x2, 0x2, 0x93, 0x91, 0x3, 0x2, 0x2, 0x2, 0x94, 0x97, 
    0x5, 0x16, 0xc, 0x2, 0x95, 0x97, 0x5, 0x10, 0x9, 0x2, 0x96, 0x94, 0x3, 
    0x2, 0x2, 0x2, 0x96, 0x95, 0x3, 0x2, 0x2, 0x2, 0x97, 0x15, 0x3, 0x2, 
    0x2, 0x2, 0x98, 0x99, 0x5, 0x26, 0x14, 0x2, 0x99, 0x17, 0x3, 0x2, 0x2, 
    0x2, 0x9a, 0x9b, 0x7, 0x10, 0x2, 0x2, 0x9b, 0x9c, 0x5, 0x16, 0xc, 0x2, 
    0x9c, 0x9d, 0x7, 0xa, 0x2, 0x2, 0x9d, 0x9e, 0x5, 0x24, 0x13, 0x2, 0x9e, 
    0x19, 0x3, 0x2, 0x2, 0x2, 0x9f, 0xa0, 0x7, 0xb, 0x2, 0x2, 0xa0, 0xa1, 
    0x5, 0x16, 0xc, 0x2, 0xa1, 0xa2, 0x7, 0xa, 0x2, 0x2, 0xa2, 0xa3, 0x5, 
    0x24, 0x13, 0x2, 0xa3, 0x1b, 0x3, 0x2, 0x2, 0x2, 0xa4, 0xa5, 0x7, 0xc, 
    0x2, 0x2, 0xa5, 0xa6, 0x7, 0xa, 0x2, 0x2, 0xa6, 0xa7, 0x5, 0x24, 0x13, 
    0x2, 0xa7, 0x1d, 0x3, 0x2, 0x2, 0x2, 0xa8, 0xa9, 0x7, 0x1b, 0x2, 0x2, 
    0xa9, 0xaa, 0x5, 0x16, 0xc, 0x2, 0xaa, 0xab, 0x7, 0xa, 0x2, 0x2, 0xab, 
    0xac, 0x5, 0x24, 0x13, 0x2, 0xac, 0x1f, 0x3, 0x2, 0x2, 0x2, 0xad, 0xae, 
    0x7, 0xf, 0x2, 0x2, 0xae, 0xaf, 0x7, 0x1e, 0x2, 0x2, 0xaf, 0xb0, 0x7, 
    0x13, 0x2, 0x2, 0xb0, 0xb1, 0x7, 0x17, 0x2, 0x2, 0xb1, 0xb2, 0x7, 0x1c, 
    0x2, 0x2, 0xb2, 0xb3, 0x5, 0x22, 0x12, 0x2, 0xb3, 0xb4, 0x7, 0x1d, 0x2, 
    0x2, 0xb4, 0xb5, 0x7, 0xa, 0x2, 0x2, 0xb5, 0xb6, 0x5, 0x24, 0x13, 0x2, 
    0xb6, 0x21, 0x3, 0x2, 0x2, 0x2, 0xb7, 0xc0, 0x7, 0x20, 0x2, 0x2, 0xb8, 
    0xb9, 0x7, 0x20, 0x2, 0x2, 0xb9, 0xba, 0x7, 0x7, 0x2, 0x2, 0xba, 0xbd, 
    0x7, 0x20, 0x2, 0x2, 0xbb, 0xbc, 0x7, 0x7, 0x2, 0x2, 0xbc, 0xbe, 0x7, 
    0x20, 0x2, 0x2, 0xbd, 0xbb, 0x3, 0x2, 0x2, 0x2, 0xbd, 0xbe, 0x3, 0x2, 
    0x2, 0x2, 0xbe, 0xc0, 0x3, 0x2, 0x2, 0x2, 0xbf, 0xb7, 0x3, 0x2, 0x2, 
    0x2, 0xbf, 0xb8, 0x3, 0x2, 0x2, 0x2, 0xc0, 0x23, 0x3, 0x2, 0x2, 0x2, 
    0xc1, 0xc5, 0x5, 0xa, 0x6, 0x2, 0xc2, 0xc3, 0x7, 0x25, 0x2, 0x2, 0xc3, 
    0xc5, 0x5, 0x4, 0x3, 0x2, 0xc4, 0xc1, 0x3, 0x2, 0x2, 0x2, 0xc4, 0xc2, 
    0x3, 0x2, 0x2, 0x2, 0xc5, 0x25, 0x3, 0x2, 0x2, 0x2, 0xc6, 0xc7, 0x8, 
    0x14, 0x1, 0x2, 0xc7, 0xc8, 0x5, 0x28, 0x15, 0x2, 0xc8, 0xce, 0x3, 0x2, 
    0x2, 0x2, 0xc9, 0xca, 0xc, 0x4, 0x2, 0x2, 0xca, 0xcb, 0x7, 0x15, 0x2, 
    0x2, 0xcb, 0xcd, 0x5, 0x28, 0x15, 0x2, 0xcc, 0xc9, 0x3, 0x2, 0x2, 0x2, 
    0xcd, 0xd0, 0x3, 0x2, 0x2, 0x2, 0xce, 0xcc, 0x3, 0x2, 0x2, 0x2, 0xce, 
    0xcf, 0x3, 0x2, 0x2, 0x2, 0xcf, 0x27, 0x3, 0x2, 0x2, 0x2, 0xd0, 0xce, 
    0x3, 0x2, 0x2, 0x2, 0xd1, 0xd2, 0x8, 0x15, 0x1, 0x2, 0xd2, 0xd3, 0x5, 
    0x2a, 0x16, 0x2, 0xd3, 0xd9, 0x3, 0x2, 0x2, 0x2, 0xd4, 0xd5, 0xc, 0x4, 
    0x2, 0x2, 0xd5, 0xd6, 0x7, 0x4, 0x2, 0x2, 0xd6, 0xd8, 0x5, 0x2a, 0x16, 
    0x2, 0xd7, 0xd4, 0x3, 0x2, 0x2, 0x2, 0xd8, 0xdb, 0x3, 0x2, 0x2, 0x2, 
    0xd9, 0xd7, 0x3, 0x2, 0x2, 0x2, 0xd9, 0xda, 0x3, 0x2, 0x2, 0x2, 0xda, 
    0x29, 0x3, 0x2, 0x2, 0x2, 0xdb, 0xd9, 0x3, 0x2, 0x2, 0x2, 0xdc, 0xdd, 
    0x7, 0x14, 0x2, 0x2, 0xdd, 0xe0, 0x5, 0x2a, 0x16, 0x2, 0xde, 0xe0, 0x5, 
    0x2c, 0x17, 0x2, 0xdf, 0xdc, 0x3, 0x2, 0x2, 0x2, 0xdf, 0xde, 0x3, 0x2, 
    0x2, 0x2, 0xe0, 0x2b, 0x3, 0x2, 0x2, 0x2, 0xe1, 0xe2, 0x8, 0x17, 0x1, 
    0x2, 0xe2, 0xe3, 0x5, 0x2e, 0x18, 0x2, 0xe3, 0xe9, 0x3, 0x2, 0x2, 0x2, 
    0xe4, 0xe5, 0xc, 0x4, 0x2, 0x2, 0xe5, 0xe6, 0x7, 0x1f, 0x2, 0x2, 0xe6, 
    0xe8, 0x5, 0x2e, 0x18, 0x2, 0xe7, 0xe4, 0x3, 0x2, 0x2, 0x2, 0xe8, 0xeb, 
    0x3, 0x2, 0x2, 0x2, 0xe9, 0xe7, 0x3, 0x2, 0x2, 0x2, 0xe9, 0xea, 0x3, 
    0x2, 0x2, 0x2, 0xea, 0x2d, 0x3, 0x2, 0x2, 0x2, 0xeb, 0xe9, 0x3, 0x2, 
    0x2, 0x2, 0xec, 0xed, 0x8, 0x18, 0x1, 0x2, 0xed, 0xee, 0x5, 0x30, 0x19, 
    0x2, 0xee, 0xf4, 0x3, 0x2, 0x2, 0x2, 0xef, 0xf0, 0xc, 0x4, 0x2, 0x2, 
    0xf0, 0xf1, 0x7, 0x22, 0x2, 0x2, 0xf1, 0xf3, 0x5, 0x30, 0x19, 0x2, 0xf2, 
    0xef, 0x3, 0x2, 0x2, 0x2, 0xf3, 0xf6, 0x3, 0x2, 0x2, 0x2, 0xf4, 0xf2, 
    0x3, 0x2, 0x2, 0x2, 0xf4, 0xf5, 0x3, 0x2, 0x2, 0x2, 0xf5, 0x2f, 0x3, 
    0x2, 0x2, 0x2, 0xf6, 0xf4, 0x3, 0x2, 0x2, 0x2, 0xf7, 0xf8, 0x8, 0x19, 
    0x1, 0x2, 0xf8, 0xf9, 0x5, 0x32, 0x1a, 0x2, 0xf9, 0xff, 0x3, 0x2, 0x2, 
    0x2, 0xfa, 0xfb, 0xc, 0x4, 0x2, 0x2, 0xfb, 0xfc, 0x7, 0x23, 0x2, 0x2, 
    0xfc, 0xfe, 0x5, 0x32, 0x1a, 0x2, 0xfd, 0xfa, 0x3, 0x2, 0x2, 0x2, 0xfe, 
    0x101, 0x3, 0x2, 0x2, 0x2, 0xff, 0xfd, 0x3, 0x2, 0x2, 0x2, 0xff, 0x100, 
    0x3, 0x2, 0x2, 0x2, 0x100, 0x31, 0x3, 0x2, 0x2, 0x2, 0x101, 0xff, 0x3, 
    0x2, 0x2, 0x2, 0x102, 0x103, 0x7, 0x22, 0x2, 0x2, 0x103, 0x106, 0x5, 
    0x32, 0x1a, 0x2, 0x104, 0x106, 0x5, 0x34, 0x1b, 0x2, 0x105, 0x102, 0x3, 
    0x2, 0x2, 0x2, 0x105, 0x104, 0x3, 0x2, 0x2, 0x2, 0x106, 0x33, 0x3, 0x2, 
    0x2, 0x2, 0x107, 0x111, 0x5, 0x36, 0x1c, 0x2, 0x108, 0x111, 0x7, 0x1e, 
    0x2, 0x2, 0x109, 0x111, 0x7, 0x24, 0x2, 0x2, 0x10a, 0x111, 0x7, 0x21, 
    0x2, 0x2, 0x10b, 0x111, 0x7, 0x20, 0x2, 0x2, 0x10c, 0x10d, 0x7, 0x1c, 
    0x2, 0x2, 0x10d, 0x10e, 0x5, 0x16, 0xc, 0x2, 0x10e, 0x10f, 0x7, 0x1d, 
    0x2, 0x2, 0x10f, 0x111, 0x3, 0x2, 0x2, 0x2, 0x110, 0x107, 0x3, 0x2, 
    0x2, 0x2, 0x110, 0x108, 0x3, 0x2, 0x2, 0x2, 0x110, 0x109, 0x3, 0x2, 
    0x2, 0x2, 0x110, 0x10a, 0x3, 0x2, 0x2, 0x2, 0x110, 0x10b, 0x3, 0x2, 
    0x2, 0x2, 0x110, 0x10c, 0x3, 0x2, 0x2, 0x2, 0x111, 0x35, 0x3, 0x2, 0x2, 
    0x2, 0x112, 0x113, 0x9, 0x2, 0x2, 0x2, 0x113, 0x37, 0x3, 0x2, 0x2, 0x2, 
    0x1a, 0x3e, 0x43, 0x48, 0x4f, 0x56, 0x5a, 0x5d, 0x64, 0x6d, 0x81, 0x88, 
    0x91, 0x96, 0xbd, 0xbf, 0xc4, 0xce, 0xd9, 0xdf, 0xe9, 0xf4, 0xff, 0x105, 
    0x110, 
  };

  atn::ATNDeserializer deserializer;
  _atn = deserializer.deserialize(_serializedATN);

  size_t count = _atn.getNumberOfDecisions();
  _decisionToDFA.reserve(count);
  for (size_t i = 0; i < count; i++) { 
    _decisionToDFA.emplace_back(_atn.getDecisionState(i), i);
  }
}

CodeParser::Initializer CodeParser::_init;
