#pragma once

#define ENTRYAPP(x) Win32::iApplication* EntryApplication() {return new x; }

namespace Win32 {

	class THESEUS_API iApplication
	{
	public:
		iApplication();
		virtual ~iApplication() {};

		virtual VOID SetupPerGameSettings() = 0;

		virtual VOID PreInitialize() = 0;

		virtual VOID Initialize() = 0;

		virtual VOID Update() = 0;

	};


	iApplication* EntryApplication();
}