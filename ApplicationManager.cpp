#include "ApplicationManager.h"
#include "Actions\AddANDgate2.h"
#include "Actions\AddNAND2gate2.h"
#include "Actions\AddORgate2.h"
#include "Actions\AddNOR3gate3.h"
#include "Actions\AddXORgate2.h"
#include "Actions\AddAND3gate3.h"
#include "Actions\AddXNORgate2.h"
#include "Actions\AddXOR3gate3.h"
#include "Actions\AddNORgate2.h"
#include "Actions\AddNOTgate.h"
#include "Actions\AddBUFFERgate.h"
#include "Actions\AddConnection.h"
#include "Actions\AddSwitch.h"
#include "Actions\AddLED.h"
#include "Actions\Simulate.h"
#include "Actions\Select.h"
#include "Actions\TruthTable.h"
#include "Actions\Copy.h"
#include "Actions\Paste.h"
#include "Actions\Probing.h"
#include "Actions\Save.h"
#include "Actions\Load.h"
#include "Actions\Edit.h"
#include "Actions\Delete.h"
#include "Actions\Cut.h"



ApplicationManager::ApplicationManager()
{
	CompCount = 0;

	for(int i=0; i<MaxCompCount; i++)
		CompList[i] = NULL;

	//Creates the Input / Output Objects & Initialize the GUI
	OutputInterface = new Output();
	InputInterface = OutputInterface->CreateInput();
}
void ApplicationManager::setIsValid(bool isValid)
{
	this->isValid = isValid;
}
void ApplicationManager::setActionType(ActionType type)
{
	copiedType = type;
}
ActionType ApplicationManager::getActionType()
{
	return copiedType;
}
////////////////////////////////////////////////////////////////////
void ApplicationManager::AddComponent(Component* pComp)
{
	CompList[CompCount++] = pComp;
	pComp->setID(CompCount);
}
void ApplicationManager::SetCopiedComponent(Component* pComp) {
	copiedComp = pComp;
}

/* Returns the last copied/cut component */
Component* ApplicationManager::GetCopiedComponent() const {
	return copiedComp;
}
Component** ApplicationManager::getComponents()
{
	return CompList;
}
void ApplicationManager::setComponents(Component** compList)
{
	for (int i = 0; i < CompCount; i++)
	{
		CompList[i] = compList[i];
	}
}
int ApplicationManager::getComponetsNumber()
{
	return CompCount;
}
void ApplicationManager::decreaseComponentNum()
{
	CompCount--;
}
//////////////////////////////////////////////////////////////////
Component* ApplicationManager::getSelectedComponent()
{
	return selectedComp;
}
void ApplicationManager::setSelectedComponent(Component* selectedComp)
{
	this->selectedComp = selectedComp;
}
ActionType ApplicationManager::GetUserAction()
{
	//Call input to get what action is reuired from the user
	return InputInterface->GetUserAction(OutputInterface);
}
////////////////////////////////////////////////////////////////////

void ApplicationManager::ExecuteAction(ActionType ActType)
{
	Action* pAct = NULL;
	switch (ActType)
	{
		case ADD_AND_GATE_2:
			pAct= new AddANDgate2(this);
			break;

		case ADD_INV:
			pAct = new AddNOTgate(this);
			break;
		
		case ADD_OR_GATE_2:
			pAct = new AddORgate2(this);
			break;
		
		case ADD_XOR_GATE_2:
			pAct = new AddXORgate2(this);
			break;
		
		case ADD_LED:
			pAct = new AddLED(this);
			break;

		case ADD_Buff:
			pAct = new AddBUFFERgate(this);
			break;

		case ADD_CONNECTION:
			pAct = new AddConnection(this);
			break;

		case ADD_XNOR_GATE_2:
			pAct = new AddXNORgate2(this);
			break;

		case ADD_NAND_GATE_2:
			pAct = new AddNAND2gate2(this);
			break;

		case ADD_NOR_GATE_3:
			pAct = new AddNOR3gate3(this);
			break;

		case ADD_AND_GATE_3:
			pAct = new AddAND3gate3(this);
			break;

		case ADD_XOR_GATE_3:
			pAct = new AddXOR3gate3(this);
			break;

		case ADD_NOR_GATE_2:
			pAct = new AddNORgate2(this);
			break;
		
		case ADD_Switch:
			pAct = new AddSwitch(this);
			break;

		case SIM_MODE:
			ExecuteAction(VALIDATION);
			if (isValid)
			{
				OutputInterface->CreateSimulationToolBar();
				pAct = new Simulate(this);
			}
			else
			{
				OutputInterface->PrintMsg("Invalid Circuit");
			}
			break;
		
		case DSN_MODE:
			OutputInterface->CreateDesignToolBar();
			UI.AppMode = DESIGN;
			break;
		case SELECT:
			pAct = new Select(this);
			break;
		
		case COPY:
			pAct = new Copy(this);
			break;
		case PASTE:
			pAct = new Paste(this);
			break;
		case Create_TruthTable:
			pAct = new TruthTable(this);
			break;
		case VALIDATION:
			pAct = new Validation(this);
			break;
		case PROBING:
			pAct = new Probing(this);
			break;
		case SAVE:
			pAct = new Save(this);
			break;
		case LOAD:
			pAct = new Load(this);
			break;
		case EDIT:
			pAct = new Edit(this);
			break;
		case DEL:
			pAct = new DeleteComp(this);
			break;
		case CUT:
			pAct = new Cut(this);
			break;
		case EXIT:
			break;
	}
	if(pAct)
	{
		pAct->Execute();
		delete pAct;
		pAct = NULL;
	}
}
////////////////////////////////////////////////////////////////////

void ApplicationManager::UpdateInterface()
{
	for (int i = 0; i < CompCount; i++)
	{
		CompList[i]->Draw(OutputInterface);
		CompList[i]->DrawLabel(OutputInterface);
	}

}
void ApplicationManager::Delete()
{
	int Count = CompCount;
	for (int i = 0; i < Count; i++)
	{
		if (dynamic_cast<Gate*>(CompList[i]))
		{
			dynamic_cast<Gate*>(CompList[i])->getOutputPin()->DeleteConnections();
			for (int k = 0; k < dynamic_cast<Gate*>(CompList[i])->getNumInputs(); k++)
			{
				if (dynamic_cast<Gate*>(CompList[i])->getInputPin(k + 1) != NULL)
				{
					dynamic_cast<Gate*>(CompList[i])->getInputPin(k + 1)->DeleteConnection();
				}
			}
		}
		if (CompList[i])
		{
			if (CompList[i] == getSelectedComponent())
			{
				delete CompList[i];
				CompList[i] = NULL;
				for (int j = i; j < CompCount; j++) {
					CompList[j] = CompList[j + 1];
				}
				i--;
				CompCount--;
			}
		}
	}
}
////////////////////////////////////////////////////////////////////
Input* ApplicationManager::GetInput()
{
	return InputInterface;
}

////////////////////////////////////////////////////////////////////
Output* ApplicationManager::GetOutput()
{
	return OutputInterface;
}

////////////////////////////////////////////////////////////////////

ApplicationManager::~ApplicationManager()
{
	for(int i=0; i<CompCount; i++)
		delete CompList[i];
	delete OutputInterface;
	delete InputInterface;
	
}