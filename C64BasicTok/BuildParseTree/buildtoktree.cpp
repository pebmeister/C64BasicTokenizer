// BuildTokTree.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#include <iostream>
#include <vector>
#include <iomanip>
#include <map>
#include <chrono>
#include <fstream>
#include <functional>
#include <algorithm>
#include <unordered_map>
#include <string>
#include <cstdint>
#include <stdexcept>

static const std::unordered_map<std::string, int> KeywordToToken{
	{"end",        0x80},
	{"for",        0x81},
	{"next",       0x82},
	{"data",       0x83},
	{"input#",     0x84},
	{"input",      0x85},
	{"dim",        0x86},
	{"read",       0x87},
	{"let",        0x88},
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
static std::unordered_map<int, std::string> TokenToKeyword = [] {
	std::unordered_map<int, std::string> rev;
	for (auto& p : KeywordToToken)
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
		std::ofstream out_file("ParseTree.h");
		if (!out_file)
		{
			throw std::runtime_error("Failed to create output file");
		}

		out_file
		        << "#pragma once\n"
		        << "// Generated ParseTree.h\n"
		        << "// DO NOT EDIT\n"
		        << "\n"

		        << "#include <memory>\n"
		        << "#include <vector>\n"
		        << "#include <unordered_map>\n"
		        << "\n"

		        << "struct ParseNode {\n"
		        << "    char ch;\n"
		        << "    int token;\n"
		        << "    std::vector<std::shared_ptr<ParseNode>> child;\n"
		        << "\n"
		        << "    ParseNode(char ch) : ch(ch), token(0) {}\n"
		        << "    ParseNode(char ch, int token) : ch(ch), token(token) {}\n"
		        << "    ParseNode(char ch, int token, std::vector<std::shared_ptr<ParseNode>> child) : \n"
		        << "        ch(ch), token(token), child(child) {}\n"
		        << "};\n"
		        << "\n"

		        << "// Result structure to return from our matching function\n"
		        << "struct MatchResult {\n"
		        << "    int token_id;\n"
		        << "    size_t length;\n"
		        << "};\n"
		        << "\n"

		        << "// Finds the longest matching prefix in the Trie starting at index 'start_pos'\n"
		        << "static MatchResult match_longest_token(std::shared_ptr<ParseNode> root, const std::string& text, size_t start_pos)\n"
		        << "{\n"
		        << "    if (!root || start_pos >= text.length()) {\n"
		        << "        return { 0, 0 };\n"
		        << "    }\n"
		        << "\n"
		        << "    std::shared_ptr<ParseNode> current = root;\n"
		        << "    size_t current_pos = start_pos;\n"
		        << "\n"
		        << "    // Track the best valid token state we've passed so far\n"
		        << "    int last_valid_token = 0;\n"
		        << "    size_t last_valid_length = 0;\n"
		        << "\n"
		        << "    while (current_pos < text.length()) {\n"
		        << "        char next_char = std::tolower(text[current_pos]);\n"
		        << "        std::shared_ptr<ParseNode> next_node = nullptr;\n"
		        << "\n"
		        << "        // Linear search through the node's children for a character match\n"
		        << "        for (const auto& child_node : current->child) {\n"
		        << "            if (child_node->ch == next_char) {\n"
		        << "                next_node = child_node;\n"
		        << "                break;\n"
		        << "            }\n"
		        << "        }\n"
		        << "\n"
		        << "        // If no matching child edge exists, we can't look further down the tree\n"
		        << "        if (!next_node) {\n"
		        << "            break;\n"
		        << "        }\n"
		        << "\n"
		        << "        // Advance into the matching child node\n"
		        << "        current = next_node;\n"
		        << "        current_pos++;\n"
		        << "\n"
		        << "        // If this state represents a complete keyword/operator, log it!\n"
		        << "        if (current->token != 0) {\n"
		        << "            last_valid_token = current->token;\n"
		        << "            last_valid_length = current_pos - start_pos;\n"
		        << "        }\n"
		        << "    }\n"
		        << "\n"
		        << "    // If we found a reserved word/operator, return it\n"
		        << "    if (last_valid_token != 0) {\n"
		        << "        return { last_valid_token, last_valid_length };\n"
		        << "    }\n"
		        << "\n"
		        << "    // Fallback: If no tree path matched a valid token, treat the first char as a literal\n"
		        << "    return { 0, 1 };\n"
		        << "}\n"
		        << "\n"

		        << "static const std::unordered_map<std::string, int> KeywordToToken\n"
		        << "{\n";
		for (auto& p : KeywordToToken)
			out_file
			        << "    {\"" << p.first << "\", " << std::to_string(p.second) << "},\n";
		out_file
		        << "};\n";

		out_file
		        << "// Reverse dictionary\n"
		        << "static std::unordered_map<int, std::string> TokenToKeyword = []\n"
		        << "{\n"
		        << "    std::unordered_map<int, std::string> rev;\n"
		        << "    for (auto& p : KeywordToToken)\n"
		        << "        rev[p.second] = p.first;\n"
		        << "    return rev;\n"
		        << "}();\n"
		        << "\n"
		        << "\n// === Generated Initializer List ===\n"
		        << "std::shared_ptr<ParseNode> root = \n";

		generateInitializerListHelper(root, 0, out_file);
		out_file << ";\n";
		out_file.close();
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
			if (node->ch == '\\' )
				out << indent << " '\\\\'";
			else if (node->ch == '\'')
				out << indent << "'\\'";
			else
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
	for (const auto& [keyword, token] : KeywordToToken) {
		toks.emplace_back(token, keyword);
	}
	tokenizer.buildtoktree(root, toks);
	// tokenizer.printParseTree(root);
	tokenizer.generateInitializerList(root);
	return 0;
}