---------------------------------------[ 更 新 记 录 ]---------------------------------------

----------------------------------------------
-- Lua随机数发生器种子 by xwdai 2010.6.4
----------------------------------------------
--math.randomseed(os.time())
--GlobalRanNum = math.random(1,100)


----------------------------------------------
-- 装备数据存放位 by xwdai 2010.5.18
----------------------------------------------
EquipTable =
{
	GetItemID = {},		--装备ID
	GetItemLevel = {}, 	--装备使用等级限制
	GetItemCLass = {}, 	--装备使用职业信息
	GetItemQuality = {}, --装备品质信息
}

----------------------------------------------
-- 药品数据存放位 by xwdai 2010.5.18
----------------------------------------------
LeeTable = 
{
	GetLeeID = {},		-- 药品ID
	GetLeeClass = {},	-- 药品使用职业信息
	GetLeeLevel = {},	-- 药品使用等级限制
}

----------------------------------------------
-- CatchPets TABLE by xwdai 2010.5.18
----------------------------------------------
CreatureTable =
{
	GetHP = {},
	GetPetsID = {},
	GetCatchBase ={},
}

----------------------------------------------
-- 获取Equipment相关信息 by xwdai 2010.5.19
----------------------------------------------
function LoadEquipmentConfig()
	--以下为获取EquipmentInfo.csv中物品使用等级字段信息
	if pIteminfoData == nil then
		return
	end	
	for idx, rIteminfoRec in pairs(pIteminfoData) do	
		if idx > 3 then
			EquipTable.GetItemCLass[idx-2] = tonumber(rIteminfoRec[8])
			EquipTable.GetItemLevel[idx-2] = tonumber(rIteminfoRec[9])
			EquipTable.GetItemQuality[idx-2] = tonumber(rIteminfoRec[13])
			EquipTable.GetItemID[idx-2] = tonumber(rIteminfoRec[1])
		end
	end
end
LoadEquipmentConfig()

-------------------------------------------------
-- 获取Leechdmodata相关信息 by xwdai 2010.5.19
-------------------------------------------------
function LoadLeedomConfig()
	if pLeeinfoData == nil then
		return
	end	
	for idx, rLeeinfoRec in pairs(pLeeinfoData) do	
		if idx>3 then
			LeeTable.GetLeeID[idx-2] = tonumber(rLeeinfoRec[1])
			LeeTable.GetLeeClass[idx-2] = tonumber(rLeeinfoRec[8])
			LeeTable.GetLeeLevel[idx-2] = tonumber(rLeeinfoRec[9])
		end
	end
end
LoadLeedomConfig()

-----------------------------------------------------------------------
-- 获取服务器当前时间 /year/month/day/hour/minute/ by xwdai 2010.5.21
-----------------------------------------------------------------------
function Clock()
	local YearInfo = os.date("%y")
	local MonthInfo = os.date("%m")  
	local DayInfo = os.date("%d")
	local HourInfo = os.date("%H")
	local MinuteInfo = os.date("%M")

	local Now_Year = tonumber(YearInfo)
	local Now_Month = tonumber(MonthInfo)
	local Now_Day = tonumber(DayInfo)
	local Now_Hour = tonumber(HourInfo)
	local Now_Minute = tonumber(MinuteInfo)

	local Now_Clock = Now_Year * 100000000 + Now_Month * 1000000 + Now_Day * 10000 + Now_Hour* 100 + Now_Minute
	return Now_Clock
end

-----------------------------------------------------------------------
-- 获取服务器当前时间 /hour/minute/ by xwdai 2010.5.21
-----------------------------------------------------------------------
function Clock2()
	local HourInfo = os.date("%H")
	local MinuteInfo = os.date("%M")

--	local Now_Year = tonumber(YearInfo)
--	local Now_Month = tonumber(MonthInfo)
--	local Now_Day = tonumber(DayInfo)
	local Now_Hour = tonumber(HourInfo)
	local Now_Minute = tonumber(MinuteInfo)

	local Now_Clock2 = Now_Hour* 100 + Now_Minute

--	API_Trace("Now_Year"..Now_Year)
--	API_Trace("Now_Month"..Now_Month)
--	API_Trace("Now_Day"..Now_Day)
--	API_Trace("Now_Hour"..Now_Hour)	
--	API_Trace("Now_Minute"..Now_Minute)	
--	API_Trace("Now_Clock"..Now_Clock)
	--API_Trace(string.format("%4d年%2d月%2d日",YearInfo,MonthInfo,DayInfo))
	return Now_Clock2
end

function Itemuse_4001(lActorID,lGoodsID,GoodsUid)
	local num = API_GetNumByGoodsID(lActorID,lGoodsID, 0)
	if num == 0 then
		API_SendErrorMsg(lActorID, "你大爷的开挂啊啊啊啊啊")
	else
		local id = lGoodsID - 4000
		local cardid = id*10000 + math.random(1,8)*100 + 1
		API_LuaStructDataPushItem(cardid,1)
		local canadd = API_CanAddItemToBags(lActorID)
		if canadd == true then
			API_RemoveGoods(lActorID,lGoodsID,1)
			API_AddGoods(lActorID,cardid,1)
			API_LuaStructDataSendItemList(lActorID)
		else
			API_SendPacketFull(lActorID, "您的背包已满，无法获得物品")
		end		
	end
	API_LuaStructDataClear()
end
function Itemuse_4005(lActorID,lGoodsID,GoodsUid)
	local num = API_GetNumByGoodsID(lActorID,lGoodsID, 0)
	if num == 0 then
		API_SendErrorMsg(lActorID, "你大爷的开挂啊啊啊啊啊")
	else
		local id = math.random(1,10)
		local cardid = 0
			cardid = (lGoodsID - 4004)*10000 + id*100 + 1
		API_LuaStructDataPushItem(cardid,1)
		local canadd = API_CanAddItemToBags(lActorID)
		if canadd == true then
			API_RemoveGoods(lActorID,lGoodsID,1)
			API_AddGoods(lActorID,cardid,1)
			API_LuaStructDataSendItemList(lActorID)
		else
			API_SendPacketFull(lActorID, "您的背包已满，无法获得物品")
		end
	end
	API_LuaStructDataClear()
end
function Itemuse_4006(lActorID,lGoodsID,GoodsUid)
	local num = API_GetNumByGoodsID(lActorID,lGoodsID, 0)
	if num == 0 then
		API_SendErrorMsg(lActorID, "你大爷的开挂啊啊啊啊啊")
	else
		local id = math.random(1,7)
		local cardid = 0
		if id == 1 then
			cardid = 10201
		end
		if id == 2 then
			cardid = 20201
		end
		if id == 3 then
			cardid = 30201
		end
		if id == 4 then
			cardid = 40201
		end
		if id == 5 then
			cardid = 10601
		end
		if id == 6 then
			cardid = 20701
		end
		if id == 7 then
			cardid = 40601
		end
		API_LuaStructDataPushItem(cardid,1)
		local canadd = API_CanAddItemToBags(lActorID)
		if canadd == true then
			API_RemoveGoods(lActorID,lGoodsID,1)
			API_AddGoods(lActorID,cardid,1)
			API_LuaStructDataSendItemList(lActorID)
		else
			API_SendPacketFull(lActorID, "您的背包已满，无法获得物品")
		end
	end
	API_LuaStructDataClear()
end

function Itemuse_4007(lActorID,lGoodsID,GoodsUid)
	local num = API_GetNumByGoodsID(lActorID,lGoodsID, 0)
	if num == 0 then
		API_SendErrorMsg(lActorID, "你大爷的开挂啊啊啊啊啊")
	else
		local id = math.random(1,7)
		local cardid = 0
		if id == 1 then
			cardid = 10301
		end
		if id == 2 then
			cardid = 20301
		end
		if id == 3 then
			cardid = 30301
		end
		if id == 4 then
			cardid = 40301
		end
		if id == 5 then
			cardid = 10701
		end
		if id == 6 then
			cardid = 30701
		end
		if id == 7 then
			cardid = 40701
		end
		API_LuaStructDataPushItem(cardid,1)
		local canadd = API_CanAddItemToBags(lActorID)
		if canadd == true then
			API_RemoveGoods(lActorID,lGoodsID,1)
			API_AddGoods(lActorID,cardid,1)
			API_LuaStructDataSendItemList(lActorID)
		else
			API_SendPacketFull(lActorID, "您的背包已满，无法获得物品")
		end
	end
	API_LuaStructDataClear()
end

function Itemuse_4008(lActorID,lGoodsID,GoodsUid)
	local num = API_GetNumByGoodsID(lActorID,lGoodsID, 0)
	if num == 0 then
		API_SendErrorMsg(lActorID, "你大爷的开挂啊啊啊啊啊")
	else
		local id = math.random(1,6)
		local cardid = 0
		if id == 1 then
			cardid = 10401
		end
		if id == 2 then
			cardid = 20401
		end
		if id == 3 then
			cardid = 30401
		end
		if id == 4 then
			cardid = 40401
		end
		if id == 5 then
			cardid = 20801
		end
		if id == 6 then
			cardid = 30801
		end
		API_LuaStructDataPushItem(cardid,1)
		local canadd = API_CanAddItemToBags(lActorID)
		if canadd == true then
			API_RemoveGoods(lActorID,lGoodsID,1)
			API_AddGoods(lActorID,cardid,1)
			API_LuaStructDataSendItemList(lActorID)
		else
			API_SendPacketFull(lActorID, "您的背包已满，无法获得物品")
		end
	end
	API_LuaStructDataClear()
end

function Itemuse_4009(lActorID,lGoodsID,GoodsUid)
	local num = API_GetNumByGoodsID(lActorID,lGoodsID, 0)
	if num == 0 then
		API_SendErrorMsg(lActorID, "你大爷的开挂啊啊啊啊啊")
	else
		local id = math.random(1,6)
		local cardid = 0
		if id == 1 then
			cardid = 10501
		end
		if id == 2 then
			cardid = 20501
		end
		if id == 3 then
			cardid = 30501
		end
		if id == 4 then
			cardid = 40501
		end
		if id == 5 then
			cardid = 10801
		end
		if id == 6 then
			cardid = 40801
		end
		API_LuaStructDataPushItem(cardid,1)
		local canadd = API_CanAddItemToBags(lActorID)
		if canadd == true then
			API_RemoveGoods(lActorID,lGoodsID,1)
			API_AddGoods(lActorID,cardid,1)
			API_LuaStructDataSendItemList(lActorID)
		else
			API_SendPacketFull(lActorID, "您的背包已满，无法获得物品")
		end
	end
	API_LuaStructDataClear()
end
function Itemuse_4010(lActorID,lGoodsID,GoodsUid)
	local num = API_GetNumByGoodsID(lActorID,lGoodsID, 0)
	if num == 0 then
		API_SendErrorMsg(lActorID, "你大爷的开挂啊啊啊啊啊")
	else
		local id = 1012 + math.random(1,6)
		API_LuaStructDataPushItem(id,1)
		local canadd = API_CanAddItemToBags(lActorID)
		if canadd == true then
			API_RemoveGoods(lActorID,lGoodsID,1)
			API_AddGoods(lActorID,id,1)
			API_LuaStructDataSendItemList(lActorID)
		else
			API_SendPacketFull(lActorID, "您的背包已满，无法获得物品")
		end		
	end
	API_LuaStructDataClear()
end

function Itemuse_4011(lActorID,lGoodsID,GoodsUid)
	local num = API_GetNumByGoodsID(lActorID,lGoodsID, 0)
	if num == 0 then
		API_SendErrorMsg(lActorID, "你大爷的开挂啊啊啊啊啊")
	else
		local randoid = math.random(1,5)
		local key = randoid
		local id = 1000 + key*2-1 
		API_LuaStructDataPushItem(id,1)
		local canadd = API_CanAddItemToBags(lActorID)
		if canadd == true then
			API_RemoveGoods(lActorID,lGoodsID,1)
			API_AddGoods(lActorID,id,1)
			API_LuaStructDataSendItemList(lActorID)
		else
			API_SendPacketFull(lActorID, "您的背包已满，无法获得物品")
		end		
	end
	API_LuaStructDataClear()
end

function Itemuse_4012(lActorID,lGoodsID,GoodsUid)
	local num = API_GetNumByGoodsID(lActorID,lGoodsID, 0)
	if num == 0 then
		API_SendErrorMsg(lActorID, "你大爷的开挂啊啊啊啊啊")
	else
		local randoid = math.random(1,5)
		local key = randoid
		local id = 1018 + key*2-1
		API_LuaStructDataPushItem(id,1)
		local canadd = API_CanAddItemToBags(lActorID)
		if canadd == true then
			API_RemoveGoods(lActorID,lGoodsID,1)
			API_AddGoods(lActorID,id,1)
			API_LuaStructDataSendItemList(lActorID)
		else
			API_SendPacketFull(lActorID, "您的背包已满，无法获得物品")
		end		
	end
	API_LuaStructDataClear()
end

function Itemuse_4017(lActorID,lGoodsID,GoodsUid)
	local num = API_GetNumByGoodsID(lActorID,lGoodsID, 0)
	if num == 0 then
		API_SendErrorMsg(lActorID, "你大爷的开挂啊啊啊啊啊")
	else
		local id = lGoodsID - 4016
		local cardid1 = id*10000 + 101
		local cardid2 = id*10000 + 201
		local cardid3 = id*10000 + 301
		local cardid4 = id*10000 + 401
		local cardid5 = id*10000 + 501
		API_LuaStructDataPushItem(cardid1,1)
		API_LuaStructDataPushItem(cardid2,1)
		API_LuaStructDataPushItem(cardid3,1)
		API_LuaStructDataPushItem(cardid4,1)
		API_LuaStructDataPushItem(cardid5,1)
		local canadd = API_CanAddItemToBags(lActorID)
		if canadd == true then
			API_RemoveGoods(lActorID,lGoodsID,1)
			API_AddGoods(lActorID,cardid1,1)
			API_AddGoods(lActorID,cardid2,1)
			API_AddGoods(lActorID,cardid3,1)
			API_AddGoods(lActorID,cardid4,1)
			API_AddGoods(lActorID,cardid5,1)
			API_LuaStructDataSendItemList(lActorID)
		else
			API_SendPacketFull(lActorID, "您的背包已满，无法获得物品")
		end		
	end
	API_LuaStructDataClear()
end
function Itemuse_4013(lActorID,lGoodsID,GoodsUid)
	local num = API_GetNumByGoodsID(lActorID,lGoodsID, 0)
	if num == 0 then
		API_SendErrorMsg(lActorID, "你大爷的开挂啊啊啊啊啊")
	else
		local id = lGoodsID - 4012
		local cardid = id*10000 + 100*math.random(6,8) + 1
		API_LuaStructDataPushItem(cardid,2)
		local canadd = API_CanAddItemToBags(lActorID)
		if canadd == true then
			API_RemoveGoods(lActorID,lGoodsID,1)
			API_AddGoods(lActorID,cardid,2)
			API_LuaStructDataSendItemList(lActorID)
		else
			API_SendPacketFull(lActorID, "您的背包已满，无法获得物品")
		end		
	end
	API_LuaStructDataClear()
end

function Itemuse_4021(lActorID,lGoodsID,GoodsUid)
	list = {}
	local num = API_GetNumByGoodsID(lActorID,lGoodsID, 0)
	if num == 0 then
		API_SendErrorMsg(lActorID, "你大爷的开挂啊啊啊啊啊")
	else
		local itemid = math.random(1,2)	
		local num = math.random(1,20)
		local num1 = 20
		for i = 1,5 do
			if i == 5 then
			   num = num1
			end
			list[i] = num
			if itemid == 1 then
				API_LuaStructDataPushItem(70006+i,num+4)
			else
				API_LuaStructDataPushItem(70012-i,num+4)
			end
			num1 = num1 - num
			if num1 > 1 then
				num = math.random(1,num1)
			else
			   num = num1
			end
		end
		local canadd = API_CanAddItemToBags(lActorID)
		if canadd == true then		
			API_RemoveGoods(lActorID,lGoodsID,1)
		for i = 1,5 do
			if itemid == 1 then
				API_AddGoods(lActorID,70006+i,list[i]+4)
			else
				API_AddGoods(lActorID,70012-i,list[i]+4)
			end
		end
			API_LuaStructDataSendItemList(lActorID)
		else 
			API_SendErrorMsg(lActorID, "您的背包已满，无法获得物品")
		end
	end
	API_LuaStructDataClear()
end
	
function Itemuse_4022(lActorID,lGoodsID,GoodsUid)
	list = {}
	local num = API_GetNumByGoodsID(lActorID,lGoodsID, 0)
	if num == 0 then
		API_SendErrorMsg(lActorID, "你大爷的开挂啊啊啊啊啊")
	else
		local itemid = math.random(1,2)	
		local num = math.random(1,50)
		local num1 = 50
		for i = 1,5 do
			if i == 5 then
			   num = num1
			end
			list[i] = num
			if itemid == 1 then
				API_LuaStructDataPushItem(70006+i,num+10)
			else
				API_LuaStructDataPushItem(70012-i,num+10)
			end
			num1 = num1 - num
			if num1 > 1 then
				num = math.random(1,num1)
			else
			   num = num1
			end
		end
		local canadd = API_CanAddItemToBags(lActorID)
		if canadd == true then		
			API_RemoveGoods(lActorID,lGoodsID,1)
		for i = 1,5 do
			if itemid == 1 then
				API_AddGoods(lActorID,70006+i,list[i]+10)
			else
				API_AddGoods(lActorID,70012-i,list[i]+10)
			end
		end
			API_LuaStructDataSendItemList(lActorID)
		else 
			API_SendErrorMsg(lActorID, "您的背包已满，无法获得物品")
		end
	end
	API_LuaStructDataClear()
end

function Itemuse_4023(lActorID,lGoodsID,GoodsUid)
	list = {}
	local num = API_GetNumByGoodsID(lActorID,lGoodsID, 0)
	if num == 0 then
		API_SendErrorMsg(lActorID, "你大爷的开挂啊啊啊啊啊")
	else
		local itemid = math.random(1,2)	
		local num = math.random(1,150)
		local num1 = 150
		for i = 1,5 do
			if i == 5 then
			   num = num1
			end
			list[i] = num
			if itemid == 1 then
				API_LuaStructDataPushItem(70006+i,num+30)
			else
				API_LuaStructDataPushItem(70012-i,num+30)
			end
			num1 = num1 - num
			if num1 > 1 then
				num = math.random(1,num1)
			else
			   num = num1
			end
		end
		local canadd = API_CanAddItemToBags(lActorID)
		if canadd == true then		
			API_RemoveGoods(lActorID,lGoodsID,1)
		for i = 1,5 do
			if itemid == 1 then
				API_AddGoods(lActorID,70006+i,list[i]+30)
			else
				API_AddGoods(lActorID,70012-i,list[i]+30)
			end
		end
			API_LuaStructDataSendItemList(lActorID)
		else 
			API_SendErrorMsg(lActorID, "您的背包已满，无法获得物品")
		end
	end
	API_LuaStructDataClear()
end
function Itemuse_4024(lActorID,lGoodsID,GoodsUid)
	local num = API_GetNumByGoodsID(lActorID,lGoodsID, 0)
	if num == 0 then
		API_SendErrorMsg(lActorID, "你大爷的开挂啊啊啊啊啊")
	else
		local id = math.random(1,100)
		local cardid = 0
		if id >= 1 and id <= 20 then
			cardid = 70004
		end
		if id >= 21 and id <= 35 then
			cardid = 4010
		end
		if id >= 36 and id <= 50 then
			cardid = 4011
		end
		if id >= 51 and id <= 75 then
			cardid = 70049
		end
		if id >= 76 and id <= 100 then
			cardid = 70050
		end
		API_LuaStructDataPushItem(cardid,1)
		local canadd = API_CanAddItemToBags(lActorID)
		if canadd == true then
			API_RemoveGoods(lActorID,lGoodsID,1)
			API_AddGoods(lActorID,cardid,1)
			API_LuaStructDataSendItemList(lActorID)
		else
			API_SendPacketFull(lActorID, "您的背包已满，无法获得物品")
		end
	end
	API_LuaStructDataClear()
end
function Itemuse_4025(lActorID,lGoodsID,GoodsUid)
	local num = API_GetNumByGoodsID(lActorID,lGoodsID, 0)
	if num == 0 then
		API_SendErrorMsg(lActorID, "你大爷的开挂啊啊啊啊啊")
	else
		local id = math.random(1,100)
		local cardid = 0
		if id >= 1 and id <= 20 then
			cardid = 70036
		end
		if id >= 21 and id <= 35 then
			cardid = 4010
		end
		if id >= 36 and id <= 50 then
			cardid = 4011
		end
		if id >= 51 and id <= 75 then
			cardid = 70049
		end
		if id >= 76 and id <= 100 then
			cardid = 70050
		end
		API_LuaStructDataPushItem(cardid,1)
		local canadd = API_CanAddItemToBags(lActorID)
		if canadd == true then
			API_RemoveGoods(lActorID,lGoodsID,1)
			API_AddGoods(lActorID,cardid,1)
			API_LuaStructDataSendItemList(lActorID)
		else
			API_SendPacketFull(lActorID, "您的背包已满，无法获得物品")
		end
	end
	API_LuaStructDataClear()
end

function Itemuse_4026(lActorID,lGoodsID,GoodsUid)
	local num = API_GetNumByGoodsID(lActorID,lGoodsID, 0)
	if num == 0 then
		API_SendErrorMsg(lActorID, "你大爷的开挂啊啊啊啊啊")
	else
		local id = math.random(1,100)
		local cardid = 0
		if id >= 1 and id <= 20 then
			cardid = 70036
		end
		if id >= 21 and id <= 50 then
			cardid = 70004
		end
		if id >= 51 and id <= 75 then
			cardid = 4010
		end
		if id >= 76 and id <= 100 then
			cardid = 4011
		end
		API_LuaStructDataPushItem(cardid,1)
		local canadd = API_CanAddItemToBags(lActorID)
		if canadd == true then
			API_RemoveGoods(lActorID,lGoodsID,1)
			API_AddGoods(lActorID,cardid,1)
			API_LuaStructDataSendItemList(lActorID)
		else
			API_SendPacketFull(lActorID, "您的背包已满，无法获得物品")
		end
	end
	API_LuaStructDataClear()
end

function Itemuse_4027(lActorID,lGoodsID,GoodsUid)
	local num = API_GetNumByGoodsID(lActorID,lGoodsID, 0)
	if num == 0 then
		API_SendErrorMsg(lActorID, "你大爷的开挂啊啊啊啊啊")
	else
		local id = math.random(1,100)
		local cardid = 0
		if id >= 1 and id <= 3 then
			cardid = 70001
		end
		if id >= 4 and id <= 40 then
			cardid = 70036
		end
		if id >= 41 and id <= 100 then
			cardid = 70004
		end
		API_LuaStructDataPushItem(cardid,1)
		local canadd = API_CanAddItemToBags(lActorID)
		if canadd == true then
			API_RemoveGoods(lActorID,lGoodsID,1)
			API_AddGoods(lActorID,cardid,1)
			API_LuaStructDataSendItemList(lActorID)
		else
			API_SendPacketFull(lActorID, "您的背包已满，无法获得物品")
		end
	end
	API_LuaStructDataClear()
end

function Itemuse_4028(lActorID,lGoodsID,GoodsUid)
	local num = API_GetNumByGoodsID(lActorID,lGoodsID, 0)
	if num == 0 then
		API_SendErrorMsg(lActorID, "你大爷的开挂啊啊啊啊啊")
	else
		local id = math.random(1,100)
		local cardid = 0
		if id >= 1 and id <= 17 then
			cardid = 70015
		end
		if id >= 18 and id <= 37 then
			cardid = 70001
		end
		if id >= 38 and id <= 100 then
			cardid = 70036
		end
		API_LuaStructDataPushItem(cardid,1)
		local canadd = API_CanAddItemToBags(lActorID)
		if canadd == true then
			API_RemoveGoods(lActorID,lGoodsID,1)
			API_AddGoods(lActorID,cardid,1)
			API_LuaStructDataSendItemList(lActorID)
		else
			API_SendPacketFull(lActorID, "您的背包已满，无法获得物品")
		end
	end
	API_LuaStructDataClear()
end
function Itemuse_4029(lActorID,lGoodsID,GoodsUid)
	local num = API_GetNumByGoodsID(lActorID,lGoodsID, 0)
	if num == 0 then
		API_SendErrorMsg(lActorID, "你大爷的开挂啊啊啊啊啊")
	else
		local id = math.random(1,100)
		local cardid = 0
		if id >= 1 and id <= 20 then
			cardid = 70081
		end
		if id >= 21 and id <= 40 then
			cardid = 70082
		end
		if id >= 41 and id <= 60 then
			cardid = 70083
		end
		if id >= 61 and id <= 80 then
			cardid = 70084
		end
		if id >= 81 and id <= 100 then
			cardid = 70085
		end
		API_LuaStructDataPushItem(cardid,1)
		local canadd = API_CanAddItemToBags(lActorID)
		if canadd == true then
			API_RemoveGoods(lActorID,lGoodsID,1)
			API_AddGoods(lActorID,cardid,1)
			API_LuaStructDataSendItemList(lActorID)
		else
			API_SendPacketFull(lActorID, "您的背包已满，无法获得物品")
		end
	end
	API_LuaStructDataClear()
end

function Itemuse_4030(lActorID,lGoodsID,GoodsUid)
	local num = API_GetNumByGoodsID(lActorID,lGoodsID, 0)
	if num == 0 then
		API_SendErrorMsg(lActorID, "你大爷的开挂啊啊啊啊啊")
	else
		local id = math.random(1,100)
		local cardid = 0
		if id >= 1 and id <= 20 then
			cardid = 70086
		end
		if id >= 21 and id <= 40 then
			cardid = 70087
		end
		if id >= 41 and id <= 60 then
			cardid = 70088
		end
		if id >= 61 and id <= 80 then
			cardid = 70089
		end
		if id >= 81 and id <= 100 then
			cardid = 70090
		end
		API_LuaStructDataPushItem(cardid,1)
		local canadd = API_CanAddItemToBags(lActorID)
		if canadd == true then
			API_RemoveGoods(lActorID,lGoodsID,1)
			API_AddGoods(lActorID,cardid,1)
			API_LuaStructDataSendItemList(lActorID)
		else
			API_SendPacketFull(lActorID, "您的背包已满，无法获得物品")
		end
	end
	API_LuaStructDataClear()
end

function Itemuse_4031(lActorID,lGoodsID,GoodsUid)
	local num = API_GetNumByGoodsID(lActorID,lGoodsID, 0)
	if num == 0 then
		API_SendErrorMsg(lActorID, "你大爷的开挂啊啊啊啊啊")
	else
		local id = math.random(1,100)
		local cardid = 0
		if id >= 1 and id <= 20 then
			cardid = 70225
		end
		if id >= 21 and id <= 40 then
			cardid = 70226
		end
		if id >= 41 and id <= 60 then
			cardid = 70227
		end
		if id >= 61 and id <= 80 then
			cardid = 70228
		end
		if id >= 81 and id <= 100 then
			cardid = 70229
		end
		API_LuaStructDataPushItem(cardid,1)
		local canadd = API_CanAddItemToBags(lActorID)
		if canadd == true then
			API_RemoveGoods(lActorID,lGoodsID,1)
			API_AddGoods(lActorID,cardid,1)
			API_LuaStructDataSendItemList(lActorID)
		else
			API_SendPacketFull(lActorID, "您的背包已满，无法获得物品")
		end
	end
	API_LuaStructDataClear()
end

function Itemuse_4999(lActorID,lGoodsID,GoodsUid)
	local num = API_GetNumByGoodsID(lActorID,lGoodsID, 0)
	if num == 0 then
		API_SendErrorMsg(lActorID, "你大爷的开挂啊啊啊啊啊")
	else
		local id = API_GetPlayerHeadID(lActorID)
		local cardid1 = 0
		local cardid2 = 0
		if id == 1 then
			cardid1 = 100101
			cardid2 = 200101
		end
		if id == 2 then
			cardid1 = 100401
			cardid2 = 200301
		end
		if id == 3 then
			cardid1 = 100701
			cardid2 = 200501
		end
		if id == 4 then
			cardid1 = 101001
			cardid2 = 200701
		end
		API_LuaStructDataPushItem(cardid1,1)
		API_LuaStructDataPushItem(cardid2,1)
		local canadd = API_CanAddItemToBags(lActorID)
		if canadd == true then
			API_RemoveGoods(lActorID,lGoodsID,1)
			API_AddGoods(lActorID,cardid1,1)
			API_AddGoods(lActorID,cardid2,1)
			API_LuaStructDataSendItemList(lActorID)
		else
			API_SendPacketFull(lActorID, "您的背包已满，无法获得物品")
		end
	end
	API_LuaStructDataClear()
end



function Itemuse_4998(lActorID,lGoodsID,GoodsUid)
	local num = API_GetNumByGoodsID(lActorID,lGoodsID, 0)
	if num == 0 then
		API_SendErrorMsg(lActorID, "你大爷的开挂啊啊啊啊啊")
	else
		local id = math.random(1,100)
		local cardid = math.random(1,4)*10000 + math.random(1,8)*100 + 1
		API_LuaStructDataPushItem(cardid,2)
		local canadd = API_CanAddItemToBags(lActorID)
		if canadd == true then
			API_RemoveGoods(lActorID,lGoodsID,1)
			API_AddGoods(lActorID,cardid,2)
			API_LuaStructDataSendItemList(lActorID)
		else
			API_SendPacketFull(lActorID, "您的背包已满，无法获得物品")
		end
	end
	API_LuaStructDataClear()
end

function Itemuse_4997(lActorID,lGoodsID,GoodsUid)
	local num = API_GetNumByGoodsID(lActorID,lGoodsID, 0)
	if num == 0 then
		API_SendErrorMsg(lActorID, "你大爷的开挂啊啊啊啊啊")
	else
		local id = math.random(1,100)
		local cardid = math.random(1,4)*10000 + math.random(1,8)*100 + 1
		API_LuaStructDataPushItem(cardid,1)
		local canadd = API_CanAddItemToBags(lActorID)
		if canadd == true then
			API_RemoveGoods(lActorID,lGoodsID,1)
			API_AddGoods(lActorID,cardid,1)
			API_LuaStructDataSendItemList(lActorID)
		else
			API_SendPacketFull(lActorID, "您的背包已满，无法获得物品")
		end
	end
	API_LuaStructDataClear()
end

function Itemuse_100(lActorID,lGoodsID,GoodsUid)
	local num = API_GetNumByGoodsID(lActorID,lGoodsID, 0)
	if num == 0 then
		API_SendErrorMsg(lActorID, "你大爷的开挂啊啊啊啊啊")
	else
		API_AddPlayerGoodsEnergy(lActorID, 20)
	end
end

function Itemuse_2000(lActorID,lGoodsID,GoodsUid)
	local num = API_GetNumByGoodsID(lActorID,lGoodsID, 0)
	if num == 0 then
		API_SendErrorMsg(lActorID, "你大爷的开挂啊啊啊啊啊")
	else
		API_RemoveGoods(lActorID,lGoodsID,1)
		API_AddPlayerRMB(lActorID, 20)
	end
end 

function Itemuse_2001(lActorID,lGoodsID,GoodsUid)
	local num = API_GetNumByGoodsID(lActorID,lGoodsID, 0)
	if num == 0 then
		API_SendErrorMsg(lActorID, "你大爷的开挂啊啊啊啊啊")
	else
		API_RemoveGoods(lActorID,lGoodsID,1)
		API_AddPlayerRMB(lActorID, 1)
	end
end 

function Itemuse_2002(lActorID,lGoodsID,GoodsUid)
	local num = API_GetNumByGoodsID(lActorID,lGoodsID, 0)
	if num == 0 then
		API_SendErrorMsg(lActorID, "你大爷的开挂啊啊啊啊啊")
	else
		API_RemoveGoods(lActorID,lGoodsID,1)
		API_AddPlayerRMB(lActorID, 10)
	end
end 

function Itemuse_2003(lActorID,lGoodsID,GoodsUid)
	local num = API_GetNumByGoodsID(lActorID,lGoodsID, 0)
	if num == 0 then
		API_SendErrorMsg(lActorID, "你大爷的开挂啊啊啊啊啊")
	else
		API_RemoveGoods(lActorID,lGoodsID,1)
		API_AddPlayerRMB(lActorID, 6)
	end
end 

function Itemuse_2004(lActorID,lGoodsID,GoodsUid)
	local num = API_GetNumByGoodsID(lActorID,lGoodsID, 0)
	if num == 0 then
		API_SendErrorMsg(lActorID, "你大爷的开挂啊啊啊啊啊")
	else
		API_RemoveGoods(lActorID,lGoodsID,1)
		API_AddPlayerRMB(lActorID, 2)
	end
end 

function Itemuse_2005(lActorID,lGoodsID,GoodsUid)
	local num = API_GetNumByGoodsID(lActorID,lGoodsID, 0)
	if num == 0 then
		API_SendErrorMsg(lActorID, "你大爷的开挂啊啊啊啊啊")
	else
		API_RemoveGoods(lActorID,lGoodsID,1)
		API_AddPlayerRMB(lActorID, 6)
	end
end 

function Itemuse_2006(lActorID,lGoodsID,GoodsUid)
	local num = API_GetNumByGoodsID(lActorID,lGoodsID, 0)
	if num == 0 then
		API_SendErrorMsg(lActorID, "你大爷的开挂啊啊啊啊啊")
	else
		API_RemoveGoods(lActorID,lGoodsID,1)
		API_AddPlayerRMB(lActorID, 10)
	end
end 

function Itemuse_2007(lActorID,lGoodsID,GoodsUid)
	local num = API_GetNumByGoodsID(lActorID,lGoodsID, 0)
	if num == 0 then
		API_SendErrorMsg(lActorID, "你大爷的开挂啊啊啊啊啊")
	else
		API_RemoveGoods(lActorID,lGoodsID,1)
		API_AddPlayerExp(lActorID, 5000)
		API_AddPlayerMoney(lActorID, 12000)
	end
end 


function Itemuse_5001(lActorID,lGoodsID,GoodsUid)
	local num = API_GetNumByGoodsID(lActorID,lGoodsID, 0)
	if num == 0 then
		API_SendErrorMsg(lActorID, "你大爷的开挂啊啊啊啊啊")
	else
		local cardid1 = 0
		local id1 = math.random(1,100)
		if id1 >= 1 and id1 <= 9	then
			cardid1 = 400101
		end
		if id1 >= 10 and id1 <= 18	then
			cardid1 = 400201
		end
		if id1 >= 19 and id1 <= 27	then
			cardid1 = 400301
		end
		if id1 >= 28 and id1 <= 36	then
			cardid1 = 400401
		end
		if id1 >= 37 and id1 <= 45	then
			cardid1 = 400501
		end
		if id1 >= 46 and id1 <= 54	then
			cardid1 = 500101
		end
		if id1 >= 55 and id1 <= 63	then
			cardid1 = 500201
		end
		if id1 >= 64 and id1 <= 72	then
			cardid1 = 500301
		end
		if id1 >= 73 and id1 <= 81	then
			cardid1 = 500401
		end
		if id1 >= 82 and id1 <= 90	then
			cardid1 = 500501
		end
		if id1 >= 91 and id1 <= 100	then
			cardid1 = 600101
		end
		API_LuaStructDataPushItem(cardid1,1)
		local canadd = API_CanAddItemToBags(lActorID)
			if canadd == true then
				API_RemoveGoods(lActorID,lGoodsID,1)
				API_AddGoods(lActorID,cardid1,1)
				API_LuaStructDataSendItemList(lActorID)
			else
				API_SendPacketFull(lActorID, "您的背包已满，无法获得物品")
			end
		API_LuaStructDataClear()
	end
	API_LuaStructDataClear()
end

function Itemuse_5002(lActorID,lGoodsID,GoodsUid)
	local num = API_GetNumByGoodsID(lActorID,lGoodsID, 0)
	if num == 0 then
		API_SendErrorMsg(lActorID, "你大爷的开挂啊啊啊啊啊")
	else
		local cardid1 = 0
		local id1 = math.random(1,100)
		if id1 >= 1 and id1 <= 9	then
			cardid1 = 400102
		end
		if id1 >= 10 and id1 <= 18	then
			cardid1 = 400202
		end
		if id1 >= 19 and id1 <= 27	then
			cardid1 = 400302
		end
		if id1 >= 28 and id1 <= 36	then
			cardid1 = 400402
		end
		if id1 >= 37 and id1 <= 45	then
			cardid1 = 400502
		end
		if id1 >= 46 and id1 <= 54	then
			cardid1 = 500102
		end
		if id1 >= 55 and id1 <= 63	then
			cardid1 = 500202
		end
		if id1 >= 64 and id1 <= 72	then
			cardid1 = 500302
		end
		if id1 >= 73 and id1 <= 81	then
			cardid1 = 500402
		end
		if id1 >= 82 and id1 <= 90	then
			cardid1 = 500502
		end
		if id1 >= 91 and id1 <= 100	then
			cardid1 = 600102
		end
		API_LuaStructDataPushItem(cardid1,1)
		local canadd = API_CanAddItemToBags(lActorID)
			if canadd == true then
				API_RemoveGoods(lActorID,lGoodsID,1)
				API_AddGoods(lActorID,cardid1,1)
				API_LuaStructDataSendItemList(lActorID)
			else
				API_SendPacketFull(lActorID, "您的背包已满，无法获得物品")
			end
		API_LuaStructDataClear()
	end
	API_LuaStructDataClear()
end

function Itemuse_5003(lActorID,lGoodsID,GoodsUid)
	local num = API_GetNumByGoodsID(lActorID,lGoodsID, 0)
	if num == 0 then
		API_SendErrorMsg(lActorID, "你大爷的开挂啊啊啊啊啊")
	else
		local cardid1 = 0
		local id1 = math.random(1,100)
		if id1 >= 1 and id1 <= 9	then
			cardid1 = 400103
		end
		if id1 >= 10 and id1 <= 18	then
			cardid1 = 400203
		end
		if id1 >= 19 and id1 <= 27	then
			cardid1 = 400303
		end
		if id1 >= 28 and id1 <= 36	then
			cardid1 = 400403
		end
		if id1 >= 37 and id1 <= 45	then
			cardid1 = 400503
		end
		if id1 >= 46 and id1 <= 54	then
			cardid1 = 500103
		end
		if id1 >= 55 and id1 <= 63	then
			cardid1 = 500203
		end
		if id1 >= 64 and id1 <= 72	then
			cardid1 = 500303
		end
		if id1 >= 73 and id1 <= 81	then
			cardid1 = 500403
		end
		if id1 >= 82 and id1 <= 90	then
			cardid1 = 500503
		end
		if id1 >= 91 and id1 <= 100	then
			cardid1 = 600103
		end
		API_LuaStructDataPushItem(cardid1,1)
		local canadd = API_CanAddItemToBags(lActorID)
			if canadd == true then
				API_RemoveGoods(lActorID,lGoodsID,1)
				API_AddGoods(lActorID,cardid1,1)
				API_LuaStructDataSendItemList(lActorID)
			else
				API_SendPacketFull(lActorID, "您的背包已满，无法获得物品")
			end
		API_LuaStructDataClear()
	end
	API_LuaStructDataClear()
end



function Itemuse_5010(lActorID,lGoodsID,GoodsUid)
	local num = API_GetNumByGoodsID(lActorID,lGoodsID, 0)
	if num == 0 then
		API_SendErrorMsg(lActorID, "你大爷的开挂啊啊啊啊啊")
	else
		API_RemoveGoods(lActorID,lGoodsID,1)
		API_AddPlayerGoodsEnergy(lActorID, 1)
	end
end

function Itemuse_5011(lActorID,lGoodsID,GoodsUid)
	local num = API_GetNumByGoodsID(lActorID,lGoodsID, 0)
	if num == 0 then
		API_SendErrorMsg(lActorID, "你大爷的开挂啊啊啊啊啊")
	else
		API_RemoveGoods(lActorID,lGoodsID,1)
		API_AddPlayerGoodsEnergy(lActorID, 3)
	end
end

function Itemuse_5012(lActorID,lGoodsID,GoodsUid)
	local num = API_GetNumByGoodsID(lActorID,lGoodsID, 0)
	if num == 0 then
		API_SendErrorMsg(lActorID, "你大爷的开挂啊啊啊啊啊")
	else
		API_RemoveGoods(lActorID,lGoodsID,1)
		API_AddPlayerGoodsEnergy(lActorID, 10)
	end
end

function Itemuse_5004(lActorID,lGoodsID,GoodsUid)
	local num = API_GetNumByGoodsID(lActorID,lGoodsID, 0)
	if num == 0 then
		API_SendErrorMsg(lActorID, "你大爷的开挂啊啊啊啊啊")
	else
		local cardid1 = 1031
		local cardid2 = 70086
		local cardid3 = 70087
		local cardid4 = 70088
		local cardid5 = 70089
		local cardid6 = 70090
		local cardid7 = 4021
		API_LuaStructDataPushItem(cardid1,10)
		API_LuaStructDataPushItem(cardid2,1)
		API_LuaStructDataPushItem(cardid3,1)
		API_LuaStructDataPushItem(cardid4,1)
		API_LuaStructDataPushItem(cardid5,1)
		API_LuaStructDataPushItem(cardid6,1)
		API_LuaStructDataPushItem(cardid7,5)
		local canadd = API_CanAddItemToBags(lActorID)
			if canadd == true then
				API_RemoveGoods(lActorID,lGoodsID,1)
				API_AddGoods(lActorID,cardid1,10)
				API_AddGoods(lActorID,cardid2,1)
				API_AddGoods(lActorID,cardid3,1)
				API_AddGoods(lActorID,cardid4,1)
				API_AddGoods(lActorID,cardid5,1)
				API_AddGoods(lActorID,cardid6,1)
				API_AddGoods(lActorID,cardid7,5)
				API_LuaStructDataSendItemList(lActorID)
			else
				API_SendPacketFull(lActorID, "您的背包已满，无法获得物品")
			end
		API_LuaStructDataClear()
	end
	API_LuaStructDataClear()
end

function Itemuse_5005(lActorID,lGoodsID,GoodsUid)
	local num = API_GetNumByGoodsID(lActorID,lGoodsID, 0)
	if num == 0 then
		API_SendErrorMsg(lActorID, "你大爷的开挂啊啊啊啊啊")
	else
		local item1 = 0
		local item2 = 0
		local item3 = 0
		local id1 = math.random(1,10)
		if id1 == 1 then
			item1 = 10006
		else
			item1 = 4021
		end
		local id2 = math.random(1,2)
		if id2 == 1 then
			item2 = 70054
		else
			item2 = 4011
		end
		local id3 = math.random(1,5)
		if id3 == 1 then
			item3 = 1031
		else
			item3 = 4012
		end
		local level = API_GetPlayerLevel(lActorID)
		if level > 25 then
			level = 25
		end
		if item1 == 10006 then
			item1 = 10006 + math.floor(level/5) - 1
		end
		API_LuaStructDataPushItem(item1,1)
		API_LuaStructDataPushItem(item2,1)
		API_LuaStructDataPushItem(item3,1)	
		local canadd = API_CanAddItemToBags(lActorID)
		if canadd == true then		
			API_RemoveGoods(lActorID,lGoodsID,1)
			API_AddGoods(lActorID,item1,1)
			API_AddGoods(lActorID,item2,1)
			API_AddGoods(lActorID,item3,1)
			API_LuaStructDataSendItemList(lActorID)
		else 
			API_SendPacketFull(lActorID, "您的背包已满，无法获得物品")
		end
	end
	API_LuaStructDataClear()
end

function Itemuse_5006(lActorID,lGoodsID,GoodsUid)
	local num = API_GetNumByGoodsID(lActorID,lGoodsID, 0)
	if num == 0 then
		API_SendErrorMsg(lActorID, "你大爷的开挂啊啊啊啊啊")
	else
		local cardid1 = 0
		local id1 = math.random(1,100)
		if id1 >= 1 and id1 <= 20	then
			cardid1 = 10011
		end
		if id1 >= 21 and id1 <= 40	then
			cardid1 = 10012
		end
		if id1 >= 41 and id1 <= 60	then
			cardid1 = 10013
		end
		if id1 >= 61 and id1 <= 80	then
			cardid1 = 10014
		end
		if id1 >= 81 and id1 <= 100	then
			cardid1 = 10015
		end
		API_LuaStructDataPushItem(cardid1,1)
		local canadd = API_CanAddItemToBags(lActorID)
			if canadd == true then
				API_RemoveGoods(lActorID,lGoodsID,1)
				API_AddGoods(lActorID,cardid1,1)
				API_LuaStructDataSendItemList(lActorID)
			else
				API_SendPacketFull(lActorID, "您的背包已满，无法获得物品")
			end
		API_LuaStructDataClear()
	end
	API_LuaStructDataClear()
end

function Itemuse_5007(lActorID,lGoodsID,GoodsUid)
	local num = API_GetNumByGoodsID(lActorID,lGoodsID, 0)
	if num == 0 then
		API_SendErrorMsg(lActorID, "你大爷的开挂啊啊啊啊啊")
	else
		local cardid1 = 0
		local id1 = math.random(1,100)
		if id1 >= 1 and id1 <= 33	then
			cardid1 = 10011
		end
		if id1 >= 34 and id1 <= 66	then
			cardid1 = 10012
		end
		if id1 >= 67 and id1 <= 100	then
			cardid1 = 10014
		end
		API_LuaStructDataPushItem(cardid1,1)
		local canadd = API_CanAddItemToBags(lActorID)
			if canadd == true then
				API_RemoveGoods(lActorID,lGoodsID,1)
				API_AddGoods(lActorID,cardid1,1)
				API_LuaStructDataSendItemList(lActorID)
			else
				API_SendPacketFull(lActorID, "您的背包已满，无法获得物品")
			end
		API_LuaStructDataClear()
	end
	API_LuaStructDataClear()
end

function Itemuse_5009(lActorID,lGoodsID,GoodsUid)
	local num = API_GetNumByGoodsID(lActorID,lGoodsID, 0)
	if num == 0 then
		API_SendErrorMsg(lActorID, "你大爷的开挂啊啊啊啊啊")
	else
		local cardid3 = 0
		local cardid4 = 0
		local id1 = math.random(1,100)
		if id1 >= 1 and id1 <= 20	then
			cardid3 = 70076
		end
		if id1 >= 21 and id1 <= 40	then
			cardid3 = 70077
		end
		if id1 >= 41 and id1 <= 60	then
			cardid3 = 70078
		end
		if id1 >= 61 and id1 <= 80	then
			cardid3 = 70079
		end
		if id1 >= 81 and id1 <= 100	then
			cardid3 = 70080
		end
		local id2 = math.random(1,100)
		if id2 >= 1 and id2 <= 20	then
			cardid4 = 70007
		end
		if id2 >= 21 and id2 <= 40	then
			cardid4 = 70008
		end
		if id2 >= 41 and id2 <= 60	then
			cardid4 = 70009
		end
		if id2 >= 61 and id2 <= 80	then
			cardid4 = 70010
		end
		if id2 >= 81 and id2 <= 100	then
			cardid4 = 70011
		end
		API_LuaStructDataPushItem(cardid3,1)
		API_LuaStructDataPushItem(cardid4,1)
		local canadd = API_CanAddItemToBags(lActorID)
			if canadd == true then
				API_RemoveGoods(lActorID,lGoodsID,1)
				API_AddGoods(lActorID,cardid3,1)
				API_AddGoods(lActorID,cardid4,1)
				API_LuaStructDataSendItemList(lActorID)
			else
				API_SendPacketFull(lActorID, "您的背包已满，无法获得物品")
			end
		API_LuaStructDataClear()
	end
	API_LuaStructDataClear()
end

function Itemuse_5013(lActorID,lGoodsID,GoodsUid)
	local num = API_GetNumByGoodsID(lActorID,lGoodsID, 0)
	if num == 0 then
		API_SendErrorMsg(lActorID, "你大爷的开挂啊啊啊啊啊")
	else
		local cardid1 = 2000
				API_LuaStructDataPushItem(cardid1,5)
		local canadd = API_CanAddItemToBags(lActorID)
			if canadd == true then
				API_RemoveGoods(lActorID,lGoodsID,1)
				API_AddGoods(lActorID,cardid1,5)
				API_LuaStructDataSendItemList(lActorID)
			else
				API_SendPacketFull(lActorID, "您的背包已满，无法获得物品")
			end
		API_LuaStructDataClear()
	end
	API_LuaStructDataClear()
end

function Itemuse_5014(lActorID,lGoodsID,GoodsUid)
	local num = API_GetNumByGoodsID(lActorID,lGoodsID, 0)
	if num == 0 then
		API_SendErrorMsg(lActorID, "你大爷的开挂啊啊啊啊啊")
	else
		local cardid1 = 2002
				API_LuaStructDataPushItem(cardid1,5)
		local canadd = API_CanAddItemToBags(lActorID)
			if canadd == true then
				API_RemoveGoods(lActorID,lGoodsID,1)
				API_AddGoods(lActorID,cardid1,5)
				API_LuaStructDataSendItemList(lActorID)
			else
				API_SendPacketFull(lActorID, "您的背包已满，无法获得物品")
			end
		API_LuaStructDataClear()
	end
	API_LuaStructDataClear()
end

function Itemuse_5015(lActorID,lGoodsID,GoodsUid)
	local num = API_GetNumByGoodsID(lActorID,lGoodsID, 0)
	if num == 0 then
		API_SendErrorMsg(lActorID, "你大爷的开挂啊啊啊啊啊")
	else
		local cardid1 = 2002
				API_LuaStructDataPushItem(cardid1,1)
		local canadd = API_CanAddItemToBags(lActorID)
			if canadd == true then
				API_RemoveGoods(lActorID,lGoodsID,1)
				API_AddGoods(lActorID,cardid1,1)
				API_LuaStructDataSendItemList(lActorID)
			else
				API_SendPacketFull(lActorID, "您的背包已满，无法获得物品")
			end
		API_LuaStructDataClear()
	end
	API_LuaStructDataClear()
end



function Itemuse_5016(lActorID,lGoodsID,GoodsUid)
	local num = API_GetNumByGoodsID(lActorID,lGoodsID, 0)
	if num == 0 then
		API_SendErrorMsg(lActorID, "你大爷的开挂啊啊啊啊啊")
	else
		local cardid1 = 2001
				API_LuaStructDataPushItem(cardid1,5)
		local canadd = API_CanAddItemToBags(lActorID)
			if canadd == true then
				API_RemoveGoods(lActorID,lGoodsID,1)
				API_AddGoods(lActorID,cardid1,5)
				API_LuaStructDataSendItemList(lActorID)
			else
				API_SendPacketFull(lActorID, "您的背包已满，无法获得物品")
			end
		API_LuaStructDataClear()
	end
	API_LuaStructDataClear()
end

function Itemuse_5017(lActorID,lGoodsID,GoodsUid)
	local num = API_GetNumByGoodsID(lActorID,lGoodsID, 0)
	if num == 0 then
		API_SendErrorMsg(lActorID, "你大爷的开挂啊啊啊啊啊")
	else
			API_RemoveGoods(lActorID,lGoodsID,1)
			API_AddPlayerMoney(lActorID, 88888)
	end
end



function Itemuse_5018(lActorID,lGoodsID,GoodsUid)
	local num = API_GetNumByGoodsID(lActorID,lGoodsID, 0)
	if num == 0 then
		API_SendErrorMsg(lActorID, "你大爷的开挂啊啊啊啊啊")
	else
		local cardid1 = 0
		local id1 = math.random(1,100)
		if id1 >= 1 and id1 <= 10	then
			cardid1 = 70007
		end
		if id1 >= 11 and id1 <= 20	then
			cardid1 = 70008
		end
		if id1 >= 21 and id1 <= 30	then
			cardid1 = 70009
		end
		if id1 >= 31 and id1 <= 40	then
			cardid1 = 70010
		end
		if id1 >= 41 and id1 <= 50	then
			cardid1 = 70011
		end
		if id1 >= 51 and id1 <= 60	then
			cardid1 = 12101
		end
		if id1 >= 61 and id1 <= 70	then
			cardid1 = 32101
		end
		if id1 >= 71 and id1 <= 80	then
			cardid1 = 32101
		end
		if id1 >= 81 and id1 <= 90	then
			cardid1 = 42101
		end
		if id1 >= 91 and id1 <= 100	then
			cardid1 = 52101
		end
				API_LuaStructDataPushItem(cardid1,1)
		local canadd = API_CanAddItemToBags(lActorID)
			if canadd == true then
				API_RemoveGoods(lActorID,lGoodsID,1)
				API_AddGoods(lActorID,cardid1,1)
				API_LuaStructDataSendItemList(lActorID)
			else
				API_SendPacketFull(lActorID, "您的背包已满，无法获得物品")
			end
		API_LuaStructDataClear()
	end
	API_LuaStructDataClear()
end
function Itemuse_5019(lActorID,lGoodsID,GoodsUid)
	local num = API_GetNumByGoodsID(lActorID,lGoodsID, 0)
	local lv =  API_GetPlayerLevel(lActorID)
	if num == 0 then
		API_SendErrorMsg(lActorID, "你大爷的开挂啊啊啊啊啊")
	end
	if lv < 5 then
		API_SendErrorMsg(lActorID, "角色需要达到5级时才能打开")
	else
		local cardid1 = 70076
		local cardid2 = 70077
		local cardid3 = 70078
		local cardid4 = 70079
		local cardid5 = 70080
		local cardid6 = 5020
		API_LuaStructDataPushItem(cardid1,1)
		API_LuaStructDataPushItem(cardid2,1)
		API_LuaStructDataPushItem(cardid3,1)
		API_LuaStructDataPushItem(cardid4,1)
		API_LuaStructDataPushItem(cardid5,1)
		API_LuaStructDataPushItem(cardid6,1)
		local canadd = API_CanAddItemToBags(lActorID)
			if canadd == true then
				API_RemoveGoods(lActorID,lGoodsID,1)
				API_AddGoods(lActorID,cardid1,1)
				API_AddGoods(lActorID,cardid2,1)
				API_AddGoods(lActorID,cardid3,1)
				API_AddGoods(lActorID,cardid4,1)
				API_AddGoods(lActorID,cardid5,1)
				API_AddGoods(lActorID,cardid6,1)
				API_LuaStructDataSendItemList(lActorID)
			else
				API_SendPacketFull(lActorID, "您的背包已满，无法获得物品")
			end
		API_LuaStructDataClear()
	end
	API_LuaStructDataClear()
end

function Itemuse_5020(lActorID,lGoodsID,GoodsUid)
	local num = API_GetNumByGoodsID(lActorID,lGoodsID, 0)
	local lv =  API_GetPlayerLevel(lActorID)
	if num == 0 then
		API_SendErrorMsg(lActorID, "你大爷的开挂啊啊啊啊啊")
	end
	if lv < 10 then
		API_SendErrorMsg(lActorID, "角色需要达到10级时才能打开")
	else
		local cardid1 = 70076
		local cardid2 = 70077
		local cardid3 = 70078
		local cardid4 = 70079
		local cardid5 = 70080
		local cardid6 = 5021
		API_LuaStructDataPushItem(cardid1,2)
		API_LuaStructDataPushItem(cardid2,2)
		API_LuaStructDataPushItem(cardid3,2)
		API_LuaStructDataPushItem(cardid4,2)
		API_LuaStructDataPushItem(cardid5,2)
		API_LuaStructDataPushItem(cardid6,1)
		local canadd = API_CanAddItemToBags(lActorID)
			if canadd == true then
				API_RemoveGoods(lActorID,lGoodsID,1)
				API_AddGoods(lActorID,cardid1,2)
				API_AddGoods(lActorID,cardid2,2)
				API_AddGoods(lActorID,cardid3,2)
				API_AddGoods(lActorID,cardid4,2)
				API_AddGoods(lActorID,cardid5,2)
				API_AddGoods(lActorID,cardid6,1)
				API_LuaStructDataSendItemList(lActorID)
			else
				API_SendPacketFull(lActorID, "您的背包已满，无法获得物品")
			end
		API_LuaStructDataClear()
	end
	API_LuaStructDataClear()
end

function Itemuse_5021(lActorID,lGoodsID,GoodsUid)
	local num = API_GetNumByGoodsID(lActorID,lGoodsID, 0)
	local lv =  API_GetPlayerLevel(lActorID)
	if num == 0 then
		API_SendErrorMsg(lActorID, "你大爷的开挂啊啊啊啊啊")
	end
	if lv < 15 then
		API_SendErrorMsg(lActorID, "角色需要达到15级时才能打开")
	else
		local cardid1 = 70076
		local cardid2 = 70077
		local cardid3 = 70078
		local cardid4 = 70079
		local cardid5 = 70080
		local cardid6 = 5022
		API_LuaStructDataPushItem(cardid1,3)
		API_LuaStructDataPushItem(cardid2,3)
		API_LuaStructDataPushItem(cardid3,3)
		API_LuaStructDataPushItem(cardid4,3)
		API_LuaStructDataPushItem(cardid5,3)
		API_LuaStructDataPushItem(cardid6,1)
		local canadd = API_CanAddItemToBags(lActorID)
			if canadd == true then
				API_RemoveGoods(lActorID,lGoodsID,1)
				API_AddGoods(lActorID,cardid1,3)
				API_AddGoods(lActorID,cardid2,3)
				API_AddGoods(lActorID,cardid3,3)
				API_AddGoods(lActorID,cardid4,3)
				API_AddGoods(lActorID,cardid5,3)
				API_AddGoods(lActorID,cardid6,1)
				API_LuaStructDataSendItemList(lActorID)
			else
				API_SendPacketFull(lActorID, "您的背包已满，无法获得物品")
			end
		API_LuaStructDataClear()
	end
	API_LuaStructDataClear()
end

function Itemuse_5022(lActorID,lGoodsID,GoodsUid)
	local num = API_GetNumByGoodsID(lActorID,lGoodsID, 0)
	local lv =  API_GetPlayerLevel(lActorID)
	if num == 0 then
		API_SendErrorMsg(lActorID, "你大爷的开挂啊啊啊啊啊")
	end
	if lv < 20 then
		API_SendErrorMsg(lActorID, "角色需要达到20级时才能打开")
	else
		local cardid1 = 70081
		local cardid2 = 70082
		local cardid3 = 70083
		local cardid4 = 70084
		local cardid5 = 70085
		API_LuaStructDataPushItem(cardid1,2)
		API_LuaStructDataPushItem(cardid2,2)
		API_LuaStructDataPushItem(cardid3,2)
		API_LuaStructDataPushItem(cardid4,2)
		API_LuaStructDataPushItem(cardid5,2)
		local canadd = API_CanAddItemToBags(lActorID)
			if canadd == true then
				API_RemoveGoods(lActorID,lGoodsID,1)
				API_AddGoods(lActorID,cardid1,2)
				API_AddGoods(lActorID,cardid2,2)
				API_AddGoods(lActorID,cardid3,2)
				API_AddGoods(lActorID,cardid4,2)
				API_AddGoods(lActorID,cardid5,2)
				API_LuaStructDataSendItemList(lActorID)
			else
				API_SendPacketFull(lActorID, "您的背包已满，无法获得物品")
			end
		API_LuaStructDataClear()
	end
	API_LuaStructDataClear()
end

function Itemuse_5023(lActorID,lGoodsID,GoodsUid)
	local num = API_GetNumByGoodsID(lActorID,lGoodsID, 0)
	if num == 0 then
		API_SendErrorMsg(lActorID, "你大爷的开挂啊啊啊啊啊")
	else
		API_RemoveGoods(lActorID,lGoodsID,1)
		API_AddPlayerMoney(lActorID, 100)
	end
end 

function Itemuse_5024(lActorID,lGoodsID,GoodsUid)
	local num = API_GetNumByGoodsID(lActorID,lGoodsID, 0)
	if num == 0 then
		API_SendErrorMsg(lActorID, "你大爷的开挂啊啊啊啊啊")
	else
		API_RemoveGoods(lActorID,lGoodsID,1)
		API_AddPlayerRMB(lActorID, 200)
	end
end 


function Itemuse_5025(lActorID,lGoodsID,GoodsUid)
	local num = API_GetNumByGoodsID(lActorID,lGoodsID, 0)
	if num == 0 then
		API_SendErrorMsg(lActorID, "你大爷的开挂啊啊啊啊啊")
	else
		local id1 = 0
		local id2 = 0
		local id3 = 0
		local id4 = 0
		local id5 = 0
		local lv =  API_GetPlayerLevel(lActorID)
		local num = 0
		local cardid1 = 70076
		local cardid2 = 70077
		local cardid3 = 70078
		local cardid4 = 70079
		local cardid5 = 70080
		if lv >=1 and lv <= 4 then
			num = 1
		end
		if lv >=5 and lv <= 9 then
			num = 2
		end
		if lv >=10 and lv <= 14 then
			num = 3
		end
		if lv >=15  then
			num = 4
		end		
			id1 = 12100+num
			id2 = 22100+num
			id3 = 32100+num
			id4 = 42100+num
			id5 = 52100+num
		API_LuaStructDataPushItem(id1,1)
		API_LuaStructDataPushItem(id2,1)
		API_LuaStructDataPushItem(id3,1)
		API_LuaStructDataPushItem(id4,1)
		API_LuaStructDataPushItem(id5,1)	
		API_LuaStructDataPushItem(cardid1,1)
		API_LuaStructDataPushItem(cardid2,1)
		API_LuaStructDataPushItem(cardid3,1)
		API_LuaStructDataPushItem(cardid4,1)
		API_LuaStructDataPushItem(cardid5,1)
		local canadd = API_CanAddItemToBags(lActorID)
			if canadd == true then
				API_RemoveGoods(lActorID,lGoodsID,1)
				API_AddGoods(lActorID,id1,1)
				API_AddGoods(lActorID,id2,1)
				API_AddGoods(lActorID,id3,1)
				API_AddGoods(lActorID,id4,1)
				API_AddGoods(lActorID,id5,1)
				API_AddGoods(lActorID,cardid1,1)
				API_AddGoods(lActorID,cardid2,1)
				API_AddGoods(lActorID,cardid3,1)
				API_AddGoods(lActorID,cardid4,1)
				API_AddGoods(lActorID,cardid5,1)
				API_LuaStructDataSendItemList(lActorID)
			else
				API_SendPacketFull(lActorID, "您的背包已满，无法获得物品")
			end
		API_LuaStructDataClear()
	end
	API_LuaStructDataClear()
end

function Itemuse_5026(lActorID,lGoodsID,GoodsUid)
	local num = API_GetNumByGoodsID(lActorID,lGoodsID, 0)
	if num == 0 then
		API_SendErrorMsg(lActorID, "你大爷的开挂啊啊啊啊啊")
	else
		local cardid1 = 70081
		local cardid2 = 70082
		local cardid3 = 70083
		local cardid4 = 70084
		local cardid5 = 70085
			API_LuaStructDataPushItem(cardid1,1)
		API_LuaStructDataPushItem(cardid2,1)
		API_LuaStructDataPushItem(cardid3,1)
		API_LuaStructDataPushItem(cardid4,1)
		API_LuaStructDataPushItem(cardid5,1)
			local canadd = API_CanAddItemToBags(lActorID)
			if canadd == true then
				API_RemoveGoods(lActorID,lGoodsID,1)
				API_AddGoods(lActorID,cardid1,1)
				API_AddGoods(lActorID,cardid2,1)
				API_AddGoods(lActorID,cardid3,1)
				API_AddGoods(lActorID,cardid4,1)
				API_AddGoods(lActorID,cardid5,1)
				API_LuaStructDataSendItemList(lActorID)
			else
				API_SendPacketFull(lActorID, "您的背包已满，无法获得物品")
			end
		API_LuaStructDataClear()
	end
	API_LuaStructDataClear()
end
function Itemuse_5027(lActorID,lGoodsID,GoodsUid)
	local num = API_GetNumByGoodsID(lActorID,lGoodsID, 0)
	if num == 0 then
		API_SendErrorMsg(lActorID, "你大爷的开挂啊啊啊啊啊")
	else
		local cardid1 = 0
		local id1 = math.random(1,100)
		if id1 >=1 and id1 <= 8 then
			cardid1 = 14101
		end
		if id1 >=9 and id1 <= 16 then
			cardid1 = 24101
		end
		if id1 >=17 and id1 <= 24 then
			cardid1 = 34101
		end
		if id1 >=25 and id1 <= 32 then
			cardid1 = 44101
		end
		if id1 >=33 and id1 <= 40 then
			cardid1 = 54101
		end
		if id1 >=41 and id1 <= 48 then
			cardid1 = 14201
		end
		if id1 >=49 and id1 <= 56 then
			cardid1 = 34201
		end
		if id1 >=57 and id1 <= 64 then
			cardid1 = 44201
		end
		if id1 >=65 and id1 <= 72 then
			cardid1 = 54201
		end
		if id1 >=73 and id1 <= 79 then
			cardid1 = 14301
		end
		if id1 >=80 and id1 <= 86 then
			cardid1 = 34301
		end
		if id1 >=87 and id1 <= 93 then
			cardid1 = 54301
		end
		if id1 >=94 and id1 <= 100 then
			cardid1 = 14401
		end
		API_LuaStructDataPushItem(cardid1,1)
		local canadd = API_CanAddItemToBags(lActorID)
			if canadd == true then
				API_RemoveGoods(lActorID,lGoodsID,1)
				API_AddGoods(lActorID,cardid1,1)
				API_LuaStructDataSendItemList(lActorID)
			else
				API_SendPacketFull(lActorID, "您的背包已满，无法获得物品")
			end
		API_LuaStructDataClear()
	end
	API_LuaStructDataClear()
end

function Itemuse_5028(lActorID,lGoodsID,GoodsUid)
	local num = API_GetNumByGoodsID(lActorID,lGoodsID, 0)
	if num == 0 then
		API_SendErrorMsg(lActorID, "你大爷的开挂啊啊啊啊啊")
	else
		API_RemoveGoods(lActorID,lGoodsID,1)
		API_AddPlayerMoney(lActorID, 2000)
		API_AddPlayerExp(lActorID, 1500)
	end
end 

function Itemuse_5029(lActorID,lGoodsID,GoodsUid)
	local num = API_GetNumByGoodsID(lActorID,lGoodsID, 0)
	if num == 0 then
		API_SendErrorMsg(lActorID, "你大爷的开挂啊啊啊啊啊")
	else
		API_RemoveGoods(lActorID,lGoodsID,1)
		API_AddPlayerMoney(lActorID, 1000)
		API_AddPlayerExp(lActorID, 1500)
	end
end 



function Itemuse_5030(lActorID,lGoodsID,GoodsUid)
	local num = API_GetNumByGoodsID(lActorID,lGoodsID, 0)
	if num == 0 then
		API_SendErrorMsg(lActorID, "你大爷的开挂啊啊啊啊啊")
	else
		API_RemoveGoods(lActorID,lGoodsID,1)
		API_AddPlayerMoney(lActorID, 5620)
	end
end 

function Itemuse_5031(lActorID,lGoodsID,GoodsUid)
	local num = API_GetNumByGoodsID(lActorID,lGoodsID, 0)
	if num == 0 then
		API_SendErrorMsg(lActorID, "你大爷的开挂啊啊啊啊啊")
	else
		local cardid1 = 53301
			  cardid2 = 300101
				API_LuaStructDataPushItem(cardid1,1)
				API_LuaStructDataPushItem(cardid2,1)
		local canadd = API_CanAddItemToBags(lActorID)
			if canadd == true then
				API_RemoveGoods(lActorID,lGoodsID,1)
				API_AddGoods(lActorID,cardid1,1)
				API_AddGoods(lActorID,cardid2,1)
				API_AddPlayerMoney(lActorID, 11240)
				API_LuaStructDataSendItemList(lActorID)
			else
				API_SendPacketFull(lActorID, "您的背包已满，无法获得物品")
			end
		API_LuaStructDataClear()
	end
	API_LuaStructDataClear()
end

function Itemuse_5032(lActorID,lGoodsID,GoodsUid)
	local num = API_GetNumByGoodsID(lActorID,lGoodsID, 0)
	if num == 0 then
		API_SendErrorMsg(lActorID, "你大爷的开挂啊啊啊啊啊")
	else
		local cardid1 = 33201
			  cardid2 = 400101
				API_LuaStructDataPushItem(cardid1,1)
				API_LuaStructDataPushItem(cardid2,1)
			local canadd = API_CanAddItemToBags(lActorID)
			if canadd == true then
				API_RemoveGoods(lActorID,lGoodsID,1)
				API_AddGoods(lActorID,cardid1,1)
				API_AddGoods(lActorID,cardid2,1)
				API_AddPlayerMoney(lActorID, 16860)
				API_LuaStructDataSendItemList(lActorID)
			else
				API_SendPacketFull(lActorID, "您的背包已满，无法获得物品")
			end
		API_LuaStructDataClear()
	end
	API_LuaStructDataClear()
end

function Itemuse_5033(lActorID,lGoodsID,GoodsUid)
	local num = API_GetNumByGoodsID(lActorID,lGoodsID, 0)
	if num == 0 then
		API_SendErrorMsg(lActorID, "你大爷的开挂啊啊啊啊啊")
	else
		local cardid1 = 14201
				API_LuaStructDataPushItem(cardid1,1)
		local canadd = API_CanAddItemToBags(lActorID)
			if canadd == true then
				API_RemoveGoods(lActorID,lGoodsID,1)
				API_AddGoods(lActorID,cardid1,1)
				API_AddPlayerMoney(lActorID, 22480)
				API_LuaStructDataSendItemList(lActorID)
			else
				API_SendPacketFull(lActorID, "您的背包已满，无法获得物品")
			end
		API_LuaStructDataClear()
	end
	API_LuaStructDataClear()
end


function Itemuse_5034(lActorID,lGoodsID,GoodsUid)
	local num = API_GetNumByGoodsID(lActorID,lGoodsID, 0)
	if num == 0 then
		API_SendErrorMsg(lActorID, "你大爷的开挂啊啊啊啊啊")
	else
		local cardid1 = 70216
			API_LuaStructDataPushItem(cardid1,1)
		local canadd = API_CanAddItemToBags(lActorID)
			if canadd == true then
				API_RemoveGoods(lActorID,lGoodsID,1)
				API_AddGoods(lActorID,cardid1,1)
				API_LuaStructDataSendItemList(lActorID)
			else
				API_SendPacketFull(lActorID, "您的背包已满，无法获得物品")
			end
		API_LuaStructDataClear()
	end
	API_LuaStructDataClear()
end

function Itemuse_5035(lActorID,lGoodsID,GoodsUid)
	local num = API_GetNumByGoodsID(lActorID,lGoodsID, 0)
	if num == 0 then
		API_SendErrorMsg(lActorID, "你大爷的开挂啊啊啊啊啊")
	else
		local cardid1 = 70216
			API_LuaStructDataPushItem(cardid1,1)
		local canadd = API_CanAddItemToBags(lActorID)
			if canadd == true then
				API_RemoveGoods(lActorID,lGoodsID,1)
				API_AddGoods(lActorID,cardid1,1)
				API_LuaStructDataSendItemList(lActorID)
			else
				API_SendPacketFull(lActorID, "您的背包已满，无法获得物品")
			end
		API_LuaStructDataClear()
	end
	API_LuaStructDataClear()
end

function Itemuse_5036(lActorID,lGoodsID,GoodsUid)
	local num = API_GetNumByGoodsID(lActorID,lGoodsID, 0)
	if num == 0 then
		API_SendErrorMsg(lActorID, "你大爷的开挂啊啊啊啊啊")
	else
		local cardid1 = 70216
			  cardid2 = 70219
			API_LuaStructDataPushItem(cardid1,1)
			API_LuaStructDataPushItem(cardid2,1)
		local canadd = API_CanAddItemToBags(lActorID)
			if canadd == true then
				API_RemoveGoods(lActorID,lGoodsID,1)
				API_AddGoods(lActorID,cardid1,1)
				API_AddGoods(lActorID,cardid2,1)
				API_LuaStructDataSendItemList(lActorID)
			else
				API_SendPacketFull(lActorID, "您的背包已满，无法获得物品")
			end
		API_LuaStructDataClear()
	end
	API_LuaStructDataClear()
end

function Itemuse_5037(lActorID,lGoodsID,GoodsUid)
	local num = API_GetNumByGoodsID(lActorID,lGoodsID, 0)
	if num == 0 then
		API_SendErrorMsg(lActorID, "你大爷的开挂啊啊啊啊啊")
	else
		local cardid1 = 70216
			  cardid2 = 70219
			  cardid3 = 70222
			API_LuaStructDataPushItem(cardid1,1)
			API_LuaStructDataPushItem(cardid2,1)
			API_LuaStructDataPushItem(cardid3,1)
		local canadd = API_CanAddItemToBags(lActorID)
			if canadd == true then
				API_RemoveGoods(lActorID,lGoodsID,1)
				API_AddGoods(lActorID,cardid1,1)
				API_AddGoods(lActorID,cardid2,1)
				API_AddGoods(lActorID,cardid3,1)
				API_LuaStructDataSendItemList(lActorID)
			else
				API_SendPacketFull(lActorID, "您的背包已满，无法获得物品")
			end
		API_LuaStructDataClear()
	end
	API_LuaStructDataClear()
end

function Itemuse_5038(lActorID,lGoodsID,GoodsUid)
	local num = API_GetNumByGoodsID(lActorID,lGoodsID, 0)
	if num == 0 then
		API_SendErrorMsg(lActorID, "你大爷的开挂啊啊啊啊啊")
	else
		local cardid1 = 70216
			  cardid2 = 70219
			  cardid3 = 70222
			API_LuaStructDataPushItem(cardid1,2)
			API_LuaStructDataPushItem(cardid2,2)
			API_LuaStructDataPushItem(cardid3,2)
		local canadd = API_CanAddItemToBags(lActorID)
			if canadd == true then
				API_RemoveGoods(lActorID,lGoodsID,1)
				API_AddGoods(lActorID,cardid1,2)
				API_AddGoods(lActorID,cardid2,2)
				API_AddGoods(lActorID,cardid3,2)
				API_LuaStructDataSendItemList(lActorID)
			else
				API_SendPacketFull(lActorID, "您的背包已满，无法获得物品")
			end
		API_LuaStructDataClear()
	end
	API_LuaStructDataClear()
end

function Itemuse_5039(lActorID,lGoodsID,GoodsUid)
	local num = API_GetNumByGoodsID(lActorID,lGoodsID, 0)
	if num == 0 then
		API_SendErrorMsg(lActorID, "你大爷的开挂啊啊啊啊啊")
	else
		local cardid1 = 70217
			API_LuaStructDataPushItem(cardid1,1)
		local canadd = API_CanAddItemToBags(lActorID)
			if canadd == true then
				API_RemoveGoods(lActorID,lGoodsID,1)
				API_AddGoods(lActorID,cardid1,1)
				API_LuaStructDataSendItemList(lActorID)
			else
				API_SendPacketFull(lActorID, "您的背包已满，无法获得物品")
			end
		API_LuaStructDataClear()
	end
	API_LuaStructDataClear()
end

function Itemuse_5040(lActorID,lGoodsID,GoodsUid)
	local num = API_GetNumByGoodsID(lActorID,lGoodsID, 0)
	if num == 0 then
		API_SendErrorMsg(lActorID, "你大爷的开挂啊啊啊啊啊")
	else
		local cardid1 = 70217
			  cardid2 = 70220
			API_LuaStructDataPushItem(cardid1,1)
			API_LuaStructDataPushItem(cardid2,1)
		local canadd = API_CanAddItemToBags(lActorID)
			if canadd == true then
				API_RemoveGoods(lActorID,lGoodsID,1)
				API_AddGoods(lActorID,cardid1,1)
				API_AddGoods(lActorID,cardid2,1)
				API_LuaStructDataSendItemList(lActorID)
			else
				API_SendPacketFull(lActorID, "您的背包已满，无法获得物品")
			end
		API_LuaStructDataClear()
	end
	API_LuaStructDataClear()
end

function Itemuse_5041(lActorID,lGoodsID,GoodsUid)
	local num = API_GetNumByGoodsID(lActorID,lGoodsID, 0)
	if num == 0 then
		API_SendErrorMsg(lActorID, "你大爷的开挂啊啊啊啊啊")
	else
		local cardid1 = 70217
			  cardid2 = 70220
			  cardid3 = 70223
			API_LuaStructDataPushItem(cardid1,1)
			API_LuaStructDataPushItem(cardid2,1)
			API_LuaStructDataPushItem(cardid3,1)
		local canadd = API_CanAddItemToBags(lActorID)
			if canadd == true then
				API_RemoveGoods(lActorID,lGoodsID,1)
				API_AddGoods(lActorID,cardid1,1)
				API_AddGoods(lActorID,cardid2,1)
				API_AddGoods(lActorID,cardid3,1)
				API_LuaStructDataSendItemList(lActorID)
			else
				API_SendPacketFull(lActorID, "您的背包已满，无法获得物品")
			end
		API_LuaStructDataClear()
	end
	API_LuaStructDataClear()
end

function Itemuse_5042(lActorID,lGoodsID,GoodsUid)
	local num = API_GetNumByGoodsID(lActorID,lGoodsID, 0)
	if num == 0 then
		API_SendErrorMsg(lActorID, "你大爷的开挂啊啊啊啊啊")
	else
		local cardid1 = 4030
			API_LuaStructDataPushItem(cardid1,1)
		local canadd = API_CanAddItemToBags(lActorID)
			if canadd == true then
				API_RemoveGoods(lActorID,lGoodsID,1)
				API_AddGoods(lActorID,cardid1,1)
				API_LuaStructDataSendItemList(lActorID)
			else
				API_SendPacketFull(lActorID, "您的背包已满，无法获得物品")
			end
		API_LuaStructDataClear()
	end
	API_LuaStructDataClear()
end

function Itemuse_5043(lActorID,lGoodsID,GoodsUid)
	local num = API_GetNumByGoodsID(lActorID,lGoodsID, 0)
	if num == 0 then
		API_SendErrorMsg(lActorID, "你大爷的开挂啊啊啊啊啊")
	else
		API_RemoveGoods(lActorID,lGoodsID,1)
		API_AddPlayerMoney(lActorID, 400)
	end
end 


function Itemuse_5044(lActorID,lGoodsID,GoodsUid)
	local num = API_GetNumByGoodsID(lActorID,lGoodsID, 0)
	if num == 0 then
		API_SendErrorMsg(lActorID, "你大爷的开挂啊啊啊啊啊")
	else
		local cardid1 = 70209
			API_LuaStructDataPushItem(cardid1,2)
		local canadd = API_CanAddItemToBags(lActorID)
			if canadd == true then
				API_RemoveGoods(lActorID,lGoodsID,1)
				API_AddGoods(lActorID,cardid1,2)
				API_AddPlayerMoney(lActorID, 5000)
				API_LuaStructDataSendItemList(lActorID)
			else
				API_SendPacketFull(lActorID, "您的背包已满，无法获得物品")
			end
		API_LuaStructDataClear()
	end
	API_LuaStructDataClear()
end


function Itemuse_5045(lActorID,lGoodsID,GoodsUid)
	local num = API_GetNumByGoodsID(lActorID,lGoodsID, 0)
	if num == 0 then
		API_SendErrorMsg(lActorID, "你大爷的开挂啊啊啊啊啊")
	else
		local cardid1 = 70241
			  cardid2 = 70242
			  cardid3 = 70243
			  cardid4 = 70244
			  cardid5 = 70245
				API_LuaStructDataPushItem(cardid1,1)
				API_LuaStructDataPushItem(cardid2,1)
				API_LuaStructDataPushItem(cardid3,1)
				API_LuaStructDataPushItem(cardid4,1)
				API_LuaStructDataPushItem(cardid5,1)
		local canadd = API_CanAddItemToBags(lActorID)
			if canadd == true then
				API_RemoveGoods(lActorID,lGoodsID,1)
				API_AddGoods(lActorID,cardid1,1)
				API_AddGoods(lActorID,cardid2,1)
				API_AddGoods(lActorID,cardid3,1)
				API_AddGoods(lActorID,cardid4,1)
				API_AddGoods(lActorID,cardid5,1)
				API_AddPlayerMoney(lActorID, 5000)
				API_LuaStructDataSendItemList(lActorID)
			else
				API_SendPacketFull(lActorID, "您的背包已满，无法获得物品")
			end
		API_LuaStructDataClear()
	end
	API_LuaStructDataClear()
end

function Itemuse_5046(lActorID,lGoodsID,GoodsUid)
	local num = API_GetNumByGoodsID(lActorID,lGoodsID, 0)
	if num == 0 then
		API_SendErrorMsg(lActorID, "你大爷的开挂啊啊啊啊啊")
	else
		local cardid1 = 70212
			API_LuaStructDataPushItem(cardid1,2)
		local canadd = API_CanAddItemToBags(lActorID)
			if canadd == true then
				API_RemoveGoods(lActorID,lGoodsID,1)
				API_AddGoods(lActorID,cardid1,2)
				API_AddPlayerMoney(lActorID, 5000)
				API_LuaStructDataSendItemList(lActorID)
			else
				API_SendPacketFull(lActorID, "您的背包已满，无法获得物品")
			end
		API_LuaStructDataClear()
	end
	API_LuaStructDataClear()
end

function Itemuse_5047(lActorID,lGoodsID,GoodsUid)
	local num = API_GetNumByGoodsID(lActorID,lGoodsID, 0)
	if num == 0 then
		API_SendErrorMsg(lActorID, "你大爷的开挂啊啊啊啊啊")
	else
		local cardid1 = 70241
			  cardid2 = 70242
			  cardid3 = 70243
			  cardid4 = 70244
			  cardid5 = 70245
				API_LuaStructDataPushItem(cardid1,1)
				API_LuaStructDataPushItem(cardid2,1)
				API_LuaStructDataPushItem(cardid3,1)
				API_LuaStructDataPushItem(cardid4,1)
				API_LuaStructDataPushItem(cardid5,1)
		local canadd = API_CanAddItemToBags(lActorID)
			if canadd == true then
				API_RemoveGoods(lActorID,lGoodsID,1)
				API_AddGoods(lActorID,cardid1,1)
				API_AddGoods(lActorID,cardid2,1)
				API_AddGoods(lActorID,cardid3,1)
				API_AddGoods(lActorID,cardid4,1)
				API_AddGoods(lActorID,cardid5,1)
				API_AddPlayerMoney(lActorID, 5000)
				API_LuaStructDataSendItemList(lActorID)
			else
				API_SendPacketFull(lActorID, "您的背包已满，无法获得物品")
			end
		API_LuaStructDataClear()
	end
	API_LuaStructDataClear()
end

function Itemuse_5048(lActorID,lGoodsID,GoodsUid)
	local num = API_GetNumByGoodsID(lActorID,lGoodsID, 0)
	if num == 0 then
		API_SendErrorMsg(lActorID, "你大爷的开挂啊啊啊啊啊")
	else
		local cardid1 = 70206
			API_LuaStructDataPushItem(cardid1,1)
		local canadd = API_CanAddItemToBags(lActorID)
			if canadd == true then
				API_RemoveGoods(lActorID,lGoodsID,1)
				API_AddGoods(lActorID,cardid1,1)
				API_AddPlayerMoney(lActorID, 5000)
				API_LuaStructDataSendItemList(lActorID)
			else
				API_SendPacketFull(lActorID, "您的背包已满，无法获得物品")
			end
		API_LuaStructDataClear()
	end
	API_LuaStructDataClear()
end

function Itemuse_5049(lActorID,lGoodsID,GoodsUid)
	local num = API_GetNumByGoodsID(lActorID,lGoodsID, 0)
	if num == 0 then
		API_SendErrorMsg(lActorID, "你大爷的开挂啊啊啊啊啊")
	else
		local cardid1 = 70241
			  cardid2 = 70242
			  cardid3 = 70243
			  cardid4 = 70244
			  cardid5 = 70245
				API_LuaStructDataPushItem(cardid1,1)
				API_LuaStructDataPushItem(cardid2,1)
				API_LuaStructDataPushItem(cardid3,1)
				API_LuaStructDataPushItem(cardid4,1)
				API_LuaStructDataPushItem(cardid5,1)
		local canadd = API_CanAddItemToBags(lActorID)
			if canadd == true then
				API_RemoveGoods(lActorID,lGoodsID,1)
				API_AddGoods(lActorID,cardid1,1)
				API_AddGoods(lActorID,cardid2,1)
				API_AddGoods(lActorID,cardid3,1)
				API_AddGoods(lActorID,cardid4,1)
				API_AddGoods(lActorID,cardid5,1)
				API_AddPlayerMoney(lActorID, 5000)
				API_LuaStructDataSendItemList(lActorID)
			else
				API_SendPacketFull(lActorID, "您的背包已满，无法获得物品")
			end
		API_LuaStructDataClear()
	end
	API_LuaStructDataClear()
end

function Itemuse_5050(lActorID,lGoodsID,GoodsUid)
	local num = API_GetNumByGoodsID(lActorID,lGoodsID, 0)
	if num == 0 then
		API_SendErrorMsg(lActorID, "你大爷的开挂啊啊啊啊啊")
	else
		local cardid1 = 70203
			API_LuaStructDataPushItem(cardid1,1)
		local canadd = API_CanAddItemToBags(lActorID)
			if canadd == true then
				API_RemoveGoods(lActorID,lGoodsID,1)
				API_AddGoods(lActorID,cardid1,1)
				API_AddPlayerMoney(lActorID, 5000)
				API_LuaStructDataSendItemList(lActorID)
			else
				API_SendPacketFull(lActorID, "您的背包已满，无法获得物品")
			end
		API_LuaStructDataClear()
	end
	API_LuaStructDataClear()
end

function Itemuse_5051(lActorID,lGoodsID,GoodsUid)
	local num = API_GetNumByGoodsID(lActorID,lGoodsID, 0)
	if num == 0 then
		API_SendErrorMsg(lActorID, "你大爷的开挂啊啊啊啊啊")
	else
		local cardid1 = 70241
			  cardid2 = 70242
			  cardid3 = 70243
			  cardid4 = 70244
			  cardid5 = 70245
				API_LuaStructDataPushItem(cardid1,1)
				API_LuaStructDataPushItem(cardid2,1)
				API_LuaStructDataPushItem(cardid3,1)
				API_LuaStructDataPushItem(cardid4,1)
				API_LuaStructDataPushItem(cardid5,1)
		local canadd = API_CanAddItemToBags(lActorID)
			if canadd == true then
				API_RemoveGoods(lActorID,lGoodsID,1)
				API_AddGoods(lActorID,cardid1,1)
				API_AddGoods(lActorID,cardid2,1)
				API_AddGoods(lActorID,cardid3,1)
				API_AddGoods(lActorID,cardid4,1)
				API_AddGoods(lActorID,cardid5,1)
				API_AddPlayerMoney(lActorID, 5000)
				API_LuaStructDataSendItemList(lActorID)
			else
				API_SendPacketFull(lActorID, "您的背包已满，无法获得物品")
			end
		API_LuaStructDataClear()
	end
	API_LuaStructDataClear()
end

function Itemuse_5052(lActorID,lGoodsID,GoodsUid)
	local num = API_GetNumByGoodsID(lActorID,lGoodsID, 0)
	if num == 0 then
		API_SendErrorMsg(lActorID, "你大爷的开挂啊啊啊啊啊")
	else
		local cardid1 = 70209	
			  cardid2 = 70212
				API_LuaStructDataPushItem(cardid1,2)
				API_LuaStructDataPushItem(cardid2,2)
		local canadd = API_CanAddItemToBags(lActorID)
			if canadd == true then
				API_RemoveGoods(lActorID,lGoodsID,1)
				API_AddGoods(lActorID,cardid1,2)
				API_AddGoods(lActorID,cardid2,2)
				API_AddPlayerMoney(lActorID, 5000)
				API_LuaStructDataSendItemList(lActorID)
			else
				API_SendPacketFull(lActorID, "您的背包已满，无法获得物品")
			end
		API_LuaStructDataClear()
	end
	API_LuaStructDataClear()
end

function Itemuse_5053(lActorID,lGoodsID,GoodsUid)
	local num = API_GetNumByGoodsID(lActorID,lGoodsID, 0)
	if num == 0 then
		API_SendErrorMsg(lActorID, "你大爷的开挂啊啊啊啊啊")
	else
		local cardid1 = 70241
			  cardid2 = 70242
			  cardid3 = 70243
			  cardid4 = 70244
			  cardid5 = 70245
				API_LuaStructDataPushItem(cardid1,1)
				API_LuaStructDataPushItem(cardid2,1)
				API_LuaStructDataPushItem(cardid3,1)
				API_LuaStructDataPushItem(cardid4,1)
				API_LuaStructDataPushItem(cardid5,1)
		local canadd = API_CanAddItemToBags(lActorID)
			if canadd == true then
				API_RemoveGoods(lActorID,lGoodsID,1)
				API_AddGoods(lActorID,cardid1,1)
				API_AddGoods(lActorID,cardid2,1)
				API_AddGoods(lActorID,cardid3,1)
				API_AddGoods(lActorID,cardid4,1)
				API_AddGoods(lActorID,cardid5,1)
				API_AddPlayerMoney(lActorID, 5000)
				API_LuaStructDataSendItemList(lActorID)
			else
				API_SendPacketFull(lActorID, "您的背包已满，无法获得物品")
			end
		API_LuaStructDataClear()
	end
	API_LuaStructDataClear()
end

function Itemuse_5054(lActorID,lGoodsID,GoodsUid)
	local num = API_GetNumByGoodsID(lActorID,lGoodsID, 0)
	if num == 0 then
		API_SendErrorMsg(lActorID, "你大爷的开挂啊啊啊啊啊")
	else
		local cardid1 = 70203	
			  cardid2 = 70206
				API_LuaStructDataPushItem(cardid1,1)
				API_LuaStructDataPushItem(cardid2,1)
		local canadd = API_CanAddItemToBags(lActorID)
			if canadd == true then
				API_RemoveGoods(lActorID,lGoodsID,1)
				API_AddGoods(lActorID,cardid1,1)
				API_AddGoods(lActorID,cardid2,1)
				API_AddPlayerMoney(lActorID, 5000)
				API_LuaStructDataSendItemList(lActorID)
			else
				API_SendPacketFull(lActorID, "您的背包已满，无法获得物品")
			end
		API_LuaStructDataClear()
	end
	API_LuaStructDataClear()
end

function Itemuse_5055(lActorID,lGoodsID,GoodsUid)
	local num = API_GetNumByGoodsID(lActorID,lGoodsID, 0)
	if num == 0 then
		API_SendErrorMsg(lActorID, "你大爷的开挂啊啊啊啊啊")
	else
		local cardid1 = 70241
			  cardid2 = 70242
			  cardid3 = 70243
			  cardid4 = 70244
			  cardid5 = 70245
				API_LuaStructDataPushItem(cardid1,1)
				API_LuaStructDataPushItem(cardid2,1)
				API_LuaStructDataPushItem(cardid3,1)
				API_LuaStructDataPushItem(cardid4,1)
				API_LuaStructDataPushItem(cardid5,1)
		local canadd = API_CanAddItemToBags(lActorID)
			if canadd == true then
				API_RemoveGoods(lActorID,lGoodsID,1)
				API_AddGoods(lActorID,cardid1,1)
				API_AddGoods(lActorID,cardid2,1)
				API_AddGoods(lActorID,cardid3,1)
				API_AddGoods(lActorID,cardid4,1)
				API_AddGoods(lActorID,cardid5,1)
				API_AddPlayerMoney(lActorID, 5000)
				API_LuaStructDataSendItemList(lActorID)
			else
				API_SendPacketFull(lActorID, "您的背包已满，无法获得物品")
			end
		API_LuaStructDataClear()
	end
	API_LuaStructDataClear()
end

function Itemuse_5056(lActorID,lGoodsID,GoodsUid)
	local num = API_GetNumByGoodsID(lActorID,lGoodsID, 0)
	if num == 0 then
		API_SendErrorMsg(lActorID, "你大爷的开挂啊啊啊啊啊")
	else
			API_RemoveGoods(lActorID,lGoodsID,1)
			API_AddPlayerMoney(lActorID, 88888)
	end
end

function Itemuse_5057(lActorID,lGoodsID,GoodsUid)
	local num = API_GetNumByGoodsID(lActorID,lGoodsID, 0)
	if num == 0 then
		API_SendErrorMsg(lActorID, "你大爷的开挂啊啊啊啊啊")
	else
		local cardid1 = 70201
			  cardid2 = 70204
			  cardid3 = 70207
			  cardid4 = 70210
				API_LuaStructDataPushItem(cardid1,10)
				API_LuaStructDataPushItem(cardid2,10)
				API_LuaStructDataPushItem(cardid3,10)
				API_LuaStructDataPushItem(cardid4,10)
		local canadd = API_CanAddItemToBags(lActorID)
			if canadd == true then
				API_RemoveGoods(lActorID,lGoodsID,1)
				API_AddGoods(lActorID,cardid1,10)
				API_AddGoods(lActorID,cardid2,10)
				API_AddGoods(lActorID,cardid3,10)
				API_AddGoods(lActorID,cardid4,10)
				API_AddPlayerMoney(lActorID, 88888)
				API_LuaStructDataSendItemList(lActorID)
			else
				API_SendPacketFull(lActorID, "您的背包已满，无法获得物品")
			end
		API_LuaStructDataClear()
	end
	API_LuaStructDataClear()
end

function Itemuse_5058(lActorID,lGoodsID,GoodsUid)
	local num = API_GetNumByGoodsID(lActorID,lGoodsID, 0)
	if num == 0 then
		API_SendErrorMsg(lActorID, "你大爷的开挂啊啊啊啊啊")
	else
		local cardid1 = 70202
			  cardid2 = 70205
			  cardid3 = 70208
			  cardid4 = 70211
			  cardid5 = 70225
			  cardid6 = 70226
			  cardid7 = 70227
			  cardid8 = 70228
			  cardid9 = 70229
				API_LuaStructDataPushItem(cardid1,10)
				API_LuaStructDataPushItem(cardid2,10)
				API_LuaStructDataPushItem(cardid3,10)
				API_LuaStructDataPushItem(cardid4,10)
				API_LuaStructDataPushItem(cardid5,10)
				API_LuaStructDataPushItem(cardid6,10)
				API_LuaStructDataPushItem(cardid7,10)
				API_LuaStructDataPushItem(cardid8,10)
				API_LuaStructDataPushItem(cardid9,10)
		local canadd = API_CanAddItemToBags(lActorID)
			if canadd == true then
				API_RemoveGoods(lActorID,lGoodsID,1)
				API_AddGoods(lActorID,cardid1,10)
				API_AddGoods(lActorID,cardid2,10)
				API_AddGoods(lActorID,cardid3,10)
				API_AddGoods(lActorID,cardid4,10)
				API_AddGoods(lActorID,cardid5,10)
				API_AddGoods(lActorID,cardid6,10)
				API_AddGoods(lActorID,cardid7,10)
				API_AddGoods(lActorID,cardid8,10)
				API_AddGoods(lActorID,cardid9,10)
				API_AddPlayerMoney(lActorID, 88888)
				API_LuaStructDataSendItemList(lActorID)
			else
				API_SendPacketFull(lActorID, "您的背包已满，无法获得物品")
			end
		API_LuaStructDataClear()
	end
	API_LuaStructDataClear()
end

function Itemuse_5059(lActorID,lGoodsID,GoodsUid)
	local num = API_GetNumByGoodsID(lActorID,lGoodsID, 0)
	if num == 0 then
		API_SendErrorMsg(lActorID, "你大爷的开挂啊啊啊啊啊")
	else
		local cardid1 = 70203
			  cardid2 = 70206
			  cardid3 = 70209
			  cardid4 = 70212
			  cardid5 = 70241
			  cardid6 = 70242
			  cardid7 = 70243
			  cardid8 = 70244
			  cardid9 = 70245
				API_LuaStructDataPushItem(cardid1,10)
				API_LuaStructDataPushItem(cardid2,10)
				API_LuaStructDataPushItem(cardid3,10)
				API_LuaStructDataPushItem(cardid4,10)
				API_LuaStructDataPushItem(cardid5,10)
				API_LuaStructDataPushItem(cardid6,10)
				API_LuaStructDataPushItem(cardid7,10)
				API_LuaStructDataPushItem(cardid8,10)
				API_LuaStructDataPushItem(cardid9,10)
		local canadd = API_CanAddItemToBags(lActorID)
			if canadd == true then
				API_RemoveGoods(lActorID,lGoodsID,1)
				API_AddGoods(lActorID,cardid1,10)
				API_AddGoods(lActorID,cardid2,10)
				API_AddGoods(lActorID,cardid3,10)
				API_AddGoods(lActorID,cardid4,10)
				API_AddGoods(lActorID,cardid5,10)
				API_AddGoods(lActorID,cardid6,10)
				API_AddGoods(lActorID,cardid7,10)
				API_AddGoods(lActorID,cardid8,10)
				API_AddGoods(lActorID,cardid9,10)
				API_AddPlayerMoney(lActorID, 88888)
				API_LuaStructDataSendItemList(lActorID)
			else
				API_SendPacketFull(lActorID, "您的背包已满，无法获得物品")
			end
		API_LuaStructDataClear()
	end
	API_LuaStructDataClear()
end

function Itemuse_5060(lActorID,lGoodsID,GoodsUid)
	local num = API_GetNumByGoodsID(lActorID,lGoodsID, 0)
	if num == 0 then
		API_SendErrorMsg(lActorID, "你大爷的开挂啊啊啊啊啊")
	else
		local cardid1 = 0
		local num = 0
		local id1 = math.random(1,1000)
		if id1 >= 991 and id1 <= 992 then
			cardid1 = 14501
			num = 1
		end
		if id1 >= 993 and id1 <= 994 then
			cardid1 = 24301
			num = 1
		end
		if id1 >= 995 and id1 <= 996 then
			cardid1 = 34401
			num = 1
		end
		if id1 >= 997 and id1 <= 998 then
			cardid1 = 44301
			num = 1
		end
		if id1 >= 999 and id1 <= 1000 then
			cardid1 = 54501
			num = 1
		end
		if id1 >=1 and id1 <= 200 then
			cardid1 = 70215
			num = 2
		end
		if id1 >=201 and id1 <= 400 then
			cardid1 = 70218
			num = 2
		end
		if id1 >=401 and id1 <= 700 then
			cardid1 = 70221
			num = 2
		end
		if id1 >=701 and id1 <= 990 then
			cardid1 = 70224
			num = 2
		end
			API_LuaStructDataPushItem(cardid1,num)
		local canadd = API_CanAddItemToBags(lActorID)
			if canadd == true then
				API_RemoveGoods(lActorID,lGoodsID,1)
				API_AddGoods(lActorID,cardid1,num)
				API_AddPlayerMoney(lActorID, 10000)
				API_LuaStructDataSendItemList(lActorID)
			else
				API_SendPacketFull(lActorID, "您的背包已满，无法获得物品")
			end
		API_LuaStructDataClear()
	end
	API_LuaStructDataClear()
end

function Itemuse_5061(lActorID,lGoodsID,GoodsUid)
	local num = API_GetNumByGoodsID(lActorID,lGoodsID, 0)
	if num == 0 then
		API_SendErrorMsg(lActorID, "你大爷的开挂啊啊啊啊啊")
	else
		local cardid1 = 0
		local num = 0
		local id1 = math.random(1,1000)
		if id1 >= 991 and id1 <= 992 then
			cardid1 = 14501
			num = 1
		end
		if id1 >= 993 and id1 <= 994 then
			cardid1 = 24301
			num = 1
		end
		if id1 >= 995 and id1 <= 996 then
			cardid1 = 34401
			num = 1
		end
		if id1 >= 997 and id1 <= 998 then
			cardid1 = 44301
			num = 1
		end
		if id1 >= 999 and id1 <= 1000 then
			cardid1 = 54501
			num = 1
		end
		if id1 >=1 and id1 <= 200 then
			cardid1 = 70214
			num = 6
		end
		if id1 >=201 and id1 <= 400 then
			cardid1 = 70217
			num = 6
		end
		if id1 >=401 and id1 <= 700 then
			cardid1 = 70220
			num = 6
		end
		if id1 >=701 and id1 <= 990 then
			cardid1 = 70223
			num = 6
		end
			API_LuaStructDataPushItem(cardid1,num)
		local canadd = API_CanAddItemToBags(lActorID)
			if canadd == true then
				API_RemoveGoods(lActorID,lGoodsID,1)
				API_AddGoods(lActorID,cardid1,num)
				API_AddPlayerMoney(lActorID, 10000)
				API_LuaStructDataSendItemList(lActorID)
			else
				API_SendPacketFull(lActorID, "您的背包已满，无法获得物品")
			end
		API_LuaStructDataClear()
	end
	API_LuaStructDataClear()
end

function Itemuse_5062(lActorID,lGoodsID,GoodsUid)
	local num = API_GetNumByGoodsID(lActorID,lGoodsID, 0)
	if num == 0 then
		API_SendErrorMsg(lActorID, "你大爷的开挂啊啊啊啊啊")
	else
		local cardid1 = 0
		local num = 0
		local id1 = math.random(1,1000)
		if id1 >= 991 and id1 <= 992 then
			cardid1 = 14501
			num = 1
		end
		if id1 >= 993 and id1 <= 994 then
			cardid1 = 24301
			num = 1
		end
		if id1 >= 995 and id1 <= 996 then
			cardid1 = 34401
			num = 1
		end
		if id1 >= 997 and id1 <= 998 then
			cardid1 = 44301
			num = 1
		end
		if id1 >= 999 and id1 <= 1000 then
			cardid1 = 54501
			num = 1
		end
		if id1 >=1 and id1 <= 200 then
			cardid1 = 70213
			num = 18
		end
		if id1 >=201 and id1 <= 400 then
			cardid1 = 70216
			num = 18
		end
		if id1 >=401 and id1 <= 700 then
			cardid1 = 70219
			num = 18
		end
		if id1 >=701 and id1 <= 990 then
			cardid1 = 70222
			num = 18
		end
			API_LuaStructDataPushItem(cardid1,num)
		local canadd = API_CanAddItemToBags(lActorID)
			if canadd == true then
				API_RemoveGoods(lActorID,lGoodsID,1)
				API_AddGoods(lActorID,cardid1,num)
				API_AddPlayerMoney(lActorID, 10000)
				API_LuaStructDataSendItemList(lActorID)
			else
				API_SendPacketFull(lActorID, "您的背包已满，无法获得物品")
			end
		API_LuaStructDataClear()
	end
	API_LuaStructDataClear()
end

function Itemuse_5063(lActorID,lGoodsID,GoodsUid)
	local num = API_GetNumByGoodsID(lActorID,lGoodsID, 0)
	if num == 0 then
		API_SendErrorMsg(lActorID, "你大爷的开挂啊啊啊啊啊")
	else
			API_RemoveGoods(lActorID,lGoodsID,1)
			API_AddPlayerMoney(lActorID, 10000)
	end
end
