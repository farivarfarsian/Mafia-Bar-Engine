#pragma once
#include "../Mafia Bar Engine/pch.h"
class Mouse
{
	friend class RenderWindow;
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
			: state ( State::Invalid ), IsLeftPressed ( false ), IsRightPressed( false ), x(0), y(0)
		{}
		Event(State state, const Mouse& mouse) noexcept
			: state(state), IsLeftPressed( mouse.IsLeftPressed ), IsRightPressed( mouse.IsLeftPressed ),
			x( mouse.x), y( mouse.y )
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
	Mouse(const Mouse&) = delete;
	Mouse& operator= (const Mouse&) = delete;
	std::pair<int, int> GetPos() const { return { x, y }; }
	int GetPoxX() const { return x; }
	int GetPoxY() const { return y; }
	bool LeftIsPressed() const { return IsLeftPressed; }
	bool RightIsPressed() const { return IsRightPressed; }
	Mouse::Event ReadState() 
	{
		if (buffer.size() > 0u) //Checking If the Buffer is Empty or Not
		{
			Mouse::Event e = buffer.front();
			buffer.pop();
			return e;
		}
		else
		{
			return Mouse::Event();
		}
	}
	bool IsBufferEmpty() const { return buffer.empty(); }
	void FlushBuffer() { buffer = std::queue<Event>(); }
public:
	void OnMouseMove(int x, int y)
	{
		this->x = x;
		this->y = y;

		buffer.push(Mouse::Event(Mouse::Event::State::MoveCursor, *this));
		TrimBuffer();
	}
	void OnLeftPressed(int x, int y)
	{
		IsLeftPressed = true;

		buffer.push(Mouse::Event(Mouse::Event::State::LeftPress, *this));
		TrimBuffer();
	}
	void OnLeftReleased(int x, int y)
	{
		IsLeftPressed = false;

		buffer.push(Mouse::Event(Mouse::Event::State::LeftRelease, *this));
		TrimBuffer();

	}
	void OnRightPressed(int x, int y)
	{
		IsRightPressed = true;

		buffer.push(Mouse::Event(Mouse::Event::State::RightPress, *this));
		TrimBuffer();
	}
	void OnRightReleased(int x,int y)
	{
		IsRightPressed = false;

		buffer.push(Mouse::Event(Mouse::Event::State::RightRelease, *this));
		TrimBuffer();
	}
	void OnWheelUp(int x, int y)
	{
		buffer.push(Mouse::Event(Mouse::Event::State::WheelUp, *this));
		TrimBuffer();
	}
	void OnWheelDown(int x, int y)
	{
		buffer.push(Mouse::Event(Mouse::Event::State::WheelDown, *this));
		TrimBuffer();
	}
	void TrimBuffer()
	{
		while (buffer.size() > BufferSize)
		{
			buffer.pop();
		}
	}
private:
	const unsigned int BufferSize = 16u;
	int x, y;
	bool IsLeftPressed = false;
	bool IsRightPressed = false;
	std::queue<Event> buffer;
};