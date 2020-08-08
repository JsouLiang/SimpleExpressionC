//
//  main.c
//  SimpleExpressionC
//
//  Created by Liang on 2020/8/1.
//  Copyright © 2020 Liang. All rights reserved.
//

#include <stdio.h>
#include "SimpleExpressionC.h"

void test(const char *expStr, int except) {
    int errorType;
    printf("%s=%d excapt=%d\n", expStr, slm_evalC(expStr, &errorType), except);
}

int main(int argc, const char * argv[]) {
    
    test("1+2", 1+2);
    test("3-2+1", 3-2+1);
    test("2*3", 2*3);
    test("4/2", 4/2);
    test("3+4/2-1", 3+4/2-1);
    test("1*2+3%2", 1*2+3%2);
    test("2*2*2-3", 2*2*2-3);
    test("(2+4)/3", (2+4)/3);
    test("(1+2)*(2+2)", (1+2)*(2+2));
    test("(1+3*2)%3", (1+3*2)%3);
    test("3*-1", 3*-1);
    test("3+-1", 3+-1);
    test("-1+-1+1", -1+-1+1);
    test("12+1", 12+1);
    return 0;
}
