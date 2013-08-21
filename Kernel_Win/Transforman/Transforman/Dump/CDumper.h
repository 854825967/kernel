#ifndef DUMPER_H
#define DUMPER_H

#include <imagehlp.h>
// �Զ�����Dump�ļ����࣬�������Dump����ģ�鿪ʼ�ĵط�����һ�� CDumper::GetInstance(); �Ϳ�����

class CDumper
{
public:
    static CDumper&    GetInstance( void );

    ~CDumper();

    // Ĭ��Ϊ ִ�е�����.dmp
    void SetDumpFileName( const TCHAR* dumpName );

protected:
    static void CreateMiniDump( EXCEPTION_POINTERS* pep );

    static LONG __stdcall snUnhandledExceptionFilter(PEXCEPTION_POINTERS pExceptionInfo);

    static    BOOL CALLBACK MiniDumpCallback( 
        PVOID pParam,
        const PMINIDUMP_CALLBACK_INPUT pInput, 
        PMINIDUMP_CALLBACK_OUTPUT       pOutput );

private:
    CDumper(void);

    CDumper( const CDumper& rhs ) {}
private:
    LPTOP_LEVEL_EXCEPTION_FILTER    m_previousFilter;
};


#endif    // DUMPER_H