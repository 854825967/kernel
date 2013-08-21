#ifndef _DMSGKEYROOT_H__
#define _DMSGKEYROOT_H__

#include <string.h>

#include "GameType.h"

/*
��Ϣ�붨��ṹ:
	����Ϣ��
		����Ϣ��
//*/

#pragma pack(push, 1)

// ���������ͻ��˵���Ϣͷ
struct S2CMsgHead
{
	// ����Ϣ��
	u16			m_wMainCmd;
	// ����Ϣ��
	u16			m_wSubCmd;

	S2CMsgHead()
	{
		memset(this,0,sizeof(*this));
	}

};


enum RootCmd
{
	CMD_ROOT_ERROR			=	0x0001,		// ���󱨾�ר����Ϣ��
	CMD_ROOT_LOGIN			=	0x0002,		// ��¼̬��Ϣ��
	CMD_ROOT_GATEWAY		=	0x0003,		// ѡ������̬��Ϣ��
	CMD_ROOT_SELECTACTOR	=	0x0004,		// ѡ������̬��Ϣ��
	CMD_ROOT_MANAGER		=	0x0005,		// ����Աר����Ϣ�루ֻ�е�������ת������̬��Ҳ����˵ѡ������󣬷��������ᴦ��
	CMD_ROOT_CHAT			=	0x0006,		// ������Ϣ������Ϣ�루ֻ�е�������ת������̬��Ҳ����˵ѡ������󣬷��������ᴦ��
	CMD_ROOT_THING			=	0x0007,		// ʵ�嶨��
	CMD_ROOT_INTERACT		=	0x0008,		// ����ϵͳ��Ϣ��ר��
	CMD_ROOT_CONTAINER		=	0x0009,		// ��������Ϣ��
	CMD_ROOT_SKEP			=	0x000A,		// ������Ʒ����Ϣ��
	CMD_ROOT_RELATION		=	0x000B,		// ������Ϣ��
	CMD_ROOT_TEAM			=	0x000C,		// �����Ϣ��
	CMD_ROOT_TRADE			=	0x000D,		// ��Ҽ佻����Ϣ��
	CMD_ROOT_WORK_SKILL		=	0x000E,		// �����ϵͳ
	CMD_ROOT_GAMEEVENT		=	0x000F,     // ��Ϸ�¼���Ϣ��
	CMD_ROOT_UNION			=	0x0010,		// ������Ϣ��
	CMD_ROOT_TITLE			=	0x0011,		// �ƺ���Ϣ��
	CMD_ROOT_MIND			=	0x0012,		// �̳���Ϣ��
	CMD_ROOT_BATTLE			=	0x0013,		// ս����Ϣ��
	CMD_ROOT_SCRIPT_EVENT	=	0x0014,		// �ű��¼���Ϣ��
	CMD_ROOT_ROOM			=	0x0015,		// ������Ϣ��
	CMD_ROOT_MAX			=	0x0016,		// ���ROOT��Ϣ��
};

/***************************************************************/
///////////////////// �������ķ�����Ϣ��/////////////////////
// ����Ϣ��ض���CMD_ROOT_ROOM
/***************************************************************/
// ���buff
#define MSG_ROOM_ADD_BUFF									   1
struct SMsgRoomAddBuff_SC
{
	s8		bSitIndex;			// ��ʯ/����λ�ñ��
	u16		nBuffID;			// buffID
	s64		uidAdd;				// �����
};

// �Ƴ�buff
#define MSG_ROOM_REMOVE_BUFF									2
struct SMsgRoomRemoveBuff_SC
{
	s8		bSitIndex;			// ��ʯ/����λ�ñ��
	s64		uidRemove;			// �Ƴ���
};

// ������ؽ���
#define MSG_ROOM_LOADING										3
//  s32	nBattleCreatureID;		// ս������ID
struct SMsgRoomLoading_SC
{
	u8		bType;				// ����
	char		strName[13];		// ����
	u8		bLevel;				// �ȼ�
	u32		nBattleTimes;		// ս������
	u32		nWinTimes;			// ʤ������
	u32		bHeadId;			// ���id
	u8		bPetHeadId;			// �������id
};

// ��ʼ���ؿ�
#define MSG_ROOM_INIT_INSTANCE_INFO								4
struct SMsgRoomInitInstance_SC
{
	s16		nInstanceID;		// �ؿ�ID
	u16		nFinishFlag;		// ������
	u16		nFirstBattleFlag;	// ��һ�δ����Ϣ
};

// �ƶ�
#define MSG_ROOM_MOVE_ARRAY										5
struct SMsgRoomGotoInstanceStep_CS
{
	s32		nCreatureID;		// ����ID
};

// �˳�
#define MSG_ROOM_EXIT_ROOM										6

// ���½���
#define MSG_ROOM_UPDATA_INSTANCE_STEP							7
struct SMsgRoomUpdataInstanceStep_SC
{
	s32		nCreatureID;		// ս������ID
	s8		bIsWin;				// Ӯ������
};

// ˢ�·���
#define MSG_ROOM_REFRESH_ROOM									8

/***************************************************************/
///////////////////// ��������ʵ�������Ϣ��/////////////////////
// ����Ϣ��ض���CMD_ROOT_THING
/***************************************************************/
// ֪ͨ�ͻ��˴���ʵ��
#define MSG_PROP_CREATEENTITY									1
struct SMsgActionCreateNum_SC
{
	WORD		wCreateNum;			// ����ʵ�����Ŀ
	// ...wCreateNum��(SMsgPropCreateEntity_SC+����ʵ���������)
};
// ��Ϣ��
struct SMsgPropCreateEntity_SC
{
	s64	uidEntity;
	char		nEntityClass;	// ʵ������
	char		nIsHero;		// �Ƿ�ͻ������ǣ�1���ǣ�2����
	WORD		wContextLen;	// ����ʵ���ֳ������ĳ���

	// ......................   // �����ֳ�
};

///////////////////////////////////////////////////////////////////
// ֪ͨ�ͻ���ɾ��ʵ��
#define MSG_PROP_DESTROYENTITY									2
struct SMsgActionDestroyNum_SC
{
	WORD		wDestroyNum;		// ����ʵ�����Ŀ
	// ....wDestroyNum��SMsgPropDestroyEntity_SC
};
struct SMsgPropDestroyEntity_SC
{
	s64	uidEntity;
};

///////////////////////////////////////////////////////////////////
// ͬ���ͻ���ʵ������
#define MSG_PROP_UPDATEPROP										3
struct SMsgPropUpdateProp_SC
{
	s64	uidEntity;
	char		nUpdateMode;	// ����ģʽ��1��������ֵ���Ը��£�2���������Ը���
	//       3�������ַ����Ը��£�4�������ֵ���Ը���
	// ......................   // �����ֳ�
};


///////////////////////////////////////////////////////////////////
// ��ȴ��ʼ������
#define MSG_ACTION_INITCOLD									4
// ��Ϣ��
struct SMsgActionInitCold_SC
{
	struct SNodeContext
	{
		BYTE		byClassID;	// ��ȴ��ID	
		int			nColdID;	// ��ȴID
		int			nColdTime;	// ��ȴʣ��ʱ�䣨���룩
	};
	// .................		// ���SNodeContext
};


///////////////////////////////////////////////////////////////////

typedef struct tagWSPOINT
{
	WORD x;
	WORD y;
} WSPOINT;

// �����ƶ���Ϣ
#define MSG_ACTION_MOVE											5

// �����ƶ��¼�
struct SMsgActionMonsterMove_SS
{
	POINT		ptFrom;			// ���
	POINT		ptTo;			// �յ�
};

struct SMsgActionMove_SS
{
	DWORD		dwPathLen;		// ·������
	// ......................   // ·���ڵ㣬WSPOINT * dwPathLen
};
// ��Ϣ��(���������ƶ�·����)
struct SMsgActionMove_SC
{
	DWORD		dwPathLen;		// ·������
	// ......................   // ·���ڵ㣬WSPOINT * dwPathLen
};

///////////////////////////////////////////////////////////////////
// �ͻ��˲����ƶ���Ϣ
#define MSG_CS_ACTION_CLIENTOPT_MOVE								6
// ��Ϣ��
struct SMsgActionClientOptMove_CS
{
	DWORD		dwPathLen;		// ·������
	// ......................   // ·���ڵ㣬WSPOINT * dwPathLen
};

struct SMsgActionSCHead
{
	s64	uidEntity;			// Object��guid
};

//////////////////////////////////////////////////////////////////////////
// ֹͣ�ƶ���Ϣ
#define MSG_ACTION_STOPHERE										7
struct SMsgActionStopHere_SC
{
	WORD		ptHereX;		// X����
	WORD		ptHereY;		// Y����
	BYTE		byOri;			// ����
	BYTE		byForceSync;	// �Ƿ�ǿ������ 0:��ǿ�ƣ� 1:ǿ��
};

//////////////////////////////////////////////////////////////////////////
// ������Ϣ
#define MSG_ACTION_NEW_WORLD									8
struct SMsgActionNewWorld_SC
{
	DWORD		dwMapId;		// ��ͼId
};

//////////////////////////////////////////////////////////////////////////
// ״̬�ı�  ���� �ƶ��� ����
#define  MSG_ACTION_CHANAGEMOVESTYLE							9

/***************************************************************/
/////////////////// ͨ����Ʒ����Ϣ�� ////////////////////////////
/***************************************************************/
// ������Ʒ
#define MSG_ACTION_SWAP_ITEM									10
struct SMsgActionSwapItem_CS
{
	BYTE		byDestBag;	// Ŀ�걳�����
	BYTE		byDestSlot;	// Ŀ�걳���еĸ���
	BYTE		bySrcBag;	// Դ�������
	BYTE		bySrcSlot;	// Դ�����еĸ���
};

// �ָ�ѵ���Ʒ
#define MSG_ACTION_SPLIT_ITEM									11
struct SMsgActionSplitItem_CS
{
	BYTE		bySrcBag;	// Դ�������
	BYTE		bySrcSlot;	// Դ�����еĸ���
	BYTE		byDestBag;	// Ŀ�걳�����
	BYTE		byDestSlot;	// Ŀ�걳���еĸ���
	BYTE		byCount;	// �з���Ʒ�ĸ���
};

///////////////////////////////////////////////////////////////////
// ����������Ʒ
#define MSG_ACTION_BUYGOODS										12
// ��Ϣ��
struct SMsgActionBuyGoods_CS
{
	s64		uidNPC;		// NPC����
	DWORD			dwSkepID;	// ͨ����Ʒ��ID

	s64		uidGoods;	// ������Ʒ
	int				nBuyNum;	// �����

	SMsgActionBuyGoods_CS()
	{
		memset(this, 0, sizeof(*this));
	}
};

///////////////////////////////////////////////////////////////////
// ������Ʒ
#define MSG_ACTION_SALEGOODS									13
// ��Ϣ��
struct SMsgActionSaleGoods_CS
{
	s64		uidGoods;	// ���۵���Ʒ
	int				nSaleNum;	// ���۵���Ʒ����

	SMsgActionSaleGoods_CS()
	{
		memset(this, 0, sizeof(*this));
	}
};

///////////////////////////////////////////////////////////////////
// ���NPC�Ի�
#define MSG_ACTION_MEETNPC										14
// ��Ϣ��
struct SMsgActionMeetNPC_CS
{
	s64		uidNPC;		// NPC��UID
};

///////////////////////////////////////////////////////////////////
// ��Ʒ�б�
#define MSG_ACTION_LIST_INVENTORY								15
struct SMsgActionListInventory_SC
{
	s64		uidNPC;		// NPC��UID
	WORD			wItemCount;	// ��Ʒ����
	// .......................	NPC������Ʒ�б�
};

struct SMsgActionSCInvItem
{
	WORD			wIndex;		// ��Ʒλ��
	int			lItemEntry;	// ��ƷEntry
};

///////////////////////////////////////////////////////////////////
// ���buff
#define MSG_ACTION_WORLD_OBJECT_ADD_BUFF						16
struct SMsgActionWorldObjectAddBuff_SC
{
	//DWORD			dwIndex;				// ����	
	u16				dwBuffId;				// buff ID	
	s32				dwTime;					// ʣ��ʱ��
	s64		uidAdd;					// �����
};

// ���buff
#define MSG_ACTION_WORLD_OBJECT_REMOVE_BUFF						17
struct SMsgActionWorldObjectRemoveBuff_SC
{
	//DWORD			dwIndex;		// ����	
	u16				dwBuffId;				// buff ID	
	s64		uidRemove;				// ɾ����
};

/////////////////////////////////////////////////////////
//// ��  ���������������ͻ��˵�����̬��Ϣ��
/////////////////////////////////////////////////////////
// �����������ͻ��˵���Ϣͷ
struct SC_THING_HEAD : public S2CMsgHead
{
	SC_THING_HEAD(void)
	{
		m_wMainCmd = CMD_ROOT_THING;
		m_wSubCmd = 0;
	}
};

///////////////////////////////////////////////////////////////////
//�������˽��thing
#define MSG_ACTION_MAIN_PRIVATE_MULTI							18
// ������ͨ��ROOTTHING_SC_MAIN_PRIVATE_MULTI�����ͻ��˵���Ϣͷ
struct SC_THING_PRIVATE_MULTI_HEAD : public SC_THING_HEAD
{
	WORD	m_wThingClassID;		//�����Thing����
	WORD	m_wNum;					//Thing�ĸ���

	//... m_wNum��: UID + wLen + Thing����

	SC_THING_PRIVATE_MULTI_HEAD(void)
	{
		m_wSubCmd = MSG_ACTION_MAIN_PRIVATE_MULTI;

		m_wThingClassID = 0;
		m_wNum = 0;
	}
};


///////////////////////////////////////////////////////////////////
// ѧϰ���ܣ��ͻ���<-->�������� 
#define MSG_ACTION_UPGRADE_SKILL								19
// ��Ϣ��
// s16 nSkillID;


///////////////////////////////////////////////////////////////////
// ʹ�ü��ܣ��ͻ���-->��������
#define MSG_ACTION_USE_SKILL									20
// ����׼����������->�ͻ��ˣ�
#define MSG_ACTION_SKILL_PREPARE								21
// �����ͷţ�������->�ͻ��ˣ�
#define MSG_ACTION_SKILL_CAST									22
// ��Ϣ��
struct SkillContext
{
	s64	uidTarget;		/// ʹ�ü���ʱ�������λ���ϵ�ʵ�����
	s8			ptTargetTile;	/// ʹ�ü���ʱ�������λ��
	s16			nSkillId;		/// ����ID

	SkillContext()	
	{
		memset(this, 0, sizeof(SkillContext)); 
	}
};

///////////////////////////////////////////////////////////////////
// ȡ�����ܣ��ͻ���-->��������
#define MSG_ACTION_SKILL_CANCEL									23

///////////////////////////////////////////////////////////////////
// �����жϣ�������->�ͻ��ˣ�
#define MSG_ACTION_BREAK_SKILL									24
// ��Ϣ��
struct SMsgActionSkillResult_SC
{
	int			result;			/// ���ܽ��
};

///////////////////////////////////////////////////////////////////
// �˺���������->��������
#define MSG_ACTION_DAMAGE										25
// ��Ϣ��

///////////////////////////////////////////////////////////////////
// ���ƣ�������->��������
#define MSG_ACTION_CURE											26
// ��Ϣ��

///////////////////////////////////////////////////////////////////
// ���ƣ�������->�ͻ��ˣ�
#define MSG_ACTION_PREPARE_DAMAGE								27
// ���ƣ�������->�ͻ��ˣ�
#define MSG_ACTION_PREPARE_CURE									28

// ������������Դ
#define MSG_ACTION_PLAYER_CLEAN_SHOW							29
// ������
// SC_MSG_CLEAN_SHOW_CONTEXT

// �����Ӷ������
#define MSG_ACTION_DIE											30
struct SMsgActionDie_SC
{
	s64		uidMuderer;		//ıɱ�ߵ�uid
};

// ֪ͨ�Լ���������������Ϣ
#define MSG_ACTION_BUILDPACKET									31

// ֪ͨ�Լ�����װ����������Ϣ
#define MSG_ACTION_BUILDEQUIPPACKET								32

///////////////////////////////////////////////////////////////////
// ʹ��ҩƷ
#define MSG_ACTION_USELEECHDOM									33
// ��Ϣ��
struct SMsgActionUseLeechdom_SS
{	
	s64	uidLeechdom;	// ҩƷuid
};

///////////////////////////////////////////////////////////////////
#define MSG_ACTION_COLD_WORK									34
// ��ȴ֪ͨ��������->�ͻ��ˣ�
struct SMsgActionColdWork_SC
{
	DWORD	dwClassID;		// ��ȴ���ࣨ���ܣ���Ʒ������ȣ�
	DWORD	dwColdID;		// ��ȴID
	s32		nColdTime;		// ��ȴʣ��ʱ�䣨���룩
};
// ��ȡ��Ʒ���ͻ���->��������
struct SMsgActionColdWork_CS
{
	DWORD	dwClassID;		// ��ȴ���ࣨ���ܣ���Ʒ������ȣ�
	DWORD	dwColdID;		// ��ȴID	
};



//////////////////////////////////////////////////////////////////////////
// ���漼�ܿ����
#define MSG_ACTION_SHORTCUT										35
struct CS_MSG_SHORTCUT_CONTEXT
{
	BYTE	byHeroIndex;	//Ӷ��INDEX
	BYTE	byIndex;		//���������
	DWORD	dwSkillInfo;	//(0~2λ)���ܻ���ƷId 3λ(1:��ʾ���� 0:��ʾ��Ʒ)

	CS_MSG_SHORTCUT_CONTEXT()
	{
		memset(this, 0, sizeof(*this));
	}
};

///////////////////////////////////////////////////////////////////
// CS : ���󸴻�㸴��
// SC : �����ʱ
#define MSG_ACTION_ORIGINAL_RELIVE								36
// ��Ϣ��
struct SMsgActionOriginalRelive_SC
{
	POINT				coordinate;				//����
	int					nReliveCountDown;		//��Ҫ�ȴ�������
	DWORD				dwReliveMapID;			//��ͼID
	int					nTimes;					//����

};

// �ͻ��˸���㸴������
struct SMsgActionOriginalRelive_CS
{

};

///////////////////////////////////////////////////////////////////
// �Ƴ���ȴ
#define MSG_ACTION_COLD_REMOVE									37
// ��ȴ֪ͨ��������->�ͻ��ˣ�
struct SMsgActionColdRemove_SC
{
	DWORD	dwClassID;		// ��ȴ���ࣨ���ܣ���Ʒ������ȣ�
	DWORD	dwColdID;		// ��ȴID
};

///////////////////////////////////////////////////////////////////
// ʵ�帴��
#define MSG_ACTION_RELIVE										38
// ��Ϣ��
struct SMsgActionRelive_SC
{
	//.................
};

///////////////////////////////////////////////////////////////////
// �򿪱���
#define MSG_ACTION_OPENBOX										39
// ��Ϣ��
struct SMsgActionOpenBox_CS
{
	s64		uidBox;		// ����
};

///////////////////////////////////////////////////////////////////
// �رձ���
#define MSG_ACTION_CLOSEBOX										40
// ��Ϣ��
struct SMsgActionCloseBox_CS
{
	s64		uidBox;		// ����
};

///////////////////////////////////////////////////////////////////
// ������ʵ��
#define MSG_ACTION_CLICKMAST									41
// ��Ϣ��
struct SMsgActionClickMast_CS
{
	s64		uidMast;		// ����uid
};

// ���ܳ�ʼ����������->�ͻ��ˣ�
#define MSG_ACTION_SKILL_INIT									42

/////////////////////////////////////////////////////////////////
// ������Ʒ��
#define MSG_ACTION_CREATESKEP									43
// �ֳ�Ϊ SBuildSkepClientContext

// ����ʧ����Ϣ��������->�ͻ��ˣ�
#define MSG_ACTION_SKILL_FAILED									44
// ��Ϣ��
struct SMsgActionSkillFaile_SC
{
	DWORD		dwResult;			// ʧ��ԭ��
};

// ����ʧ����Ϣ��������->�ͻ��ˣ�
#define MSG_ACTION_CHANGE_FIGHT_STATUS							45
// ��Ϣ��
struct SMsgActionChangeFightStatus_SC
{
	s64	guid;				// Ŀ��
	BOOL		bStatus;			// �ı��״̬
};

// ���¼��ܵ㣨������->�ͻ��ˣ�
#define MSG_ACTION_UPDATA_SKILL_POINT							46

// �л�״̬��CS or SC��
#define MSG_ACTION_SWITCHSTATE									47
// ��Ϣ��
struct SMsgActionSwitchState_SC
{
	SMsgActionSwitchState_SC()
	{
		byState = 0;
		byLastState = 0;
		uidGood = 0;
	}
	BYTE		byState;			// ״̬(�ƶ���վ����������״̬)
	BYTE		byLastState;		// ֮ǰ��״̬
	s64	uidGood;			// ��ƷID������״̬�ı�Ϊ���״̬ʱ�������ͻ��˵���ƷID��
};

struct SMsgActionSwitchState_CS
{
	SMsgActionSwitchState_CS()
	{
		byState = 0;
		/// uidGood = 0;
	}
	BYTE		byState;			// ״̬(�ƶ���վ����������״̬)
	/// s64	uidGood;			// ��ƷID������״̬�ı�Ϊ���״̬ʱ�������ͻ��˵���ƷID��
};

// ֪ͨ�ͻ��˲���Ч
#define MSG_ACTION_PLAYSOUND									48
struct SMsgActionPlaySound_SS
{
	DWORD		dwSoundId;			// ��ЧId
	BYTE		bySendType;			// 0:���� 1:�Ź���㲥
};

struct SMsgActionPlaySound_SC
{
	DWORD		dwSoundId;			// ��ЧId
};

// ʹ�ü��ܣ�������-->��������
#define MSG_ACTION_USE_SKILL_UNCHECK							49
// ��Ϣ��
// struct SkillContext2

//////////////////////////////////////////////////////////////////////////
//////////////////////////////ContianerServer///////////////////////////////
//////////////////////////////////////////////////////////////////////////
// ���������������Ϣ��ͷ�ṹ
struct SContainerMsgHead : public S2CMsgHead
{
	SContainerMsgHead(WORD wMsg)
	{
		m_wMainCmd = CMD_ROOT_CONTAINER;
		m_wSubCmd = wMsg;
	}
};

// ������ͨ��ROOTTHING_SC_MAIN_ACTION�����ͻ��˵���Ϣͷ
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
	DWORD			dwSkepID;	// ������Ʒ��Id
};

// ��Ҽ佻�׷����������Ϣ��ͷ�ṹ
struct STradeMsgHead : public S2CMsgHead
{
	STradeMsgHead(WORD wMsg)
	{
		m_wMainCmd = CMD_ROOT_TRADE;
		m_wSubCmd = wMsg;
	}
};

///////////////////////////////////////////////////////////////////
// �л�PKģʽ
#define MSG_ACTION_SWITCHPKMODE									50
// ��Ϣ��
struct SMsgActionSwitchPKMode_CS
{
	int				nPKMode;	// PKģʽ
};

struct SMsgActionSwitchPKMode_SC
{
	int				nPKMode;	// PKģʽ
};

///////////////////////////////////////////////////////////////////
// �޸�PK������ɫ
#define MSG_ACTION_PKNAMECOLOR									51
// ��Ϣ��
struct SMsgActionPKNameColor_SC
{
	BYTE				nPKColor;	// ������ɫ
};

///////////////////////////////////////////////////////////////////
// ����װ��
#define MSG_ACTION_REPAIREQUIP									52
// ��Ϣ��
struct SMsgActionRepairEquip_CS
{
	s64		uidEquip;		// װ��
	// ���ΪINVALID_UID�����ʾ����װ��������װ��

	BYTE			byPacketSkep;	// ������
	// ���Ϊ1�����ʾװ���ڰ���������֮װ����
};

///////////////////////////////////////////////////////////////////
// npc ͷ����ʶ��
#define MSG_ACTION_NPC_HEAD_FLAG								53
struct SMsgActionNpcHeadFlag_SC
{
	/************************************************************************
	���ȼ�	��ʾ����	˵��
	1���ߣ�	��ɫ�ʺ�	�ɽ���һ������
	2			��ɫ�ʺ�	�ɽ���ÿ������
	3			��ɫ̾��	�ɻ�ȡһ������
	4			��ɫ̾��	�ɻ�ȡÿ������
	5			��ɫ�ʺ�	δ�������
	************************************************************************/
	enum
	{
		TASKSTATE_NORMAL = 0,						//
		TASKSTATE_CAN_COMPLETE,					// �����; �ɽ���һ������
		TASKSTATE_CAN_COMPLETE_DAILY,		// �ɽ���ÿ������
		TASKSTATE_CAN_ACCEPTE,						// �ɽ�; �ɻ�ȡһ������
		TASKSTATE_CAN_ACCEPTE_DAILY,			// �ɽ�ÿ������; 
		TASKSTATE_ACCEPTED,							// �Ѿ���
		TASKSTATE_NUM,				
	};

	s64	uidMonsterID;		// ����/Npc��guid
	BYTE		byState;						// ȡֵ��Χ��[TASKSTATE_NORMAL,TASKSTATE_NUM)

	SMsgActionNpcHeadFlag_SC()
	{
		memset(this,0,sizeof(SMsgActionNpcHeadFlag_SC));
	}
};

///////////////////////////////////////////////////////////////////
// ��ʼ������״̬
#define MSG_ACTION_STARTPROGRESS								54
// ��Ϣ��
struct SMsgActionStartProgress_CS
{
	BYTE byBarType;					// ����������
	int nTime;						// ����ʱ��
	char szName[32];				// ������������

};
struct SMsgActionStartProgress_SC
{
	s64 m_uidMaster;			// ������������
	BYTE	 byBarType;				// ����������
	int	 lActionId;				// ����Id
	int nTime;						// ����ʱ��
	char szName[32];				// ������������
	char szParentWndName[64];		// �����ڵ�����
	int x;							// ��������x���꣨���ص�λ��
	int y;							// ��������y���꣨���ص�λ��
	int width;						// ���ڵĿ����ص�λ��
	int height;						// ���ڵĸߣ����ص�λ��
};

///////////////////////////////////////////////////////////////////
// ����������״̬
#define MSG_ACTION_ENDPROGRESS									55
// ��Ϣ��
struct SMsgActionEndProgress_CS
{

};

struct SMsgActionEndProgress_SC
{
	s64 m_uidMaster;
	int		 nEndReason;			// ����ԭ��
};

// ��������״̬
#define MSG_ACTION_BOX_STATE_FLAG								56
struct SMsgActionBoxStateFlag_SC
{
	enum
	{
		ABSF_INVAILD = 0,		// ʧЧ״̬
		ABSF_ACTIVE,			// ����״̬
		ABSF_NUM,
	};
	
	int		lBoxID;			// �������ӵ�guid
	int		lType;			// ����
	BYTE		byState;		// ȡֵ��Χ��[ABSF_INVAILD,ABSF_NUM)

	SMsgActionBoxStateFlag_SC()
	{
		memset(this,0,sizeof(SMsgActionBoxStateFlag_SC));
	}
};

// ʹ��ҩƷ���
#define MSG_ACTION_USELEECHDOMRESULT								57
struct SMsgActionUseLeechdomResult_SC
{
	enum UseLeechdomResult
	{
		USELEECHDOMRESULT_FAIL,		// ʹ��ҩƷʧ��
		USELEECHDOMRESULT_SUCCESS,	// ʹ��ҩƷ�ɹ�
	};
	BYTE		byResult;		// ʹ��ҩƷ���
};

// ������ͨ��
#define MSG_ACTION_ERRORCODECHUNNEL									58
struct SMsgActionErrorCodeChunnel_SC
{
	BYTE		byErrorType;		// ��������
	WORD		wErrorCode;			// ������
	WORD		wErrorDespLen;		// ���������ַ�������
	//....��������
};

#define MSG_ACTION_CHANGELOCATION_FOR_SKILL							59
struct SMsgActionChangeLocationForSkill_SC
{
	POINT		ptTargetPos;		// Ŀ��λ��
	BYTE		byFlag;				// ���ܸı�λ������
	int			nCostTime;			// �ƶ���Ŀ�������ʱ��
};

///////////////////////////////////////////////////////////////////
// ����Ʒ
#define MSG_ACTION_THROWGOODS										60
// ��Ϣ��
struct SMsgActionThrowGoods_CS
{
	s64		uidGoods;
};

//////////////////////////////////////////////////////////////////
// С��,�л���ɫ
#define MSG_ACTION_CHANGEACTOR										61
// ��Ϣ��
struct SMsgActionChangeActor_CS
{

};
//���С�˵���Ϣ�ṹ
struct SC_Select : public SC_THING_HEAD
{
	DWORD ValidationCode[4];		//��֤�룬���ڵ�½��

	SC_Select()
	{
		m_wSubCmd = MSG_ACTION_CHANGEACTOR;
		memset(ValidationCode, 0, sizeof(ValidationCode));
	}
};


//////////////////////////////////////////////////////////////////
// ������
#define MSG_ACTION_SKILL_CAST_CHAIN									62
// ��Ϣ��
struct SkillChainContext
{
	s64	uidTarget;		/// ʹ�ü���ʱ�������λ���ϵ�ʵ�����
	POINT		ptTargetTile;	/// ʹ�ü���ʱ�������λ��
	s16			skillId;		/// ����ID
	int			result;			/// ���ܽ��

	BYTE		bChainCount;	/// ������Ŀ������
	// ..... s64	uidChainTarget; /// ������Ŀ�� ���

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
// ѯ���Ƿ���ܱ��˸���
#define MSG_ACTION_ASK_RELIVE										63
// ��Ϣ��
struct SMsgActionAskRelive
{
	s64		uidDoctor;		// ҽ����GUID
	int				nFlagIndex;		// �����ʶ

	SMsgActionAskRelive(void)
	{
		memset( this, 0, sizeof(SMsgActionAskRelive) );
	}
};

// ���Ƿ���ܸ���
#define MSG_ACTION_ANSWER_RELIVE									64
// ��Ϣ��
struct SMsgActionAnswerRelive
{
	BYTE			byAnswer;		// 1:���� 0:�ܾ�
	int				nFlagIndex;		// �����ʶ

	SMsgActionAnswerRelive(void)
	{
		memset( this, 0, sizeof(SMsgActionAnswerRelive) );
	}
};

//////////////////////////////////////////////////////////////////////////
// ��������Ʈ�֣�������->�ͻ��ˣ�
#define MSG_ACTION_FEW_TEXT											65
// ��Ϣ��
struct MsgActionFewText
{
	s64			tarUID;			/// ��ҪƮ�ֵ���
	WORD				ProNum;			/// ����ID
	int					nValue;			/// ��ֵ
};


//////////////////////////////////////////////////////////////////////////
// ���ø���
#define MSG_ACTION_RESET_ECTYPE										66
// ��Ϣ��
struct MsgActionResetEctype
{
	// ���޳�Ա
};

//////////////////////////////////////////////////////////////////////////
// ��ȴ֪ͨ��������->�ͻ��ˣ�
#define MSG_ACTION_SHARE_COLD_WORK									67
//struct SMsgActionColdWork_SC

//////////////////////////////////////////////////////////////////////////
// ȡ��С��
#define MSG_ACTION_CANCEL_CHANGEACTOR								68
// ��Ϣ��
struct SMsgActionCancelChangeActor_CS
{

};

//////////////////////////////////////////////////////////////////////////
// С�˿�ʼ����ʱ
#define MSG_ACTION_CHANGEACTOR_INTERVAL								69
// ��Ϣ��
struct SMsgActionChangeActorInterval_CS
{

};

//////////////////////////////////////////////////////////////////////////
// ����С��
#define MSG_ACTION_CHANGEACTOR_RIGHTNOW								70
// ��Ϣ��
struct SMsgActionChangeActorRightNow_CS
{

};

//////////////////////////////////////////////////////////////////////////
// ����npc��Ϣ
#define MSG_ACTION_SYNC_NPC_INFO									71
// ��Ϣ��
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

	BYTE	byPackNum;		// ���η���������
	BYTE	byPackIndex;	// ��ǰ�ڼ���
	int	lMapID;			// ��ͼID
	BYTE	byNum;			// npc ����
	// ...  npc_data;		// ����
};

//////////////////////////////////////////////////////////////////////////
// ��Npc����ѧϰ���
#define MSG_OPEN_NPC_TRAINSKILL										72
// ��Ϣ��
struct SMsgActionTalkToTrainSkillNpc_SC
{
	s64	llNpcUID;		// Npc guid
};

//////////////////////////////////////////////////////////////////////////
// ͨ��NPCѧϰ���ܣ�������-->�ͻ��ˣ�
#define MSG_LEARN_SKILL_FROM_NPC									73
// ��Ϣ��
struct SMsgActionLearnSkillFromNpc_CS
{
	s64	llNpcUID;		// Npc guid
	WORD		wSkillID;		// ����id
};

//////////////////////////////////////////////////////////////////////////
// �������ܣ�������-->�ͻ��ˣ� 
#define MSG_ACTION_FORGET_SKILL										74
// ��Ϣ��
// WORD wSkillId;		/// ����ID

//////////////////////////////////////////////////////////////////////////
// ��������Ǳ�ܣ�������-->�ͻ��ˣ� 
#define MSG_ACTION_FORGET_ALL_SKILL									75
// ��Ϣ�壨�ޣ�


// ����Ŀ��GUID
#define MSG_ACTION_SET_TARGET										76
// ��Ϣ��
struct SMsgActionSetTarget
{
	s64		uidTarget;

	SMsgActionSetTarget(void)
	{
		memset( this, 0, sizeof(SMsgActionSetTarget) );
	}
};

//////////////////////////////////////////////////////////////////////////
// �����ٻ���ģʽ��������<-->�ͻ��ˣ� 
#define MSG_ACTION_CALLANIMAL_AIMODE								77
// ��Ϣ��
// BYTE bMode;			// AIģʽ

//////////////////////////////////////////////////////////////////////////
// �ٻ��޹������ͻ���-->�������� 
#define MSG_ACTION_CALLANIMAL_ATTACK								78
// ��Ϣ��
// s64	tarUID;    // Ŀ��Guid

//////////////////////////////////////////////////////////////////////////
// ��ɢĳֻ�ٻ��ޣ��ͻ���-->�������� 
#define MSG_ACTION_FREE_CALLANIMAL									79
// ��Ϣ��
// s64	tarUID;    // �ٻ���Guid

///////////////////////////////////////////////////////////////////
// ����������
#define MSG_ACTION_CLICK_GAMEOBJ									80
// ��Ϣ��
struct SMsgActionClickGameObj_CS
{
	s64		uidGameObj;		// GameObj��UID

	SMsgActionClickGameObj_CS(void)
	{
		memset( this, 0, sizeof(*this) );
	}
};

//////////////////////////////////////////////////////////////////////////
// ͬ��������ʱ��
#define MSG_ACTION_SYNC_SERVERTICKS									81
// ��Ϣ��
struct SMsgActionSyncServerTicks_SC
{
	DWORD			dwServerTicks;	// ��ҵ�¼����ʧ��ʱ��(ms)

	SMsgActionSyncServerTicks_SC(void)
	{
		memset( this, 0, sizeof(*this) );
	}
};

//////////////////////////////////////////////////////////////////////////
// ���buff
#define MSG_ACTION_WORLD_OBJECT_INIT_BUFF							82

// �鿴����װ����������->�ͻ��ˣ�
#define MSG_ACTION_LOOK_ACTOR_EQUIP									83

// ���󴴽��ͻ��˲ֿⲿ����Ϣ���ͻ���->��������
// ֪ͨ�Լ������ֿⲿ����Ϣ��������->�ͻ��ˣ�
#define MSG_ACTION_BUILDSTORAGE										84

// ֪ͨ�ͻ��˴򿪲ֿ���棨������->�ͻ��ˣ�
#define MSG_ACTION_OPENSTORAGE										85

// �������㣨������->�ͻ��ˣ�
#define MSG_ACTION_UPDATA_AIR_POINT									86

// ������ͨ����(������->�ͻ���)
#define MSG_ACTION_SORT_PACKET										87
struct SMsgActionSortedGoodsInfo_CS
{
	s64		uidGoods;		//�����ŵ���Ʒ��GUID
	BYTE			byPacketIdx;	//����֮�����ĸ�������
	BYTE			byLoc;			//����֮���������е�λ��
};
struct SMsgActionSortedInfo_CS
{
	BYTE			bySortedNum;	//������Ʒ������
};

// �����������(������->�ͻ���)
#define MSG_ACTION_SORT_TASK_PACKET									88

// �����ӳ�ɾ��ʵ��(������->������)
#define MSG_ACTION_RELAY_DELETE_ENTITY								89
struct SMsgActionRelayDeleteEntity_SS
{
	s64		uidEntity;			// ʵ��UID
};

//���������ϰ��ƶ�
#define MSG_ACTION_IGNORE_OBSTALE_MOVE								113


////////////////////////////////////////////////////////////////////////////////////
/// �������
/// 
/// ֪ͨ�Լ���������װ����������Ϣ
/// ��Ϣ����ΪS2CMsgHead
#define MSG_ACTION_BUILD_PET_EQUIPPACKET							114
struct SMsgActionBuildHeroEquipPacket_SC
{
	s64		uidHero;		// Ӷ��UID
};

/// �����б�������->�ͻ��ˣ�
#define MSG_ACTION_PET_DATA_LIST									115

/// ����������ͻ���->��������������->�ͻ��ˣ��������˳�ս����Ϣ������
#define MSG_ACTION_PET_OP											116

/// �����޸����ƣ��ͻ���->��������������->�ͻ��ˣ�
#define MSG_ACTION_PET_MOD_NAME										117

/// �����޸����ƹ㲥���ͻ��ˣ�������->�ͻ��ˣ�
#define MSG_ACTION_PET_NAME											118

/// ���ó���AI��������->�ͻ���
#define MSG_ACTION_SET_PET_AI										119
////////////////////////////////////////////////////////////////////////////////////


////////////////////////////////////////////////////////////////////////////////////

// ʹ�ü��ܣ��ͻ���-->��������
#define MSG_ACTION_USE_SKILL_PET									120

//////////////////////////////////////////////////////////////////////////
// ѧϰ���ܣ�������-->�ͻ��ˣ� 
#define MSG_ACTION_UPGRADE_SKILL_PET								121

//////////////////////////////////////////////////////////////////////////
// �������ܣ�������-->�ͻ��ˣ� 
#define MSG_ACTION_FORGET_SKILL_PET									122
// ��Ϣ��
// int lPetID;			/// ����ID
// WORD wSkillId;		/// ����ID

//////////////////////////////////////////////////////////////////////////
// ��������Ǳ�ܣ�������-->�ͻ��ˣ� 
#define MSG_ACTION_FORGET_ALL_SKILL_PET								123
// ��Ϣ�壨�ޣ�

//////////////////////////////////////////////////////////////////////////
// ��ȴ��ʼ������
#define MSG_ACTION_INITCOLD_PET										124
// ��Ϣ��
//struct SMsgActionInitCold_SC

//////////////////////////////////////////////////////////////////////////
// ��ȴ֪ͨ��������->�ͻ��ˣ�
#define MSG_ACTION_SHARE_COLD_WORK_PET								125
//struct SMsgActionColdWork_SC

//////////////////////////////////////////////////////////////////////////
// ��ȴ֪ͨ��������->�ͻ��ˣ�
#define MSG_ACTION_COLD_WORK_PET									126
//struct SMsgActionColdWork_SC

// ���ܳ�ʼ����������->�ͻ��ˣ�
#define MSG_ACTION_SKILL_INIT_PET									127


/// ��Ƕ��װ��ʯ��װ���ϣ��ͻ���->��������
#define MSG_MAKE_SUIT_STONE_EQUIP									128
struct CMsgMakeSuitStoneEquipCmd
{
	s64 uidEquip;			/// װ��UID
	s64 uidStone;			/// ��װ��ʯUID

	CMsgMakeSuitStoneEquipCmd()
	{
		uidEquip = 0;
		uidStone = 0;
	}
};

/// ��Ƕ��װ��ʯ��װ���Ͻ����������->�ͻ��ˣ�
#define MSG_RET_MAKE_SUIT_STONE_EQUIP									129
struct CMsgRetMakeSuitStoneEquipCmd
{
	BYTE byRet;					/// �����0��ʧ�ܣ�1���ɹ���
	BYTE byTp;					/// ���ͣ�0����Ƕ��1��������2��ȡ�±�ʯ��

	CMsgRetMakeSuitStoneEquipCmd()
	{
		byRet = 0;
		byTp = 0;
	}
};

/// ��Ƕ��װ��ʯ����򿪣�������->�ͻ��ˣ�
#define MSG_OPEN_MAKE_SUIT_STONE_EQUIP									130
struct CMsgOpenMakeSuitStoneEquipCmd
{
	BYTE byTp;				/// ���ͣ�0����Ƕ��1��������2��ȡ�±�ʯ��

	CMsgOpenMakeSuitStoneEquipCmd()
	{
		byTp = 0;
	}
};

/// ��װ�������ͻ���->��������
#define MSG_UPGRADE_SUIT_EQUIP											131
struct CMsgUpgradeSuitEquipCmd
{
	s64 uidEquip;			/// װ��UID

	CMsgUpgradeSuitEquipCmd()
	{
		uidEquip = 0;
	}
};

/// ��װ��ʯȡ�£��ͻ���->��������
#define MSG_TAKE_DOWN_SUIT_STONE										132
struct CMsgTakeDownSuitStoneCmd
{
	s64 uidEquip;			/// װ��UID

	CMsgTakeDownSuitStoneCmd()
	{
		uidEquip = 0;
	}
};

// ���壨�ͻ���-->��������
#define MSG_ACTION_RELEASE_PET											133

// �����츳ϵ���ͻ���<-->��������
#define MSG_ACTION_UPDATA_QN_GROUP										134
// �ṹ�� 
// BYTE	 byGroup;			/// ����ϵ

// �Ƴ�buff���ͻ���-->��������
#define MSG_ACTION_REMOVE_BUFF_REQUEST									135
// �ṹ�� 
// WORD	 wBuffID;			/// buffID

/// װ��������Լ���
#define MSG_ACTION_APPRAISE_RANDOM_EFFECT								136
struct CMsgActionAppraiseRandomEffectCmd
{
	s64 uidEquip;			/// װ��UID
	s64 uidAppraise;		/// ��������UID

	CMsgActionAppraiseRandomEffectCmd()
	{
		uidEquip = 0;
		uidAppraise = 0;
	}
};

///////////////////////////////////////////////////////////////////
// �������㲥����ƶ���Ϣ���Ź������������
#define MSG_SC_ACTION_CLIENT_MOVE										138
// ��Ϣ��
struct SMsgActionClientMove_SC
{
	WSPOINT		ptFrom;			// ���
	WSPOINT		ptTo;			// �յ�
};

/// ����ping��
#define MSG_ACTION_NETWORK_PING											139
struct SMsgActionNetworkPingCmd
{
	// ping������
	DWORD dwPingIndex;
};

//////////////////////////////////////////////////////////////////////////
// �˳�ս�����ͻ���-->��������
#define MSG_ACTION_EXIT_BATTLE											140

//////////////////////////////////////////////////////////////////////////
// ����ս�����ͻ���-->��������
#define MSG_ACTION_REQ_BATTLE											141
struct SMsgActionReqBattle
{
	s32	nMatchType;			// ƥ������

	SMsgActionReqBattle()
	{
		nMatchType = 0;
	}
};

//////////////////////////////////////////////////////////////////////////
// ���󴴽�Ӷ�����ͻ���-->��������
#define MSG_ACTION_REQ_NEWHERO											142
struct SMsgActionNewHero
{
	s32 nHeroTemplateID;		// Ӣ��ģ��ID
	s32 nHeroLv;				// Ӣ�۵ȼ�

	SMsgActionNewHero()
	{
		nHeroTemplateID = 0;
		nHeroLv = 0;
	}
};

//////////////////////////////////////////////////////////////////////////
// �����˳�ս�����ͻ���-->��������
#define MSG_ACTION_REQ_EXIT_ROOM										 143

//////////////////////////////////////////////////////////////////////////
// ���󽻻���ʯ���ͻ���-->��������
#define MSG_ACTION_SWAP_GEM												 144
struct SMsgActionSwapGem
{
	s8 nSwapSrc;		// ����Դ
	s8 nSwapDst;		// ����Ŀ��

	SMsgActionSwapGem()
	{
		nSwapSrc = 0;
		nSwapDst = 0;
	}
};
// ���󽻻���ʯ��������-->�ͻ��ˣ�
struct SMsgActionSwapGemSvr
{
	s64 nSwapUID;		// ������UID
	s8 nSwapSrc;			// ����Դ
	s8 nSwapDst;			// ����Ŀ��
	// s8 bGemType;			// ��ʯ * n

	SMsgActionSwapGemSvr()
	{
		nSwapUID = 0;
		nSwapSrc = 0;
		nSwapDst = 0;
	}
};

//////////////////////////////////////////////////////////////////////////
// ��ʯ���̴�����������-->�ͻ��ˣ�
#define MSG_ACTION_NEW_GEM_MAP											  145

//////////////////////////////////////////////////////////////////////////
// ��ʼ������Դ��������-->�ͻ��ˣ�
#define MSG_ACTION_BEGIN_LOAD											  146

//////////////////////////////////////////////////////////////////////////
// ��Ϸ��ʼ��������<-->�ͻ��ˣ�
#define MSG_ACTION_ROOM_BEGIN											  147
struct SMsgActionRoomBegin
{
	char	arrSitIDTurns[6];		// ��Ϸ��ʼʱ,ÿ����λ�ϵ���ҵ��Ⱥ���˳��

	SMsgActionRoomBegin()
	{
		memset(arrSitIDTurns, -1, sizeof(arrSitIDTurns));
	}
};

//////////////////////////////////////////////////////////////////////////
// �غϽ�����������-->�ͻ��ˣ�
#define MSG_ACTION_ROUND_END											  148
// �غϽ�����������-->�ͻ��ˣ�
struct SMsgActionRoundEnd
{
	s8 nUseTime;		// ����ʱ��

	SMsgActionRoundEnd()
	{
		nUseTime = 0;
	}
};

//////////////////////////////////////////////////////////////////////////
// ͬ�����ؽ��ȣ�������<-->�ͻ��ˣ�
#define MSG_ACTION_SYNCLOAD												  149
// ͬ�����ؽ��ȣ�������<--�ͻ��ˣ�
struct SMsgActionSyncLoad_CS
{
	u8	byLoadState;	// ���ؽ���

	SMsgActionSyncLoad_CS()
	{
		byLoadState = 0;
	}
};
// ͬ�����ؽ��ȣ�������-->�ͻ��ˣ�
struct SMsgActionSyncLoad_SC
{
	u32 dwActorId;		// ��ҽ�ɫID
	u8	byLoadState;	// ���ؽ���

	SMsgActionSyncLoad_SC()
	{
		dwActorId = 0;
		byLoadState = 0;
	}
};

//��ӶӶ�����ؽ����S2C��
#define MSG_ACTION_RES_BUYHERO											150
struct SMsgActionBuyHeroRes
{
	DWORD res;
};

//Ӷ������
#define MSG_ACTION_HERO_LVUP											151
struct SMsgActionHeroLevelUp
{
	s32 nHeroIdx;		// Ӣ��λ��
	s32 nHeroDstLv;		// Ӣ��Ҫת����Ŀ��ȼ�
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

//Ӷ������
#define MSG_ACTION_LEARN_SKILL											152
struct SMsgActionHeroLearnSkill
{
	s32 nSkillIdx;		// ��������
	s32 nHeroDstLv;		// Ӣ��Ҫת����Ŀ��ȼ�
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
// ���buff
#define MSG_ACTION_WORLD_OBJECT_INIT_TOTEM_BUFF							153

// ���buff
#define MSG_ACTION_WORLD_OBJECT_ADD_TOTEM_BUFF							154
struct SMsgActionWorldObjectAddTotemBuff_SC
{
	s8				dwIndex;				// ����	
	u16				dwBuffId;				// buff ID	
	s16				dwTime;					// ʣ��ʱ��	
	s64		uidAdd;					// �����
};

// ���buff
#define MSG_ACTION_WORLD_OBJECT_REMOVE_TOTEM_BUFF						155
struct SMsgActionWorldObjectRemoveTotemBuff_SC
{
	s8				dwIndex;				// ����	
	u16				dwBuffId;				// buff ID	
	s64		uidRemove;				// ɾ����
};

#define MSG_ACTION_GAME_END_RESULT										156

struct SMsgActionGameEndResult
{
	u32 nPNum;
	struct HeroGameEndResult
	{
		u32 nbTotalMage;	//�ܵ����˺�����ֵ
		u32 ndTotalMage;	//������˺�����ֵ
		u32 nOneMage;		//��������˺�����ֵ
		u32 nFourStraNum;	//������
		u32 nFiveStraNum;	//������
		u32 nSixStraNum;	//������
		u32 nSevenStraNum;  //������
		u32 nMaxComBoxs;	//���������
		u32 nTotalGem;		//������ʯ��
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
// ��ͨ������������-->�ͻ��ˣ�
#define MSG_ACTION_NOMAL_ATTACK											158
struct SAttackContext
{
	s64	uidTarget;

	SAttackContext()	
	{
		memset(this, 0, sizeof(SAttackContext)); 
	}
};

// ������������������-->�ͻ��ˣ�
#define MSG_ACTION_NOMAL_ATTACK_END										159

//��Ƭǿ��
#define MSG_ACTION_STRENGTHEN_CARD										160
struct StrengthenCard_CS
{
	s32		 type;
	s32		 createGoodsID;		//����ID
	s64 uidCard1;			//��Ƭ1
	s64 uidCard2;			//��Ƭ2
	s64 luckyStoneID;		//����ʯ
	s64 uidGoods1;			//��Ƭ2
	s64 uidGoods2;			//��Ƭ2
	s64 uidGoods3;			//��Ƭ2
};
struct Strengthen_CS
{
	s32		 type;
	s32		 StrengthenID;		//����ID
	s64 uidGoodsMain;		//������
	s64 uidGoods1;			//��Ʒ1
	s64 uidGoods2;			//��Ʒ2
	s64 uidGoods3;			//��Ʒ3
	s64 uidGoods4;			//��Ʒ4
	s64 uidGoods5;			//��Ʒ5
};
struct StrengthenEquip_CS
{       
        s32              type;
        s32              StrengthenID;         //����ID
        s64 uidEquip;                   //װ��
        s64 uidStone;                   //ǿ��ʯ
        s32 nRmbCount;               	//����˼�����ʯ
};  

#define MSG_ACTION_STRENGTHEN_CARD_RES									161
struct StrengthenCardRes_SC
{
	s32   type;
	DWORD res;
};

// ֪ͨǰ�˴򿪳齱���棨������-->�ͻ��ˣ�
#define MSG_ACTION_ADD_A_DROP											162
struct SMsgActionAddADrop_SC
{
	u8	bDropIndex;			// �齱����
	s32 nGoodID[3];			// ��ƷID
	s32 nGoodNum[3];		// ��Ʒ����

	SMsgActionAddADrop_SC()
	{
		memset(this, 0, sizeof(*this));
	}
};

// �齱���ͻ���-->��������
#define MSG_ACTION_ROLL_DROP											163
struct SMsgActionRollDrop_CS
{
	u8	bDropIndex;			// �齱����
	u8	bItemSlot;			// �齱��Ʒλ��
};

// �齱��Ʒ��������-->�ͻ��ˣ�
struct SMsgActionRollDrop_SC
{
	u8	bDropIndex;			// �齱����
	u8	bItemSlot;			// �齱��Ʒλ��
	s32	nGoodID;			// ��ƷID
	s32 nGoodNum;			// ��Ʒ����
};

// ��ȡ�������ͻ���<-->��������
#define MSG_ACTION_GET_DROP_PRIZE										164
// �ṹ�� SMsgActionRollDrop_CS

// ��ʼ���齱��������-->�ͻ��ˣ�
#define MSG_ACTION_INIT_A_DROP											165
// struct SMsgActionAddADrop_SC

//////////////////////////////////////////////////////////////////////////
// ����ѵ�����ͻ���-->��������
#define MSG_ACTION_TRAIN_DUMMY											166
struct SMsgActionTrainDummy
{
	SMsgActionTrainDummy()
	{
	}
};

struct SMsgRankInfo
{
	s32		nRank;		// ����
	s64		qwUserID;	// �˺�ID
	s32		lLevel;		// �ȼ�

	SMsgRankInfo()
	{
		memset(this, 0, sizeof(*this));
	}
};

struct SMsgActionTrainRank
{
  SMsgRankInfo	arrRankInfo[6];	// ���������Ϣ

  SMsgActionTrainRank()
  {
    memset(this, 0, sizeof(*this));
  }
};

///////////////////////////////////////////////////////////////////////////////

// �����������ȣ��ͻ���-->��������
#define MSG_ACTION_GUIDER_STEP											167
struct SMsgActionGuiderStep
{
	u8	bStepID;			// ������
	SMsgActionGuiderStep()
	{
		bStepID = 0;
	}
};

// ����̨����ͻ���-->��������
#define MSG_ACTION_CONSOLE_CMD											168

//// ����ؿ����ͻ���-->��������
//#define MSG_ACTION_TRAIN_INSTANCE										169

struct SBoxDropGoodsInfo
{
	s32		nGoodsID;		// ��ƷID
	s32		nGoodsNum;		// ��Ʒ����

	SBoxDropGoodsInfo()
	{
		memset(this, 0, sizeof(*this));
	}
};

// ֪ͨǰ�˴򿪿�������棨������-->�ͻ��ˣ�
#define MSG_ACTION_ADD_BOX_DROP											170
struct SMsgActionAddBoxDrop_SC
{
	s32		nTotalNum;		// ���ٸ���Ʒ��Ϣ

	SMsgActionAddBoxDrop_SC()
	{
		memset(this, 0, sizeof(*this));
	}
};

//////////////////////////////////////////////////////////////////////////
// ����ѵ�����أ�������-->�ͻ��ˣ�
#define MSG_ACTION_RESULT_TRAIN_DUMMY									171
struct SMsgActionResultTrainDummy_SC
{
	u8		byObjectType;					// ��������
	s64		qwUnitID;						// ����ID������Ϊ�˺�ID, ����Ϊģ��ID��
	s8		bySex;							// �Ա�
	s8		byHeadPortraitId;				// ͷ��ID
	u8		byLevel;						// �ȼ�

	SMsgActionResultTrainDummy_SC()
	{
		memset(this, 0, sizeof(*this));
	}
};

//////////////////////////////////////////////////////////////////////////
// ���󹥻����ˣ��ͻ���-->��������
#define MSG_ACTION_ATTACK_DUMMY											172
struct SMsgActionAttackDummy
{
	s64		qwUserID;					// �˺�ID
	s32		nFightCountRMB;		// ��Ǯ����1��ս������
	s32		nCDTimeRMB;		    // ��Ǯ����1��ս��CD

	SMsgActionAttackDummy()
	{
	}
};

//֪ͨ�ͻ��˷��������¶���������-->�ͻ���-->��������
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
	s32 nFeedTempID;//ƽ̨�����¶����ɵ�ID
	SMsgActionSendFeed_CS()	
	{
		memset(this, 0, sizeof(SMsgActionSendFeed_CS)); 
	}

};

// �������������ƺ�(�ͻ���-->��������
#define MSG_ACTION_REPUTATION_TITLE_UPDATA						174

// ����ÿ�������������ͻ���-->��������
#define MSG_ACTION_REQUEST_TITLE_PRIZE								175

//��ʼ�������б�
#define MSG_ACTION_INIT_STRENGTHEN_LIST									177

#define MSG_ACTIO_WORKFINISH_GETGOOD									178
struct SMsgActionWorkFinishGetGood_SC
{
	DWORD	dwClassID;		// ��ȴ���ࣨ���ܣ���Ʒ������ȣ�
	DWORD	dwColdID;		// ��ȴID

	SMsgActionWorkFinishGetGood_SC()
	{
		memset(this, 0, sizeof(*this)); 
	}
};

// �����̵���Ʒ
#define MSG_ACTION_BUY_SHOP_ITEM										179
struct SMsgActionBuyShopItem_CS
{
	s16		nShopIndex;		// �̵���ƷΨһID
	s16		nCount;			// ����

	SMsgActionBuyShopItem_CS()
	{
		memset(this, 0, sizeof(*this)); 
	}
};

// ��ȡ����������Ʒ
#define MSG_ACTION_GET_REWARDGOODS										183
struct SMsgActionGetRewardGoods_CS
{
	s32 lRewardType;      // �������ͣ�1������Ľ�����2��ǰ��δ��Ľ�����
	SMsgActionGetRewardGoods_CS()
	{
		memset(this,0,sizeof(*this));
	}
};

#define MSG_ACTION_GET_REWARDGOODS_RES									184
struct SMsgActionSetRewardGoodsRes_SC
{
	s32 lRewardType;      // �������ͣ�1������Ľ�����2��ǰ��δ��Ľ�����
	DWORD lGetRewardRes;      // ��ȡ�������
	SMsgActionSetRewardGoodsRes_SC()
	{
		memset(this,0,sizeof(*this));
	}
};

// ������ֵ
#define MSG_ACTION_BUY_ENERGY_POINT										186
struct SMsgActionBuyEnergyPoint_CS
{
	s16		nCount;			// ����

	SMsgActionBuyEnergyPoint_CS()
	{
		memset(this, 0, sizeof(*this)); 
	}
};

// ��ȡ������½����
#define MSG_ACTION_GET_LOGIN_PRIZE										187

// ��ȡ������ѽ���
#define MSG_ACTION_GET_FRIEND_PRIZE										188
struct SMsgActionGetFriendPrize_CS
{
	s16		nCount;			// �����������
	s16		nVCount;		// ����V��������
	
	SMsgActionGetFriendPrize_CS()
	{
		memset(this, 0, sizeof(*this));
	}
};

// �����˺�ͷ��URL
#define MSG_ACTION_SET_HEAD_URL											189
struct SMsgActionSetHeadURL_CS
{
	char		szHeadURL[256];			// �����Լ����˺�ͷ��URL

	SMsgActionSetHeadURL_CS()
	{
		memset(this, 0, sizeof(*this)); 
	}
};


// ��ȡ�˺�ͷ��URL
#define MSG_ACTION_GET_HEAD_URL											190
struct SMsgActionGetHeadURL_CS
{
	s64			qwUserID;				// �˺�ID

	SMsgActionGetHeadURL_CS()
	{
		memset(this, 0, sizeof(*this)); 
	}
};

struct SMsgActionGetHeadURL_SC
{
	s64			qwUserID;				// �˺�ID
	char		szActorName[13];		// ��ɫ��
	char		szHeadURL[256];			// �˺�ͷ��URL
	char			sOpenId[64];			// OpenID

	SMsgActionGetHeadURL_SC()
	{
		memset(this, 0, sizeof(*this)); 
	}
};

//////////////////////////////////////////////////////////////////////////
// �����ȡ�д���ѣ��ͻ���-->��������
#define MSG_ACTION_PK_FRIEND											191
struct SMsgActionPKFriend
{
	s64			qwUserID;				// �˺�ID

	SMsgActionPKFriend()
	{
	}
};

// �����»��ֳ齱���ͻ���-->��������
#define MSG_ACTION_FEED_SCORE_ROLL										192
struct SMsgActionFeedScoreRoll_CS
{
	u8	bScoreIndex;		// �콱���
	u8	byRollType;			// �齱����
};

// �����»��ֳ齱��������-->�ͻ��ˣ�
struct SMsgActionFeedScoreRoll_SC
{
	u8	byResult;			// �齱�Ƿ�ɹ�(0:ʧ��, 1:�ɹ�)
	u8	bItemSlot;			// �齱��Ʒλ��
};

// ��ȡÿ�ս������ͻ���-->��������
#define MSG_ACTION_GET_EVERYDAY_PRIZE									193
// u8 bType;				// ����

// ����vip���ͻ���-->��������
#define MSG_ACTION_BUY_VIP												194
// u8 bCount;				// ����

// ��Լ��Ƭ( �ͻ���-->������ )
#define MSG_ACTION_BUY_CARD_ENDURE										195
struct SMsgActionBuyCardEndure_CS
{
	s64				uidEquip;		// װ��
	u8				byPacketSkep;	// ������
	// ���Ϊ1�����ʾװ���ڰ���������֮װ����
};

// ��Լ��Ƭ��������-->�ͻ��ˣ�
struct SMsgActionBuyCardEndure_SC
{
	u8	byResult;			// ��Լ�Ƿ�ɹ�(0:ʧ��, 1:�ɹ�)
};

// ǿ������( �ͻ���-->������ )
#define MSG_ACTION_STRENGTH_LEVELUP										196
struct SMsgActionStrengthLevelUp_CS
{
	s32				lType;			// ǿ������
	s32				lLevelUpType;	// ������ʽ
};

// ǿ������( �ͻ���-->������ )
#define MSG_ACTION_STRENGTH_BUY											197
struct SMsgActionStrengthBuy_CS
{
	s32				arrGoodsID[6];			// ������ƷID
	s32				arrGoodsNum[6];			// ������Ʒ����
};

// �������( �ͻ���-->������ )
#define MSG_ACTION_STRENGTHOVER_RIGHTNOW                                                                        198
struct SMsgActionStrengthOverRightNow_CS
{
	s32				nColdClass;			// ��ȴ����
        s32                             nColdID;			// ��ȴID
};

// ��Ƭ�������( ������-->�ͻ��� ) 
#define MSG_ACTION_CARD_ENDURE_INFO										199
// ��Ϣ��
struct SMsgActionCardEndureInfo_SC
{
	struct SCardEndureInfo
	{
		s32			nCardSlot;			// ��Ƭ���ڲ�λ
		s32			nCardID;			// ��Ƭģ��ID
	};
};

// ���������Ŀ�Ƭ( �ͻ���-->������ )
#define MSG_ACTION_BUY_LOST_CARD										200
// ��Ϣ��
struct SMsgActionBuyLostCard_CS
{
	s32	nCardSlot;						// ��Ƭ���ڲ�λ
	s32	nCardID;						// ��Ƭģ��ID
};

// ����ƽ̨���ѵ��ռ���ʼ�����ݣ��ͻ���->��������
#define MSG_ACTION_REQUEST_COLLECT_DATA             201
struct SMsgActionRequestCollectData_CS
{
  SMsgActionRequestCollectData_CS() :
    wSize(0) {}
  s16 wSize;                // ���ݸ���
  u64 qwUserIDs[0];         // �û�ID��
};

// ����û���ռ�����ƽ̨���ѵ��ռ���ʼ�����ݣ�������->�ͻ��ˣ�
#define MSG_ACTION_RESPONSE_COLLECT_DATA            202
struct SMsgActionResponseCollectData_SC
{
  SMsgActionResponseCollectData_SC() :
    wSize(0) {}
  u16 wSize;                   // ���ݸ���
  u64 friendUserIDs[0];        // ���ѵ��û�ID����
};

// �ͻ�������ͬ��ʱ�䣨�ͻ���->��������
#define MSG_ACTION_REQUEST_SYNC_TIME                203

// ��ͻ���ͬ��ʱ�䣨������->�ͻ��ˣ�
#define MSG_ACTION_SYNC_TIME                        204
struct SMsgActionSyncTime_SC
{
  SMsgActionSyncTime_SC() : qwTime(0) {}
  s64 qwTime;                 // ʱ��
};

// �ͻ��˷���ƽ̨�����ռ���ʼ���ͻ���->��������
#define MSG_ACTION_REQUEST_COLLECT_START            205
struct SMsgActionRequestCollectStart_CS
{
  SMsgActionRequestCollectStart_CS() : qwFriendUserID(0) {}
  u64 qwFriendUserID;         // �����û�ID
};

// �ظ��ͻ����Ƿ���Կ�ʼ�ռ���������->�ͻ��ˣ�
#define MSG_ACTION_RESPONSE_COLLECT_START            206
struct SMsgActionResponseCollectStart_CS
{
  SMsgActionResponseCollectStart_CS() : qwFriendUserID(0) {}
  u64 qwFriendUserID;         // �����û�ID
  u8 result;                  // 0:�����ԣ�1������
};

// �ͻ��˷���ƽ̨�����ռ��������ͻ���->��������
#define MSG_ACTION_REQUEST_COLLECT_END              207
struct SMsgActionRequestCollectEnd_CS
{
  SMsgActionRequestCollectEnd_CS() :
    qwFriendUserID(0), dwMoneyNum(0) {}
  u64 qwFriendUserID;         // ����USERID
  u32 arrGoodNum[5];          // �ء�ˮ���𡢷硢�׶�Ӧ������Ʒ����
  u32 dwMoneyNum;             // ��Ǯ����
  u8 isDoubleAward;           // �Ƿ�ӱ�������0�����ӱ���1���ӱ�
};

// ���������ͳ齱������ͻ���<--��������
#define MSG_ACTION_DAY_ROLL_RESULT                  208
// u8 bIdx;                   // ���еڼ�����1~8��

#define MSG_ACTION_ONLINE_TIME			                209
// �ͻ���->������ ���÷����������ۼ�����ʱ��
struct SMsgActionSetRemoteOnlineTime_CS
{
	s32	nOnlineTime;	// ƽ̨ͳ�Ƶ�����ʱ��
	SMsgActionSetRemoteOnlineTime_CS()
	{
		memset(this, 0, sizeof(*this));	
	}
};

// ������->�ͻ��� ����ƽ̨ͳ�Ƶ����ۼ�����ʱ��
struct SMsgActionGetOnlineTime_SC
{
	SMsgActionGetOnlineTime_SC()
	{
	}
};

#define MSG_ACTION_GET_PVPPRIZE                                  210
// �ͻ��->������ ��ȡPVP�����
struct SMsgActionGetPVPPrize_CS
{
	s32	lType;		// 0:PVPս������ 1:PVPʤ������

	SMsgActionGetPVPPrize_CS()
	{
		memset(this, 0, sizeof(*this));
	}
};

#define MSG_ACTION_OPEN_SURFACE                 211
// �ͻ���->������ �򿪽���
struct SMsgActionOpenSurface_CS
{
  u32 dwSurfaceID;    // ����ID

  SMsgActionOpenSurface_CS() : dwSurfaceID(0) {}
};

#define MSG_ACTION_GET_INSTANCE_PRIZE		212
// �ͻ���->������ ��ȡ��Ƭ����
struct SMsgActionGetInstancePrize_CS
{
	s32	nMapID;		// ���ͼID
	s32	nPrizeID;	// ����ID

	SMsgActionGetInstancePrize_CS()
	{
		memset(this, 0, sizeof(*this));
	}
};

#define MSG_ACTION_GET_INSTANCE_MONEY		213
// �ͻ���->������ �ջ���Ϸ�һ���ǿ��������Ϸ��
struct SMsgActionGetInstanceMoney
{
	s32	nType;		// 0 : ����; 1 : ǿ������

	SMsgActionGetInstanceMoney()
	{
                memset(this, 0, sizeof(*this));
        }
};

// ��ʯ�˺���������-->�ͻ��ˣ�
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

// �ͻ���->������ ��ȡ��������
#define MSG_ACTION_GET_GOODSGIFT                215
struct SMsgActionGetGoodsGift_CS
{
        SMsgActionGetGoodsGift_CS()
        {
                memset(this, 0, sizeof(*this));
        }
};

// ��ȡQ���ֵ(�ͻ���--->������)
#define MSG_ACTION_QQPOINT_PRIZE		254
struct SMsgActionQQPointPrize_CS
{
	SMsgActionQQPointPrize_CS()
	{
		memset(this, 0, sizeof(*this));
	}
};

// �ͻ���->������ ��ȡ������ս��¼
#define MSG_ACTION_GET_RANKRECORD                216
struct SMsgActionGetRankRecord_CS
{
	SMsgActionGetRankRecord_CS()
        {
                memset(this, 0, sizeof(*this));
        }
};
// ������->�ͻ��� ������ս��¼
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

// �ͻ���->������ �ֽ⿨Ƭ
#define MSG_ACTION_DECOMPOSECARD		217
struct SMsgActionDecomposeCard_CS
{
	s8	byType;		// 0:�����, 1:������
	s64	guidCard;	// ��ƬGUID

	SMsgActionDecomposeCard_CS()
	{
                memset(this, 0, sizeof(*this));
        }
};

// �ͻ���->������ �鿨
#define MSG_ACTION_ROLLCARDPRIZE		218
struct SMsgActionRollCardPrize_CS
{
	s32	lRollID;	// �鿨���

	SMsgActionRollCardPrize_CS()
        {
                memset(this, 0, sizeof(*this));
        }
};

// ������->�ͻ��� �����н���Ʒ�б�
struct SMsgActionRollCardPrize_SC
{
	s32	arrGoodsList[5];	// �н���Ʒ�б�

	SMsgActionRollCardPrize_SC()
        {
                memset(this, 0, sizeof(*this));
        }
};

// ������->�ͻ��� �����鿨�н�����
#define MSG_ACTION_ADDCARDROLL			219
struct SMsgActionAddCardRoll_SC
{
	s64	qwUserID;	// �н����˺�ID
	char	szActorName[32];// �н�������
	s32	lGoodsID;	// �н�����ID

	SMsgActionAddCardRoll_SC()
        {
                memset(this, 0, sizeof(*this));
        }
};

#define MSG_ACTION_GETCARDROLLLIST		220
// �ͻ���->������ ��ȡ�н����б�
struct SMsgActionGetCardRollList_CS
{
	SMsgActionGetCardRollList_CS()
	{
                memset(this, 0, sizeof(*this));
        }
};

// ������->�ͻ��� �����н����б�
struct SMsgCardRollResult
{
	s64     qwUserID;       // �н����˺�ID
        char    szActorName[32];// �н�������
        s32     lGoodsID;       // �н�����ID

	SMsgCardRollResult()
	{
                memset(this, 0, sizeof(*this));
        }
};

struct SMsgActionGetCardRollList_SC
{
	u16	wCount;		//����
	//���SMsgCardRollResult

	SMsgActionGetCardRollList_SC()
	{
		memset(this, 0, sizeof(*this));
	}
};

#define MSG_ACTION_VIPEXCHANGE			221
// �ͻ���->������ ���Ķһ�����
struct SMsgActionVIPExchange_CS
{
	s32	lExchangeID;	// �һ�ID
	s32	lExchangeNum;	// �һ�����

	SMsgActionVIPExchange_CS()
        {
                memset(this, 0, sizeof(*this));
        }
};

#define MSG_ACTION_ACTIVITY_FEEDBACK    222
// �ͻ���->������ ����ѷ���

// �����Ϣ��
#define MSG_ACTION_MAXID												256

#pragma pack(pop)

#endif //_DMSGKEYROOT_H__
