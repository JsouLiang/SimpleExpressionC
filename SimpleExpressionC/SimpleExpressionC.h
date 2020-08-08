//
//  SimpleExpressionC.h
//  SimpleExpressionC
//
//  Created by Liang on 2020/8/6.
//  Copyright © 2020 Liang. All rights reserved.
//

#ifndef SimpleExpressionC_h
#define SimpleExpressionC_h

#include <stdio.h>
enum {
    SLM_EXPRESSION_ERROR_TYPE_NONE = 0,
    SLM_EXPRESSION_ERROR_TYPE_EXPECT_DIGIT,
    SLM_EXPRESSION_ERROR_TYPE_DIVISION_BY_ZERO,
    SLM_EXPRESSION_ERROR_TYPE_REMAINDER_BY_ZERO,
    SLM_EXPRESSION_ERROR_TYPE_EXPECT_CLOSE_PARENTHESIS,
    SLM_EXPRESSION_ERROR_TYPE_EXPECT_END,
    SLM_EXPRESSION_ERROR_UNKNOW_TOKEN
};

int slm_evalC(const char *expStr, int *errType);

#endif /* SimpleExpressionC_h */
