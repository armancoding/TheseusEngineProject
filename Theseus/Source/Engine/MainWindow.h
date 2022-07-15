#pragma once

namespace MainScreen {
	VOID THESEUS_API Open();
	VOID THESEUS_API Close();
}

class THESEUS_API MainWindow :public Win32::Window
{
public: 
	MainWindow();
	~MainWindow();

	VOID				OnNonClientCreate()	override;
	VOID				PaintCaption(HDC hdc) override;
	VOID				OnNonClientLeftMouseButtonDown() override;


private:

};

