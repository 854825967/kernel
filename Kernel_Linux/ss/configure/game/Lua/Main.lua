API_Trace("��ӡ���԰�")

----------------------------------------------
-- ע�⣺���ݵļ������ݣ�����������
----------------------------------------------

--����ʹ�ù���
API_LoadLuaFile('Lua/ItemUse/ItemUse.lua')
API_LoadLuaFile('Lua/Activity/Activity.lua')

-- ------------------------------------------
-- ����: �ͻ����ύ��������ִ��ʱ�����������
-- ------------------------------------------
function OnRequest(szFuncName)
	local targetFunction = _G[szFuncName]
	if type(targetFunction) == 'function' then
		targetFunction()
		return
	end
	
	--API_Trace("not find function:"..szFuncName)
end
























	