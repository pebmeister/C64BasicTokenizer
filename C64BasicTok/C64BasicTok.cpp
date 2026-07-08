// C64BasicTok.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <fstream>
#include <vector>
#include <memory>
#include <string>
#include <cstdint>
#include <unordered_map>


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

static std::vector<uint8_t> Tokenize(const std::string& str)
{
    std::vector<uint8_t> out;
    std::string quote = "\"";
    size_t pos = 0;

    while (pos < str.length()) {
        auto result = match_longest_token(root, str, pos);
        std::string_view tok{ str.data() + pos, result.length };
        if (result.token_id != 0) {
            out.push_back(result.token_id);
        }
        else {
            out.push_back(tok[0]);
            if (tok == quote) {
                do
                {
                    pos ++;
                    out.push_back(str[pos]);
                } while (str[pos] != quote[0]);
            }
        }
        pos += result.length;
    }

    return out;
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

static std::string read_file_iterator(const std::string& filepath) {
    std::ifstream file(filepath);
    if (!file.is_open()) return "";

    // Instantiates the string using the file's start and end iterators
    return std::string((std::istreambuf_iterator<char>(file)),
        std::istreambuf_iterator<char>());
}

int main(int argc, char* argv[])
{
    if (argc < 2)
    {
        std::cout << "No input file provided.";
		return 1;
    }

	for (auto i = 1; i < argc; ++i)
	{
		std::string input = read_file_iterator(argv[i]);
		auto out = Tokenize(input);
		auto detok = Detokenize(out);
		if (detok != input)
		{
			std::cout << "input\n" << input << "\n============\n";
			std::cout << "detok\n" << detok << "\n============\n";
		}
	}
    return 0;
}
