#include "MB_Keyboard.h"

bool Keyboard::IsKeyPressed(unsigned char keycode) const noexcept { return keystates[keycode]; }

Keyboard::Event Keyboard::ReadKey()
{
	if (keybuffer.size() != 0u)
	{
		Keyboard::Event e = keybuffer.front();
		keybuffer.pop();
		return e;
	}
	else
	{
		return Keyboard::Event(); //Returning Invalid Event With Default Constrcutor
	}
}

bool Keyboard::IsKeyEmpty() { return keybuffer.empty(); } //Clearing Key Buffer Queue


void Keyboard::FlushKey() { keybuffer = std::queue<Event>(); } //Flushing KeyBuffer


char Keyboard::ReadChar()
{
	if (charBuffer.size() != 0u)
	{
		unsigned char charcode = charBuffer.front();
		charBuffer.pop();
		return charcode;
	}
	else
	{
		return 0; //Nan Char
	}
}

bool Keyboard::CharIsEmpty() const { return charBuffer.empty(); }

void Keyboard::FlushChar() { charBuffer = std::queue<char>(); } //Clearing CharBuffer


void Keyboard::Flush()
{
	//Clearing/Flushing Everything CharBuffer And KeyBuffer
	FlushKey();
	FlushChar();
}

void Keyboard::EnableAutoRepeat() { autorepeatenabled = true; }

void Keyboard::DisableAutoRepeat() { autorepeatenabled = false; }

bool Keyboard::IsAutoRepeatControlEnabled() const
{
	if (autorepeatenabled == true)
	{
		return true;
	}
	else
	{
		return false;
	}
}

void Keyboard::OnKeyPressed(unsigned char keycode)
{
	keystates[keycode] = true;
	keybuffer.push(Keyboard::Event(Keyboard::Event::StateKey::Press, keycode));
	TrimBufferQueueSafe(keybuffer); //For  Not Blowing Up The Buffer
}

void Keyboard::OnKeyReleased(unsigned char keycode)
{
	keystates[keycode] = false;
	keybuffer.push(Keyboard::Event(Keyboard::Event::StateKey::Release, keycode));
	TrimBufferQueueSafe(keybuffer);
}

void Keyboard::OnChar(char character)
{
	charBuffer.push(character);
	TrimBufferQueueSafe(charBuffer);
}

void Keyboard::ClearState() { keystates.reset();} //Clearing Bitset of Booleans 
