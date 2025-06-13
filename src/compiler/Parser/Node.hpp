#pragma once
// Namespace a way to group related identifiers
namespace Node {
    struct Expr {
        Token int_lit;

     };
     struct Exit {
        Node::Expr expr;
     };
}; 