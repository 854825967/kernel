/*WIN 利用这个笨办法,把每个公用文件检查一遍是否有内存越界.
运行库要改成/MTD
extern "C" {
extern  HANDLE _crtheap;
}

#ifdef _DEBUG || DEBUG
if (HeapValidate(_crtheap, 0, NULL) ==FALSE)
{
	assert(0);
}
#endif
/*
 * typedef I32 (  *SOCKETCALL )( const IKernel *, const UI32 arg1, const UI32 arg1, const IVarList & args);
 * 各个参数的意义 pKernel 引擎所给指针
 * 1 消息回调 arg1 peerid, arg2 peerid(暂时不用，该参数留作扩展用), args 消息
 * 2 事件回调 arg1 eventid, arg2 peerid, args
*/
