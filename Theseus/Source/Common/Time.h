#pragma once
#include <string>

namespace Time {

	//Get Current TIme in string format
	WSTRING THESEUS_API GetTime(BOOL stripped = FALSE);

	//Get Current Date in string format 
	WSTRING THESEUS_API GetDate(BOOL stripped = FALSE);

	//Get Current Date and Time in string format 
	WSTRING THESEUS_API GetDateTimeString(BOOL stripped = FALSE);
}
