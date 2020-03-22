all:
        flex lex_analysis.l
        yacc -d syntax.y
        gcc -g lex.yy.c  y.tab.c main.c -o first

test:
        ./first

test1:
        ./first < input.txt
clear:
        rm first
        rm y.tab.c
        rm y.tab.h
        rm lex.yy.c

testWorking:
        ./first < phase2_tests/Working/Anonymous.asc
        ./first < phase2_tests/Working/Block.asc
        ./first < phase2_tests/Working/Circle.asc
        ./first < phase2_tests/Working/GlobalAndLocal.asc
        ./first < phase2_tests/Working/Grammar.asc
        ./first < phase2_tests/Working/Random.asc
        ./first < phase2_tests/Working/ShadowedNameOffunctions.asc
        ./first < phase2_tests/Working/Simple.asc
        ./first < phase2_tests/Working/Tree.asc

testError:
        ./first < phase2_tests/Errors/Error0.asc
        ./first < phase2_tests/Errors/Error1.asc
        ./first < phase2_tests/Errors/Error2.asc
        ./first < phase2_tests/Errors/Error3.asc
        ./first < phase2_tests/Errors/Error4.asc
        ./first < phase2_tests/Errors/Error5.asc
        ./first < phase2_tests/Errors/Error6.asc
        ./first < phase2_tests/Errors/Error7.asc
        ./first < phase2_tests/Errors/Error8.asc
        ./first < phase2_tests/Errors/Error9.asc
        ./first < phase2_tests/Errors/Error10.asc
        ./first < phase2_tests/Errors/Error11.asc
        ./first < phase2_tests/Errors/Error12.asc
