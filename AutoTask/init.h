#pragma once

#include <afxwin.h>
#include "resource.h"

//The Main Dialog Class for the main interaction window
class MainDialog : public CDialog {
public:
	enum { IDD = IDD_DIALOG1 };
	MainDialog();
	~MainDialog();
	DECLARE_MESSAGE_MAP()
	afx_msg void OnExecute();
	afx_msg void OnRecord();
	void changeText(const wchar_t * newtxt);
};

//The Class to Start Things off in MFC
class Startup : public CWinApp {
public:
	BOOL InitInstance();
};

