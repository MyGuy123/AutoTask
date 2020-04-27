#include "stdafx.h"
#include "init.h"


//Just setting the things to happen on creation and destruction
MainDialog::MainDialog() : CDialog(MainDialog::IDD) {}
MainDialog::~MainDialog() {}

MainDialog mndlg;

//Making a interface to change the text on the window
void MainDialog::changeText(const wchar_t * txt) {
	this->GetDlgItem(IDC_STATUS)->SetWindowText(txt);
}

//The function to be started with
BOOL Startup::InitInstance() {
	//telling the program this is the main dlg
	m_pMainWnd = &mndlg;
	//startup the main dlg
	mndlg.DoModal();
	return TRUE;
}

//actually do the starting
Startup start;
