// C64BasicTok.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <fstream>
#include <vector>
#include <memory>
#include <string>
#include <cstdint>
#include <unordered_map>
#include "ParseTree.h"


struct LineOutput
{
	uint16_t next;
	uint16_t lineNumber;
	std::vector<uint8_t> bytes;
};

static std::string Detokenize(std::vector<uint8_t>tokens)
{
	std::string output;

    if (tokens.size() < 2) 
        return output;
        
    // get the load address
    auto pos = 0;
    uint16_t load_address = tokens[0] + (tokens[1] << 8);
    pos += 2;
    
    auto current_address = load_address;
    while (pos < tokens.size())
	{
	    if (pos + 2 >= tokens.size())
	        return output;
	        
	    uint16_t next = tokens[pos] + (tokens[pos +1] << 8);
	    pos += 2;
	    
	    if (pos + 2 >= tokens.size())
	        return output;

	    uint16_t line;
	    line = tokens[pos] + (tokens[pos +1] << 8);
	    pos += 2;
	    
	    output += std::to_string(line);
	    
	    while (pos < tokens.size())
	    {
	        auto ch = tokens[pos];
	    
	        // check for end of line
	        if (ch == 0) {
	            pos++;
	            output += "\n";
	            break;
	        }
	            
		    if (TokenToKeyword.contains(ch)) 
		        output += TokenToKeyword[ch];
		    else 
		        output += ch;
		    pos++;
	    }
	}
	return output;
}

static struct LineOutput TokenizeLine(const int current_address, const std::string& str)
{
	const std::string quote = "\"";
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
			if (result.token_id == 143) { // rem statement dont tokenize rest of line
			   pos += result.length;
			   while (pos < str.length() && str[pos] != '\n') {
			       output.bytes.push_back(str[pos]);
			       pos++;
			   }
			   // output.bytes.push_back(0);
			   continue;
			}
		}
		else {
			output.bytes.push_back(tok[0]);
			if (tok == quote) {
				do
				{
					pos++;
					output.bytes.push_back(str[pos]);
				} while (pos < str.length() && str[pos] != quote[0]);
			}
		}
		pos += result.length;
	}
	output.bytes.push_back(0);  // end of line marker
	output.next = current_address + output.bytes.size() + 4;
	return output;
}

std::vector<uint8_t> TokenizeFile(std::string filename)
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
	
	output.push_back(current_address & 0xFF);
	output.push_back((current_address >> 8) & 0xFF);
	
	// Read line by line until the end of the file

	while (std::getline(file, line)) {
		auto tokline = TokenizeLine(current_address, line);
		output.push_back(tokline.next & 0xFF);
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

	auto out = TokenizeFile(input_path);
	auto detok = Detokenize(out);
    std::cout << detok << "\n";
    
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