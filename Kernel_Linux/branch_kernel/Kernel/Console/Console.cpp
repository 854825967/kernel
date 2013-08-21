/* 
 * File:   Console.cpp
 * Author: traveler
 * 
 * Created on January 15, 2013, 6:38 PM
 */

#include "Console.h"
#include "../NetSystem/NetSystem.h"

Console * Console::m_pSelf = NULL;
INetSystem * Console::m_pNetSystem = NULL;

IConsole * Console::Employ() {
    if (NULL == m_pSelf) {
        m_pSelf = NEW Console;
        if (!m_pSelf->Bron()) {
            delete m_pSelf;
            m_pSelf = NULL;
        }
    }
    return m_pSelf;
}

Console::Console() {

}

Console::~Console() {

}

bool Console::Command(const char *) {
    m_pNetSystem->Dead();
    return true;
}

bool Console::Bron() {
    return true;
}

bool Console::Dead() {
    return true;
}

bool Console::Initialize() {
    if(NULL == (m_pNetSystem = NetSystem::Employ())) {
        Assert(false);
        return false;
    }
    return true;
}

bool Console::Destroy() {
    
    if(m_pSelf != NULL) {
        delete m_pSelf;
        m_pSelf = NULL;
    }
    
    return true;
}
