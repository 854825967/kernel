/* 
 * File:   LogicManage.h
 * Author: traveler
 *
 * Created on December 18, 2012, 6:13 PM
 */

#ifndef LOGICMANAGE_H
#define	LOGICMANAGE_H

#include "../Interface/ILogicManage.h"
#include <map>
#include <vector>
#include <string>
using namespace std;

class IKernel;
class IConfigManage;
class ILogicModule;
class ILogSystem;

class LogicManage : public ILogicManage {
public:
    static ILogicManage * Employ();
    virtual bool Bron();
    virtual bool Initialize();
    virtual bool Dead();
    virtual bool Destroy();
    virtual ILogicModule * FindModule(const char * pStrModuleName);
    
private:
    LogicManage(){}
    ~LogicManage();
    
private:
    static LogicManage * m_pSelf;
    static IKernel * m_pKernel;
    static IConfigManage * m_pConfigManage;
    static ILogSystem * m_pLogSystem;
    
    vector<void *> m_vctDllHandle;
    map<string, ILogicModule *> m_mapModules;
};

#endif	/* LOGICMANAGE_H */

