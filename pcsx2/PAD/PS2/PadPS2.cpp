
#include "PrecompiledHeader.h"
#include "PadPS2.h"

#include "./PAD/PadUtils.h"

PadPS2::PadPS2() = default;
PadPS2::~PadPS2() = default;

bool PadPS2::IsInConfigMode()
{
	return config;
}

bool PadPS2::IsAnalogLightOn()
{
	return analogLight;
}

bool PadPS2::IsAnalogLocked()
{
	return analogLocked;
}

// Some of the "Constant" functions of the protocol are
// called twice back to back but expecting different responses
// each time; this bool tracks whether we are on an even or odd
// call.
bool PadPS2::GetConstantStage()
{
	return constantStage;
}

bool PadPS2::IsConfigResponse()
{
	return configResponse;
}

PadPS2Type PadPS2::GetPadType()
{
	return type;
}

PadPS2Physical PadPS2::GetPadPhysicalType()
{
	return physical;
}

u8 PadPS2::GetDigitalByte1()
{
	u8 ret = 0xff;
	if (buttonStates.right) ret &= DigitalByte1::RIGHT;
	if (buttonStates.left) ret &= DigitalByte1::LEFT;
	if (buttonStates.up) ret &= DigitalByte1::UP;
	if (buttonStates.down) ret &= DigitalByte1::DOWN;
	if (buttonStates.select) ret &= DigitalByte1::SELECT;
	if (buttonStates.l3) ret &= DigitalByte1::L3;
	if (buttonStates.r3) ret &= DigitalByte1::R3;
	if (buttonStates.start) ret &= DigitalByte1::START;
	return ret;
}

u8 PadPS2::GetDigitalByte2()
{
	u8 ret = 0xff;
	if (buttonStates.triangle) ret &= DigitalByte2::TRIANGLE;
	if (buttonStates.circle) ret &= DigitalByte2::CIRCLE;
	if (buttonStates.cross) ret &= DigitalByte2::CROSS;
	if (buttonStates.square) ret &= DigitalByte2::SQUARE;
	if (buttonStates.l1) ret &= DigitalByte2::L1;
	if (buttonStates.r1) ret &= DigitalByte2::R1;
	if (buttonStates.l2) ret &= DigitalByte2::L2;
	if (buttonStates.r2) ret &= DigitalByte2::R2;
	return ret;
}

u8 PadPS2::GetButton(PS2Button button)
{
	switch (button)
	{
	case PS2Button::RIGHT:
		return buttonStates.right;
	case PS2Button::LEFT:
		return buttonStates.left;
	case PS2Button::UP:
		return buttonStates.up;
	case PS2Button::DOWN:
		return buttonStates.down;
	case PS2Button::TRIANGLE:
		return buttonStates.triangle;
	case PS2Button::CIRCLE:
		return buttonStates.circle;
	case PS2Button::CROSS:
		return buttonStates.cross;
	case PS2Button::SQUARE:
		return buttonStates.square;
	case PS2Button::L1:
		return buttonStates.l1;
	case PS2Button::R1:
		return buttonStates.r1;
	case PS2Button::L2:
		return buttonStates.l2;
	case PS2Button::R2:
		return buttonStates.r2;
	case PS2Button::SELECT:
		return buttonStates.select;
	case PS2Button::L3:
		return buttonStates.l3;
	case PS2Button::R3:
		return buttonStates.r3;
	case PS2Button::START:
		return buttonStates.start;
	default:
		return 0xff;
	}
}

u8 PadPS2::GetAnalog(PS2Analog analog)
{
	switch (analog)
	{
	case PS2Analog::LEFT_X:
		return buttonStates.leftX;
	case PS2Analog::LEFT_Y:
		return buttonStates.leftY;
	case PS2Analog::RIGHT_X:
		return buttonStates.rightX;
	case PS2Analog::RIGHT_Y:
		return buttonStates.rightY;
	default:
		return 0xff;
	}
}

void PadPS2::SetInConfigMode(bool b)
{
	config = b;
}

void PadPS2::SetAnalogLight(bool b)
{
	analogLight = b;
}

void PadPS2::SetAnalogLocked(bool b)
{
	analogLocked = b;
}

// Set the constantStage bool. The third byte sent in the command
// indicates whether this is the first (0) or second (1) time
// this command has been sent.
void PadPS2::SetConstantStage(bool b)
{
	constantStage = b;
}

void PadPS2::SetConfigResponse(bool b)
{
	configResponse = b;
}

void PadPS2::SetPadType(PadPS2Type type)
{
	this->type = type;
}

void PadPS2::SetPadPhysicalType(PadPS2Physical physical)
{
	this->physical = physical;
}

void PadPS2::SetButton(PS2Button button, u8 data)
{
	switch (button)
	{
	case PS2Button::RIGHT:
		buttonStates.right = data;
		break;
	case PS2Button::LEFT:
		buttonStates.left = data;
		break;
	case PS2Button::UP:
		buttonStates.up = data;
		break;
	case PS2Button::DOWN:
		buttonStates.down = data;
		break;
	case PS2Button::TRIANGLE:
		buttonStates.triangle = data;
		break;
	case PS2Button::CIRCLE:
		buttonStates.circle = data;
		break;
	case PS2Button::CROSS:
		buttonStates.cross = data;
		break;
	case PS2Button::SQUARE:
		buttonStates.square = data;
		break;
	case PS2Button::L1:
		buttonStates.l1 = data;
		break;
	case PS2Button::R1:
		buttonStates.r1 = data;
		break;
	case PS2Button::L2:
		buttonStates.l2 = data;
		break;
	case PS2Button::R2:
		buttonStates.r2 = data;
		break;
	case PS2Button::SELECT:
		buttonStates.select = data;
		break;
	case PS2Button::L3:
		buttonStates.l3 = data;
		break;
	case PS2Button::R3:
		buttonStates.r3 = data;
		break;
	case PS2Button::START:
		buttonStates.start = data;
		break;
	}
}

void PadPS2::SetAnalog(PS2Analog analog, u8 data)
{
	switch (analog)
	{
	case PS2Analog::LEFT_X:
		buttonStates.leftX = data;
	case PS2Analog::LEFT_Y:
		buttonStates.leftY = data;
	case PS2Analog::RIGHT_X:
		buttonStates.rightX = data;
	case PS2Analog::RIGHT_Y:
		buttonStates.rightY = data;
	}
}


void PadPS2::Debug_Poll()
{
#ifdef _WIN32
	XInput_Poll(this);
#endif
}