#pragma once

#include <string>
#include <vector>

enum class TokenType
{
    exit,    // basic return TokenType
    int_lit, // TokenType for an integer literal
    semi,    // TokenType to represent a semicolon i.e. ';'
    open_param,
    close_param,
    let,
    eq,
    ident
};

struct Token
{
    TokenType type;
    std::optional<std::string> value{};
};

class Tokenizer
{
public:
    inline explicit Tokenizer(std::string src)
        : m_src(std::move(src))
    {
    }

    inline std::vector<Token> tokenize(std::string input)
    {
        std::vector<Token> tokens;
        std::string buf;

        while (peek().has_value())
        {
            if (std::isalpha(peek().value()))
            {
                buf.push_back(consume());
                while (peek().has_value() && std::isalnum(peek().value()))
                {
                    buf.push_back(consume());
                }
                if (buf == "exit")
                {
                    tokens.push_back({.type = TokenType::exit});
                    buf.clear();
                    continue;
                }
                else if (buf == "let")
                {
                    tokens.push_back({.type = TokenType::let, .value = buf});
                    buf.clear();
                    continue;
                }
                else
                {
                    tokens.push_back({.type = TokenType::ident, .value = buf});
                    buf.clear();
                    continue;
                }
            }
            else if (std::isdigit(peek().value()))
            {
                buf.push_back(consume());
                while (peek().has_value() && std::isdigit(peek().value()))
                {
                    buf.push_back(consume());
                }
                tokens.push_back({.type = TokenType::int_lit, .value = buf});
                buf.clear();
                continue;
            }
            else if (peek().value() == '(')
            {
                consume();
                tokens.push_back({.type = TokenType::open_param});
            }
            else if (peek().value() == ')')
            {
                consume();
                tokens.push_back({.type = TokenType::close_param});
            }
            else if (peek().value() == ';')
            {
                consume();
                tokens.push_back({.type = TokenType::semi});
                continue;
            }
            else if (peek().value() == '=')
            {
                consume();
                tokens.push_back({.type = TokenType::eq});
                continue;
            }
            else if (std::isspace(peek().value()))
            {
                consume();
                continue;
            }
            else
            {
                std::cerr << "something is wrong!" << std::endl;
                exit(EXIT_FAILURE);
            }
        }
        m_index = 0;
        return tokens;
    }

private:
    [[nodiscard]] inline std::optional<char> peek(int offset = 0) const
    {
        if (m_index + offset >= m_src.length())
        {
            return {};
        }
        else
        {
            return m_src.at(m_index + offset);
        }
    }

    inline char consume()
    {
        return m_src.at(m_index++);
    }

    const std::string m_src;
    size_t m_index = 0;
};