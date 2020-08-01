//
//  SimpleExpressionC.c
//  SimpleExpressionC
//
//  Created by Liang on 2020/8/1.
//  Copyright © 2020 Liang. All rights reserved.
//

/**
 简单加减法
 expr = expr + num | expr - num | null
  转成右递归：
     expr = num expr1
     expr1 = [+,-] num expr | null
 */
#include "AS.h"

int expr1(int lvalue, const char *expStr);

/// num: '0' | '1' | '2' | '3' | '4' | '5' | '6' | '7' | '8' | '9'
int number(const char *expStr) {
    return *expStr - '0';
}

/// expr = expr + num | expr - num | null
/// 转成右递归：
///     expr = num expr1
///     expr1 = [+,-] num expr | null
int expr(const char *expStr) {
    int res = number(expStr++);
    return expr1(res, expStr);
}

/// expr1 = + num expr1
///       | - num expr1
///       | null
int expr1(int lvalue, const char *expStr) {
    if (*expStr == '+') {
        // eat character +
        expStr++;
        // + num expr1
        int num = number(expStr++);
        return expr1(lvalue + num, expStr);
    } else if (*expStr == '-') {
        // eat character -
        expStr++;
        int num = number(expStr++);
        return expr1(lvalue - num, expStr);
    }
    return lvalue;
}

int slm_eval(const char *expStr)
{
    return expr(expStr);
}
