#pragma once
/*
* 
* Keyboard Events By Mafia Bar From Scratch Keyboard.h
* But We Recommend to Use DirectX Keyboard.h (it's better for now) With DirectX namespace
*
*/
#include "../Mafia Bar Engine/pch.h"
#include <bitset>

class Keyboard
{
	friend class Window;
public:
	class Event
	{
	public:
		enum class StateKey
		{
			Press, // 0
			Release, // 1
			Invalid // 2
		};
	private:
		StateKey statekeys;
		unsigned char codekey;
	public:
		Event()
			: statekeys( StateKey::Invalid ), codekey ( 0u )
		{

		}
		Event(const StateKey& keysate, unsigned char code) noexcept
			: statekeys ( keysate ), codekey ( code )
		{

		}
		bool isPress() const { return statekeys == StateKey::Press;  }
		bool isRelease() const { return statekeys == StateKey::Release; }
		bool isInvalid() const { return statekeys == StateKey::Invalid; }
		unsigned char GetKeyCode() const { return codekey; } //codekey unsgined char Getter 
	};
public:
	Keyboard() = default;
	Keyboard(const Keyboard&) = delete;
	Keyboard& operator=(const Keyboard&) = delete;
	//Key Events
	bool IsKeyPressed(unsigned char keycode) const noexcept
	{
		return keystates[keycode];
	}
	Event ReadKey()
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
	bool IsKeyEmpty()
	{
		return keybuffer.empty(); //Clearing Key Buffer Queue
	}
	void FlushKey()
	{
		keybuffer = std::queue<Event>(); //Flushing KeyBuffer
	}

	//while (kbhit()) getch(); Clear Whole Keyboard Input
	
	//Char Events Stream Characters 
	char ReadChar()
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
	bool CharIsEmpty() const
	{
		return charBuffer.empty();
	}
	void FlushChar()
	{
		charBuffer = std::queue<char>(); //Clearing CharBuffer
	}
	void Flush()
	{
		//Clearing/Flushing Everything CharBuffer And KeyBuffer
		FlushKey();
		FlushChar();
	}

	//Repeat Control
	void EnableAutoRepeat()
	{
		autorepeatenabled = true;
	}
	void DisableAutoRepeat()
	{
		autorepeatenabled = false;
	}
	bool IsAutoRepeatControlEnabled() const
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
	void OnKeyPressed(unsigned char keycode) //Updating KeyState on pressing key
	{
		keystates[keycode] = true;
		keybuffer.push(Keyboard::Event(Keyboard::Event::StateKey::Press, keycode));
		TrimBufferQueueSafe(keybuffer); //For  Not Blowing Up The Buffer

	}
	void OnKeyReleased(unsigned char keycode)//Updating KeyState on releasing key
	{
		keystates[keycode] = false;
		keybuffer.push(Keyboard::Event(Keyboard::Event::StateKey::Release, keycode));
		TrimBufferQueueSafe(keybuffer);
	}
	void OnChar(char character)
	{
		charBuffer.push(character);
		TrimBufferQueueSafe(charBuffer);
	}
	void ClearState()
	{
		keystates.reset(); //Clearing Bitset of Booleans
	}
	template<typename T>
	static void TrimBufferQueueSafe(std::queue<T>& buffer)
	{
		while (buffer.size() > BufferSize)
		{
			buffer.pop();
		}
	}
private:
	static constexpr unsigned int nkeys = 265u;
	static constexpr unsigned int BufferSize = 16u;
	bool autorepeatenabled = false;
	std::bitset<nkeys> keystates; //Packing 256 into  bits as bool
	std::queue<Event> keybuffer; //Storing Them into Even Class in a queue
	std::queue<char> charBuffer; //CharBuffer


};
