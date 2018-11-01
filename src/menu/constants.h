#pragma once

#include <string>

namespace menu {
	const char SPACE = ' ';
	const int PADDING = 2;

	const char LEFT_PARENTHESIS = '(';
	const char RIGHT_PARENTHESIS = ')';
	const char LEFT_SQUARE_BRACKET = '[';
	const char RIGHT_SQUARE_BRACKET = ']';
	const char APOSTROPHE = '\'';
	const char COMMA = ',';
	const char SEMICOLON = ';';

	const char PROMPT = '>';

	const std::string EMPTY_STRING = "";

	const std::string BACK_COMMAND_NAME = "back";
	const std::string BACK_COMMAND_STRING = "..";

	const std::string PRINT_LEAVES_COMMAND_NAME = "print leaves";
	const std::string PRINT_LEAVES_COMMAND_STRING = "leaves";

	const std::string INVALID_COMMAND_MESSAGE = "invalid command";
	const std::string DEFAULT_COMMAND_MESSAGE = "default command";
	const std::string EMPTY_COMMAND_MESSAGE = "empty command";
}