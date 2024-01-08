#pragma once

class RecvTable;

class ClientClass;

// Linked list of all known client classes
extern ClientClass* g_pClientClassHead;

// The serial number that gets passed in is used for ehandles.
typedef void* (*CreateClientClassFn)(int entnum, int serialNum);
typedef void* (*CreateEventFn)();

//-----------------------------------------------------------------------------
// Purpose: Client side class definition
//-----------------------------------------------------------------------------
class ClientClass
{
public:
	ClientClass(const char* pNetworkName, CreateClientClassFn createFn, CreateEventFn createEventFn, RecvTable* pRecvTable)
	{
		m_pNetworkName = pNetworkName;
		m_pCreateFn = createFn;
		m_pCreateEventFn = createEventFn;
		m_pRecvTable = pRecvTable;

		// Link it in
		m_pNext = g_pClientClassHead;
		g_pClientClassHead = this;
	}

	const char* GetName()
	{
		return m_pNetworkName;
	}

public:
	CreateClientClassFn	m_pCreateFn;
	CreateEventFn		m_pCreateEventFn; //Only called for event objects.
	const char* m_pNetworkName;
	RecvTable* m_pRecvTable;
	ClientClass* m_pNext;
	int					m_ClassID; //Managed by the engine.
};

class IBaseClient
{
public:
	virtual void func_1() = 0;
	virtual void func_2() = 0;
	virtual void func_3() = 0;
	virtual void func_4() = 0;
	virtual void func_5() = 0;
	virtual void func_6() = 0;
	virtual void func_7() = 0;
public:
	virtual ClientClass* GetAllClasses() = 0;
};