#include "Mouse.h"

std::pair<int, int> MafiaBar::Mouse::GetPos() const { return { x, y }; }

int MafiaBar::Mouse::GetPosX() const { return x; }

int MafiaBar::Mouse::GetPosY() const { return y; }

bool MafiaBar::Mouse::LeftIsPressed() const { return IsLeftPressed; }

bool MafiaBar::Mouse::RightIsPressed() const { return IsRightPressed; }

MafiaBar::Mouse::Event MafiaBar::Mouse::ReadState() 
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

bool MafiaBar::Mouse::IsBufferEmpty() const { return buffer.empty(); }

void MafiaBar::Mouse::FlushBuffer() { buffer = std::queue<Event>(); }

void MafiaBar::Mouse::OnMouseMove(int x, int y) 
{
	this->x = x;
	this->y = y;

	buffer.push(Mouse::Event(Mouse::Event::State::MoveCursor, *this));
	TrimBuffer();
}

void MafiaBar::Mouse::OnLeftPressed(int x, int y)
{
	IsLeftPressed = true;

	buffer.push(Mouse::Event(Mouse::Event::State::LeftPress, *this));
	TrimBuffer();
}

void MafiaBar::Mouse::OnLeftReleased(int x, int y)
{
	IsLeftPressed = false;

	buffer.push(Mouse::Event(Mouse::Event::State::LeftRelease, *this));
	TrimBuffer();

}

void MafiaBar::Mouse::OnRightPressed(int x, int y)
{
	IsRightPressed = true;

	buffer.push(Mouse::Event(Mouse::Event::State::RightPress, *this));
	TrimBuffer();
}

void MafiaBar::Mouse::OnRightReleased(int x, int y)
{
	IsRightPressed = false;

	buffer.push(Mouse::Event(Mouse::Event::State::RightRelease, *this));
	TrimBuffer();
}

void MafiaBar::Mouse::OnWheelUp(int x, int y)
{
	buffer.push(Mouse::Event(Mouse::Event::State::WheelUp, *this));
	TrimBuffer();
}

void MafiaBar::Mouse::OnWheelDown(int x, int y)
{
	buffer.push(Mouse::Event(Mouse::Event::State::WheelDown, *this));
	TrimBuffer();
}

void MafiaBar::Mouse::TrimBuffer()
{
	while (buffer.size() > BufferSize)
	{
		buffer.pop();
	}
}
