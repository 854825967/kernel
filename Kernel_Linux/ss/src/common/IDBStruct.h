#ifndef _IDBSTRUCT_H_
#define _IDBSTRUCT_H_

#include "include/GameType.h"

#define REQUESTID_CENTERDB_LOGIN			1	// ÕÊºÅµÇÂ¼
#define REQUESTID_CENTERDB_CREATEACTOR  	2	// ½ÇÉ«ÖĞĞÄÊı¾İ¿âÉú³É½ÇÉ«ID
#define REQUESTID_CENTERDB_DELETEACTOR  	3	// ½ÇÉ«ÖĞĞÄÊı¾İ¿âÉ¾³ı½ÇÉ«ID
#define REQUESTID_CENTERDB_UPDATEHEADURL	4	// ½ÇÉ«ÖĞĞÄÊı¾İ¿â¸üĞÂÕËºÅÍ·ÏñURL
#define REQUESTID_CENTERDB_UPDATEACTOR		5	// ½ÇÉ«ÖĞĞÄÊı¾İ¿â¸üĞÂ½ÇÉ«Êı¾İ
#define REQUESTID_CLEAR_UPDATE_DAY_DATA		6   // Çå³ıµ±ÌìÊı¾İ
#define REQUESTID_CLEAR_UPDATE_PERIOD_DATA	7   // Ë¢ĞÂµ±½ìÊı¾İ
#define REQUESTID_ACTOR_LAST_ARRANGE_GET	8	// »ñÈ¡ÉÏ½ìÅÅĞĞÁĞ±í
#define REQUESTID_CENTERDB_GETHEADURL		9	// ½ÇÉ«ÖĞĞÄÊı¾İ¿â»ñÈ¡ÕËºÅÍ·ÏñURL

#define	REQUESTID_ACTOR_GET					10	// »ñÈ¡½ÇÉ«
#define REQUESTID_ACTOR_CREATE  			11	// ´´½¨½ÇÉ«
#define REQUESTID_ACTOR_DELETE  			12	// É¾³ı½ÇÉ«
#define REQUESTID_INVITATION_NUM_GET		13  // »ñÈ¡Íæ¼ÒÑûÇë


#define REQUESTID_ACTOR_LOGIN				20	// ½ÇÉ«µÇÂ¼
#define REQUESTID_ACTOR_UPDATE				21	// ¸üĞÂ½ÇÉ«Êı¾İ
#define REQUESTID_GOODS_GET					22	// »ñÈ¡½ÇÉ«ÎïÆ·
#define REQUESTID_GOODS_UPDATE				23	// ¸üĞÂ½ÇÉ«ÎïÆ·
#define REQUESTID_ACTOR_LOGOUT				24	// ½ÇÉ«ÏÂÏß½âËø
#define REQUESTID_GOODS_GET_GIFT			25	// »ñÈ¡ÊÕµ½ÀñÎï
#define REQUESTID_PAYREWARD_GET                         26      // »ñÈ¡³äÖµËÍÀñµÀ¾ß

#define REQUESTID_INTERACT_LOAD				30	// ¶ÁÈ¡½»»¥Êı¾İ
#define REQUESTID_INTERACT_SAVE				31	// ±£´æ½»»¥Êı¾İ


#define REQUESTID_RELATION_GETLIST			40	// »ñÈ¡ÎÒºÍË­ÓĞ¹ØÏµµÄÍæ¼ÒÁĞ±í
#define REQUESTID_RELATION_GETLIST2			41	// »ñÈ¡Ë­ºÍÎÒÓĞ¹ØÏµµÄÍæ¼ÒÁĞ±í
#define REQUESTID_RELATION_ADD				42	// Ìí¼Ó¹ØÏµ
#define REQUESTID_RELATION_UPDATE			43	// ¸üĞÂ¹ØÏµ
#define REQUESTID_RELATION_DELETE			44	// É¾³ı¹ØÏµ

//ÓÎÏ·ÊÂ¼şÏà¹Ø
#define REQUESTID_GAMEEVENT_SEND			50	// ·¢ËÍÓÎÏ·ÊÂ¼ş
#define REQUESTID_GAMEEVENT_GETLIST			51	// »ñÈ¡ÓÎÏ·ÊÂ¼şÁĞ±í
#define REQUESTID_GAMEEVENT_UPDATE			52	// ¸üĞÂÓÎÏ·ÊÂ¼ş(ÁìÈ¡½±Àø)
#define REQUESTID_GAMEEVENT_DEL				53	// É¾³ıÓÎÏ·ÊÂ¼ş

// ´óÈüÅÅÃûÏà¹Ø
#define REQUESTID_RANK_GET				60	// »ñÈ¡ËùÓĞ´óÈüÅÅÃûĞÅÏ¢
#define REQUESTID_RANK_UPDATE				61	// ĞŞ¸Ä´óÈüÅÅÃûĞÅÏ¢
#define REQUESTID_RANKPRIZE_GET				62	// »ñÈ¡´óÈüÈÕÅÅÃû½±Àø
#define REQUESTID_RANKPRIZE_UPDATE			63	// ÁìÈ¡Ö¸¶¨´óÈü½±Àø
#define REQUESTID_RANKPRIZE_INSERT			64	// Éú³É±¾´Î´óÈüÅÅÃû½á¹û
#define REQUESTID_RANKRECORD_INSERT			65	// Éú³ÉÕ½¶·¼ÇÂ¼
#define REQUESTID_RANKRECORD_GET			66	// »ñÈ¡Õ½¶·¼ÇÂ¼

/// ¼Ò×åÏà¹Ø
#define REQUESTID_UNION_CREATE_ID			70	// ÇëÇó¼Ò×åÖĞĞÄÊı¾İ¿â·ÖÅä¼Ò×åID
#define REQUESTID_UNION_DELETE_ID			71	// ÇëÇó¼Ò×åÖĞĞÄÊı¾İ¿âÉ¾³ı¼Ò×åID
#define REQUESTID_UNION_REQUEST				72	// ÇëÇó¼Ò×åÊı¾İ
#define REQUESTID_UNION_INSERT				73	// ÇëÇó²åÈë¼Ò×åÊı¾İ
#define REQUESTID_UNION_UPDATE				74	// ÇëÇó¸üĞÂ¼Ò×åÊı¾İ
#define REQUESTID_UNION_DELETE				75	// ÇëÇóÉ¾³ı¼Ò×åÊı¾İ
#define REQUESTID_UNIONMMEBER_REQUEST		76	// ÇëÇó×åÔ±Êı¾İ
#define REQUESTID_UNIONMEMBER_INSERT		77	// ÇëÇó²åÈë×åÔ±Êı¾İ
#define REQUESTID_UNIONMEMBER_UPDATE		78	// ÇëÇó¸üĞÂ×åÔ±Êı¾İ
#define REQUESTID_UNIONMEMBER_DELETE		79	// ÇëÇóÉ¾³ı×åÔ±Êı¾İ

// ¼ÙÈËÏà¹Ø
#define REQUESTID_DUMMY_BASE_GET			80	// »ñÈ¡¼ÙÈË»ù±¾ĞÅÏ¢
#define REQUESTID_DUMMY_ALL_GET				81	// »ñÈ¡¼ÙÈËÍê±¸ĞÅÏ¢
#define REQUESTID_FRIEND_BASE_GET			82	// »ñÈ¡ºÃÓÑ»ù±¾ĞÅÏ¢

/// Ó¶±ø
#define REQUESTID_HERO_REQUEST				90	// Ó¶±øÊı¾İÇëÇó
#define REQUESTID_HERO_UPDATE				91	// Ó¶±øÊı¾İ¸üĞÂ
#define REQUESTID_HERO_DELETE				92	// Ó¶±øÊı¾İÉ¾³ı
#define REQUESTID_HERO_INSERT				93	// Ó¶±øÊı¾İ²åÈë
#define REQUESTID_ONE_HERO_REQUEST			94  // ÇëÇóµ¥¸öÓ¶±øÊı¾İ

#define REQUESTID_QQ_GETBUYGOODS			100	// »ñÈ¡Qµã¹ºÂòµÀ¾ß
#define REQUESTID_QQ_GETYELLOWVIP                       101     // »ñÈ¡³ä»Æ×êĞÅÏ¢
#define REQUESTID_QQ_GETPOINTPRIZE			102	// »ñÈ¡Qµã³äÖµĞÅÏ¢


// OSS ¼à¿Ø
#define REQUESTID_MONITOR_ACTORVALUE		200 // Íæ¼ÒÊıÖµ¼à¿Ø(½ğÇ®¡¢¾­ÑéµÈ)
#define REQUESTID_MONITOR_LEVEL				201	// Íæ¼ÒµÈ¼¶¼à¿Ø
#define REQUESTID_MONITOR_MONSTER			202	// ¹ÖÎï¼à¿Ø
#define REQUESTID_MONITOR_TASK				203	// ÈÎÎñ¼à¿Ø
#define REQUESTID_MONITOR_GOODS_CREATE		204	// ÎïÆ·²úÉú¼à¿Ø
#define REQUESTID_MONITOR_GOODS_DESTROY		205	// ÎïÆ·ÏûºÄ¼à¿Ø
#define REQUESTID_MONITOR_ACTORGOODS		206	// Íæ¼ÒÎïÆ·×ªÒÆÈÕÖ¾
#define REQUESTID_MONITOR_WARNING			207	// ±¨¾¯¼à¿Ø

#define REQUESTID_MONITOR_LEVEL_DISTRIBUTE	208	// µØÍ¼Íæ¼ÒµÈ¼¶·Ö²¼¼à¿Ø
#define REQUESTID_MONITOR_MONSTER_KILL		209	// ¹ÖÎïÉ±ËÀÍæ¼ÒµÈ¼¶¼à¿Ø
#define REQUESTID_MONITOR_PLAYER_INFO		210	// Íæ¼ÒÊµÊ±ĞÅÏ¢¼à¿Ø

#define REQUESTID_MONITOR_BATTLE			145	// Íæ¼ÒÕ½³¡Ä£Ê½·Ö²¼¼à¿Ø
#define REQUESTID_MONITOR_GAME_DATA			150	// ÓÎÏ·Êı¾İ¼à¿Ø

#define REQUESTID_UPDATE_PLAYER_DATA_COUNT   151 // ¸üĞÂÍæ¼ÒÊı¾İÍ³¼Æ
#define REQUESTID_REQUEST_PLAYER_DATA_COUNT  152 // ÇëÇóÍæ¼ÒÊı¾İÍ³¼Æ

#define REQUESTID_MAX						1000
#pragma pack(push,1)	

//////////////////////////////////////////////////////////////////////////
// REQUESTID_CENTERDB_LOGIN
// ÕÊºÅµÇÂ¼ - ÊäÈë½á¹¹Ìå
struct SCenterDBLogin_Set
{
	char	szUserName[33];		// ÓÃ»§Ãû
	char	szPassword[41];		// ÓÃ»§ÃÜÂë(²»¿ÉÄæ¼ÓÃÜsha1)

	char	szGameWorld[16];	// ÓÎÏ·ÊÀ½çÃû
	char	szIP[16];			// ÓÃ»§IP
	char	szSerialNO[20];		// Íø¿¨ĞòÁĞºÅ

	SCenterDBLogin_Set()
	{
		memset(this, 0, sizeof(*this));
	}
};

// ÕÊºÅµÇÂ¼ - Êä³ö½á¹¹Ìå
struct SCenterDBLogin_Get
{
	int	lReturn;			// ·µ»ØÖµ
	char	szDes[128];			// ÃèÊöĞÅÏ¢

	s64 qwUserID;			// ÓÃ»§ID
	int	lUserType;			// Íæ¼ÒÀàĞÍ, 0: Íæ¼ÒÕÊºÅ; 1: GMÕÊºÅ
	char	szSecPsw[41];		// ¶ş¼¶ÃÜÂë(²»¿ÉÄæ¼ÓÃÜsha1)

	int lPromptFlag;			// Ä¬ÈÏÖµ·µ»Ø0£¬·µ»Ø1±íÊ¾Òªµ¯³öÌáÊ¾ĞÅÏ¢µÄ´°¿Ú£¬¾ßÌåÄÚÈİ»áÍ¨¹ıszDesÌá¹©
 
	SCenterDBLogin_Get()
	{
		memset(this, 0, sizeof(*this));
	}
};
// REQUESTID_CENTERDB_LOGIN
//////////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////////
// REQUESTID_CENTERDB_CREATEACTOR
// Éú³É½ÇÉ«ID
struct SCenterDBCreateActor_Set
{
	s64   qwUserID;							// ÓÃ»§ID
	char	szName[13];							// ½ÇÉ«Ãû
	char	bySex;								// ĞÔ±ğ
	char	byHeadPortraitId;					// Í·ÏñID
	char	szIP[16];							// ÓÃ»§IP
	char	szGameWorld[32];					// ÓÎÏ·ÊÀ½çÃû

	SCenterDBCreateActor_Set()
	{
		memset(this, 0, sizeof(*this));
	}
};

// Éú³É½ÇÉ«ID
struct SCenterDBCreateActor_Get
{
	int	lReturn;			// ·µ»ØÖµ
	int	lActorID;			// ½ÇÉ«ID

	SCenterDBCreateActor_Get()
	{
		memset(this, 0, sizeof(*this));
	}
};
// REQUESTID_CENTERDB_CREATEACTOR
//////////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////////
// REQUESTID_CENTERDB_DELETEACTOR
// ÖĞĞÄDBÉ¾³ı½ÇÉ«ID
struct SCenterDBDeleteActor_Set
{
	s64 qwUserID;			// ÓÃ»§ID
	int	lActorID;			// É¾³ı

	SCenterDBDeleteActor_Set()
	{
		memset(this, 0, sizeof(*this));
	}
};

// Éú³É½ÇÉ«ID
struct SCenterDBDeleteActor_Get
{
	int		lReturn;			// ·µ»ØÖµ
	char	szDes[128];			// ÃèÊöĞÅÏ¢


	SCenterDBDeleteActor_Get()
	{
		memset(this, 0, sizeof(*this));
	}
};
// REQUESTID_CENTERDB_DELETEACTOR
//////////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////////
// REQUESTID_CENTERDB_UPDATEHEADURL
// ½ÇÉ«ÖĞĞÄÊı¾İ¿â¸üĞÂÕËºÅÍ·ÏñURL
struct SCenterDBUpdateHeadURL_Set
{
	s32		lActorID;			// ½ÇÉ«ID
	char	szHeadURL[256];		// ÕËºÅÍ·ÏñURL

	SCenterDBUpdateHeadURL_Set()
	{
		memset(this, 0, sizeof(*this));
	}
};

// Éú³É½ÇÉ«ID
struct SCenterDBUpdateHeadURL_Get
{
	s32		lReturn;			// ·µ»ØÖµ

	SCenterDBUpdateHeadURL_Get()
	{
		memset(this, 0, sizeof(*this));
	}
};
// REQUESTID_CENTERDB_UPDATEHEADURL
//////////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////////
// REQUESTID_CENTERDB_GETHEADURL
// ½ÇÉ«ÖĞĞÄÊı¾İ¿â»ñÈ¡ÕËºÅÍ·ÏñURL
struct SCenterDBGetHeadURL_Set
{
	s32		lActorID;			// ÇëÇóÕß½ÇÉ«ID
	s64		qwUserID;			// ÇëÇó¶ÔÏóÕËºÅID

	SCenterDBGetHeadURL_Set()
	{
		memset(this, 0, sizeof(*this));
	}
};

// Éú³É½ÇÉ«ID
struct SCenterDBGetHeadURL_Get
{
	s32		lReturn;			// ·µ»ØÖµ
	s32		lActorID;			// ÇëÇóÕß½ÇÉ«ID
	s64		qwUserID;			// ÇëÇó¶ÔÏóÕËºÅID
	char	szActorName[13];	// ½ÇÉ«Ãû
	char	szHeadURL[256];		// ÕËºÅÍ·ÏñURL
	char		sOpenId[64];			// OpenID

	SCenterDBGetHeadURL_Get()
	{
		memset(this, 0, sizeof(*this));
	}
};
// REQUESTID_CENTERDB_GETHEADURL
//////////////////////////////////////////////////////////////////////////

// 0µãÇå³ıµ±ÌìÊı¾İ
struct SCenterDBClearDayData
{
	s64	qwUserID;			// ÓÃ»§ID

	SCenterDBClearDayData()
	{
		memset(this, 0, sizeof(*this));
	}
};

//»ñÈ¡ÅÅĞĞÁĞ±íÊäÈë½á¹¹Ìå
struct SCenterDBActorArrange_Set
{
	s32 arrangeType;
	SCenterDBActorArrange_Set()
	{
		memset(this,0,sizeof(*this));
	}
};

//»ñÈ¡ÅÅĞĞÁĞ±íÊä³ö½á¹¹Ìå
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

//»ñÈ¡Àú½ì¹Ú¾üÁĞ±íÊä³ö½á¹¹Ìå
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
// ¸üĞÂ½ÇÉ«ÖĞĞÄ½ÇÉ«ĞÅÏ¢ - ÊäÈë½á¹¹Ìå
struct SCenterActorUpdate_Set
{
	int	lActorID;			// ½ÇÉ«ID
	u8		lLevel;				// ½ÇÉ«µÈ¼¶

	SCenterActorUpdate_Set()
	{
		memset(this, 0, sizeof(*this));
	}
};

// ¸üĞÂ½ÇÉ«ÖĞĞÄ½ÇÉ«ĞÅÏ¢ - Êä³ö½á¹¹Ìå
struct SCenterActorUpdate_Get
{
	int	lReturn;			// ·µ»ØÖµ

	SCenterActorUpdate_Get()
	{
		memset(this, 0, sizeof(*this));
	}
};

// »ñÈ¡Ã¿¸öÓÎÏ·ÊÀ½çµÄ½ÇÉ«ÊıÁ¿- Êä³ö½á¹û¼¯½á¹¹Ìå
struct SCenterActorGet_GetSet
{

	WORD	wGameWorldID;		// ÓÎÏ·ÊÀ½ç±àºÅ
	BYTE	byNum;				// ½ÇÉ«ÊıÁ¿

	SCenterActorGet_GetSet()
	{
		memset(this, 0, sizeof(*this));
	}
};
// REQUESTID_CENTERDB_UPDATEACTOR
//////////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////////
// REQUESTID_ACTOR_GET
// »ñÈ¡½ÇÉ« - ÊäÈë½á¹¹Ìå
struct SActorGet_Set
{
	s64	qwUserID;			// ÓÃ»§ID

	SActorGet_Set()
	{
		memset(this, 0, sizeof(*this));
	}
};

// »ñÈ¡½ÇÉ« - Êä³ö½á¹¹Ìå
struct SActorGet_Get
{
	int	lReturn;			// ·µ»ØÖµ
	int	lActorNum;			// ½ÇÉ«ÊıÁ¿
	int	lActorID;			// ½ÇÉ«Id
	char	szActorName[13];	// ½ÇÉ«Ãû
	char	bySex;				// ĞÔ±ğ
	char	byHeadPortraitId;	// Í·ÏñID
	int	lFlag;				// ·âºÅ±êÖ¾£¬0£ºÕı³££¬1£º·âºÅ

	SActorGet_Get()
	{
		memset(this, 0, sizeof(*this));
	}
};
// REQUESTID_ACTOR_GET
//////////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////////
// REQUESTID_ACTOR_CREATE
// ´´½¨½ÇÉ« - ÊäÈë½á¹¹Ìå
struct SActorCreate_Set
{
	s64	qwUserID;			// ÓÃ»§ID
	int	lActorID;			// ½ÇÉ«ID
	char	szName[13];			// ½ÇÉ«Ãû
	char	bySex;				// ĞÔ±ğ
	char	byHeadPortraitId;	// Í·ÏñID

	SActorCreate_Set()
	{
		memset(this, 0, sizeof(*this));
	}
};

// ´´½¨½ÇÉ« - Êä³ö½á¹¹Ìå
// ÔÚÕâÀïÊ¹ÓÃÁËÉÏÃæµÄ SActorGet_Get

// ´´½¨½ÇÉ« - Êä³ö½á¹û¼¯½á¹¹Ìå
// ÔÚÕâÀïÊ¹ÓÃÁËÉÏÃæµÄ SActorGet_GetSet
// REQUESTID_ACTOR_CREATE
//////////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////////
// REQUESTID_ACTOR_DELETE
// É¾³ı½ÇÉ« - ÊäÈë½á¹¹Ìå
struct SActorDelete_Set
{
	s64	qwUserID;			// ÓÃ»§ID
	int	lActorID;			// ½ÇÉ«ID

	SActorDelete_Set()
	{
		memset(this, 0, sizeof(*this));
	}
};

// É¾³ı½ÇÉ« - Êä³ö½á¹¹Ìå
// ÔÚÕâÀïÊ¹ÓÃÁËÉÏÃæµÄ SActorGet_Get

// É¾³ı½ÇÉ« - Êä³ö½á¹û¼¯½á¹¹Ìå
// ÔÚÕâÀïÊ¹ÓÃÁËÉÏÃæµÄ SActorGet_GetSet
// REQUESTID_ACTOR_DELETE
//////////////////////////////////////////////////////////////////////////



/////////////////////////////////////////////////////////
// REQUESTID_ACTOR_LOGIN
// ½ÇÉ«µÇÂ¼ - ÊäÈë½á¹¹Ìå
struct SActorLogin_Set
{
	u32		lIdenID;			// Ê¶±ğID(DB²»ÓÃ¹ØĞÄ)
	s64		qwUserID;			// ÓÃ»§ID
	s32		lActorID;			// ½ÇÉ«ID
	char	szIP[16];			// ÓÃ»§IP
	char	szSerialNO[20];		// Íø¿¨ĞòÁĞºÅ

	SActorLogin_Set()
	{
		memset(this, 0, sizeof(*this));
	}
};

//»ñÈ¡ÒªÇëºÃÓÑÊıÁ¿ÊäÈë½á¹¹Ìå
struct SActorInvitationNum_Set
{
	s64 qwUserId;
	SActorInvitationNum_Set()
	{
		memset(this, 0, sizeof(*this));
	}
};

//»ñÈ¡ÒªÇëºÃÓÑÊıÁ¿Êä³ö
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
	s32		lReturn;				// ½á¹û·µ»Ø
	char		ActorName[13];			// ½ÇÉ«Ãû×Ö
	char	szHeadURL[256];			// ÕËºÅÍ·ÏñURL
	s8		bySex;					// ĞÔ±ğ
	s8		byHeadPortraitId;		// Í·ÏñID
	u8		lLevel;					// µÈ¼¶
	u32		lExp;					// ¾­Ñé
	u32		lMoney;					// ½ğÇ®
	u32		lRmb;					// ÉÌ³Ç±Ò
	s32		lRoomID;				// ·¿¼äID
	u32		lEnergy;				// µ±Ç°¾«Á¦Öµ
	u32		lGoodsEnergy;			// Í¨¹ıµÀ¾ß»ñÈ¡µÄ¾«Á¦Öµ
	u32		lPVPTimes;				// ´ò¾º¼¼³¡´ÎÊı
	u32		lPVPWinTimes;			// ´ò¾º¼¼³¡Ó®µÄ´ÎÊı
	u8		lGuiderStep;			// ĞÂÊÖÒıµ¼½ø¶È
	char		pszDropContext[106];	// µôÂä²¿¼şÉÏÏÂÎÄ
	char		StatusBuffer[104];		// ×´Ì¬Êı¾İÇø(8 + 16 * sizeof(SExportDBContext))
	s32		lGMPurview;				// GMÈ¨ÏŞ×Ö¶Î
	char		szLastDate[11];			// ÉÏ´ÎÏÂÏßÊ±¼ä
	u32		lLastTime;				// ÉÏ´ÎÏÂÏßÊ±¼ä
	u8		bBuyEnergyPoint;		// µ±Ìì¹ºÂò¾«Á¦µãÊıÁ¿
	s32		lCardRollFlg;			// Ã¿ÈÕ³é¿¨±êÊ¶
	s32		lNull2;		        // (ÉáÆú£©
	s32		lNull3;		        // (ÉáÆú£©
	s32		lTrainCount;			// ´óÈüÁìÈ¡±êÊ¾ºÍÌôÕ½´ÎÊı(0:×òÈÕÅÅÃûÁìÈ¡±êÖ¾ 1:Ç°ÌìÅÅÃûÁìÈ¡±êÖ¾ 2:ÌôÕ½´ÎÊı 3:µ±Ç°ÉùÍûµÈ¼¶)
	s32		lTrainCDTime;		  // ´óÈüCDÊ±¼ä
	s32		lReputation;			// ÉùÍû
	s32		lInvitationNum;			// ÑûÇëºÃÓÑÓĞĞ§ÊıÁ¿
	s32		lInviteRewardNum;		// ÑûÇëºÃÓÑ³é½±´ÎÊı
	u8		lCDTimeBuffer[176];		// ÀäÈ´Êı¾İÇø(8 + 24 * sizeof(SNodeExportContext))
	u8		lWorkSkillBuffer[32];   // Éú»î¼¼ÄÜ²úÎïÊı¾İÇø
	u8		byContinueLoginCount;	// Á¬ĞøµÇÂ½´ÎÊı
	u8		byGetLoginPrize;		// Á¬ĞøµÇÂ½½±Àø
	u8		byGetFriendPrize;		// ÑûÇëºÃÓÑ½±Àø
  	u8    		byGetFriendCollect; // Ã¿ÌìºÃÓÑÊÕ¼¯´ÎÊı
	s8		byFeedScore;			// ĞÂÏÊÊÂ·ÖÏí»ı·Ö
	s8		byFeedRewardFlg;		// »ı·ÖÁì½±±êÊ¶
	u32		lVIPtime;				// VIPµ½ÆÚÊ±¼ä
	u32		lDayPrizeFlag;			// Ã¿ÈÕÁìÈ¡±êÖ¾Î»£¨1~32Î» 1£ºVIP 2:Ã¿ÈÕ»Æ×ê 3:Äê¸¶·ÑÓÃ»§ 4:¿ªÍ¨»Æ×ê£©
	s32		lStrengthLevel;			// Ç¿»¯µÈ¼¶
	s32		lPayMoney;				// ×î½ü»î¶¯³äÖµÊı
	s32		lPVPPrize;			// PVP»î¶¯½±Àø
	s64             qwAnotherUserID;                // ´óÈüÕ½Ê¤¶ÔÊÖÕËºÅID
	s8              lResult;                        // ´óÈü½á¹û
	s32             lEnforceCollect;                // Ç¿ÖÆÕ÷ÊÕ´ÎÊı
	s32		lTotalVIPInfo;			// QQËùÓĞVIPĞÅÏ¢
	s32		lQQVIPLevel;			// QQ»Æ×êµÈ¼¶
  s32   nDayConsumeRunes;       // µ±ÌìÏûºÄ·ûÎÄÊıÁ¿
  u8    byDayFeedbackNumber;    // µ±Ìì·ûÎÄ·µ»¹´ÎÊı

	SActorLogin_Get()
	{
		memset(this, 0, sizeof(*this));
	}
};


// REQUESTID_ACTOR_LOGIN
/////////////////////////////////////////////////////////


/////////////////////////////////////////////////////////
// REQUESTID_ACTOR_UPDATE
// ¸üĞÂ½ÇÉ«ĞÅÏ¢ - ÊäÈë½á¹¹Ìå
struct SActorUpdate_Set
{
	s64	qwUserID;				// ÓÃ»§ID
	s32	lActorID;				// ActorID
 
	char	ActorName[13];			// ½ÇÉ«Ãû×Ö
	char szHeadURL[256];		// Íæ¼ÒÍ·ÏñURL
	s8	bySex;					// ĞÔ±ğ
	s8	byHeadPortraitId;		// Í·ÏñID
	u8	bLevel;					// µÈ¼¶
	u32	lExp;					// ¾­Ñé
	u32 lMoney;					// ½ğÇ®
	u32 lRmb;					// ÉÌ³Ç±Ò
	s32	lRoomID;				// ·¿¼äID
	u32	lEnergy;				// µ±Ç°¾«Á¦Öµ
	u32 lGoodsEnergy;			// Í¨¹ıµÀ¾ß»ñÈ¡µÄ¾«Á¦Öµ
	u32	lPVPTimes;				// ´ò¾º¼¼³¡´ÎÊı
	u32	lPVPWinTimes;			// ´ò¾º¼¼³¡Ó®µÄ´ÎÊı
	u8	lGuiderStep;			// ĞÂÊÖÒıµ¼½ø¶È
	char	pszDropContext[106];	// µôÂä²¿¼şÉÏÏÂÎÄ
	char	StatusBuffer[104];		// ×´Ì¬Êı¾İÇø(8 + 16 * sizeof(SExportDBContext))
	s32	lGMPurview;				// GMÈ¨ÏŞ×Ö¶Î
	char	szLastDate[11];			// ÉÏ´ÎÏÂÏßÊ±¼ä
	u32	lLastTime;				// ÉÏ´ÎÏÂÏßÊ±¼ä
	u8	bBuyEnergyPoint;		// µ±Ìì¹ºÂò¾«Á¦µãÊıÁ¿
  	s32	lCardRollFlg;			// Ã¿ÈÕ³é¿¨±êÊ¶
	s32		lNull2;		        // (ÉáÆú£©
	s32		lNull3;		        // (ÉáÆú£©
	s32		lTrainCount;			// ´óÈüÁìÈ¡±êÊ¾ºÍÌôÕ½´ÎÊı(0:×òÈÕÅÅÃûÁìÈ¡±êÖ¾ 1:Ç°ÌìÅÅÃûÁìÈ¡±êÖ¾ 2:ÌôÕ½´ÎÊı 3:µ±Ç°ÉùÍûµÈ¼¶)
	s32		lTrainCDTime;		  // ´óÈüCDÊ±¼ä
	s32		lReputation;			// ÉùÍû
	s32 lInvitationNum;			// ÑûÇëºÃÓÑÓĞĞ§ÊıÁ¿
	s32	lInviteRewardNum;		// ÑûÇëºÃÓÑ³é½±´ÎÊı
	u8  lCDTimeBuffer[176];		// ÀäÈ´Êı¾İÇø(8 + 24 * sizeof(SNodeExportContext))
	u8	lWorkSkillBuffer[32];   // Éú»î¼¼ÄÜ²úÎïÊı¾İÇø
	u8	byContinueLoginCount;	// Á¬ĞøµÇÂ½´ÎÊı
	u8	byGetLoginPrize;		// Á¬ĞøµÇÂ½½±Àø
	u8	byGetFriendPrize;		// ÑûÇëºÃÓÑ½±Àø
  u8  byGetFriendCollect; // Ã¿ÌìºÃÓÑÊÕ¼¯´ÎÊı
	s8	byFeedScore;			// ĞÂÏÊÊÂ·ÖÏí»ı·Ö
	s8	byFeedRewardFlg;		// »ı·ÖÁì½±±êÊ¶
	u32 lVIPtime;				// VIPµ½ÆÚÊ±¼ä
	u32	lDayPrizeFlag;			// Ã¿ÈÕÁìÈ¡±êÖ¾Î»£¨1~32Î» 1£ºVIP 2:Ã¿ÈÕ»Æ×ê 3:Äê¸¶·ÑÓÃ»§ 4:¿ªÍ¨»Æ×ê£©
	s32	lStrengthLevel;			// Ç¿»¯µÈ¼¶
	s32	lPayMoney;				// ×î½ü»î¶¯³äÖµÊı
	s32	lPVPPrize;			// PVP»î¶¯½±Àø
	s64     qwAnotherUserID;                // ´óÈüÕ½Ê¤¶ÔÊÖÕËºÅID
	s8	lResult;			// ´óÈü½á¹û
	s32     lEnforceCollect;                // Ç¿ÖÆÕ÷ÊÕ´ÎÊı
	s32	lTotalVIPInfo;			// QQËùÓĞVIPĞÅÏ¢
	s32	lQQVIPLevel;			// QQ»Æ×êµÈ¼¶
  s32   nDayConsumeRunes;       // »î¶¯ÖĞµ±ÌìÏûºÄ·ûÎÄÊıÁ¿
  u8    byDayFeedbackNumber;    // »î¶¯ÖĞµ±Ìì·ûÎÄ·µ»¹´ÎÊı

	SActorUpdate_Set()
	{
		memset(this, 0, sizeof(*this));
	}
};

// ¸üĞÂ½ÇÉ«ĞÅÏ¢ - Êä³ö½á¹¹Ìå
struct SActorUpdate_Get
{
	int	lReturn;		// ½á¹û·µ»Ø

	SActorUpdate_Get()
	{
		memset(this, 0, sizeof(*this));
	}
};
// REQUESTID_ACTOR_UPDATE
/////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////////
// REQUESTID_GOODS_GET
// »ñÈ¡½ÇÉ«ÎïÆ· - Êäë½á¹¹Ìå
struct SGoodsGet_Set
{
	int	lActorID;		// ½ÇÉ«ID
	BYTE	byContainerID;	// ÈİÆ÷ID

	SGoodsGet_Set()
	{
		memset(this, 0, sizeof(*this));
	}
};

// »ñÈ¡½ÇÉ«ÎïÆ· - Êä³ö½á¹¹Ìå
struct SGoodsGet_Get
{
	int	lReturn;		// ½á¹û·µ»Ø
	BYTE	lGoodsNum;		// ÎïÆ·¸öÊı, ×î´ó²»ÄÜ³¬¹ı40¸ö

	SGoodsGet_Get()
	{
		memset(this, 0, sizeof(*this));
	}
};



//»ñÈ¡Íæ¼ÒÊÕµ½µÄÎïÆ·
struct SGoodsGet_Set_Gift
{
	s64 qwUserId;
	s32 lActorID;
	SGoodsGet_Set_Gift()
	{
		memset(this, 0, sizeof(*this));
	}
};

//»ñÈ¡Íæ¼ÒÊÕµ½µÄÎïÆ·
struct SGoodsGet_Get_Gift
{
	s32  lReturn;
	int lGoodsID;
	SGoodsGet_Get_Gift()
	{
		memset(this, 0, sizeof(*this));
	}
};

//»ñÈ¡Íæ¼Ò³äÖµËÍÀñ½±ÀøÎïÆ·
struct SGoodsGet_Set_PayReward
{                       
        s64 qwUserId;   
        SGoodsGet_Set_PayReward()    
        {                       
                memset(this, 0, sizeof(*this));
        }                               
};

//»ñÈ¡Íæ¼Ò³äÖµËÍÀñ½±ÀøÎïÆ·
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

// »ñÈ¡½ÇÉ«ÎïÆ· - Êä³ö½á¹û¼¯½á¹¹Ìå
struct SGoodsGet_GetSet
{
	int	lGoodsID;		// ÎïÆ·ID
	BYTE	byContainerID;	// ËùÊôÈİÆ÷ID
	BYTE	byPlace;		// ÔÚÈİÆ÷ÖĞµÄÎ»ÖÃ
	short	wGoodsNum;		// ÊıÁ¿
	int	lExistsTime;	// ÎïÆ·´æÔÚÊ±¼ä (ÓÎÏ·Ê±¼ä»òÕßÏÖÊµÊ±¼ä)
	BYTE	byFlag;			// 0x1:ÊÇ·ñ°ó¶¨£¬0x2:ÊÇ·ñ¼ø¶¨£¬0x3:ÊÇ·ñ¼¤»î£¬0x4:ÄÜ·ñ³öÊÛ¸øNPC
	WORD	wCurEndure;		// µ±Ç°ÄÍ¾Ã£¨Ä§Áé£ºµ±Ç°¾­Ñé£©
	WORD	wCurMaxEndure;	// µ±Ç°×î´óÄÍ¾ÃÉÏÏŞ
	BYTE	lSmeltLevel;	// °¼²ÛÊıÁ¿2+Éı¼¶´ÎÊı6
	BYTE	EffectBuf[26];	// Ëæ»úĞ§¹û(8) + ÏâÇ¶»ê¾§(6) + ÖÆÔìĞ§¹û(6) + Ì××°±¦Ê¯ID(4) + Ëæ»úĞ§¹ûÊÇ·ñ¼¤»î(1)
	BYTE	szItemName[16];	// Î¨Ò»ID (Ê±¼ä6+½ÇÉ«ID4+¾²Ì¬µØÍ¼ID2+Î¨Ò»2+³¡¾°·şID1+²ú³ö1)

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
// ¸üĞÂ½ÇÉ«ÎïÆ· - ÊäÈë½á¹¹Ìå
struct SGoodsUpdate_Set
{
	int	lActorID;		// ½ÇÉ«ID
	BYTE	byContainerID;	// ÈİÆ÷ID
	BYTE	lGoodsNum;		// ÎïÆ·¸ñÊ½£¬×î´ó²»ÄÜ³¬¹ı40¸ö
	BYTE	szGoodsBuf[2400];	// ÎïÆ·Buffer, ÓÉlGoodsNum¸öSGoodsGet_GetSet½á¹¹×é³É

	SGoodsUpdate_Set()
	{
		memset(this, 0, sizeof(*this));
	}
};

// ¸üĞÂ½ÇÉ«ÎïÆ· - Êä³ö½á¹¹Ìå
struct SGoodsUpdate_Get
{
	int	lReturn;		// ½á¹û·µ»Ø

	SGoodsUpdate_Get()
	{
		memset(this, 0, sizeof(*this));
	}
};
// REQUESTID_GOODS_UPDATE
//////////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////////
// REQUESTID_ACTOR_LOGOUT
// ½ÇÉ«ÏÂÏß½âËø - ÊäÈë½á¹¹Ìå
struct SActorLogout_Set
{
	s64	qwUserID;				// ÓÃ»§ID
	int	lActorID;				// ActorID
	char	ipAddress[16];		// ÓÃ»§IP


	SActorLogout_Set()
	{
		memset(this, 0, sizeof(*this));
	}
};

// ½ÇÉ«ÏÂÏß½âËø - Êä³ö½á¹¹Ìå
struct SActorLogout_Get
{
	int	lReturn;		// ½á¹û·µ»Ø
	char	szDes[128];		// ½á¹ûÃèÊö

	SActorLogout_Get()
	{
		memset(this, 0, sizeof(*this));
	}
};
// REQUESTID_ACTOR_LOGOUT
//////////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////////
// REQUESTID_INTERACT_LOAD
// ¶ÁÈ¡½»»¥Êı¾İ
struct SInteractLoad_Set
{
	BYTE	lTypeID;	// ÀàĞÍID
	BYTE	lServerID;	// ·şÎñÆ÷ID
	int	lOwnerID;	// ËùÊôID

	SInteractLoad_Set()
	{
		memset(this, 0, sizeof(*this));
	}
};

// ¶ÁÈ¡½»»¥Êı¾İ
struct SInteractLoad_Get
{
	int	lReturn;	// ·µ»ØÖµ

	BYTE	DataBuffer[2048];	// ½»»¥¶ş½øÖÆÊı¾İ¿é

	SInteractLoad_Get()
	{
		memset(this, 0, sizeof(*this));
	}
};
// REQUESTID_INTERACT_LOAD
//////////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////////
// REQUESTID_INTERACT_SAVE
// ±£´æ½»»¥Êı¾İ
struct SInteractSave_Set
{
	BYTE	lTypeID;	// ÀàĞÍID
	BYTE	lServerID;	// ·şÎñÆ÷ID
	int	lOwnerID;	// ËùÊôID
	BYTE	DataBuffer[2048];	// ½»»¥¶ş½øÖÆÊı¾İ¿é

	SInteractSave_Set()
	{
		memset(this, 0, sizeof(*this));
	}
};

// ±£´æ½»»¥Êı¾İ
struct SInteractSave_Get
{
	int	lReturn;	// ·µ»ØÖµ
	char	szDes[128];	// ·µ»ØÃèÊö

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

	BYTE	lSex;				// ĞÔ±ğ
	BYTE	lNation;			// ¹ú¼ÒID
	BYTE	lProfession;		// Ö°Òµ
	BYTE	lLevel;				// ¼¶±ğ

	char	ipAddress[16];	// µÇÂ¼IpµØÖ·
	char	szSerialNO[20]; // Íø¿¨MAC

	SActorLogin_Log_Set()
	{
		memset(this, 0, sizeof(*this));
	}
};

// ±£´æ½»»¥Êı¾İ
struct SActorLogin_Log_Get
{
	int	lReturn;	// ·µ»ØÖµ
	char	szDes[128];	// ·µ»ØÃèÊö

	SActorLogin_Log_Get()
	{
		memset(this, 0, sizeof(*this));
	}
};

// REQUESTID_LOG_ACTORLOG
//////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////
// REQUESTID_MONITOR_ACTORVALUE
// Íæ¼ÒÊıÖµ¼à¿Ø - ÊäÈë½á¹¹Ìå
struct SMonitorActorValue_Set
{
	s32		lActorId;		// Íæ¼ÒID
	s32		lReserveId;		// ±£ÁôID
	u8		lValueType;		// ÊıÖµÖÖÀà(1½ğÇ®¡¢2°ó¶¨½ğÇ®¡¢3Ôª±¦¡¢4°ó¶¨Ôª±¦¡¢5ÉíÉÏÈ«²¿½ğÇ®¡¢6ÉíÉÏÈ«²¿°ó¶¨½ğÇ®¡¢7ÉíÉÏÈ«²¿Ôª±¦¡¢8ÉíÉÏÈ«²¿°ó¶¨Ôª±¦¡¢9ÉíÉÏÈ«²¿°ó¶¨Ôª±¦)
	s32		lNum;			// ÊıÖµÊıÁ¿
	u8		lOpType;		// ²Ù×÷ÀàĞÍ(ÏûºÄ¡¢²úÉú¡¢×ªÒÆµÈ)
	u8  	lApproach;		// Í¾¾¶
	s32		lReserveTime;	// ±£ÁôÊ±¼ä
	char	szDesc[32];		// ÃèÊö×Ö·û´®

	SMonitorActorValue_Set()
	{
		memset(this, 0, sizeof(*this));
	}
};

// Íæ¼ÒÊıÖµ¼à¿Ø - Êä³ö½á¹¹Ìå
struct SMonitorActorValue_Get
{
	s32		lReturn;		// ·µ»ØÖµ

	SMonitorActorValue_Get()
	{
		memset(this, 0, sizeof(*this));
	}
};
// REQUESTID_MONITOR_ACTORVALUE
//////////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////////
// REQUESTID_MONITOR_LEVEL
// Íæ¼ÒµÈ¼¶¼à¿Ø - ÊäÈë½á¹¹Ìå
struct SMonitorLevel_Set
{
	int	lActorID;		// ½ÇÉ«ID
	BYTE	lLevel;			// µ±Ç°¼¶±ğ 
	int	lTime;			// ´ïµ½±¾¼¶ËùÓÃÊ±¼ä³¤¶È(Ãë)

	SMonitorLevel_Set()
	{
		memset(this, 0, sizeof(*this));
	}
};

// Íæ¼ÒµÈ¼¶¼à¿Ø - Êä³ö½á¹¹Ìå
struct SMonitorLevel_Get
{
	int	lReturn;	// ·µ»ØÖµ
	char	szDes[128];	// ·µ»ØÃèÊö

	SMonitorLevel_Get()
	{
		memset(this, 0, sizeof(*this));
	}
};
// REQUESTID_MONITOR_LEVEL
//////////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////////
// REQUESTID_MONITOR_MONSTER
// ¹ÖÎï¼à¿Ø - ÊäÈë½á¹¹Ìå
struct SMonitorMonster_Set
{
	int	lNum;				// ¼ÇÂ¼Êı, ×î¶à450¸ö
	BYTE	MonsterBuf[3600];	// Êı¾İ»º³åÇø£¬Ã¿¸ö¼ÇÂ¼¸ñÊ½Îª: ¹ÖÎïID(4×Ö½Ú) + ËÀÍö´ÎÊı(4×Ö½Ú)

	SMonitorMonster_Set()
	{
		memset(this, 0, sizeof(*this));
	}
};

// ¹ÖÎï¼à¿Ø - Êä³ö½á¹¹Ìå
struct SMonitorMonster_Get
{
	int	lReturn;		// ·µ»ØÖµ
	char	szDes[128];		// ·µ»ØÃèÊö

	SMonitorMonster_Get()
	{
		memset(this, 0, sizeof(*this));
	}
};
// REQUESTID_MONITOR_MONSTER
//////////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////////
// REQUESTID_MONITOR_TASK
// ÈÎÎñ¼à¿Ø - ÊäÈë½á¹¹Ìå
struct SMonitorTask_Set
{
	int	lNum;				// ¼ÇÂ¼Êı, ×î¶à225¸ö
	BYTE	TaskBuf[3600];		// Êı¾İ»º³åÇø£¬Ã¿¸ö¼ÇÂ¼¸ñÊ½Îª: ÈÎÎñID(4×Ö½Ú) + ½ÓÈÎÎñ´ÎÊı(4×Ö½Ú) + Íê³É´ÎÊı(4×Ö½Ú) + ·ÅÆú´ÎÊı(4×Ö½Ú)

	SMonitorTask_Set()
	{
		memset(this, 0, sizeof(*this));
	}
};

// ÈÎÎñ¼à¿Ø = Êä³ö½á¹¹Ìå
struct SMonitorTask_Get
{
	int	lReturn;		// ·µ»ØÖµ

	SMonitorTask_Get()
	{
		memset(this, 0, sizeof(*this));
	}
};
// REQUESTID_MONITOR_TASK
//////////////////////////////////////////////////////////////////////////



//////////////////////////////////////////////////////////////////////////
// REQUESTID_MONITOR_GOODS_CREATE
// ÎïÆ·²úÉú¼à¿Ø - ÊäÈë½á¹¹Ìå
struct SMonitorGoodsCreate_Set
{
	int	lNum;				// ¼ÇÂ¼Êı, ×î¶à400¸ö
	BYTE	GoodsBuf[3600];		// Êı¾İ»º³åÇø£¬Ã¿¸ö¼ÇÂ¼¸ñÊ½Îª: ÎïÆ·²úÉúÍ¾¾¶(1×Ö½Ú) + ÎïÆ·ID(4×Ö½Ú) + ÎïÆ·¸öÊı(4×Ö½Ú)

	SMonitorGoodsCreate_Set()
	{
		memset(this, 0, sizeof(*this));
	}
};

// ÎïÆ·²úÉú¼à¿Ø - Êä³ö½á¹¹Ìå
struct SMonitorGoodsCreate_Get
{
	int	lReturn;	// ·µ»ØÖµ
	char	szDes[128];	// ·µ»ØÃèÊö

	SMonitorGoodsCreate_Get()
	{
		memset(this, 0, sizeof(*this));
	}
};
// REQUESTID_MONITOR_GOODS_CREATE
//////////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////////
// REQUESTID_MONITOR_GOODS_DESTROY
// ÎïÆ·ÏûºÄ¼à¿Ø - ÊäÈë½á¹¹Ìå
struct SMonitorGoodsDestroy_Set
{
	int	lNum;				// ¼ÇÂ¼Êı, ×î¶à400¸ö
	BYTE	GoodsBuf[3600];		// Êı¾İ»º³åÇø£¬Ã¿¸ö¼ÇÂ¼¸ñÊ½Îª: ÎïÆ·ÏûºÄÍ¾¾¶(1×Ö½Ú) + ÎïÆ·ID(4×Ö½Ú) + ÎïÆ·¸öÊı(4×Ö½Ú)

	SMonitorGoodsDestroy_Set()
	{
		memset(this, 0, sizeof(*this));
	}
};

// ÎïÆ·ÏûºÄ¼à¿Ø - Êä³ö½á¹¹Ìå
struct SMonitorGoodsDestroy_Get
{
	int	lReturn;	// ·µ»ØÖµ
	char	szDes[128];	// ·µ»ØÃèÊö

	SMonitorGoodsDestroy_Get()
	{
		memset(this, 0, sizeof(*this));
	}
};
// REQUESTID_MONITOR_GOODS_DESTROY
//////////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////////
// REQUESTID_MONITOR_ACTORGOODS
// Íæ¼ÒÎïÆ·×ªÒÆÈÕÖ¾ - ÊäÈë½á¹¹Ìå
struct SMonitorActorGoods_Set
{
	s32		lGoodsId;			// ÎïÆ·ID(ÆäÖĞ°üÀ¨½ğÇ®ID)
	s16		lGoodsNum;			// ÎïÆ·¸öÊı(Èç¹ûÉÏÃæÎª½ğÇ®ID£¬ÄÇÃ´±¾²ÎÊıÎª½ğÇ®ÊıÁ¿)
	s16		lMapID;				// ¹Ø¿¨µØÍ¼ID»òÕßÊÔÁ¶Ö®Ëş
	s32		lFrom;				// ÎïÆ·Ô­Ö÷Id  »òÕß¹ÖÎïµÄID,ÈÎÎñNpc,Id
	BYTE	lFromType;			// ÎïÆ·Ô­Ö÷ÀàĞÍ
	s32		lTo;				// ÎïÆ·ĞÂÖ÷Id
	BYTE	lToType;			// ÎïÆ·ĞÂÖ÷ÀàĞÍ
	s16  	lApproach;			// Í¾¾¶
	BYTE	aAssoc[20];			// ¹ØÁªÁ÷Ë®ºÅ
	s32		lTradeMoneyNum;		// ½»Ò×Éæ¼°µÄ½ğÇ®ÊıÁ¿
	s32		nMonitoTime;		// ½»Ò×Ê±¼ä

	SMonitorActorGoods_Set()
	{
		memset(this, 0, sizeof(*this));
	}
};

struct SMonitorActorGoodsBuff_Set
{
	s32		lNum;				// ¼ÇÂ¼Êı, ×î¶à75¸ö
	BYTE	GoodsBuf[3600];		// Êı¾İ»º³åÇø£¬Ã¿¸ö¼ÇÂ¼¸ñÊ½Îª: sizeof(SMonitorActorGoods_Set) = 48 ,48 * 75 

	SMonitorActorGoodsBuff_Set()
	{
		memset(this, 0, sizeof(*this));
	}
};

// Íæ¼ÒÎïÆ·×ªÒÆÈÕÖ¾ - Êä³ö½á¹¹Ìå
struct SMonitorActorGoodsBuff_Get
{
	s32		lReturn;		// ·µ»ØÖµ

	SMonitorActorGoodsBuff_Get()
	{
		memset(this, 0, sizeof(*this));
	}
};
// REQUESTID_MONITOR_ACTORGOODS
//////////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////////
// REQUESTID_MONITOR_WARNING
// ±¨¾¯¼à¿Ø - ÊäÈë½á¹¹Ìå
struct SMonitorWarning_Set
{
	BYTE	lType;			// ´íÎóÀàĞÍ
	int	lActorID;		// ½ÇÉ«ID
	char	szErrMsg[128];	// ´íÎóÃèÊö

	SMonitorWarning_Set()
	{
		memset(this, 0, sizeof(*this));
	}
};

// ±¨¾¯¼à¿Ø
struct SMonitorWarning_Get
{
	int	lReturn;		// ·µ»ØÖµ
	char	szDes[128];		// ·µ»ØÃèÊö

	SMonitorWarning_Get()
	{
		memset(this, 0, sizeof(*this));
	}
};
// REQUESTID_MONITOR_WARNING
//////////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////////
// REQUESTID_MONITOR_GAME_DATA
// ÓÎÏ·Êı¾İ¼à¿Ø - ÊäÈë½á¹¹Ìå
struct SMonitorGameData_Set 
{
	short shNum;					// ¼ÇÂ¼Êı£¬×î¶à248¸ö£¬248 * 16 = 3968
	BYTE MoraleGoodsBuf[3968];		// Êı¾İ»º³åÇø£¬Ã¿¸ö¼ÇÂ¼¸ñÊ½Îª£º
	// Key1(4×Ö½Ú) + Key2(4×Ö½Ú) + Key3(4×Ö½Ú£¬ÓÃ»§À´Ô´) + Value(4×Ö½Ú)

	SMonitorGameData_Set()
	{
		memset(this, 0, sizeof(*this));
	}
};

// ÓÎÏ·Êı¾İ¼à¿Ø - Êä³ö½á¹¹Ìå
struct SMonitorGameData_Get
{
	int lReturn;		// ·µ»ØÖµ
	char szDes[128];	// ·µ»ØÃèÊö

	SMonitorGameData_Get()
	{
		memset(this, 0, sizeof(*this));
	}
};
// REQUESTID_MONITOR_GAME_DATA
//////////////////////////////////////////////////////////////////////////



//////////////////////////////////////////////////////////////////////////
// REQUESTID_MONITOR_LEVEL_DISTRIBUTE	208	// µØÍ¼Íæ¼ÒµÈ¼¶·Ö²¼¼à¿Ø
struct SMonitorLevelDistribute_Set
{
	short	wMapID;		/// µØÍ¼ID
	BYTE	byLevel;	/// µÈ¼¶
	int	lNum;		/// ÊıÁ¿
	SMonitorLevelDistribute_Set()
	{
		memset(this, 0, sizeof(*this));
	}
};
struct SMonitorLevelDistributeBuff_Set
{
	int	lNum;					// ¼ÇÂ¼Êı, ×î¶à514¸ö
	BYTE	datasBuff[3600];		// Êı¾İ»º³åÇø£¬sizeof(SMonitorLevelDistribute_Set) = 7

	SMonitorLevelDistributeBuff_Set()
	{
		memset(this, 0, sizeof(*this));
	}
};
// Êä³ö½á¹¹Ìå
struct SMonitorLevelDistributeBuff_Get
{
	int	lReturn;		// ·µ»ØÖµ
	char	szDes[128];		// ·µ»ØÃèÊö

	SMonitorLevelDistributeBuff_Get()
	{
		memset(this, 0, sizeof(*this));
	}
};
// REQUESTID_MONITOR_LEVEL_DISTRIBUTE
//////////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////////
// REQUESTID_MONITOR_MONSTER_KILL		209	// ¹ÖÎïÉ±ËÀÍæ¼ÒµÈ¼¶¼à¿Ø
struct SMonitorMosterKill_Set
{
	int	lMosterID;		/// ¹ÖÎïID
	BYTE	byActorLevel;	/// µÈ¼¶
	int	lNum;			/// ÊıÁ¿
	SMonitorMosterKill_Set()
	{
		memset(this, 0, sizeof(*this));
	}
};
struct SMonitorMosterKillBuff_Set
{
	int	lNum;					// ¼ÇÂ¼Êı, ×î¶à400¸ö
	BYTE	datasBuff[3600];		// Êı¾İ»º³åÇø£¬sizeof(SMonitorMosterKill_Set)=9

	SMonitorMosterKillBuff_Set()
	{
		memset(this, 0, sizeof(*this));
	}
};
// Êä³ö½á¹¹Ìå
struct SMonitorMosterKillBuff_Get
{
	int	lReturn;		// ·µ»ØÖµ
	char	szDes[128];		// ·µ»ØÃèÊö

	SMonitorMosterKillBuff_Get()
	{
		memset(this, 0, sizeof(*this));
	}
};
// REQUESTID_MONITOR_LEVEL_DISTRIBUTE
//////////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////////
// REQUESTID_MONITOR_PLAYER_INFO		210	// Íæ¼ÒÊµÊ±ĞÅÏ¢¼à¿Ø
struct SMonitorActorInfo_Set
{
	int	lActorID;			/// Íæ¼ÒID
	BYTE	byLevel;			/// µÈ¼¶
	short	wMapID;				/// µØÍ¼ID
	int	lExp;				/// Íæ¼Ò¾­Ñé
	SMonitorActorInfo_Set()
	{
		memset(this, 0, sizeof(*this));
	}
};
struct SMonitorActorInfoBuff_Set
{
	int	lNum;					// ¼ÇÂ¼Êı, ×î¶à327¸ö
	int	lTime;					/// Í³¼ÆÊ±¼äµã
	BYTE	datasBuff[3600];		// Êı¾İ»º³åÇø£¬sizeof(SMonitorActorInfo_Set) = 11

	SMonitorActorInfoBuff_Set()
	{
		memset(this, 0, sizeof(*this));
	}
};
// Êä³ö½á¹¹Ìå
struct SMonitorActorInfoBuff_Get
{
	int	lReturn;		// ·µ»ØÖµ
	char	szDes[128];		// ·µ»ØÃèÊö

	SMonitorActorInfoBuff_Get()
	{
		memset(this, 0, sizeof(*this));
	}
};
// REQUESTID_MONITOR_LEVEL_DISTRIBUTE
//////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////
// REQUESTID_RELATION_GETLIST
// »ñÈ¡ÎÒºÍË­ÓĞ¹ØÏµµÄÍæ¼ÒÁĞ±í - ÊäÈë½á¹¹Ìå
struct SRelationGetList_Set
{
	int	lActorID;	// Íæ¼ÒID

	SRelationGetList_Set()
	{
		memset(this, 0, sizeof(*this));
	}
};

// »ñÈ¡ÎÒºÍË­ÓĞ¹ØÏµµÄÍæ¼ÒÁĞ±í - Êä³ö½á¹¹Ìå
struct SRelationGetList_Get
{
	int	lReturn;		// ½á¹û·µ»Ø
	char	szDes[128];		// ½á¹ûÃèÊö

	int	lActorNum;			// ÓĞ¹ØÏµµÄÍæ¼Ò¸öÊı

	SRelationGetList_Get()
	{
		memset(this, 0, sizeof(*this));
	}
};

// »ñÈ¡ÎÒºÍË­ÓĞ¹ØÏµµÄÍæ¼ÒÁĞ±í - Êä³ö½á¹û¼¯½á¹¹Ìå
struct SRelationGetList_GetSet
{
	int	lRelationID;			// Íæ¼ÒID
	char	szActorName[19];		// Íæ¼ÒÃû×Ö 

	BYTE	wProfession;			//Ö°Òµ
	BYTE	bSex;					//ĞÔ±ğ
	BYTE	bNation;				//¹ú¼Ò

	BYTE	bType;					//ÀàĞÍ(0ºÃÓÑ 1³ğÈË)

	BYTE    bFriendType;            //Óë×Ô¼ºµÄ¹ØÏµ  (ºÃÓÑÀàĞÍ²ÅÓĞ) ·òÆŞÊ¦¸µÍ½µÜ ÆÕÍ¨
	int    FriendValue;             //ÓÑºÃ¶È        (ºÃÓÑÀàĞÍ²ÅÓĞ)

	SRelationGetList_GetSet()
	{
		memset(this, 0, sizeof(*this));
	}
};
// REQUESTID_RELATION_GETLIST
//////////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////////
// REQUESTID_RELATION_GETLIST2
// »ñÈ¡Ë­ºÍÎÒÓĞ¹ØÏµµÄÍæ¼ÒÁĞ±í - ÊäÈë½á¹¹Ìå
struct SRelationGetList2_Set
{
	int	lActorID;	// Íæ¼ÒID

	SRelationGetList2_Set()
	{
		memset(this, 0, sizeof(*this));
	}
};

// »ñÈ¡Ë­ºÍÎÒÓĞ¹ØÏµµÄÍæ¼ÒÁĞí - Êä³ö½á¹¹Ìå
struct SRelationGetList2_Get
{
	int	lReturn;		// ½á¹û·µ»Ø
	char	szDes[128];		// ½á¹ûÃèÊö

	int	lRelationNum;			// ÓĞ¹ØÏµµÄÍæ¼Ò¸öÊı

	SRelationGetList2_Get()
	{
		memset(this, 0, sizeof(*this));
	}
};

// »ñÈ¡Ë­ºÍÎÒÓĞ¹ØÏµµÄÍæ¼ÒÁĞ±í - Êä³ö½á¹û¼¯½á¹¹Ìå
struct SRelationGetList2_GetSet
{
	int	lRelationID;	// Íæ¼ÒID

	SRelationGetList2_GetSet()
	{
		memset(this, 0, sizeof(*this));
	}
};
// REQUESTID_RELATION_GETLIST2
//////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////
//REQUESTID_RELATION_ADD
// ¸ù¾İID »òÕßÃû×Ö Ìí¼Ó¹ØÏµ - ÊäÈë½á¹¹Ìå
struct SRelationAddByID_Set
{
	int	lAskerActorID;         //ÇëÇóÕß½ÇÉ«ID
	int	lActorID;              //ĞèÌí¼Ó¹ØÏµµÄ½ÇÉ«ID
	char	szName[19];			   //ĞèÌí¼Ó¹ØÏµµÄ½ÇÉ«Ãû
	BYTE	bType;                 //²Ù×÷¹ØÏµÀàĞÍ£¨0ºÃÓÑ 1³ğÈË£©

	SRelationAddByID_Set()
	{
		memset(this, 0, sizeof(*this));
	}
};

// ¸ù¾İIDÌí¼Ó¹ØÏµ - Êä³ö½á¹¹Ìå
struct SRelationAddByID_Get
{
	int	lReturn;		// ½á¹û·µ»Ø
	char	szDes[128];		// ½á¹ûÃèÊö


	int	lrActorID;              //Ìí¼Ó¹ØÏµµÄ½ÇÉ«ID
	char	szrName[19];			//Ìí¼Ó¹ØÏµµÄ½ÇÉ«Ãû
	BYTE	wProfession;			//Ö°Òµ
	BYTE	bSex;					//ĞÔ±ğ
	BYTE	bNation;				//¹ú¼Ò

	BYTE   bFriendType;            //Óë×Ô¼ºµÄ¹ØÏµ  (ºÃÓÑÀàĞÍ²ÅÓĞ)
	int    FriendValue;            //ÓÑºÃ¶È        (ºÃÓÑÀàĞÍ²ÅÓĞ)

	SRelationAddByID_Get()
	{
		memset(this, 0, sizeof(*this));
	}
};
//REQUESTID_RELATION_ADD
//////////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////////
// REQUESTID_RELATION_UPDATE
// ¸üĞÂ¹ØÏµ - ÊäÈë½á¹¹Ìå
struct SRelationUpdate_Set
{
	int lAskerActorID;         //ÇëÇóÕß½ÇÉ«ID
	int lActorID;              //Ğè±ä¸ü¹ØÏµµÄ½ÇÉ«ID

	BYTE bType;                 //²Ù×÷¹ØÏµÀàĞÍ£¨0ºÃÓÑ 1³ğÈË 2 ºÚÃûµ¥ £©

	BYTE    bFriendType;            //Óë×Ô¼ºµÄ¹ØÏµ  (ºÃÓÑÀàĞÍ²ÅÓĞ)
	int    FriendValue;            //ÓÑºÃ¶È        (ºÃÓÑÀàĞÍ²ÅÓĞ)


	SRelationUpdate_Set()
	{
		memset(this, 0, sizeof(*this));
	}
};

// ¸üĞÂ¹ØÏµ - Êä³ö½á¹¹Ìå
struct SRelationUpdate_Get
{
	int	lReturn;		// ½á¹û·µ»Ø
	char	szDes[128];		// ½á¹ûÃèÊö

	SRelationUpdate_Get()
	{
		memset(this, 0, sizeof(*this));
	}
};
// REQUESTID_RELATION_UPDATE
//////////////////////////////////////////////////////////////////////////



//////////////////////////////////////////////////////////////////////////
// REQUESTID_RELATION_DELETE
// É¾³ı ¹ØÏµ - ÊäÈë½á¹¹Ìå  2¸öÈËÖ»ÄÜÊÇÔÚºÃÓÑ»òÕß³ğÈËµÄ×´Ì¬ÏÂ ²ÅÄÜ¸üĞÂ
struct SRelationDel_Set
{
	int lAskerActorID;         //ÇëÇóÕß½ÇÉ«ID
	int lActorID;              //Ğè±ä¸ü¹ØÏµµÄ½ÇÉ«ID

	SRelationDel_Set()
	{
		memset(this, 0, sizeof(*this));
	}
};

// ¸üĞÂ¹ØÏµ - Êä³ö½á¹¹Ìå
struct SRelationDel_Get
{
	int	lReturn;		// ½á¹û·µ»Ø
	char	szDes[128];		// ½á¹ûÃèÊö

	SRelationDel_Get()
	{
		memset(this, 0, sizeof(*this));
	}
};
// REQUESTID_RELATION_DELETE
//////////////////////////////////////////////////////////////////////////



//////////////////////////////////////////////////////////////////////////
// REQUESTID_GAMEEVENT_SEND
// ·¢ËÍÓÎÏ·ÊÂ¼ş - ÊäÈë½á¹¹Ìå
struct SGameEventSend_Set
{
	s32		lActorID;					// ·¢ËÍÓÎÏ·ÊÂ¼şµÄ½ÇÉ«ID
	s32		lToActorID;					// ½ÓÊÕÓÎÏ·ÊÂ¼şµÄ½ÇÉ«ID
	char	szGameEventDesz[256];		// ÓÊ¼şÕıÎÄ
	u8		lGameEventState;			// ÓÎÏ·ÊÂ¼ş×´Ì¬(1: Î´ÁìÈ¡, 2: ÒÑ¶ÁÈ¡, 0: Ã»ÓĞ¿ÉÁìÈ¡)
	char	szGoodsBuffer[36];			// 6¸öÎïÆ·(4×Ö½ÚlGoodsID + 2×Ö½ÚlGoodsNum)

	SGameEventSend_Set()
	{
		memset(this, 0, sizeof(*this));
	}
};

// ·¢ËÍÓÎÏ·ÊÂ¼ş - Êä³ö½á¹¹Ìå
struct SGameEventSend_Get
{
	s32		lReturn;			// ·µ»ØÖµ
	s32		lToActorID;			// ½ÓÊÕÓÎÏ·ÊÂ¼şµÄ½ÇÉ«ID
	s32		lGameEventID;		// ÓÎÏ·ÊÂ¼şID
	char	szTime[20];			// ·¢ËÍÊ±¼ä

	SGameEventSend_Get()
	{
		memset(this, 0, sizeof(*this));
	}
};
// REQUESTID_GAMEEVENT_SEND
//////////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////////
// REQUESTID_GAMEEVENT_GETLIST
// »ñÈ¡ÓÎÏ·ÊÂ¼şÁĞ±í - ÊäÈë½á¹¹Ìå
struct SGameEventGetList_Set
{
	s32	lActorID;		// Íæ¼ÒID

	SGameEventGetList_Set()
	{
		memset(this, 0, sizeof(*this));
	}
};

// »ñÈ¡ÓÎÏ·ÊÂ¼şÁĞ±í - Êä³ö½á¹¹Ìå
struct SGameEventGetList_Get
{
	s32		lReturn;				// ·µ»ØÖµ
	s32		lGameEventID;			// ÓÎÏ·ÊÂ¼şID
	s32		lSendActorID;			// ·¢ËÍÓÎÏ·ÊÂ¼şµÄ½ÇÉ«ID
	char	szGameEventDesz[256];	// ÓÎÏ·ÊÂ¼şÕıÎÄ
	char	szTime[20];				// ·¢ËÍÊ±¼ä
	u8		lGameEventState;		// ÓÎÏ·ÊÂ¼ş×´Ì¬(1: Î´ÁìÈ¡, 2: ÒÑ¶ÁÈ¡, 0: Ã»ÓĞ¿ÉÁìÈ¡)
	s32		lLeftTime;				// Ê£Óà±£´æÌìÊı
	char	szGoodsBuffer[36];		// 6¸öÎïÆ·(4×Ö½ÚlGoodsID + 2×Ö½ÚlGoodsNum)

	SGameEventGetList_Get()
	{
		memset(this, 0, sizeof(*this));
	}
};
// REQUESTID_GAMEEVENT_GETLIST
//////////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////////
// REQUESTID_GAMEEVENT_UPDATE
// ¸üĞÂÓÎÏ·ÊÂ¼ş - ÊäÈë½á¹¹Ìå
struct SGameEventUpdate_Set
{
	s32		lActorID;		// Íæ¼ÒID
	s32		lGameEventID;	// ÓÎÏ·ÊÂ¼şID

	SGameEventUpdate_Set()
	{
		memset(this, 0, sizeof(*this));
	}
};

// ¸üĞÂÓÎÏ·ÊÂ¼ş - Êä³ö½á¹¹Ìå
struct SGameEventUpdate_Get
{
	s32		lReturn;		// ·µ»ØÖµ

	SGameEventUpdate_Get()
	{
		memset(this, 0, sizeof(*this));
	}
};

// ¸üĞÂÓÎÏ·ÊÂ¼ş - Êä³ö½á¹¹Ìå½á¹û¼¯
// REQUESTID_GAMEEVENT_UPDATE
//////////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////////
// REQUESTID_GAMEEVENT_DEL
// É¾³ıÓÎÏ·ÊÂ¼ş - ÊäÈë½á¹¹Ìå
struct SGameEventDel_Set
{
	s32		lActorID;		// Íæ¼ÒID
	s32		lGameEventID;	// ÓÎÏ·ÊÂ¼şID

	SGameEventDel_Set()
	{
		memset(this, 0, sizeof(*this));
	}
};

// É¾³ıÓÎÏ·ÊÂ¼ş - Êä³ö½á¹¹Ìå
struct SGameEventDel_Get
{
	s32		lReturn;		// ·µ»ØÖµ

	SGameEventDel_Get()
	{
		memset(this, 0, sizeof(*this));
	}
};
// É¾³ıÓÎÏ·ÊÂ¼ş - Êä³ö½á¹¹Ìå½á¹û¼¯
// REQUESTID_GAMEEVENT_DEL
//////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////
// REQUESTID_CHECK_EXERCISE_GET
// »î¶¯ÅĞ¶Ï - ÊäÈë½á¹¹Ìå
struct SCheckExercise_Set
{
	int	lExerciseID;	// »î¶¯ID
	s64	qwUserID;		// Íæ¼ÒID
	int	lActorID;		// ½ÇÉ«ID
	char	ActorName[19];	// ½ÇÉ«Ãû×Ö
	char	szIP[16];		// Íæ¼ÒµÇÂ½IP
	char	lParam_1[64];	// ²ÎÊı1
	char	lParam_2[64];	// ²ÎÊı2
	char	lParam_3[64];	// ²ÎÊı3

	SCheckExercise_Set()
	{
		memset(this,0,sizeof(*this));
	}
};

// »î¶¯ÅĞ¶Ï - Êä³ö½á¹¹Ìå
struct SCheckExercise_Get
{
	int	lReturn;		// ·µ»ØÖµ
	char	szDes[128];		// ·µ»ØÃèÊö

	SCheckExercise_Get()
	{
		memset(this,0,sizeof(*this));
	}
};

// REQUESTID_CHECK_EXERCISE_GET
//////////////////////////////////////////////////////////////////////////



//////////////////////////////////////////////////////////////////////////
// ´óÈüÅÅÃûDB½á¹¹Ìå
//////////////////////////////////////////////////////////////////////////

//REQUESTID_RANK_GET
//»ñÈ¡ËùÓĞ´óÈüÅÅÃûĞÅÏ¢ - ÊäÈë½á¹¹Ìå
struct SRankGet_Set
{
	s32	lType;		                          // ÀàĞÍ

	SRankGet_Set()
	{
		memset(this, 0, sizeof(*this));
	}
};
// »ñÈ¡ËùÓĞ´óÈüÅÅÃûĞÅÏ¢ - Êä³ö½á¹¹Ìå
struct SRankGet_Get
{
	s32	lReturn;		                          // ·µ»ØÖµ     0:Ã»ÕÒµ½; 1:ÕÒµ½
	s32	nRank;						  // ÅÅÃû
	s64	lUserID;					  // ÕËºÅID
	s32	lActorID;					  // ½ÇÉ«ID
	s32	lLevel;						  // µÈ¼¶
	s8	byHeadPortraitId;				  // Í·Ïñ

	SRankGet_Get()
	{
		memset(this, 0, sizeof(*this));
	}
};
//EQUESTID_RANK_GET
//////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////
//REQUESTID_RANK_UPDATE
// ĞŞ¸Ä´óÈüÅÅÃûĞÅÏ¢ - ÊäÈë½á¹¹Ìå Èç¹û¸ÃÃû´Î²»´æÔÚ¾Í²åÈë
struct SRankUpdate_Set
{
	s32	nRank;		                          // ÅÅÃû
	s64	lUserID;				  // ÕËºÅID
	s32	lActorID;				  // ½ÇÉ«ID
	s32	lLevel;					  // µÈ¼¶
	s8	byHeadPortraitId;			  // Í·Ïñ		

	SRankUpdate_Set()
	{
		memset(this, 0, sizeof(*this));
	}
};

// ĞŞ¸Ä´óÈüÅÅÃûĞÅÏ¢ - Êä³ö½á¹¹Ìå
struct SRankUpdate_Get
{
	s32	lReturn;		                         // ·µ»ØÖµ

	SRankUpdate_Get()
	{
		memset(this, 0, sizeof(*this));
	}
};
//REQUESTID_RANK_UPDATE
//////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////
// RQUESTID_RANKPRIZE_GET
// »ñÈ¡´óÈüÈÕÅÅÃû½±Àø - ÊäÈë½á¹¹Ìå
struct SRankPrizeGet_Set
{
	s64	lUserID;		                          // ÕËºÅID
	s32	lActorID;					  // ½ÇÉ«ID

	SRankPrizeGet_Set()
	{
		memset(this, 0, sizeof(*this));
	}
};

// »ñÈ¡´óÈüÈÕÅÅÃû½±Àø - Êä³ö½á¹¹Ìå
struct SRankPrizeGet_Get
{
	s32	lReturn;		                         // ·µ»ØÖµ
	s32	lRID;						 // ´óÈü½±ÀøÎ¨Ò»ID
	s32	nRank;						 // ÅÅÃû
	s32	logTime;					 // ¼ÇÂ¼Ê±¼ä

	SRankPrizeGet_Get()
	{
		memset(this, 0, sizeof(*this));
	}
};

// REQUESTID_RANKPRIZE_GET
///////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////////
// REQUESTID_RANKPRIZE_UPDATE
// ÁìÈ¡Ö¸¶¨´óÈü½±Àø - ÊäÈë½á¹¹Ìå
struct SRankPrizeUpdate_Set
{
        s32     lRID;                                          // ´óÈü½±ÀøÎ¨Ò»ID

        SRankPrizeUpdate_Set()
        {
                memset(this, 0, sizeof(*this));
        }
};

// ÁìÈ¡Ö¸¶¨´óÈü½±Àø - Êä³ö½á¹¹Ìå
struct SRankPrizeUpdate_Get
{
        s32     lReturn;                                         // ·µ»ØÖµ

        SRankPrizeUpdate_Get()
        {
                memset(this, 0, sizeof(*this));
        }
};
// REQUESTID_RANKPRIZE_UPDATE
//////////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////////
// REQUESTID_RANKPRIZE_INSERT
// Éú³É±¾´Î´óÈüÅÅÃû½á¹û  - ÊäÈë½á¹¹Ìå
struct SRankPrizeInsert_Set
{
        s32     lType;                                          // ÀàĞÍ-ÔİÊ±Ã»ÓÃµ½

        SRankPrizeInsert_Set()
        {
                memset(this, 0, sizeof(*this));
        }
};

// Éú³É±¾´Î´óÈüÅÅÃû½á¹û - Êä³ö½á¹¹Ìå
struct SRankPrizeInsert_Get
{
        s32     lReturn;                                         // ·µ»ØÖµ

        SRankPrizeInsert_Get()
        {
                memset(this, 0, sizeof(*this));
        }
};
// REQUESTID_RANKPRIZE_INSERT
//////////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////////
// REQUESTID_RANKRECORD_INSERT
// Éú³ÉÕ½¶·¼ÇÂ¼  - ÊäÈë½á¹¹Ìå
struct SRankRecordInsert_Set
{
	s64	lAttUserID;					// ¹¥·½ÕËºÅID
	s64	lDefUserID;					// ÊØ·½ÕËºÅID
	s8	lResult;					// ½á¹û
	s32	lAttRank;					// ¹¥·½ÅÅÃû±ä»¯
	s32	lDefRank;					// ÊØ·½ÅÅÃû±ä»¯

	SRankRecordInsert_Set()
        {
                memset(this, 0, sizeof(*this));
        }
};

// Éú³ÉÕ½¶·¼ÇÂ¼ - Êä³ö½á¹¹Ìå
struct SRankRecordInsert_Get
{
        s32     lReturn;                                         // ·µ»ØÖµ

        SRankRecordInsert_Get()
        {
                memset(this, 0, sizeof(*this));
        }
};

// REQUESTID_RANKRECORD_INSERT
//////////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////////
// REQUESTID_RANKRECORD_GET
// »ñÈ¡Õ½¶·¼ÇÂ¼  - ÊäÈë½á¹¹Ìå
struct SRankRecordGet_Set
{
	s64	lUserID;					// ÕËºÅID
	s32	lActorID;					// ½ÇÉ«ID

	SRankRecordGet_Set()
        {
                memset(this, 0, sizeof(*this));
        }
};

// »ñÈ¡Õ½¶·¼ÇÂ¼ - Êä³ö½á¹¹Ìå
struct SRankRecordGet_Get
{
	s32     lReturn;                                         // ·µ»ØÖµ
	s64	lAttUserID;					 // ¹¥·½ÕËºÅID
	s64     lDefUserID;                                      // ÊØ·½ÕËºÅID
	s8      lResult;                                         // ½á¹û
        s32     lAttRank;                                        // ¹¥·½ÅÅÃû±ä»¯
	s32	lDefRank;					 // ÊØ·½ÅÅÃû±ä»¯
	s32	lLogTime;					 // ¼ÇÂ¼Ê±¼ä

	SRankRecordGet_Get()
        {
                memset(this, 0, sizeof(*this));
        }
};
// REQUESTID_RANKRECORD_GET
//////////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////////
/// REQUESTID_UNION_CREATE_ID
/// ÇëÇóÖĞĞÄ¼Ò×åÊı¾İ¿â·ÖÅäID
struct SUnionCreateID_Set
{
	char	szUnionName[20+1];			// ¼Ò×åÃû³Æ
	BYTE	byCountryID;				// ¼Ò×åËùÔÚ¹ú¼Ò
	//BYTE byCityID;					// ¼Ò×åËùÔÚ³ÇÊĞ

	/// ÏÂÃæÊÇÒ»¸ö×åÔ±µÄÊı¾İ£¨Ó¦¸ÃÊÇ´´½¨Õß£©
	DWORD	dwMemberID;					// ×åÔ±ID
	char	psMemberName[18 + 1];		// ×åÔ±Ãû
	BYTE	byPost;						// ×åÔ±Ö°Î»

	SUnionCreateID_Set()
	{
		memset(this, 0, sizeof(*this));
	}
};

/// ·µ»Ø·ÖÅäµÄ¼Ò×åID - Êä³ö½á¹¹Ìå
struct SUnionCreateID_Get
{
	int lReturn;						// ·µ»ØÖµ
	char szDes[128];					// ·µ»ØÃèÊö
	DWORD dwUnionID;					// ·µ»Ø¼Ò×åID

	SUnionCreateID_Get()
	{
		memset(this, 0, sizeof(*this));
	}
};
/// REQUESTID_UNION_CREATE_ID
//////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////
/// REQUESTID_UNION_DELETE_ID
/// ÇëÇóÖĞĞÄ¼Ò×åÊı¾İ¿âÉ¾³ıID
struct SUnionDeleteID_Set
{
	DWORD dwUnionID;					// ¼Ò×åID

	SUnionDeleteID_Set()
	{
		memset(this, 0, sizeof(*this));
	}
};

/// ·µ»ØÉ¾³ı½á¹û - Êä³ö½á¹¹Ìå
struct SUnionDeleteID_Get
{
	int lReturn;						// ·µ»ØÖµ
	char szDes[128];					// ·µ»ØÃèÊö

	SUnionDeleteID_Get()
	{
		memset(this, 0, sizeof(*this));
	}
};
/// REQUESTID_UNION_DELETE_ID
//////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////
/// REQUESTID_UNION_REQUEST	
/// ÇëÇó¼Ò×åÊı¾İ - ÊäÈë½á¹¹Ìå
struct SUnionInfoList_Set
{
	DWORD dwPageSize;					// Ã¿Ò³ÏÔÊ¾¼ÇÂ¼ÌõÊı£¬Ä¬ÈÏÎª100 
	DWORD PageIndex;					// µ±Ç°ÌáÈ¡ÒªÏÔÊ¾µÄÒ³Âë£¬Ä¬ÈÏÎª1£¬Êı¾İ¿â¸ù¾İPageSize,PageIndex ¼ÆËã·µ»ØÒ»Ò³Êı¾İ   

	SUnionInfoList_Set()
	{
		memset(this, 0, sizeof(*this));
	}
};

/// ÇëÇó¼Ò×åÊı¾İ - Êä³ö½á¹¹Ìå
struct SUnionInfoList_Get
{
	int lReturn;						// ·µ»ØÖµ
	char szDes[128];					// ·µ»ØÃèÊö
	DWORD RetTotal;						// ×ÜÊı¾İ¸öÊı
	DWORD RetCount;						// ·µ»ØÊı¾İ¸öÊı£¨ºóÃæ¸úÉÏN¸öSUnionDataInfo£©
	DWORD RetPageIndex;					// ×ÜÒ³Êı

	SUnionInfoList_Get()
	{
		memset(this, 0, sizeof(*this));
	}
};

/// ÇëÇó¼Ò×åÊı¾İ - Êä³ö½á¹¹Ìå½á¹û¼¯
struct SUnionInfoList_GetSet
{
	DWORD dwUnionID;					// ¼Ò×åID
	char szUnionName[20+1];				// ¼Ò×åÃû³Æ
	// BYTE byCityID;						// ¼Ò×åËùÊô³ÇÊĞ
	BYTE byCountryID;					// ¼Ò×åËùÊô¹ú¼Ò
	BYTE byLevel;						// ¼Ò×åµÈ¼¶
	DWORD dwMasterID;					// ¼Ò×å×å³¤ID
	char szMasterName[18+1];			// ¼Ò×å×å³¤Ãû³Æ
	BYTE szUnionPower[40];				// ¼Ò×åÈ¨ÏŞÁĞ±í 16Î»Ò»¸öÖ°ÎñÈ¨ÏŞ 2 *20¸öÖ°Îñ
	char szUnionNote[200+1];			// ¼Ò×å¹«¸æ
	int lAlivePoint;					// ¼Ò×å»îÔ¾¶È£¨¶¨Ê±Æ÷¶¨Ê±¼õÉÙ£¬¼õÉÙµ½0Ôò½âÉ¢¼Ò×å£©
	DWORD	 lUnionExp;					// ¼Ò×å¾­Ñé
	BYTE	 szTreeBuffer[75];			// ¼Ò×å¿Æ¼¼Ê÷
	BYTE	 szShopBuffer1[100];		// ¼Ò×åÉÌµêÊı¾İÇø1
	BYTE	 szShopBuffer2[100];		// ¼Ò×åÉÌµêÊı¾İÇø2
	BYTE	 szShopBuffer3[100];		// ¼Ò×åÉÌµêÊı¾İÇø3
	BYTE	 szShopBuffer4[100];		// ¼Ò×åÉÌµêÊı¾İÇø4
	BYTE	 szShopBuffer5[100];		// ¼Ò×åÉÌµêÊı¾İÇø5

	SUnionInfoList_GetSet()
	{
		memset(this, 0, sizeof(*this));
	}
};
/// REQUESTID_UNION_REQUEST	
//////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////
/// REQUESTID_UNION_INSERT
/// ´´½¨¼Ò×å£¬²åÈëÊı¾İ¿â£¨Í¬Ê±²åÈëÒ»¸ö×åÔ±Êı¾İ£© - ÊäÈë½á¹¹Ìå
struct SUnion_Add_Set
{
	DWORD dwUnionID;					// ¼Ò×åID
	char szUnionName[20+1];				// ¼Ò×åÃû³Æ
	BYTE byCountryID;					// ¼Ò×åËùÔÚ¹ú¼Ò
	//BYTE byCityID;					// ¼Ò×åËùÔÚ³ÇÊĞ
	BYTE szUnionPower[40];				// ¼Ò×åÈ¨ÏŞÁĞ±í 16Î»Ò»¸öÖ°ÎñÈ¨ÏŞ 2 *20¸öÖ°Îñ

	/// ÏÂÃæÊÇÒ»¸ö×åÔ±µÄÊı¾İ£¨Ó¦¸ÃÊÇ´´½¨Õß£©
	DWORD	dwMemberID;					// ×åÔ±ID
	char	psMemberName[18 + 1];		// ×åÔ±Ãû
	BYTE	byPost;						// ×åÔ±Ö°Î»

	SUnion_Add_Set()
	{
		memset(this, 0, sizeof(*this));
	}
};

/// ·µ»Ø - Êä³ö½á¹¹Ìå
struct SUnion_Add_Get
{
	int lReturn;						// ·µ»ØÖµ
	char szDes[128];					// ·µ»ØÃèÊö

	SUnion_Add_Get()
	{
		memset(this, 0, sizeof(*this));
	}
};
/// REQUESTID_UNION_REQUEST	
//////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////
/// REQUESTID_UNION_UPDATE
/// ÇëÇó¸üĞÂ¼Ò×åÊı¾İ - ÊäÈë½á¹¹Ìå
struct SUnion_Update_Set
{
	DWORD dwUnionID;					// ¼Ò×åID
	char szUnionName[20+1];				// ¼Ò×åÃû³Æ
	BYTE byCountryID;					// ¼Ò×åËùÊô¹ú¼Ò ´´½¨¼Ò×åµÄÍæ¼ÒËùÔÚ¹ú¼Ò
	BYTE byLevel;						// ¼Ò×åµÈ¼¶
	//BYTE byCityID;					// ¼Ò×åËùÊô³ÇÊĞ
	DWORD dwMasterID;					// ¼Ò×å×å³¤ID
	char szMasterName[18+1];			// ¼Ò×å×å³¤Ãû³Æ
	BYTE szUnionPower[40];				// ¼Ò×åÈ¨ÏŞÁĞ±í 16Î»Ò»¸öÖ°ÎñÈ¨ÏŞ 2 *20¸öÖ°Îñ
	char szUnionNote[200+1];			// ¼Ò×å¹«¸æ
	int lLastAliveTime;				// ÉÏ´Î¼Ò×å»îÔ¾Ê±¼ä£¨ÉÏÒ»´Î×îºóÒ»¸ö×åÔ±ÏÂÏßµÄÊ±¼ä£©
	DWORD lUnionExp;					// ¼Ò×å¾­Ñé

	SUnion_Update_Set()
	{
		memset(this, 0, sizeof(*this));
	}
};

/// ·µ»Ø¸üĞÂ¼Ò×å½á¹û - Êä³ö½á¹¹Ìå
struct SUnion_Update_Get
{
	int lReturn;						// ·µ»ØÖµ
	char szDes[128];					// ·µ»ØÃèÊö

	SUnion_Update_Get()
	{
		memset(this, 0, sizeof(*this));
	}
};
/// REQUESTID_UNION_REQUEST	
//////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////
/// REQUESTID_UNION_TEACH_UPDATE
/// ÇëÇó¸üĞÂ¼Ò×å¿Æ¼¼Êı¾İ - ÊäÈë½á¹¹Ìå
struct SUnion_Teach_Update_Set
{
	DWORD	 dwUnionID;					// ¼Ò×åID
	DWORD	 lUnionExp;					// ¼Ò×å¾­Ñé
	BYTE	 szTreeBuffer[75];			// ¼Ò×å¿Æ¼¼Ê÷
	BYTE	 szShopBuffer1[100];		// ¼Ò×åÉÌµêÊı¾İÇø1
	BYTE	 szShopBuffer2[100];		// ¼Ò×åÉÌµêÊı¾İÇø2
	BYTE	 szShopBuffer3[100];		// ¼Ò×åÉÌµêÊı¾İÇø3
	BYTE	 szShopBuffer4[100];		// ¼Ò×åÉÌµêÊı¾İÇø4
	BYTE	 szShopBuffer5[100];		// ¼Ò×åÉÌµêÊı¾İÇø5

	SUnion_Teach_Update_Set()
	{
		memset(this, 0, sizeof(*this));
	}
};

/// ·µ»Ø¸üĞÂ¼Ò×å½á¹û - Êä³ö½á¹¹Ìå
struct SUnion_Teach_Update_Get
{
	int lReturn;						// ·µ»ØÖµ
	char szDes[128];					// ·µ»ØÃèÊö

	SUnion_Teach_Update_Get()
	{
		memset(this, 0, sizeof(*this));
	}
};
/// REQUESTID_UNION_UPDATE_SHOP	
//////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////
/// REQUESTID_UNION_DELETE
/// ÇëÇó - ÊäÈë½á¹¹Ìå
struct SUnion_Del_Set
{
	DWORD dwUnionID;					// ¼Ò×åID
	BYTE byReason;						// É¾³ıÔ­Òò

	SUnion_Del_Set()
	{
		memset(this, 0, sizeof(*this));
	}
};

/// ·µ»Ø½á¹û - Êä³ö½á¹¹Ìå
struct SUnion_Del_Get
{
	int lReturn;						// ·µ»ØÖµ
	char szDes[128];					// ·µ»ØÃèÊö
	WORD wSize;							// É¾³ı×åÔ±µÄ¸öÊı

	SUnion_Del_Get()
	{
		memset(this, 0, sizeof(*this));
	}
};

/// ·µ»Ø½á¹û¼¯ - ×åÔ±½á¹¹
struct SUnion_Del_GetSet
{
	char psMember[18 + 1];				// É¾³ıµÄÍæ¼ÒÃû

	SUnion_Del_GetSet()
	{
		memset(this, 0, sizeof(*this));
	}
};
/// REQUESTID_UNION_REQUEST	
//////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////
/// REQUESTID_UNIONMMEBER_REQUEST
/// ÇëÇó×åÔ±Êı¾İ - ÊäÈë½á¹¹Ìå
struct SUnionMemberList_Set
{
	DWORD dwUnionID;					// ¼Ò×åID

	SUnionMemberList_Set()
	{
		memset(this, 0, sizeof(*this));
	}
};

/// ×åÔ±Êı¾İ½á¹û£¬·µ»Ø¸Ã¼Ò×åµÄËùÓĞ×åÔ±Êı¾İ - Êä³ö½á¹¹Ìå
struct SUnionMemberList_Get
{
	int lReturn;						// ·µ»ØÖµ
	char szDes[128];					// ·µ»ØÃèÊö
	WORD size;							// Êı¾İ¸öÊı£¨ºóÃæ¸úÉÏN¸öSUnionMemberList_GetSet£©

	SUnionMemberList_Get()
	{
		memset(this, 0, sizeof(*this));
	}
};

/// ×åÔ±Êı¾İ - Êä³ö½á¹¹Ìå½á¹û¼¯
struct SUnionMemberList_GetSet
{
	DWORD dwMemberID;					// ×åÔ±ID
	char psMemberName[18 + 1];			// ×åÔ±Ãû
	BYTE byPost;						// ×åÔ±Ö°Î»
	BYTE byProfession;					// ×åÔ±Ö°Òµ
	BYTE bySex;							// ×åÔ±ĞÔ±ğ
	int lLevel;						// ×åÔ±µÈ¼¶

	SUnionMemberList_GetSet()
	{
		memset(this, 0, sizeof(*this));
	}
};
/// REQUESTID_UNION_REQUEST	
//////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////
/// REQUESTID_UNIONMEMBER_INSERT
/// ¼ÓÈëÃÅ£¬²åÈëÊı¾İ¿â - ÊäÈë½á¹¹Ìå
struct SUnionMember_Add_Set
{
	DWORD	dwUnionID;					// ËùÊô¼Ò×åID
	DWORD	dwMemberID;					// ×åÔ±ID
	char	psMemberName[18 + 1];		// ×åÔ±Ãû
	BYTE	byPost;						// ×åÔ±Ö°Î»
	BYTE	byProfession;				// ×åÔ±Ö°Òµ
	BYTE	bySex;						// ×åÔ±ĞÔ±ğ
	int	lLevel;						// ×åÔ±µÈ¼¶

	SUnionMember_Add_Set()
	{
		memset(this, 0, sizeof(*this));
	}
};

/// ·µ»Ø - Êä³ö½á¹¹Ìå
struct SUnionMember_Add_Get
{
	int lReturn;						// ·µ»ØÖµ
	char szDes[128];					// ·µ»ØÃèÊö

	SUnionMember_Add_Get()
	{
		memset(this, 0, sizeof(*this));
	}
};
/// REQUESTID_UNION_REQUEST	
//////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////
/// REQUESTID_UNIONMEMBER_UPDATE
/// ¸üĞÂ×åÔ±Êı¾İ - ÊäÈë½á¹¹Ìå
struct SUnionMember_Update_Set
{
	DWORD	dwUnionID;					// ËùÊô¼Ò×åID
	DWORD	dwMemberID;					// ×åÔ±ID
	char	psMemberName[18 + 1];		// ×åÔ±Ãû
	BYTE	byPost;						// ×åÔ±Ö°Î»
	BYTE	byProfession;				// ×åÔ±Ö°Òµ
	BYTE	bySex;						// ×åÔ±ĞÔ±ğ
	int	lLevel;						// ×åÔ±µÈ¼¶

	SUnionMember_Update_Set()
	{
		memset(this, 0, sizeof(*this));
	}
};

/// ·µ»Ø - Êä³ö½á¹¹Ìå
struct SUnionMember_Update_Get
{
	int lReturn;						// ·µ»ØÖµ
	char szDes[128];					// ·µ»ØÃèÊö

	SUnionMember_Update_Get()
	{
		memset(this, 0, sizeof(*this));
	}
};
/// REQUESTID_UNION_REQUEST	
//////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////
/// REQUESTID_UNIONMEMBER_DELETE
/// É¾³ı×åÔ±Êı¾İ - ÊäÈë½á¹¹Ìå
struct SUnionMember_Del_Set
{
	DWORD dwMemberID;					// ÇëÇóÉ¾³ıµÄ×åÔ±ID

	SUnionMember_Del_Set()
	{
		memset(this, 0, sizeof(*this));
	}
};

/// ·µ»Ø - Êä³ö½á¹¹Ìå
struct SUnionMember_Del_Get
{
	int lReturn;						// ·µ»ØÖµ
	char szDes[128];					// ·µ»ØÃèÊö

	SUnionMember_Del_Get()
	{
		memset(this, 0, sizeof(*this));
	}
};
/// REQUESTID_UNION_REQUEST	
//////////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////////
/// REQUESTID_DUMMY_BASE_GET
/// »ñÈ¡¼ÙÈË»ù±¾ĞÅÏ¢ - ÊäÈë½á¹¹Ìå
struct SDummy_Base_Request_Set
{
	int	lRequestActorID;		// ÇëÇóÕß½ÇÉ«ID
	u8		lRequestLevel;			// ÇëÇóÕßµÈ¼¶
	int		nNum;					// ÇëÇóÊıÁ¿
	int		nOffset;				// ÇëÇóÆ«ÒÆ
	s32		nRequestType;		// 0 : ÊÔÁ¶Ö®Ëş; 1 : PVP»î¶¯

	SDummy_Base_Request_Set()
	{
		memset(this, 0, sizeof(*this));
	}
};

struct SDummy_Base_Request_Get
{
	int	lReturn;						// ·µ»ØÖµ
	s64	qwDummyUserID;					// ¼ÙÈËÕËºÅID
	int	lDummyActorID;					// ¼ÙÈË½ÇÉ«ID
	char		ActorName[13];					// ½ÇÉ«Ãû×Ö
	s8		bySex;							// ĞÔ±ğ
	s8		byHeadPortraitId;				// Í·ÏñID
	u8		lLevel;							// µÈ¼¶
	u32		lPVPTimes;						// ´ò¾º¼¼³¡´ÎÊı
	u32		lPVPWinTimes;					// ´ò¾º¼¼³¡Ó®µÄ´ÎÊı

	SDummy_Base_Request_Get()
	{
		memset(this, 0, sizeof(*this));
	}
};
/// REQUESTID_DUMMY_BASE_GET
//////////////////////////////////////////////////////////////////////////



//////////////////////////////////////////////////////////////////////////
/// REQUESTID_DUMMY_ALL_GET
/// »ñÈ¡¼ÙÈËÍê±¸ĞÅÏ¢ - ÊäÈë½á¹¹Ìå
struct SDummy_All_Request_Set
{
	int	lRoomID;				// ·¿¼äID
	s64	qwDummyUserID;			// ¼ÙÈËÕËºÅID

	SDummy_All_Request_Set()
	{
		memset(this, 0, sizeof(*this));
	}
};

struct SDummy_All_Request_Get
{
	int	lReturn;				// ·µ»ØÖµ
	s64		qwUserID;				// ÕËºÅID
	u32		lActorID;				// ½ÇÉ«ID
	char		ActorName[13];			// ½ÇÉ«Ãû×Ö
	char	szHeadURL[256];			// ¼ÙÈËÍ·ÏñURL
	s8		bySex;					// ĞÔ±ğ
	s8		byHeadPortraitId;		// Í·ÏñID
	u8		lLevel;					// µÈ¼¶
	u32		lPVPTimes;				// ´ò¾º¼¼³¡´ÎÊı
	u32		lPVPWinTimes;			// ´ò¾º¼¼³¡Ó®µÄ´ÎÊı

	SDummy_All_Request_Get()
	{
		memset(this, 0, sizeof(*this));
	}
};

struct SDummy_Notch_Request_Get
{
	BYTE	lGoodsNum;				// ÎïÆ·¸öÊı, ×î´ó²»ÄÜ³¬¹ı40¸ö

	SDummy_Notch_Request_Get()
	{
		memset(this, 0, sizeof(*this));
	}
};

/// REQUESTID_DUMMY_ALL_GET
//////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////
/// REQUESTID_FRIEND_BASE_GET
/// »ñÈ¡ºÃÓÑ»ù±¾ĞÅÏ¢ - ÊäÈë½á¹¹Ìå
struct SFriend_Base_Request_Set
{
	s32		lRequestActorID;		// ÇëÇóÕß½ÇÉ«ID
	s64		qwFriendUserID;			// ºÃÓÑµÄÕËºÅID
	

	SFriend_Base_Request_Set()
	{
		memset(this, 0, sizeof(*this));
	}
};

struct SFriend_Base_Request_Get
{
	s32		lReturn;						// ·µ»ØÖµ
	s64		qwFriendUserID;					// ºÃÓÑÕËºÅID
	s32		lFriendActorID;					// ºÃÓÑ½ÇÉ«ID
	char	ActorName[13];					// ½ÇÉ«Ãû×Ö
	s8		bySex;							// ĞÔ±ğ
	s8		byHeadPortraitId;				// Í·ÏñID
	u8		lLevel;							// µÈ¼¶
	u32		lPVPTimes;						// ´ò¾º¼¼³¡´ÎÊı
	u32		lPVPWinTimes;					// ´ò¾º¼¼³¡Ó®µÄ´ÎÊı

	SFriend_Base_Request_Get()
	{
		memset(this, 0, sizeof(*this));
	}
};
/// REQUESTID_FRIEND_BASE_GET
//////////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////////
/// REQUESTID_HERO_REQUEST
/// ÇëÇóÓ¶±ø - ÊäÈë½á¹¹Ìå
struct SHero_Request_Set
{
	u32 dwActorID;						/// Íæ¼ÒID

	SHero_Request_Set()
	{
		memset(this, 0, sizeof(*this));
	}
};

/// Ó¶±øÊı¾İ
struct SHeroData
{
	u8	lHeroIndex;						/// Ë÷Òı
	s32 nTemplateID;					/// Ä£°åID
	u8	bLevel;							/// µÈ¼¶
	u32 nExp;							/// ¾­Ñé
	u8  bState;							/// ×´Ì¬
	s32 nHungry;						/// ±¥Ê³¶È

	SHeroData()
	{
		memset(this, 0, sizeof(*this));
	}
};
/// REQUESTID_HERO_REQUEST
//////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////
/// REQUESTID_ONE_HERO_REQUEST
/// ÇëÇóÓ¶±ø - ÊäÈë½á¹¹Ìå
struct SOneHero_Request_Set
{
	u32 dwActorID;						/// Íæ¼ÒID
	u8	lHeroIndex;						/// Ë÷Òı

	SOneHero_Request_Set()
	{
		memset(this, 0, sizeof(*this));
	}
};

/// REQUESTID_ONE_HERO_REQUEST
//////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////
/// REQUESTID_HERO_UPDATE
/// Ó¶±øÊı¾İ¸üĞÂ
///
/// ¸üĞÂÓ¶±ø - ÊäÈë½á¹¹Ìå
struct SHero_Update_Set
{
	u32 dwActorID;						/// Íæ¼ÒID
	u8  lHeroIndex;						/// Ë÷Òı
	s32 nTemplateID;					/// Ó¶±øÄ£°åID
	u8	bLevel;							/// µÈ¼¶
	u32 nExp;							/// ¾­Ñé
	u8  bState;							/// ×´Ì¬
	s32 nHungry;						/// ±¥Ê³¶È

	SHero_Update_Set()
	{
		memset(this, 0, sizeof(*this));
	}
};

/// ¸üĞÂÓ¶±ø - Êä³ö½á¹¹Ìå
struct SHero_Update_Get
{
	int lReturn;						/// ·µ»ØÖµ
	char szDes[128];					/// ·µ»ØÃèÊö

	SHero_Update_Get()
	{
		memset(this, 0, sizeof(*this));
	}
};
/// REQUESTID_HERO_UPDATE
//////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////
/// REQUESTID_HERO_DELETE
/// Ó¶±øÊı¾İÉ¾³ı
/// 
/// É¾³ıÓ¶±ø - ÊäÈë½á¹¹Ìå
struct SHero_Delete_Set
{
	u32 dwActorID;					/// Ó¶±øÖ÷ÈËµÄID
	u8  lHeroIndex;					/// Ó¶±øID;

	SHero_Delete_Set()
	{
		memset(this, 0, sizeof(*this));
	}
};

/// É¾³ıÓ¶±ø - Êä³ö½á¹¹Ìå
struct SHero_Delete_Get
{
	int lReturn;						/// ·µ»ØÖµ
	char szDes[128];					/// ·µ»ØÃèÊö

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
/// ²åÈëÓ¶±ø - ÊäÈë½á¹¹Ìå
struct SHero_Insert_Set
{
	u32 dwActorID;						/// Íæ¼ÒID
	u8  lHeroIndex;						/// Ë÷Òı
	s32 nPetTemplateID;					/// Ó¶±øÄ£°åID
	u8	bLevel;							/// µÈ¼¶
	u32 nExp;							/// ¾­Ñé

	SHero_Insert_Set()
	{
		memset(this, 0, sizeof(*this));
	}
};

/// ²åÈëÓ¶±ø - Êä³ö½á¹¹Ìå
struct SHero_Insert_Get
{
	int lReturn;						/// ·µ»ØÖµ
	char szDes[128];					/// ·µ»ØÃèÊö

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
/// »ñÈ¡Qµã¹ºÂòÎïÆ· - ÊäÈë½á¹¹Ìå
struct SQQBuyGoods_Set
{
	s64 lUserID;                   // ÓÃ»§ID
	s32 lActorID;		       // ½ÇÉ«ID

        SQQBuyGoods_Set()
        {
                memset(this, 0, sizeof(*this));
        }
};

/// »ñÈ¡Qµã¹ºÂòÎïÆ· - Êä³ö½á¹¹Ìå
struct SQQBuyGoods_Get
{
        s32 lReturn;                                            /// ·µ»ØÖµ
	s32 goodID;						/// ÎïÆ·ID
	s32 Num;						/// ÎïÆ·ÊıÁ¿

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
/// »ñÈ¡³ä»Æ×êĞÅÏ¢ - ÊäÈë½á¹¹Ìå
struct SQQYellowVIP_Set
{
        s64 lUserID;                   // ÓÃ»§ID
        s32 lActorID;                  // ½ÇÉ«ID

        SQQYellowVIP_Set()
        {
                memset(this, 0, sizeof(*this));
        }
};

/// »ñÈ¡Qµã¹ºÂòÎïÆ· - Êä³ö½á¹¹Ìå
struct SQQYellowVIP_Get
{
        s32 lReturn;                                            /// ·µ»ØÖµ
        s32 lYellowVIP;                                         /// ÊÇ·ñ³ä»Æ×ê(0:Ã»ÓĞ, 1:³äÁË)

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
/// »ñÈ¡Qµã³äÖµĞÅÏ¢ - ÊäÈë½á¹¹Ìå
struct SQQPointPrize_Set
{
	s64 lUserID;                   // ÓÃ»§ID
        s32 lActorID;                  // ½ÇÉ«ID
  s64 lStartTime;               // ¿ªÊ¼Ê±¼ä
  s64 lEndTime;                 // ½áÊøÊ±¼ä

	SQQPointPrize_Set()
        {
                memset(this, 0, sizeof(*this));
        }
};

/// »ñÈ¡Qµã³äÖµĞÅÏ¢ - Êä³ö½á¹¹Ìå
struct SQQPointPrize_Get
{
	s32 lReturn;                                            /// ·µ»ØÖµ
        s32 lQQPoint;                                           /// QµãÏû·Ñ(x10)

	SQQPointPrize_Get()
        {
                memset(this, 0, sizeof(*this));
        }

};
/// REQUESTID_QQ_GETPOINTPRIZE
//////////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////////
/// REQUESTID_UPDATE_PLAYER_DATA_COUNT
/// Íæ¼ÒÊı¾İÍ³¼Æ - ÊäÈë½á¹¹Ìå
struct SUpdate_Player_Data_Count_Set
{
  s32 lActorID;

  s32 staySurface1;    // Êı¾İÍ³¼Æ-½çÃæÍ£Áô
  s32 staySurface2;
  s32 staySurface3;
  s32 staySurface4;
  s32 staySurface5;
  s32 staySurface6;
  s32 staySurface7;
  s32 staySurface8;
  s32 staySurface9;
  s32 staySurface10;

  s32 fightMob1;        // Êı¾İÍ³¼Æ-´ò¹Ö
  s32 fightMob2;
  s32 fightMob3;
  s32 fightMob4;
  s32 fightMob5;

  s32 makeItem1;        // Êı¾İÍ³¼Æ-ÔìµÀ¾ß
  s32 makeItem2;
  s32 makeItem3;
  s32 makeItem4;
  s32 makeItem5;

  s32 makeEquip1;       // Êı¾İÍ³¼Æ-Ôì×°±¸
  s32 makeEquip2;
  s32 makeEquip3;
  s32 makeEquip4;
  s32 makeEquip5;

  s32 makeCard1;        // Êı¾İÍ³¼Æ-Ôì¿¨Æ¬
  s32 makeCard2;
  s32 makeCard3;
  s32 makeCard4;
  s32 makeCard5;

  SUpdate_Player_Data_Count_Set()
  {
    memset(this, 0, sizeof(*this));
  }
};
/// ÇëÇóÍæ¼ÒÊı¾İÍ³¼Æ - Êä³ö½á¹¹Ìå
struct SUpdate_Player_Data_Count_Get
{
	int lReturn;          // ·µ»ØÖµ
	char szDes[128];      // ·µ»ØÃèÊö

	SUpdate_Player_Data_Count_Get()
	{
		memset(this, 0, sizeof(*this));
	}
};
/// REQUESTID_UPDATE_PLAYER_DATA_COUNT
//////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////
/// REQUESTID_REQUEST_PLAYER_DATA_COUNT
/// ÇëÇóÍæ¼ÒÊı¾İÍ³¼Æ - ÊäÈë½á¹¹Ìå
struct SRequest_Player_Data_Count_Set
{
  s32   lActorID;     // ½ÇÉ«ID

  SRequest_Player_Data_Count_Set()
  {
    memset(this, 0, sizeof(*this));
  }
};
/// ÇëÇóÍæ¼ÒÊı¾İÍ³¼Æ - Êä³ö½á¹¹Ìå
struct SRequest_Player_Data_Count_Get
{
  int lReturn;          // ·µ»ØÖµ
  s32 staySurface1;    // Êı¾İÍ³¼Æ-½çÃæÍ£Áô
  s32 staySurface2;
  s32 staySurface3;
  s32 staySurface4;
  s32 staySurface5;
  s32 staySurface6;
  s32 staySurface7;
  s32 staySurface8;
  s32 staySurface9;
  s32 staySurface10;

  s32 fightMob1;        // Êı¾İÍ³¼Æ-´ò¹Ö
  s32 fightMob2;
  s32 fightMob3;
  s32 fightMob4;
  s32 fightMob5;

  s32 makeItem1;        // Êı¾İÍ³¼Æ-ÔìµÀ¾ß
  s32 makeItem2;
  s32 makeItem3;
  s32 makeItem4;
  s32 makeItem5;

  s32 makeEquip1;       // Êı¾İÍ³¼Æ-Ôì×°±¸
  s32 makeEquip2;
  s32 makeEquip3;
  s32 makeEquip4;
  s32 makeEquip5;

  s32 makeCard1;        // Êı¾İÍ³¼Æ-Ôì¿¨Æ¬
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
