#include "Keyboard.h"

bool Keyboard::KeyIsPressed(unsigned char keycode) const noexcept {
	return keystates[keycode];
}

Keyboard::Event Keyboard::ReadKey() noexcept{
	if (keyBuffer.size() > 0u) {
		Keyboard::Event e = keyBuffer.front();
		keyBuffer.pop();
		return e;
	}
	else {
		return Keyboard::Event();
	}
}

bool Keyboard::KeyIsEmpty() const noexcept {
	return keyBuffer.empty();
}

char Keyboard::ReadChar() noexcept {
	if (charBuffer.size() > 0u) {
		unsigned int charcode = charBuffer.front();
		keyBuffer.pop();
		return charcode;
	}
	else {
		return 0;
	}
}

bool Keyboard::CharIsEmpty() const noexcept {
	return charBuffer.empty();
}

void Keyboard::FlushKey() noexcept {
	keyBuffer = std::queue<Event>();
}

void Keyboard::FlushChar() noexcept {
	charBuffer = std::queue<char>();
}

void Keyboard::Flush() noexcept {
	FlushKey();
	FlushChar();
}

void Keyboard::EnableAutorepeat() noexcept {
	autorepeatEnabled = true;
}

bool Keyboard::AutorepeatIsEnabled() noexcept {
	return autorepeatEnabled;
}

void Keyboard::OnKeyPressed(unsigned char keycode) noexcept {
	keystates[keycode] = true;
	keyBuffer.push(Keyboard::Event(Keyboard::Event::Type::Press, keycode));
	TrimBuffer(keyBuffer);
}

void Keyboard::OnKeyReleased(unsigned char keycode) noexcept {
	keystates[keycode] = false;
	keyBuffer.push(Keyboard::Event(Keyboard::Event::Type::Release, keycode));
	TrimBuffer(keyBuffer);
}

void Keyboard::OnChar(char character) noexcept {
	charBuffer.push(character);
	TrimBuffer(charBuffer);
}

void Keyboard::ClearState() noexcept {
	keystates.reset();
}

template<typename T>
void Keyboard::TrimBuffer(std::queue<T>& buffer) noexcept {
	while (buffer.size() > bufferSize) {
		buffer.pop();
	}
}