visit_npc_list40 = { {"东郊的孙叔通", 432},{"东郊的王莽", 433},{"南郊的房玄龄", 443},{"南郊的田开疆", 449} };
visit_npc_list402 = { {"南郊的公孙捷", 450},{"北郊的伍参", 456},{"白骨洞三的介子", 428} };

get_weapon_list40 = { {"65级斩马刀(白色)", 10307, 0}, {"65级龙鳞杖(白色)", 10507, 0}, {"65级黄金弓(白色)", 10557, 0}, {"65级银月扇(白色)", 10607, 0}, {"65级飞雪棍(白色)", 10657, 0}};
get_weapon_list402 = { {"65级斩马刀(蓝色)", 10307, 1}, {"65级龙鳞杖(蓝色)", 10507, 1}, {"65级黄金弓(蓝色)", 10557, 1}, {"65级银月扇(蓝色)", 10607, 1}, {"65级飞雪棍(蓝色)", 10657, 1}};

kill_npc_list40 = { {"精怪洞三层的70级蜘蛛妖", 16241}, {"北郊的70级黑豹", 15030}, {"凤祥镇的70级叛军弓兵", 15094}, {"千江镇的70级地痞", 15170} };
kill_npc_list402 = { {"白骨洞八层的75级骷髅", 16071}, {"北郊的75级雌火猪(魔)", 15037}, {"千江镇的75级打手", 15173} };

get_item_list40 = { {"大荔枝", 1878}, {"精致的兽皮", 1805}, {"牛肉干", 1905} }; 
get_item_list402 = { {"大钱包", 1904}, {"草莓", 1832}, {"肉猪", 1972} };

kill_get_list40 = { {"杀边境45级的痞子获得10件夜行衣", 16151, 2050}, {"杀边境45级的弩灵获得10块黑布", 16152, 2065}, {"杀东郊45级的异军步兵获得10把染血的刀", 16173, 2062} };

kill_get_list402 = { {"杀东郊50级的异军巫医获得10个毒药", 16176, 2088}, {"杀东郊50级的异军哨探获得10个异族秘宝", 16175, 2121}, {"白骨洞一层的劈头僵尸获得骷髅骨头", 16013, 2021} };

kill_boss_list = { {"龙冈山一寨上的山贼刺客ID:16440", 16440} };
kill_boss_list2 = { {"龙冈山四寨上的山贼隐士ID:16441", 16441} };

menu_820_1 = [[
function IsHasTask()
return true
end
function TaskDialog()
this:AddTalk("    这是一个环式任务，一旦接了就不能删除，完成任务后可以找NPC领取奖励，每次的奖励根据完成的任务数量和任务所在的环数决定。\n\n    这是本环第#qs#个任务\n    这是今天的第#round#环。\n\n经验奖励：#exp#");
this:AddTaskCmdItem("接受任务", "accept_820", 21102, 1)
this:AddDialogItem("环任务存档(0)", "Dialog99")
this:AddTaskCmdItem("结束本日环任务", "accept_820", 21102, 102)
end
function Dialog99()
this:AddTalk("    你确定要将现在完成的环数存档么？\n    一旦存档，您必须先将档案取出才能继续环式任务。这将消耗您900点荣誉点。")
this:AddTaskCmdItem("确定存档-900荣誉值{10001}", "accept_820", 21102, 99)
end
function Dialog45()
this:AddTalk("帮我把这封信交给#place#，然后回来我给你奖励。");
end
function MoveCanClose()
	return true
end

]]

menu_820_2 = [[
function IsHasTask()
return true
end
function TaskDialog()
this:AddTalk("    这是一个环式任务，一旦接了就不能删除，完成任务后可以找NPC领取奖励，每次的奖励根据完成的任务数量和任务所在的环数决定。\n\n    这是本环第#qs#个任务\n    这是今天的第#round#环。\n\n经验奖励：#exp#");
this:AddTaskCmdItem("接受任务", "accept_820", 21102, 2)
this:AddDialogItem("环任务存档(0)", "Dialog99")
this:AddTaskCmdItem("结束本日环任务", "accept_820", 21102, 102)
end
function Dialog99()
this:AddTalk("    你确定要将现在完成的环数存档么？\n    一旦存档，您必须先将档案取出才能继续环式任务。这将消耗您100点荣誉点。")
this:AddTaskCmdItem("确定存档-900荣誉值{10001}", "accept_820", 21102, 99)
end
function Dialog45()
this:AddTalk("帮我杀#npc#5只，然后回来告诉我。");
end
function MoveCanClose()
	return true
end

]]

--收集物品任务
menu_820_3 = [[
function IsHasTask()
return true
end
function TaskDialog()
this:AddTalk("    这是一个环式任务，一旦接了就不能删除，完成任务后可以找NPC领取奖励，每次的奖励根据完成的任务数量和任务所在的环数决定。\n\n    这是本环第#qs#个任务\n    这是今天的第#round#环。\n\n经验奖励：#exp#");
this:AddTaskCmdItem("接受任务", "accept_820", 21102, 3)
this:AddDialogItem("环任务存档(0)", "Dialog99")
this:AddTaskCmdItem("结束本日环任务", "accept_820", 21102, 102)
end
function Dialog99()
this:AddTalk("    你确定要将现在完成的环数存档么？\n    一旦存档，您必须先将档案取出才能继续环式任务。这将消耗您100点荣誉点。")
this:AddTaskCmdItem("确定存档-900荣誉值{10001}", "accept_820", 21102, 99)
end
function Dialog45()
this:AddTalk("我需要3个#name#，全部找到后拿来给我。");
end
function MoveCanClose()
	return true
end

]]

menu_820_13 = [[
function IsHasTask()
return true
end
function TaskDialog()
this:AddTalk("    这是一个环式任务，一旦接了就不能删除，完成任务后可以找NPC领取奖励，每次的奖励根据完成的任务数量和任务所在的环数决定。\n\n    这是本环第#qs#个任务\n    这是今天的第#round#环。\n\n经验奖励：#exp#");
this:AddTaskCmdItem("接受任务", "accept_820", 21102, 13)
this:AddDialogItem("环任务存档(0)", "Dialog99")
this:AddTaskCmdItem("结束本日环任务", "accept_820", 21102, 102)
end
function Dialog99()
this:AddTalk("    你确定要将现在完成的环数存档么？\n    一旦存档，您必须先将档案取出才能继续环式任务。这将消耗您100点荣誉点。")
this:AddTaskCmdItem("确定存档-900荣誉值{10001}", "accept_820", 21102, 99)
end
function MoveCanClose()
	return true
end

]]

--收集装备接任务
menu_820_15 = [[
function IsHasTask()
return true
end
function TaskDialog()
this:AddTalk("    这是一个环式任务，一旦接了就不能删除，完成任务后可以找NPC领取奖励，每次的奖励根据完成的任务数量和任务所在的环数决定。\n\n    这是本环第#qs#个任务\n    这是今天的第#round#环。\n\n经验奖励：#exp#");
this:AddTaskCmdItem("接受任务", "accept_820", 21102, 15)
this:AddDialogItem("环任务存档(0)", "Dialog99")
this:AddTaskCmdItem("结束本日环任务", "accept_820", 21102, 102)
end
function Dialog99()
this:AddTalk("    你确定要将现在完成的环数存档么？\n    一旦存档，您必须先将档案取出才能继续环式任务。这将消耗您100点荣誉点。")
this:AddTaskCmdItem("确定存档-900荣誉值{10001}", "accept_820", 21102, 99)
end
function MoveCanClose()
	return true
end

]]

--杀BOSS接任务对话
menu_820_17 = [[
function IsHasTask()
return true
end
function TaskDialog()
this:AddTalk("    这是一个环式任务，一旦接了就不能删除，完成任务后可以找NPC领取奖励，每次的奖励根据完成的任务数量和任务所在的环数决定。\n\n    这是本环第#qs#个任务\n    这是今天的第#round#环。\n\n经验奖励：#exp#");
this:AddTaskCmdItem("接受任务", "accept_820", 21102, 17)
this:AddDialogItem("环任务存档(0)", "Dialog99")
this:AddTaskCmdItem("结束本日环任务", "accept_820", 21102, 102)
end
function Dialog99()
this:AddTalk("    你确定要将现在完成的环数存档么？\n    一旦存档，您必须先将档案取出才能继续环式任务。这将消耗您100点荣誉点。")
this:AddTaskCmdItem("确定存档-900荣誉值{10001}", "accept_820", 21102, 99)
end
function MoveCanClose()
	return true
end

]]

menu_820_23 = [[
function IsHasTask()
return true
end
function TaskDialog()
this:AddTalk("去#name#后给我。");
this:AddCloseItem("知道了")
end

]]

--收集装备通知
menu_820_45 = [[
function IsHasTask()
return true
end
function TaskDialog()
this:AddTalk("去收集一个#name#给我。");
this:AddCloseItem("知道了")
end

]]

menu_820_4 = [[
function IsHasTask()
return true
end
function TaskDialog()
this:AddTalk("我需要3个#name#，全部找到后拿来给我。");
this:AddCloseItem("知道了")
end

]]

menu_820_5 = [[
function IsHasTask()
return true
end
function TaskDialog()
this:AddTalk("帮我把这封信交给#place#，回来后我会给你奖励的。");
this:AddCloseItem("知道了")
end

]]

menu_820_6 = [[
function IsHasTask()
return true
end
function TaskDialog()
this:AddTalk("帮我杀#name#15只，然后回来告诉我。");
this:AddCloseItem("知道了")
end

]]

menu_820_7 = [[
function IsHasTask()
return true
end
function TaskDialog()
this:AddTalk("帮我杀#name#，然后回来告诉我。");
this:AddCloseItem("知道了")
end

]]


menu_820_11 = [[
function IsHasTask()
return true
end
function TaskDialog()
this:AddTalk("恭喜你完成了任务，你想现在领取奖励么？");
this:AddTaskCmdItem("接受奖励", "accept_820", 21102, 11)
end

]]

menu_820_8 = [[
function IsHasTask()
return true
end
function TaskDialog()
this:AddTalk("3个#name#，你已经收集好了么？");
this:AddTaskCmdItem("拿出物品", "accept_820", 21102, 8)
end

]]

menu_820_31 = [[
function IsHasTask()
return true
end
function TaskDialog()
this:AddTalk("10个那么快就弄到啦，真是太能干了，快给我。");
this:AddTaskCmdItem("拿出物品", "accept_820", 21102, 31)
end

]]

--收集装备任务交任务对话
menu_820_35 = [[
function IsHasTask()
return true
end
function TaskDialog()
this:AddTalk("#name#那么快就弄到啦，真是太能干了，快给我。");
this:AddTaskCmdItem("拿出物品", "accept_820", 21102, 35)
end

]]


menu_820_80 = [[
function IsHasTask()
return true
end
function TaskDialog()
this:AddTalk("信总算送来了，你回去告诉环式任务使者，我知道了。");
this:AddCloseItem("我这就去告诉他")
end

]]

menu_820_90 = [[
function IsHasTask()
return true
end
function TaskDialog()
this:AddTalk("    你今天能完成的环数已达到上限，下周六才能继续");
this:AddCloseItem("离开")
end

]]

menu_820_91 = [[
function IsHasTask()
return true
end
function TaskDialog()
this:AddTalk("    你还没有家族，无法接家族环式任务。");
this:AddCloseItem("离开")
end

]]

menu_820_92 = [[
function IsHasTask()
return true
end
function TaskDialog()
this:AddTalk("    你昨天任务已经结束，接下来将开始今天的环式任务。");
this:AddCloseItem("离开")
end

]]


menu_820_94 = [[
function IsHasTask()
return true
end
function TaskDialog()
this:AddTalk("    由于贵家族今天完成家族荣耀任务，因此您本日可以重新做一次家族环式任务，是否要现在开始呢？");
this:AddTaskCmdItem("再次开始本日家族环式任务", "accept_820", 21102, 94)
end

]]

menu_820_100 = [[
function IsHasTask()
return true
end
function TaskDialog()
this:AddTalk("    你确定要现在取出你的环式任务存档么？");
this:AddTaskCmdItem("取出存档", "accept_820", 21102, 100)
end

]]

menu_820_101 = [[
function IsHasTask()
return true
end
function TaskDialog()
this:AddTalk("    由于你离线时间过长，需要结束本日任务。");
this:AddTaskCmdItem("结束本日任务", "accept_820", 21102, 101)
end

]]

function visit_npc(npc)
	--print("visit");
	player = me();
	local v = player.quest:vars(21102);
	if not v then
		return 0;
	end

	local s = v:get("state");
	local id = v:get("id");
	local type = v:get("type");
	--print(s);
	--print(id);
	--print(type);
	--print(npc:id());

	if s == 1 and id==npc:id() and type == 1 then
		--print(1);
		show_dialog(npc, menu_820_80);	
		--print(2);
		player:remove_ob(2068, 1, 0);
		v:set("state", -3);	
		npc:refresh();
		local tempid = v:get("npc");
		refresh_npc(tempid);		
		return 1;
	end	
	
	return 0;
end

function state_npc(npc)
	player = me();
	if not player then return 0; end
	
	local v = player.quest:vars(21102);
	if not v then
		return 0;
	end

	local s = v:get("state");
	local id = v:get("id");
	local type = v:get("type");
	
	if s == 1 and id==npc:id() and type == 1 then
		return Quest.FINISH;
	end

	return 0;
end


function kill_npc(npc)
	--print("kill");
	player = me();
	local v = player.quest:vars(21102);
	if not v then return 0; end
	
	local s = v:get("state");
	local id = v:get("id");
	local type = v:get("type");
	local item = v:get("item");
	
	--print(npc:id());
	--print(1);
	
	if s == 1 and id==npc:id() and type == 2 then
		local kill = v:get("kills");
		
			--print(2);
			if kill < 1 then 
				v:set("kills", 1); 
				kill=1;
				--print("killtest");
				--print(kill);
				
				local xxx="环式任务目标：#num#/15";
				xxx = string.gsub(xxx, "#num#", kill);	
				v:sets("num", xxx);
				--print(xxx);
				v:refresh(player,"num")
					
				player.quest:add(21102, v, player, true);
				
			end		
		
			v:set("kills", kill+1);
			
			if kill >= 1 then

				local xxx="环式任务目标：#num#/15";
				xxx = string.gsub(xxx, "#num#", kill);	
				v:sets("num", xxx);
				--print(xxx);
				v:refresh(player,"num")
				
				player.quest:add(21102, v, player, true);

			end
						
			if kill >= 15 then

				local xxx="环式任务目标：#num#/15";
				xxx = string.gsub(xxx, "#num#", kill);	
				v:sets("num", xxx);
				--print(xxx);
				v:refresh(player,"num")
				
				player.quest:add(21102, v, player, true);

				sys(player, 5, "环式任务完成");
				v:set("state", -3);
				local tempid = v:get("npc");
				refresh_npc(tempid);
			end
				
		return 1;
	end
	
	return 0;
end

function get_object(object)
	--print("get_ob");
	player = me();
	local v = player.quest:vars(21102);
	if not v then return 0; end
	--print(3);
	
	local s = v:get("state");
	local id = v:get("id");
	local item = v:get("item");
	local type = v:get("type");
	
	--if s == 1 and id==npc:id() and type == 3 then
		if s == 1 and type == 3 then

			local get = v:get("item_nums");
			
			--print(2);
			if not get then 
				v:set("item_nums", 1); 
				sys(player, 5, "获得环式任务物品");
			else		
				v:set("item_nums", get+1);
				sys(player, 5, "获得环式任务物品");
				if get >= 5 then
					sys(player, 5, "恭喜你收集了足够的物品");
					v:set("state", -3);
					local tempid = v:get("id");
					refresh_npc(tempid);
				end
			end
				
			return 1;
		end
		
		
		local s = v:get("state");
		local id = v:get("id");
		local item = v:get("item");
		local type = v:get("type");
		
			--print(s);
			--print(type);
			--print(item);
	
		--if s == 1 and id==npc:id() and item==npc:item() and type == 4 then
		--print("开始判断");
		if s == 1 and type == 4 then

			local get = v:get("item_nums");
			
			if get < 1 then 
				v:set("item_nums", 1); 
				get=1;
				local xxx="环式任务目标：#num#/10";
				xxx = string.gsub(xxx, "#num#", get);	
				v:sets("num", xxx);
				--print(xxx);
				v:refresh(player,"num")
				player.quest:add(21102, v, player, true);
			end
			
			if get >= 1 then 
				v:set("item_nums", get+1); 
				local xxx="环式任务目标：#num#/10";
				xxx = string.gsub(xxx, "#num#", get);	
				v:sets("num", xxx);
				--print(xxx);
				v:refresh(player,"num")
				player.quest:add(21102, v, player, true);
			end
			
			if get >= 10 then 
					v:set("item_nums", get+1); 
					local xxx="环式任务目标：#num#/10";
					xxx = string.gsub(xxx, "#num#", get);	
					v:sets("num", xxx);
					--print(xxx);
					v:refresh(player,"num")
					player.quest:add(21102, v, player, true);
			
					sys(player, 5, "恭喜你收集了足够的物品");
					v:set("state", -3);
					local tempid = v:get("id");
					refresh_npc(tempid);
			end
				
			return 1;
		end
	
	return 0;
end

function gain_exp(player, qs, qss)
		local baseexp = 2*player.charbase.level*player.charbase.level;
		local exp = 15*baseexp*(0.5+0.25*(qs + qss));
	player:add_exp(exp, false, 0, 0, false);
end
