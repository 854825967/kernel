#ifndef _IDBSTRUCT_H_
#define _IDBSTRUCT_H_

#include "include/GameType.h"

#define REQUESTID_CENTERDB_LOGIN			1	// �ʺŵ�¼
#define REQUESTID_CENTERDB_CREATEACTOR  	2	// ��ɫ�������ݿ����ɽ�ɫID
#define REQUESTID_CENTERDB_DELETEACTOR  	3	// ��ɫ�������ݿ�ɾ����ɫID
#define REQUESTID_CENTERDB_UPDATEHEADURL	4	// ��ɫ�������ݿ�����˺�ͷ��URL
#define REQUESTID_CENTERDB_UPDATEACTOR		5	// ��ɫ�������ݿ���½�ɫ����
#define REQUESTID_CLEAR_UPDATE_DAY_DATA		6   // �����������
#define REQUESTID_CLEAR_UPDATE_PERIOD_DATA	7   // ˢ�µ�������
#define REQUESTID_ACTOR_LAST_ARRANGE_GET	8	// ��ȡ�Ͻ������б�
#define REQUESTID_CENTERDB_GETHEADURL		9	// ��ɫ�������ݿ��ȡ�˺�ͷ��URL

#define	REQUESTID_ACTOR_GET					10	// ��ȡ��ɫ
#define REQUESTID_ACTOR_CREATE  			11	// ������ɫ
#define REQUESTID_ACTOR_DELETE  			12	// ɾ����ɫ
#define REQUESTID_INVITATION_NUM_GET		13  // ��ȡ�������


#define REQUESTID_ACTOR_LOGIN				20	// ��ɫ��¼
#define REQUESTID_ACTOR_UPDATE				21	// ���½�ɫ����
#define REQUESTID_GOODS_GET					22	// ��ȡ��ɫ��Ʒ
#define REQUESTID_GOODS_UPDATE				23	// ���½�ɫ��Ʒ
#define REQUESTID_ACTOR_LOGOUT				24	// ��ɫ���߽���
#define REQUESTID_GOODS_GET_GIFT			25	// ��ȡ�յ�����
#define REQUESTID_PAYREWARD_GET                         26      // ��ȡ��ֵ�������

#define REQUESTID_INTERACT_LOAD				30	// ��ȡ��������
#define REQUESTID_INTERACT_SAVE				31	// ���潻������


#define REQUESTID_RELATION_GETLIST			40	// ��ȡ�Һ�˭�й�ϵ������б�
#define REQUESTID_RELATION_GETLIST2			41	// ��ȡ˭�����й�ϵ������б�
#define REQUESTID_RELATION_ADD				42	// ��ӹ�ϵ
#define REQUESTID_RELATION_UPDATE			43	// ���¹�ϵ
#define REQUESTID_RELATION_DELETE			44	// ɾ����ϵ

//��Ϸ�¼����
#define REQUESTID_GAMEEVENT_SEND			50	// ������Ϸ�¼�
#define REQUESTID_GAMEEVENT_GETLIST			51	// ��ȡ��Ϸ�¼��б�
#define REQUESTID_GAMEEVENT_UPDATE			52	// ������Ϸ�¼�(��ȡ����)
#define REQUESTID_GAMEEVENT_DEL				53	// ɾ����Ϸ�¼�

// �����������
#define REQUESTID_RANK_GET				60	// ��ȡ���д���������Ϣ
#define REQUESTID_RANK_UPDATE				61	// �޸Ĵ���������Ϣ
#define REQUESTID_RANKPRIZE_GET				62	// ��ȡ��������������
#define REQUESTID_RANKPRIZE_UPDATE			63	// ��ȡָ����������
#define REQUESTID_RANKPRIZE_INSERT			64	// ���ɱ��δ����������
#define REQUESTID_RANKRECORD_INSERT			65	// ����ս����¼
#define REQUESTID_RANKRECORD_GET			66	// ��ȡս����¼

/// �������
#define REQUESTID_UNION_CREATE_ID			70	// ��������������ݿ�������ID
#define REQUESTID_UNION_DELETE_ID			71	// ��������������ݿ�ɾ������ID
#define REQUESTID_UNION_REQUEST				72	// �����������
#define REQUESTID_UNION_INSERT				73	// ��������������
#define REQUESTID_UNION_UPDATE				74	// ������¼�������
#define REQUESTID_UNION_DELETE				75	// ����ɾ����������
#define REQUESTID_UNIONMMEBER_REQUEST		76	// ������Ա����
#define REQUESTID_UNIONMEMBER_INSERT		77	// ���������Ա����
#define REQUESTID_UNIONMEMBER_UPDATE		78	// ���������Ա����
#define REQUESTID_UNIONMEMBER_DELETE		79	// ����ɾ����Ա����

// �������
#define REQUESTID_DUMMY_BASE_GET			80	// ��ȡ���˻�����Ϣ
#define REQUESTID_DUMMY_ALL_GET				81	// ��ȡ�����걸��Ϣ
#define REQUESTID_FRIEND_BASE_GET			82	// ��ȡ���ѻ�����Ϣ

/// Ӷ��
#define REQUESTID_HERO_REQUEST				90	// Ӷ����������
#define REQUESTID_HERO_UPDATE				91	// Ӷ�����ݸ���
#define REQUESTID_HERO_DELETE				92	// Ӷ������ɾ��
#define REQUESTID_HERO_INSERT				93	// Ӷ�����ݲ���
#define REQUESTID_ONE_HERO_REQUEST			94  // ���󵥸�Ӷ������

#define REQUESTID_QQ_GETBUYGOODS			100	// ��ȡQ�㹺�����
#define REQUESTID_QQ_GETYELLOWVIP                       101     // ��ȡ�������Ϣ
#define REQUESTID_QQ_GETPOINTPRIZE			102	// ��ȡQ���ֵ��Ϣ


// OSS ���
#define REQUESTID_MONITOR_ACTORVALUE		200 // �����ֵ���(��Ǯ�������)
#define REQUESTID_MONITOR_LEVEL				201	// ��ҵȼ����
#define REQUESTID_MONITOR_MONSTER			202	// ������
#define REQUESTID_MONITOR_TASK				203	// ������
#define REQUESTID_MONITOR_GOODS_CREATE		204	// ��Ʒ�������
#define REQUESTID_MONITOR_GOODS_DESTROY		205	// ��Ʒ���ļ��
#define REQUESTID_MONITOR_ACTORGOODS		206	// �����Ʒת����־
#define REQUESTID_MONITOR_WARNING			207	// �������

#define REQUESTID_MONITOR_LEVEL_DISTRIBUTE	208	// ��ͼ��ҵȼ��ֲ����
#define REQUESTID_MONITOR_MONSTER_KILL		209	// ����ɱ����ҵȼ����
#define REQUESTID_MONITOR_PLAYER_INFO		210	// ���ʵʱ��Ϣ���

#define REQUESTID_MONITOR_BATTLE			145	// ���ս��ģʽ�ֲ����
#define REQUESTID_MONITOR_GAME_DATA			150	// ��Ϸ���ݼ��

#define REQUESTID_UPDATE_PLAYER_DATA_COUNT   151 // �����������ͳ��
#define REQUESTID_REQUEST_PLAYER_DATA_COUNT  152 // �����������ͳ��

#define REQUESTID_MAX						1000
#pragma pack(push,1)	

//////////////////////////////////////////////////////////////////////////
// REQUESTID_CENTERDB_LOGIN
// �ʺŵ�¼ - ����ṹ��
struct SCenterDBLogin_Set
{
	char	szUserName[33];		// �û���
	char	szPassword[41];		// �û�����(���������sha1)

	char	szGameWorld[16];	// ��Ϸ������
	char	szIP[16];			// �û�IP
	char	szSerialNO[20];		// �������к�

	SCenterDBLogin_Set()
	{
		memset(this, 0, sizeof(*this));
	}
};

// �ʺŵ�¼ - ����ṹ��
struct SCenterDBLogin_Get
{
	int	lReturn;			// ����ֵ
	char	szDes[128];			// ������Ϣ

	s64 qwUserID;			// �û�ID
	int	lUserType;			// �������, 0: ����ʺ�; 1: GM�ʺ�
	char	szSecPsw[41];		// ��������(���������sha1)

	int lPromptFlag;			// Ĭ��ֵ����0������1��ʾҪ������ʾ��Ϣ�Ĵ��ڣ��������ݻ�ͨ��szDes�ṩ
 
	SCenterDBLogin_Get()
	{
		memset(this, 0, sizeof(*this));
	}
};
// REQUESTID_CENTERDB_LOGIN
//////////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////////
// REQUESTID_CENTERDB_CREATEACTOR
// ���ɽ�ɫID
struct SCenterDBCreateActor_Set
{
	s64   qwUserID;							// �û�ID
	char	szName[13];							// ��ɫ��
	char	bySex;								// �Ա�
	char	byHeadPortraitId;					// ͷ��ID
	char	szIP[16];							// �û�IP
	char	szGameWorld[32];					// ��Ϸ������

	SCenterDBCreateActor_Set()
	{
		memset(this, 0, sizeof(*this));
	}
};

// ���ɽ�ɫID
struct SCenterDBCreateActor_Get
{
	int	lReturn;			// ����ֵ
	int	lActorID;			// ��ɫID

	SCenterDBCreateActor_Get()
	{
		memset(this, 0, sizeof(*this));
	}
};
// REQUESTID_CENTERDB_CREATEACTOR
//////////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////////
// REQUESTID_CENTERDB_DELETEACTOR
// ����DBɾ����ɫID
struct SCenterDBDeleteActor_Set
{
	s64 qwUserID;			// �û�ID
	int	lActorID;			// ɾ��

	SCenterDBDeleteActor_Set()
	{
		memset(this, 0, sizeof(*this));
	}
};

// ���ɽ�ɫID
struct SCenterDBDeleteActor_Get
{
	int		lReturn;			// ����ֵ
	char	szDes[128];			// ������Ϣ


	SCenterDBDeleteActor_Get()
	{
		memset(this, 0, sizeof(*this));
	}
};
// REQUESTID_CENTERDB_DELETEACTOR
//////////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////////
// REQUESTID_CENTERDB_UPDATEHEADURL
// ��ɫ�������ݿ�����˺�ͷ��URL
struct SCenterDBUpdateHeadURL_Set
{
	s32		lActorID;			// ��ɫID
	char	szHeadURL[256];		// �˺�ͷ��URL

	SCenterDBUpdateHeadURL_Set()
	{
		memset(this, 0, sizeof(*this));
	}
};

// ���ɽ�ɫID
struct SCenterDBUpdateHeadURL_Get
{
	s32		lReturn;			// ����ֵ

	SCenterDBUpdateHeadURL_Get()
	{
		memset(this, 0, sizeof(*this));
	}
};
// REQUESTID_CENTERDB_UPDATEHEADURL
//////////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////////
// REQUESTID_CENTERDB_GETHEADURL
// ��ɫ�������ݿ��ȡ�˺�ͷ��URL
struct SCenterDBGetHeadURL_Set
{
	s32		lActorID;			// �����߽�ɫID
	s64		qwUserID;			// ��������˺�ID

	SCenterDBGetHeadURL_Set()
	{
		memset(this, 0, sizeof(*this));
	}
};

// ���ɽ�ɫID
struct SCenterDBGetHeadURL_Get
{
	s32		lReturn;			// ����ֵ
	s32		lActorID;			// �����߽�ɫID
	s64		qwUserID;			// ��������˺�ID
	char	szActorName[13];	// ��ɫ��
	char	szHeadURL[256];		// �˺�ͷ��URL
	char		sOpenId[64];			// OpenID

	SCenterDBGetHeadURL_Get()
	{
		memset(this, 0, sizeof(*this));
	}
};
// REQUESTID_CENTERDB_GETHEADURL
//////////////////////////////////////////////////////////////////////////

// 0�������������
struct SCenterDBClearDayData
{
	s64	qwUserID;			// �û�ID

	SCenterDBClearDayData()
	{
		memset(this, 0, sizeof(*this));
	}
};

//��ȡ�����б�����ṹ��
struct SCenterDBActorArrange_Set
{
	s32 arrangeType;
	SCenterDBActorArrange_Set()
	{
		memset(this,0,sizeof(*this));
	}
};

//��ȡ�����б�����ṹ��
struct SCenterDBActorArrange_Get
{
	s32 lReturn;
	s64 qwUserID;
	s32 lTrainScore;
	SCenterDBActorArrange_Get()
	{
		memset(this,0,sizeof(*this));
	}
};

//��ȡ����ھ��б�����ṹ��
struct SCenterDBChampionList_Get
{
	s32 lReturn;
	s32 lPeriodID;
	s64 qwUserID;
	s32 lScore;
	s32 logTime;
	SCenterDBChampionList_Get()
	{
		memset(this,0,sizeof(*this));
	}
};


//////////////////////////////////////////////////////////////////////////
// REQUESTID_CENTERDB_UPDATEACTOR
// ���½�ɫ���Ľ�ɫ��Ϣ - ����ṹ��
struct SCenterActorUpdate_Set
{
	int	lActorID;			// ��ɫID
	u8		lLevel;				// ��ɫ�ȼ�

	SCenterActorUpdate_Set()
	{
		memset(this, 0, sizeof(*this));
	}
};

// ���½�ɫ���Ľ�ɫ��Ϣ - ����ṹ��
struct SCenterActorUpdate_Get
{
	int	lReturn;			// ����ֵ

	SCenterActorUpdate_Get()
	{
		memset(this, 0, sizeof(*this));
	}
};

// ��ȡÿ����Ϸ����Ľ�ɫ����- ���������ṹ��
struct SCenterActorGet_GetSet
{

	WORD	wGameWorldID;		// ��Ϸ������
	BYTE	byNum;				// ��ɫ����

	SCenterActorGet_GetSet()
	{
		memset(this, 0, sizeof(*this));
	}
};
// REQUESTID_CENTERDB_UPDATEACTOR
//////////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////////
// REQUESTID_ACTOR_GET
// ��ȡ��ɫ - ����ṹ��
struct SActorGet_Set
{
	s64	qwUserID;			// �û�ID

	SActorGet_Set()
	{
		memset(this, 0, sizeof(*this));
	}
};

// ��ȡ��ɫ - ����ṹ��
struct SActorGet_Get
{
	int	lReturn;			// ����ֵ
	int	lActorNum;			// ��ɫ����
	int	lActorID;			// ��ɫId
	char	szActorName[13];	// ��ɫ��
	char	bySex;				// �Ա�
	char	byHeadPortraitId;	// ͷ��ID
	int	lFlag;				// ��ű�־��0��������1�����

	SActorGet_Get()
	{
		memset(this, 0, sizeof(*this));
	}
};
// REQUESTID_ACTOR_GET
//////////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////////
// REQUESTID_ACTOR_CREATE
// ������ɫ - ����ṹ��
struct SActorCreate_Set
{
	s64	qwUserID;			// �û�ID
	int	lActorID;			// ��ɫID
	char	szName[13];			// ��ɫ��
	char	bySex;				// �Ա�
	char	byHeadPortraitId;	// ͷ��ID

	SActorCreate_Set()
	{
		memset(this, 0, sizeof(*this));
	}
};

// ������ɫ - ����ṹ��
// ������ʹ��������� SActorGet_Get

// ������ɫ - ���������ṹ��
// ������ʹ��������� SActorGet_GetSet
// REQUESTID_ACTOR_CREATE
//////////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////////
// REQUESTID_ACTOR_DELETE
// ɾ����ɫ - ����ṹ��
struct SActorDelete_Set
{
	s64	qwUserID;			// �û�ID
	int	lActorID;			// ��ɫID

	SActorDelete_Set()
	{
		memset(this, 0, sizeof(*this));
	}
};

// ɾ����ɫ - ����ṹ��
// ������ʹ��������� SActorGet_Get

// ɾ����ɫ - ���������ṹ��
// ������ʹ��������� SActorGet_GetSet
// REQUESTID_ACTOR_DELETE
//////////////////////////////////////////////////////////////////////////



/////////////////////////////////////////////////////////
// REQUESTID_ACTOR_LOGIN
// ��ɫ��¼ - ����ṹ��
struct SActorLogin_Set
{
	u32		lIdenID;			// ʶ��ID(DB���ù���)
	s64		qwUserID;			// �û�ID
	s32		lActorID;			// ��ɫID
	char	szIP[16];			// �û�IP
	char	szSerialNO[20];		// �������к�

	SActorLogin_Set()
	{
		memset(this, 0, sizeof(*this));
	}
};

//��ȡҪ�������������ṹ��
struct SActorInvitationNum_Set
{
	s64 qwUserId;
	SActorInvitationNum_Set()
	{
		memset(this, 0, sizeof(*this));
	}
};

//��ȡҪ������������
struct SActorInvitationNum_Get
{
	s32		lReturn;
	s32		lInvitationNum;
	SActorInvitationNum_Get()
	{
		memset(this,0,sizeof(*this));
	}
};

struct SActorLogin_Get
{
	s32		lReturn;				// �������
	char		ActorName[13];			// ��ɫ����
	char	szHeadURL[256];			// �˺�ͷ��URL
	s8		bySex;					// �Ա�
	s8		byHeadPortraitId;		// ͷ��ID
	u8		lLevel;					// �ȼ�
	u32		lExp;					// ����
	u32		lMoney;					// ��Ǯ
	u32		lRmb;					// �̳Ǳ�
	s32		lRoomID;				// ����ID
	u32		lEnergy;				// ��ǰ����ֵ
	u32		lGoodsEnergy;			// ͨ�����߻�ȡ�ľ���ֵ
	u32		lPVPTimes;				// �򾺼�������
	u32		lPVPWinTimes;			// �򾺼���Ӯ�Ĵ���
	u8		lGuiderStep;			// ������������
	char		pszDropContext[106];	// ���䲿��������
	char		StatusBuffer[104];		// ״̬������(8 + 16 * sizeof(SExportDBContext))
	s32		lGMPurview;				// GMȨ���ֶ�
	char		szLastDate[11];			// �ϴ�����ʱ��
	u32		lLastTime;				// �ϴ�����ʱ��
	u8		bBuyEnergyPoint;		// ���칺����������
	s32		lCardRollFlg;			// ÿ�ճ鿨��ʶ
	s32		lNull2;		        // (������
	s32		lNull3;		        // (������
	s32		lTrainCount;			// ������ȡ��ʾ����ս����(0:����������ȡ��־ 1:ǰ��������ȡ��־ 2:��ս���� 3:��ǰ�����ȼ�)
	s32		lTrainCDTime;		  // ����CDʱ��
	s32		lReputation;			// ����
	s32		lInvitationNum;			// ���������Ч����
	s32		lInviteRewardNum;		// ������ѳ齱����
	u8		lCDTimeBuffer[176];		// ��ȴ������(8 + 24 * sizeof(SNodeExportContext))
	u8		lWorkSkillBuffer[32];   // ����ܲ���������
	u8		byContinueLoginCount;	// ������½����
	u8		byGetLoginPrize;		// ������½����
	u8		byGetFriendPrize;		// ������ѽ���
  	u8    		byGetFriendCollect; // ÿ������ռ�����
	s8		byFeedScore;			// �����·������
	s8		byFeedRewardFlg;		// �����콱��ʶ
	u32		lVIPtime;				// VIP����ʱ��
	u32		lDayPrizeFlag;			// ÿ����ȡ��־λ��1~32λ 1��VIP 2:ÿ�ջ��� 3:�긶���û� 4:��ͨ���꣩
	s32		lStrengthLevel;			// ǿ���ȼ�
	s32		lPayMoney;				// ������ֵ��
	s32		lPVPPrize;			// PVP�����
	s64             qwAnotherUserID;                // ����սʤ�����˺�ID
	s8              lResult;                        // �������
	s32             lEnforceCollect;                // ǿ�����մ���
	s32		lTotalVIPInfo;			// QQ����VIP��Ϣ
	s32		lQQVIPLevel;			// QQ����ȼ�
  s32   nDayConsumeRunes;       // �������ķ�������
  u8    byDayFeedbackNumber;    // ������ķ�������

	SActorLogin_Get()
	{
		memset(this, 0, sizeof(*this));
	}
};


// REQUESTID_ACTOR_LOGIN
/////////////////////////////////////////////////////////


/////////////////////////////////////////////////////////
// REQUESTID_ACTOR_UPDATE
// ���½�ɫ��Ϣ - ����ṹ��
struct SActorUpdate_Set
{
	s64	qwUserID;				// �û�ID
	s32	lActorID;				// ActorID
 
	char	ActorName[13];			// ��ɫ����
	char szHeadURL[256];		// ���ͷ��URL
	s8	bySex;					// �Ա�
	s8	byHeadPortraitId;		// ͷ��ID
	u8	bLevel;					// �ȼ�
	u32	lExp;					// ����
	u32 lMoney;					// ��Ǯ
	u32 lRmb;					// �̳Ǳ�
	s32	lRoomID;				// ����ID
	u32	lEnergy;				// ��ǰ����ֵ
	u32 lGoodsEnergy;			// ͨ�����߻�ȡ�ľ���ֵ
	u32	lPVPTimes;				// �򾺼�������
	u32	lPVPWinTimes;			// �򾺼���Ӯ�Ĵ���
	u8	lGuiderStep;			// ������������
	char	pszDropContext[106];	// ���䲿��������
	char	StatusBuffer[104];		// ״̬������(8 + 16 * sizeof(SExportDBContext))
	s32	lGMPurview;				// GMȨ���ֶ�
	char	szLastDate[11];			// �ϴ�����ʱ��
	u32	lLastTime;				// �ϴ�����ʱ��
	u8	bBuyEnergyPoint;		// ���칺����������
  	s32	lCardRollFlg;			// ÿ�ճ鿨��ʶ
	s32		lNull2;		        // (������
	s32		lNull3;		        // (������
	s32		lTrainCount;			// ������ȡ��ʾ����ս����(0:����������ȡ��־ 1:ǰ��������ȡ��־ 2:��ս���� 3:��ǰ�����ȼ�)
	s32		lTrainCDTime;		  // ����CDʱ��
	s32		lReputation;			// ����
	s32 lInvitationNum;			// ���������Ч����
	s32	lInviteRewardNum;		// ������ѳ齱����
	u8  lCDTimeBuffer[176];		// ��ȴ������(8 + 24 * sizeof(SNodeExportContext))
	u8	lWorkSkillBuffer[32];   // ����ܲ���������
	u8	byContinueLoginCount;	// ������½����
	u8	byGetLoginPrize;		// ������½����
	u8	byGetFriendPrize;		// ������ѽ���
  u8  byGetFriendCollect; // ÿ������ռ�����
	s8	byFeedScore;			// �����·������
	s8	byFeedRewardFlg;		// �����콱��ʶ
	u32 lVIPtime;				// VIP����ʱ��
	u32	lDayPrizeFlag;			// ÿ����ȡ��־λ��1~32λ 1��VIP 2:ÿ�ջ��� 3:�긶���û� 4:��ͨ���꣩
	s32	lStrengthLevel;			// ǿ���ȼ�
	s32	lPayMoney;				// ������ֵ��
	s32	lPVPPrize;			// PVP�����
	s64     qwAnotherUserID;                // ����սʤ�����˺�ID
	s8	lResult;			// �������
	s32     lEnforceCollect;                // ǿ�����մ���
	s32	lTotalVIPInfo;			// QQ����VIP��Ϣ
	s32	lQQVIPLevel;			// QQ����ȼ�
  s32   nDayConsumeRunes;       // ��е������ķ�������
  u8    byDayFeedbackNumber;    // ��е�����ķ�������

	SActorUpdate_Set()
	{
		memset(this, 0, sizeof(*this));
	}
};

// ���½�ɫ��Ϣ - ����ṹ��
struct SActorUpdate_Get
{
	int	lReturn;		// �������

	SActorUpdate_Get()
	{
		memset(this, 0, sizeof(*this));
	}
};
// REQUESTID_ACTOR_UPDATE
/////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////////
// REQUESTID_GOODS_GET
// ��ȡ��ɫ��Ʒ - ���ṹ��
struct SGoodsGet_Set
{
	int	lActorID;		// ��ɫID
	BYTE	byContainerID;	// ����ID

	SGoodsGet_Set()
	{
		memset(this, 0, sizeof(*this));
	}
};

// ��ȡ��ɫ��Ʒ - ����ṹ��
struct SGoodsGet_Get
{
	int	lReturn;		// �������
	BYTE	lGoodsNum;		// ��Ʒ����, ����ܳ���40��

	SGoodsGet_Get()
	{
		memset(this, 0, sizeof(*this));
	}
};



//��ȡ����յ�����Ʒ
struct SGoodsGet_Set_Gift
{
	s64 qwUserId;
	s32 lActorID;
	SGoodsGet_Set_Gift()
	{
		memset(this, 0, sizeof(*this));
	}
};

//��ȡ����յ�����Ʒ
struct SGoodsGet_Get_Gift
{
	s32  lReturn;
	int lGoodsID;
	SGoodsGet_Get_Gift()
	{
		memset(this, 0, sizeof(*this));
	}
};

//��ȡ��ҳ�ֵ��������Ʒ
struct SGoodsGet_Set_PayReward
{                       
        s64 qwUserId;   
        SGoodsGet_Set_PayReward()    
        {                       
                memset(this, 0, sizeof(*this));
        }                               
};

//��ȡ��ҳ�ֵ��������Ʒ
struct SGoodsGet_Get_PayReward
{
        s32	lReturn; 
        s32	lGoodsID;
	s32	lNum;
        SGoodsGet_Get_PayReward()
        {
                memset(this, 0, sizeof(*this));
        }
};

// ��ȡ��ɫ��Ʒ - ���������ṹ��
struct SGoodsGet_GetSet
{
	int	lGoodsID;		// ��ƷID
	BYTE	byContainerID;	// ��������ID
	BYTE	byPlace;		// �������е�λ��
	short	wGoodsNum;		// ����
	int	lExistsTime;	// ��Ʒ����ʱ�� (��Ϸʱ�������ʵʱ��)
	BYTE	byFlag;			// 0x1:�Ƿ�󶨣�0x2:�Ƿ������0x3:�Ƿ񼤻0x4:�ܷ���۸�NPC
	WORD	wCurEndure;		// ��ǰ�;ã�ħ�飺��ǰ���飩
	WORD	wCurMaxEndure;	// ��ǰ����;�����
	BYTE	lSmeltLevel;	// ��������2+��������6
	BYTE	EffectBuf[26];	// ���Ч��(8) + ��Ƕ�꾧(6) + ����Ч��(6) + ��װ��ʯID(4) + ���Ч���Ƿ񼤻�(1)
	BYTE	szItemName[16];	// ΨһID (ʱ��6+��ɫID4+��̬��ͼID2+Ψһ2+������ID1+����1)

	// 60B
	SGoodsGet_GetSet()
	{
		memset(this, 0, sizeof(*this));
	}
};
// REQUESTID_GOODS_GET
//////////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////////
// REQUESTID_GOODS_UPDATE
// ���½�ɫ��Ʒ - ����ṹ��
struct SGoodsUpdate_Set
{
	int	lActorID;		// ��ɫID
	BYTE	byContainerID;	// ����ID
	BYTE	lGoodsNum;		// ��Ʒ��ʽ������ܳ���40��
	BYTE	szGoodsBuf[2400];	// ��ƷBuffer, ��lGoodsNum��SGoodsGet_GetSet�ṹ���

	SGoodsUpdate_Set()
	{
		memset(this, 0, sizeof(*this));
	}
};

// ���½�ɫ��Ʒ - ����ṹ��
struct SGoodsUpdate_Get
{
	int	lReturn;		// �������

	SGoodsUpdate_Get()
	{
		memset(this, 0, sizeof(*this));
	}
};
// REQUESTID_GOODS_UPDATE
//////////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////////
// REQUESTID_ACTOR_LOGOUT
// ��ɫ���߽��� - ����ṹ��
struct SActorLogout_Set
{
	s64	qwUserID;				// �û�ID
	int	lActorID;				// ActorID
	char	ipAddress[16];		// �û�IP


	SActorLogout_Set()
	{
		memset(this, 0, sizeof(*this));
	}
};

// ��ɫ���߽��� - ����ṹ��
struct SActorLogout_Get
{
	int	lReturn;		// �������
	char	szDes[128];		// �������

	SActorLogout_Get()
	{
		memset(this, 0, sizeof(*this));
	}
};
// REQUESTID_ACTOR_LOGOUT
//////////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////////
// REQUESTID_INTERACT_LOAD
// ��ȡ��������
struct SInteractLoad_Set
{
	BYTE	lTypeID;	// ����ID
	BYTE	lServerID;	// ������ID
	int	lOwnerID;	// ����ID

	SInteractLoad_Set()
	{
		memset(this, 0, sizeof(*this));
	}
};

// ��ȡ��������
struct SInteractLoad_Get
{
	int	lReturn;	// ����ֵ

	BYTE	DataBuffer[2048];	// �������������ݿ�

	SInteractLoad_Get()
	{
		memset(this, 0, sizeof(*this));
	}
};
// REQUESTID_INTERACT_LOAD
//////////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////////
// REQUESTID_INTERACT_SAVE
// ���潻������
struct SInteractSave_Set
{
	BYTE	lTypeID;	// ����ID
	BYTE	lServerID;	// ������ID
	int	lOwnerID;	// ����ID
	BYTE	DataBuffer[2048];	// �������������ݿ�

	SInteractSave_Set()
	{
		memset(this, 0, sizeof(*this));
	}
};

// ���潻������
struct SInteractSave_Get
{
	int	lReturn;	// ����ֵ
	char	szDes[128];	// ��������

	SInteractSave_Get()
	{
		memset(this, 0, sizeof(*this));
	}
};
// REQUESTID_INTERACT_SAVE
//////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////
// REQUESTID_LOG_ACTORLOG
struct SActorLogin_Log_Set
{
	s64	qwUserID;
	int	lActorID;
	char	szActorName[19];

	BYTE	lSex;				// �Ա�
	BYTE	lNation;			// ����ID
	BYTE	lProfession;		// ְҵ
	BYTE	lLevel;				// ����

	char	ipAddress[16];	// ��¼Ip��ַ
	char	szSerialNO[20]; // ����MAC

	SActorLogin_Log_Set()
	{
		memset(this, 0, sizeof(*this));
	}
};

// ���潻������
struct SActorLogin_Log_Get
{
	int	lReturn;	// ����ֵ
	char	szDes[128];	// ��������

	SActorLogin_Log_Get()
	{
		memset(this, 0, sizeof(*this));
	}
};

// REQUESTID_LOG_ACTORLOG
//////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////
// REQUESTID_MONITOR_ACTORVALUE
// �����ֵ��� - ����ṹ��
struct SMonitorActorValue_Set
{
	s32		lActorId;		// ���ID
	s32		lReserveId;		// ����ID
	u8		lValueType;		// ��ֵ����(1��Ǯ��2�󶨽�Ǯ��3Ԫ����4��Ԫ����5����ȫ����Ǯ��6����ȫ���󶨽�Ǯ��7����ȫ��Ԫ����8����ȫ����Ԫ����9����ȫ����Ԫ��)
	s32		lNum;			// ��ֵ����
	u8		lOpType;		// ��������(���ġ�������ת�Ƶ�)
	u8  	lApproach;		// ;��
	s32		lReserveTime;	// ����ʱ��
	char	szDesc[32];		// �����ַ���

	SMonitorActorValue_Set()
	{
		memset(this, 0, sizeof(*this));
	}
};

// �����ֵ��� - ����ṹ��
struct SMonitorActorValue_Get
{
	s32		lReturn;		// ����ֵ

	SMonitorActorValue_Get()
	{
		memset(this, 0, sizeof(*this));
	}
};
// REQUESTID_MONITOR_ACTORVALUE
//////////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////////
// REQUESTID_MONITOR_LEVEL
// ��ҵȼ���� - ����ṹ��
struct SMonitorLevel_Set
{
	int	lActorID;		// ��ɫID
	BYTE	lLevel;			// ��ǰ���� 
	int	lTime;			// �ﵽ��������ʱ�䳤��(��)

	SMonitorLevel_Set()
	{
		memset(this, 0, sizeof(*this));
	}
};

// ��ҵȼ���� - ����ṹ��
struct SMonitorLevel_Get
{
	int	lReturn;	// ����ֵ
	char	szDes[128];	// ��������

	SMonitorLevel_Get()
	{
		memset(this, 0, sizeof(*this));
	}
};
// REQUESTID_MONITOR_LEVEL
//////////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////////
// REQUESTID_MONITOR_MONSTER
// ������ - ����ṹ��
struct SMonitorMonster_Set
{
	int	lNum;				// ��¼��, ���450��
	BYTE	MonsterBuf[3600];	// ���ݻ�������ÿ����¼��ʽΪ: ����ID(4�ֽ�) + ��������(4�ֽ�)

	SMonitorMonster_Set()
	{
		memset(this, 0, sizeof(*this));
	}
};

// ������ - ����ṹ��
struct SMonitorMonster_Get
{
	int	lReturn;		// ����ֵ
	char	szDes[128];		// ��������

	SMonitorMonster_Get()
	{
		memset(this, 0, sizeof(*this));
	}
};
// REQUESTID_MONITOR_MONSTER
//////////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////////
// REQUESTID_MONITOR_TASK
// ������ - ����ṹ��
struct SMonitorTask_Set
{
	int	lNum;				// ��¼��, ���225��
	BYTE	TaskBuf[3600];		// ���ݻ�������ÿ����¼��ʽΪ: ����ID(4�ֽ�) + ���������(4�ֽ�) + ��ɴ���(4�ֽ�) + ��������(4�ֽ�)

	SMonitorTask_Set()
	{
		memset(this, 0, sizeof(*this));
	}
};

// ������ = ����ṹ��
struct SMonitorTask_Get
{
	int	lReturn;		// ����ֵ

	SMonitorTask_Get()
	{
		memset(this, 0, sizeof(*this));
	}
};
// REQUESTID_MONITOR_TASK
//////////////////////////////////////////////////////////////////////////



//////////////////////////////////////////////////////////////////////////
// REQUESTID_MONITOR_GOODS_CREATE
// ��Ʒ������� - ����ṹ��
struct SMonitorGoodsCreate_Set
{
	int	lNum;				// ��¼��, ���400��
	BYTE	GoodsBuf[3600];		// ���ݻ�������ÿ����¼��ʽΪ: ��Ʒ����;��(1�ֽ�) + ��ƷID(4�ֽ�) + ��Ʒ����(4�ֽ�)

	SMonitorGoodsCreate_Set()
	{
		memset(this, 0, sizeof(*this));
	}
};

// ��Ʒ������� - ����ṹ��
struct SMonitorGoodsCreate_Get
{
	int	lReturn;	// ����ֵ
	char	szDes[128];	// ��������

	SMonitorGoodsCreate_Get()
	{
		memset(this, 0, sizeof(*this));
	}
};
// REQUESTID_MONITOR_GOODS_CREATE
//////////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////////
// REQUESTID_MONITOR_GOODS_DESTROY
// ��Ʒ���ļ�� - ����ṹ��
struct SMonitorGoodsDestroy_Set
{
	int	lNum;				// ��¼��, ���400��
	BYTE	GoodsBuf[3600];		// ���ݻ�������ÿ����¼��ʽΪ: ��Ʒ����;��(1�ֽ�) + ��ƷID(4�ֽ�) + ��Ʒ����(4�ֽ�)

	SMonitorGoodsDestroy_Set()
	{
		memset(this, 0, sizeof(*this));
	}
};

// ��Ʒ���ļ�� - ����ṹ��
struct SMonitorGoodsDestroy_Get
{
	int	lReturn;	// ����ֵ
	char	szDes[128];	// ��������

	SMonitorGoodsDestroy_Get()
	{
		memset(this, 0, sizeof(*this));
	}
};
// REQUESTID_MONITOR_GOODS_DESTROY
//////////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////////
// REQUESTID_MONITOR_ACTORGOODS
// �����Ʒת����־ - ����ṹ��
struct SMonitorActorGoods_Set
{
	s32		lGoodsId;			// ��ƷID(���а�����ǮID)
	s16		lGoodsNum;			// ��Ʒ����(�������Ϊ��ǮID����ô������Ϊ��Ǯ����)
	s16		lMapID;				// �ؿ���ͼID��������֮��
	s32		lFrom;				// ��Ʒԭ��Id  ���߹����ID,����Npc,Id
	BYTE	lFromType;			// ��Ʒԭ������
	s32		lTo;				// ��Ʒ����Id
	BYTE	lToType;			// ��Ʒ��������
	s16  	lApproach;			// ;��
	BYTE	aAssoc[20];			// ������ˮ��
	s32		lTradeMoneyNum;		// �����漰�Ľ�Ǯ����
	s32		nMonitoTime;		// ����ʱ��

	SMonitorActorGoods_Set()
	{
		memset(this, 0, sizeof(*this));
	}
};

struct SMonitorActorGoodsBuff_Set
{
	s32		lNum;				// ��¼��, ���75��
	BYTE	GoodsBuf[3600];		// ���ݻ�������ÿ����¼��ʽΪ: sizeof(SMonitorActorGoods_Set) = 48 ,48 * 75 

	SMonitorActorGoodsBuff_Set()
	{
		memset(this, 0, sizeof(*this));
	}
};

// �����Ʒת����־ - ����ṹ��
struct SMonitorActorGoodsBuff_Get
{
	s32		lReturn;		// ����ֵ

	SMonitorActorGoodsBuff_Get()
	{
		memset(this, 0, sizeof(*this));
	}
};
// REQUESTID_MONITOR_ACTORGOODS
//////////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////////
// REQUESTID_MONITOR_WARNING
// ������� - ����ṹ��
struct SMonitorWarning_Set
{
	BYTE	lType;			// ��������
	int	lActorID;		// ��ɫID
	char	szErrMsg[128];	// ��������

	SMonitorWarning_Set()
	{
		memset(this, 0, sizeof(*this));
	}
};

// �������
struct SMonitorWarning_Get
{
	int	lReturn;		// ����ֵ
	char	szDes[128];		// ��������

	SMonitorWarning_Get()
	{
		memset(this, 0, sizeof(*this));
	}
};
// REQUESTID_MONITOR_WARNING
//////////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////////
// REQUESTID_MONITOR_GAME_DATA
// ��Ϸ���ݼ�� - ����ṹ��
struct SMonitorGameData_Set 
{
	short shNum;					// ��¼�������248����248 * 16 = 3968
	BYTE MoraleGoodsBuf[3968];		// ���ݻ�������ÿ����¼��ʽΪ��
	// Key1(4�ֽ�) + Key2(4�ֽ�) + Key3(4�ֽڣ��û���Դ) + Value(4�ֽ�)

	SMonitorGameData_Set()
	{
		memset(this, 0, sizeof(*this));
	}
};

// ��Ϸ���ݼ�� - ����ṹ��
struct SMonitorGameData_Get
{
	int lReturn;		// ����ֵ
	char szDes[128];	// ��������

	SMonitorGameData_Get()
	{
		memset(this, 0, sizeof(*this));
	}
};
// REQUESTID_MONITOR_GAME_DATA
//////////////////////////////////////////////////////////////////////////



//////////////////////////////////////////////////////////////////////////
// REQUESTID_MONITOR_LEVEL_DISTRIBUTE	208	// ��ͼ��ҵȼ��ֲ����
struct SMonitorLevelDistribute_Set
{
	short	wMapID;		/// ��ͼID
	BYTE	byLevel;	/// �ȼ�
	int	lNum;		/// ����
	SMonitorLevelDistribute_Set()
	{
		memset(this, 0, sizeof(*this));
	}
};
struct SMonitorLevelDistributeBuff_Set
{
	int	lNum;					// ��¼��, ���514��
	BYTE	datasBuff[3600];		// ���ݻ�������sizeof(SMonitorLevelDistribute_Set) = 7

	SMonitorLevelDistributeBuff_Set()
	{
		memset(this, 0, sizeof(*this));
	}
};
// ����ṹ��
struct SMonitorLevelDistributeBuff_Get
{
	int	lReturn;		// ����ֵ
	char	szDes[128];		// ��������

	SMonitorLevelDistributeBuff_Get()
	{
		memset(this, 0, sizeof(*this));
	}
};
// REQUESTID_MONITOR_LEVEL_DISTRIBUTE
//////////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////////
// REQUESTID_MONITOR_MONSTER_KILL		209	// ����ɱ����ҵȼ����
struct SMonitorMosterKill_Set
{
	int	lMosterID;		/// ����ID
	BYTE	byActorLevel;	/// �ȼ�
	int	lNum;			/// ����
	SMonitorMosterKill_Set()
	{
		memset(this, 0, sizeof(*this));
	}
};
struct SMonitorMosterKillBuff_Set
{
	int	lNum;					// ��¼��, ���400��
	BYTE	datasBuff[3600];		// ���ݻ�������sizeof(SMonitorMosterKill_Set)=9

	SMonitorMosterKillBuff_Set()
	{
		memset(this, 0, sizeof(*this));
	}
};
// ����ṹ��
struct SMonitorMosterKillBuff_Get
{
	int	lReturn;		// ����ֵ
	char	szDes[128];		// ��������

	SMonitorMosterKillBuff_Get()
	{
		memset(this, 0, sizeof(*this));
	}
};
// REQUESTID_MONITOR_LEVEL_DISTRIBUTE
//////////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////////
// REQUESTID_MONITOR_PLAYER_INFO		210	// ���ʵʱ��Ϣ���
struct SMonitorActorInfo_Set
{
	int	lActorID;			/// ���ID
	BYTE	byLevel;			/// �ȼ�
	short	wMapID;				/// ��ͼID
	int	lExp;				/// ��Ҿ���
	SMonitorActorInfo_Set()
	{
		memset(this, 0, sizeof(*this));
	}
};
struct SMonitorActorInfoBuff_Set
{
	int	lNum;					// ��¼��, ���327��
	int	lTime;					/// ͳ��ʱ���
	BYTE	datasBuff[3600];		// ���ݻ�������sizeof(SMonitorActorInfo_Set) = 11

	SMonitorActorInfoBuff_Set()
	{
		memset(this, 0, sizeof(*this));
	}
};
// ����ṹ��
struct SMonitorActorInfoBuff_Get
{
	int	lReturn;		// ����ֵ
	char	szDes[128];		// ��������

	SMonitorActorInfoBuff_Get()
	{
		memset(this, 0, sizeof(*this));
	}
};
// REQUESTID_MONITOR_LEVEL_DISTRIBUTE
//////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////
// REQUESTID_RELATION_GETLIST
// ��ȡ�Һ�˭�й�ϵ������б� - ����ṹ��
struct SRelationGetList_Set
{
	int	lActorID;	// ���ID

	SRelationGetList_Set()
	{
		memset(this, 0, sizeof(*this));
	}
};

// ��ȡ�Һ�˭�й�ϵ������б� - ����ṹ��
struct SRelationGetList_Get
{
	int	lReturn;		// �������
	char	szDes[128];		// �������

	int	lActorNum;			// �й�ϵ����Ҹ���

	SRelationGetList_Get()
	{
		memset(this, 0, sizeof(*this));
	}
};

// ��ȡ�Һ�˭�й�ϵ������б� - ���������ṹ��
struct SRelationGetList_GetSet
{
	int	lRelationID;			// ���ID
	char	szActorName[19];		// ������� 

	BYTE	wProfession;			//ְҵ
	BYTE	bSex;					//�Ա�
	BYTE	bNation;				//����

	BYTE	bType;					//����(0���� 1����)

	BYTE    bFriendType;            //���Լ��Ĺ�ϵ  (�������Ͳ���) ����ʦ��ͽ�� ��ͨ
	int    FriendValue;             //�Ѻö�        (�������Ͳ���)

	SRelationGetList_GetSet()
	{
		memset(this, 0, sizeof(*this));
	}
};
// REQUESTID_RELATION_GETLIST
//////////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////////
// REQUESTID_RELATION_GETLIST2
// ��ȡ˭�����й�ϵ������б� - ����ṹ��
struct SRelationGetList2_Set
{
	int	lActorID;	// ���ID

	SRelationGetList2_Set()
	{
		memset(this, 0, sizeof(*this));
	}
};

// ��ȡ˭�����й�ϵ�������� - ����ṹ��
struct SRelationGetList2_Get
{
	int	lReturn;		// �������
	char	szDes[128];		// �������

	int	lRelationNum;			// �й�ϵ����Ҹ���

	SRelationGetList2_Get()
	{
		memset(this, 0, sizeof(*this));
	}
};

// ��ȡ˭�����й�ϵ������б� - ���������ṹ��
struct SRelationGetList2_GetSet
{
	int	lRelationID;	// ���ID

	SRelationGetList2_GetSet()
	{
		memset(this, 0, sizeof(*this));
	}
};
// REQUESTID_RELATION_GETLIST2
//////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////
//REQUESTID_RELATION_ADD
// ����ID �������� ��ӹ�ϵ - ����ṹ��
struct SRelationAddByID_Set
{
	int	lAskerActorID;         //�����߽�ɫID
	int	lActorID;              //����ӹ�ϵ�Ľ�ɫID
	char	szName[19];			   //����ӹ�ϵ�Ľ�ɫ��
	BYTE	bType;                 //������ϵ���ͣ�0���� 1���ˣ�

	SRelationAddByID_Set()
	{
		memset(this, 0, sizeof(*this));
	}
};

// ����ID��ӹ�ϵ - ����ṹ��
struct SRelationAddByID_Get
{
	int	lReturn;		// �������
	char	szDes[128];		// �������


	int	lrActorID;              //��ӹ�ϵ�Ľ�ɫID
	char	szrName[19];			//��ӹ�ϵ�Ľ�ɫ��
	BYTE	wProfession;			//ְҵ
	BYTE	bSex;					//�Ա�
	BYTE	bNation;				//����

	BYTE   bFriendType;            //���Լ��Ĺ�ϵ  (�������Ͳ���)
	int    FriendValue;            //�Ѻö�        (�������Ͳ���)

	SRelationAddByID_Get()
	{
		memset(this, 0, sizeof(*this));
	}
};
//REQUESTID_RELATION_ADD
//////////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////////
// REQUESTID_RELATION_UPDATE
// ���¹�ϵ - ����ṹ��
struct SRelationUpdate_Set
{
	int lAskerActorID;         //�����߽�ɫID
	int lActorID;              //������ϵ�Ľ�ɫID

	BYTE bType;                 //������ϵ���ͣ�0���� 1���� 2 ������ ��

	BYTE    bFriendType;            //���Լ��Ĺ�ϵ  (�������Ͳ���)
	int    FriendValue;            //�Ѻö�        (�������Ͳ���)


	SRelationUpdate_Set()
	{
		memset(this, 0, sizeof(*this));
	}
};

// ���¹�ϵ - ����ṹ��
struct SRelationUpdate_Get
{
	int	lReturn;		// �������
	char	szDes[128];		// �������

	SRelationUpdate_Get()
	{
		memset(this, 0, sizeof(*this));
	}
};
// REQUESTID_RELATION_UPDATE
//////////////////////////////////////////////////////////////////////////



//////////////////////////////////////////////////////////////////////////
// REQUESTID_RELATION_DELETE
// ɾ�� ��ϵ - ����ṹ��  2����ֻ�����ں��ѻ��߳��˵�״̬�� ���ܸ���
struct SRelationDel_Set
{
	int lAskerActorID;         //�����߽�ɫID
	int lActorID;              //������ϵ�Ľ�ɫID

	SRelationDel_Set()
	{
		memset(this, 0, sizeof(*this));
	}
};

// ���¹�ϵ - ����ṹ��
struct SRelationDel_Get
{
	int	lReturn;		// �������
	char	szDes[128];		// �������

	SRelationDel_Get()
	{
		memset(this, 0, sizeof(*this));
	}
};
// REQUESTID_RELATION_DELETE
//////////////////////////////////////////////////////////////////////////



//////////////////////////////////////////////////////////////////////////
// REQUESTID_GAMEEVENT_SEND
// ������Ϸ�¼� - ����ṹ��
struct SGameEventSend_Set
{
	s32		lActorID;					// ������Ϸ�¼��Ľ�ɫID
	s32		lToActorID;					// ������Ϸ�¼��Ľ�ɫID
	char	szGameEventDesz[256];		// �ʼ�����
	u8		lGameEventState;			// ��Ϸ�¼�״̬(1: δ��ȡ, 2: �Ѷ�ȡ, 0: û�п���ȡ)
	char	szGoodsBuffer[36];			// 6����Ʒ(4�ֽ�lGoodsID + 2�ֽ�lGoodsNum)

	SGameEventSend_Set()
	{
		memset(this, 0, sizeof(*this));
	}
};

// ������Ϸ�¼� - ����ṹ��
struct SGameEventSend_Get
{
	s32		lReturn;			// ����ֵ
	s32		lToActorID;			// ������Ϸ�¼��Ľ�ɫID
	s32		lGameEventID;		// ��Ϸ�¼�ID
	char	szTime[20];			// ����ʱ��

	SGameEventSend_Get()
	{
		memset(this, 0, sizeof(*this));
	}
};
// REQUESTID_GAMEEVENT_SEND
//////////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////////
// REQUESTID_GAMEEVENT_GETLIST
// ��ȡ��Ϸ�¼��б� - ����ṹ��
struct SGameEventGetList_Set
{
	s32	lActorID;		// ���ID

	SGameEventGetList_Set()
	{
		memset(this, 0, sizeof(*this));
	}
};

// ��ȡ��Ϸ�¼��б� - ����ṹ��
struct SGameEventGetList_Get
{
	s32		lReturn;				// ����ֵ
	s32		lGameEventID;			// ��Ϸ�¼�ID
	s32		lSendActorID;			// ������Ϸ�¼��Ľ�ɫID
	char	szGameEventDesz[256];	// ��Ϸ�¼�����
	char	szTime[20];				// ����ʱ��
	u8		lGameEventState;		// ��Ϸ�¼�״̬(1: δ��ȡ, 2: �Ѷ�ȡ, 0: û�п���ȡ)
	s32		lLeftTime;				// ʣ�ౣ������
	char	szGoodsBuffer[36];		// 6����Ʒ(4�ֽ�lGoodsID + 2�ֽ�lGoodsNum)

	SGameEventGetList_Get()
	{
		memset(this, 0, sizeof(*this));
	}
};
// REQUESTID_GAMEEVENT_GETLIST
//////////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////////
// REQUESTID_GAMEEVENT_UPDATE
// ������Ϸ�¼� - ����ṹ��
struct SGameEventUpdate_Set
{
	s32		lActorID;		// ���ID
	s32		lGameEventID;	// ��Ϸ�¼�ID

	SGameEventUpdate_Set()
	{
		memset(this, 0, sizeof(*this));
	}
};

// ������Ϸ�¼� - ����ṹ��
struct SGameEventUpdate_Get
{
	s32		lReturn;		// ����ֵ

	SGameEventUpdate_Get()
	{
		memset(this, 0, sizeof(*this));
	}
};

// ������Ϸ�¼� - ����ṹ������
// REQUESTID_GAMEEVENT_UPDATE
//////////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////////
// REQUESTID_GAMEEVENT_DEL
// ɾ����Ϸ�¼� - ����ṹ��
struct SGameEventDel_Set
{
	s32		lActorID;		// ���ID
	s32		lGameEventID;	// ��Ϸ�¼�ID

	SGameEventDel_Set()
	{
		memset(this, 0, sizeof(*this));
	}
};

// ɾ����Ϸ�¼� - ����ṹ��
struct SGameEventDel_Get
{
	s32		lReturn;		// ����ֵ

	SGameEventDel_Get()
	{
		memset(this, 0, sizeof(*this));
	}
};
// ɾ����Ϸ�¼� - ����ṹ������
// REQUESTID_GAMEEVENT_DEL
//////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////
// REQUESTID_CHECK_EXERCISE_GET
// ��ж� - ����ṹ��
struct SCheckExercise_Set
{
	int	lExerciseID;	// �ID
	s64	qwUserID;		// ���ID
	int	lActorID;		// ��ɫID
	char	ActorName[19];	// ��ɫ����
	char	szIP[16];		// ��ҵ�½IP
	char	lParam_1[64];	// ����1
	char	lParam_2[64];	// ����2
	char	lParam_3[64];	// ����3

	SCheckExercise_Set()
	{
		memset(this,0,sizeof(*this));
	}
};

// ��ж� - ����ṹ��
struct SCheckExercise_Get
{
	int	lReturn;		// ����ֵ
	char	szDes[128];		// ��������

	SCheckExercise_Get()
	{
		memset(this,0,sizeof(*this));
	}
};

// REQUESTID_CHECK_EXERCISE_GET
//////////////////////////////////////////////////////////////////////////



//////////////////////////////////////////////////////////////////////////
// ��������DB�ṹ��
//////////////////////////////////////////////////////////////////////////

//REQUESTID_RANK_GET
//��ȡ���д���������Ϣ - ����ṹ��
struct SRankGet_Set
{
	s32	lType;		                          // ����

	SRankGet_Set()
	{
		memset(this, 0, sizeof(*this));
	}
};
// ��ȡ���д���������Ϣ - ����ṹ��
struct SRankGet_Get
{
	s32	lReturn;		                          // ����ֵ     0:û�ҵ�; 1:�ҵ�
	s32	nRank;						  // ����
	s64	lUserID;					  // �˺�ID
	s32	lActorID;					  // ��ɫID
	s32	lLevel;						  // �ȼ�
	s8	byHeadPortraitId;				  // ͷ��

	SRankGet_Get()
	{
		memset(this, 0, sizeof(*this));
	}
};
//EQUESTID_RANK_GET
//////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////
//REQUESTID_RANK_UPDATE
// �޸Ĵ���������Ϣ - ����ṹ�� ��������β����ھͲ���
struct SRankUpdate_Set
{
	s32	nRank;		                          // ����
	s64	lUserID;				  // �˺�ID
	s32	lActorID;				  // ��ɫID
	s32	lLevel;					  // �ȼ�
	s8	byHeadPortraitId;			  // ͷ��		

	SRankUpdate_Set()
	{
		memset(this, 0, sizeof(*this));
	}
};

// �޸Ĵ���������Ϣ - ����ṹ��
struct SRankUpdate_Get
{
	s32	lReturn;		                         // ����ֵ

	SRankUpdate_Get()
	{
		memset(this, 0, sizeof(*this));
	}
};
//REQUESTID_RANK_UPDATE
//////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////
// RQUESTID_RANKPRIZE_GET
// ��ȡ�������������� - ����ṹ��
struct SRankPrizeGet_Set
{
	s64	lUserID;		                          // �˺�ID
	s32	lActorID;					  // ��ɫID

	SRankPrizeGet_Set()
	{
		memset(this, 0, sizeof(*this));
	}
};

// ��ȡ�������������� - ����ṹ��
struct SRankPrizeGet_Get
{
	s32	lReturn;		                         // ����ֵ
	s32	lRID;						 // ��������ΨһID
	s32	nRank;						 // ����
	s32	logTime;					 // ��¼ʱ��

	SRankPrizeGet_Get()
	{
		memset(this, 0, sizeof(*this));
	}
};

// REQUESTID_RANKPRIZE_GET
///////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////////
// REQUESTID_RANKPRIZE_UPDATE
// ��ȡָ���������� - ����ṹ��
struct SRankPrizeUpdate_Set
{
        s32     lRID;                                          // ��������ΨһID

        SRankPrizeUpdate_Set()
        {
                memset(this, 0, sizeof(*this));
        }
};

// ��ȡָ���������� - ����ṹ��
struct SRankPrizeUpdate_Get
{
        s32     lReturn;                                         // ����ֵ

        SRankPrizeUpdate_Get()
        {
                memset(this, 0, sizeof(*this));
        }
};
// REQUESTID_RANKPRIZE_UPDATE
//////////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////////
// REQUESTID_RANKPRIZE_INSERT
// ���ɱ��δ����������  - ����ṹ��
struct SRankPrizeInsert_Set
{
        s32     lType;                                          // ����-��ʱû�õ�

        SRankPrizeInsert_Set()
        {
                memset(this, 0, sizeof(*this));
        }
};

// ���ɱ��δ���������� - ����ṹ��
struct SRankPrizeInsert_Get
{
        s32     lReturn;                                         // ����ֵ

        SRankPrizeInsert_Get()
        {
                memset(this, 0, sizeof(*this));
        }
};
// REQUESTID_RANKPRIZE_INSERT
//////////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////////
// REQUESTID_RANKRECORD_INSERT
// ����ս����¼  - ����ṹ��
struct SRankRecordInsert_Set
{
	s64	lAttUserID;					// �����˺�ID
	s64	lDefUserID;					// �ط��˺�ID
	s8	lResult;					// ���
	s32	lAttRank;					// ���������仯
	s32	lDefRank;					// �ط������仯

	SRankRecordInsert_Set()
        {
                memset(this, 0, sizeof(*this));
        }
};

// ����ս����¼ - ����ṹ��
struct SRankRecordInsert_Get
{
        s32     lReturn;                                         // ����ֵ

        SRankRecordInsert_Get()
        {
                memset(this, 0, sizeof(*this));
        }
};

// REQUESTID_RANKRECORD_INSERT
//////////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////////
// REQUESTID_RANKRECORD_GET
// ��ȡս����¼  - ����ṹ��
struct SRankRecordGet_Set
{
	s64	lUserID;					// �˺�ID
	s32	lActorID;					// ��ɫID

	SRankRecordGet_Set()
        {
                memset(this, 0, sizeof(*this));
        }
};

// ��ȡս����¼ - ����ṹ��
struct SRankRecordGet_Get
{
	s32     lReturn;                                         // ����ֵ
	s64	lAttUserID;					 // �����˺�ID
	s64     lDefUserID;                                      // �ط��˺�ID
	s8      lResult;                                         // ���
        s32     lAttRank;                                        // ���������仯
	s32	lDefRank;					 // �ط������仯
	s32	lLogTime;					 // ��¼ʱ��

	SRankRecordGet_Get()
        {
                memset(this, 0, sizeof(*this));
        }
};
// REQUESTID_RANKRECORD_GET
//////////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////////
/// REQUESTID_UNION_CREATE_ID
/// �������ļ������ݿ����ID
struct SUnionCreateID_Set
{
	char	szUnionName[20+1];			// ��������
	BYTE	byCountryID;				// �������ڹ���
	//BYTE byCityID;					// �������ڳ���

	/// ������һ����Ա�����ݣ�Ӧ���Ǵ����ߣ�
	DWORD	dwMemberID;					// ��ԱID
	char	psMemberName[18 + 1];		// ��Ա��
	BYTE	byPost;						// ��Աְλ

	SUnionCreateID_Set()
	{
		memset(this, 0, sizeof(*this));
	}
};

/// ���ط���ļ���ID - ����ṹ��
struct SUnionCreateID_Get
{
	int lReturn;						// ����ֵ
	char szDes[128];					// ��������
	DWORD dwUnionID;					// ���ؼ���ID

	SUnionCreateID_Get()
	{
		memset(this, 0, sizeof(*this));
	}
};
/// REQUESTID_UNION_CREATE_ID
//////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////
/// REQUESTID_UNION_DELETE_ID
/// �������ļ������ݿ�ɾ��ID
struct SUnionDeleteID_Set
{
	DWORD dwUnionID;					// ����ID

	SUnionDeleteID_Set()
	{
		memset(this, 0, sizeof(*this));
	}
};

/// ����ɾ����� - ����ṹ��
struct SUnionDeleteID_Get
{
	int lReturn;						// ����ֵ
	char szDes[128];					// ��������

	SUnionDeleteID_Get()
	{
		memset(this, 0, sizeof(*this));
	}
};
/// REQUESTID_UNION_DELETE_ID
//////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////
/// REQUESTID_UNION_REQUEST	
/// ����������� - ����ṹ��
struct SUnionInfoList_Set
{
	DWORD dwPageSize;					// ÿҳ��ʾ��¼������Ĭ��Ϊ100 
	DWORD PageIndex;					// ��ǰ��ȡҪ��ʾ��ҳ�룬Ĭ��Ϊ1�����ݿ����PageSize,PageIndex ���㷵��һҳ����   

	SUnionInfoList_Set()
	{
		memset(this, 0, sizeof(*this));
	}
};

/// ����������� - ����ṹ��
struct SUnionInfoList_Get
{
	int lReturn;						// ����ֵ
	char szDes[128];					// ��������
	DWORD RetTotal;						// �����ݸ���
	DWORD RetCount;						// �������ݸ������������N��SUnionDataInfo��
	DWORD RetPageIndex;					// ��ҳ��

	SUnionInfoList_Get()
	{
		memset(this, 0, sizeof(*this));
	}
};

/// ����������� - ����ṹ������
struct SUnionInfoList_GetSet
{
	DWORD dwUnionID;					// ����ID
	char szUnionName[20+1];				// ��������
	// BYTE byCityID;						// ������������
	BYTE byCountryID;					// ������������
	BYTE byLevel;						// ����ȼ�
	DWORD dwMasterID;					// �����峤ID
	char szMasterName[18+1];			// �����峤����
	BYTE szUnionPower[40];				// ����Ȩ���б� 16λһ��ְ��Ȩ�� 2 *20��ְ��
	char szUnionNote[200+1];			// ���幫��
	int lAlivePoint;					// �����Ծ�ȣ���ʱ����ʱ���٣����ٵ�0���ɢ���壩
	DWORD	 lUnionExp;					// ���徭��
	BYTE	 szTreeBuffer[75];			// ����Ƽ���
	BYTE	 szShopBuffer1[100];		// �����̵�������1
	BYTE	 szShopBuffer2[100];		// �����̵�������2
	BYTE	 szShopBuffer3[100];		// �����̵�������3
	BYTE	 szShopBuffer4[100];		// �����̵�������4
	BYTE	 szShopBuffer5[100];		// �����̵�������5

	SUnionInfoList_GetSet()
	{
		memset(this, 0, sizeof(*this));
	}
};
/// REQUESTID_UNION_REQUEST	
//////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////
/// REQUESTID_UNION_INSERT
/// �������壬�������ݿ⣨ͬʱ����һ����Ա���ݣ� - ����ṹ��
struct SUnion_Add_Set
{
	DWORD dwUnionID;					// ����ID
	char szUnionName[20+1];				// ��������
	BYTE byCountryID;					// �������ڹ���
	//BYTE byCityID;					// �������ڳ���
	BYTE szUnionPower[40];				// ����Ȩ���б� 16λһ��ְ��Ȩ�� 2 *20��ְ��

	/// ������һ����Ա�����ݣ�Ӧ���Ǵ����ߣ�
	DWORD	dwMemberID;					// ��ԱID
	char	psMemberName[18 + 1];		// ��Ա��
	BYTE	byPost;						// ��Աְλ

	SUnion_Add_Set()
	{
		memset(this, 0, sizeof(*this));
	}
};

/// ���� - ����ṹ��
struct SUnion_Add_Get
{
	int lReturn;						// ����ֵ
	char szDes[128];					// ��������

	SUnion_Add_Get()
	{
		memset(this, 0, sizeof(*this));
	}
};
/// REQUESTID_UNION_REQUEST	
//////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////
/// REQUESTID_UNION_UPDATE
/// ������¼������� - ����ṹ��
struct SUnion_Update_Set
{
	DWORD dwUnionID;					// ����ID
	char szUnionName[20+1];				// ��������
	BYTE byCountryID;					// ������������ ���������������ڹ���
	BYTE byLevel;						// ����ȼ�
	//BYTE byCityID;					// ������������
	DWORD dwMasterID;					// �����峤ID
	char szMasterName[18+1];			// �����峤����
	BYTE szUnionPower[40];				// ����Ȩ���б� 16λһ��ְ��Ȩ�� 2 *20��ְ��
	char szUnionNote[200+1];			// ���幫��
	int lLastAliveTime;				// �ϴμ����Ծʱ�䣨��һ�����һ����Ա���ߵ�ʱ�䣩
	DWORD lUnionExp;					// ���徭��

	SUnion_Update_Set()
	{
		memset(this, 0, sizeof(*this));
	}
};

/// ���ظ��¼����� - ����ṹ��
struct SUnion_Update_Get
{
	int lReturn;						// ����ֵ
	char szDes[128];					// ��������

	SUnion_Update_Get()
	{
		memset(this, 0, sizeof(*this));
	}
};
/// REQUESTID_UNION_REQUEST	
//////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////
/// REQUESTID_UNION_TEACH_UPDATE
/// ������¼���Ƽ����� - ����ṹ��
struct SUnion_Teach_Update_Set
{
	DWORD	 dwUnionID;					// ����ID
	DWORD	 lUnionExp;					// ���徭��
	BYTE	 szTreeBuffer[75];			// ����Ƽ���
	BYTE	 szShopBuffer1[100];		// �����̵�������1
	BYTE	 szShopBuffer2[100];		// �����̵�������2
	BYTE	 szShopBuffer3[100];		// �����̵�������3
	BYTE	 szShopBuffer4[100];		// �����̵�������4
	BYTE	 szShopBuffer5[100];		// �����̵�������5

	SUnion_Teach_Update_Set()
	{
		memset(this, 0, sizeof(*this));
	}
};

/// ���ظ��¼����� - ����ṹ��
struct SUnion_Teach_Update_Get
{
	int lReturn;						// ����ֵ
	char szDes[128];					// ��������

	SUnion_Teach_Update_Get()
	{
		memset(this, 0, sizeof(*this));
	}
};
/// REQUESTID_UNION_UPDATE_SHOP	
//////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////
/// REQUESTID_UNION_DELETE
/// ���� - ����ṹ��
struct SUnion_Del_Set
{
	DWORD dwUnionID;					// ����ID
	BYTE byReason;						// ɾ��ԭ��

	SUnion_Del_Set()
	{
		memset(this, 0, sizeof(*this));
	}
};

/// ���ؽ�� - ����ṹ��
struct SUnion_Del_Get
{
	int lReturn;						// ����ֵ
	char szDes[128];					// ��������
	WORD wSize;							// ɾ����Ա�ĸ���

	SUnion_Del_Get()
	{
		memset(this, 0, sizeof(*this));
	}
};

/// ���ؽ���� - ��Ա�ṹ
struct SUnion_Del_GetSet
{
	char psMember[18 + 1];				// ɾ���������

	SUnion_Del_GetSet()
	{
		memset(this, 0, sizeof(*this));
	}
};
/// REQUESTID_UNION_REQUEST	
//////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////
/// REQUESTID_UNIONMMEBER_REQUEST
/// ������Ա���� - ����ṹ��
struct SUnionMemberList_Set
{
	DWORD dwUnionID;					// ����ID

	SUnionMemberList_Set()
	{
		memset(this, 0, sizeof(*this));
	}
};

/// ��Ա���ݽ�������ظü����������Ա���� - ����ṹ��
struct SUnionMemberList_Get
{
	int lReturn;						// ����ֵ
	char szDes[128];					// ��������
	WORD size;							// ���ݸ������������N��SUnionMemberList_GetSet��

	SUnionMemberList_Get()
	{
		memset(this, 0, sizeof(*this));
	}
};

/// ��Ա���� - ����ṹ������
struct SUnionMemberList_GetSet
{
	DWORD dwMemberID;					// ��ԱID
	char psMemberName[18 + 1];			// ��Ա��
	BYTE byPost;						// ��Աְλ
	BYTE byProfession;					// ��Աְҵ
	BYTE bySex;							// ��Ա�Ա�
	int lLevel;						// ��Ա�ȼ�

	SUnionMemberList_GetSet()
	{
		memset(this, 0, sizeof(*this));
	}
};
/// REQUESTID_UNION_REQUEST	
//////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////
/// REQUESTID_UNIONMEMBER_INSERT
/// �����ţ��������ݿ� - ����ṹ��
struct SUnionMember_Add_Set
{
	DWORD	dwUnionID;					// ��������ID
	DWORD	dwMemberID;					// ��ԱID
	char	psMemberName[18 + 1];		// ��Ա��
	BYTE	byPost;						// ��Աְλ
	BYTE	byProfession;				// ��Աְҵ
	BYTE	bySex;						// ��Ա�Ա�
	int	lLevel;						// ��Ա�ȼ�

	SUnionMember_Add_Set()
	{
		memset(this, 0, sizeof(*this));
	}
};

/// ���� - ����ṹ��
struct SUnionMember_Add_Get
{
	int lReturn;						// ����ֵ
	char szDes[128];					// ��������

	SUnionMember_Add_Get()
	{
		memset(this, 0, sizeof(*this));
	}
};
/// REQUESTID_UNION_REQUEST	
//////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////
/// REQUESTID_UNIONMEMBER_UPDATE
/// ������Ա���� - ����ṹ��
struct SUnionMember_Update_Set
{
	DWORD	dwUnionID;					// ��������ID
	DWORD	dwMemberID;					// ��ԱID
	char	psMemberName[18 + 1];		// ��Ա��
	BYTE	byPost;						// ��Աְλ
	BYTE	byProfession;				// ��Աְҵ
	BYTE	bySex;						// ��Ա�Ա�
	int	lLevel;						// ��Ա�ȼ�

	SUnionMember_Update_Set()
	{
		memset(this, 0, sizeof(*this));
	}
};

/// ���� - ����ṹ��
struct SUnionMember_Update_Get
{
	int lReturn;						// ����ֵ
	char szDes[128];					// ��������

	SUnionMember_Update_Get()
	{
		memset(this, 0, sizeof(*this));
	}
};
/// REQUESTID_UNION_REQUEST	
//////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////
/// REQUESTID_UNIONMEMBER_DELETE
/// ɾ����Ա���� - ����ṹ��
struct SUnionMember_Del_Set
{
	DWORD dwMemberID;					// ����ɾ������ԱID

	SUnionMember_Del_Set()
	{
		memset(this, 0, sizeof(*this));
	}
};

/// ���� - ����ṹ��
struct SUnionMember_Del_Get
{
	int lReturn;						// ����ֵ
	char szDes[128];					// ��������

	SUnionMember_Del_Get()
	{
		memset(this, 0, sizeof(*this));
	}
};
/// REQUESTID_UNION_REQUEST	
//////////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////////
/// REQUESTID_DUMMY_BASE_GET
/// ��ȡ���˻�����Ϣ - ����ṹ��
struct SDummy_Base_Request_Set
{
	int	lRequestActorID;		// �����߽�ɫID
	u8		lRequestLevel;			// �����ߵȼ�
	int		nNum;					// ��������
	int		nOffset;				// ����ƫ��
	s32		nRequestType;		// 0 : ����֮��; 1 : PVP�

	SDummy_Base_Request_Set()
	{
		memset(this, 0, sizeof(*this));
	}
};

struct SDummy_Base_Request_Get
{
	int	lReturn;						// ����ֵ
	s64	qwDummyUserID;					// �����˺�ID
	int	lDummyActorID;					// ���˽�ɫID
	char		ActorName[13];					// ��ɫ����
	s8		bySex;							// �Ա�
	s8		byHeadPortraitId;				// ͷ��ID
	u8		lLevel;							// �ȼ�
	u32		lPVPTimes;						// �򾺼�������
	u32		lPVPWinTimes;					// �򾺼���Ӯ�Ĵ���

	SDummy_Base_Request_Get()
	{
		memset(this, 0, sizeof(*this));
	}
};
/// REQUESTID_DUMMY_BASE_GET
//////////////////////////////////////////////////////////////////////////



//////////////////////////////////////////////////////////////////////////
/// REQUESTID_DUMMY_ALL_GET
/// ��ȡ�����걸��Ϣ - ����ṹ��
struct SDummy_All_Request_Set
{
	int	lRoomID;				// ����ID
	s64	qwDummyUserID;			// �����˺�ID

	SDummy_All_Request_Set()
	{
		memset(this, 0, sizeof(*this));
	}
};

struct SDummy_All_Request_Get
{
	int	lReturn;				// ����ֵ
	s64		qwUserID;				// �˺�ID
	u32		lActorID;				// ��ɫID
	char		ActorName[13];			// ��ɫ����
	char	szHeadURL[256];			// ����ͷ��URL
	s8		bySex;					// �Ա�
	s8		byHeadPortraitId;		// ͷ��ID
	u8		lLevel;					// �ȼ�
	u32		lPVPTimes;				// �򾺼�������
	u32		lPVPWinTimes;			// �򾺼���Ӯ�Ĵ���

	SDummy_All_Request_Get()
	{
		memset(this, 0, sizeof(*this));
	}
};

struct SDummy_Notch_Request_Get
{
	BYTE	lGoodsNum;				// ��Ʒ����, ����ܳ���40��

	SDummy_Notch_Request_Get()
	{
		memset(this, 0, sizeof(*this));
	}
};

/// REQUESTID_DUMMY_ALL_GET
//////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////
/// REQUESTID_FRIEND_BASE_GET
/// ��ȡ���ѻ�����Ϣ - ����ṹ��
struct SFriend_Base_Request_Set
{
	s32		lRequestActorID;		// �����߽�ɫID
	s64		qwFriendUserID;			// ���ѵ��˺�ID
	

	SFriend_Base_Request_Set()
	{
		memset(this, 0, sizeof(*this));
	}
};

struct SFriend_Base_Request_Get
{
	s32		lReturn;						// ����ֵ
	s64		qwFriendUserID;					// �����˺�ID
	s32		lFriendActorID;					// ���ѽ�ɫID
	char	ActorName[13];					// ��ɫ����
	s8		bySex;							// �Ա�
	s8		byHeadPortraitId;				// ͷ��ID
	u8		lLevel;							// �ȼ�
	u32		lPVPTimes;						// �򾺼�������
	u32		lPVPWinTimes;					// �򾺼���Ӯ�Ĵ���

	SFriend_Base_Request_Get()
	{
		memset(this, 0, sizeof(*this));
	}
};
/// REQUESTID_FRIEND_BASE_GET
//////////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////////
/// REQUESTID_HERO_REQUEST
/// ����Ӷ�� - ����ṹ��
struct SHero_Request_Set
{
	u32 dwActorID;						/// ���ID

	SHero_Request_Set()
	{
		memset(this, 0, sizeof(*this));
	}
};

/// Ӷ������
struct SHeroData
{
	u8	lHeroIndex;						/// ����
	s32 nTemplateID;					/// ģ��ID
	u8	bLevel;							/// �ȼ�
	u32 nExp;							/// ����
	u8  bState;							/// ״̬
	s32 nHungry;						/// ��ʳ��

	SHeroData()
	{
		memset(this, 0, sizeof(*this));
	}
};
/// REQUESTID_HERO_REQUEST
//////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////
/// REQUESTID_ONE_HERO_REQUEST
/// ����Ӷ�� - ����ṹ��
struct SOneHero_Request_Set
{
	u32 dwActorID;						/// ���ID
	u8	lHeroIndex;						/// ����

	SOneHero_Request_Set()
	{
		memset(this, 0, sizeof(*this));
	}
};

/// REQUESTID_ONE_HERO_REQUEST
//////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////
/// REQUESTID_HERO_UPDATE
/// Ӷ�����ݸ���
///
/// ����Ӷ�� - ����ṹ��
struct SHero_Update_Set
{
	u32 dwActorID;						/// ���ID
	u8  lHeroIndex;						/// ����
	s32 nTemplateID;					/// Ӷ��ģ��ID
	u8	bLevel;							/// �ȼ�
	u32 nExp;							/// ����
	u8  bState;							/// ״̬
	s32 nHungry;						/// ��ʳ��

	SHero_Update_Set()
	{
		memset(this, 0, sizeof(*this));
	}
};

/// ����Ӷ�� - ����ṹ��
struct SHero_Update_Get
{
	int lReturn;						/// ����ֵ
	char szDes[128];					/// ��������

	SHero_Update_Get()
	{
		memset(this, 0, sizeof(*this));
	}
};
/// REQUESTID_HERO_UPDATE
//////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////
/// REQUESTID_HERO_DELETE
/// Ӷ������ɾ��
/// 
/// ɾ��Ӷ�� - ����ṹ��
struct SHero_Delete_Set
{
	u32 dwActorID;					/// Ӷ�����˵�ID
	u8  lHeroIndex;					/// Ӷ��ID;

	SHero_Delete_Set()
	{
		memset(this, 0, sizeof(*this));
	}
};

/// ɾ��Ӷ�� - ����ṹ��
struct SHero_Delete_Get
{
	int lReturn;						/// ����ֵ
	char szDes[128];					/// ��������

	SHero_Delete_Get()
	{
		memset(this, 0, sizeof(*this));
	}
};
/// REQUESTID_HERO_DELETE
//////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////
/// REQUESTID_HERO_INSERT
/// 
/// ����Ӷ�� - ����ṹ��
struct SHero_Insert_Set
{
	u32 dwActorID;						/// ���ID
	u8  lHeroIndex;						/// ����
	s32 nPetTemplateID;					/// Ӷ��ģ��ID
	u8	bLevel;							/// �ȼ�
	u32 nExp;							/// ����

	SHero_Insert_Set()
	{
		memset(this, 0, sizeof(*this));
	}
};

/// ����Ӷ�� - ����ṹ��
struct SHero_Insert_Get
{
	int lReturn;						/// ����ֵ
	char szDes[128];					/// ��������

	SHero_Insert_Get()
	{
		memset(this, 0, sizeof(*this));
	}
};
/// REQUESTID_HERO_INSERT
//////////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////////
/// REQUESTID_QQ_GETBUYGOODS
///
/// ��ȡQ�㹺����Ʒ - ����ṹ��
struct SQQBuyGoods_Set
{
	s64 lUserID;                   // �û�ID
	s32 lActorID;		       // ��ɫID

        SQQBuyGoods_Set()
        {
                memset(this, 0, sizeof(*this));
        }
};

/// ��ȡQ�㹺����Ʒ - ����ṹ��
struct SQQBuyGoods_Get
{
        s32 lReturn;                                            /// ����ֵ
	s32 goodID;						/// ��ƷID
	s32 Num;						/// ��Ʒ����

	SQQBuyGoods_Get()
        {
                memset(this, 0, sizeof(*this));
        }
};
/// REQUESTID_QQ_GETBUYGOODS
//////////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////////
/// REQUESTID_QQ_GETYELLOWVIP
///
/// ��ȡ�������Ϣ - ����ṹ��
struct SQQYellowVIP_Set
{
        s64 lUserID;                   // �û�ID
        s32 lActorID;                  // ��ɫID

        SQQYellowVIP_Set()
        {
                memset(this, 0, sizeof(*this));
        }
};

/// ��ȡQ�㹺����Ʒ - ����ṹ��
struct SQQYellowVIP_Get
{
        s32 lReturn;                                            /// ����ֵ
        s32 lYellowVIP;                                         /// �Ƿ�����(0:û��, 1:����)

        SQQYellowVIP_Get()
        {
                memset(this, 0, sizeof(*this));
        }
};
/// REQUESTID_QQ_GETYELLOWVIP
//////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////
/// REQUESTID_QQ_GETPOINTPRIZE
///
/// ��ȡQ���ֵ��Ϣ - ����ṹ��
struct SQQPointPrize_Set
{
	s64 lUserID;                   // �û�ID
        s32 lActorID;                  // ��ɫID
  s64 lStartTime;               // ��ʼʱ��
  s64 lEndTime;                 // ����ʱ��

	SQQPointPrize_Set()
        {
                memset(this, 0, sizeof(*this));
        }
};

/// ��ȡQ���ֵ��Ϣ - ����ṹ��
struct SQQPointPrize_Get
{
	s32 lReturn;                                            /// ����ֵ
        s32 lQQPoint;                                           /// Q������(x10)

	SQQPointPrize_Get()
        {
                memset(this, 0, sizeof(*this));
        }

};
/// REQUESTID_QQ_GETPOINTPRIZE
//////////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////////
/// REQUESTID_UPDATE_PLAYER_DATA_COUNT
/// �������ͳ�� - ����ṹ��
struct SUpdate_Player_Data_Count_Set
{
  s32 lActorID;

  s32 staySurface1;    // ����ͳ��-����ͣ��
  s32 staySurface2;
  s32 staySurface3;
  s32 staySurface4;
  s32 staySurface5;
  s32 staySurface6;
  s32 staySurface7;
  s32 staySurface8;
  s32 staySurface9;
  s32 staySurface10;

  s32 fightMob1;        // ����ͳ��-���
  s32 fightMob2;
  s32 fightMob3;
  s32 fightMob4;
  s32 fightMob5;

  s32 makeItem1;        // ����ͳ��-�����
  s32 makeItem2;
  s32 makeItem3;
  s32 makeItem4;
  s32 makeItem5;

  s32 makeEquip1;       // ����ͳ��-��װ��
  s32 makeEquip2;
  s32 makeEquip3;
  s32 makeEquip4;
  s32 makeEquip5;

  s32 makeCard1;        // ����ͳ��-�쿨Ƭ
  s32 makeCard2;
  s32 makeCard3;
  s32 makeCard4;
  s32 makeCard5;

  SUpdate_Player_Data_Count_Set()
  {
    memset(this, 0, sizeof(*this));
  }
};
/// �����������ͳ�� - ����ṹ��
struct SUpdate_Player_Data_Count_Get
{
	int lReturn;          // ����ֵ
	char szDes[128];      // ��������

	SUpdate_Player_Data_Count_Get()
	{
		memset(this, 0, sizeof(*this));
	}
};
/// REQUESTID_UPDATE_PLAYER_DATA_COUNT
//////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////
/// REQUESTID_REQUEST_PLAYER_DATA_COUNT
/// �����������ͳ�� - ����ṹ��
struct SRequest_Player_Data_Count_Set
{
  s32   lActorID;     // ��ɫID

  SRequest_Player_Data_Count_Set()
  {
    memset(this, 0, sizeof(*this));
  }
};
/// �����������ͳ�� - ����ṹ��
struct SRequest_Player_Data_Count_Get
{
  int lReturn;          // ����ֵ
  s32 staySurface1;    // ����ͳ��-����ͣ��
  s32 staySurface2;
  s32 staySurface3;
  s32 staySurface4;
  s32 staySurface5;
  s32 staySurface6;
  s32 staySurface7;
  s32 staySurface8;
  s32 staySurface9;
  s32 staySurface10;

  s32 fightMob1;        // ����ͳ��-���
  s32 fightMob2;
  s32 fightMob3;
  s32 fightMob4;
  s32 fightMob5;

  s32 makeItem1;        // ����ͳ��-�����
  s32 makeItem2;
  s32 makeItem3;
  s32 makeItem4;
  s32 makeItem5;

  s32 makeEquip1;       // ����ͳ��-��װ��
  s32 makeEquip2;
  s32 makeEquip3;
  s32 makeEquip4;
  s32 makeEquip5;

  s32 makeCard1;        // ����ͳ��-�쿨Ƭ
  s32 makeCard2;
  s32 makeCard3;
  s32 makeCard4;
  s32 makeCard5;

  SRequest_Player_Data_Count_Get()
  {
    memset(this, 0, sizeof(*this));
  }
};
/// REQUESTID_REQUEST_PLAYER_DATA_COUNT
//////////////////////////////////////////////////////////////////////////

#pragma pack(pop)


#endif// _IDBSTRUCT_H_
