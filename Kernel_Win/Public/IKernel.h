#ifndef IKERNEL_H
#define IKERNEL_H

#include "ComDefine.h"

class VarList;
class Archive;
class IKernel;
class ILogicModule;
typedef I32 (__cdecl * CALLFUN)(IKernel *, const UI64, const VarList &);

enum eventtype
{
    //�¼�ö��
    EVENT_LAUNCH = 0,       //Launch��ʼ���������(�������������,����������)
    EVENT_CONNECT = 1,      //���ӳɹ�
    EVENT_NEW_CONNECT = 2,   //���µ�����
    EVENT_DISCONNECT = 3,   //Disconnect�Ͽ�����
};

class IKernel
{
public:
    //��ȡ��ǰӦ��ID
    virtual const UI32_ID GetAppID() = 0;
    //��ȡ��ǰ��ȺID
    virtual const UI32_ID GetClusterID() = 0;
    //��ȡ��ǰ������ID
    virtual const UI32_ID GetServerID() = 0;
    /*
     *��ȡ��ǰ���ŵĶ˿�
     *portInfo (0:UI16���Ŷ˿�����,1:const char * ��������(Lister,Server��),2:const char * ip, 3:UI16 �˿ں�,4:const char * ��������(Lister,Server��),5:const char * ip,6:UI16 �˿ں�...
     */
    virtual bool GetPublicPort(VarList & portInfo) = 0;

    //ע����Ϣ�ص�
    virtual bool AddMsgCall(const char * pStrPeerName, const UI32_ID nMsgID, const CALLFUN pFun) = 0;
    //ע���¼��ص� �¼�������enum eventtype
    virtual bool AddEventCall(const char * pStrPeerName, const UI32_ID nEventID, const CALLFUN pFun) = 0;
    //���������߼�ģ��
    virtual ILogicModule * FindModule(const char * pStrModuleName) = 0;

    //����Tcp��Ϣ
    virtual bool TcpSend(const UI16 nConID, const Archive & arch) = 0;

protected:
private:
};

#endif