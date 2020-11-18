//
//  main.cpp
//  tinygrammar
//
//  Created by tangles on 6/8/16.
//  Copyright © 2016 visgraph. All rights reserved.
//

#include <iostream>
#include "expansion_manager.h"
#include "svg.h"
string grammar_filename;

int main(int argc, const char * argv[]) {
    int X;
    cin >> X;
    switch (X)
    {
    case 1:
        grammar_filename = "grammars/one.json";
        break;

    case 2:
        grammar_filename = "grammars/two.json";
        break;
    
    case 3:
        grammar_filename = "grammars/three.json";
        break;
    
    default:
        break;
    }
    auto em = make_history(0);
    expand_init(em);
    save_svg(em, {600,600}, {300, 300}, {1.0, 1.0});

    while (expand(em)){
        save_svg(em, {600,600}, {300, 300}, {1.0, 1.0});
        printf("...");
    };
    save_svg(em, {600,600}, {300, 300}, {1.0, 1.0});
}
