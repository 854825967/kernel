#ifndef __DMSGLOGINFOMAT_H__
#define __DMSGLOGINFOMAT_H__

#include "DMsgKeyMain.h"
#include "DMsgKeyRoot.h"
#include "DLoginServerMsg.h"
#include "DServerDef.h"
#include "ItemDefines.h"

#pragma pack(push,1)	

/////////////////////////////////////////////////////////
//// 描  述：服务器发给客户端的登陆态消息码
/////////////////////////////////////////////////////////
struct SC_LOGIN_HEAD
{
	WORD    m_wKeyRoot;
	WORD    m_wKeyMain;

	SC_LOGIN_HEAD(WORD wKeyMain)
	{
		m_wKeyRoot = CMD_ROOT_LOGIN;
		m_wKeyMain = wKeyMain;
	}

	SC_LOGIN_HEAD(void)
	{
		m_wKeyRoot = CMD_ROOT_LOGIN;
		m_wKeyMain = 0;
	}
};


/////////////////////////////////////////////////////////
//// 描  述：客户端发给服务器的登陆态消息码
/////////////////////////////////////////////////////////
struct CS_LOGIN_HEAD
{
	WORD    m_wKeyRoot;
	WORD    m_wKeyMain;

	CS_LOGIN_HEAD(WORD wKeyMain)
	{
		m_wKeyRoot = CMD_ROOT_LOGIN;
		m_wKeyMain = wKeyMain;
	}

	CS_LOGIN_HEAD(void)
	{
		m_wKeyRoot = CMD_ROOT_LOGIN;
		m_wKeyMain = 0;
	}
};


/////////////////////////////////////////////////////////
//// 描  述：服务器发给客户端的选择人物态消息码
/////////////////////////////////////////////////////////
struct SC_SELECTACTOR_HEAD
{
	WORD    m_wKeyRoot;
	WORD    m_wKeyMain;

	SC_SELECTACTOR_HEAD(void)
	{
		m_wKeyRoot = CMD_ROOT_SELECTACTOR;
		m_wKeyMain = 0;
	}

	SC_SELECTACTOR_HEAD(WORD wKeyMain)
	{
		m_wKeyRoot = CMD_ROOT_SELECTACTOR;
		m_wKeyMain = wKeyMain;
	}
};	

struct SC_SELECTACTOR_ENTERCODE : public SC_SELECTACTOR_HEAD
{
	DWORD	m_dwEnterCode;

	SC_SELECTACTOR_ENTERCODE(DWORD dwEnterCode)
	{
		m_wKeyMain = ROOTSELECTACTOR_SC_MAIN_ENTERCODE;
		m_dwEnterCode = dwEnterCode;
	}

	SC_SELECTACTOR_ENTERCODE()
	{
		m_wKeyMain = ROOTSELECTACTOR_SC_MAIN_ENTERCODE;
		m_dwEnterCode = 0;
	}
};


/////////////////////////////////////////////////////////
//// 描  述：客户端发给服务器的选择人物态消息码
/////////////////////////////////////////////////////////
struct CS_SELECTACTOR_HEAD
{
	WORD    m_wKeyRoot;
	WORD    m_wKeyMain;

	CS_SELECTACTOR_HEAD(void)
	{
		m_wKeyRoot = CMD_ROOT_SELECTACTOR;
		m_wKeyMain = 0;

	}
};

struct CS_SELECTACTOR_SELECT_HEAD : public CS_SELECTACTOR_HEAD
{
	char	m_szUserName[32 + 1];	//帐号
	char	m_szPassword[32 + 1];	//密码

	DWORD	m_dwSelActorID;			//选择的人物ActorID

	char	szSerialNO[20];			//网卡序列号

	CS_SELECTACTOR_SELECT_HEAD(void)
	{
		m_wKeyMain = ROOTSELECTACTOR_CS_MAIN_SELECT;

		m_dwSelActorID = 0;
		memset(m_szUserName, 0, sizeof(m_szUserName));
		memset(m_szPassword, 0, sizeof(m_szPassword));
		memset(szSerialNO, 0, sizeof(szSerialNO));
	}

	CS_SELECTACTOR_SELECT_HEAD(DWORD dwActorID)
	{
		m_wKeyMain = ROOTSELECTACTOR_CS_MAIN_SELECT;

		m_dwSelActorID = dwActorID;
		memset(m_szUserName, 0, sizeof(m_szUserName));
		memset(m_szPassword, 0, sizeof(m_szPassword));
		memset(szSerialNO, 0, sizeof(szSerialNO));
	}
};

struct CS_SELECTACTOR_MAC_HEAD : public CS_SELECTACTOR_HEAD
{
	char m_MACBuf[128];			//存放客户端随机串的空间
	char RandChar16_V[16];		//存放16字节随机串的空间
	char szRand[16];			//存放16字节客户端标示串

	s64 m_qwUserID;			//帐号的UserID
	DWORD m_dwActorID;			//选择的人物ActorID

	char	szSerialNO[20];		//网卡序列号

	CS_SELECTACTOR_MAC_HEAD()
	{
		m_wKeyMain = ROOTSELECTACTOR_CS_MAIN_MAC;

		m_qwUserID = 0;
		m_dwActorID = 0;
		memset(szSerialNO, 0, sizeof(szSerialNO));
	}
};

/////////////////////////////////////////////////////////
//消  息    码：MAINACTION_MSGID_BAGS_CHG
//描        述：角色的背包改变
//支持流通类型：CSC
/////////////////////////////////////////////////////////
struct SBagsChg
{
	int nLocation;			//背包的位置
	DWORD dwContainer;		//背包容器的指针
	DWORD dwEventID;		//取值：MAINCONTAINER_CSC_ADD、MAINCONTAINER_CSC_REMOVE

	SBagsChg()
	{
		memset(this, 0, sizeof(*this));
	}
};

/////////////////////////////////////////////////////////
//消  息    码：MAINACTION_MSGID_CLEAN_SHOW
//描        述：刷新外观
//支持流通类型：CSC
/////////////////////////////////////////////////////////
struct SC_MSG_UPDATE_SHOW_CONTEXT
{
	BYTE			byUpdateShowResCount;	// 更新外观的数量
	//....多个 SC_MSG_CLEAN_SHOW_CONTEXT::SHOWRES

	SC_MSG_UPDATE_SHOW_CONTEXT()
	{
		memset(this, 0, sizeof(*this));
	}
};
struct SC_MSG_CLEAN_SHOW_CONTEXT
{
	struct SHOWRES
	{
		DWORD		dwGoodsID;		//物品ID
		BYTE		EquipmentType;	// 装备类型(位置)
		DWORD		auraID;         // 装备外观特效
	};

	SHOWRES	stShowRes[EQUIPMENT_SLOT_VISIBLE_END];

	SC_MSG_CLEAN_SHOW_CONTEXT()
	{
		memset(this, 0, sizeof(*this));
		for( BYTE byIdx = 0; byIdx < EQUIPMENT_SLOT_VISIBLE_END; ++byIdx )
		{
			stShowRes[byIdx].EquipmentType = byIdx;
		}
	}
};

//角色身上装备的耐久档次发生改变
struct SC_Endure_Change
{
	char chPos;			//耐久发生变化的装备在装备栏容器中的位置，见DGoodsProp.h的enum EQUIP_POS
	WORD wEndureRank;	//装备当前的耐久档次

	SC_Endure_Change()
	{
		chPos = 0;
		wEndureRank = 0;
	}
};

struct CS_MSG_LOOK_ACTOR_EQUIP_CONTEXT
{
	UID uidMaster;		//观察的人

	CS_MSG_LOOK_ACTOR_EQUIP_CONTEXT()
	{
		uidMaster = INVALID_UID;
	}
};

struct SC_MSG_LOOK_ACTOR_EQUIP_CONTEXT
{
	UID		uidMaster;						//被观察的人
	UID		uidEquip[10];					//装备栏的物品UID
	DWORD	dwContainerID_Equip;			//被观察玩家的装备栏容器ID

	SC_MSG_LOOK_ACTOR_EQUIP_CONTEXT()
	{
		memset(this, 0, sizeof(*this));

		memset(uidEquip, 0xff, sizeof(uidEquip));
		uidMaster = INVALID_UID;
	}
};


#pragma pack(pop)	

#endif

