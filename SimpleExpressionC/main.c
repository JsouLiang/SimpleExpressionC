//
//  main.c
//  SimpleExpressionC
//
//  Created by Liang on 2020/8/1.
//  Copyright © 2020 Liang. All rights reserved.
//

#include <stdio.h>

int main(int argc, const char * argv[]) {
    printf("1+2=%d\n", slm_eval("1+2"));
    printf("1-2+3=%d\n", slm_eval("1-2+3"));
    return 0;
}
