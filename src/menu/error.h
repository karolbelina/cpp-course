#pragma once

#include <sstream>
#include <vector>

namespace menu {
	struct Error {
	public:
		Error();

		void syntaxError(size_t position, char character);
		void syntaxError(size_t position, std::initializer_list<char> characterList);
		void invalidElementError(size_t position);
		void duplicateElementError(size_t position);

		explicit operator bool() const;
		friend std::ostream& operator<<(std::ostream &stream, const menu::Error &error);

	private:
		enum Type {
			SyntaxError, InvalidElementError, DuplcateElementError
		};

		bool occured;
		Type type;
		size_t position;
		std::vector<char> expectedCharacters;
	};
}