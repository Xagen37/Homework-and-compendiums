#pragma once
#include "lexer.h"
#include "cgraph.h"
#include "cdt.h"

#include <cstdarg>
#include <exception>
#include <initializer_list>
#include <memory>
#include <string>
#include <vector>

struct unexpected_token : std::exception
{
    const char* what() const noexcept override
    {
        return "Parse error: unexpected token";
    }
};

class SyntaxTree
{
public:
    SyntaxTree() = default;

    SyntaxTree(std::string str)
        : val(str)
    {}

    SyntaxTree(std::string str, std::initializer_list<SyntaxTree> children)
        : val(str)
        , children_v(children)
    {}

    Agraph_t* as_cgraph() const
    {
        Agraph_t* g;
        char name[11] = "Parse tree";
        g = agopen(name, Agundirected, NULL);
        dfs(g, nullptr);
        return g;
    }
private:
    void dfs(Agraph_t* g, Agnode_t* par) const
    {
        Agnode_t* curr;
        curr = agnode(g, const_cast<char*>(val.c_str()), TRUE);
        if (par != nullptr)
        {
            char name[1] = "";
            agedge(g, par, curr, name, TRUE);
        }
        for (const SyntaxTree& child : children_v)
        {
            child.dfs(g, curr);
        }
    }
private:
    std::string val;
    std::vector<SyntaxTree> children_v;
};

class Parser
{
public:
    Parser(std::string input)
        : lex(input)
    {}

    SyntaxTree parse()
    {
        SyntaxTree res = S();
        lex.next_token();
        throw_if_not({ Token::END });
        return res;
    }

private:
    void throw_if_not(std::initializer_list<Token> models)
    {
        Token to_check = lex.curr_token();
        for (const Token& model : models)
        {
            if (to_check == model)
                return;
        }
        throw unexpected_token();
    }

    SyntaxTree S()
    {
        throw_if_not({ Token::VAL, Token::VAR });
        SyntaxTree res;
        switch (lex.curr_token())
        {
            case Token::VAL:
            {
                SyntaxTree res = V1();
                break;
            }
            case Token::VAR:
            {
                SyntaxTree res = V2();
                break;
            }
            default:
                throw unexpected_token();
        }

        throw_if_not({ Token::SEMICOL });
        SyntaxTree semicol = SyntaxTree(";");

        return SyntaxTree("S()", { res, semicol });
    }

    SyntaxTree V1()
    {
        // It is already asserted in S()
        SyntaxTree key = SyntaxTree("val");

        lex.next_token();
        SyntaxTree desc = B();

        lex.next_token();
        SyntaxTree init = I();

        return SyntaxTree("V1()", { key, desc, init });
    }

    SyntaxTree V2()
    {
        // It is already asserted in S()
        SyntaxTree key = SyntaxTree("var");

        lex.next_token();
        SyntaxTree desc = B();

        lex.next_token();
        SyntaxTree cont = C();

        return SyntaxTree("V2()", { key, desc, cont });
    }

    SyntaxTree B()
    {
        SyntaxTree name = N();

        lex.next_token();
        throw_if_not({ Token::COL });
        SyntaxTree colon = SyntaxTree(":");

        lex.next_token();
        SyntaxTree type = T();

        return SyntaxTree("D()", { name, colon, type });
    }

    SyntaxTree N()
    {
        throw_if_not({ Token::NAME_OR_TYPE });
        return SyntaxTree("N()", { SyntaxTree(lex.get_str_val()) });
    }

    SyntaxTree T()
    {
        throw_if_not({ Token::NAME_OR_TYPE });
        return SyntaxTree("T()", { SyntaxTree(lex.get_str_val()) });
    }

    SyntaxTree C()
    {
        // eps
        if (lex.curr_token() == Token::SEMICOL)
        {
            return SyntaxTree("C()", { SyntaxTree("#eps#") });
        }

        // I
        SyntaxTree init = I();
        return SyntaxTree("C()", { init });
    }

    SyntaxTree I()
    {
        throw_if_not({ Token::EQ });
        SyntaxTree eq_sign = SyntaxTree("=");

        lex.next_token();
        SyntaxTree init_val = V();

        lex.next_token();
        return SyntaxTree("I()", { eq_sign, init_val });
    }

    SyntaxTree V()
    {
        throw_if_not({ Token::NUM });
        return SyntaxTree("V()", { SyntaxTree(lex.get_str_val()) });
    }

    //SyntaxTree S()
    //{
    //    SyntaxTree keyword = K();

    //    lex.next_token();
    //    SyntaxTree description = D();

    //    throw_if_not({ Token::SEMICOL });
    //    SyntaxTree semicol = SyntaxTree(";");

    //    return SyntaxTree("S()", { keyword, description, semicol });
    //}

    //SyntaxTree K()
    //{
    //    throw_if_not({ Token::VAL, Token::VAR });
    //    return lex.curr_token() == Token::VAL ? 
    //        SyntaxTree("K()", { SyntaxTree("val") }) : 
    //        SyntaxTree("K()", { SyntaxTree("var") });
    //}

    //SyntaxTree D()
    //{
    //    SyntaxTree name = N();

    //    lex.next_token();
    //    throw_if_not({ Token::COL });
    //    SyntaxTree colon = SyntaxTree(":");

    //    lex.next_token();
    //    SyntaxTree initblock = I();

    //    return SyntaxTree("D()", { name, colon, initblock });
    //}

    //SyntaxTree N()
    //{
    //    throw_if_not({ Token::NAME_OR_TYPE });
    //    return SyntaxTree("N()", { SyntaxTree(lex.get_str_val()) });
    //}

    //SyntaxTree I()
    //{
    //    SyntaxTree type = T();

    //    lex.next_token();
    //    SyntaxTree initializer = C();

    //    return SyntaxTree("I()", { type, initializer });
    //}

    //SyntaxTree T()
    //{
    //    throw_if_not({ Token::NAME_OR_TYPE });
    //    return SyntaxTree("T()", { SyntaxTree(lex.get_str_val()) });
    //}

    //SyntaxTree C()
    //{
    //    // eps
    //    if (lex.curr_token() == Token::SEMICOL)
    //    {
    //        return SyntaxTree("C()", { SyntaxTree("#eps#") });
    //    }

    //    // = V
    //    throw_if_not({ Token::EQ });
    //    SyntaxTree eq_sign = SyntaxTree("=");

    //    lex.next_token();
    //    SyntaxTree init_val = V();

    //    lex.next_token();
    //    return SyntaxTree("C()", { eq_sign, init_val });
    //}

    //SyntaxTree V()
    //{
    //    throw_if_not({ Token::NUM });
    //    return SyntaxTree("V()", { SyntaxTree(lex.get_str_val()) });
    //}

private:
    Lexer lex;
};