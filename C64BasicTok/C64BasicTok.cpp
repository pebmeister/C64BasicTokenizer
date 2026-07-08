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

static const std::unordered_map<std::string, uint8_t> BasicKeywordToToken{
    {"END",        0x80},
    {"FOR",        0x81},
    {"NEXT",       0x82},
    {"DATA",       0x83},
    {"INPUT#",     0x84},
    {"INPUT",      0x85},
    {"DIM",        0x86},
    {"READ",       0x87},
    {"LET",        0x88},
    {"GOTO",       0x89},
    {"RUN",        0x8A},
    {"IF",         0x8B},
    {"RESTORE",    0x8C},
    {"GOSUB",      0x8D},
    {"RETURN",     0x8E},
    {"REM",        0x8F},
    {"STOP",       0x90},
    {"ON",         0x91},
    {"WAIT",       0x92},
    {"LOAD",       0x93},
    {"SAVE",       0x94},
    {"VERIFY",     0x95},
    {"DEF",        0x96},
    {"POKE",       0x97},
    {"PRINT#",     0x98},
    {"PRINT",      0x99},
    {"CONT",       0x9A},
    {"LIST",       0x9B},
    {"CLR",        0x9C},
    {"CMD",        0x9D},
    {"SYS",        0x9E},
    {"OPEN",       0x9F},
    {"CLOSE",      0xA0},
    {"GET",        0xA1},
    {"NEW",        0xA2},

    // Operators
    {"TAB(",       0xA3},
    {"TO",         0xA4},
    {"FN",         0xA5},
    {"SPC(",       0xA6},
    {"THEN",       0xA7},
    {"NOT",        0xA8},
    {"STEP",       0xA9},

    // Math functions
    {"+",          0xAA},
    {"-",          0xAB},
    {"*",          0xAC},
    {"/",          0xAD},
    {"^",          0xAE},
    {"AND",        0xAF},
    {"OR",         0xB0},
    {">",          0xB1},
    {"=",          0xB2},
    {"<",          0xB3},
    {"SGN",        0xB4},
    {"INT",        0xB5},
    {"ABS",        0xB6},
    {"USR",        0xB7},
    {"FRE",        0xB8},
    {"POS",        0xB9},
    {"SQR",        0xBA},
    {"RND",        0xBB},
    {"LOG",        0xBC},
    
    {"EXP",        0xBD},
    {"COS",        0xBE},
    {"SIN",        0xBF},
    {"TAN",        0xC0},
    {"ATN",        0xC1},
    {"PEEK",       0xC2},
    {"LEN",        0xC3},
    {"STR$",       0xC4},
    {"VAL",        0xC5},
    {"ASC",        0xC6},
    {"CHR$",       0xC7},
    {"LEFT$",      0xC8},
    {"RIGHT$",     0xC9},
    {"MID$",       0xCA}
};

// Reverse dictionary
static std::unordered_map<uint8_t, std::string> TokenToBasicKeyword = [] {
    std::unordered_map<uint8_t, std::string> rev;
    for (auto& p : BasicKeywordToToken)
        rev[p.second] = p.first;
    return rev;
    }();

  // Updated struct to allow for branching (Trie structure)
struct ParseNode {
    char ch;
    int token;
    std::vector<std::shared_ptr<ParseNode>> child;

    ParseNode(char ch) : ch(ch), token(0) {}
    ParseNode(char ch, int token) : ch(ch), token(token) {}
    ParseNode(char ch, int token, std::vector<std::shared_ptr<ParseNode>> child) : ch(ch), token(token), child(child) {}
};

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
          'A', 0,
          std::vector<std::shared_ptr<ParseNode>>{
                std::make_shared<ParseNode>(
                  'B', 0,
                  std::vector<std::shared_ptr<ParseNode>>{
                        std::make_shared<ParseNode>(
                          'S', 182,
                          std::vector<std::shared_ptr<ParseNode>>{}
                        )
                  }
                ),
                std::make_shared<ParseNode>(
                  'N', 0,
                  std::vector<std::shared_ptr<ParseNode>>{
                        std::make_shared<ParseNode>(
                          'D', 175,
                          std::vector<std::shared_ptr<ParseNode>>{}
                        )
                  }
                ),
                std::make_shared<ParseNode>(
                  'S', 0,
                  std::vector<std::shared_ptr<ParseNode>>{
                        std::make_shared<ParseNode>(
                          'C', 198,
                          std::vector<std::shared_ptr<ParseNode>>{}
                        )
                  }
                ),
                std::make_shared<ParseNode>(
                  'T', 0,
                  std::vector<std::shared_ptr<ParseNode>>{
                        std::make_shared<ParseNode>(
                          'N', 193,
                          std::vector<std::shared_ptr<ParseNode>>{}
                        )
                  }
                )
          }
        ),
        std::make_shared<ParseNode>(
          'C', 0,
          std::vector<std::shared_ptr<ParseNode>>{
                std::make_shared<ParseNode>(
                  'H', 0,
                  std::vector<std::shared_ptr<ParseNode>>{
                        std::make_shared<ParseNode>(
                          'R', 0,
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
                  'L', 0,
                  std::vector<std::shared_ptr<ParseNode>>{
                        std::make_shared<ParseNode>(
                          'O', 0,
                          std::vector<std::shared_ptr<ParseNode>>{
                                std::make_shared<ParseNode>(
                                  'S', 0,
                                  std::vector<std::shared_ptr<ParseNode>>{
                                        std::make_shared<ParseNode>(
                                          'E', 160,
                                          std::vector<std::shared_ptr<ParseNode>>{}
                                        )
                                  }
                                )
                          }
                        ),
                        std::make_shared<ParseNode>(
                          'R', 156,
                          std::vector<std::shared_ptr<ParseNode>>{}
                        )
                  }
                ),
                std::make_shared<ParseNode>(
                  'M', 0,
                  std::vector<std::shared_ptr<ParseNode>>{
                        std::make_shared<ParseNode>(
                          'D', 157,
                          std::vector<std::shared_ptr<ParseNode>>{}
                        )
                  }
                ),
                std::make_shared<ParseNode>(
                  'O', 0,
                  std::vector<std::shared_ptr<ParseNode>>{
                        std::make_shared<ParseNode>(
                          'N', 0,
                          std::vector<std::shared_ptr<ParseNode>>{
                                std::make_shared<ParseNode>(
                                  'T', 154,
                                  std::vector<std::shared_ptr<ParseNode>>{}
                                )
                          }
                        ),
                        std::make_shared<ParseNode>(
                          'S', 190,
                          std::vector<std::shared_ptr<ParseNode>>{}
                        )
                  }
                )
          }
        ),
        std::make_shared<ParseNode>(
          'D', 0,
          std::vector<std::shared_ptr<ParseNode>>{
                std::make_shared<ParseNode>(
                  'A', 0,
                  std::vector<std::shared_ptr<ParseNode>>{
                        std::make_shared<ParseNode>(
                          'T', 0,
                          std::vector<std::shared_ptr<ParseNode>>{
                                std::make_shared<ParseNode>(
                                  'A', 131,
                                  std::vector<std::shared_ptr<ParseNode>>{}
                                )
                          }
                        )
                  }
                ),
                std::make_shared<ParseNode>(
                  'E', 0,
                  std::vector<std::shared_ptr<ParseNode>>{
                        std::make_shared<ParseNode>(
                          'F', 150,
                          std::vector<std::shared_ptr<ParseNode>>{}
                        )
                  }
                ),
                std::make_shared<ParseNode>(
                  'I', 0,
                  std::vector<std::shared_ptr<ParseNode>>{
                        std::make_shared<ParseNode>(
                          'M', 134,
                          std::vector<std::shared_ptr<ParseNode>>{}
                        )
                  }
                )
          }
        ),
        std::make_shared<ParseNode>(
          'E', 0,
          std::vector<std::shared_ptr<ParseNode>>{
                std::make_shared<ParseNode>(
                  'N', 0,
                  std::vector<std::shared_ptr<ParseNode>>{
                        std::make_shared<ParseNode>(
                          'D', 128,
                          std::vector<std::shared_ptr<ParseNode>>{}
                        )
                  }
                ),
                std::make_shared<ParseNode>(
                  'X', 0,
                  std::vector<std::shared_ptr<ParseNode>>{
                        std::make_shared<ParseNode>(
                          'P', 189,
                          std::vector<std::shared_ptr<ParseNode>>{}
                        )
                  }
                )
          }
        ),
        std::make_shared<ParseNode>(
          'F', 0,
          std::vector<std::shared_ptr<ParseNode>>{
                std::make_shared<ParseNode>(
                  'N', 165,
                  std::vector<std::shared_ptr<ParseNode>>{}
                ),
                std::make_shared<ParseNode>(
                  'O', 0,
                  std::vector<std::shared_ptr<ParseNode>>{
                        std::make_shared<ParseNode>(
                          'R', 129,
                          std::vector<std::shared_ptr<ParseNode>>{}
                        )
                  }
                ),
                std::make_shared<ParseNode>(
                  'R', 0,
                  std::vector<std::shared_ptr<ParseNode>>{
                        std::make_shared<ParseNode>(
                          'E', 184,
                          std::vector<std::shared_ptr<ParseNode>>{}
                        )
                  }
                )
          }
        ),
        std::make_shared<ParseNode>(
          'G', 0,
          std::vector<std::shared_ptr<ParseNode>>{
                std::make_shared<ParseNode>(
                  'E', 0,
                  std::vector<std::shared_ptr<ParseNode>>{
                        std::make_shared<ParseNode>(
                          'T', 161,
                          std::vector<std::shared_ptr<ParseNode>>{}
                        )
                  }
                ),
                std::make_shared<ParseNode>(
                  'O', 0,
                  std::vector<std::shared_ptr<ParseNode>>{
                        std::make_shared<ParseNode>(
                          'S', 0,
                          std::vector<std::shared_ptr<ParseNode>>{
                                std::make_shared<ParseNode>(
                                  'U', 0,
                                  std::vector<std::shared_ptr<ParseNode>>{
                                        std::make_shared<ParseNode>(
                                          'B', 141,
                                          std::vector<std::shared_ptr<ParseNode>>{}
                                        )
                                  }
                                )
                          }
                        ),
                        std::make_shared<ParseNode>(
                          'T', 0,
                          std::vector<std::shared_ptr<ParseNode>>{
                                std::make_shared<ParseNode>(
                                  'O', 137,
                                  std::vector<std::shared_ptr<ParseNode>>{}
                                )
                          }
                        )
                  }
                )
          }
        ),
        std::make_shared<ParseNode>(
          'I', 0,
          std::vector<std::shared_ptr<ParseNode>>{
                std::make_shared<ParseNode>(
                  'F', 139,
                  std::vector<std::shared_ptr<ParseNode>>{}
                ),
                std::make_shared<ParseNode>(
                  'N', 0,
                  std::vector<std::shared_ptr<ParseNode>>{
                        std::make_shared<ParseNode>(
                          'P', 0,
                          std::vector<std::shared_ptr<ParseNode>>{
                                std::make_shared<ParseNode>(
                                  'U', 0,
                                  std::vector<std::shared_ptr<ParseNode>>{
                                        std::make_shared<ParseNode>(
                                          'T', 133,
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
                          'T', 181,
                          std::vector<std::shared_ptr<ParseNode>>{}
                        )
                  }
                )
          }
        ),
        std::make_shared<ParseNode>(
          'L', 0,
          std::vector<std::shared_ptr<ParseNode>>{
                std::make_shared<ParseNode>(
                  'E', 0,
                  std::vector<std::shared_ptr<ParseNode>>{
                        std::make_shared<ParseNode>(
                          'F', 0,
                          std::vector<std::shared_ptr<ParseNode>>{
                                std::make_shared<ParseNode>(
                                  'T', 0,
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
                          'N', 195,
                          std::vector<std::shared_ptr<ParseNode>>{}
                        ),
                        std::make_shared<ParseNode>(
                          'T', 136,
                          std::vector<std::shared_ptr<ParseNode>>{}
                        )
                  }
                ),
                std::make_shared<ParseNode>(
                  'I', 0,
                  std::vector<std::shared_ptr<ParseNode>>{
                        std::make_shared<ParseNode>(
                          'S', 0,
                          std::vector<std::shared_ptr<ParseNode>>{
                                std::make_shared<ParseNode>(
                                  'T', 155,
                                  std::vector<std::shared_ptr<ParseNode>>{}
                                )
                          }
                        )
                  }
                ),
                std::make_shared<ParseNode>(
                  'O', 0,
                  std::vector<std::shared_ptr<ParseNode>>{
                        std::make_shared<ParseNode>(
                          'A', 0,
                          std::vector<std::shared_ptr<ParseNode>>{
                                std::make_shared<ParseNode>(
                                  'D', 147,
                                  std::vector<std::shared_ptr<ParseNode>>{}
                                )
                          }
                        ),
                        std::make_shared<ParseNode>(
                          'G', 188,
                          std::vector<std::shared_ptr<ParseNode>>{}
                        )
                  }
                )
          }
        ),
        std::make_shared<ParseNode>(
          'M', 0,
          std::vector<std::shared_ptr<ParseNode>>{
                std::make_shared<ParseNode>(
                  'I', 0,
                  std::vector<std::shared_ptr<ParseNode>>{
                        std::make_shared<ParseNode>(
                          'D', 0,
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
          'N', 0,
          std::vector<std::shared_ptr<ParseNode>>{
                std::make_shared<ParseNode>(
                  'E', 0,
                  std::vector<std::shared_ptr<ParseNode>>{
                        std::make_shared<ParseNode>(
                          'W', 162,
                          std::vector<std::shared_ptr<ParseNode>>{}
                        ),
                        std::make_shared<ParseNode>(
                          'X', 0,
                          std::vector<std::shared_ptr<ParseNode>>{
                                std::make_shared<ParseNode>(
                                  'T', 130,
                                  std::vector<std::shared_ptr<ParseNode>>{}
                                )
                          }
                        )
                  }
                ),
                std::make_shared<ParseNode>(
                  'O', 0,
                  std::vector<std::shared_ptr<ParseNode>>{
                        std::make_shared<ParseNode>(
                          'T', 168,
                          std::vector<std::shared_ptr<ParseNode>>{}
                        )
                  }
                )
          }
        ),
        std::make_shared<ParseNode>(
          'O', 0,
          std::vector<std::shared_ptr<ParseNode>>{
                std::make_shared<ParseNode>(
                  'N', 145,
                  std::vector<std::shared_ptr<ParseNode>>{}
                ),
                std::make_shared<ParseNode>(
                  'P', 0,
                  std::vector<std::shared_ptr<ParseNode>>{
                        std::make_shared<ParseNode>(
                          'E', 0,
                          std::vector<std::shared_ptr<ParseNode>>{
                                std::make_shared<ParseNode>(
                                  'N', 159,
                                  std::vector<std::shared_ptr<ParseNode>>{}
                                )
                          }
                        )
                  }
                ),
                std::make_shared<ParseNode>(
                  'R', 176,
                  std::vector<std::shared_ptr<ParseNode>>{}
                )
          }
        ),
        std::make_shared<ParseNode>(
          'P', 0,
          std::vector<std::shared_ptr<ParseNode>>{
                std::make_shared<ParseNode>(
                  'E', 0,
                  std::vector<std::shared_ptr<ParseNode>>{
                        std::make_shared<ParseNode>(
                          'E', 0,
                          std::vector<std::shared_ptr<ParseNode>>{
                                std::make_shared<ParseNode>(
                                  'K', 194,
                                  std::vector<std::shared_ptr<ParseNode>>{}
                                )
                          }
                        )
                  }
                ),
                std::make_shared<ParseNode>(
                  'O', 0,
                  std::vector<std::shared_ptr<ParseNode>>{
                        std::make_shared<ParseNode>(
                          'K', 0,
                          std::vector<std::shared_ptr<ParseNode>>{
                                std::make_shared<ParseNode>(
                                  'E', 151,
                                  std::vector<std::shared_ptr<ParseNode>>{}
                                )
                          }
                        ),
                        std::make_shared<ParseNode>(
                          'S', 185,
                          std::vector<std::shared_ptr<ParseNode>>{}
                        )
                  }
                ),
                std::make_shared<ParseNode>(
                  'R', 0,
                  std::vector<std::shared_ptr<ParseNode>>{
                        std::make_shared<ParseNode>(
                          'I', 0,
                          std::vector<std::shared_ptr<ParseNode>>{
                                std::make_shared<ParseNode>(
                                  'N', 0,
                                  std::vector<std::shared_ptr<ParseNode>>{
                                        std::make_shared<ParseNode>(
                                          'T', 153,
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
          'R', 0,
          std::vector<std::shared_ptr<ParseNode>>{
                std::make_shared<ParseNode>(
                  'E', 0,
                  std::vector<std::shared_ptr<ParseNode>>{
                        std::make_shared<ParseNode>(
                          'A', 0,
                          std::vector<std::shared_ptr<ParseNode>>{
                                std::make_shared<ParseNode>(
                                  'D', 135,
                                  std::vector<std::shared_ptr<ParseNode>>{}
                                )
                          }
                        ),
                        std::make_shared<ParseNode>(
                          'M', 143,
                          std::vector<std::shared_ptr<ParseNode>>{}
                        ),
                        std::make_shared<ParseNode>(
                          'S', 0,
                          std::vector<std::shared_ptr<ParseNode>>{
                                std::make_shared<ParseNode>(
                                  'T', 0,
                                  std::vector<std::shared_ptr<ParseNode>>{
                                        std::make_shared<ParseNode>(
                                          'O', 0,
                                          std::vector<std::shared_ptr<ParseNode>>{
                                                std::make_shared<ParseNode>(
                                                  'R', 0,
                                                  std::vector<std::shared_ptr<ParseNode>>{
                                                        std::make_shared<ParseNode>(
                                                          'E', 140,
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
                          'T', 0,
                          std::vector<std::shared_ptr<ParseNode>>{
                                std::make_shared<ParseNode>(
                                  'U', 0,
                                  std::vector<std::shared_ptr<ParseNode>>{
                                        std::make_shared<ParseNode>(
                                          'R', 0,
                                          std::vector<std::shared_ptr<ParseNode>>{
                                                std::make_shared<ParseNode>(
                                                  'N', 142,
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
                  'I', 0,
                  std::vector<std::shared_ptr<ParseNode>>{
                        std::make_shared<ParseNode>(
                          'G', 0,
                          std::vector<std::shared_ptr<ParseNode>>{
                                std::make_shared<ParseNode>(
                                  'H', 0,
                                  std::vector<std::shared_ptr<ParseNode>>{
                                        std::make_shared<ParseNode>(
                                          'T', 0,
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
                  'N', 0,
                  std::vector<std::shared_ptr<ParseNode>>{
                        std::make_shared<ParseNode>(
                          'D', 187,
                          std::vector<std::shared_ptr<ParseNode>>{}
                        )
                  }
                ),
                std::make_shared<ParseNode>(
                  'U', 0,
                  std::vector<std::shared_ptr<ParseNode>>{
                        std::make_shared<ParseNode>(
                          'N', 138,
                          std::vector<std::shared_ptr<ParseNode>>{}
                        )
                  }
                )
          }
        ),
        std::make_shared<ParseNode>(
          'S', 0,
          std::vector<std::shared_ptr<ParseNode>>{
                std::make_shared<ParseNode>(
                  'A', 0,
                  std::vector<std::shared_ptr<ParseNode>>{
                        std::make_shared<ParseNode>(
                          'V', 0,
                          std::vector<std::shared_ptr<ParseNode>>{
                                std::make_shared<ParseNode>(
                                  'E', 148,
                                  std::vector<std::shared_ptr<ParseNode>>{}
                                )
                          }
                        )
                  }
                ),
                std::make_shared<ParseNode>(
                  'G', 0,
                  std::vector<std::shared_ptr<ParseNode>>{
                        std::make_shared<ParseNode>(
                          'N', 180,
                          std::vector<std::shared_ptr<ParseNode>>{}
                        )
                  }
                ),
                std::make_shared<ParseNode>(
                  'I', 0,
                  std::vector<std::shared_ptr<ParseNode>>{
                        std::make_shared<ParseNode>(
                          'N', 191,
                          std::vector<std::shared_ptr<ParseNode>>{}
                        )
                  }
                ),
                std::make_shared<ParseNode>(
                  'P', 0,
                  std::vector<std::shared_ptr<ParseNode>>{
                        std::make_shared<ParseNode>(
                          'C', 0,
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
                  'Q', 0,
                  std::vector<std::shared_ptr<ParseNode>>{
                        std::make_shared<ParseNode>(
                          'R', 186,
                          std::vector<std::shared_ptr<ParseNode>>{}
                        )
                  }
                ),
                std::make_shared<ParseNode>(
                  'T', 0,
                  std::vector<std::shared_ptr<ParseNode>>{
                        std::make_shared<ParseNode>(
                          'E', 0,
                          std::vector<std::shared_ptr<ParseNode>>{
                                std::make_shared<ParseNode>(
                                  'P', 169,
                                  std::vector<std::shared_ptr<ParseNode>>{}
                                )
                          }
                        ),
                        std::make_shared<ParseNode>(
                          'O', 0,
                          std::vector<std::shared_ptr<ParseNode>>{
                                std::make_shared<ParseNode>(
                                  'P', 144,
                                  std::vector<std::shared_ptr<ParseNode>>{}
                                )
                          }
                        ),
                        std::make_shared<ParseNode>(
                          'R', 0,
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
                  'Y', 0,
                  std::vector<std::shared_ptr<ParseNode>>{
                        std::make_shared<ParseNode>(
                          'S', 158,
                          std::vector<std::shared_ptr<ParseNode>>{}
                        )
                  }
                )
          }
        ),
        std::make_shared<ParseNode>(
          'T', 0,
          std::vector<std::shared_ptr<ParseNode>>{
                std::make_shared<ParseNode>(
                  'A', 0,
                  std::vector<std::shared_ptr<ParseNode>>{
                        std::make_shared<ParseNode>(
                          'B', 0,
                          std::vector<std::shared_ptr<ParseNode>>{
                                std::make_shared<ParseNode>(
                                  '(', 163,
                                  std::vector<std::shared_ptr<ParseNode>>{}
                                )
                          }
                        ),
                        std::make_shared<ParseNode>(
                          'N', 192,
                          std::vector<std::shared_ptr<ParseNode>>{}
                        )
                  }
                ),
                std::make_shared<ParseNode>(
                  'H', 0,
                  std::vector<std::shared_ptr<ParseNode>>{
                        std::make_shared<ParseNode>(
                          'E', 0,
                          std::vector<std::shared_ptr<ParseNode>>{
                                std::make_shared<ParseNode>(
                                  'N', 167,
                                  std::vector<std::shared_ptr<ParseNode>>{}
                                )
                          }
                        )
                  }
                ),
                std::make_shared<ParseNode>(
                  'O', 164,
                  std::vector<std::shared_ptr<ParseNode>>{}
                )
          }
        ),
        std::make_shared<ParseNode>(
          'U', 0,
          std::vector<std::shared_ptr<ParseNode>>{
                std::make_shared<ParseNode>(
                  'S', 0,
                  std::vector<std::shared_ptr<ParseNode>>{
                        std::make_shared<ParseNode>(
                          'R', 183,
                          std::vector<std::shared_ptr<ParseNode>>{}
                        )
                  }
                )
          }
        ),
        std::make_shared<ParseNode>(
          'V', 0,
          std::vector<std::shared_ptr<ParseNode>>{
                std::make_shared<ParseNode>(
                  'A', 0,
                  std::vector<std::shared_ptr<ParseNode>>{
                        std::make_shared<ParseNode>(
                          'L', 197,
                          std::vector<std::shared_ptr<ParseNode>>{}
                        )
                  }
                ),
                std::make_shared<ParseNode>(
                  'E', 0,
                  std::vector<std::shared_ptr<ParseNode>>{
                        std::make_shared<ParseNode>(
                          'R', 0,
                          std::vector<std::shared_ptr<ParseNode>>{
                                std::make_shared<ParseNode>(
                                  'I', 0,
                                  std::vector<std::shared_ptr<ParseNode>>{
                                        std::make_shared<ParseNode>(
                                          'F', 0,
                                          std::vector<std::shared_ptr<ParseNode>>{
                                                std::make_shared<ParseNode>(
                                                  'Y', 149,
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
          'W', 0,
          std::vector<std::shared_ptr<ParseNode>>{
                std::make_shared<ParseNode>(
                  'A', 0,
                  std::vector<std::shared_ptr<ParseNode>>{
                        std::make_shared<ParseNode>(
                          'I', 0,
                          std::vector<std::shared_ptr<ParseNode>>{
                                std::make_shared<ParseNode>(
                                  'T', 146,
                                  std::vector<std::shared_ptr<ParseNode>>{}
                                )
                          }
                        )
                  }
                )
          }
        ),
        std::make_shared<ParseNode>(
          '^', 174,
          std::vector<std::shared_ptr<ParseNode>>{}
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