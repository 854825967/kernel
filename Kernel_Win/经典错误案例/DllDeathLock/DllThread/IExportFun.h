#pragma once

#if defined DLLTHREAD_EXPORTS
#define EXPORT_FUN __declspec(dllexport)
#else
#define EXPORT_FUN __declspec(dllimport)
#endif


class IFunctionInterface
{
public:
	virtual ~IFunctionInterface(){}

public:
	virtual bool StartWork() = 0;
};

extern "C" EXPORT_FUN IFunctionInterface* GetInterface();