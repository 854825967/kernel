/* 
 * File:   Console.h
 * Author: traveler
 *
 * Created on January 15, 2013, 6:38 PM
 */

#ifndef CONSOLE_H
#define	CONSOLE_H
#include "../Interface/IConsole.h"

class INetSystem;

class Console : public IConsole {
public:
    static IConsole * Employ();
    virtual bool Command(const char *);
    virtual bool Bron();
    virtual bool Initialize();
    virtual bool Dead();
    virtual bool Destroy();
private:
    Console();
    ~Console();

private:
    static Console * m_pSelf;
    static INetSystem * m_pNetSystem;
};

#endif	/* CONSOLE_H */

