visit_npc_list120 = { {"千江镇的来俊臣", 462}, {"凤祥镇的霍光", 451}, {"凤尾村的李斯", 421}, {"皇城的李克用", 5103} };
visit_npc_list1202 = { {"清源村的高渐离", 440}, {"凤尾村的阎乐", 422}, {"千江镇的赵高", 461}, {"栖息地的杨继业", 5104} };

get_weapon_list120 = { {"115级血魔刀(白色)", 10312, 0}, {"115级血魔杖(白色)", 10512, 0}, {"115级血魔弓(白色)", 10562, 0}, {"115级血魔扇(白色)", 10612, 0}, {"115级血魔棍(白色)", 10662, 0} }; 
get_weapon_list1202 = { {"115级血魔刀(蓝色)", 10312, 1}, {"115级血魔杖(蓝色)", 10512, 1}, {"115级血魔弓(蓝色)", 10562, 1}, {"115级血魔扇(蓝色)", 10612, 1}, {"115级血魔棍(蓝色)", 10662, 1} }; 

kill_npc_list120 = { {"蛟龙洞二层的120级狂战侏儒", 16121}, {"皇城的120级异域叛兵", 16455}, {"武夷王墓五层的120级骸骨士兵", 16529} };
kill_npc_list1202 = { {"武夷王墓五层的120级魔化犬戎", 16526}, {"武夷王墓六层的125级骸骨卫兵", 16530}, {"武夷王墓六层的125级骸骨祭师", 16532}, {"千江镇的125级高级打手", 16603} }; 

get_item_list120 = { {"大荔枝", 1878}, {"精致的兽皮", 1805}, {"金苹果", 1864}, {"天空梨", 1865}, {"蟠桃", 1866} };
get_item_list1202 = { {"蓬莱荔枝", 1867}, {"斗鸡", 2401}, {"天鹅", 2402}, {"军犬", 2403}, {"斗牛", 2404} };

kill_get_list = { {"杀兽王谷老虎获得10个虎头", 15014, 2098}, {"杀山寨前哨的山贼哨兵获得10件山贼染血衣", 10097, 2015}, {"杀山寨前哨的山贼战士获得10个山贼武器", 10098, 2016} };

kill_get_list2 = { {"杀龙冈山一寨的山贼弓手获得10个山贼武器", 10100, 2017}, {"杀龙冈山一寨的山贼护卫获得10件山贼染血衣", 10113, 2015}, {"杀龙冈山二寨的特级山贼获得10个山贼武器", 10109, 2017} };

kill_boss_list = { {"龙冈山一寨上的山贼刺客ID:16440", 16440} };

kill_boss_list2 = { {"龙冈山四寨上的山贼隐士ID:16441", 16441} };

menu_888_1 = [[
function IsHasTask()
return true
end
function TaskDialog()
this:AddTalk("    这是一个环式任务，一旦接了就不能删除，完成任务后可以找NPC领取奖励，每次的奖励根据完成的任务数量和任务所在的环数决定。\n\n    这是本环第#qs#个任务\n    这是今天的第#round#环。\n\n经验奖励：#exp#");
this:AddTaskCmdItem("接受任务", "accept_888", 21102, 1)
this:AddDialogItem("环任务存档(0)", "Dialog99")
this:AddTaskCmdItem("结束本日环任务", "accept_888", 21102, 102)
end
function Dialog99()
this:AddTalk("    你确定要将现在完成的环数存档么？\n    一旦存档，您必须先将档案取出才能继续环式任务。这将消耗您900点荣誉点。")
this:AddTaskCmdItem("确定存档-900荣誉值{10001}", "accept_888", 21102, 99)
end
function Dialog45()
this:AddTalk("帮我把这封信交给#place#，然后回来我给你奖励。");
end
function MoveCanClose()
	return true
end

]]

menu_888_2 = [[
function IsHasTask()
return true
end
function TaskDialog()
this:AddTalk("    这是一个环式任务，一旦接了就不能删除，完成任务后可以找NPC领取奖励，每次的奖励根据完成的任务数量和任务所在的环数决定。\n\n    这是本环第#qs#个任务\n    这是今天的第#round#环。\n\n经验奖励：#exp#");
this:AddTaskCmdItem("接受任务", "accept_888", 21102, 2)
this:AddDialogItem("环任务存档(0)", "Dialog99")
this:AddTaskCmdItem("结束本日环任务", "accept_888", 21102, 102)
end
function Dialog99()
this:AddTalk("    你确定要将现在完成的环数存档么？\n    一旦存档，您必须先将档案取出才能继续环式任务。这将消耗您100点荣誉点。")
this:AddTaskCmdItem("确定存档-900荣誉值{10001}", "accept_888", 21102, 99)
end
function Dialog45()
this:AddTalk("帮我杀#npc#5只，然后回来告诉我。");
end
function MoveCanClose()
	return true
end

]]

--收集物品任务
menu_888_3 = [[
function IsHasTask()
return true
end
function TaskDialog()
this:AddTalk("    这是一个环式任务，一旦接了就不能删除，完成任务后可以找NPC领取奖励，每次的奖励根据完成的任务数量和任务所在的环数决定。\n\n    这是本环第#qs#个任务\n    这是今天的第#round#环。\n\n经验奖励：#exp#");
this:AddTaskCmdItem("接受任务", "accept_888", 21102, 3)
this:AddDialogItem("环任务存档(0)", "Dialog99")
this:AddTaskCmdItem("结束本日环任务", "accept_888", 21102, 102)
end
function Dialog99()
this:AddTalk("    你确定要将现在完成的环数存档么？\n    一旦存档，您必须先将档案取出才能继续环式任务。这将消耗您100点荣誉点。")
this:AddTaskCmdItem("确定存档-900荣誉值{10001}", "accept_888", 21102, 99)
end
function Dialog45()
this:AddTalk("我需要3个#name#，全部找到后拿来给我。");
end
function MoveCanClose()
	return true
end

]]

menu_888_13 = [[
function IsHasTask()
return true
end
function TaskDialog()
this:AddTalk("    这是一个环式任务，一旦接了就不能删除，完成任务后可以找NPC领取奖励，每次的奖励根据完成的任务数量和任务所在的环数决定。\n\n    这是本环第#qs#个任务\n    这是今天的第#round#环。\n\n经验奖励：#exp#");
this:AddTaskCmdItem("接受任务", "accept_888", 21102, 13)
this:AddDialogItem("环任务存档(0)", "Dialog99")
this:AddTaskCmdItem("结束本日环任务", "accept_888", 21102, 102)
end
function Dialog99()
this:AddTalk("    你确定要将现在完成的环数存档么？\n    一旦存档，您必须先将档案取出才能继续环式任务。这将消耗您100点荣誉点。")
this:AddTaskCmdItem("确定存档-900荣誉值{10001}", "accept_888", 21102, 99)
end
function MoveCanClose()
	return true
end

]]

--收集装备接任务
menu_888_15 = [[
function IsHasTask()
return true
end
function TaskDialog()
this:AddTalk("    这是一个环式任务，一旦接了就不能删除，完成任务后可以找NPC领取奖励，每次的奖励根据完成的任务数量和任务所在的环数决定。\n\n    这是本环第#qs#个任务\n    这是今天的第#round#环。\n\n经验奖励：#exp#");
this:AddTaskCmdItem("接受任务", "accept_888", 21102, 15)
this:AddDialogItem("环任务存档(0)", "Dialog99")
this:AddTaskCmdItem("结束本日环任务", "accept_888", 21102, 102)
end
function Dialog99()
this:AddTalk("    你确定要将现在完成的环数存档么？\n    一旦存档，您必须先将档案取出才能继续环式任务。这将消耗您100点荣誉点。")
this:AddTaskCmdItem("确定存档-900荣誉值{10001}", "accept_888", 21102, 99)
end
function MoveCanClose()
	return true
end

]]

--杀BOSS接任务对话
menu_888_17 = [[
function IsHasTask()
return true
end
function TaskDialog()
this:AddTalk("    这是一个环式任务，一旦接了就不能删除，完成任务后可以找NPC领取奖励，每次的奖励根据完成的任务数量和任务所在的环数决定。\n\n    这是本环第#qs#个任务\n    这是今天的第#round#环。\n\n经验奖励：#exp#");
this:AddTaskCmdItem("接受任务", "accept_888", 21102, 17)
this:AddDialogItem("环任务存档(0)", "Dialog99")
this:AddTaskCmdItem("结束本日环任务", "accept_888", 21102, 102)
end
function Dialog99()
this:AddTalk("    你确定要将现在完成的环数存档么？\n    一旦存档，您必须先将档案取出才能继续环式任务。这将消耗您100点荣誉点。")
this:AddTaskCmdItem("确定存档-900荣誉值{10001}", "accept_888", 21102, 99)
end
function MoveCanClose()
	return true
end

]]

menu_888_23 = [[
function IsHasTask()
return true
end
function TaskDialog()
this:AddTalk("去#name#后给我。");
this:AddCloseItem("知道了")
end

]]

--收集装备通知
menu_888_45 = [[
function IsHasTask()
return true
end
function TaskDialog()
this:AddTalk("去收集一个#name#给我。");
this:AddCloseItem("知道了")
end

]]

menu_888_4 = [[
function IsHasTask()
return true
end
function TaskDialog()
this:AddTalk("我需要3个#name#，全部找到后拿来给我。");
this:AddCloseItem("知道了")
end

]]

menu_888_5 = [[
function IsHasTask()
return true
end
function TaskDialog()
this:AddTalk("帮我把这封信交给#place#，回来后我会给你奖励的。");
this:AddCloseItem("知道了")
end

]]

menu_888_6 = [[
function IsHasTask()
return true
end
function TaskDialog()
this:AddTalk("帮我杀#name#15只，然后回来告诉我。");
this:AddCloseItem("知道了")
end

]]

menu_888_7 = [[
function IsHasTask()
return true
end
function TaskDialog()
this:AddTalk("帮我杀#name#，然后回来告诉我。");
this:AddCloseItem("知道了")
end

]]


menu_888_11 = [[
function IsHasTask()
return true
end
function TaskDialog()
this:AddTalk("恭喜你完成了任务，你想现在领取奖励么？");
this:AddTaskCmdItem("接受奖励", "accept_888", 21102, 11)
end

]]

menu_888_8 = [[
function IsHasTask()
return true
end
function TaskDialog()
this:AddTalk("3个#name#，你已经收集好了么？");
this:AddTaskCmdItem("拿出物品", "accept_888", 21102, 8)
end

]]

menu_888_31 = [[
function IsHasTask()
return true
end
function TaskDialog()
this:AddTalk("10个那么快就弄到啦，真是太能干了，快给我。");
this:AddTaskCmdItem("拿出物品", "accept_888", 21102, 31)
end

]]

--收集装备任务交任务对话
menu_888_35 = [[
function IsHasTask()
return true
end
function TaskDialog()
this:AddTalk("#name#那么快就弄到啦，真是太能干了，快给我。");
this:AddTaskCmdItem("拿出物品", "accept_888", 21102, 35)
end

]]


menu_888_80 = [[
function IsHasTask()
return true
end
function TaskDialog()
this:AddTalk("信总算送来了，你回去告诉环式任务使者，我知道了。");
this:AddCloseItem("我这就去告诉他")
end

]]

menu_888_90 = [[
function IsHasTask()
return true
end
function TaskDialog()
this:AddTalk("    你今天能完成的环数已达到上限，下周六才能继续");
this:AddCloseItem("离开")
end

]]

menu_888_91 = [[
function IsHasTask()
return true
end
function TaskDialog()
this:AddTalk("    你还没有家族，无法接家族环式任务。");
this:AddCloseItem("离开")
end

]]

menu_888_92 = [[
function IsHasTask()
return true
end
function TaskDialog()
this:AddTalk("    你昨天任务已经结束，接下来将开始今天的环式任务。");
this:AddCloseItem("离开")
end

]]


menu_888_94 = [[
function IsHasTask()
return true
end
function TaskDialog()
this:AddTalk("    由于贵家族今天完成家族荣耀任务，因此您本日可以重新做一次家族环式任务，是否要现在开始呢？");
this:AddTaskCmdItem("再次开始本日家族环式任务", "accept_888", 21102, 94)
end

]]

menu_888_100 = [[
function IsHasTask()
return true
end
function TaskDialog()
this:AddTalk("    你确定要现在取出你的环式任务存档么？");
this:AddTaskCmdItem("取出存档", "accept_888", 21102, 100)
end

]]

menu_888_101 = [[
function IsHasTask()
return true
end
function TaskDialog()
this:AddTalk("    由于你离线时间过长，需要结束本日任务。");
this:AddTaskCmdItem("结束本日任务", "accept_888", 21102, 101)
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
		show_dialog(npc, menu_888_80);	
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
	
	
		local s = v:get("state");
		local id = v:get("id");
		local item = v:get("item");
		local type = v:get("type");
		
	return 0;
end

function gain_exp(player, qs, qss)
		local baseexp = 2*player.charbase.level*player.charbase.level;
		local exp = 15*baseexp*(0.5+0.25*(qs + qss));
	player:add_exp(exp, false, 0, 0, false);
end
