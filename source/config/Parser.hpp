#ifndef PARSER_HPP
#define PARSER_HPP

#include <iostream>
#include <vector>
#include "Token.hpp"
#include "node/ConfigNode.hpp"
#include "node/ServerNode.hpp"
#include "ParseResult.hpp"

class Parser {
public:
    Parser(std::vector<Token> &tokens_);

    Token &advance();

    ParseResult parse();

    ParseResult config();

    ParseResult server();

    ParseResult route();

    ParseResult param(const ContextInfo *paramsInfo);

    static const ContextInfo &getParamInfo(const ContextInfo *paramsInfo, const std::string &param);

    bool expect_lcurly(ParseResult &result);

    bool expect_rcurly(ParseResult &result);

    void skip_end_of_line_tokens();

    void skip_param_or_group_tokens();

    std::vector<Token> &tokens;
    Token              *current_token;
    int tok_idx;
};

#endif
