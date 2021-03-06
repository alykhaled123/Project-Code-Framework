#include "OR2.h"


OR2::OR2(const GraphicsInfo& r_GfxInfo, int r_FanOut) :Gate(2, r_FanOut)
{
	m_GfxInfo.x1 = r_GfxInfo.x1;
	m_GfxInfo.y1 = r_GfxInfo.y1;
	m_GfxInfo.x2 = r_GfxInfo.x2;
	m_GfxInfo.y2 = r_GfxInfo.y2;
}


void OR2::Operate()
{
	for (int i = 0; i < m_Inputs; i++)
	{
		if (m_InputPins[i].getStatus() == HIGH)
		{
			m_OutputPin.setStatus(HIGH);
			break;
		}
		m_OutputPin.setStatus(LOW);

	}
}

ActionType OR2::getType() {
	return ADD_OR_GATE_2;
}
string OR2::getName()
{
	return "OR2";
}
GraphicsInfo OR2::getCenter()
{
	GraphicsInfo gfx = m_GfxInfo;
	gfx.x1 += UI.OR_Width / 2;
	gfx.y1 += UI.OR_Height / 2;
	return gfx;
}

// Function Draw
// Draws 2-input AND gate
void OR2::Draw(Output* pOut)
{
	//Call output class and pass gate drawing info to it.
	pOut->DrawOR2(m_GfxInfo,selected);
}

//returns status of outputpin
int OR2::GetOutPinStatus()
{
	return m_OutputPin.getStatus();
}


//returns status of Inputpin #n
int OR2::GetInputPinStatus(int n)
{
	return m_InputPins[n - 1].getStatus();	//n starts from 1 but array index starts from 0.
}

GraphicsInfo OR2::getInputPinPosition(int n)
{
	GraphicsInfo gfx = m_GfxInfo;
	gfx.x2 -= UI.OR_Width / 2;
	if (n == 1)
	{
		gfx.y2 -= 25;
	}
	else
	{
		gfx.y1 += 25;
	}

	return gfx;
}

GraphicsInfo OR2::getOutputPinPosition()
{
	GraphicsInfo gfx = m_GfxInfo;
	gfx.x1 += UI.OR_Width / 2;
	return gfx;
}

//Set status of an input pin ot HIGH or LOW
void OR2::setInputPinStatus(int n, STATUS s)
{
	m_InputPins[n - 1].setStatus(s);
}
