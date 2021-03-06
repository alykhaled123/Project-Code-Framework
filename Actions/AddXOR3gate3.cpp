#include "AddXOR3gate3.h"
#include"..\Components\XNOR2.h"
#include "..\ApplicationManager.h"


AddXOR3gate3::AddXOR3gate3(ApplicationManager* pApp) :Action(pApp)
{

}

AddXOR3gate3::~AddXOR3gate3(void)
{

}

void AddXOR3gate3::ReadActionParameters()
{
	//Get a Pointer to the Input / Output Interfaces
	Output* pOut = pManager->GetOutput();
	Input* pIn = pManager->GetInput();

	//Print Action Message
	pOut->PrintMsg("3-Input XOR3 Gate: Click to add the gate");

	//Wait for User Input
	pIn->GetPointClicked(Cx, Cy);

	//Clear Status Bar
	pOut->ClearStatusBar();

}

void AddXOR3gate3::Execute()
{
	//Get Center point of the Gate
	ReadActionParameters();
	int yup, ybot;
	Output* pOut = pManager->GetOutput();

	//Calculate the rectangle Corners
	int Len = UI.XOR3_Width;
	int Wdth = UI.XOR3_Height;
	for (int i = 0; i < pManager->getComponetsNumber(); i++)
	{
		GraphicsInfo gfx = pManager->getComponents()[i]->getPosition();
		if (gfx.x1 <= Cx && gfx.x2 >= Cx && gfx.y1 <= Cy && gfx.y2 >= Cy || (Cy >= 0 && Cy < UI.ToolBarHeight + UI.ActionToolBarHeight))
		{
			pOut->PrintMsg("Invaild Position");
			return;
		}

	}
	if (Cy >= 0 && Cy < UI.ToolBarHeight + UI.ActionToolBarHeight)
	{
		pOut->PrintMsg("Invaild Position");
		return;
	}
	GraphicsInfo GInfo; //Gfx info to be used to construct the AND2 gate

	yup = Cy / 100;
	yup *= 100;
	yup += 30;

	ybot = Cy / 100;
	ybot *= 100;
	ybot += 80;

	if (abs((Cy - yup)) > abs(Cy - ybot))
	{
		GInfo.y1 = ybot;
		Cy = ybot;
	}
	else
	{
		GInfo.y1 = yup;
		Cy = yup;
	}

	GInfo.x1 = Cx - Len / 2;
	GInfo.x2 = Cx + Len / 2;
	GInfo.y1 = Cy - Wdth / 2;
	GInfo.y2 = Cy + Wdth / 2;

	/*GraphicsInfo border = GInfo;
	border.x1 -= 3;
	border.x2 += 3;
	border.y1 -= 3;
	border.y2 += 3;
	pOut->DrawRectangle(border);*/

	Input* pIn = pManager->GetInput();
	string label = pIn->GetSrting(pOut);

	XOR3* pA = new XOR3(GInfo, AND2_FANOUT);
	pA->setLabel(label);
	pManager->AddComponent(pA);
}

void AddXOR3gate3::Undo()
{

}

void AddXOR3gate3::Redo()
{

}