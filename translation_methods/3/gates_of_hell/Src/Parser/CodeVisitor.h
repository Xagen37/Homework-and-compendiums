
// Generated from Code.g4 by ANTLR 4.9.3

#pragma once


#include "antlr4-runtime.h"
#include "CodeParser.h"



/**
 * This class defines an abstract visitor for a parse tree
 * produced by CodeParser.
 */
class  CodeVisitor : public antlr4::tree::AbstractParseTreeVisitor {
public:

  /**
   * Visit parse trees produced by CodeParser.
   */
    virtual antlrcpp::Any visitFile(CodeParser::FileContext *context) = 0;

    virtual antlrcpp::Any visitExpressions(CodeParser::ExpressionsContext *context) = 0;

    virtual antlrcpp::Any visitExpression(CodeParser::ExpressionContext *context) = 0;

    virtual antlrcpp::Any visitMulti_line_expr(CodeParser::Multi_line_exprContext *context) = 0;

    virtual antlrcpp::Any visitMany_one_line_exprs(CodeParser::Many_one_line_exprsContext *context) = 0;

    virtual antlrcpp::Any visitOne_line_expr(CodeParser::One_line_exprContext *context) = 0;

    virtual antlrcpp::Any visitPrint(CodeParser::PrintContext *context) = 0;

    virtual antlrcpp::Any visitInput(CodeParser::InputContext *context) = 0;

    virtual antlrcpp::Any visitVar_ass(CodeParser::Var_assContext *context) = 0;

    virtual antlrcpp::Any visitInit(CodeParser::InitContext *context) = 0;

    virtual antlrcpp::Any visitOperation(CodeParser::OperationContext *context) = 0;

    virtual antlrcpp::Any visitIf_statement(CodeParser::If_statementContext *context) = 0;

    virtual antlrcpp::Any visitElif_statement(CodeParser::Elif_statementContext *context) = 0;

    virtual antlrcpp::Any visitElse_statement(CodeParser::Else_statementContext *context) = 0;

    virtual antlrcpp::Any visitWhile_statement(CodeParser::While_statementContext *context) = 0;

    virtual antlrcpp::Any visitFor_statement(CodeParser::For_statementContext *context) = 0;

    virtual antlrcpp::Any visitRange(CodeParser::RangeContext *context) = 0;

    virtual antlrcpp::Any visitAfter_colon(CodeParser::After_colonContext *context) = 0;

    virtual antlrcpp::Any visitDisj(CodeParser::DisjContext *context) = 0;

    virtual antlrcpp::Any visitConj(CodeParser::ConjContext *context) = 0;

    virtual antlrcpp::Any visitNegate(CodeParser::NegateContext *context) = 0;

    virtual antlrcpp::Any visitComparison(CodeParser::ComparisonContext *context) = 0;

    virtual antlrcpp::Any visitSum_term(CodeParser::Sum_termContext *context) = 0;

    virtual antlrcpp::Any visitMul_term(CodeParser::Mul_termContext *context) = 0;

    virtual antlrcpp::Any visitTerm(CodeParser::TermContext *context) = 0;

    virtual antlrcpp::Any visitAtom(CodeParser::AtomContext *context) = 0;

    virtual antlrcpp::Any visitBool_lit(CodeParser::Bool_litContext *context) = 0;


};

