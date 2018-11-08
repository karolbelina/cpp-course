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
	const char SLASH = '/';

	const char PROMPT = '>';

	const std::string BACK_COMMAND = "back";
	const std::string SEARCH_COMMAND = "search";
	const std::string HELP_COMMAND = "help";

	const std::string INVALID_COMMAND_MESSAGE = "Invalid command";
	const std::string DEFAULT_COMMAND_MESSAGE = "Default command";
	const std::string EMPTY_COMMAND_MESSAGE = "Empty command";
	const std::string NO_MATCHES_MESSAGE = "No matches";
	const std::string NO_HELP_AVAILABLE_MESSAGE = "No help available";
}