#include <any>
#include <exception>
#include <iostream>
#include <map>
#include <set>
#include <string>
#include <vector>

#include "antlr4-runtime/antlr4-runtime.h"
#include "Parser/CodeLexer.h"
#include "Parser/CodeParser.h"
#include "Parser/CodeVisitor.h"

struct parser_visitor_exception : std::exception
{
    const char* what() const noexcept override
    {
        return "Visitor error: unexpected token";
    }
};

struct transfer_exception : std::exception
{
    const char* what() const noexcept override
    {
        return "Transfer error: met unsupported opperation";
    }
};

using namespace antlr4;

class Visitor : CodeVisitor
{
    using op_ret_t = std::pair<std::string, std::string>;  // string - type
    std::map<std::string, std::string> vars;               // from name to type
    int level = 1;                                         // tabulation level

    std::string gen_indent()
    {
        return std::string(level * 4, ' ');
    }
public:
    // Inherited via CodeVisitor
    virtual antlrcpp::Any visitFile(CodeParser::FileContext* context) override
    {
        std::cerr << "visitFile\n";
        std::string include = "#include <stdio.h>\n";

        std::string main_decl = "int main (void)\n{\n";

        std::string body = visitExpressions(context->expressions()).as<std::string>();
        while (level > 1)
        {
            level--;
            body += gen_indent() + "}\n";
        }
        std::string vars_decls = "";
        for (const auto& [name, type] : vars)
        {
            if (type == "char")
            {
                vars_decls += type + " " + name + "[256];\n";
            }
            else
            {
                vars_decls += type + " " + name + ";\n";
            }
        }

        std::string end = gen_indent() + "return 0;\n}\n";

        std::string result = include + vars_decls + main_decl + body + end;
        std::cerr << "visitFile2\n";
        return result;
    }

    virtual antlrcpp::Any visitExpressions(CodeParser::ExpressionsContext* context) override
    {
        std::cerr << "visitExpressions\n";
        std::vector<std::string> exprs;
        for (auto exprCon : context->expression())
        {
            std::string ops = visitExpression(exprCon).as<std::string>();
            exprs.emplace_back(std::move(ops));
        }

        std::string body;
        for (const std::string & str : exprs)
        { body += str; }

        std::cerr << "visitExpressions2\n";
        return body;
    }

    virtual antlrcpp::Any visitExpression(CodeParser::ExpressionContext* context) override
    {
        std::cerr << "visitExpression\n";
        std::string pre;
        while (context->TAB().size() + 1 < level)
        {
            level--;
            pre += gen_indent() + "}\n";
        }
        if (context->many_one_line_exprs())
        {
            return pre + visitMany_one_line_exprs(context->many_one_line_exprs()).as<std::string>();
        }
        else if (context->multi_line_expr())
        {
            return pre + visitMulti_line_expr(context->multi_line_expr()).as<std::string>();
        }
        else throw parser_visitor_exception();
    }

    virtual antlrcpp::Any visitMulti_line_expr(CodeParser::Multi_line_exprContext* context) override
    {
        std::cerr << "visitMulti_line_expr\n";
        if (context->if_statement())
        {
            return visitIf_statement(context->if_statement());
        }
        else if (context->elif_statement())
        {
            return visitElif_statement(context->elif_statement());
        }
        else if (context->else_statement())
        {
            return visitElse_statement(context->else_statement());
        }
        else if (context->while_statement())
        {
            return visitWhile_statement(context->while_statement());
        }
        else if (context->for_statement())
        {
            return visitFor_statement(context->for_statement());
        }
        else throw parser_visitor_exception();
    }

    virtual antlrcpp::Any visitMany_one_line_exprs(CodeParser::Many_one_line_exprsContext* context) override
    {
        std::cerr << "visitMany_one_line_exprs\n";
        std::string res;
        for (auto exprCon : context->one_line_expr())
        {
            res += visitOne_line_expr(exprCon).as<std::string>();
        }
        std::cerr << "visitMany_one_line_exprs2\n";
        return res;
    }

    virtual antlrcpp::Any visitOne_line_expr(CodeParser::One_line_exprContext* context) override
    {
        std::cerr << "visitOne_line_expr\n";
        std::string indent = gen_indent();

        std::string expr;
        if (context->var_ass())
        {
            return visitVar_ass(context->var_ass()).as<std::string>();
        }
        else if (context->operation())
        {
            expr = visitOperation(context->operation()).as<op_ret_t>().first;
        }
        else if (context->BREAK())
        {
            expr = "break";
        }
        else if (context->CONTINUE())
        {
            expr = "continue";
        }
        else if (context->print())
        {
            expr = visitPrint(context->print()).as<std::string>();
        }
        else throw parser_visitor_exception();

        std::cerr << "visitOne_line_expr2\n";
        return indent + expr + ";\n";
    }

    virtual antlrcpp::Any visitPrint(CodeParser::PrintContext* context) override
    {
        std::cerr << "visitPrint\n";
        std::vector<std::string> ops;
        std::vector<std::string> formats;
        for (auto opCon : context->operation())
        {
            auto [_expr, _type] = visitOperation(opCon).as<op_ret_t>();
            if (_type == "const char *" || _type == "char")
            {
                if (vars.count(_expr) == 0)
                { formats.push_back(_expr.substr(1, _expr.size() - 2)); }
                else
                {
                    formats.push_back("%s");
                    ops.push_back(_expr);
                }
            }
            else if (_type == "double")
            {
                formats.push_back("%lf");
                ops.push_back(_expr);
            }
            else if (_type == "int")
            {
                formats.push_back("%d");
                ops.push_back(_expr);
            }
            formats.push_back(" ");
        }

        std::string format = "\"";
        for (const std::string& form : formats)
        {
            format += form;
        }
        format += "\\n\"";

        std::string args;
        for (const std::string& arg : ops)
        {
            args += ", ";
            args += arg;
        }
        
        std::cerr << "visitPrint2\n";
        return "printf(" + format + args + ")";
    }

    virtual antlrcpp::Any visitInput(CodeParser::InputContext* context) override
    {
        std::cerr << "visitInput\n";
        if (context->INT_TYPE())
        {
            return std::string("int");
        }
        else if (context->FLOAT_TYPE())
        {
            return std::string("double");
        }
        else
        {
            return std::string("char");
        }
    }

    virtual antlrcpp::Any visitVar_ass(CodeParser::Var_assContext* context) override
    {
        std::cerr << "visitVar_ass\n";
        std::string inits;
        std::string indent = gen_indent();
        for (int i = 0; i < context->IDENTIFICATOR().size(); i++)
        {
            std::string var_name = context->IDENTIFICATOR(i)->getText();
            auto [_expr, _type] = visitInit(context->init(i)).as<op_ret_t>();
            std::string expr, type;
            if (_expr == "")
            {
                type = _type;
                if (type == "int")
                {
                    expr = "scanf(\"%d\", &" + var_name + ")";
                }
                else if (type == "double")
                {
                    expr = "scanf(\"%lf\", &" + var_name + ")";
                }
                else if (type == "char")
                {
                    expr = "scanf(\"%s\", " + var_name + ")";
                }
            }
            else
            {
                expr = var_name + " = " + _expr;
                type = _type;
            }
            inits += indent + expr + ";\n";
            vars[var_name] = type;
        }

        std::cerr << "visitVar_ass2\n";
        return inits;
    }

    virtual antlrcpp::Any visitInit(CodeParser::InitContext* context) override
    {
        if (context->input())
        {
            std::string _type = visitInput(context->input()).as<std::string>();
            std::string expr = "";
            return op_ret_t(expr, _type);
        }
        else if (context->operation())
        {
            return visitOperation(context->operation()).as<op_ret_t>();
        }
        else throw parser_visitor_exception();
    }

    virtual antlrcpp::Any visitOperation(CodeParser::OperationContext* context) override
    {
        std::cerr << "visitOperation\n";
        return visitDisj(context->disj());
    }

    virtual antlrcpp::Any visitIf_statement(CodeParser::If_statementContext* context) override
    {
        std::cerr << "visitIf_statement\n";
        std::string indent = gen_indent();

        std::string condition = visitOperation(context->cond).as<op_ret_t>().first;
        std::string header    = indent + "if (" + condition + ")\n";
        std::string body      = visitAfter_colon(context->block).as<std::string>();

        std::cerr << "visitIf_statement2\n";
        return header + body;
    }

    virtual antlrcpp::Any visitElif_statement(CodeParser::Elif_statementContext* context) override
    {
        std::cerr << "visitElif_statement\n";
        std::string indent = gen_indent();

        std::string condition = visitOperation(context->cond).as<op_ret_t>().first;
        std::string header    = indent + "else if (" + condition + ")\n";
        std::string body      = visitAfter_colon(context->block).as<std::string>();

        std::cerr << "visitElif_statement2\n";
        return header + body;
    }

    virtual antlrcpp::Any visitElse_statement(CodeParser::Else_statementContext* context) override
    {
        std::cerr << "visitElse_statement\n";
        std::string indent = gen_indent();

        std::string header = indent + "else\n";
        std::string body   = visitAfter_colon(context->block).as<std::string>();

        std::cerr << "visitElse_statement2\n";
        return header + body;
    }

    virtual antlrcpp::Any visitWhile_statement(CodeParser::While_statementContext* context) override
    {
        std::cerr << "visitWhile_statement\n";
        std::string indent    = gen_indent();
        std::string condition = visitOperation(context->cond).as<op_ret_t>().first;
        std::string header = indent + "while (" + condition + ")\n";
        std::string body      = visitAfter_colon(context->block).as<std::string>();
        
        std::cerr << "visitWhile_statement2\n";
        return header + body;
    }

    virtual antlrcpp::Any visitFor_statement(CodeParser::For_statementContext* context) override
    {
        std::cerr << "visitFor_statement\n";
        using ret_t = std::vector<std::string>; 

        std::string indent    = gen_indent();
        std::string var_name  = context->IDENTIFICATOR()->getText();
        vars[var_name] = "int";

        ret_t cond_vec = visitRange(context->range()).as<ret_t>();
        std::string start;
        std::string end;
        std::string step;
        switch (cond_vec.size())
        {
            case 1:
            {
                start = "0";
                end   = cond_vec[0];
                step  = "++";
                break;
            }
            case 2:
            {
                start = cond_vec[0];
                end   = cond_vec[1];
                step  = "++";
                break;
            }
            case 3:
            {
                start = cond_vec[0];
                end   = cond_vec[1];
                step  = " += " + cond_vec[2];
                break;
            }
        }
        std::string condition = var_name + " = " + start + "; " + var_name + " < " + end + "; " + var_name + step;
        std::string header    = indent + "for (" + condition + ")\n";
        std::string body      = visitAfter_colon(context->block).as<std::string>();
        
        std::cerr << "visitFor_statement2\n";
        return header + body;
    }

    virtual antlrcpp::Any visitRange(CodeParser::RangeContext* context) override
    {
        std::cerr << "visitRange\n";
        std::vector<std::string> res;

        if (context->from)
        {
            res.push_back(context->from->getText());
        }

        res.push_back(context->to->getText());

        if (context->step)
        {
            res.push_back(context->step->getText());
        }
        
        std::cerr << "visitRange2\n";
        return res;
    }

    virtual antlrcpp::Any visitAfter_colon(CodeParser::After_colonContext* context) override
    {
        std::cerr << "visitAfter_colon\n";
        std::string start_indent  = gen_indent();
        std::string open_bracket  = start_indent + "{\n";
        std::string body;
        level++;
        if (context->expressions())
        {
            body = visitExpressions(context->expressions()).as<std::string>();
        }
        else if (context->many_one_line_exprs())
        {
            body = visitMany_one_line_exprs(context->many_one_line_exprs()).as<std::string>();
        }
        std::cerr << "visitAfter_colon2\n";
        return open_bracket + body;
    }

    virtual antlrcpp::Any visitDisj(CodeParser::DisjContext* context) override
    {
        std::cerr << "visitDisj\n";
        if (context->OR())
        {
            auto [_disj_expr, _disj_type] = visitDisj(context->lhs).as<op_ret_t>();
            std::string op = context->OR()->getText();
            auto [_conj_expr, _conj_type] = visitConj(context->rhs).as<op_ret_t>();

            op_ret_t res(_disj_expr + " " + op + " " + _conj_expr, "int");
            std::cerr << "visitDisj2\n";
            return res;
        }
        else if (context->val)
        {
            return visitConj(context->val);
        }
        else throw parser_visitor_exception();
    }
    virtual antlrcpp::Any visitConj(CodeParser::ConjContext* context) override
    {
        std::cerr << "visitConj\n";
        if (context->AND())
        {
            auto [_conj_expr, _conj_type] = visitConj(context->lhs).as<op_ret_t>();
            std::string op = context->AND()->getText();
            auto [_neg_expr, _neg_type] = visitNegate(context->rhs).as<op_ret_t>();

            op_ret_t res(_conj_expr + " " + op + " " + _neg_expr, "int");
            std::cerr << "visitConj2\n";
            return res;
        }
        else if (context->val)
        {
            return visitNegate(context->val);
        }
        else throw parser_visitor_exception();
    }
    virtual antlrcpp::Any visitNegate(CodeParser::NegateContext* context) override
    {
        std::cerr << "visitNegate\n";
        if (context->op)
        {
            std::string op = context->op->getText();
            auto [_expr, _type] = visitNegate(context->arg).as<op_ret_t>();

            op_ret_t res(op + _expr, "int");
            std::cerr << "visitNegate2\n";
            return res;
        }
        else if (context->val)
        {
            return visitComparison(context->val);
        }
        else throw parser_visitor_exception();
    }
    virtual antlrcpp::Any visitComparison(CodeParser::ComparisonContext* context) override
    {
        std::cerr << "visitComparison\n";
        if (context->op)
        {
            auto [_comp_expr, _comp_type] = visitComparison(context->lhs).as<op_ret_t>();
            std::string op = context->op->getText();
            auto [_sum_expr, _sum_type] = visitSum_term(context->rhs).as<op_ret_t>();

            std::string type;
            if (_comp_type == _sum_type)
            {
                type = "int";
            }
            else if (_comp_type == "int" && _sum_type == "double" ||
                     _comp_type == "double" && _sum_type == "int")
            {
                type = "int";
            }
            else throw transfer_exception();

            op_ret_t res(_comp_expr + " " + op + " " + _sum_expr, type);
            std::cerr << "visitComparison2\n";
            return res;
        }
        else if (context->val)
        {
            return visitSum_term(context->val);
        }
        else throw parser_visitor_exception();
    }
    virtual antlrcpp::Any visitSum_term(CodeParser::Sum_termContext* context) override
    {
        std::cerr << "visitSum_term\n";
        if (context->op)
        {
            auto [_sum_expr, _sum_type] = visitSum_term(context->lhs).as<op_ret_t>();
            std::string op = context->op->getText();
            auto [_mul_expr, _mul_type] = visitMul_term(context->rhs).as<op_ret_t>();

            std::string type;
            if (_sum_type == _mul_type && (_sum_type == "int" || _sum_type == "double"))
            {
                type = _sum_type;
            }
            else if (_sum_type == "int" && _mul_type == "double" ||
                     _sum_type == "double" && _mul_type == "int")
            {
                type = "double";
            }
            else throw transfer_exception();

            op_ret_t res(_sum_expr + " " + op + " " + _mul_expr, type);
            std::cerr << "visitSum_term2\n";
            return res;
        }
        else if (context->val)
        {
            return visitMul_term(context->val);
        }
        else throw parser_visitor_exception();
    }
    virtual antlrcpp::Any visitMul_term(CodeParser::Mul_termContext* context) override
    {
        std::cerr << "visitMul_term\n";
        if (context->op)
        {
            auto [_mul_expr, _mul_type] = visitMul_term(context->lhs).as<op_ret_t>();
            std::string op = context->op->getText();
            auto [_term_expr, _term_type] = visitTerm(context->rhs).as<op_ret_t>();

            std::string type;
            if (_mul_type == _term_type && (_mul_type == "int" || _mul_type == "double"))
            {
                type = _mul_type;
            }
            else if (_mul_type == "int" && _term_type == "double" ||
                     _mul_type == "double" && _term_type == "int")
            {
                type = "double";
            }
            else throw transfer_exception();

            op_ret_t res(_mul_expr + " " + op + " " + _term_expr, type);
            std::cerr << "visitMul_term2\n";
            return res;
        }
        else if (context->val)
        {
            return visitTerm(context->val);
        }
        else throw parser_visitor_exception();
    }
    virtual antlrcpp::Any visitTerm(CodeParser::TermContext* context) override
    {
        std::cerr << "visitTerm\n";
        if (context->val)
        {
            return visitAtom(context->val);
        }
        else if (context->arg)
        {
            std::string op = context->op->getText();
            auto [_expr, _type] = visitTerm(context->arg).as<op_ret_t>();
            if (_type != "int" && _type != "double")
            {
                throw transfer_exception();
            }
            op_ret_t res(op + "(" + _expr + ")", _type);
            std::cerr << "visitTerm2\n";
            return res;
        }
        else throw parser_visitor_exception();
    }
    virtual antlrcpp::Any visitAtom(CodeParser::AtomContext* context) override
    {
        std::cerr << "visitAtom\n";
        std::string expr;
        std::string type;
        if (context->IDENTIFICATOR())
        {
            expr = context->IDENTIFICATOR()->getText();
            type = vars[expr];
        }
        else if (context->bool_lit())
        {
            return visitBool_lit(context->bool_lit());
        }
        else if (context->STRING())
        {
            expr = context->STRING()->getText();
            type = "const char *";
        }
        else if (context->NUM())
        {
            expr = context->NUM()->getText();
            type = (expr.find('.') == std::string::npos) ? "int" : "double";
        }
        else if (context->INT())
        {
            expr = context->INT()->getText();
            type = "int";
        }
        else if (context->operation())
        {
            auto [_expr, _type] = visitOperation(context->operation()).as<op_ret_t>();
            expr = "(" + _expr + ")";
            type = _type;
        }
        else throw parser_visitor_exception();

        op_ret_t res(expr, type);
        std::cerr << "visitAtom2\n";
        return res;
    }
    virtual antlrcpp::Any visitBool_lit(CodeParser::Bool_litContext* context) override
    {
        std::cerr << "visitBool_lit\n";
        std::string val;
        std::string type = "int";
        if (context->TRUE())
        {
            val = "1";
        }
        else if (context->FALSE())
        {
            val = "0";
        }
        else throw parser_visitor_exception();

        op_ret_t res(val, type);
        return res;
    }
};

int main()
{
    std::cout << "Hello, parsers\nEnter a filename of corresponding filename.py file to parse: ";
    std::string filename; std::cin >> filename;
    //std::string filename = "test.txt";
    std::ifstream input;
    input.open(filename + ".py");

    ANTLRInputStream is(input);
    CodeLexer lexer(&is);
    CommonTokenStream tokens(&lexer);
    CodeParser parser(&tokens);

    CodeParser::FileContext* tree = parser.file();
    Visitor m_v;
    std::cout << "Running parser... \n\n";
    std::string out = m_v.visitFile(tree).as<std::string>();
    std::cout << "\n\n... Completed!\n";
    //std::cout << out;
    std::ofstream output;
    output.open("parsed_" + filename + ".c");
    output << out;
    return 0;
}