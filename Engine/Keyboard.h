#pragma once
#include "../Mafia Bar Engine/pch.h"

namespace MafiaBar
{
	class EXP_ENGINE Keyboard
	{
		friend class Window;
	public:
        enum KeyboardKeys : unsigned char //Used From Keyboard.h (DirectX Library)
        {
            Back = 0x8,
            Tab = 0x9,
            Enter = 0xd,
            Escape = 0x1b,
            Space = 0x20,
            PageUp = 0x21,
            PageDown = 0x22,
            End = 0x23,
            Home = 0x24,
            Left = 0x25,
            Up = 0x26,
            Right = 0x27,
            Down = 0x28,
            Select = 0x29,
            PrintScreen = 0x2c,
            Insert = 0x2d,
            Delete = 0x2e,
            A = 0x41,
            B = 0x42,
            C = 0x43,
            D = 0x44,
            E = 0x45,
            F = 0x46,
            G = 0x47,
            H = 0x48,
            I = 0x49,
            J = 0x4a,
            K = 0x4b,
            L = 0x4c,
            M = 0x4d,
            N = 0x4e,
            O = 0x4f,
            P = 0x50,
            Q = 0x51,
            R = 0x52,
            S = 0x53,
            T = 0x54,
            U = 0x55,
            V = 0x56,
            W = 0x57,
            X = 0x58,
            Y = 0x59,
            Z = 0x5a,
            LeftWindows = 0x5b,
            RightWindows = 0x5c,
            LeftShift = 0xa0,
            RightShift = 0xa1,
            LeftControl = 0xa2,
            RightControl = 0xa3,
            LeftAlt = 0xa4,
            RightAlt = 0xa5,
            F1 = 0x70,
            F2 = 0x71,
            F3 = 0x72,
            F4 = 0x73,
            F5 = 0x74,
            F6 = 0x75,
            F7 = 0x76,
            F8 = 0x77,
            F9 = 0x78,
            F10 = 0x79,
            F11 = 0x7a,
            F12 = 0x7b,
            F13 = 0x7c,
            F14 = 0x7d,
            F15 = 0x7e,
            F16 = 0x7f,
            F17 = 0x80,
            F18 = 0x81,
            F19 = 0x82,
            F20 = 0x83,
            F21 = 0x84,
            F22 = 0x85,
            F23 = 0x86,
            F24 = 0x87,
            NumPad0 = 0x60,
            NumPad1 = 0x61,
            NumPad2 = 0x62,
            NumPad3 = 0x63,
            NumPad4 = 0x64,
            NumPad5 = 0x65,
            NumPad6 = 0x66,
            NumPad7 = 0x67,
            NumPad8 = 0x68,
            NumPad9 = 0x69,
            Multiply = 0x6a,
            Add = 0x6b,
            Separator = 0x6c,
            Subtract = 0x6d,
            Decimal = 0x6e,
            Divide = 0x6f,
        };
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

