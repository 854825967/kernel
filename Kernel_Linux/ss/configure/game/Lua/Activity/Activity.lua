---------------------------------------[ 更 新 记 录 ]---------------------------------------

function Activity_MoneyPay(lUserID,lActorID,lActivityID)
	API_SysSendGameEventToActor(-1, lUserID, lActorID, "恭喜您充值金额达到100元，快来领取我们的特大礼包吧！", 0, 5004, 1, 0, 0);
end

function gonggao(lActivityType)
	API_SendScrollText("冬季商店特卖会11月23日11点火爆开启，送金币、送材料碎片、还送极品4星卡哟！详情请点击论坛查看！");
end

