#pragma once
// Generated ParseTree.h
// DO NOT EDIT

#include <memory>
#include <vector>
#include <unordered_map>

struct ParseNode {
    char ch;
    int token;
    std::vector<std::shared_ptr<ParseNode>> child;

    ParseNode(char ch) : ch(ch), token(0) {}
    ParseNode(char ch, int token) : ch(ch), token(token) {}
    ParseNode(char ch, int token, std::vector<std::shared_ptr<ParseNode>> child) : 
        ch(ch), token(token), child(child) {}
};

// Result structure to return from our matching function
struct MatchResult {
    int token_id;
    size_t length;
};

// Finds the longest matching prefix in the Trie starting at index 'start_pos'
static MatchResult match_longest_token(std::shared_ptr<ParseNode> root, const std::string& text, size_t start_pos)
{
    if (!root || start_pos >= text.length()) {
        return { 0, 0 };
    }

    std::shared_ptr<ParseNode> current = root;
    size_t current_pos = start_pos;

    // Track the best valid token state we've passed so far
    int last_valid_token = 0;
    size_t last_valid_length = 0;

    while (current_pos < text.length()) {
        char next_char = std::tolower(text[current_pos]);
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

static const std::unordered_map<std::string, int> KeywordToToken
{
    {"mid$", 202},
    {"right$", 201},
    {"left$", 200},
    {"chr$", 199},
    {"val", 197},
    {"str$", 196},
    {"peek", 194},
    {"atn", 193},
    {"sin", 191},
    {"log", 188},
    {"rnd", 187},
    {"wait", 146},
    {"tan", 192},
    {"^", 174},
    {"cont", 154},
    {"poke", 151},
    {"=", 178},
    {"save", 148},
    {"len", 195},
    {"print#", 152},
    {"clr", 156},
    {"rem", 143},
    {"on", 145},
    {"input", 133},
    {"exp", 189},
    {"return", 142},
    {"let", 136},
    {"gosub", 141},
    {"to", 164},
    {"input#", 132},
    {"then", 167},
    {"for", 129},
    {"or", 176},
    {"restore", 140},
    {"list", 155},
    {"run", 138},
    {"and", 175},
    {">", 177},
    {"goto", 137},
    {"next", 130},
    {"end", 128},
    {"data", 131},
    {"tab(", 163},
    {"dim", 134},
    {"get", 161},
    {"def", 150},
    {"verify", 149},
    {"stop", 144},
    {"asc", 198},
    {"read", 135},
    {"if", 139},
    {"fn", 165},
    {"sys", 158},
    {"open", 159},
    {"not", 168},
    {"abs", 182},
    {"close", 160},
    {"int", 181},
    {"new", 162},
    {"cmd", 157},
    {"spc(", 166},
    {"+", 170},
    {"-", 171},
    {"*", 172},
    {"print", 153},
    {"/", 173},
    {"load", 147},
    {"fre", 184},
    {"sgn", 180},
    {"step", 169},
    {"usr", 183},
    {"cos", 190},
    {"pos", 185},
    {"<", 179},
    {"sqr", 186},
};
// Reverse dictionary
static std::unordered_map<int, std::string> TokenToKeyword = []
{
    std::unordered_map<int, std::string> rev;
    for (auto& p : KeywordToToken)
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
