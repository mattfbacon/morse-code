#include <iostream>
#include <iomanip>
#include <array>
#include <cstdint>
#include <cstddef>
#include <cassert>

namespace Morse {

enum Unit : char {
	pause = 0, // for zero-filling purposes
	dot = '.',
	dash = '-',
};

size_t constexpr MAX_MORSE_LENGTH = 4;

// take advantage of zero-filling to fill the rest with pauses
std::array<std::array<Unit, MAX_MORSE_LENGTH>, 'z' - 'a' + 1> letters{
	std::array<Unit, MAX_MORSE_LENGTH>{ dot, dash }, // A
	{ dash, dot, dot, dot }, // B
	{ dash, dot, dash, dot }, // C
	{ dash, dot, dot }, // D
	{ dot }, // E
	{ dot, dot, dash, dot }, // F
	{ dash, dash, dot }, // G
	{ dot, dot, dot, dot }, // H
	{ dot, dot }, // I
	{ dot, dash, dash, dash }, // J
	{ dash, dot, dash, }, // K
	{ dot, dash, dot, dot }, // L
	{ dash, dash }, // M
	{ dash, dot }, // N
	{ dash, dash, dash }, // O
	{ dot, dash, dash, dot }, // P
	{ dash, dash, dot, dash }, // Q
	{ dot, dash, dot }, // R
	{ dot, dot, dot }, // S
	{ dash }, // T
	{ dot, dot, dash }, // U
	{ dot, dot, dot, dash }, // V
	{ dot, dash, dash }, // W
	{ dash, dot, dot, dash }, // X
	{ dash, dot, dash, dash }, // Y
	{ dash, dash, dot, dot }, // Z
};

std::ostream& operator<<(std::ostream& o, decltype(letters[0]) const& code) {
	for (size_t i = 0; i < code.size() && code[i] != Unit::pause; i++) {
		o << code[i];
	}
	return o;
}

}

using Morse::operator<<;

bool isalpha(char const c) {
	return (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z');
}

int main() {
	char c;
	while (std::cin.get(c)) {
		if (c == decltype(std::cin)::traits_type::eof()) {
			break;
		} else if (c == ' ' || c == '\n') {
			std::cout << " / ";
		} else if (isalpha(c)) {
			c |= 32; // upper to lower
			c -= 'a';
			assert(c < (char)Morse::letters.size());
			std::cout << Morse::letters[c] << ' ';
		} else {
#ifndef NDEBUG
			std::clog << "Unknown character " << c << " (0x" << std::setfill('0') << std::setw(2) << std::hex << +c << "), ignoring" << std::endl;
#endif
		}
	}
	std::cout << std::endl;
	return 0;
}
