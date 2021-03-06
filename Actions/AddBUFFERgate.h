#pragma once

#include "action.h"
#include "..\Components\Buffer.h"
#include "..\ApplicationManager.h"

class AddBUFFERgate : public Action
{
private:
	//Parameters for rectangular area to be occupied by the gate
	int Cx, Cy;	//Center point of the gate
	int x1, y1, x2, y2;	//Two corners of the rectangluar area
public:
	AddBUFFERgate(ApplicationManager* pApp);
	virtual ~AddBUFFERgate(void);

	//Reads parameters required for action to execute
	virtual void ReadActionParameters();
	//Execute action (code depends on action type)
	virtual void Execute();

	virtual void Undo();
	virtual void Redo();


};
