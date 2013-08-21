/*******************************************************************
** 文件名:	DChatMsg.h
** 版  权:	(C) 
** 创建人:	汪捷
** 日  期:	2010-02-04
** 版  本:	
** 描  述:	聊天定义头文件
** 应  用:  

**************************** 修改记录 ******************************
** 修改人: 
** 日  期: 
** 描  述: 
********************************************************************/

#ifndef CHAT_MSG
#define CHAT_MSG

#pragma pack(push,1)

//聊天类型 m_wKeyMa定义

//聊天所有频道
enum EChatChannel  
{
	
    CHATTYPE_AREA = 0,           //区域聊天 （C->S S->C）
	CHATTYPE_MAP,                //地图聊天 （C->S S->C）
	CHATTYPE_WORLD,              //世界聊天 （C->S S->C）
	CHATTYPE_TRADE,              //交易聊天 （C->S S->C）
	CHATTYPE_TEAM,               //组队聊天 （C->S S->C）
	CHATTYPE_FAMILY,             //家族聊天 （C->S S->C）
	CHATTYPE_PRIVATE,            //私聊     （C->S S->C）
	CHATTYPE_SYSTEM,             //系统消息频道  (S->C)
	CHATTYPE_CREATURE = 255,      //生物聊天信息  （S->C）
	
	CHATTYPE_MAX,
};

//////////////////////////////////////////////////////////////////////////
//系统消息相关定义
//////////////////////////////////////////////////////////////////////////
enum ESystemInfo   //发送对象枚举
{
	ESI_AREA = 0,             //区域发送
	ESI_MAP,                  //地图发送
	ESI_WORLD,                //世界发送
	ESI_ACTOR,                //指定玩家发送 
	ESI_TEAM,                 //指定队伍发送
	ESI_FAMILY,               //指定家族发送
    ESI_CONSORTIA,            //指定公会频道发送
	ESI_SYSTEM,               //指定系统频道发送          
};

enum ESInfoLevel
{
	ESIL_LOW = 0,          //低        聊天界面显示
	ESIL_NORMAL,           //普通      屏幕中间显示
	ESIL_HIGH,             //重要      屏幕顶部滚动显示
	ESIL_NEWMAIL,          //特殊用途  新邮件提示
	ESIL_HINT,             //提示信息  只在中间提示区显示
};

enum ESystemColor
{
	COLOR_NORMAL    = 0,     //正常提示
	COLOR_SPECIAL,           //特殊
	COLOR_IMPORTANT,         //重要
	//COLOR_MAPNAME,           //区域地图名(特殊)
	
};
// 系统消息字体
enum ESystemFontSize
{
	TYPE_SMALL       = 0,
	TYPE_NORMAL,
	TYPE_BIG,
};

struct SC_SYSTEMINFO
{
    ESystemInfo esi;       //发送对象类型
	ESInfoLevel level;     //重要性等级
	ESystemColor color;    //颜色
	ESystemFontSize font;  //字体大小
	int objectID;         //发送目标actorID

    SC_SYSTEMINFO()
	{
		esi = ESI_WORLD;
        level = ESIL_LOW;
		color = COLOR_NORMAL;
		font = TYPE_SMALL;
        objectID = 0;
	} 
};


/////////////////////////////////////////////////////////
//// 描  述：客户端发给服务器的聊天信息结构 
/////////////////////////////////////////////////////////
struct CS_CHAT
{
	BYTE nChannel;				// 频道
    int textLenth;              //文本内容长度
	int actorID ;		        // 发送者角色id
	char accepterName[32];      //接收者名字(用于私聊)

	BYTE	bItemsNum;		    // 附带物品数量
	int     buffLen;            // 所有附带物品BUFF总长
	//BYTE	BuffData[512];	    // 物品的存储BUFF一个物品guid+len+变长BUF, 最多5个

	CS_CHAT()
	{ 
		nChannel = CHATTYPE_AREA;
		actorID = 0;
		textLenth = 0;
		bItemsNum = 0;
		buffLen = 0;
		memset(accepterName,0,sizeof(accepterName)); 
	}
};

struct SC_CHAT
{
	BYTE nChannel;			// 频道
	int textLenth;			//文本内容长度
	LONGLONG lGuid;         //发送者账号ID
	char senderName[32];    //发送者角色NAME
	char accepterName[32];	//接收者名字(用于私聊)

	BYTE	bItemsNum;		    // 附带物品数量
	int     buffLen;            // 所有附带物品BUFF总长

	
	SC_CHAT()
	{		
		nChannel = CHATTYPE_AREA;
		textLenth = 0;
		lGuid = 0;
		bItemsNum = 0;
		buffLen = 0;
		memset(senderName,0,sizeof(senderName)); 
		memset(accepterName,0,sizeof(accepterName)); 
	}
};

//////////////////////////////////////////////////////////////////////////
//GM指令
//////////////////////////////////////////////////////////////////////////

enum GMCOMMOND
{
	GMD_GOTO            = 1 << 0,           //GM位置跳转
	GMD_Drag            = 1 << 1,           //拉人
	GMD_REFRESH_MONSTER = 1 << 2,           //刷新指定ID的怪物
	GMD_SPEAKFORBID     = 1 << 3,           //禁言
	GMD_KICK            = 1 << 4,           //踢人下线
};


//社会服 - 场景服聊天插件 子消息码
#define YS_S_SEND_CHAT                  1      //聊天内容转发

#define S_YS_SUB_ForbidSpeak_CHAT            2      //禁言（GM功能） 场景服-》社会服
struct SForbidSpeak_YSS
{
	char name[19];     //禁言者名字
	int time;         //禁言持续时间

    SForbidSpeak_YSS()
	{
		time = 0;
		memset(name,0,sizeof(name));
	}
};

#define YS_S_SUB_ForbidSpeak_CHAT            2      //禁言（GM功能） 社会服-》场景服
struct SForbidSpeak_SYS
{
	int actorID;      //禁言者ID
	int startTime;    //禁言             (单位是毫秒)
	int time;         //禁言禁言持续时间 (单位是秒)

	SForbidSpeak_SYS()
	{
		memset(this,0,sizeof(*this));
	}
};

#define SYS_SUB_UnForbidSpeak_CHAT           3      //解除 禁言 社会服《-》场景服 
struct SUnForbidSpeak
{
    int actorID;                         //解除禁言者ID

	SUnForbidSpeak()
	{
		memset(this,0,sizeof(*this));
	}
};

#define SYS_SUB_Kick_CHAT                    4      //踢人下线 社会服《-》场景服
struct SKickInfo
{
	char name[19];                           //被T者名字

	SKickInfo()
	{
		memset(name,0,sizeof(name));
	}
};

#pragma pack(pop)

#endif
