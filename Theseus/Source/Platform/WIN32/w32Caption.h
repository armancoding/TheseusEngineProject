#pragma once

#define			CB_CLOSE		0
#define			CB_MINIMIZE		1
#define			CB_MAXIMIZE		2

#define			CB_FILE			0
#define			CB_EDIT			1
#define			CB_WINDOW		2
#define			CB_TOOLS		3

namespace Win32 {
	class Caption
	{
	public:
		struct CaptionButton
		{
			WSTRING Text = L"X";
			INT Command = -1;
			INT Width = 50;
			RECT Rect; 
			CaptionButton(WSTRING text, INT command, INT width = 50) { Text = text; Command = command; Width = width; }
		};


	private:
		BOOL m_ShowTitle = TRUE;
		std::list<CaptionButton*> m_CaptionButtons;
		std::list<CaptionButton*> m_CaptionButtonsProp;

	public:
		BOOL ShowTitle() { return m_ShowTitle; }
		std::list<CaptionButton*> CaptionButtons() { return m_CaptionButtons; }
		std::list<CaptionButton*> CaptionButtonsProp() { return m_CaptionButtonsProp; }

	public:
		VOID ShowTitle(BOOL show) { m_ShowTitle = show; }

	public: 
		VOID AddCaptionButton(CaptionButton* button);
		VOID AddCaptionButtonProp(CaptionButton* button);

	};

}