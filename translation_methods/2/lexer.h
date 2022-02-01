#pragma once
#include <exception>
#include <functional>
#include <string>
#include <sstream>

enum class Token
{
    VAL, VAR,
    NAME_OR_TYPE, COL,
    EQ, NUM,
    SEMICOL,
    END
};

struct unexpected_char : std::exception
{
    const char* what() const noexcept override
    {
        return "Lexer got an unexpected character";
    }
};

class Lexer
{
    std::istringstream str;
    std::string accum;
    Token token;
    int where = 0; // debug variable

    void consume_while(const std::function<bool(const char&)>& predicate)
    {
        char ch = 0;
        while ((ch = str.peek()) >= 0 && predicate(ch))
        { 
            str.get();
            accum += ch;
            where++;
        }
    }

    void skip_whitespace()
    {
        consume_while([](const char& ch) { return std::isspace(static_cast<unsigned char>(ch)); });
    }

    int next_char()
    {
        where++;
        return str ? str.get() : INT_MIN;
    }
public:
    Lexer(const std::string& text)
        : str(text)
        , token(Token::END)
    {
        next_token();
    }

    Lexer(std::string&& text) noexcept
        : str(std::move(text))
        , token(Token::END)
    {
        next_token();
    }

    operator bool() const
    { return str.good(); }

    Token curr_token() const noexcept
    {
        return token;
    }

    void next_token()
    {
        skip_whitespace();
        accum.clear();
        int curr_char = next_char();
        if (curr_char < 0)
        { token = Token::END; }
        else if (curr_char == ':')
        { token = Token::COL; }
        else if (curr_char == ';')
        { token = Token::SEMICOL; }
        else if (curr_char == '=')
        { token = Token::EQ; }
        else if (std::isdigit(static_cast<unsigned char>(curr_char)) || curr_char == '-')
        {
            accum += curr_char;
            token = Token::NUM;
            consume_while([](const char& ch) { return std::isdigit(static_cast<unsigned char>(ch)); });
        }
        else if (std::isalpha(static_cast<unsigned char>(curr_char)))
        {
            if (curr_char == 'v')
            {
                accum += 'v';
                if ((curr_char = next_char()) == 'a')
                {
                    accum += 'a';
                    curr_char = next_char();
                    if (isspace(static_cast<unsigned char>(str.peek())))
                    {
                        if (curr_char == 'r')
                        {
                            token = Token::VAR;
                            return;
                        }
                        else if (curr_char == 'l')
                        {
                            token = Token::VAL;
                            return;
                        }
                    }
                }
            }
            token = Token::NAME_OR_TYPE;
            accum += curr_char;
            consume_while([](const char& ch) { return std::isdigit(static_cast<unsigned char>(ch)) || 
                                                      std::isalpha(static_cast<unsigned char>(ch)) ||
                                                      ch == '_'; });
        }
        else
        {
            throw unexpected_char();
        }
    }

    std::string get_str_val() const
    {
        return accum;
    }
};