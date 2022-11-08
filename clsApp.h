#pragma once
#include "clsHGOapplication.h"
#include "clsWindow.h"

class clsApp : public clsHGOapplication {
public:
	clsWindow* pWindow = 0;
public:
	virtual bool DoInitilize() override;
	virtual bool DoBegin(int nCmdShow) override;
	virtual bool DoRunning() override;
	virtual void DoEnd() override;
};

