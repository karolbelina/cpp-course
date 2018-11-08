#pragma once

#include "error.h"

#include <sstream>
#include <vector>

menu::Error::Error(): occured(false) {}

void menu::Error::syntaxError(size_t position, char character) {
	occured = true;
	type = SyntaxError;
	this->position = position;
	expectedCharacters.push_back(character);
}

void menu::Error::syntaxError(size_t position, std::initializer_list<char> characterList) {
	occured = true;
	type = SyntaxError;
	this->position = position;
	expectedCharacters = characterList;
}

void menu::Error::invalidElementError(size_t position) {
	occured = true;
	type = InvalidElementError;
	this->position = position;
}

void menu::Error::duplicateElementError(size_t position) {
	occured = true;
	type = DuplcateElementError;
	this->position = position;
}

menu::Error::operator bool() const {
	return occured;
}

std::ostream& menu::operator<<(std::ostream &stream, const menu::Error &error) {
	if(error) {
		if(error.type == Error::Type::SyntaxError) {
			stream << "Error: expected ";

			size_t size = error.expectedCharacters.size();
			for(size_t i = 0; i < size; ++i) {
				stream << "'" << error.expectedCharacters[i] << "'";

				if(size > 1) {
					if(i < size - 2) {
						stream << ", ";
					}
					else if(i == size - 2) {
						stream << " or ";
					}
				}
			}

			stream << " on position " << error.position;
		}
		else if(error.type == Error::Type::InvalidElementError) {
			stream << "Error: invalid element on position " << error.position;
		}
		else {
			stream << "Error: duplicate element on position " << error.position;
		}
	}

	return stream;
}