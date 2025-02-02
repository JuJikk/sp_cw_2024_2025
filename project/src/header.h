#pragma once

#define MAX_TOKENS      1000
#define MAX_IDENTIFIER  10

enum TypeOfToken {
    StartProgram,
    StartBlock,
    Variable,
    Type,
    EndBlock,
    Input,
    Output,
    If,
    Else,
    Goto,
    For,
    To,
    Downto,
    Do,
    While,
    Continue,
    Exit,
    End,
    Repeat,
    Until,

    Identifier,

    Number,
    Float,

    Assign,
    Add,
    Sub,
    Mul,
    Div,
    Mod,

    Equality,
    NotEquality,
    Greate,
    Less,
    Not,
    And,
    Or,

    LBracket,
    RBracket,

    Semicolon,
    Colon,
    Comma,
    Unknown_
};

struct Token {
    char name[16];      // ім'я лексеми
    int value;          // значення (для констант)
    int line;           // номер рядка
    enum TypeOfToken type;   // тип лексеми
};

struct id {
    char name[16];
    //unsigned int pos;   //for labels
};

enum States {
    Start,      // початковий стан
    Finish,     // фінальний стан
    Letter,     // опрацювання слів (ключові слова та ідентифікаторів)
    Digit,      // опрацювання цифр
    Separator,  // опрацювання роздільників
    Another,    // опрацювання інших символів
    EndOFile,   // кінець файлу
    SComment,   // початок коментаря
    Comment,    // ігнорування коментаря
    MultiCommentStart
};

enum TypeOfNode {
    program_node,
    id_node,
    var_node,
    statement_node,
    input_node,
    output_node,
    add_node,
    sub_node,
    mul_node,
    div_node,
    mod_node,
    number_node,
    assign_node,
    if_node,
    else_node,
    or_node,
    and_node,
    not_node,
    eq_node,
    neq_node,
    gr_node,
    ls_node,
    goto_node,
    label_node,
    for_node,
    to_node,
    downto_node,
    while_node,
    continue_node,
    exit_node,
    repeat_node,
    compound_node,
    empty_node
};

struct astNode {
    enum TypeOfNode type;
    char name[16];
    struct astNode* left;
    struct astNode* right;
};

const char* lexemeTypeName(enum TypeOfToken type);
