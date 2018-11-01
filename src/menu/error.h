#pragma once

namespace menu {
	struct Error {
		bool occured;
		size_t position;
		char expectedCharacter; // expand to multiple chars (char array)

		Error() : occured(false) {}

		void occur(size_t position, char expectedCharacter) {
			occured = true;
			this->position = position;
			this->expectedCharacter = expectedCharacter;
		}
	};
}