#pragma once
#include <fstream>

class THESEUS_API Logger 
{
	//Getters and Setters for singleton static class
private:
	static Logger* inst;
public:
	static Logger* Instance() { return inst; }

public:
	Logger();
	~Logger();

	static VOID PrintLog(const WCHAR* fmt, ...);
	static WSTRING LogDirectory();
	static WSTRING LogFile();

	//Print a lne of '-' chars 
	static VOID PrintDebugSeparator();

	//Check to see if MTail is already running
	static BOOL IsMTailRunning();

	// Start MTail Application
	static VOID StartMTail();

};