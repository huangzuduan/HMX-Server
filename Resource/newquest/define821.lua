visit_npc_list50 = { {"边境的吕公", 423},{"边境的刘承佑", 424},{"白骨洞二的单超", 441},{"白骨洞三的重耳", 426} };
visit_npc_list502 = { {"白骨洞二的张让", 442},{"白骨洞三的狐偃", 427},{"北郊的张松", 457},{"凤凰城的齐姜", 429} };

get_weapon_list50 = { {"75级古锭刀(白色)", 10308, 0}, {"75级冰魄杖(白色)", 10508, 0}, {"75级宝雕弓(白色)", 10558, 0}, {"75级星彩扇(白色)", 10608, 0}, {"75级冰鳞棍(白色)", 10658, 0}}; 
get_weapon_list502 = { {"75级古锭刀(蓝色)", 10308, 1}, {"75级冰魄杖(蓝色)", 10508, 1}, {"75级宝雕弓(蓝色)", 10558, 1}, {"75级星彩扇(蓝色)", 10608, 1}, {"75级冰鳞棍(蓝色)", 10658, 1}}; 

kill_npc_list50 = { {"白骨洞九层的80级破魂僵尸", 16476}, {"精怪洞七层的80级赤虎精", 16256}, {"皇城的80级老虎", 16348}, {"千江镇的80级混混", 15176} };
kill_npc_list502 = { {"白骨洞九层的85级破魂僵尸", 16482}, {"精怪洞八层的85级猴精(魔）", 16261}, {"沼泽湿地的85级水精鳄", 15147} };

get_item_list50 = { {"耕牛", 1971}, {"桂圆", 1879}, {"甜果", 1903}, };
get_item_list502 = { {"猕猴桃", 1880}, {"鼓鼓的钱包", 1907}, {"铁甲蛙", 1973} };

kill_get_list50 = { {"杀东郊的异军护卫获得10件夜行衣", 16179, 2050}, {"杀白骨洞三层的狂爪僵尸获得10块黑布", 16024, 2065}, {"杀东郊的异军操兽师获得10把染血的刀", 16178, 2062} };

kill_get_list502 = { {"杀南郊60级的异军枪兵获得10个毒药", 16215, 2088}, {"杀四层60级的白骨斧手获得10个骷髅武器", 16033, 2023}, {"杀白骨洞四层的食怨僵尸获得僵尸内脏", 16034, 2125} };

kill_boss_list = { {"龙冈山一寨上的山贼刺客ID:16440", 16440} };
kill_boss_list2 = { {"龙冈山四寨上的山贼隐士ID:16441", 16441} };

menu_821_1 = [[
function IsHasTask()
return true
end
function TaskDialog()
this:AddTalk("    这是一个环式任务，一旦接了就不能删除，完成任务后可以找NPC领取奖励，每次的奖励根据完成的任务数量和任务所在的环数决定。\n\n    这是本环第#qs#个任务\n    这是今天的第#round#环。\n\n经验奖励：#exp#");
this:AddTaskCmdItem("接受任务", "accept_821", 21102, 1)
this:AddDialogItem("环任务存档(0)", "Dialog99")
this:AddTaskCmdItem("结束本日环任务", "accept_821", 21102, 102)
end
function Dialog99()
this:AddTalk("    你确定要将现在完成的环数存档么？\n    一旦存档，您必须先将档案取出才能继续环式任务。这将消耗您900点荣誉点。")
this:AddTaskCmdItem("确定存档-900荣誉值{10001}", "accept_821", 21102, 99)
end
function Dialog45()
this:AddTalk("帮我把这封信交给#place#，然后回来我给你奖励。");
end
function MoveCanClose()
	return true
end

]]

menu_821_2 = [[
function IsHasTask()
return true
end
function TaskDialog()
this:AddTalk("    这是一个环式任务，一旦接了就不能删除，完成任务后可以找NPC领取奖励，每次的奖励根据完成的任务数量和任务所在的环数决定。\n\n    这是本环第#qs#个任务\n    这是今天的第#round#环。\n\n经验奖励：#exp#");
this:AddTaskCmdItem("接受任务", "accept_821", 21102, 2)
this:AddDialogItem("环任务存档(0)", "Dialog99")
this:AddTaskCmdItem("结束本日环任务", "accept_821", 21102, 102)
end
function Dialog99()
this:AddTalk("    你确定要将现在完成的环数存档么？\n    一旦存档，您必须先将档案取出才能继续环式任务。这将消耗您100点荣誉点。")
this:AddTaskCmdItem("确定存档-900荣誉值{10001}", "accept_821", 21102, 99)
end
function Dialog45()
this:AddTalk("帮我杀#npc#5只，然后回来告诉我。");
end
function MoveCanClose()
	return true
end

]]

--收集物品任务
menu_821_3 = [[
function IsHasTask()
return true
end
function TaskDialog()
this:AddTalk("    这是一个环式任务，一旦接了就不能删除，完成任务后可以找NPC领取奖励，每次的奖励根据完成的任务数量和任务所在的环数决定。\n\n    这是本环第#qs#个任务\n    这是今天的第#round#环。\n\n经验奖励：#exp#");
this:AddTaskCmdItem("接受任务", "accept_821", 21102, 3)
this:AddDialogItem("环任务存档(0)", "Dialog99")
this:AddTaskCmdItem("结束本日环任务", "accept_821", 21102, 102)
end
function Dialog99()
this:AddTalk("    你确定要将现在完成的环数存档么？\n    一旦存档，您必须先将档案取出才能继续环式任务。这将消耗您100点荣誉点。")
this:AddTaskCmdItem("确定存档-900荣誉值{10001}", "accept_821", 21102, 99)
end
function Dialog45()
this:AddTalk("我需要3个#name#，全部找到后拿来给我。");
end
function MoveCanClose()
	return true
end

]]

menu_821_13 = [[
function IsHasTask()
return true
end
function TaskDialog()
this:AddTalk("    这是一个环式任务，一旦接了就不能删除，完成任务后可以找NPC领取奖励，每次的奖励根据完成的任务数量和任务所在的环数决定。\n\n    这是本环第#qs#个任务\n    这是今天的第#round#环。\n\n经验奖励：#exp#");
this:AddTaskCmdItem("接受任务", "accept_821", 21102, 13)
this:AddDialogItem("环任务存档(0)", "Dialog99")
this:AddTaskCmdItem("结束本日环任务", "accept_821", 21102, 102)
end
function Dialog99()
this:AddTalk("    你确定要将现在完成的环数存档么？\n    一旦存档，您必须先将档案取出才能继续环式任务。这将消耗您100点荣誉点。")
this:AddTaskCmdItem("确定存档-900荣誉值{10001}", "accept_821", 21102, 99)
end
function MoveCanClose()
	return true
end

]]

--收集装备接任务
menu_821_15 = [[
function IsHasTask()
return true
end
function TaskDialog()
this:AddTalk("    这是一个环式任务，一旦接了就不能删除，完成任务后可以找NPC领取奖励，每次的奖励根据完成的任务数量和任务所在的环数决定。\n\n    这是本环第#qs#个任务\n    这是今天的第#round#环。\n\n经验奖励：#exp#");
this:AddTaskCmdItem("接受任务", "accept_821", 21102, 15)
this:AddDialogItem("环任务存档(0)", "Dialog99")
this:AddTaskCmdItem("结束本日环任务", "accept_821", 21102, 102)
end
function Dialog99()
this:AddTalk("    你确定要将现在完成的环数存档么？\n    一旦存档，您必须先将档案取出才能继续环式任务。这将消耗您100点荣誉点。")
this:AddTaskCmdItem("确定存档-900荣誉值{10001}", "accept_821", 21102, 99)
end
function MoveCanClose()
	return true
end

]]

--杀BOSS接任务对话
menu_821_17 = [[
function IsHasTask()
return true
end
function TaskDialog()
this:AddTalk("    这是一个环式任务，一旦接了就不能删除，完成任务后可以找NPC领取奖励，每次的奖励根据完成的任务数量和任务所在的环数决定。\n\n    这是本环第#qs#个任务\n    这是今天的第#round#环。\n\n经验奖励：#exp#");
this:AddTaskCmdItem("接受任务", "accept_821", 21102, 17)
this:AddDialogItem("环任务存档(0)", "Dialog99")
this:AddTaskCmdItem("结束本日环任务", "accept_821", 21102, 102)
end
function Dialog99()
this:AddTalk("    你确定要将现在完成的环数存档么？\n    一旦存档，您必须先将档案取出才能继续环式任务。这将消耗您100点荣誉点。")
this:AddTaskCmdItem("确定存档-900荣誉值{10001}", "accept_821", 21102, 99)
end
function MoveCanClose()
	return true
end

]]

menu_821_23 = [[
function IsHasTask()
return true
end
function TaskDialog()
this:AddTalk("去#name#后给我。");
this:AddCloseItem("知道了")
end

]]

--收集装备通知
menu_821_45 = [[
function IsHasTask()
return true
end
function TaskDialog()
this:AddTalk("去收集一个#name#给我。");
this:AddCloseItem("知道了")
end

]]

menu_821_4 = [[
function IsHasTask()
return true
end
function TaskDialog()
this:AddTalk("我需要3个#name#，全部找到后拿来给我。");
this:AddCloseItem("知道了")
end

]]

menu_821_5 = [[
function IsHasTask()
return true
end
function TaskDialog()
this:AddTalk("帮我把这封信交给#place#，回来后我会给你奖励的。");
this:AddCloseItem("知道了")
end

]]

menu_821_6 = [[
function IsHasTask()
return true
end
function TaskDialog()
this:AddTalk("帮我杀#name#15只，然后回来告诉我。");
this:AddCloseItem("知道了")
end

]]

menu_821_7 = [[
function IsHasTask()
return true
end
function TaskDialog()
this:AddTalk("帮我杀#name#，然后回来告诉我。");
this:AddCloseItem("知道了")
end

]]


menu_821_11 = [[
function IsHasTask()
return true
end
function TaskDialog()
this:AddTalk("恭喜你完成了任务，你想现在领取奖励么？");
this:AddTaskCmdItem("接受奖励", "accept_821", 21102, 11)
end

]]

menu_821_8 = [[
function IsHasTask()
return true
end
function TaskDialog()
this:AddTalk("3个#name#，你已经收集好了么？");
this:AddTaskCmdItem("拿出物品", "accept_821", 21102, 8)
end

]]

menu_821_31 = [[
function IsHasTask()
return true
end
function TaskDialog()
this:AddTalk("10个那么快就弄到啦，真是太能干了，快给我。");
this:AddTaskCmdItem("拿出物品", "accept_821", 21102, 31)
end

]]

--收集装备任务交任务对话
menu_821_35 = [[
function IsHasTask()
return true
end
function TaskDialog()
this:AddTalk("#name#那么快就弄到啦，真是太能干了，快给我。");
this:AddTaskCmdItem("拿出物品", "accept_821", 21102, 35)
end

]]


menu_821_80 = [[
function IsHasTask()
return true
end
function TaskDialog()
this:AddTalk("信总算送来了，你回去告诉环式任务使者，我知道了。");
this:AddCloseItem("我这就去告诉他")
end

]]

menu_821_90 = [[
function IsHasTask()
return true
end
function TaskDialog()
this:AddTalk("    你今天能完成的环数已达到上限，下周六才能继续");
this:AddCloseItem("离开")
end

]]

menu_821_91 = [[
function IsHasTask()
return true
end
function TaskDialog()
this:AddTalk("    你还没有家族，无法接家族环式任务。");
this:AddCloseItem("离开")
end

]]

menu_821_92 = [[
function IsHasTask()
return true
end
function TaskDialog()
this:AddTalk("    你昨天任务已经结束，接下来将开始今天的环式任务。");
this:AddCloseItem("离开")
end

]]


menu_821_94 = [[
function IsHasTask()
return true
end
function TaskDialog()
this:AddTalk("    由于贵家族今天完成家族荣耀任务，因此您本日可以重新做一次家族环式任务，是否要现在开始呢？");
this:AddTaskCmdItem("再次开始本日家族环式任务", "accept_821", 21102, 94)
end

]]

menu_821_100 = [[
function IsHasTask()
return true
end
function TaskDialog()
this:AddTalk("    你确定要现在取出你的环式任务存档么？");
this:AddTaskCmdItem("取出存档", "accept_821", 21102, 100)
end

]]

menu_821_101 = [[
function IsHasTask()
return true
end
function TaskDialog()
this:AddTalk("    由于你离线时间过长，需要结束本日任务。");
this:AddTaskCmdItem("结束本日任务", "accept_821", 21102, 101)
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
		show_dialog(npc, menu_821_80);	
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
