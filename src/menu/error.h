#pragma once

#include <sstream>
#include <vector>

namespace menu {
	struct Error {
	private:
		enum Type {
			SyntaxError, InvalidElementError, DuplcateElementError
		};

		bool occured;
		Type type;
		size_t position;
		std::vector<char> expectedCharacters;

	public:
		Error() : occured(false) {}

		void syntaxError(size_t position, char character) {
			occured = true;
			type = SyntaxError;
			this->position = position;
			expectedCharacters.push_back(character);
		}

		void syntaxError(size_t position, std::initializer_list<char> characterList) {
			occured = true;
			type = SyntaxError;
			this->position = position;
			expectedCharacters = characterList;
		}

		void invalidElementError(size_t position) {
			occured = true;
			type = InvalidElementError;
			this->position = position;
		}

		void duplicateElementError(size_t position) {
			occured = true;
			type = DuplcateElementError;
			this->position = position;
		}

		explicit operator bool() const {
			return occured;
		}

		friend std::ostream& operator<<(std::ostream &stream, const Error &error) {
			if(error) {
				if(error.type == SyntaxError) {
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
				else if(error.type == InvalidElementError) {
					stream << "Error: invalid element on position " << error.position;
				}
				else {
					stream << "Error: duplicate element on position " << error.position;
				}
			}

			return stream;
		}
	};
}