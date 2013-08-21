API_Trace("打印测试啊")

----------------------------------------------
-- 注意：数据的加载数据，请勿随便调整
----------------------------------------------

--道具使用功能
API_LoadLuaFile('Lua/ItemUse/ItemUse.lua')
API_LoadLuaFile('Lua/Activity/Activity.lua')

-- ------------------------------------------
-- 描述: 客户端提交数据请求执行时调用这个函数
-- ------------------------------------------
function OnRequest(szFuncName)
	local targetFunction = _G[szFuncName]
	if type(targetFunction) == 'function' then
		targetFunction()
		return
	end
	
	--API_Trace("not find function:"..szFuncName)
end
























	