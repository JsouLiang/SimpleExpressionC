//
//  SimpleExpressionC.c
//  SimpleExpressionC
//
//  Created by Liang on 2020/8/6.
//  Copyright © 2020 Liang. All rights reserved.
//

#include "SimpleExpressionC.h"
#include <ctype.h>

enum {
    SLM_EXPRESSION_TOKEN_UNKNOWN = 0,
    // 数字
    SLM_EXPRESSION_TOKEN_DIGITS,
    // +
    SLM_EXPRESSION_TOKEN_ADD,
    // -
    SLM_EXPRESSION_TOKEN_SUB_OR_MINUS,
    // *
    SLM_EXPRESSION_TOKEN_MUL,
    // /
    SLM_EXPRESSION_TOKEN_DIV,
    // %
    SLM_EXPRESSION_TOKEN_MOD,
    // (
    SLM_EXPRESSION_TOKEN_OPEN,
    // )
    SLM_EXPRESSION_TOKEN_CLOSE,
    SLM_EXPRESSION_TOKEN_END
};


typedef struct {
    int type;
    int value;
} slm_token;

typedef struct {
    const char *exprStr;
    slm_token token;
    int errType;
} slm_expr;

/**
 解析 Token
 */
static void next(slm_expr *expr) {
    // 空格
    while (isspace(*expr->exprStr)) {
        (expr->exprStr)++;
    }
    if (*expr->exprStr == 0) {
        expr->token.type = SLM_EXPRESSION_TOKEN_UNKNOWN;
    } else if (isdigit(*expr->exprStr)) {
        // digit
        expr->token.type = SLM_EXPRESSION_TOKEN_DIGITS;
        expr->token.value = *expr->exprStr - '0';
        expr->exprStr++;
        while (isdigit(*expr->exprStr)) {
            expr->token.value = expr->token.value * 10 + (*expr->exprStr - '0');
            expr->exprStr++;
        }
    } else {
        switch (*expr->exprStr) {
            case '+':
                expr->token.type = SLM_EXPRESSION_TOKEN_ADD;
                expr->exprStr++;
                break;
            case '-':
                expr->token.type = SLM_EXPRESSION_TOKEN_SUB_OR_MINUS;
                expr->exprStr++;
                break;
            case '*':
                expr->token.type = SLM_EXPRESSION_TOKEN_MUL;
                expr->exprStr++;
                break;
            case '/':
                expr->token.type = SLM_EXPRESSION_TOKEN_DIV;
                expr->exprStr++;
                break;
            case '%':
                expr->token.type = SLM_EXPRESSION_TOKEN_MOD;
                expr->exprStr++;
                break;
            case '(':
                expr->token.type = SLM_EXPRESSION_TOKEN_OPEN;
                expr->exprStr++;
                break;
            case ')':
                expr->token.type = SLM_EXPRESSION_TOKEN_CLOSE;
                expr->exprStr++;
                break;
            default:
                expr->token.type = SLM_EXPRESSION_TOKEN_UNKNOWN;
                expr->errType = SLM_EXPRESSION_ERROR_UNKNOW_TOKEN;
                break;
        }
    }
}

static int digit(slm_expr *);
static int expr1(int , slm_expr *);
static int term(slm_expr *);
static int term1(int , slm_expr *);
static int factor(slm_expr *);
/**
 加减乘除：
 expr = expr + term | expr - term | term
 term = term * num | term / num | num
 num = -digit | +digit | digit
 digit = 0 ~ 9
 
 通过 factor 支持括号
 expr = expr + term | expr - term | term
 term = term * factor | term / factor | term % factor | factor
 factor = num | '(' expr ')'
 num = + | - digit
 digit = 0 ~ 9
 */
static int num(slm_expr *slm_expr) {
    
    int isMinus = 0;
    if (slm_expr->token.type == SLM_EXPRESSION_TOKEN_SUB_OR_MINUS) {
        isMinus = 1;
        next(slm_expr);
    }
    if (slm_expr->token.type != SLM_EXPRESSION_TOKEN_DIGITS) {
        // TODO: throw error
    }
    
    int value = digit(slm_expr);

    
    if (isMinus) {
        return value * -1;
    }
    return value;
}

static int digit(slm_expr *slm_expr) {
    int value = slm_expr->token.value;
    next(slm_expr);
    return value;
}

/**
 expr = expr + term | expr - term | term
 =>
 expr = term expr1
 expr1 = + term | - term | null
 */
int expr(slm_expr *sml_expr) {
    int termVal = term(sml_expr);
    return expr1(termVal, sml_expr);
}


int expr1(int lvalue, slm_expr *sml_expr) {
    if (sml_expr->token.type == SLM_EXPRESSION_TOKEN_ADD) {
        next(sml_expr);
        int termVal = term(sml_expr);
        return expr1(lvalue + termVal, sml_expr);
    } else if (sml_expr->token.type == SLM_EXPRESSION_TOKEN_SUB_OR_MINUS) {
        next(sml_expr);
        int termVal = term(sml_expr);
        return expr1(lvalue - termVal, sml_expr);
    }
    return lvalue;
}

/**
 term = term * factor | term * factor | term % factor | factor
 =>
 term = factor term1
 term1 = * factor term1 | / factor term1 | % factor term1 | null
 */
int term(slm_expr *slm_expr) {
    int factorVal = factor(slm_expr);
    return term1(factorVal, slm_expr);
}

static int term1(int lvalue, slm_expr *slm_expr) {
    
    if (slm_expr->token.type == SLM_EXPRESSION_TOKEN_MUL) {
        next(slm_expr);
        int factorValue = factor(slm_expr);
        return term1(lvalue * factorValue, slm_expr);
    } else if (slm_expr->token.type == SLM_EXPRESSION_TOKEN_DIV) {
        next(slm_expr);
        int factorValue = factor(slm_expr);
        return term1(lvalue / factorValue, slm_expr);
    } else if (slm_expr->token.type == SLM_EXPRESSION_TOKEN_MOD) {
        next(slm_expr);
        int factorValue = factor(slm_expr);
        return term1(lvalue % factorValue, slm_expr);
    }
    return lvalue;
}

/**
 factor = num | '(' expr ')'
 */
static int factor(slm_expr *slm_expr) {
    if (slm_expr->token.type == SLM_EXPRESSION_TOKEN_OPEN) {
        next(slm_expr);
        int value = expr(slm_expr);
        next(slm_expr);
        return value;
    }
    return num(slm_expr);
}

int slm_evalC(const char *expStr, int *errType)
{
    slm_expr e;
    e.exprStr = expStr;
    e.errType = SLM_EXPRESSION_ERROR_TYPE_NONE;
    next(&e);
    int result = expr(&e);
    if (e.errType == 0 && *e.exprStr != 0) {
        e.errType = SLM_EXPRESSION_ERROR_TYPE_EXPECT_END;
        result = 0;
    }
    if (errType) {
        *errType = e.errType;
    }
    return result;
}
