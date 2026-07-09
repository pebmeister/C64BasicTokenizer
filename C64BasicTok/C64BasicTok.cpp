// C64BasicTok.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <fstream>
#include <vector>
#include <memory>
#include <string>
#include <cstdint>
#include <unordered_map>

struct LineOutput 
{
    uint16_t next;
    uint16_t lineNumber;
    std::vector<uint8_t> bytes;
};

    // Updated struct to allow for branching (Tree structure)
    struct ParseNode {
        char ch;
        int token;
        std::vector<std::shared_ptr<ParseNode>> child;

        ParseNode(char ch) : ch(ch), token(0) {}
        ParseNode(char ch, int token) : ch(ch), token(token) {}
        ParseNode(char ch, int token, std::vector<std::shared_ptr<ParseNode>> child) : ch(ch), token(token), child(child) {}
    };

static const std::unordered_map<std::string, uint8_t> BasicKeywordToToken{
    {"end",        0x80},
    {"for",        0x81},
    {"next",       0x82},
    {"data",       0x83},
    {"input#",     0x84},
    {"input",      0x85},
    {"dim",        0x86},
    {"read",       0x87},
    {"let",        0x88
    {"goto",       0x89},
    {"run",        0x8A},
    {"if",         0x8B},
    {"restore",    0x8C},
    {"gosub",      0x8D},
    {"return",     0x8E},
    {"rem",        0x8F},
    {"stop",       0x90},
    {"on",         0x91},
    {"wait",       0x92},
    {"load",       0x93},
    {"save",       0x94},
    {"verify",     0x95},
    {"def",        0x96},
    {"poke",       0x97},
    {"print#",     0x98},
    {"print",      0x99},
    {"cont",       0x9A},
    {"list",       0x9B},
    {"clr",        0x9C},
    {"cmd",        0x9D},
    {"sys",        0x9E},
    {"open",       0x9F},
    {"close",      0xA0},
    {"get",        0xA1},
    {"new",        0xA2},

    // Operators
    {"tab(",       0xA3},
    {"to",         0xA4},
    {"fn",         0xA5},
    {"spc(",       0xA6},
    {"then",       0xA7},
    {"not",        0xA8},
    {"step",       0xA9},

    // Math functions
    {"+",          0xAA},
    {"-",          0xAB},
    {"*",          0xAC},
    {"/",          0xAD},
    {"^",          0xAE},
    {"and",        0xAF},
    {"or",         0xB0},
    {">",          0xB1},
    {"=",          0xB2},
    {"<",          0xB3},
    {"sgn",        0xB4},
    {"int",        0xB5},
    {"abs",        0xB6},
    {"usr",        0xB7},
    {"fre",        0xB8},
    {"pos",        0xB9},
    {"sqr",        0xBA},
    {"rnd",        0xBB},
    {"log",        0xBC},
    {"exp",        0xBD},
    {"cos",        0xBE},
    {"sin",        0xBF},
    {"tan",        0xC0},
    {"atn",        0xC1},
    {"peek",       0xC2},
    {"len",        0xC3},
    {"str$",       0xC4},
    {"val",        0xC5},
    {"asc",        0xC6},
    {"chr$",       0xC7},
    {"left$",      0xC8},
    {"right$",     0xC9},
    {"mid$",       0xCA}
};


// Reverse dictionary
static std::unordered_map<uint8_t, std::string> TokenToBasicKeyword = [] {
    std::unordered_map<uint8_t, std::string> rev;
    for (auto& p : BasicKeywordToToken)
        rev[p.second] = p.first;
    return rev;
    }();

// === Generated Initializer List ===
std::shared_ptr<ParseNode> root = 
std::make_shared<ParseNode>(
  0, 0,
  std::vector<std::shared_ptr<ParseNode>>{
        std::make_shared<ParseNode>(
          '*', 172,
          std::vector<std::shared_ptr<ParseNode>>{}
        ),
        std::make_shared<ParseNode>(
          '+', 170,
          std::vector<std::shared_ptr<ParseNode>>{}
        ),
        std::make_shared<ParseNode>(
          '-', 171,
          std::vector<std::shared_ptr<ParseNode>>{}
        ),
        std::make_shared<ParseNode>(
          '/', 173,
          std::vector<std::shared_ptr<ParseNode>>{}
        ),
        std::make_shared<ParseNode>(
          '<', 179,
          std::vector<std::shared_ptr<ParseNode>>{}
        ),
        std::make_shared<ParseNode>(
          '=', 178,
          std::vector<std::shared_ptr<ParseNode>>{}
        ),
        std::make_shared<ParseNode>(
          '>', 177,
          std::vector<std::shared_ptr<ParseNode>>{}
        ),
        std::make_shared<ParseNode>(
          '^', 174,
          std::vector<std::shared_ptr<ParseNode>>{}
        ),
        std::make_shared<ParseNode>(
          'a', 0,
          std::vector<std::shared_ptr<ParseNode>>{
                std::make_shared<ParseNode>(
                  'b', 0,
                  std::vector<std::shared_ptr<ParseNode>>{
                        std::make_shared<ParseNode>(
                          's', 182,
                          std::vector<std::shared_ptr<ParseNode>>{}
                        )
                  }
                ),
                std::make_shared<ParseNode>(
                  'n', 0,
                  std::vector<std::shared_ptr<ParseNode>>{
                        std::make_shared<ParseNode>(
                          'd', 175,
                          std::vector<std::shared_ptr<ParseNode>>{}
                        )
                  }
                ),
                std::make_shared<ParseNode>(
                  's', 0,
                  std::vector<std::shared_ptr<ParseNode>>{
                        std::make_shared<ParseNode>(
                          'c', 198,
                          std::vector<std::shared_ptr<ParseNode>>{}
                        )
                  }
                ),
                std::make_shared<ParseNode>(
                  't', 0,
                  std::vector<std::shared_ptr<ParseNode>>{
                        std::make_shared<ParseNode>(
                          'n', 193,
                          std::vector<std::shared_ptr<ParseNode>>{}
                        )
                  }
                )
          }
        ),
        std::make_shared<ParseNode>(
          'c', 0,
          std::vector<std::shared_ptr<ParseNode>>{
                std::make_shared<ParseNode>(
                  'h', 0,
                  std::vector<std::shared_ptr<ParseNode>>{
                        std::make_shared<ParseNode>(
                          'r', 0,
                          std::vector<std::shared_ptr<ParseNode>>{
                                std::make_shared<ParseNode>(
                                  '$', 199,
                                  std::vector<std::shared_ptr<ParseNode>>{}
                                )
                          }
                        )
                  }
                ),
                std::make_shared<ParseNode>(
                  'l', 0,
                  std::vector<std::shared_ptr<ParseNode>>{
                        std::make_shared<ParseNode>(
                          'o', 0,
                          std::vector<std::shared_ptr<ParseNode>>{
                                std::make_shared<ParseNode>(
                                  's', 0,
                                  std::vector<std::shared_ptr<ParseNode>>{
                                        std::make_shared<ParseNode>(
                                          'e', 160,
                                          std::vector<std::shared_ptr<ParseNode>>{}
                                        )
                                  }
                                )
                          }
                        ),
                        std::make_shared<ParseNode>(
                          'r', 156,
                          std::vector<std::shared_ptr<ParseNode>>{}
                        )
                  }
                ),
                std::make_shared<ParseNode>(
                  'm', 0,
                  std::vector<std::shared_ptr<ParseNode>>{
                        std::make_shared<ParseNode>(
                          'd', 157,
                          std::vector<std::shared_ptr<ParseNode>>{}
                        )
                  }
                ),
                std::make_shared<ParseNode>(
                  'o', 0,
                  std::vector<std::shared_ptr<ParseNode>>{
                        std::make_shared<ParseNode>(
                          'n', 0,
                          std::vector<std::shared_ptr<ParseNode>>{
                                std::make_shared<ParseNode>(
                                  't', 154,
                                  std::vector<std::shared_ptr<ParseNode>>{}
                                )
                          }
                        ),
                        std::make_shared<ParseNode>(
                          's', 190,
                          std::vector<std::shared_ptr<ParseNode>>{}
                        )
                  }
                )
          }
        ),
        std::make_shared<ParseNode>(
          'd', 0,
          std::vector<std::shared_ptr<ParseNode>>{
                std::make_shared<ParseNode>(
                  'a', 0,
                  std::vector<std::shared_ptr<ParseNode>>{
                        std::make_shared<ParseNode>(
                         't', 0,
                          std::vector<std::shared_ptr<ParseNode>>{
                                std::make_shared<ParseNode>(
                                  'a', 131,
                                  std::vector<std::shared_ptr<ParseNode>>{}
                                )
                          }
                        )
                  }
                ),
                std::make_shared<ParseNode>(
                  'e', 0,
                  std::vector<std::shared_ptr<ParseNode>>{
                        std::make_shared<ParseNode>(
                          'f', 150,
                          std::vector<std::shared_ptr<ParseNode>>{}
                        )
                  }
                ),
                std::make_shared<ParseNode>(
                  'i', 0,
                  std::vector<std::shared_ptr<ParseNode>>{
                        std::make_shared<ParseNode>(
                          'm', 134,
                          std::vector<std::shared_ptr<ParseNode>>{}
                        )
                  }
                )
          }
        ),
        std::make_shared<ParseNode>(
          'e', 0,
          std::vector<std::shared_ptr<ParseNode>>{
                std::make_shared<ParseNode>(
                  'n', 0,
                  std::vector<std::shared_ptr<ParseNode>>{
                        std::make_shared<ParseNode>(
                          'd', 128,
                          std::vector<std::shared_ptr<ParseNode>>{}
                        )
                  }
                ),
                std::make_shared<ParseNode>(
                  'x', 0,
                  std::vector<std::shared_ptr<ParseNode>>{
                        std::make_shared<ParseNode>(
                          'p', 189,
                          std::vector<std::shared_ptr<ParseNode>>{}
                        )
                  }
                )
          }
        ),
        std::make_shared<ParseNode>(
          'f', 0,
          std::vector<std::shared_ptr<ParseNode>>{
                std::make_shared<ParseNode>(
                  'n', 165,
                  std::vector<std::shared_ptr<ParseNode>>{}
                ),
                std::make_shared<ParseNode>(
                  'o', 0,
                  std::vector<std::shared_ptr<ParseNode>>{
                        std::make_shared<ParseNode>(
                          'r', 129,
                          std::vector<std::shared_ptr<ParseNode>>{}
                        )
                  }
                ),
                std::make_shared<ParseNode>(
                  'r', 0,
                  std::vector<std::shared_ptr<ParseNode>>{
                        std::make_shared<ParseNode>(
                          'e', 184,
                          std::vector<std::shared_ptr<ParseNode>>{}
                        )
                  }
                )
          }
        ),
        std::make_shared<ParseNode>(
          'g', 0,
          std::vector<std::shared_ptr<ParseNode>>{
                std::make_shared<ParseNode>(
                  'e', 0,
                  std::vector<std::shared_ptr<ParseNode>>{
                        std::make_shared<ParseNode>(
                          't', 161,
                          std::vector<std::shared_ptr<ParseNode>>{}
                        )
                  }
                ),
                std::make_shared<ParseNode>(
                  'o', 0,
                  std::vector<std::shared_ptr<ParseNode>>{
                        std::make_shared<ParseNode>(
                          's', 0,
                          std::vector<std::shared_ptr<ParseNode>>{
                                std::make_shared<ParseNode>(
                                  'u', 0,
                                  std::vector<std::shared_ptr<ParseNode>>{
                                        std::make_shared<ParseNode>(
                                          'b', 141,
                                          std::vector<std::shared_ptr<ParseNode>>{}
                                        )
                                  }
                                )
                          }
                        ),
                        std::make_shared<ParseNode>(
                          't', 0,
                          std::vector<std::shared_ptr<ParseNode>>{
                                std::make_shared<ParseNode>(
                                  'o', 137,
                                  std::vector<std::shared_ptr<ParseNode>>{}
                                )
                          }
                        )
                  }
                )
          }
        ),
        std::make_shared<ParseNode>(
          'i', 0,
          std::vector<std::shared_ptr<ParseNode>>{
                std::make_shared<ParseNode>(
                  'f', 139,
                  std::vector<std::shared_ptr<ParseNode>>{}
                ),
                std::make_shared<ParseNode>(
                  'n', 0,
                  std::vector<std::shared_ptr<ParseNode>>{
                        std::make_shared<ParseNode>(
                          'p', 0,
                          std::vector<std::shared_ptr<ParseNode>>{
                                std::make_shared<ParseNode>(
                                  'u', 0,
                                  std::vector<std::shared_ptr<ParseNode>>{
                                        std::make_shared<ParseNode>(
                                          't', 133,
                                          std::vector<std::shared_ptr<ParseNode>>{
                                                std::make_shared<ParseNode>(
                                                  '#', 132,
                                                  std::vector<std::shared_ptr<ParseNode>>{}
                                                )
                                          }
                                        )
                                  }
                                )
                          }
                        ),
                        std::make_shared<ParseNode>(
                          't', 181,
                          std::vector<std::shared_ptr<ParseNode>>{}
                        )
                  }
                )
          }
        ),
        std::make_shared<ParseNode>(
          'l', 0,
          std::vector<std::shared_ptr<ParseNode>>{
                std::make_shared<ParseNode>(
                  'e', 0,
                  std::vector<std::shared_ptr<ParseNode>>{
                        std::make_shared<ParseNode>(
                          'f', 0,
                          std::vector<std::shared_ptr<ParseNode>>{
                                std::make_shared<ParseNode>(
                                  't', 0,
                                  std::vector<std::shared_ptr<ParseNode>>{
                                        std::make_shared<ParseNode>(
                                          '$', 200,
                                          std::vector<std::shared_ptr<ParseNode>>{}
                                        )
                                  }
                                )
                          }
                        ),
                        std::make_shared<ParseNode>(
                          'n', 195,
                          std::vector<std::shared_ptr<ParseNode>>{}
                        ),
                        std::make_shared<ParseNode>(
                          't', 136,
                          std::vector<std::shared_ptr<ParseNode>>{}
                        )
                  }
                ),
                std::make_shared<ParseNode>(
                  'i', 0,
                  std::vector<std::shared_ptr<ParseNode>>{
                        std::make_shared<ParseNode>(
                          's', 0,
                          std::vector<std::shared_ptr<ParseNode>>{
                                std::make_shared<ParseNode>(
                                  't', 155,
                                  std::vector<std::shared_ptr<ParseNode>>{}
                                )
                          }
                        )
                  }
                ),
                std::make_shared<ParseNode>(
                  'o', 0,
                  std::vector<std::shared_ptr<ParseNode>>{
                        std::make_shared<ParseNode>(
                          'a', 0,
                          std::vector<std::shared_ptr<ParseNode>>{
                                std::make_shared<ParseNode>(
                                  'd', 147,
                                  std::vector<std::shared_ptr<ParseNode>>{}
                                )
                          }
                        ),
                        std::make_shared<ParseNode>(
                          'g', 188,
                          std::vector<std::shared_ptr<ParseNode>>{}
                        )
                  }
                )
          }
        ),
        std::make_shared<ParseNode>(
          'm', 0,
          std::vector<std::shared_ptr<ParseNode>>{
                std::make_shared<ParseNode>(
                  'i', 0,
                  std::vector<std::shared_ptr<ParseNode>>{
                        std::make_shared<ParseNode>(
                          'd', 0,
                          std::vector<std::shared_ptr<ParseNode>>{
                                std::make_shared<ParseNode>(
                                  '$', 202,
                                  std::vector<std::shared_ptr<ParseNode>>{}
                                )
                          }
                        )
                  }
                )
          }
        ),
        std::make_shared<ParseNode>(
          'n', 0,
          std::vector<std::shared_ptr<ParseNode>>{
                std::make_shared<ParseNode>(
                  'e', 0,
                  std::vector<std::shared_ptr<ParseNode>>{
                        std::make_shared<ParseNode>(
                          'w', 162,
                          std::vector<std::shared_ptr<ParseNode>>{}
                        ),
                        std::make_shared<ParseNode>(
                          'x', 0,
                          std::vector<std::shared_ptr<ParseNode>>{
                                std::make_shared<ParseNode>(
                                  't', 130,
                                  std::vector<std::shared_ptr<ParseNode>>{}
                                )
                          }
                        )
                  }
                ),
                std::make_shared<ParseNode>(
                  'o', 0,
                  std::vector<std::shared_ptr<ParseNode>>{
                        std::make_shared<ParseNode>(
                          't', 168,
                          std::vector<std::shared_ptr<ParseNode>>{}
                        )
                  }
                )
          }
        ),
        std::make_shared<ParseNode>(
          'o', 0,
          std::vector<std::shared_ptr<ParseNode>>{
                std::make_shared<ParseNode>(
                  'n', 145,
                  std::vector<std::shared_ptr<ParseNode>>{}
                ),
                std::make_shared<ParseNode>(
                  'p', 0,
                  std::vector<std::shared_ptr<ParseNode>>{
                        std::make_shared<ParseNode>(
                          'e', 0,
                          std::vector<std::shared_ptr<ParseNode>>{
                                std::make_shared<ParseNode>(
                                  'n', 159,
                                  std::vector<std::shared_ptr<ParseNode>>{}
                                )
                          }
                        )
                  }
                ),
                std::make_shared<ParseNode>(
                  'r', 176,
                  std::vector<std::shared_ptr<ParseNode>>{}
                )
          }
        ),
        std::make_shared<ParseNode>(
          'p', 0,
          std::vector<std::shared_ptr<ParseNode>>{
                std::make_shared<ParseNode>(
                  'e', 0,
                  std::vector<std::shared_ptr<ParseNode>>{
                        std::make_shared<ParseNode>(
                          'e', 0,
                          std::vector<std::shared_ptr<ParseNode>>{
                                std::make_shared<ParseNode>(
                                  'k', 194,
                                  std::vector<std::shared_ptr<ParseNode>>{}
                                )
                          }
                        )
                  }
                ),
                std::make_shared<ParseNode>(
                  'o', 0,
                  std::vector<std::shared_ptr<ParseNode>>{
                        std::make_shared<ParseNode>(
                          'k', 0,
                          std::vector<std::shared_ptr<ParseNode>>{
                                std::make_shared<ParseNode>(
                                  'e', 151,
                                  std::vector<std::shared_ptr<ParseNode>>{}
                                )
                          }
                        ),
                        std::make_shared<ParseNode>(
                          's', 185,
                          std::vector<std::shared_ptr<ParseNode>>{}
                        )
                  }
                ),
                std::make_shared<ParseNode>(
                  'r', 0,
                  std::vector<std::shared_ptr<ParseNode>>{
                        std::make_shared<ParseNode>(
                          'i', 0,
                          std::vector<std::shared_ptr<ParseNode>>{
                                std::make_shared<ParseNode>(
                                  'n', 0,
                                  std::vector<std::shared_ptr<ParseNode>>{
                                        std::make_shared<ParseNode>(
                                          't', 153,
                                          std::vector<std::shared_ptr<ParseNode>>{
                                                std::make_shared<ParseNode>(
                                                  '#', 152,
                                                  std::vector<std::shared_ptr<ParseNode>>{}
                                                )
                                          }
                                        )
                                  }
                                )
                          }
                        )
                  }
                )
          }
        ),
        std::make_shared<ParseNode>(
          'r', 0,
          std::vector<std::shared_ptr<ParseNode>>{
                std::make_shared<ParseNode>(
                  'e', 0,
                  std::vector<std::shared_ptr<ParseNode>>{
                        std::make_shared<ParseNode>(
                          'a', 0,
                          std::vector<std::shared_ptr<ParseNode>>{
                                std::make_shared<ParseNode>(
                                  'd', 135,
                                  std::vector<std::shared_ptr<ParseNode>>{}
                                )
                          }
                        ),
                        std::make_shared<ParseNode>(
                          'm', 143,
                          std::vector<std::shared_ptr<ParseNode>>{}
                        ),
                        std::make_shared<ParseNode>(
                          's', 0,
                          std::vector<std::shared_ptr<ParseNode>>{
                                std::make_shared<ParseNode>(
                                  't', 0,
                                  std::vector<std::shared_ptr<ParseNode>>{
                                        std::make_shared<ParseNode>(
                                          'o', 0,
                                          std::vector<std::shared_ptr<ParseNode>>{
                                                std::make_shared<ParseNode>(
                                                  'r', 0,
                                                  std::vector<std::shared_ptr<ParseNode>>{
                                                        std::make_shared<ParseNode>(
                                                          'e', 140,
                                                          std::vector<std::shared_ptr<ParseNode>>{}
                                                        )
                                                  }
                                                )
                                          }
                                        )
                                  }
                                )
                          }
                        ),
                        std::make_shared<ParseNode>(
                          't', 0,
                          std::vector<std::shared_ptr<ParseNode>>{
                                std::make_shared<ParseNode>(
                                  'u', 0,
                                  std::vector<std::shared_ptr<ParseNode>>{
                                        std::make_shared<ParseNode>(
                                          'r', 0,
                                          std::vector<std::shared_ptr<ParseNode>>{
                                                std::make_shared<ParseNode>(
                                                  'n', 142,
                                                  std::vector<std::shared_ptr<ParseNode>>{}
                                                )
                                          }
                                        )
                                  }
                                )
                          }
                        )
                  }
                ),
                std::make_shared<ParseNode>(
                  'i', 0,
                  std::vector<std::shared_ptr<ParseNode>>{
                        std::make_shared<ParseNode>(
                          'g', 0,
                          std::vector<std::shared_ptr<ParseNode>>{
                                std::make_shared<ParseNode>(
                                  'h', 0,
                                  std::vector<std::shared_ptr<ParseNode>>{
                                        std::make_shared<ParseNode>(
                                          't', 0,
                                          std::vector<std::shared_ptr<ParseNode>>{
                                                std::make_shared<ParseNode>(
                                                  '$', 201,
                                                  std::vector<std::shared_ptr<ParseNode>>{}
                                                )
                                          }
                                        )
                                  }
                                )
                          }
                        )
                  }
                ),
                std::make_shared<ParseNode>(
                  'n', 0,
                  std::vector<std::shared_ptr<ParseNode>>{
                        std::make_shared<ParseNode>(
                          'd', 187,
                          std::vector<std::shared_ptr<ParseNode>>{}
                        )
                  }
                ),
                std::make_shared<ParseNode>(
                  'u', 0,
                  std::vector<std::shared_ptr<ParseNode>>{
                        std::make_shared<ParseNode>(
                          'n', 138,
                          std::vector<std::shared_ptr<ParseNode>>{}
                        )
                  }
                )
          }
        ),
        std::make_shared<ParseNode>(
          's', 0,
          std::vector<std::shared_ptr<ParseNode>>{
                std::make_shared<ParseNode>(
                  'a', 0,
                  std::vector<std::shared_ptr<ParseNode>>{
                        std::make_shared<ParseNode>(
                          'v', 0,
                          std::vector<std::shared_ptr<ParseNode>>{
                                std::make_shared<ParseNode>(
                                  'e', 148,
                                  std::vector<std::shared_ptr<ParseNode>>{}
                                )
                          }
                        )
                  }
                ),
                std::make_shared<ParseNode>(
                  'g', 0,
                  std::vector<std::shared_ptr<ParseNode>>{
                        std::make_shared<ParseNode>(
                          'n', 180,
                          std::vector<std::shared_ptr<ParseNode>>{}
                        )
                  }
                ),
                std::make_shared<ParseNode>(
                  'i', 0,
                  std::vector<std::shared_ptr<ParseNode>>{
                        std::make_shared<ParseNode>(
                          'n', 191,
                          std::vector<std::shared_ptr<ParseNode>>{}
                        )
                  }
                ),
                std::make_shared<ParseNode>(
                  'p', 0,
                  std::vector<std::shared_ptr<ParseNode>>{
                        std::make_shared<ParseNode>(
                          'c', 0,
                          std::vector<std::shared_ptr<ParseNode>>{
                                std::make_shared<ParseNode>(
                                  '(', 166,
                                  std::vector<std::shared_ptr<ParseNode>>{}
                                )
                          }
                        )
                  }
                ),
                std::make_shared<ParseNode>(
                  'q', 0,
                  std::vector<std::shared_ptr<ParseNode>>{
                        std::make_shared<ParseNode>(
                          'r', 186,
                          std::vector<std::shared_ptr<ParseNode>>{}
                        )
                  }
                ),
                std::make_shared<ParseNode>(
                  't', 0,
                  std::vector<std::shared_ptr<ParseNode>>{
                        std::make_shared<ParseNode>(
                          'e', 0,
                          std::vector<std::shared_ptr<ParseNode>>{
                                std::make_shared<ParseNode>(
                                  'p', 169,
                                  std::vector<std::shared_ptr<ParseNode>>{}
                                )
                          }
                        ),
                        std::make_shared<ParseNode>(
                          'o', 0,
                          std::vector<std::shared_ptr<ParseNode>>{
                                std::make_shared<ParseNode>(
                                  'p', 144,
                                  std::vector<std::shared_ptr<ParseNode>>{}
                                )
                          }
                        ),
                        std::make_shared<ParseNode>(
                          'r', 0,
                          std::vector<std::shared_ptr<ParseNode>>{
                                std::make_shared<ParseNode>(
                                  '$', 196,
                                  std::vector<std::shared_ptr<ParseNode>>{}
                                )
                          }
                        )
                  }
                ),
                std::make_shared<ParseNode>(
                  'y', 0,
                  std::vector<std::shared_ptr<ParseNode>>{
                        std::make_shared<ParseNode>(
                          's', 158,
                          std::vector<std::shared_ptr<ParseNode>>{}
                        )
                  }
                )
          }
        ),
        std::make_shared<ParseNode>(
          't', 0,
          std::vector<std::shared_ptr<ParseNode>>{
                std::make_shared<ParseNode>(
                  'a', 0,
                  std::vector<std::shared_ptr<ParseNode>>{
                        std::make_shared<ParseNode>(
                          'b', 0,
                          std::vector<std::shared_ptr<ParseNode>>{
                                std::make_shared<ParseNode>(
                                  '(', 163,
                                  std::vector<std::shared_ptr<ParseNode>>{}
                                )
                          }
                        ),
                        std::make_shared<ParseNode>(
                          'n', 192,
                          std::vector<std::shared_ptr<ParseNode>>{}
                        )
                  }
                ),
                std::make_shared<ParseNode>(
                  'h', 0,
                  std::vector<std::shared_ptr<ParseNode>>{
                        std::make_shared<ParseNode>(
                          'e', 0,
                          std::vector<std::shared_ptr<ParseNode>>{
                                std::make_shared<ParseNode>(
                                  'n', 167,
                                  std::vector<std::shared_ptr<ParseNode>>{}
                                )
                          }
                        )
                  }
                ),
                std::make_shared<ParseNode>(
                  'o', 164,
                  std::vector<std::shared_ptr<ParseNode>>{}
                )
          }
        ),
        std::make_shared<ParseNode>(
          'u', 0,
          std::vector<std::shared_ptr<ParseNode>>{
                std::make_shared<ParseNode>(
                  's', 0,
                  std::vector<std::shared_ptr<ParseNode>>{
                        std::make_shared<ParseNode>(
                          'r', 183,
                          std::vector<std::shared_ptr<ParseNode>>{}
                        )
                  }
                )
          }
        ),
        std::make_shared<ParseNode>(
          'v', 0,
          std::vector<std::shared_ptr<ParseNode>>{
                std::make_shared<ParseNode>(
                  'a', 0,
                  std::vector<std::shared_ptr<ParseNode>>{
                        std::make_shared<ParseNode>(
                          'l', 197,
                          std::vector<std::shared_ptr<ParseNode>>{}
                        )
                  }
                ),
                std::make_shared<ParseNode>(
                  'e', 0,
                  std::vector<std::shared_ptr<ParseNode>>{
                        std::make_shared<ParseNode>(
                          'r', 0,
                          std::vector<std::shared_ptr<ParseNode>>{
                                std::make_shared<ParseNode>(
                                  'i', 0,
                                  std::vector<std::shared_ptr<ParseNode>>{
                                        std::make_shared<ParseNode>(
                                          'f', 0,
                                          std::vector<std::shared_ptr<ParseNode>>{
                                                std::make_shared<ParseNode>(
                                                  'y', 149,
                                                  std::vector<std::shared_ptr<ParseNode>>{}
                                                )
                                          }
                                        )
                                  }
                                )
                          }
                        )
                  }
                )
          }
        ),
        std::make_shared<ParseNode>(
          'w', 0,
          std::vector<std::shared_ptr<ParseNode>>{
                std::make_shared<ParseNode>(
                  'a', 0,
                  std::vector<std::shared_ptr<ParseNode>>{
                        std::make_shared<ParseNode>(
                          'i', 0,
                          std::vector<std::shared_ptr<ParseNode>>{
                                std::make_shared<ParseNode>(
                                  't', 146,
                                  std::vector<std::shared_ptr<ParseNode>>{}
                                )
                          }
                        )
                  }
                )
          }
        )
  }
);


// Result structure to return from our matching function
struct MatchResult {
    int token_id;
    size_t length;
};

// Finds the longest matching prefix in the Trie starting at index 'start_pos'
static MatchResult match_longest_token(std::shared_ptr<ParseNode> root, const std::string& text, size_t start_pos) {
    if (!root || start_pos >= text.length()) {
        return { 0, 0 };
    }

    std::shared_ptr<ParseNode> current = root;
    size_t current_pos = start_pos;

    // Track the best valid token state we've passed so far
    int last_valid_token = 0;
    size_t last_valid_length = 0;

    while (current_pos < text.length()) {
        char next_char = text[current_pos];
        std::shared_ptr<ParseNode> next_node = nullptr;

        // Linear search through the node's children for a character match
        for (const auto& child_node : current->child) {
            if (child_node->ch == next_char) {
                next_node = child_node;
                break;
            }
        }

        // If no matching child edge exists, we can't look further down the tree
        if (!next_node) {
            break;
        }

        // Advance into the matching child node
        current = next_node;
        current_pos++;

        // If this state represents a complete keyword/operator, log it!
        if (current->token != 0) {
            last_valid_token = current->token;
            last_valid_length = current_pos - start_pos;
        }
    }

    // If we found a reserved word/operator, return it
    if (last_valid_token != 0) {
        return { last_valid_token, last_valid_length };
    }

    // Fallback: If no tree path matched a valid token, treat the first char as a literal
    return { 0, 1 };
}

static struct LineOutput TokenizeLine(const int current_address, const std::string& str)
{
    std::string quote = "\"";
    size_t pos = 0;
    LineOutput output;
    
    // get line line lineNumber
    std::string linenum;
    while (pos < str.length() && std::isdigit(str[pos])) {
        linenum += str[pos];
        pos++;
    }
    output.lineNumber = std::stoi(linenum);
    
    while (pos < str.length()) {
        auto result = match_longest_token(root, str, pos);
        std::string_view tok{ str.data() + pos, result.length };
        if (result.token_id != 0) {
            output.bytes.push_back(result.token_id);
        }
        else {
            output.bytes.push_back(tok[0]);
            if (tok == quote) {
                do
                {
                    pos++;
                    output.bytes.push_back(str[pos]);
                } while (str[pos] != quote[0]);
            }
        }
        pos += result.length;
    }
    output.bytes.push_back(0);  // end of line marker
    output.next = current_address + output.bytes.size() + 4;
    return output;
}

static std::string Detokenize(std::vector<uint8_t>tokens)
{
    std::string output;

    for (auto& ch : tokens)
    {
        if (TokenToBasicKeyword.contains(ch))
        {
            output += TokenToBasicKeyword[ch];
        }
        else
        {
            output += ch;
        }
    }   
    return output;
}


std::vector<uint8_t> ProcessFile(std::string filename)
{
    std::vector<uint8_t> output;
    
    // Open the file using an input file stream
    std::ifstream file(filename);

    // Check if the file opened successfully
    if (!file.is_open()) {
        std::cerr << "Error: Could not open the file." << std::endl;
        return output;
    }

    std::string line;
    auto current_address = 0x0801;
    // Read line by line until the end of the file

    while (std::getline(file, line)) {
        auto tokline = TokenizeLine(current_address, line);
        output.push_back(tokline.next &0xFF);
        output.push_back((tokline.next >> 8) & 0xFF);
        output.push_back(tokline.lineNumber & 0xFF);
        output.push_back((tokline.lineNumber >> 8) & 0xFF);
        
        output.insert(output.end(), tokline.bytes.begin(), tokline.bytes.end());
        current_address = tokline.next;
    }
    // mark end of file
    output.push_back(0);
    output.push_back(0);

    // File stream closes automatically when it goes out of scope
    return output;
}

int main(int argc, char* argv[])
{
    // We expect exactly 3 arguments: the program name, input file, and output file
    if (argc != 3)
    {
        std::clog << "Usage: " << argv[0] << " <input_file> <output_file>\n";
        return 1;
    }

    std::string input_path = argv[1];
    std::string output_path = argv[2];

    auto out = ProcessFile(input_path);
    auto detok = Detokenize(out);

//    if (detok != input)
//    {
//        std::cout << "Mismatch detected in file: " << input_path << "\n";
 //       std::cout << "input\n" << input << "\n============\n";
  //      std::cout << "output\n" << detok << "\n============\n";
  //      return 1;
  //  }

    // Open the output file in binary mode to write the raw uint8_t vector
    std::ofstream out_file(output_path, std::ios::binary);
    if (!out_file)
    {
        std::cerr << "Error: Could not open output file " << output_path << "\n";
        return 1;
    }

    // Write the vector data safely by casting the pointer to const char*
    out_file.write(reinterpret_cast<const char*>(out.data()), out.size());

    std::cout << "File processed successfully. Binary data saved to: " << output_path << "\n";
    return 0;
}