visit_npc_list150 = { {"凤尾村的阎乐", 422}, {"沼泽湿地的田文", 470}, {"皇城的李克用", 5103}, {"栖息地的杨继业", 5104} };
visit_npc_list1502 = { {"千江镇的赵普", 460}, {"凤祥镇西郊的杜康", 467}, {"魔族巢穴一层的朱全忠", 5101}, {"魔族巢穴一层的周保全", 5102} };

get_weapon_list150 = { {"145级白虎刀(白色)", 10317, 0}, {"145级白虎杖(白色)", 10517, 0}, {"145级白虎弓(白色)", 10567, 0}, {"145级白虎扇(白色)", 10617, 0}, {"145级白虎棍(白色)", 10667, 0} }; 
get_weapon_list1502 = { {"145级白虎刀(蓝色)", 10317, 1}, {"145级白虎杖(蓝色)", 10517, 1}, {"145级白虎弓(蓝色)", 10567, 1}, {"145级白虎扇(蓝色)", 10617, 1}, {"145级白虎棍(蓝色)", 10667, 1} }; 

kill_npc_list150 = { {"武夷王墓九层的150级守墓护卫", 16547}, {"武夷王墓十层的150级守墓战灵", 16550}, {"武夷王墓十层的150级护墓战灵", 16553}, {"魔族巢穴一层的150级月魔人", 16625} };
kill_npc_list1502 = { {"魔族巢穴二层的150级月魔法师", 16626}, {"魔族巢穴二层的155级月魔弓手", 16627}, {"魔族巢穴二层的155级月魔战士", 16628}, {"魔族巢穴二层的160级月魔统领", 16630} }; 

get_item_list150 = { {"干粮", 1908}, {"龙蛇草", 1835}, {"长白人参", 1871}, {"雪山灵芝", 1872}, {"天山雪莲", 1873} };
get_item_list1502 = { {"灵参果", 1874}, {"灵血腹蛇", 2407}, {"汗血宝马", 2408}, {"龟臣相", 2409}, {"凤凰鸟", 2410} };

kill_get_list = { {"杀兽王谷老虎获得10个虎头", 15014, 2098}, {"杀山寨前哨的山贼哨兵获得10件山贼染血衣", 10097, 2015}, {"杀山寨前哨的山贼战士获得10个山贼武器", 10098, 2016} };

kill_get_list2 = { {"杀龙冈山一寨的山贼弓手获得10个山贼武器", 10100, 2017}, {"杀龙冈山一寨的山贼护卫获得10件山贼染血衣", 10113, 2015}, {"杀龙冈山二寨的特级山贼获得10个山贼武器", 10109, 2017} };

kill_boss_list = { {"龙冈山一寨上的山贼刺客ID:16440", 16440} };

kill_boss_list2 = { {"龙冈山四寨上的山贼隐士ID:16441", 16441} };

menu_891_1 = [[
function IsHasTask()
return true
end
function TaskDialog()
this:AddTalk("    这是一个环式任务，一旦接了就不能删除，完成任务后可以找NPC领取奖励，每次的奖励根据完成的任务数量和任务所在的环数决定。\n\n    这是本环第#qs#个任务\n    这是今天的第#round#环。\n\n经验奖励：#exp#");
this:AddTaskCmdItem("接受任务", "accept_891", 21102, 1)
this:AddDialogItem("环任务存档(0)", "Dialog99")
this:AddTaskCmdItem("结束本日环任务", "accept_891", 21102, 102)
end
function Dialog99()
this:AddTalk("    你确定要将现在完成的环数存档么？\n    一旦存档，您必须先将档案取出才能继续环式任务。这将消耗您900点荣誉点。")
this:AddTaskCmdItem("确定存档-900荣誉值{10001}", "accept_891", 21102, 99)
end
function Dialog45()
this:AddTalk("帮我把这封信交给#place#，然后回来我给你奖励。");
end
function MoveCanClose()
	return true
end

]]

menu_891_2 = [[
function IsHasTask()
return true
end
function TaskDialog()
this:AddTalk("    这是一个环式任务，一旦接了就不能删除，完成任务后可以找NPC领取奖励，每次的奖励根据完成的任务数量和任务所在的环数决定。\n\n    这是本环第#qs#个任务\n    这是今天的第#round#环。\n\n经验奖励：#exp#");
this:AddTaskCmdItem("接受任务", "accept_891", 21102, 2)
this:AddDialogItem("环任务存档(0)", "Dialog99")
this:AddTaskCmdItem("结束本日环任务", "accept_891", 21102, 102)
end
function Dialog99()
this:AddTalk("    你确定要将现在完成的环数存档么？\n    一旦存档，您必须先将档案取出才能继续环式任务。这将消耗您100点荣誉点。")
this:AddTaskCmdItem("确定存档-900荣誉值{10001}", "accept_891", 21102, 99)
end
function Dialog45()
this:AddTalk("帮我杀#npc#5只，然后回来告诉我。");
end
function MoveCanClose()
	return true
end

]]

--收集物品任务
menu_891_3 = [[
function IsHasTask()
return true
end
function TaskDialog()
this:AddTalk("    这是一个环式任务，一旦接了就不能删除，完成任务后可以找NPC领取奖励，每次的奖励根据完成的任务数量和任务所在的环数决定。\n\n    这是本环第#qs#个任务\n    这是今天的第#round#环。\n\n经验奖励：#exp#");
this:AddTaskCmdItem("接受任务", "accept_891", 21102, 3)
this:AddDialogItem("环任务存档(0)", "Dialog99")
this:AddTaskCmdItem("结束本日环任务", "accept_891", 21102, 102)
end
function Dialog99()
this:AddTalk("    你确定要将现在完成的环数存档么？\n    一旦存档，您必须先将档案取出才能继续环式任务。这将消耗您100点荣誉点。")
this:AddTaskCmdItem("确定存档-900荣誉值{10001}", "accept_891", 21102, 99)
end
function Dialog45()
this:AddTalk("我需要3个#name#，全部找到后拿来给我。");
end
function MoveCanClose()
	return true
end

]]

menu_891_13 = [[
function IsHasTask()
return true
end
function TaskDialog()
this:AddTalk("    这是一个环式任务，一旦接了就不能删除，完成任务后可以找NPC领取奖励，每次的奖励根据完成的任务数量和任务所在的环数决定。\n\n    这是本环第#qs#个任务\n    这是今天的第#round#环。\n\n经验奖励：#exp#");
this:AddTaskCmdItem("接受任务", "accept_891", 21102, 13)
this:AddDialogItem("环任务存档(0)", "Dialog99")
this:AddTaskCmdItem("结束本日环任务", "accept_891", 21102, 102)
end
function Dialog99()
this:AddTalk("    你确定要将现在完成的环数存档么？\n    一旦存档，您必须先将档案取出才能继续环式任务。这将消耗您100点荣誉点。")
this:AddTaskCmdItem("确定存档-900荣誉值{10001}", "accept_891", 21102, 99)
end
function MoveCanClose()
	return true
end

]]

--收集装备接任务
menu_891_15 = [[
function IsHasTask()
return true
end
function TaskDialog()
this:AddTalk("    这是一个环式任务，一旦接了就不能删除，完成任务后可以找NPC领取奖励，每次的奖励根据完成的任务数量和任务所在的环数决定。\n\n    这是本环第#qs#个任务\n    这是今天的第#round#环。\n\n经验奖励：#exp#");
this:AddTaskCmdItem("接受任务", "accept_891", 21102, 15)
this:AddDialogItem("环任务存档(0)", "Dialog99")
this:AddTaskCmdItem("结束本日环任务", "accept_891", 21102, 102)
end
function Dialog99()
this:AddTalk("    你确定要将现在完成的环数存档么？\n    一旦存档，您必须先将档案取出才能继续环式任务。这将消耗您100点荣誉点。")
this:AddTaskCmdItem("确定存档-900荣誉值{10001}", "accept_891", 21102, 99)
end
function MoveCanClose()
	return true
end

]]

--杀BOSS接任务对话
menu_891_17 = [[
function IsHasTask()
return true
end
function TaskDialog()
this:AddTalk("    这是一个环式任务，一旦接了就不能删除，完成任务后可以找NPC领取奖励，每次的奖励根据完成的任务数量和任务所在的环数决定。\n\n    这是本环第#qs#个任务\n    这是今天的第#round#环。\n\n经验奖励：#exp#");
this:AddTaskCmdItem("接受任务", "accept_891", 21102, 17)
this:AddDialogItem("环任务存档(0)", "Dialog99")
this:AddTaskCmdItem("结束本日环任务", "accept_891", 21102, 102)
end
function Dialog99()
this:AddTalk("    你确定要将现在完成的环数存档么？\n    一旦存档，您必须先将档案取出才能继续环式任务。这将消耗您100点荣誉点。")
this:AddTaskCmdItem("确定存档-900荣誉值{10001}", "accept_891", 21102, 99)
end
function MoveCanClose()
	return true
end

]]

menu_891_23 = [[
function IsHasTask()
return true
end
function TaskDialog()
this:AddTalk("去#name#后给我。");
this:AddCloseItem("知道了")
end

]]

--收集装备通知
menu_891_45 = [[
function IsHasTask()
return true
end
function TaskDialog()
this:AddTalk("去收集一个#name#给我。");
this:AddCloseItem("知道了")
end

]]

menu_891_4 = [[
function IsHasTask()
return true
end
function TaskDialog()
this:AddTalk("我需要3个#name#，全部找到后拿来给我。");
this:AddCloseItem("知道了")
end

]]

menu_891_5 = [[
function IsHasTask()
return true
end
function TaskDialog()
this:AddTalk("帮我把这封信交给#place#，回来后我会给你奖励的。");
this:AddCloseItem("知道了")
end

]]

menu_891_6 = [[
function IsHasTask()
return true
end
function TaskDialog()
this:AddTalk("帮我杀#name#15只，然后回来告诉我。");
this:AddCloseItem("知道了")
end

]]

menu_891_7 = [[
function IsHasTask()
return true
end
function TaskDialog()
this:AddTalk("帮我杀#name#，然后回来告诉我。");
this:AddCloseItem("知道了")
end

]]


menu_891_11 = [[
function IsHasTask()
return true
end
function TaskDialog()
this:AddTalk("恭喜你完成了任务，你想现在领取奖励么？");
this:AddTaskCmdItem("接受奖励", "accept_891", 21102, 11)
end

]]

menu_891_8 = [[
function IsHasTask()
return true
end
function TaskDialog()
this:AddTalk("3个#name#，你已经收集好了么？");
this:AddTaskCmdItem("拿出物品", "accept_891", 21102, 8)
end

]]

menu_891_31 = [[
function IsHasTask()
return true
end
function TaskDialog()
this:AddTalk("10个那么快就弄到啦，真是太能干了，快给我。");
this:AddTaskCmdItem("拿出物品", "accept_891", 21102, 31)
end

]]

--收集装备任务交任务对话
menu_891_35 = [[
function IsHasTask()
return true
end
function TaskDialog()
this:AddTalk("#name#那么快就弄到啦，真是太能干了，快给我。");
this:AddTaskCmdItem("拿出物品", "accept_891", 21102, 35)
end

]]


menu_891_80 = [[
function IsHasTask()
return true
end
function TaskDialog()
this:AddTalk("信总算送来了，你回去告诉环式任务使者，我知道了。");
this:AddCloseItem("我这就去告诉他")
end

]]

menu_891_90 = [[
function IsHasTask()
return true
end
function TaskDialog()
this:AddTalk("    你今天能完成的环数已达到上限，下周六才能继续");
this:AddCloseItem("离开")
end

]]

menu_891_91 = [[
function IsHasTask()
return true
end
function TaskDialog()
this:AddTalk("    你还没有家族，无法接家族环式任务。");
this:AddCloseItem("离开")
end

]]

menu_891_92 = [[
function IsHasTask()
return true
end
function TaskDialog()
this:AddTalk("    你昨天任务已经结束，接下来将开始今天的环式任务。");
this:AddCloseItem("离开")
end

]]


menu_891_94 = [[
function IsHasTask()
return true
end
function TaskDialog()
this:AddTalk("    由于贵家族今天完成家族荣耀任务，因此您本日可以重新做一次家族环式任务，是否要现在开始呢？");
this:AddTaskCmdItem("再次开始本日家族环式任务", "accept_891", 21102, 94)
end

]]

menu_891_100 = [[
function IsHasTask()
return true
end
function TaskDialog()
this:AddTalk("    你确定要现在取出你的环式任务存档么？");
this:AddTaskCmdItem("取出存档", "accept_891", 21102, 100)
end

]]

menu_891_101 = [[
function IsHasTask()
return true
end
function TaskDialog()
this:AddTalk("    由于你离线时间过长，需要结束本日任务。");
this:AddTaskCmdItem("结束本日任务", "accept_891", 21102, 101)
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
		show_dialog(npc, menu_891_80);	
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
	player = me();
	local v = player.quest:vars(21102);
	if not v then return 0; end
	
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
