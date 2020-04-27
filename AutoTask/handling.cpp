#include "stdafx.h"
#include "init.h"
#include <memory>

#define NULLKEY 0xff

//map commands or whatever to functions
BEGIN_MESSAGE_MAP(MainDialog, CDialog)
	ON_COMMAND(ID_RECORDING_EXECUTE, &MainDialog::OnExecute)
	ON_COMMAND(ID_RECORDING_RECORD, &MainDialog::OnRecord)
END_MESSAGE_MAP()

//main thread
bool recordingPressed = false;

//not main thread
//key to start recording and end
UINT8 startRecordingKey = NULLKEY;
//Whether the key has been pressed a second time
bool startedRecording = false;

//shared things
std::shared_ptr <bool> recordingPressedShared(&recordingPressed);

//std::shared_ptr <void (*)(const char*)> changeTxtShared(&changeTxtToShare);
std::shared_ptr <MainDialog> mainDlgShared;


//Deal with keyboard input
LRESULT __declspec (dllexport) WINAPI KbdInput(HWND wnd, UINT msg,  WPARAM wP, LPARAM lP) {
	if (*recordingPressedShared) {
		if (startedRecording) {
			if (((KEYBDINPUT*)wP)->wVk == startRecordingKey && msg == WM_KEYUP) {
				*recordingPressedShared = false;
				startRecordingKey = NULLKEY;
				startedRecording = false;
				return NULL;
			}
		} else if (startRecordingKey == NULLKEY) {
			//When key is released it is a full press 
			if (msg == WM_KEYUP) {
				startRecordingKey = ((KEYBDINPUT*)wP)->wVk;
				(*mainDlgShared).changeText(L"Key pressed");
			}
		}
		else if (((KEYBDINPUT *) wP)->wVk == startRecordingKey && msg == WM_KEYUP){
			startedRecording = true;
		}

	}
	//do the default thing with the input (otherwise it wont)
	return DefWindowProc(wnd, msg, wP, lP);
}

//When execute is pressed
void MainDialog::OnExecute()
{
	//TODO: Code the execution
}
//When record is pressed
void MainDialog::OnRecord()
{
	mainDlgShared = std::make_shared <MainDialog>(this);
	this->changeText(L"hello world");
	SetWindowsHookEx(WH_KEYBOARD_LL, (HOOKPROC)KbdInput, GetModuleHandle(NULL), NULL);
	// TODO: Add your command handler code here
}
