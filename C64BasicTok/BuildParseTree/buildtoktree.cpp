// BuildTokTree.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#include <iostream>
#include <vector>
#include <iomanip>
#include <map>
#include <chrono>
#include <functional>
#include <algorithm>
#include <unordered_map>
#include <string>
#include <cstdint>

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

class Tokenizer {

public:
    // Updated struct to allow for branching (Tree structure)
    struct ParseNode {
        char ch;
        int token;
        std::vector<std::shared_ptr<ParseNode>> child;

        ParseNode(char ch) : ch(ch), token(0) {}
        ParseNode(char ch, int token) : ch(ch), token(token) {}
        ParseNode(char ch, int token, std::vector<std::shared_ptr<ParseNode>> child) : ch(ch), token(token), child(child) {}
    };

    void printParseTree(const std::shared_ptr<ParseNode>& root)
    {
        std::cout << "=== Parse Tree ===" << std::endl;
        printParseTreeHelper(root, 0);
    }

    void generateInitializerList(std::shared_ptr<ParseNode>& root)
    {
        std::cout << "\n// === Generated Initializer List ===" << std::endl;
        std::cout << "std::shared_ptr<ParseNode> root = \n";
        generateInitializerListHelper(root, 0, std::cout);
        std::cout << ";\n";
    }

private:
  
    std::shared_ptr<ParseNode> op_root = std::make_shared<ParseNode>(0);

    void insertToken(std::shared_ptr<ParseNode> root, int token, const std::string& word)
    {
        auto curnode = root;
        for (auto& ch : word)
        {
            auto it = std::lower_bound(curnode->child.begin(), curnode->child.end(), ch,
                [](const std::shared_ptr<ParseNode>& node, char c) {
                    return node->ch < c;
                });

            if (it != curnode->child.end() && (*it)->ch == ch) {
                curnode = *it;
            }
            else {
                auto newNode = std::make_shared<ParseNode>(ch);
                curnode->child.insert(it, newNode);
                curnode = newNode;
            }
        }

        curnode->token = token;
    }

    void printParseTreeHelper(const std::shared_ptr<ParseNode>& node, int depth)
    {
        if (!node) {
            return;
        }

        if (node->ch != 0) {
            std::string indent(depth * 4, ' ');
            std::cout << indent << "ch: '" << (node->ch == 0 ? '0' : node->ch) << "'";

            if (node->token != 0) {
                std::cout << " -> TOKEN: " << node->token;
            }

            std::cout << std::endl;
        }
        for (const auto& child : node->child) {
            printParseTreeHelper(child, depth + 1);
        }
    }



    void generateInitializerListHelper(const std::shared_ptr<ParseNode>& node, int depth, std::ostream& out)
    {
        if (!node) {
            return;
        }

        std::string indent(depth * 4, ' ');

        if (node->ch == 0) {
            // Root node
            out << "std::make_shared<ParseNode>(\n";
            out << indent << "  0, 0,\n";
            out << indent << "  std::vector<std::shared_ptr<ParseNode>>{\n";
        }
        else {
            out << indent << "std::make_shared<ParseNode>(\n";
            out << indent << "  '" << node->ch << "', ";

            if (node->token != 0) {
                out << node->token;
            }
            else {
                out << 0;
            }
            out << ",\n";

            if (!node->child.empty()) {
                out << indent << "  std::vector<std::shared_ptr<ParseNode>>{\n";
            }
            else {
                out << indent << "  std::vector<std::shared_ptr<ParseNode>>{}\n";
                out << indent << ")";
                return;
            }
        }

        for (size_t i = 0; i < node->child.size(); ++i) {
            generateInitializerListHelper(node->child[i], depth + 2, out);

            if (i < node->child.size() - 1) {
                out << ",\n";
            }
            else {
                out << "\n";
            }
        }

        out << indent << "  }\n";
        out << indent << ")";
    }


public:
    void buildtoktree(std::shared_ptr<ParseNode>& root, std::vector<std::pair<int, std::string>>& toks)
    {
        std::sort(toks.begin(), toks.end(), [](const auto& a, const auto& b) {
            return a.second < b.second;
            });

        for (const auto& [tok, str] : toks) {
            insertToken(root, tok, str);
        }
    }
};

int main()
{
	Tokenizer tokenizer;
	std::shared_ptr<Tokenizer::ParseNode> root = std::make_shared<Tokenizer::ParseNode>(0);
	std::vector<std::pair<int, std::string>> toks;
	for (const auto& [keyword, token] : BasicKeywordToToken) {
		toks.emplace_back(token, keyword);
	}
	tokenizer.buildtoktree(root, toks);
	tokenizer.printParseTree(root);
	tokenizer.generateInitializerList(root);
	return 0;
}