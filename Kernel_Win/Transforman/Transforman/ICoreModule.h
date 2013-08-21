#ifndef ICMODULE_H
#define ICMODULE_H

class ICoreModule
{
public:
    virtual bool Initialize() = 0;
    virtual bool DelayInitialize() = 0;
    virtual bool Destroy() = 0;
protected:
private:
};

#endif //ICMODULE_H