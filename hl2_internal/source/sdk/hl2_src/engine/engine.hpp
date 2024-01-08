#pragma once
#define abstract_class class

class IVEngineClient013
{

};

abstract_class IVEngineClient : public IVEngineClient013
{
public:
	virtual unsigned int GetProtocolVersion() = 0;
	virtual bool IsWindowedMode() = 0;

	// Flash the window (os specific)
	virtual void	FlashWindow() = 0;

	// Client version from the steam.inf, this will be compared to the GC version
	virtual int GetClientVersion() const = 0; // engines build

	// Is App Active 
	virtual bool IsActiveApp() = 0;

	virtual void DisconnectInternal() = 0;

	virtual int GetInstancesRunningCount() = 0;
};