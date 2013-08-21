#ifndef _DMSGKEYROOT_H__
#define _DMSGKEYROOT_H__

#include <string.h>

#include "GameType.h"

/*
ÏûÏ¢Âë¶¨Òå½á¹¹:
	Ö÷ÏûÏ¢Âë
		×ÓÏûÏ¢Âë
//*/

#pragma pack(push, 1)

// ³¡¾°·şµ½¿Í»§¶ËµÄÏûÏ¢Í·
struct S2CMsgHead
{
	// ¸ùÏûÏ¢Âë
	u16			m_wMainCmd;
	// ×ÓÏûÏ¢Âë
	u16			m_wSubCmd;

	S2CMsgHead()
	{
		memset(this,0,sizeof(*this));
	}

};


enum RootCmd
{
	CMD_ROOT_ERROR			=	0x0001,		// ´íÎó±¨¾¯×¨ÓÃÏûÏ¢Âë
	CMD_ROOT_LOGIN			=	0x0002,		// µÇÂ¼Ì¬ÏûÏ¢Âë
	CMD_ROOT_GATEWAY		=	0x0003,		// Ñ¡ÔñÈËÎïÌ¬ÏûÏ¢Âë
	CMD_ROOT_SELECTACTOR	=	0x0004,		// Ñ¡ÔñÈËÎïÌ¬ÏûÏ¢Âë
	CMD_ROOT_MANAGER		=	0x0005,		// ¹ÜÀíÔ±×¨ÓÃÏûÏ¢Âë£¨Ö»ÓĞµ±·şÎñÆ÷×ªµ½ÔËĞĞÌ¬£¬Ò²¾ÍÊÇËµÑ¡¶¨ÈËÎïºó£¬·şÎñÆ÷·½»á´¦Àí£©
	CMD_ROOT_CHAT			=	0x0006,		// ÁÄÌìÏûÏ¢¹ÜÀíÏûÏ¢Âë£¨Ö»ÓĞµ±·şÎñÆ÷×ªµ½ÔËĞĞÌ¬£¬Ò²¾ÍÊÇËµÑ¡¶¨ÈËÎïºó£¬·şÎñÆ÷·½»á´¦Àí£©
	CMD_ROOT_THING			=	0x0007,		// ÊµÌå¶¨Òå
	CMD_ROOT_INTERACT		=	0x0008,		// ½»»¥ÏµÍ³ÏûÏ¢Âë×¨ÓÃ
	CMD_ROOT_CONTAINER		=	0x0009,		// ÈİÆ÷ÀàÏûÏ¢Âë
	CMD_ROOT_SKEP			=	0x000A,		// ĞéÄâÎïÆ·ÀºÏûÏ¢Âë
	CMD_ROOT_RELATION		=	0x000B,		// ºÃÓÑÏûÏ¢Âë
	CMD_ROOT_TEAM			=	0x000C,		// ×é¶ÓÏûÏ¢Âë
	CMD_ROOT_TRADE			=	0x000D,		// Íæ¼Ò¼ä½»Ò×ÏûÏ¢Âë
	CMD_ROOT_WORK_SKILL		=	0x000E,		// Éú»î¼¼ÄÜÏµÍ³
	CMD_ROOT_GAMEEVENT		=	0x000F,     // ÓÎÏ·ÊÂ¼şÏûÏ¢Âë
	CMD_ROOT_UNION			=	0x0010,		// ¼Ò×åÏûÏ¢Âë
	CMD_ROOT_TITLE			=	0x0011,		// ³ÆºÅÏûÏ¢Âë
	CMD_ROOT_MIND			=	0x0012,		// ÉÌ³ÇÏûÏ¢Âë
	CMD_ROOT_BATTLE			=	0x0013,		// Õ½³¡ÏûÏ¢Âë
	CMD_ROOT_SCRIPT_EVENT	=	0x0014,		// ½Å±¾ÊÂ¼şÏûÏ¢Âë
	CMD_ROOT_ROOM			=	0x0015,		// ·¿¼äÏûÏ¢Âë
	CMD_ROOT_MAX			=	0x0016,		// ×î´óROOTÏûÏ¢Âë
};

/***************************************************************/
///////////////////// ³¡¾°·şµÄ·¿¼äÏûÏ¢Âë/////////////////////
// Ö÷ÏûÏ¢Âë±Ø¶¨ÊÇCMD_ROOT_ROOM
/***************************************************************/
// Ìí¼Óbuff
#define MSG_ROOM_ADD_BUFF									   1
struct SMsgRoomAddBuff_SC
{
	s8		bSitIndex;			// ±¦Ê¯/ÆåÅÌÎ»ÖÃ±àºÅ
	u16		nBuffID;			// buffID
	s64		uidAdd;				// Ìí¼ÓÕß
};

// ÒÆ³ıbuff
#define MSG_ROOM_REMOVE_BUFF									2
struct SMsgRoomRemoveBuff_SC
{
	s8		bSitIndex;			// ±¦Ê¯/ÆåÅÌÎ»ÖÃ±àºÅ
	s64		uidRemove;			// ÒÆ³ıÕß
};

// ·¿¼ä¼ÓÔØ½çÃæ
#define MSG_ROOM_LOADING										3
//  s32	nBattleCreatureID;		// Õ½¶·¹ÖÎïID
struct SMsgRoomLoading_SC
{
	u8		bType;				// ÀàĞÍ
	char		strName[13];		// Ãû³Æ
	u8		bLevel;				// µÈ¼¶
	u32		nBattleTimes;		// Õ½¶·´ÎÊı
	u32		nWinTimes;			// Ê¤Àû´ÎÊı
	u32		bHeadId;			// Íâ¹Ûid
	u8		bPetHeadId;			// ³èÎïÍâ¹Ûid
};

// ³õÊ¼»¯¹Ø¿¨
#define MSG_ROOM_INIT_INSTANCE_INFO								4
struct SMsgRoomInitInstance_SC
{
	s16		nInstanceID;		// ¹Ø¿¨ID
	u16		nFinishFlag;		// Íê³ÉÇé¿ö
	u16		nFirstBattleFlag;	// µÚÒ»´Î´ò¹ÖĞÅÏ¢
};

// ÒÆ¶¯
#define MSG_ROOM_MOVE_ARRAY										5
struct SMsgRoomGotoInstanceStep_CS
{
	s32		nCreatureID;		// ¹ÖÎïID
};

// ÍË³ö
#define MSG_ROOM_EXIT_ROOM										6

// ¸üĞÂ½ø¶È
#define MSG_ROOM_UPDATA_INSTANCE_STEP							7
struct SMsgRoomUpdataInstanceStep_SC
{
	s32		nCreatureID;		// Õ½¶·¹ÖÎïID
	s8		bIsWin;				// Ó®»¹ÊÇÊä
};

// Ë¢ĞÂ·¿¼ä
#define MSG_ROOM_REFRESH_ROOM									8

/***************************************************************/
///////////////////// ³¡¾°·şµÄÊµÌåÀàµÄÏûÏ¢Âë/////////////////////
// Ö÷ÏûÏ¢Âë±Ø¶¨ÊÇCMD_ROOT_THING
/***************************************************************/
// Í¨Öª¿Í»§¶Ë´´½¨ÊµÌå
#define MSG_PROP_CREATEENTITY									1
struct SMsgActionCreateNum_SC
{
	WORD		wCreateNum;			// ´´½¨ÊµÌåµÄÊıÄ¿
	// ...wCreateNum¸ö(SMsgPropCreateEntity_SC+´´½¨ÊµÌåµÄÉÏÏÂÎÄ)
};
// ÏûÏ¢Ìå
struct SMsgPropCreateEntity_SC
{
	s64	uidEntity;
	char		nEntityClass;	// ÊµÌåÀàĞÍ
	char		nIsHero;		// ÊÇ·ñ¿Í»§¶ËÖ÷½Ç£º1£ºÊÇ£¬2£º·ñ
	WORD		wContextLen;	// ´´½¨ÊµÌåÏÖ³¡ÉÏÏÂÎÄ³¤¶È

	// ......................   // ´´½¨ÏÖ³¡
};

///////////////////////////////////////////////////////////////////
// Í¨Öª¿Í»§¶ËÉ¾³ıÊµÌå
#define MSG_PROP_DESTROYENTITY									2
struct SMsgActionDestroyNum_SC
{
	WORD		wDestroyNum;		// Ïú»ÙÊµÌåµÄÊıÄ¿
	// ....wDestroyNum¸öSMsgPropDestroyEntity_SC
};
struct SMsgPropDestroyEntity_SC
{
	s64	uidEntity;
};

///////////////////////////////////////////////////////////////////
// Í¬²½¿Í»§¶ËÊµÌåÊôĞÔ
#define MSG_PROP_UPDATEPROP										3
struct SMsgPropUpdateProp_SC
{
	s64	uidEntity;
	char		nUpdateMode;	// ¸üĞÂÄ£Ê½£º1¡¢µ¥¸öÊıÖµÊôĞÔ¸üĞÂ£¬2£ºÕû¸öÊôĞÔ¸üĞÂ
	//       3£ºµ¥¸ö×Ö·ûÊôĞÔ¸üĞÂ£¬4£º¶à¸öÊıÖµÊôĞÔ¸üĞÂ
	// ......................   // ¸üĞÂÏÖ³¡
};


///////////////////////////////////////////////////////////////////
// ÀäÈ´³õÊ¼»¯Êı¾İ
#define MSG_ACTION_INITCOLD									4
// ÏûÏ¢Ìå
struct SMsgActionInitCold_SC
{
	struct SNodeContext
	{
		BYTE		byClassID;	// ÀäÈ´ÀàID	
		int			nColdID;	// ÀäÈ´ID
		int			nColdTime;	// ÀäÈ´Ê£ÓàÊ±¼ä£¨ºÁÃë£©
	};
	// .................		// ¶à¸öSNodeContext
};


///////////////////////////////////////////////////////////////////

typedef struct tagWSPOINT
{
	WORD x;
	WORD y;
} WSPOINT;

// ÉúÎïÒÆ¶¯ÏûÏ¢
#define MSG_ACTION_MOVE											5

// ¹ÖÎïÒÆ¶¯ÊÂ¼ş
struct SMsgActionMonsterMove_SS
{
	POINT		ptFrom;			// Æğµã
	POINT		ptTo;			// ÖÕµã
};

struct SMsgActionMove_SS
{
	DWORD		dwPathLen;		// Â·¾¶³¤¶È
	// ......................   // Â·¾¶½Úµã£¬WSPOINT * dwPathLen
};
// ÏûÏ¢Ìå(°üÀ¨ËùÓĞÒÆ¶¯Â·¾¶µã)
struct SMsgActionMove_SC
{
	DWORD		dwPathLen;		// Â·¾¶³¤¶È
	// ......................   // Â·¾¶½Úµã£¬WSPOINT * dwPathLen
};

///////////////////////////////////////////////////////////////////
// ¿Í»§¶Ë²Ù×÷ÒÆ¶¯ÏûÏ¢
#define MSG_CS_ACTION_CLIENTOPT_MOVE								6
// ÏûÏ¢Ìå
struct SMsgActionClientOptMove_CS
{
	DWORD		dwPathLen;		// Â·¾¶³¤¶È
	// ......................   // Â·¾¶½Úµã£¬WSPOINT * dwPathLen
};

struct SMsgActionSCHead
{
	s64	uidEntity;			// ObjectµÄguid
};

//////////////////////////////////////////////////////////////////////////
// Í£Ö¹ÒÆ¶¯ÏûÏ¢
#define MSG_ACTION_STOPHERE										7
struct SMsgActionStopHere_SC
{
	WORD		ptHereX;		// X×ø±ê
	WORD		ptHereY;		// Y×ø±ê
	BYTE		byOri;			// ·½Ïò
	BYTE		byForceSync;	// ÊÇ·ñÇ¿ÖÆÀ­ÈË 0:²»Ç¿ÖÆ£¬ 1:Ç¿ÖÆ
};

//////////////////////////////////////////////////////////////////////////
// ´«ËÍÏûÏ¢
#define MSG_ACTION_NEW_WORLD									8
struct SMsgActionNewWorld_SC
{
	DWORD		dwMapId;		// µØÍ¼Id
};

//////////////////////////////////////////////////////////////////////////
// ×´Ì¬¸Ä±ä  ±ÈÈç ÒÆ¶¯µ½ ×øÏÂ
#define  MSG_ACTION_CHANAGEMOVESTYLE							9

/***************************************************************/
/////////////////// Í¨ÓÃÎïÆ·ÀàÏûÏ¢Âë ////////////////////////////
/***************************************************************/
// ½»»»ÎïÆ·
#define MSG_ACTION_SWAP_ITEM									10
struct SMsgActionSwapItem_CS
{
	BYTE		byDestBag;	// Ä¿±ê±³°ü±àºÅ
	BYTE		byDestSlot;	// Ä¿±ê±³°üÖĞµÄ¸ñ×Ó
	BYTE		bySrcBag;	// Ô´±³°ü±àºÅ
	BYTE		bySrcSlot;	// Ô´±³°üÖĞµÄ¸ñ×Ó
};

// ·Ö¸î¶ÑµşÎïÆ·
#define MSG_ACTION_SPLIT_ITEM									11
struct SMsgActionSplitItem_CS
{
	BYTE		bySrcBag;	// Ô´±³°ü±àºÅ
	BYTE		bySrcSlot;	// Ô´±³°üÖĞµÄ¸ñ×Ó
	BYTE		byDestBag;	// Ä¿±ê±³°ü±àºÅ
	BYTE		byDestSlot;	// Ä¿±ê±³°üÖĞµÄ¸ñ×Ó
	BYTE		byCount;	// ÇĞ·ÖÎïÆ·µÄ¸öÊı
};

///////////////////////////////////////////////////////////////////
// ¸úÉÌÈËÂòÎïÆ·
#define MSG_ACTION_BUYGOODS										12
// ÏûÏ¢Ìå
struct SMsgActionBuyGoods_CS
{
	s64		uidNPC;		// NPCÉÌÈË
	DWORD			dwSkepID;	// Í¨ÓÃÎïÆ·ÀºID

	s64		uidGoods;	// ÂòÈëÎïÆ·
	int				nBuyNum;	// Âò¸öÊı

	SMsgActionBuyGoods_CS()
	{
		memset(this, 0, sizeof(*this));
	}
};

///////////////////////////////////////////////////////////////////
// ³öÊÛÎïÆ·
#define MSG_ACTION_SALEGOODS									13
// ÏûÏ¢Ìå
struct SMsgActionSaleGoods_CS
{
	s64		uidGoods;	// ³öÊÛµÄÎïÆ·
	int				nSaleNum;	// ³öÊÛµÄÎïÆ·ÊıÁ¿

	SMsgActionSaleGoods_CS()
	{
		memset(this, 0, sizeof(*this));
	}
};

///////////////////////////////////////////////////////////////////
// µã»÷NPC¶Ô»°
#define MSG_ACTION_MEETNPC										14
// ÏûÏ¢Ìå
struct SMsgActionMeetNPC_CS
{
	s64		uidNPC;		// NPCµÄUID
};

///////////////////////////////////////////////////////////////////
// ÎïÆ·ÁĞ±í
#define MSG_ACTION_LIST_INVENTORY								15
struct SMsgActionListInventory_SC
{
	s64		uidNPC;		// NPCµÄUID
	WORD			wItemCount;	// ÎïÆ·¸öÊı
	// .......................	NPCÉÌÈËÎïÆ·ÁĞ±í
};

struct SMsgActionSCInvItem
{
	WORD			wIndex;		// ÎïÆ·Î»ÖÃ
	int			lItemEntry;	// ÎïÆ·Entry
};

///////////////////////////////////////////////////////////////////
// Ìí¼Óbuff
#define MSG_ACTION_WORLD_OBJECT_ADD_BUFF						16
struct SMsgActionWorldObjectAddBuff_SC
{
	//DWORD			dwIndex;				// Ë÷Òı	
	u16				dwBuffId;				// buff ID	
	s32				dwTime;					// Ê£ÓàÊ±¼ä
	s64		uidAdd;					// Ìí¼ÓÕß
};

// Ìí¼Óbuff
#define MSG_ACTION_WORLD_OBJECT_REMOVE_BUFF						17
struct SMsgActionWorldObjectRemoveBuff_SC
{
	//DWORD			dwIndex;		// Ë÷Òı	
	u16				dwBuffId;				// buff ID	
	s64		uidRemove;				// É¾³ıÕß
};

/////////////////////////////////////////////////////////
//// Ãè  Êö£º·şÎñÆ÷·¢¸ø¿Í»§¶ËµÄÔËĞĞÌ¬ÏûÏ¢Âë
/////////////////////////////////////////////////////////
// ·şÎñÆ÷·¢¸ø¿Í»§¶ËµÄÏûÏ¢Í·
struct SC_THING_HEAD : public S2CMsgHead
{
	SC_THING_HEAD(void)
	{
		m_wMainCmd = CMD_ROOT_THING;
		m_wSubCmd = 0;
	}
};

///////////////////////////////////////////////////////////////////
//·¢²¼¶à¸öË½ÓĞthing
#define MSG_ACTION_MAIN_PRIVATE_MULTI							18
// ·şÎñÆ÷Í¨¹ıROOTTHING_SC_MAIN_PRIVATE_MULTI·¢¸ø¿Í»§¶ËµÄÏûÏ¢Í·
struct SC_THING_PRIVATE_MULTI_HEAD : public SC_THING_HEAD
{
	WORD	m_wThingClassID;		//´ò°üµÄThingÀàĞÍ
	WORD	m_wNum;					//ThingµÄ¸öÊı

	//... m_wNum¸ö: UID + wLen + ThingÊı¾İ

	SC_THING_PRIVATE_MULTI_HEAD(void)
	{
		m_wSubCmd = MSG_ACTION_MAIN_PRIVATE_MULTI;

		m_wThingClassID = 0;
		m_wNum = 0;
	}
};


///////////////////////////////////////////////////////////////////
// Ñ§Ï°¼¼ÄÜ£¨¿Í»§¶Ë<-->·şÎñÆ÷£© 
#define MSG_ACTION_UPGRADE_SKILL								19
// ÏûÏ¢Ìå
// s16 nSkillID;


///////////////////////////////////////////////////////////////////
// Ê¹ÓÃ¼¼ÄÜ£¨¿Í»§¶Ë-->·şÎñÆ÷£©
#define MSG_ACTION_USE_SKILL									20
// ¼¼ÄÜ×¼±¸£¨·şÎñÆ÷->¿Í»§¶Ë£©
#define MSG_ACTION_SKILL_PREPARE								21
// ¼¼ÄÜÊÍ·Å£¨·şÎñÆ÷->¿Í»§¶Ë£©
#define MSG_ACTION_SKILL_CAST									22
// ÏûÏ¢Ìå
struct SkillContext
{
	s64	uidTarget;		/// Ê¹ÓÃ¼¼ÄÜÊ±Êó±êµã»÷µÄÎ»ÖÃÉÏµÄÊµÌå¶ÔÏó
	s8			ptTargetTile;	/// Ê¹ÓÃ¼¼ÄÜÊ±Êó±êµã»÷µÄÎ»ÖÃ
	s16			nSkillId;		/// ¼¼ÄÜID

	SkillContext()	
	{
		memset(this, 0, sizeof(SkillContext)); 
	}
};

///////////////////////////////////////////////////////////////////
// È¡Ïû¼¼ÄÜ£¨¿Í»§¶Ë-->·şÎñÆ÷£©
#define MSG_ACTION_SKILL_CANCEL									23

///////////////////////////////////////////////////////////////////
// ¼¼ÄÜÖĞ¶Ï£¨·şÎñÆ÷->¿Í»§¶Ë£©
#define MSG_ACTION_BREAK_SKILL									24
// ÏûÏ¢Ìå
struct SMsgActionSkillResult_SC
{
	int			result;			/// ¼¼ÄÜ½á¹û
};

///////////////////////////////////////////////////////////////////
// ÉËº¦£¨·şÎñÆ÷->·şÎñÆ÷£©
#define MSG_ACTION_DAMAGE										25
// ÏûÏ¢Ìå

///////////////////////////////////////////////////////////////////
// ÖÎÁÆ£¨·şÎñÆ÷->·şÎñÆ÷£©
#define MSG_ACTION_CURE											26
// ÏûÏ¢Ìå

///////////////////////////////////////////////////////////////////
// ÖÎÁÆ£¨·şÎñÆ÷->¿Í»§¶Ë£©
#define MSG_ACTION_PREPARE_DAMAGE								27
// ÖÎÁÆ£¨·şÎñÆ÷->¿Í»§¶Ë£©
#define MSG_ACTION_PREPARE_CURE									28

// ¸üĞÂÍæ¼ÒÍâ¹Û×ÊÔ´
#define MSG_ACTION_PLAYER_CLEAN_SHOW							29
// ³¡¾°·ş
// SC_MSG_CLEAN_SHOW_CONTEXT

// ¹ÖÎï»òÓ¶±øËÀÍö
#define MSG_ACTION_DIE											30
struct SMsgActionDie_SC
{
	s64		uidMuderer;		//Ä±É±ÕßµÄuid
};

// Í¨Öª×Ô¼º´´½¨±³°ü²¿¼şÏûÏ¢
#define MSG_ACTION_BUILDPACKET									31

// Í¨Öª×Ô¼º´´½¨×°±¸À¸²¿¼şÏûÏ¢
#define MSG_ACTION_BUILDEQUIPPACKET								32

///////////////////////////////////////////////////////////////////
// Ê¹ÓÃÒ©Æ·
#define MSG_ACTION_USELEECHDOM									33
// ÏûÏ¢Ìå
struct SMsgActionUseLeechdom_SS
{	
	s64	uidLeechdom;	// Ò©Æ·uid
};

///////////////////////////////////////////////////////////////////
#define MSG_ACTION_COLD_WORK									34
// ÀäÈ´Í¨Öª£¨·şÎñÆ÷->¿Í»§¶Ë£©
struct SMsgActionColdWork_SC
{
	DWORD	dwClassID;		// ÀäÈ´´óÀà£¨¼¼ÄÜ£¬ÎïÆ·£¬ÁÄÌìµÈ£©
	DWORD	dwColdID;		// ÀäÈ´ID
	s32		nColdTime;		// ÀäÈ´Ê£ÓàÊ±¼ä£¨ºÁÃë£©
};
// ÁìÈ¡ÎïÆ·£¨¿Í»§¶Ë->·şÎñÆ÷£©
struct SMsgActionColdWork_CS
{
	DWORD	dwClassID;		// ÀäÈ´´óÀà£¨¼¼ÄÜ£¬ÎïÆ·£¬ÁÄÌìµÈ£©
	DWORD	dwColdID;		// ÀäÈ´ID	
};



//////////////////////////////////////////////////////////////////////////
// ±£´æ¼¼ÄÜ¿ì½İÀ¸
#define MSG_ACTION_SHORTCUT										35
struct CS_MSG_SHORTCUT_CONTEXT
{
	BYTE	byHeroIndex;	//Ó¶±øINDEX
	BYTE	byIndex;		//¿ì½İÀ¸Ë÷Òı
	DWORD	dwSkillInfo;	//(0~2Î»)¼¼ÄÜ»òÎïÆ·Id 3Î»(1:±íÊ¾¼¼ÄÜ 0:±íÊ¾ÎïÆ·)

	CS_MSG_SHORTCUT_CONTEXT()
	{
		memset(this, 0, sizeof(*this));
	}
};

///////////////////////////////////////////////////////////////////
// CS : ÇëÇó¸´»îµã¸´»î
// SC : ¸´»îµ¹¼ÆÊ±
#define MSG_ACTION_ORIGINAL_RELIVE								36
// ÏûÏ¢Ìå
struct SMsgActionOriginalRelive_SC
{
	POINT				coordinate;				//×ø±ê
	int					nReliveCountDown;		//ĞèÒªµÈ´ı×ÜÃëÊı
	DWORD				dwReliveMapID;			//µØÍ¼ID
	int					nTimes;					//´ÎÊı

};

// ¿Í»§¶Ë¸´»îµã¸´»îÇëÇó
struct SMsgActionOriginalRelive_CS
{

};

///////////////////////////////////////////////////////////////////
// ÒÆ³ıÀäÈ´
#define MSG_ACTION_COLD_REMOVE									37
// ÀäÈ´Í¨Öª£¨·şÎñÆ÷->¿Í»§¶Ë£©
struct SMsgActionColdRemove_SC
{
	DWORD	dwClassID;		// ÀäÈ´´óÀà£¨¼¼ÄÜ£¬ÎïÆ·£¬ÁÄÌìµÈ£©
	DWORD	dwColdID;		// ÀäÈ´ID
};

///////////////////////////////////////////////////////////////////
// ÊµÌå¸´»î
#define MSG_ACTION_RELIVE										38
// ÏûÏ¢Ìå
struct SMsgActionRelive_SC
{
	//.................
};

///////////////////////////////////////////////////////////////////
// ´ò¿ª±¦Ïä
#define MSG_ACTION_OPENBOX										39
// ÏûÏ¢Ìå
struct SMsgActionOpenBox_CS
{
	s64		uidBox;		// ±¦Ïä
};

///////////////////////////////////////////////////////////////////
// ¹Ø±Õ±¦Ïä
#define MSG_ACTION_CLOSEBOX										40
// ÏûÏ¢Ìå
struct SMsgActionCloseBox_CS
{
	s64		uidBox;		// ±¦Ïä
};

///////////////////////////////////////////////////////////////////
// µã»÷Æì±êÊµÌå
#define MSG_ACTION_CLICKMAST									41
// ÏûÏ¢Ìå
struct SMsgActionClickMast_CS
{
	s64		uidMast;		// Æì±êµÄuid
};

// ¼¼ÄÜ³õÊ¼»¯£¨·şÎñÆ÷->¿Í»§¶Ë£©
#define MSG_ACTION_SKILL_INIT									42

/////////////////////////////////////////////////////////////////
// ´´½¨ÎïÆ·Àº
#define MSG_ACTION_CREATESKEP									43
// ÏÖ³¡Îª SBuildSkepClientContext

// ¼¼ÄÜÊ§°ÜĞÅÏ¢£¨·şÎñÆ÷->¿Í»§¶Ë£©
#define MSG_ACTION_SKILL_FAILED									44
// ÏûÏ¢Ìå
struct SMsgActionSkillFaile_SC
{
	DWORD		dwResult;			// Ê§°ÜÔ­Òò
};

// ¼¼ÄÜÊ§°ÜĞÅÏ¢£¨·şÎñÆ÷->¿Í»§¶Ë£©
#define MSG_ACTION_CHANGE_FIGHT_STATUS							45
// ÏûÏ¢Ìå
struct SMsgActionChangeFightStatus_SC
{
	s64	guid;				// Ä¿±ê
	BOOL		bStatus;			// ¸Ä±äºó×´Ì¬
};

// ¸üĞÂ¼¼ÄÜµã£¨·şÎñÆ÷->¿Í»§¶Ë£©
#define MSG_ACTION_UPDATA_SKILL_POINT							46

// ÇĞ»»×´Ì¬£¨CS or SC£©
#define MSG_ACTION_SWITCHSTATE									47
// ÏûÏ¢Ìå
struct SMsgActionSwitchState_SC
{
	SMsgActionSwitchState_SC()
	{
		byState = 0;
		byLastState = 0;
		uidGood = 0;
	}
	BYTE		byState;			// ×´Ì¬(ÒÆ¶¯¡¢Õ¾Á¢¡¢´ò×øµÈ×´Ì¬)
	BYTE		byLastState;		// Ö®Ç°µÄ×´Ì¬
	s64	uidGood;			// ÎïÆ·ID£¨ÓÃÓÚ×´Ì¬¸Ä±äÎªÆï³Ë×´Ì¬Ê±£¬´«¸ø¿Í»§¶ËµÄÎïÆ·ID£©
};

struct SMsgActionSwitchState_CS
{
	SMsgActionSwitchState_CS()
	{
		byState = 0;
		/// uidGood = 0;
	}
	BYTE		byState;			// ×´Ì¬(ÒÆ¶¯¡¢Õ¾Á¢¡¢´ò×øµÈ×´Ì¬)
	/// s64	uidGood;			// ÎïÆ·ID£¨ÓÃÓÚ×´Ì¬¸Ä±äÎªÆï³Ë×´Ì¬Ê±£¬´«¸ø¿Í»§¶ËµÄÎïÆ·ID£©
};

// Í¨Öª¿Í»§¶Ë²¥ÒôĞ§
#define MSG_ACTION_PLAYSOUND									48
struct SMsgActionPlaySound_SS
{
	DWORD		dwSoundId;			// ÒôĞ§Id
	BYTE		bySendType;			// 0:µ¥²¥ 1:¾Å¹¬¸ñ¹ã²¥
};

struct SMsgActionPlaySound_SC
{
	DWORD		dwSoundId;			// ÒôĞ§Id
};

// Ê¹ÓÃ¼¼ÄÜ£¨·şÎñÆ÷-->·şÎñÆ÷£©
#define MSG_ACTION_USE_SKILL_UNCHECK							49
// ÏûÏ¢Ìå
// struct SkillContext2

//////////////////////////////////////////////////////////////////////////
//////////////////////////////ContianerServer///////////////////////////////
//////////////////////////////////////////////////////////////////////////
// ÈİÆ÷·şÎñÆ÷Ïà¹ØÏûÏ¢°üÍ·½á¹¹
struct SContainerMsgHead : public S2CMsgHead
{
	SContainerMsgHead(WORD wMsg)
	{
		m_wMainCmd = CMD_ROOT_CONTAINER;
		m_wSubCmd = wMsg;
	}
};

// ·şÎñÆ÷Í¨¹ıROOTTHING_SC_MAIN_ACTION·¢¸ø¿Í»§¶ËµÄÏûÏ¢Í·
struct SC_THING_ACTION_HEAD : public SC_THING_HEAD
{
	s64		m_uidThing;

	SC_THING_ACTION_HEAD(void)
	{
		m_wMainCmd = CMD_ROOT_THING;
		m_wSubCmd = 0;
		m_uidThing = 0;
	}
};

struct SMsgSkepCSCHead
{
	DWORD			dwSkepID;	// ĞéÄâÎïÆ·À¸Id
};

// Íæ¼Ò¼ä½»Ò×·şÎñÆ÷Ïà¹ØÏûÏ¢°üÍ·½á¹¹
struct STradeMsgHead : public S2CMsgHead
{
	STradeMsgHead(WORD wMsg)
	{
		m_wMainCmd = CMD_ROOT_TRADE;
		m_wSubCmd = wMsg;
	}
};

///////////////////////////////////////////////////////////////////
// ÇĞ»»PKÄ£Ê½
#define MSG_ACTION_SWITCHPKMODE									50
// ÏûÏ¢Ìå
struct SMsgActionSwitchPKMode_CS
{
	int				nPKMode;	// PKÄ£Ê½
};

struct SMsgActionSwitchPKMode_SC
{
	int				nPKMode;	// PKÄ£Ê½
};

///////////////////////////////////////////////////////////////////
// ĞŞ¸ÄPKÃû×ÖÑÕÉ«
#define MSG_ACTION_PKNAMECOLOR									51
// ÏûÏ¢Ìå
struct SMsgActionPKNameColor_SC
{
	BYTE				nPKColor;	// Ãû×ÖÑÕÉ«
};

///////////////////////////////////////////////////////////////////
// ĞŞÀí×°±¸
#define MSG_ACTION_REPAIREQUIP									52
// ÏûÏ¢Ìå
struct SMsgActionRepairEquip_CS
{
	s64		uidEquip;		// ×°±¸
	// Èç¹ûÎªINVALID_UID£¬Ôò±íÊ¾ĞŞÀí×°±¸À¸ËùÓĞ×°±¸

	BYTE			byPacketSkep;	// °ü¹üÀ¸
	// Èç¹ûÎª1£¬Ôò±íÊ¾×°±¸ÔÚ°ü¹üÀ¸£¬·´Ö®×°±¸À¸
};

///////////////////////////////////////////////////////////////////
// npc Í·¶¥±êÊ¶·û
#define MSG_ACTION_NPC_HEAD_FLAG								53
struct SMsgActionNpcHeadFlag_SC
{
	/************************************************************************
	ÓÅÏÈ¼¶	ÏÔÊ¾ÀàĞÍ	ËµÃ÷
	1£¨¸ß£©	»ÆÉ«ÎÊºÅ	¿É½»¸¶Ò»°ãÈÎÎñ
	2			À¶É«ÎÊºÅ	¿É½»¸¶Ã¿ÈÕÈÎÎñ
	3			»ÆÉ«Ì¾ºÅ	¿É»ñÈ¡Ò»°ãÈÎÎñ
	4			À¶É«Ì¾ºÅ	¿É»ñÈ¡Ã¿ÈÕÈÎÎñ
	5			°×É«ÎÊºÅ	Î´Íê³ÉÈÎÎñ
	************************************************************************/
	enum
	{
		TASKSTATE_NORMAL = 0,						//
		TASKSTATE_CAN_COMPLETE,					// ¿ÉÍê³É; ¿É½»¸¶Ò»°ãÈÎÎñ
		TASKSTATE_CAN_COMPLETE_DAILY,		// ¿É½»¸¶Ã¿ÈÕÈÎÎñ
		TASKSTATE_CAN_ACCEPTE,						// ¿É½Ó; ¿É»ñÈ¡Ò»°ãÈÎÎñ
		TASKSTATE_CAN_ACCEPTE_DAILY,			// ¿É½ÓÃ¿ÈÕÈÎÎñ; 
		TASKSTATE_ACCEPTED,							// ÒÑ¾­½Ó
		TASKSTATE_NUM,				
	};

	s64	uidMonsterID;		// ¹ÖÎï/NpcµÄguid
	BYTE		byState;						// È¡Öµ·¶Î§£º[TASKSTATE_NORMAL,TASKSTATE_NUM)

	SMsgActionNpcHeadFlag_SC()
	{
		memset(this,0,sizeof(SMsgActionNpcHeadFlag_SC));
	}
};

///////////////////////////////////////////////////////////////////
// ¿ªÊ¼½ø¶ÈÌõ×´Ì¬
#define MSG_ACTION_STARTPROGRESS								54
// ÏûÏ¢Ìå
struct SMsgActionStartProgress_CS
{
	BYTE byBarType;					// ½ø¶ÈÌõÀàĞÍ
	int nTime;						// ³ÖĞøÊ±¼ä
	char szName[32];				// ½ø¶ÈÌõµÄÃû×Ö

};
struct SMsgActionStartProgress_SC
{
	s64 m_uidMaster;			// ½ø¶ÈÌõµÄÖ÷ÈË
	BYTE	 byBarType;				// ½ø¶ÈÌõÀàĞÍ
	int	 lActionId;				// ¶¯×÷Id
	int nTime;						// ³ÖĞøÊ±¼ä
	char szName[32];				// ½ø¶ÈÌõµÄÃû×Ö
	char szParentWndName[64];		// ¸¸´°¿ÚµÄÃû×Ö
	int x;							// ´°¿Ú×óÉÏx×ø±ê£¨ÏñËØµ¥Î»£©
	int y;							// ´°¿Ú×óÉÏy×ø±ê£¨ÏñËØµ¥Î»£©
	int width;						// ´°¿ÚµÄ¿í£¨ÏñËØµ¥Î»£©
	int height;						// ´°¿ÚµÄ¸ß£¨ÏñËØµ¥Î»£©
};

///////////////////////////////////////////////////////////////////
// ½áÊø½ø¶ÈÌõ×´Ì¬
#define MSG_ACTION_ENDPROGRESS									55
// ÏûÏ¢Ìå
struct SMsgActionEndProgress_CS
{

};

struct SMsgActionEndProgress_SC
{
	s64 m_uidMaster;
	int		 nEndReason;			// ½áÊøÔ­Òò
};

// ³¡¾°ºĞ×Ó×´Ì¬
#define MSG_ACTION_BOX_STATE_FLAG								56
struct SMsgActionBoxStateFlag_SC
{
	enum
	{
		ABSF_INVAILD = 0,		// Ê§Ğ§×´Ì¬
		ABSF_ACTIVE,			// ¼¤»î×´Ì¬
		ABSF_NUM,
	};
	
	int		lBoxID;			// ³¡¾°ºĞ×ÓµÄguid
	int		lType;			// ÀàĞÍ
	BYTE		byState;		// È¡Öµ·¶Î§£º[ABSF_INVAILD,ABSF_NUM)

	SMsgActionBoxStateFlag_SC()
	{
		memset(this,0,sizeof(SMsgActionBoxStateFlag_SC));
	}
};

// Ê¹ÓÃÒ©Æ·½á¹û
#define MSG_ACTION_USELEECHDOMRESULT								57
struct SMsgActionUseLeechdomResult_SC
{
	enum UseLeechdomResult
	{
		USELEECHDOMRESULT_FAIL,		// Ê¹ÓÃÒ©Æ·Ê§°Ü
		USELEECHDOMRESULT_SUCCESS,	// Ê¹ÓÃÒ©Æ·³É¹¦
	};
	BYTE		byResult;		// Ê¹ÓÃÒ©Æ·½á¹û
};

// ´íÎóÂëÍ¨µÀ
#define MSG_ACTION_ERRORCODECHUNNEL									58
struct SMsgActionErrorCodeChunnel_SC
{
	BYTE		byErrorType;		// ´íÎóÀàĞÍ
	WORD		wErrorCode;			// ´íÎóÂë
	WORD		wErrorDespLen;		// ´íÎóÃèÊö×Ö·û´®³¤¶È
	//....´íÎóÃèÊö
};

#define MSG_ACTION_CHANGELOCATION_FOR_SKILL							59
struct SMsgActionChangeLocationForSkill_SC
{
	POINT		ptTargetPos;		// Ä¿±êÎ»ÖÃ
	BYTE		byFlag;				// ¼¼ÄÜ¸Ä±äÎ»ÖÃÀàĞÍ
	int			nCostTime;			// ÒÆ¶¯ÖÁÄ¿±êµãËùĞèÊ±¼ä
};

///////////////////////////////////////////////////////////////////
// ¶ªÎïÆ·
#define MSG_ACTION_THROWGOODS										60
// ÏûÏ¢Ìå
struct SMsgActionThrowGoods_CS
{
	s64		uidGoods;
};

//////////////////////////////////////////////////////////////////
// Ğ¡ÍË,ÇĞ»»½ÇÉ«
#define MSG_ACTION_CHANGEACTOR										61
// ÏûÏ¢Ìå
struct SMsgActionChangeActor_CS
{

};
//Íæ¼ÒĞ¡ÍËµÄÏûÏ¢½á¹¹
struct SC_Select : public SC_THING_HEAD
{
	DWORD ValidationCode[4];		//ÑéÖ¤Âë£¬ÓÃÓÚµÇÂ½·ş

	SC_Select()
	{
		m_wSubCmd = MSG_ACTION_CHANGEACTOR;
		memset(ValidationCode, 0, sizeof(ValidationCode));
	}
};


//////////////////////////////////////////////////////////////////
// ÉÁµçÁ´
#define MSG_ACTION_SKILL_CAST_CHAIN									62
// ÏûÏ¢Ìå
struct SkillChainContext
{
	s64	uidTarget;		/// Ê¹ÓÃ¼¼ÄÜÊ±Êó±êµã»÷µÄÎ»ÖÃÉÏµÄÊµÌå¶ÔÏó
	POINT		ptTargetTile;	/// Ê¹ÓÃ¼¼ÄÜÊ±Êó±êµã»÷µÄÎ»ÖÃ
	s16			skillId;		/// ¼¼ÄÜID
	int			result;			/// ¼¼ÄÜ½á¹û

	BYTE		bChainCount;	/// ÉÁµçÁ´Ä¿±êÊıÁ¿
	// ..... s64	uidChainTarget; /// ÉÁµçÁ´Ä¿±ê ¶à¸ö

	SkillChainContext()	
	{
		uidTarget		= 0;
		ptTargetTile.x	= 0;
		ptTargetTile.y	= 0;
		skillId			= 0;
		result			= 0;
		bChainCount		= 0;
	}
};

//////////////////////////////////////////////////////////////////////////
// Ñ¯ÎÊÊÇ·ñ½ÓÊÜ±ğÈË¸´»î
#define MSG_ACTION_ASK_RELIVE										63
// ÏûÏ¢Ìå
struct SMsgActionAskRelive
{
	s64		uidDoctor;		// Ò½ÉúµÄGUID
	int				nFlagIndex;		// ¸´»î±êÊ¶

	SMsgActionAskRelive(void)
	{
		memset( this, 0, sizeof(SMsgActionAskRelive) );
	}
};

// ´ğ¸´ÊÇ·ñ½ÓÊÜ¸´»î
#define MSG_ACTION_ANSWER_RELIVE									64
// ÏûÏ¢Ìå
struct SMsgActionAnswerRelive
{
	BYTE			byAnswer;		// 1:½ÓÊÜ 0:¾Ü¾ø
	int				nFlagIndex;		// ¸´»î±êÊ¶

	SMsgActionAnswerRelive(void)
	{
		memset( this, 0, sizeof(SMsgActionAnswerRelive) );
	}
};

//////////////////////////////////////////////////////////////////////////
// ¸½¼ÓÊôĞÔÆ®×Ö£¨·şÎñÆ÷->¿Í»§¶Ë£©
#define MSG_ACTION_FEW_TEXT											65
// ÏûÏ¢Ìå
struct MsgActionFewText
{
	s64			tarUID;			/// ĞèÒªÆ®×ÖµÄÈË
	WORD				ProNum;			/// ÊôĞÔID
	int					nValue;			/// ÊıÖµ
};


//////////////////////////////////////////////////////////////////////////
// ÖØÖÃ¸±±¾
#define MSG_ACTION_RESET_ECTYPE										66
// ÏûÏ¢Ìå
struct MsgActionResetEctype
{
	// ÔİÎŞ³ÉÔ±
};

//////////////////////////////////////////////////////////////////////////
// ÀäÈ´Í¨Öª£¨·şÎñÆ÷->¿Í»§¶Ë£©
#define MSG_ACTION_SHARE_COLD_WORK									67
//struct SMsgActionColdWork_SC

//////////////////////////////////////////////////////////////////////////
// È¡ÏûĞ¡ÍË
#define MSG_ACTION_CANCEL_CHANGEACTOR								68
// ÏûÏ¢Ìå
struct SMsgActionCancelChangeActor_CS
{

};

//////////////////////////////////////////////////////////////////////////
// Ğ¡ÍË¿ªÊ¼µ¹¼ÆÊ±
#define MSG_ACTION_CHANGEACTOR_INTERVAL								69
// ÏûÏ¢Ìå
struct SMsgActionChangeActorInterval_CS
{

};

//////////////////////////////////////////////////////////////////////////
// Á¢¼´Ğ¡ÍË
#define MSG_ACTION_CHANGEACTOR_RIGHTNOW								70
// ÏûÏ¢Ìå
struct SMsgActionChangeActorRightNow_CS
{

};

//////////////////////////////////////////////////////////////////////////
// ·¢ËÍnpcĞÅÏ¢
#define MSG_ACTION_SYNC_NPC_INFO									71
// ÏûÏ¢Ìå
struct SMsgActionSyncNpcInfo_CS
{
	struct SNpcInfo
	{
		int	lID; 
		POINT	position;
		char	szName[32];	

		SNpcInfo()
		{
			memset(this,0,sizeof(*this));
		}
	};

	BYTE	byPackNum;		// ±¾´Î·¢ËÍ×ÜÅúÊı
	BYTE	byPackIndex;	// µ±Ç°µÚ¼¸Åú
	int	lMapID;			// µØÍ¼ID
	BYTE	byNum;			// npc ÊıÁ¿
	// ...  npc_data;		// Êı¾İ
};

//////////////////////////////////////////////////////////////////////////
// ´ò¿ªNpc¼¼ÄÜÑ§Ï°Ãæ°å
#define MSG_OPEN_NPC_TRAINSKILL										72
// ÏûÏ¢Ìå
struct SMsgActionTalkToTrainSkillNpc_SC
{
	s64	llNpcUID;		// Npc guid
};

//////////////////////////////////////////////////////////////////////////
// Í¨¹ıNPCÑ§Ï°¼¼ÄÜ£¨·şÎñÆ÷-->¿Í»§¶Ë£©
#define MSG_LEARN_SKILL_FROM_NPC									73
// ÏûÏ¢Ìå
struct SMsgActionLearnSkillFromNpc_CS
{
	s64	llNpcUID;		// Npc guid
	WORD		wSkillID;		// ¼¼ÄÜid
};

//////////////////////////////////////////////////////////////////////////
// ÒÅÍü¼¼ÄÜ£¨·şÎñÆ÷-->¿Í»§¶Ë£© 
#define MSG_ACTION_FORGET_SKILL										74
// ÏûÏ¢Ìå
// WORD wSkillId;		/// ¼¼ÄÜID

//////////////////////////////////////////////////////////////////////////
// ÒÅÍüËùÓĞÇ±ÄÜ£¨·şÎñÆ÷-->¿Í»§¶Ë£© 
#define MSG_ACTION_FORGET_ALL_SKILL									75
// ÏûÏ¢Ìå£¨ÎŞ£©


// ÉèÖÃÄ¿±êGUID
#define MSG_ACTION_SET_TARGET										76
// ÏûÏ¢Ìå
struct SMsgActionSetTarget
{
	s64		uidTarget;

	SMsgActionSetTarget(void)
	{
		memset( this, 0, sizeof(SMsgActionSetTarget) );
	}
};

//////////////////////////////////////////////////////////////////////////
// ÉèÖÃÕÙ»½ÊŞÄ£Ê½£¨·şÎñÆ÷<-->¿Í»§¶Ë£© 
#define MSG_ACTION_CALLANIMAL_AIMODE								77
// ÏûÏ¢Ìå
// BYTE bMode;			// AIÄ£Ê½

//////////////////////////////////////////////////////////////////////////
// ÕÙ»½ÊŞ¹¥»÷£¨¿Í»§¶Ë-->·şÎñÆ÷£© 
#define MSG_ACTION_CALLANIMAL_ATTACK								78
// ÏûÏ¢Ìå
// s64	tarUID;    // Ä¿±êGuid

//////////////////////////////////////////////////////////////////////////
// ½âÉ¢Ä³Ö»ÕÙ»½ÊŞ£¨¿Í»§¶Ë-->·şÎñÆ÷£© 
#define MSG_ACTION_FREE_CALLANIMAL									79
// ÏûÏ¢Ìå
// s64	tarUID;    // ÕÙ»½ÊŞGuid

///////////////////////////////////////////////////////////////////
// µã»÷³¡¾°Îï¼ş
#define MSG_ACTION_CLICK_GAMEOBJ									80
// ÏûÏ¢Ìå
struct SMsgActionClickGameObj_CS
{
	s64		uidGameObj;		// GameObjµÄUID

	SMsgActionClickGameObj_CS(void)
	{
		memset( this, 0, sizeof(*this) );
	}
};

//////////////////////////////////////////////////////////////////////////
// Í¬²½·şÎñÆ÷Ê±ÖÓ
#define MSG_ACTION_SYNC_SERVERTICKS									81
// ÏûÏ¢Ìå
struct SMsgActionSyncServerTicks_SC
{
	DWORD			dwServerTicks;	// Íæ¼ÒµÇÂ¼ºóÁ÷Ê§µÄÊ±¼ä(ms)

	SMsgActionSyncServerTicks_SC(void)
	{
		memset( this, 0, sizeof(*this) );
	}
};

//////////////////////////////////////////////////////////////////////////
// Ìí¼Óbuff
#define MSG_ACTION_WORLD_OBJECT_INIT_BUFF							82

// ²é¿´±ğÈË×°±¸£¨·şÎñÆ÷->¿Í»§¶Ë£©
#define MSG_ACTION_LOOK_ACTOR_EQUIP									83

// ÇëÇó´´½¨¿Í»§¶Ë²Ö¿â²¿¼şÏûÏ¢£¨¿Í»§¶Ë->·şÎñÆ÷£©
// Í¨Öª×Ô¼º´´½¨²Ö¿â²¿¼şÏûÏ¢£¨·şÎñÆ÷->¿Í»§¶Ë£©
#define MSG_ACTION_BUILDSTORAGE										84

// Í¨Öª¿Í»§¶Ë´ò¿ª²Ö¿â½çÃæ£¨·şÎñÆ÷->¿Í»§¶Ë£©
#define MSG_ACTION_OPENSTORAGE										85

// ¸üĞÂÆøµã£¨·şÎñÆ÷->¿Í»§¶Ë£©
#define MSG_ACTION_UPDATA_AIR_POINT									86

// ÕûÀíÆÕÍ¨°ü¹ü(·şÎñÆ÷->¿Í»§¶Ë)
#define MSG_ACTION_SORT_PACKET										87
struct SMsgActionSortedGoodsInfo_CS
{
	s64		uidGoods;		//±»ÖØÅÅµÄÎïÆ·µÄGUID
	BYTE			byPacketIdx;	//ÖØÅÅÖ®ºóÔÚÄÄ¸ö±³°üÖĞ
	BYTE			byLoc;			//ÖØÅÅÖ®ºóÔÚÈİÆ÷ÖĞµÄÎ»ÖÃ
};
struct SMsgActionSortedInfo_CS
{
	BYTE			bySortedNum;	//ÖØÅÅÎïÆ·µÄÊıÁ¿
};

// ÕûÀíÈÎÎñ°ü¹ü(·şÎñÆ÷->¿Í»§¶Ë)
#define MSG_ACTION_SORT_TASK_PACKET									88

// ÇëÇóÑÓ³ÙÉ¾³ıÊµÌå(·şÎñÆ÷->·şÎñÆ÷)
#define MSG_ACTION_RELAY_DELETE_ENTITY								89
struct SMsgActionRelayDeleteEntity_SS
{
	s64		uidEntity;			// ÊµÌåUID
};

//¹ÖÎïÎŞÊÓÕÏ°­ÒÆ¶¯
#define MSG_ACTION_IGNORE_OBSTALE_MOVE								113


////////////////////////////////////////////////////////////////////////////////////
/// ³èÎïÏà¹Ø
/// 
/// Í¨Öª×Ô¼º´´½¨³èÎï×°±¸À¸²¿¼şÏûÏ¢
/// ÏûÏ¢±¾ÉíÎªS2CMsgHead
#define MSG_ACTION_BUILD_PET_EQUIPPACKET							114
struct SMsgActionBuildHeroEquipPacket_SC
{
	s64		uidHero;		// Ó¶±øUID
};

/// ³èÎïÁĞ±í£¨·şÎñÆ÷->¿Í»§¶Ë£©
#define MSG_ACTION_PET_DATA_LIST									115

/// ³èÎï²Ù×÷£¨¿Í»§¶Ë->·şÎñÆ÷£¬·şÎñÆ÷->¿Í»§¶Ë£©£¬°üÀ¨ÁË³öÕ½¡¢ĞİÏ¢¡¢·ÅÆú
#define MSG_ACTION_PET_OP											116

/// ³èÎïĞŞ¸ÄÃû³Æ£¨¿Í»§¶Ë->·şÎñÆ÷£¬·şÎñÆ÷->¿Í»§¶Ë£©
#define MSG_ACTION_PET_MOD_NAME										117

/// ³èÎïĞŞ¸ÄÃû³Æ¹ã²¥¸ø¿Í»§¶Ë£¨·şÎñÆ÷->¿Í»§¶Ë£©
#define MSG_ACTION_PET_NAME											118

/// ÉèÖÃ³èÎïAI£¨·şÎñÆ÷->¿Í»§¶Ë
#define MSG_ACTION_SET_PET_AI										119
////////////////////////////////////////////////////////////////////////////////////


////////////////////////////////////////////////////////////////////////////////////

// Ê¹ÓÃ¼¼ÄÜ£¨¿Í»§¶Ë-->·şÎñÆ÷£©
#define MSG_ACTION_USE_SKILL_PET									120

//////////////////////////////////////////////////////////////////////////
// Ñ§Ï°¼¼ÄÜ£¨·şÎñÆ÷-->¿Í»§¶Ë£© 
#define MSG_ACTION_UPGRADE_SKILL_PET								121

//////////////////////////////////////////////////////////////////////////
// ÒÅÍü¼¼ÄÜ£¨·şÎñÆ÷-->¿Í»§¶Ë£© 
#define MSG_ACTION_FORGET_SKILL_PET									122
// ÏûÏ¢Ìå
// int lPetID;			/// ³èÎïID
// WORD wSkillId;		/// ¼¼ÄÜID

//////////////////////////////////////////////////////////////////////////
// ÒÅÍüËùÓĞÇ±ÄÜ£¨·şÎñÆ÷-->¿Í»§¶Ë£© 
#define MSG_ACTION_FORGET_ALL_SKILL_PET								123
// ÏûÏ¢Ìå£¨ÎŞ£©

//////////////////////////////////////////////////////////////////////////
// ÀäÈ´³õÊ¼»¯Êı¾İ
#define MSG_ACTION_INITCOLD_PET										124
// ÏûÏ¢Ìå
//struct SMsgActionInitCold_SC

//////////////////////////////////////////////////////////////////////////
// ÀäÈ´Í¨Öª£¨·şÎñÆ÷->¿Í»§¶Ë£©
#define MSG_ACTION_SHARE_COLD_WORK_PET								125
//struct SMsgActionColdWork_SC

//////////////////////////////////////////////////////////////////////////
// ÀäÈ´Í¨Öª£¨·şÎñÆ÷->¿Í»§¶Ë£©
#define MSG_ACTION_COLD_WORK_PET									126
//struct SMsgActionColdWork_SC

// ¼¼ÄÜ³õÊ¼»¯£¨·şÎñÆ÷->¿Í»§¶Ë£©
#define MSG_ACTION_SKILL_INIT_PET									127


/// ÏâÇ¶Ì××°±¦Ê¯µ½×°±¸ÉÏ£¨¿Í»§¶Ë->·şÎñÆ÷£©
#define MSG_MAKE_SUIT_STONE_EQUIP									128
struct CMsgMakeSuitStoneEquipCmd
{
	s64 uidEquip;			/// ×°±¸UID
	s64 uidStone;			/// Ì××°±¦Ê¯UID

	CMsgMakeSuitStoneEquipCmd()
	{
		uidEquip = 0;
		uidStone = 0;
	}
};

/// ÏâÇ¶Ì××°±¦Ê¯µ½×°±¸ÉÏ½á¹û£¨·şÎñÆ÷->¿Í»§¶Ë£©
#define MSG_RET_MAKE_SUIT_STONE_EQUIP									129
struct CMsgRetMakeSuitStoneEquipCmd
{
	BYTE byRet;					/// ½á¹û£¨0£ºÊ§°Ü£¬1£º³É¹¦£©
	BYTE byTp;					/// ÀàĞÍ£¨0£ºÏâÇ¶£¬1£ºÉı¼¶£¬2£ºÈ¡ÏÂ±¦Ê¯£©

	CMsgRetMakeSuitStoneEquipCmd()
	{
		byRet = 0;
		byTp = 0;
	}
};

/// ÏâÇ¶Ì××°±¦Ê¯½çÃæ´ò¿ª£¨·şÎñÆ÷->¿Í»§¶Ë£©
#define MSG_OPEN_MAKE_SUIT_STONE_EQUIP									130
struct CMsgOpenMakeSuitStoneEquipCmd
{
	BYTE byTp;				/// ÀàĞÍ£¨0£ºÏâÇ¶£¬1£ºÉı¼¶£¬2£ºÈ¡ÏÂ±¦Ê¯£©

	CMsgOpenMakeSuitStoneEquipCmd()
	{
		byTp = 0;
	}
};

/// Ì××°Éı¼¶£¨¿Í»§¶Ë->·şÎñÆ÷£©
#define MSG_UPGRADE_SUIT_EQUIP											131
struct CMsgUpgradeSuitEquipCmd
{
	s64 uidEquip;			/// ×°±¸UID

	CMsgUpgradeSuitEquipCmd()
	{
		uidEquip = 0;
	}
};

/// Ì××°±¦Ê¯È¡ÏÂ£¨¿Í»§¶Ë->·şÎñÆ÷£©
#define MSG_TAKE_DOWN_SUIT_STONE										132
struct CMsgTakeDownSuitStoneCmd
{
	s64 uidEquip;			/// ×°±¸UID

	CMsgTakeDownSuitStoneCmd()
	{
		uidEquip = 0;
	}
};

// ½âÌå£¨¿Í»§¶Ë-->·şÎñÆ÷£©
#define MSG_ACTION_RELEASE_PET											133

// ¿ªÆôÌì¸³Ïµ£¨¿Í»§¶Ë<-->·şÎñÆ÷£©
#define MSG_ACTION_UPDATA_QN_GROUP										134
// ½á¹¹Ìå 
// BYTE	 byGroup;			/// ¿ªÆôÏµ

// ÒÆ³ıbuff£¨¿Í»§¶Ë-->·şÎñÆ÷£©
#define MSG_ACTION_REMOVE_BUFF_REQUEST									135
// ½á¹¹Ìå 
// WORD	 wBuffID;			/// buffID

/// ×°±¸Ëæ»úÊôĞÔ¼ø¶¨
#define MSG_ACTION_APPRAISE_RANDOM_EFFECT								136
struct CMsgActionAppraiseRandomEffectCmd
{
	s64 uidEquip;			/// ×°±¸UID
	s64 uidAppraise;		/// ¼ø¶¨¾íÖáUID

	CMsgActionAppraiseRandomEffectCmd()
	{
		uidEquip = 0;
		uidAppraise = 0;
	}
};

///////////////////////////////////////////////////////////////////
// ·şÎñÆ÷¹ã²¥Íæ¼ÒÒÆ¶¯ÏûÏ¢¸ø¾Å¹¬¸ñÄÚÆäËûÍæ¼Ò
#define MSG_SC_ACTION_CLIENT_MOVE										138
// ÏûÏ¢Ìå
struct SMsgActionClientMove_SC
{
	WSPOINT		ptFrom;			// Æğµã
	WSPOINT		ptTo;			// ÖÕµã
};

/// ÍøÂçping°ü
#define MSG_ACTION_NETWORK_PING											139
struct SMsgActionNetworkPingCmd
{
	// ping°üË÷Òı
	DWORD dwPingIndex;
};

//////////////////////////////////////////////////////////////////////////
// ÍË³öÕ½¶·£¨¿Í»§¶Ë-->·şÎñÆ÷£©
#define MSG_ACTION_EXIT_BATTLE											140

//////////////////////////////////////////////////////////////////////////
// ÇëÇóÕ½¶·£¨¿Í»§¶Ë-->·şÎñÆ÷£©
#define MSG_ACTION_REQ_BATTLE											141
struct SMsgActionReqBattle
{
	s32	nMatchType;			// Æ¥ÅäÀàĞÍ

	SMsgActionReqBattle()
	{
		nMatchType = 0;
	}
};

//////////////////////////////////////////////////////////////////////////
// ÇëÇó´´½¨Ó¶±ø£¨¿Í»§¶Ë-->·şÎñÆ÷£©
#define MSG_ACTION_REQ_NEWHERO											142
struct SMsgActionNewHero
{
	s32 nHeroTemplateID;		// Ó¢ĞÛÄ£°åID
	s32 nHeroLv;				// Ó¢ĞÛµÈ¼¶

	SMsgActionNewHero()
	{
		nHeroTemplateID = 0;
		nHeroLv = 0;
	}
};

//////////////////////////////////////////////////////////////////////////
// ÇëÇóÍË³öÕ½¶·£¨¿Í»§¶Ë-->·şÎñÆ÷£©
#define MSG_ACTION_REQ_EXIT_ROOM										 143

//////////////////////////////////////////////////////////////////////////
// ÇëÇó½»»»±¦Ê¯£¨¿Í»§¶Ë-->·şÎñÆ÷£©
#define MSG_ACTION_SWAP_GEM												 144
struct SMsgActionSwapGem
{
	s8 nSwapSrc;		// ½»»»Ô´
	s8 nSwapDst;		// ½»»»Ä¿±ê

	SMsgActionSwapGem()
	{
		nSwapSrc = 0;
		nSwapDst = 0;
	}
};
// ÇëÇó½»»»±¦Ê¯£¨·şÎñÆ÷-->¿Í»§¶Ë£©
struct SMsgActionSwapGemSvr
{
	s64 nSwapUID;		// ½»»»ÕßUID
	s8 nSwapSrc;			// ½»»»Ô´
	s8 nSwapDst;			// ½»»»Ä¿±ê
	// s8 bGemType;			// ±¦Ê¯ * n

	SMsgActionSwapGemSvr()
	{
		nSwapUID = 0;
		nSwapSrc = 0;
		nSwapDst = 0;
	}
};

//////////////////////////////////////////////////////////////////////////
// ±¦Ê¯ÆåÅÌ´´½¨£¨·şÎñÆ÷-->¿Í»§¶Ë£©
#define MSG_ACTION_NEW_GEM_MAP											  145

//////////////////////////////////////////////////////////////////////////
// ¿ªÊ¼¼ÓÔØ×ÊÔ´£¨·şÎñÆ÷-->¿Í»§¶Ë£©
#define MSG_ACTION_BEGIN_LOAD											  146

//////////////////////////////////////////////////////////////////////////
// ÓÎÏ·¿ªÊ¼£¨·şÎñÆ÷<-->¿Í»§¶Ë£©
#define MSG_ACTION_ROOM_BEGIN											  147
struct SMsgActionRoomBegin
{
	char	arrSitIDTurns[6];		// ÓÎÏ·¿ªÊ¼Ê±,Ã¿¸ö×ùÎ»ÉÏµÄÍæ¼ÒµÄÏÈºóÊÖË³Ğò

	SMsgActionRoomBegin()
	{
		memset(arrSitIDTurns, -1, sizeof(arrSitIDTurns));
	}
};

//////////////////////////////////////////////////////////////////////////
// »ØºÏ½áÊø£¨·şÎñÆ÷-->¿Í»§¶Ë£©
#define MSG_ACTION_ROUND_END											  148
// »ØºÏ½áÊø£¨·şÎñÆ÷-->¿Í»§¶Ë£©
struct SMsgActionRoundEnd
{
	s8 nUseTime;		// »¨·ÑÊ±¼ä

	SMsgActionRoundEnd()
	{
		nUseTime = 0;
	}
};

//////////////////////////////////////////////////////////////////////////
// Í¬²½¼ÓÔØ½ø¶È£¨·şÎñÆ÷<-->¿Í»§¶Ë£©
#define MSG_ACTION_SYNCLOAD												  149
// Í¬²½¼ÓÔØ½ø¶È£¨·şÎñÆ÷<--¿Í»§¶Ë£©
struct SMsgActionSyncLoad_CS
{
	u8	byLoadState;	// ¼ÓÔØ½ø¶È

	SMsgActionSyncLoad_CS()
	{
		byLoadState = 0;
	}
};
// Í¬²½¼ÓÔØ½ø¶È£¨·şÎñÆ÷-->¿Í»§¶Ë£©
struct SMsgActionSyncLoad_SC
{
	u32 dwActorId;		// Íæ¼Ò½ÇÉ«ID
	u8	byLoadState;	// ¼ÓÔØ½ø¶È

	SMsgActionSyncLoad_SC()
	{
		dwActorId = 0;
		byLoadState = 0;
	}
};

//¹ÍÓ¶Ó¶±ø·µ»Ø½á¹û£¨S2C£©
#define MSG_ACTION_RES_BUYHERO											150
struct SMsgActionBuyHeroRes
{
	DWORD res;
};

//Ó¶±øÉı¼¶
#define MSG_ACTION_HERO_LVUP											151
struct SMsgActionHeroLevelUp
{
	s32 nHeroIdx;		// Ó¢ĞÛÎ»ÖÃ
	s32 nHeroDstLv;		// Ó¢ĞÛÒª×ª»»µÄÄ¿±êµÈ¼¶
	SMsgActionHeroLevelUp()
	{
		nHeroDstLv = 0;
		nHeroIdx = 0;
	}


};

struct SMsgActionHeroLevelUpRes
{
	DWORD res;
};

//Ó¶±øÉı¼¶
#define MSG_ACTION_LEARN_SKILL											152
struct SMsgActionHeroLearnSkill
{
	s32 nSkillIdx;		// ¼¼ÄÜÀàĞÍ
	s32 nHeroDstLv;		// Ó¢ĞÛÒª×ª»»µÄÄ¿±êµÈ¼¶
	SMsgActionHeroLearnSkill()
	{
		nHeroDstLv = 0;
		nSkillIdx = 0;
	}
};

struct SMsgActionHeroLearnSkillRes
{
	DWORD res;
};

///////////////////////////////////////////////////////////////////
// Ìí¼Óbuff
#define MSG_ACTION_WORLD_OBJECT_INIT_TOTEM_BUFF							153

// Ìí¼Óbuff
#define MSG_ACTION_WORLD_OBJECT_ADD_TOTEM_BUFF							154
struct SMsgActionWorldObjectAddTotemBuff_SC
{
	s8				dwIndex;				// Ë÷Òı	
	u16				dwBuffId;				// buff ID	
	s16				dwTime;					// Ê£ÓàÊ±¼ä	
	s64		uidAdd;					// Ìí¼ÓÕß
};

// Ìí¼Óbuff
#define MSG_ACTION_WORLD_OBJECT_REMOVE_TOTEM_BUFF						155
struct SMsgActionWorldObjectRemoveTotemBuff_SC
{
	s8				dwIndex;				// Ë÷Òı	
	u16				dwBuffId;				// buff ID	
	s64		uidRemove;				// É¾³ıÕß
};

#define MSG_ACTION_GAME_END_RESULT										156

struct SMsgActionGameEndResult
{
	u32 nPNum;
	struct HeroGameEndResult
	{
		u32 nbTotalMage;	//ÊÜµ½×ÜÉËº¦µÄÊıÖµ
		u32 ndTotalMage;	//Ôì³É×ÜÉËº¦µÄÊıÖµ
		u32 nOneMage;		//µ¥´Î×î¸ßÉËº¦µÄÊıÖµ
		u32 nFourStraNum;	//ËÄÁ¬ĞÇ
		u32 nFiveStraNum;	//ÎåÁ¬ĞÇ
		u32 nSixStraNum;	//ÁùÁ¬ĞÇ
		u32 nSevenStraNum;  //ÆßÁ¬ĞÇ
		u32 nMaxComBoxs;	//×î¸ßÁ¬»÷Êı
		u32 nTotalGem;		//×ÜÏû±¦Ê¯Êı
		u32 nExp;
		u32 nMoney;
		HeroGameEndResult()
		{
			nbTotalMage = 0;	
			ndTotalMage = 0;	
			nOneMage = 0;		
			nFourStraNum = 0;
			nFiveStraNum = 0;
			nSixStraNum = 0;	
			nSevenStraNum = 0;
			nMaxComBoxs = 0;	
			nTotalGem = 0;		
			nExp = 0;
			nMoney = 0;
		}
	};
	HeroGameEndResult endResult[6];
};

///////////////////////////////////////////////////////////////////
// ÆÕÍ¨¹¥»÷£¨·şÎñÆ÷-->¿Í»§¶Ë£©
#define MSG_ACTION_NOMAL_ATTACK											158
struct SAttackContext
{
	s64	uidTarget;

	SAttackContext()	
	{
		memset(this, 0, sizeof(SAttackContext)); 
	}
};

// ±¾Á¬»÷½áÊø£¨·şÎñÆ÷-->¿Í»§¶Ë£©
#define MSG_ACTION_NOMAL_ATTACK_END										159

//¿¨Æ¬Ç¿»¯
#define MSG_ACTION_STRENGTHEN_CARD										160
struct StrengthenCard_CS
{
	s32		 type;
	s32		 createGoodsID;		//²úÎïID
	s64 uidCard1;			//¿¨Æ¬1
	s64 uidCard2;			//¿¨Æ¬2
	s64 luckyStoneID;		//ĞÒÔËÊ¯
	s64 uidGoods1;			//¿¨Æ¬2
	s64 uidGoods2;			//¿¨Æ¬2
	s64 uidGoods3;			//¿¨Æ¬2
};
struct Strengthen_CS
{
	s32		 type;
	s32		 StrengthenID;		//²úÎïID
	s64 uidGoodsMain;		//Ö÷²ÄÁÏ
	s64 uidGoods1;			//ÎïÆ·1
	s64 uidGoods2;			//ÎïÆ·2
	s64 uidGoods3;			//ÎïÆ·3
	s64 uidGoods4;			//ÎïÆ·4
	s64 uidGoods5;			//ÎïÆ·5
};
struct StrengthenEquip_CS
{       
        s32              type;
        s32              StrengthenID;         //²úÎïID
        s64 uidEquip;                   //×°±¸
        s64 uidStone;                   //Ç¿»¯Ê¯
        s32 nRmbCount;               	//µã»÷ÁË¼¸´Î×êÊ¯
};  

#define MSG_ACTION_STRENGTHEN_CARD_RES									161
struct StrengthenCardRes_SC
{
	s32   type;
	DWORD res;
};

// Í¨ÖªÇ°¶Ë´ò¿ª³é½±½çÃæ£¨·şÎñÆ÷-->¿Í»§¶Ë£©
#define MSG_ACTION_ADD_A_DROP											162
struct SMsgActionAddADrop_SC
{
	u8	bDropIndex;			// ³é½±×é±àºÅ
	s32 nGoodID[3];			// ÎïÆ·ID
	s32 nGoodNum[3];		// ÎïÆ·ÊıÁ¿

	SMsgActionAddADrop_SC()
	{
		memset(this, 0, sizeof(*this));
	}
};

// ³é½±£¨¿Í»§¶Ë-->·şÎñÆ÷£©
#define MSG_ACTION_ROLL_DROP											163
struct SMsgActionRollDrop_CS
{
	u8	bDropIndex;			// ³é½±×é±àºÅ
	u8	bItemSlot;			// ³é½±ÎïÆ·Î»ÖÃ
};

// ³é½±ÎïÆ·£¨·şÎñÆ÷-->¿Í»§¶Ë£©
struct SMsgActionRollDrop_SC
{
	u8	bDropIndex;			// ³é½±×é±àºÅ
	u8	bItemSlot;			// ³é½±ÎïÆ·Î»ÖÃ
	s32	nGoodID;			// ÎïÆ·ID
	s32 nGoodNum;			// ÎïÆ·ÊıÁ¿
};

// »ñÈ¡½±Àø£¨¿Í»§¶Ë<-->·şÎñÆ÷£©
#define MSG_ACTION_GET_DROP_PRIZE										164
// ½á¹¹Ìå SMsgActionRollDrop_CS

// ³õÊ¼»¯³é½±£¨·şÎñÆ÷-->¿Í»§¶Ë£©
#define MSG_ACTION_INIT_A_DROP											165
// struct SMsgActionAddADrop_SC

//////////////////////////////////////////////////////////////////////////
// ÇëÇóÑµÁ·£¨¿Í»§¶Ë-->·şÎñÆ÷£©
#define MSG_ACTION_TRAIN_DUMMY											166
struct SMsgActionTrainDummy
{
	SMsgActionTrainDummy()
	{
	}
};

struct SMsgRankInfo
{
	s32		nRank;		// ÅÅÃû
	s64		qwUserID;	// ÕËºÅID
	s32		lLevel;		// µÈ¼¶

	SMsgRankInfo()
	{
		memset(this, 0, sizeof(*this));
	}
};

struct SMsgActionTrainRank
{
  SMsgRankInfo	arrRankInfo[6];	// ´óÈüÍæ¼ÒĞÅÏ¢

  SMsgActionTrainRank()
  {
    memset(this, 0, sizeof(*this));
  }
};

///////////////////////////////////////////////////////////////////////////////

// ĞÂÊÖÒıµ¼½ø¶È£¨¿Í»§¶Ë-->·şÎñÆ÷£©
#define MSG_ACTION_GUIDER_STEP											167
struct SMsgActionGuiderStep
{
	u8	bStepID;			// ²½Öè±àºÅ
	SMsgActionGuiderStep()
	{
		bStepID = 0;
	}
};

// ¿ØÖÆÌ¨ÃüÁî£¨¿Í»§¶Ë-->·şÎñÆ÷£©
#define MSG_ACTION_CONSOLE_CMD											168

//// ÇëÇó¹Ø¿¨£¨¿Í»§¶Ë-->·şÎñÆ÷£©
//#define MSG_ACTION_TRAIN_INSTANCE										169

struct SBoxDropGoodsInfo
{
	s32		nGoodsID;		// ÎïÆ·ID
	s32		nGoodsNum;		// ÎïÆ·ÊıÁ¿

	SBoxDropGoodsInfo()
	{
		memset(this, 0, sizeof(*this));
	}
};

// Í¨ÖªÇ°¶Ë´ò¿ª¿ª±¦Ïä½çÃæ£¨·şÎñÆ÷-->¿Í»§¶Ë£©
#define MSG_ACTION_ADD_BOX_DROP											170
struct SMsgActionAddBoxDrop_SC
{
	s32		nTotalNum;		// ¶àÉÙ¸öÎïÆ·ĞÅÏ¢

	SMsgActionAddBoxDrop_SC()
	{
		memset(this, 0, sizeof(*this));
	}
};

//////////////////////////////////////////////////////////////////////////
// ÇëÇóÑµÁ··µ»Ø£¨·şÎñÆ÷-->¿Í»§¶Ë£©
#define MSG_ACTION_RESULT_TRAIN_DUMMY									171
struct SMsgActionResultTrainDummy_SC
{
	u8		byObjectType;					// ¶ÔÏóÀàĞÍ
	s64		qwUnitID;						// ÉúÎïID£¨¼ÙÈËÎªÕËºÅID, ¹ÖÎïÎªÄ£°åID£©
	s8		bySex;							// ĞÔ±ğ
	s8		byHeadPortraitId;				// Í·ÏñID
	u8		byLevel;						// µÈ¼¶

	SMsgActionResultTrainDummy_SC()
	{
		memset(this, 0, sizeof(*this));
	}
};

//////////////////////////////////////////////////////////////////////////
// ÇëÇó¹¥»÷¼ÙÈË£¨¿Í»§¶Ë-->·şÎñÆ÷£©
#define MSG_ACTION_ATTACK_DUMMY											172
struct SMsgActionAttackDummy
{
	s64		qwUserID;					// ÕËºÅID
	s32		nFightCountRMB;		// »¨Ç®¹ºÂò1´ÎÕ½¶·´ÎÊı
	s32		nCDTimeRMB;		    // »¨Ç®¹ºÂò1´ÎÕ½¶·CD

	SMsgActionAttackDummy()
	{
	}
};

//Í¨Öª¿Í»§¶Ë·¢ËÍĞÂÏÊÊÂ¶ù£¨·şÎñÆ÷-->¿Í»§¶Ë-->·şÎñÆ÷£©
#define MSG_ACTION_SEND_FEED											173
struct SMsgActionSendFeed_SC
{
	s32 nFeedTempID;
	SMsgActionSendFeed_SC()	
	{
		memset(this, 0, sizeof(SMsgActionSendFeed_SC)); 
	}

};
struct SMsgActionSendFeed_CS
{
	s32 nFeedID;
	s32 nFeedTempID;//Æ½Ì¨ĞÂÏÊÊÂ¶ùÉú³ÉµÄID
	SMsgActionSendFeed_CS()	
	{
		memset(this, 0, sizeof(SMsgActionSendFeed_CS)); 
	}

};

// ÇëÇóÉı¼¶ÉùÍû³ÆºÅ(¿Í»§¶Ë-->·şÎñÆ÷£©
#define MSG_ACTION_REPUTATION_TITLE_UPDATA						174

// ÇëÇóÃ¿ÈÕÉùÍû½±Àø£¨¿Í»§¶Ë-->·şÎñÆ÷£©
#define MSG_ACTION_REQUEST_TITLE_PRIZE								175

//³õÊ¼»¯Á¶½ğÁĞ±í
#define MSG_ACTION_INIT_STRENGTHEN_LIST									177

#define MSG_ACTIO_WORKFINISH_GETGOOD									178
struct SMsgActionWorkFinishGetGood_SC
{
	DWORD	dwClassID;		// ÀäÈ´´óÀà£¨¼¼ÄÜ£¬ÎïÆ·£¬ÁÄÌìµÈ£©
	DWORD	dwColdID;		// ÀäÈ´ID

	SMsgActionWorkFinishGetGood_SC()
	{
		memset(this, 0, sizeof(*this)); 
	}
};

// ¹ºÂòÉÌµêÎïÆ·
#define MSG_ACTION_BUY_SHOP_ITEM										179
struct SMsgActionBuyShopItem_CS
{
	s16		nShopIndex;		// ÉÌµêÎïÆ·Î¨Ò»ID
	s16		nCount;			// ÊıÁ¿

	SMsgActionBuyShopItem_CS()
	{
		memset(this, 0, sizeof(*this)); 
	}
};

// »ñÈ¡´óÈü½±ÀøÎïÆ·
#define MSG_ACTION_GET_REWARDGOODS										183
struct SMsgActionGetRewardGoods_CS
{
	s32 lRewardType;      // ½±ÀøÀàĞÍ£¨1£º×òÌìµÄ½±Àø£¬2£ºÇ°ÌìÎ´ÁìµÄ½±Àø£©
	SMsgActionGetRewardGoods_CS()
	{
		memset(this,0,sizeof(*this));
	}
};

#define MSG_ACTION_GET_REWARDGOODS_RES									184
struct SMsgActionSetRewardGoodsRes_SC
{
	s32 lRewardType;      // ½±ÀøÀàĞÍ£¨1£º×òÌìµÄ½±Àø£¬2£ºÇ°ÌìÎ´ÁìµÄ½±Àø£©
	DWORD lGetRewardRes;      // ÁìÈ¡½±Àø½á¹û
	SMsgActionSetRewardGoodsRes_SC()
	{
		memset(this,0,sizeof(*this));
	}
};

// ¹ºÂò¾«Á¦Öµ
#define MSG_ACTION_BUY_ENERGY_POINT										186
struct SMsgActionBuyEnergyPoint_CS
{
	s16		nCount;			// ÊıÁ¿

	SMsgActionBuyEnergyPoint_CS()
	{
		memset(this, 0, sizeof(*this)); 
	}
};

// »ñÈ¡Á¬ĞøµÇÂ½½±Àø
#define MSG_ACTION_GET_LOGIN_PRIZE										187

// »ñÈ¡ÑûÇëºÃÓÑ½±Àø
#define MSG_ACTION_GET_FRIEND_PRIZE										188
struct SMsgActionGetFriendPrize_CS
{
	s16		nCount;			// ÑûÇëºÃÓÑÊıÁ¿
	s16		nVCount;		// ÑûÇëV´ïÈËÊıÁ¿
	
	SMsgActionGetFriendPrize_CS()
	{
		memset(this, 0, sizeof(*this));
	}
};

// ÉèÖÃÕËºÅÍ·ÏñURL
#define MSG_ACTION_SET_HEAD_URL											189
struct SMsgActionSetHeadURL_CS
{
	char		szHeadURL[256];			// ÉèÖÃ×Ô¼ºµÄÕËºÅÍ·ÏñURL

	SMsgActionSetHeadURL_CS()
	{
		memset(this, 0, sizeof(*this)); 
	}
};


// »ñÈ¡ÕËºÅÍ·ÏñURL
#define MSG_ACTION_GET_HEAD_URL											190
struct SMsgActionGetHeadURL_CS
{
	s64			qwUserID;				// ÕËºÅID

	SMsgActionGetHeadURL_CS()
	{
		memset(this, 0, sizeof(*this)); 
	}
};

struct SMsgActionGetHeadURL_SC
{
	s64			qwUserID;				// ÕËºÅID
	char		szActorName[13];		// ½ÇÉ«Ãû
	char		szHeadURL[256];			// ÕËºÅÍ·ÏñURL
	char			sOpenId[64];			// OpenID

	SMsgActionGetHeadURL_SC()
	{
		memset(this, 0, sizeof(*this)); 
	}
};

//////////////////////////////////////////////////////////////////////////
// ÇëÇó»ñÈ¡ÇĞ´èºÃÓÑ£¨¿Í»§¶Ë-->·şÎñÆ÷£©
#define MSG_ACTION_PK_FRIEND											191
struct SMsgActionPKFriend
{
	s64			qwUserID;				// ÕËºÅID

	SMsgActionPKFriend()
	{
	}
};

// ĞÂÏÊÊÂ»ı·Ö³é½±£¨¿Í»§¶Ë-->·şÎñÆ÷£©
#define MSG_ACTION_FEED_SCORE_ROLL										192
struct SMsgActionFeedScoreRoll_CS
{
	u8	bScoreIndex;		// Áì½±±àºÅ
	u8	byRollType;			// ³é½±ÀàĞÍ
};

// ĞÂÏÊÊÂ»ı·Ö³é½±£¨·şÎñÆ÷-->¿Í»§¶Ë£©
struct SMsgActionFeedScoreRoll_SC
{
	u8	byResult;			// ³é½±ÊÇ·ñ³É¹¦(0:Ê§°Ü, 1:³É¹¦)
	u8	bItemSlot;			// ³é½±ÎïÆ·Î»ÖÃ
};

// ÁìÈ¡Ã¿ÈÕ½±Àø£¨¿Í»§¶Ë-->·şÎñÆ÷£©
#define MSG_ACTION_GET_EVERYDAY_PRIZE									193
// u8 bType;				// ÀàĞÍ

// ¹ºÂòvip£¨¿Í»§¶Ë-->·şÎñÆ÷£©
#define MSG_ACTION_BUY_VIP												194
// u8 bCount;				// ÊıÁ¿

// ÆõÔ¼¿¨Æ¬( ¿Í»§¶Ë-->·şÎñÆ÷ )
#define MSG_ACTION_BUY_CARD_ENDURE										195
struct SMsgActionBuyCardEndure_CS
{
	s64				uidEquip;		// ×°±¸
	u8				byPacketSkep;	// °ü¹üÀ¸
	// Èç¹ûÎª1£¬Ôò±íÊ¾×°±¸ÔÚ°ü¹üÀ¸£¬·´Ö®×°±¸À¸
};

// ÆõÔ¼¿¨Æ¬£¨·şÎñÆ÷-->¿Í»§¶Ë£©
struct SMsgActionBuyCardEndure_SC
{
	u8	byResult;			// ÆõÔ¼ÊÇ·ñ³É¹¦(0:Ê§°Ü, 1:³É¹¦)
};

// Ç¿»¯Éı¼¶( ¿Í»§¶Ë-->·şÎñÆ÷ )
#define MSG_ACTION_STRENGTH_LEVELUP										196
struct SMsgActionStrengthLevelUp_CS
{
	s32				lType;			// Ç¿»¯ÀàĞÍ
	s32				lLevelUpType;	// Éı¼¶·½Ê½
};

// Ç¿»¯¹ºÂò( ¿Í»§¶Ë-->·şÎñÆ÷ )
#define MSG_ACTION_STRENGTH_BUY											197
struct SMsgActionStrengthBuy_CS
{
	s32				arrGoodsID[6];			// ¹ºÂòÎïÆ·ID
	s32				arrGoodsNum[6];			// ¹ºÂòÎïÆ·ÊıÁ¿
};

// Á¢¼´Íê³É( ¿Í»§¶Ë-->·şÎñÆ÷ )
#define MSG_ACTION_STRENGTHOVER_RIGHTNOW                                                                        198
struct SMsgActionStrengthOverRightNow_CS
{
	s32				nColdClass;			// ÀäÈ´ÀàĞÍ
        s32                             nColdID;			// ÀäÈ´ID
};

// ¿¨Æ¬ÏûºÄÇé¿ö( ·şÎñÆ÷-->¿Í»§¶Ë ) 
#define MSG_ACTION_CARD_ENDURE_INFO										199
// ÏûÏ¢Ìå
struct SMsgActionCardEndureInfo_SC
{
	struct SCardEndureInfo
	{
		s32			nCardSlot;			// ¿¨Æ¬ËùÔÚ²ÛÎ»
		s32			nCardID;			// ¿¨Æ¬Ä£°åID
	};
};

// ¹ºÂòÒÑÏûºÄ¿¨Æ¬( ¿Í»§¶Ë-->·şÎñÆ÷ )
#define MSG_ACTION_BUY_LOST_CARD										200
// ÏûÏ¢Ìå
struct SMsgActionBuyLostCard_CS
{
	s32	nCardSlot;						// ¿¨Æ¬ËùÔÚ²ÛÎ»
	s32	nCardID;						// ¿¨Æ¬Ä£°åID
};

// ÇëÇóÆ½Ì¨ºÃÓÑµÄÊÕ¼¯³õÊ¼»¯Êı¾İ£¨¿Í»§¶Ë->·şÎñÆ÷£©
#define MSG_ACTION_REQUEST_COLLECT_DATA             201
struct SMsgActionRequestCollectData_CS
{
  SMsgActionRequestCollectData_CS() :
    wSize(0) {}
  s16 wSize;                // Êı¾İ¸öÊı
  u64 qwUserIDs[0];         // ÓÃ»§ID×é
};

// ·µ»ØÃ»ÓĞÊÕ¼¯¹ıµÄÆ½Ì¨ºÃÓÑµÄÊÕ¼¯³õÊ¼»¯Êı¾İ£¨·şÎñÆ÷->¿Í»§¶Ë£©
#define MSG_ACTION_RESPONSE_COLLECT_DATA            202
struct SMsgActionResponseCollectData_SC
{
  SMsgActionResponseCollectData_SC() :
    wSize(0) {}
  u16 wSize;                   // Êı¾İ¸öÊı
  u64 friendUserIDs[0];        // ºÃÓÑµÄÓÃ»§IDÊı¾İ
};

// ¿Í»§¶ËÇëÇóÍ¬²½Ê±¼ä£¨¿Í»§¶Ë->·şÎñÆ÷£©
#define MSG_ACTION_REQUEST_SYNC_TIME                203

// Ïò¿Í»§¶ËÍ¬²½Ê±¼ä£¨·şÎñÆ÷->¿Í»§¶Ë£©
#define MSG_ACTION_SYNC_TIME                        204
struct SMsgActionSyncTime_SC
{
  SMsgActionSyncTime_SC() : qwTime(0) {}
  s64 qwTime;                 // Ê±¼ä
};

// ¿Í»§¶Ë·¢ËÍÆ½Ì¨ºÃÓÑÊÕ¼¯¿ªÊ¼£¨¿Í»§¶Ë->·şÎñÆ÷£©
#define MSG_ACTION_REQUEST_COLLECT_START            205
struct SMsgActionRequestCollectStart_CS
{
  SMsgActionRequestCollectStart_CS() : qwFriendUserID(0) {}
  u64 qwFriendUserID;         // ºÃÓÑÓÃ»§ID
};

// »Ø¸´¿Í»§¶ËÊÇ·ñ¿ÉÒÔ¿ªÊ¼ÊÕ¼¯£¨·şÎñÆ÷->¿Í»§¶Ë£©
#define MSG_ACTION_RESPONSE_COLLECT_START            206
struct SMsgActionResponseCollectStart_CS
{
  SMsgActionResponseCollectStart_CS() : qwFriendUserID(0) {}
  u64 qwFriendUserID;         // ºÃÓÑÓÃ»§ID
  u8 result;                  // 0:²»¿ÉÒÔ£¬1£º¿ÉÒÔ
};

// ¿Í»§¶Ë·¢ËÍÆ½Ì¨ºÃÓÑÊÕ¼¯½áÊø£¨¿Í»§¶Ë->·şÎñÆ÷£©
#define MSG_ACTION_REQUEST_COLLECT_END              207
struct SMsgActionRequestCollectEnd_CS
{
  SMsgActionRequestCollectEnd_CS() :
    qwFriendUserID(0), dwMoneyNum(0) {}
  u64 qwFriendUserID;         // ºÃÓÑUSERID
  u32 arrGoodNum[5];          // µØ¡¢Ë®¡¢»ğ¡¢·ç¡¢À×¶ÔÓ¦½±ÀøÎïÆ·¸öÊı
  u32 dwMoneyNum;             // ½ğÇ®ÊıÁ¿
  u8 isDoubleAward;           // ÊÇ·ñ¼Ó±¶½±Àø£¬0£º²»¼Ó±¶£¬1£º¼Ó±¶
};

// ·şÎñÆ÷·¢ËÍ³é½±½á¹û£¨¿Í»§¶Ë<--·şÎñÆ÷£©
#define MSG_ACTION_DAY_ROLL_RESULT                  208
// u8 bIdx;                   // ³éÖĞµÚ¼¸¸ö£¨1~8£©

#define MSG_ACTION_ONLINE_TIME			                209
// ¿Í»§¶Ë->·şÎñÆ÷ ÉèÖÃ·şÎñÆ÷µ±ÈÕÀÛ¼ÆÔÚÏßÊ±³¤
struct SMsgActionSetRemoteOnlineTime_CS
{
	s32	nOnlineTime;	// Æ½Ì¨Í³¼ÆµÄÔÚÏßÊ±³¤
	SMsgActionSetRemoteOnlineTime_CS()
	{
		memset(this, 0, sizeof(*this));	
	}
};

// ·şÎñÆ÷->¿Í»§¶Ë ÇëÇóÆ½Ì¨Í³¼Æµ±ÈÕÀÛ¼ÆÔÚÏßÊ±³¤
struct SMsgActionGetOnlineTime_SC
{
	SMsgActionGetOnlineTime_SC()
	{
	}
};

#define MSG_ACTION_GET_PVPPRIZE                                  210
// ¿Í»§Ë->·şÎñÆ÷ ÁìÈ¡PVP»î¶¯½±Àø
struct SMsgActionGetPVPPrize_CS
{
	s32	lType;		// 0:PVPÕ½¶·´ÎÊı 1:PVPÊ¤Àû´ÎÊı

	SMsgActionGetPVPPrize_CS()
	{
		memset(this, 0, sizeof(*this));
	}
};

#define MSG_ACTION_OPEN_SURFACE                 211
// ¿Í»§¶Ë->·şÎñÆ÷ ´ò¿ª½çÃæ
struct SMsgActionOpenSurface_CS
{
  u32 dwSurfaceID;    // ½çÃæID

  SMsgActionOpenSurface_CS() : dwSurfaceID(0) {}
};

#define MSG_ACTION_GET_INSTANCE_PRIZE		212
// ¿Í»§¶Ë->·şÎñÆ÷ ÁìÈ¡ËéÆ¬½±Àø
struct SMsgActionGetInstancePrize_CS
{
	s32	nMapID;		// ´óµØÍ¼ID
	s32	nPrizeID;	// ½±ÀøID

	SMsgActionGetInstancePrize_CS()
	{
		memset(this, 0, sizeof(*this));
	}
};

#define MSG_ACTION_GET_INSTANCE_MONEY		213
// ¿Í»§¶Ë->·şÎñÆ÷ ÊÕ»ñÓÎÏ·±Ò»òÕßÇ¿ÖÆÕ÷ÊÕÓÎÏ·±Ò
struct SMsgActionGetInstanceMoney
{
	s32	nType;		// 0 : Õ÷ÊÕ; 1 : Ç¿ÖÆÕ÷ÊÕ

	SMsgActionGetInstanceMoney()
	{
                memset(this, 0, sizeof(*this));
        }
};

// ±¦Ê¯ÉËº¦£¨·şÎñÆ÷-->¿Í»§¶Ë£©
#define MSG_ACTION_DAMAGE_PREPARE		214
struct SDamageContext
{
	s32	nValue;
  s32 nCombCount;
  s32 nIsCrit;

	SDamageContext()	
	{
		memset(this, 0, sizeof(SDamageContext)); 
	}
};

// ¿Í»§¶Ë->·şÎñÆ÷ »ñÈ¡ºÃÓÑÀñÎï
#define MSG_ACTION_GET_GOODSGIFT                215
struct SMsgActionGetGoodsGift_CS
{
        SMsgActionGetGoodsGift_CS()
        {
                memset(this, 0, sizeof(*this));
        }
};

// »ñÈ¡Qµã³äÖµ(¿Í»§¶Ë--->·şÎñÆ÷)
#define MSG_ACTION_QQPOINT_PRIZE		254
struct SMsgActionQQPointPrize_CS
{
	SMsgActionQQPointPrize_CS()
	{
		memset(this, 0, sizeof(*this));
	}
};

// ¿Í»§¶Ë->·şÎñÆ÷ »ñÈ¡´óÈüÌôÕ½¼ÇÂ¼
#define MSG_ACTION_GET_RANKRECORD                216
struct SMsgActionGetRankRecord_CS
{
	SMsgActionGetRankRecord_CS()
        {
                memset(this, 0, sizeof(*this));
        }
};
// ·şÎñÆ÷->¿Í»§¶Ë ´óÈüÌôÕ½¼ÇÂ¼
struct SMsgActionGetRankRecord_SC
{
	s64	qwAttUserID;
	s64	qwDefUserID;
	s8	lResult;
	s32	nAttRank;
	s32	nDefRank;
	s32	lLogTime;

	SMsgActionGetRankRecord_SC()
        {
                memset(this, 0, sizeof(*this));
        }
};

// ¿Í»§¶Ë->·şÎñÆ÷ ·Ö½â¿¨Æ¬
#define MSG_ACTION_DECOMPOSECARD		217
struct SMsgActionDecomposeCard_CS
{
	s8	byType;		// 0:»¨½ğ±Ò, 1:»¨·ûÎÄ
	s64	guidCard;	// ¿¨Æ¬GUID

	SMsgActionDecomposeCard_CS()
	{
                memset(this, 0, sizeof(*this));
        }
};

// ¿Í»§¶Ë->·şÎñÆ÷ ³é¿¨
#define MSG_ACTION_ROLLCARDPRIZE		218
struct SMsgActionRollCardPrize_CS
{
	s32	lRollID;	// ³é¿¨±àºÅ

	SMsgActionRollCardPrize_CS()
        {
                memset(this, 0, sizeof(*this));
        }
};

// ·şÎñÆ÷->¿Í»§¶Ë ·µ»ØÖĞ½±ÎïÆ·ÁĞ±í
struct SMsgActionRollCardPrize_SC
{
	s32	arrGoodsList[5];	// ÖĞ½±ÎïÆ·ÁĞ±í

	SMsgActionRollCardPrize_SC()
        {
                memset(this, 0, sizeof(*this));
        }
};

// ·şÎñÆ÷->¿Í»§¶Ë ĞÂÔö³é¿¨ÖĞ½±Ãûµ¥
#define MSG_ACTION_ADDCARDROLL			219
struct SMsgActionAddCardRoll_SC
{
	s64	qwUserID;	// ÖĞ½±ÕßÕËºÅID
	char	szActorName[32];// ÖĞ½±ÕßÃû×Ö
	s32	lGoodsID;	// ÖĞ½±µÀ¾ßID

	SMsgActionAddCardRoll_SC()
        {
                memset(this, 0, sizeof(*this));
        }
};

#define MSG_ACTION_GETCARDROLLLIST		220
// ¿Í»§¶Ë->·şÎñÆ÷ »ñÈ¡ÖĞ½±ÕßÁĞ±í
struct SMsgActionGetCardRollList_CS
{
	SMsgActionGetCardRollList_CS()
	{
                memset(this, 0, sizeof(*this));
        }
};

// ·şÎñÆ÷->¿Í»§¶Ë ·µ»ØÖĞ½±ÕßÁĞ±í
struct SMsgCardRollResult
{
	s64     qwUserID;       // ÖĞ½±ÕßÕËºÅID
        char    szActorName[32];// ÖĞ½±ÕßÃû×Ö
        s32     lGoodsID;       // ÖĞ½±µÀ¾ßID

	SMsgCardRollResult()
	{
                memset(this, 0, sizeof(*this));
        }
};

struct SMsgActionGetCardRollList_SC
{
	u16	wCount;		//¸öÊı
	//¶à¸öSMsgCardRollResult

	SMsgActionGetCardRollList_SC()
	{
		memset(this, 0, sizeof(*this));
	}
};

#define MSG_ACTION_VIPEXCHANGE			221
// ¿Í»§¶Ë->·şÎñÆ÷ ·ûÎÄ¶Ò»»µÀ¾ß
struct SMsgActionVIPExchange_CS
{
	s32	lExchangeID;	// ¶Ò»»ID
	s32	lExchangeNum;	// ¶Ò»»ÊıÁ¿

	SMsgActionVIPExchange_CS()
        {
                memset(this, 0, sizeof(*this));
        }
};

#define MSG_ACTION_ACTIVITY_FEEDBACK    222
// ¿Í»§¶Ë->·şÎñÆ÷ »î¶¯Ïû·Ñ·µÀû

// ×î´óÏûÏ¢Âë
#define MSG_ACTION_MAXID												256

#pragma pack(pop)

#endif //_DMSGKEYROOT_H__
