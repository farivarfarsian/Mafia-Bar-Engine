#pragma once
#include "../Mafia Bar Engine/pch.h"

namespace MafiaBar
{
	class EXP_ENGINE Keyboard
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
				: statekeys(StateKey::Invalid), codekey(0u)
			{

			}
			Event(const StateKey& keysate, unsigned char code) noexcept
				: statekeys(keysate), codekey(code)
			{

			}
			bool isPress() const { return statekeys == StateKey::Press; }
			bool isRelease() const { return statekeys == StateKey::Release; }
			bool isInvalid() const { return statekeys == StateKey::Invalid; }
			unsigned char GetKeyCode() const { return codekey; } //codekey unsgined char Getter 
		};
	public:
		Keyboard() = default;
		Keyboard(const Keyboard&) = delete;
		Keyboard& operator=(const Keyboard&) = delete;
		//Key Events
		bool IsKeyPressed(unsigned char keycode) const noexcept;
		Event ReadKey();
		bool IsKeyEmpty();
		void FlushKey();

		//while (kbhit()) getch(); Clear Whole Keyboard Input

		//Char Events Stream Characters 
		char ReadChar();
		bool CharIsEmpty() const;
		void FlushChar();
		void Flush();

		//Repeat Control
		void EnableAutoRepeat();
		void DisableAutoRepeat();
		bool IsAutoRepeatControlEnabled() const;
		void OnKeyPressed(unsigned char keycode); //Updating KeyState on pressing key
		void OnKeyReleased(unsigned char keycode); //Updating KeyState on releasing key
		void OnChar(char character);
		void ClearState();
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
}

