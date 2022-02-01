
// Generated from Code.g4 by ANTLR 4.9.3

#pragma once


#include "antlr4-runtime.h"
#include "CodeVisitor.h"


/**
 * This class provides an empty implementation of CodeVisitor, which can be
 * extended to create a visitor which only needs to handle a subset of the available methods.
 */
class  CodeBaseVisitor : public CodeVisitor {
public:

  virtual antlrcpp::Any visitFile(CodeParser::FileContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitExpressions(CodeParser::ExpressionsContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitExpression(CodeParser::ExpressionContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitMulti_line_expr(CodeParser::Multi_line_exprContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitMany_one_line_exprs(CodeParser::Many_one_line_exprsContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitOne_line_expr(CodeParser::One_line_exprContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitPrint(CodeParser::PrintContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitInput(CodeParser::InputContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitVar_ass(CodeParser::Var_assContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitInit(CodeParser::InitContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitOperation(CodeParser::OperationContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitIf_statement(CodeParser::If_statementContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitElif_statement(CodeParser::Elif_statementContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitElse_statement(CodeParser::Else_statementContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitWhile_statement(CodeParser::While_statementContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitFor_statement(CodeParser::For_statementContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitRange(CodeParser::RangeContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitAfter_colon(CodeParser::After_colonContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitDisj(CodeParser::DisjContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitConj(CodeParser::ConjContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitNegate(CodeParser::NegateContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitComparison(CodeParser::ComparisonContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitSum_term(CodeParser::Sum_termContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitMul_term(CodeParser::Mul_termContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitTerm(CodeParser::TermContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitAtom(CodeParser::AtomContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitBool_lit(CodeParser::Bool_litContext *ctx) override {
    return visitChildren(ctx);
  }


};

