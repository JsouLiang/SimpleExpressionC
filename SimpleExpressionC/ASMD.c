//
//  ASMD.c
//  SimpleExpressionC
//
//  Created by Liang on 2020/8/1.
//  Copyright © 2020 Liang. All rights reserved.
//

#include "ASMD.h"
static int expr1(int , const char *);
static int term(const char **);
static int term1(int , const char **);
static void eat(const char **);
/**
 加减乘除：
 expr = expr + term | expr - term | term
 term = term * num | term / num | num
 num = 0 ~ 9
 */
static int num(const char **expStr) {
    int val = **expStr - '0';
    (*expStr)++;
    return val;
}

/**
 expr = expr + term | expr - term | term
 => 右递归
 expr = term expr1
 expr1 = + term expr1 | - term expr1 | null
 */
static int expr(const char *expStr) {
    int termVal = term(&expStr);
    return expr1(termVal, expStr);
}

static int expr1(int lvalue, const char *expStr) {
    if (*expStr == '+') {
        eat(&expStr);
        int value = term(&expStr);
        return expr1(lvalue + value, expStr);
    } else if (*expStr == '-') {
        eat(&expStr);
        int value = term(&expStr);
        return expr1(lvalue - value, expStr);
    } else {
        return lvalue;
    }
}

/**
 term = term * num | term / num | num
 => 右递归
 term = num term1
 term1 = * num term1 | / num term1 | null
 */
static int term(const char **expStr) {
    int value = num(expStr);
    return term1(value, expStr);
}

static int term1(int lvalue, const char **expStr) {
    if (**expStr == '*') {
        // 吃掉 *
        eat(expStr);
        int value = num(expStr);
        return term1(lvalue * value, expStr);
    } else if (**expStr == '/') {
        // 吃掉 /
        eat(expStr);
        int value = num(expStr);
        return term1(lvalue / value, expStr);
    }
    return lvalue;
}

static void eat(const char **expStr) {
    (*expStr)++;
}


int eval(const char *exp) {
    return expr(exp);
}
