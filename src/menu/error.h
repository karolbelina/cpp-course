#pragma once

namespace menu {
	struct Error {
		bool occured;
		size_t position;
		char expectedCharacter;

		Error() : occured(false) {}

		void occur(size_t position, char expectedCharacter) {
			occured = true;
			this->position = position;
			this->expectedCharacter = expectedCharacter;
		}
	};
}