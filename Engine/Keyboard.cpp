#include "Keyboard.h"

bool MafiaBar::Keyboard::IsKeyPressed(unsigned char keycode) const noexcept { return keystates[keycode]; }

MafiaBar::Keyboard::Event MafiaBar::Keyboard::ReadKey()
{
	if (keybuffer.size() != 0u)
	{
		MafiaBar::Keyboard::Event e = keybuffer.front();
		keybuffer.pop();
		return e;
	}
	else
	{
		return MafiaBar::Keyboard::Event(); //Returning Invalid Event With Default Constrcutor
	}
}

bool MafiaBar::Keyboard::IsKeyEmpty() { return keybuffer.empty(); } //Clearing Key Buffer Queue


void MafiaBar::Keyboard::FlushKey() { keybuffer = std::queue<Event>(); } //Flushing KeyBuffer


char MafiaBar::Keyboard::ReadChar()
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

bool MafiaBar::Keyboard::CharIsEmpty() const { return charBuffer.empty(); }

void MafiaBar::Keyboard::FlushChar() { charBuffer = std::queue<char>(); } //Clearing CharBuffer


void MafiaBar::Keyboard::Flush()
{
	//Clearing/Flushing Everything CharBuffer And KeyBuffer
	FlushKey();
	FlushChar();
}

void MafiaBar::Keyboard::EnableAutoRepeat() { autorepeatenabled = true; }

void MafiaBar::Keyboard::DisableAutoRepeat() { autorepeatenabled = false; }

bool MafiaBar::Keyboard::IsAutoRepeatControlEnabled() const
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

void MafiaBar::Keyboard::OnKeyPressed(unsigned char keycode)
{
	keystates[keycode] = true;
	keybuffer.push(Keyboard::Event(Keyboard::Event::StateKey::Press, keycode));
	TrimBufferQueueSafe(keybuffer); //For  Not Blowing Up The Buffer
}

void MafiaBar::Keyboard::OnKeyReleased(unsigned char keycode)
{
	keystates[keycode] = false;
	keybuffer.push(Keyboard::Event(Keyboard::Event::StateKey::Release, keycode));
	TrimBufferQueueSafe(keybuffer);
}

void MafiaBar::Keyboard::OnChar(char character)
{
	charBuffer.push(character);
	TrimBufferQueueSafe(charBuffer);
}

void MafiaBar::Keyboard::ClearState() { keystates.reset();} //Clearing Bitset of Booleans 
