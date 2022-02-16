#pragma once
#include "Definitions.h"
#include <queue>

namespace MafiaBar
{
	class EXP_ENGINE Mouse
	{
		friend class Window;
	public:
		class Event
		{
		public:
			enum class State
			{
				LeftPress,
				LeftRelease,
				RightPress,
				RightRelease,
				WheelUp,
				WheelDown,
				MoveCursor,
				Invalid
			};
		private:
			State state;
			bool IsLeftPressed;
			bool IsRightPressed;
			int x, y;
		public:
			Event()
				: state(State::Invalid), IsLeftPressed(false), IsRightPressed(false), x(0), y(0)
			{}
			Event(State state, const Mouse& mouse) noexcept
				: state(state), IsLeftPressed(mouse.IsLeftPressed), IsRightPressed(mouse.IsLeftPressed),
				x(mouse.x), y(mouse.y)
			{}
		public:
			bool IsValid() const { return state != State::Invalid; }
			State GetState() const { return state; }
			std::pair<int, int> GetPos() const { return { x, y }; }
			int GetPosX() const { return x; }
			int GetPosY() const { return y; }
			bool LeftIsPressed() const { return state == State::LeftPress; }
			bool LeftIsReleased() const { return state == State::LeftRelease; }
			bool RightIsPressed() const { return state == State::RightPress; }
			bool RightIsReleased() const { return state == State::RightRelease; }
		};
	public:
		Mouse() = default;
		Mouse& operator= (const Mouse&) = delete;
		std::pair<int, int> GetPos() const;
		int GetPosX() const;
		int GetPosY() const;
		bool LeftIsPressed() const;
		bool RightIsPressed() const;
		Mouse::Event ReadState();
		bool IsBufferEmpty() const;
		void FlushBuffer();
	public:
		void OnMouseMove(int x, int y);
		void OnLeftPressed(int x, int y);
		void OnLeftReleased(int x, int y);
		void OnRightPressed(int x, int y);
		void OnRightReleased(int x, int y);
		void OnWheelUp(int x, int y);
		void OnWheelDown(int x, int y);
		void TrimBuffer();
	private:
		const unsigned int BufferSize = 16u;
		int x, y;
		bool IsLeftPressed = false;
		bool IsRightPressed = false;
		std::queue<Event> buffer;
	};
}
