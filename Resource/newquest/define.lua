--visit_npc_list = { {"清源村的56001", 56001}, {"清源村的56003", 56003}, {"清源村的56006", 56006} };
--kill_npc_list = { {"动物50007", 50007}, {"动物50021", 50021}, {"动物10038", 10038} };
--get_item_list = { {"兽耳", 1800}, {"羽毛", 1801}, {"兽毛", 1802} };
--kill_get_list = { {"杀50007获得1800兽耳", 50007, 1800}, {"杀50021获得1801羽毛", 50021, 1801}, {"杀10038获得1802兽耳", 10038, 1802} };

menu_247_1 = [[
function IsHasTask()
return true
end
function TaskDialog()
this:AddTalk("这是一个环式任务，一旦接了就不能删除，完成任务后可以找接任务的NPC领取奖励，每天只能接一次，你是否要开始今天的任务。");
this:AddTaskCmdItem("接受任务", "accept_247", 21101, 1)
end
function Dialog45()
this:AddTalk("帮我把这封信交给#place#，然后回来我回给你奖励的。");
end
function MoveCanClose()
	return false
end

]]

menu_247_2 = [[
function IsHasTask()
return true
end
function TaskDialog()
this:AddTalk("这是一个环式任务，一旦接了就不能删除，完成任务后可以找接任务的NPC领取奖励，每天只能接一次，你是否要开始今天的任务。");
this:AddTaskCmdItem("接受任务", "accept_247", 21101, 2)
end
function Dialog45()
this:AddTalk("帮我杀#npc#怪物5只，然后回来告诉我。");
end
function MoveCanClose()
	return false
end

]]


menu_247_3 = [[
function IsHasTask()
return true
end
function TaskDialog()
this:AddTalk("这是一个环式任务，一旦接了就不能删除，完成任务后可以找接任务的NPC领取奖励，每天只能接一次，你是否要开始今天的任务。");
this:AddTaskCmdItem("接受任务", "accept_247", 21101, 3)
end
function Dialog45()
this:AddTalk("我需要3个#name#，物品ID为#id#，全部找到后拿来给我。");
end
function MoveCanClose()
	return false
end

]]

menu_247_13 = [[
function IsHasTask()
return true
end
function TaskDialog()
this:AddTalk("这是一个环式任务，一旦接了就不能删除，完成任务后可以找接任务的NPC领取奖励，每天只能接一次，你是否要开始今天的任务。");
this:AddTaskCmdItem("接受任务", "accept_247", 21101, 13)
end
function MoveCanClose()
	return false
end

]]

menu_247_23 = [[
function IsHasTask()
return true
end
function TaskDialog()
this:AddTalk("#name#，要杀的怪物为#kill#，拿到3个#item#后给我。");
end

]]

menu_247_4 = [[
function IsHasTask()
return true
end
function TaskDialog()
this:AddTalk("我需要3个#name#，物品ID为#id#，全部找到后拿来给我。");
end

]]

menu_247_5 = [[
function IsHasTask()
return true
end
function TaskDialog()
this:AddTalk("帮我把这封信交给#place#，然后回来我回给你奖励的。");
end

]]

menu_247_6 = [[
function IsHasTask()
return true
end
function TaskDialog()
this:AddTalk("帮我杀#npc#怪物5只，然后回来告诉我。");
end

]]


menu_247_11 = [[
function IsHasTask()
return true
end
function TaskDialog()
this:AddTalk("恭喜你完成了任务，这是你的奖励");
end

]]

menu_247_8 = [[
function IsHasTask()
return true
end
function TaskDialog()
this:AddTalk("3个#name#，物品ID为#id#，你已经收集好了么？");
this:AddTaskCmdItem("交出物品", "accept_247", 21101, 8)
end

]]


menu_247_80 = [[
function IsHasTask()
return true
end
function TaskDialog()
this:AddTalk("信总算送来了，你回去告诉他我知道了。");
end

]]

function visit_npc(npc)
	--print("visit");
	player = me();
	local v = player.quest:vars(21101);
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
		show_dialog(npc, menu_247_80);	
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
	
	local v = player.quest:vars(21101);
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
	local v = player.quest:vars(21101);
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
		if not kill then 
			v:set("kills", 1); 
		else		
			v:set("kills", kill+1);
			if (kill+1) >= 3 then
				sys(player, 1, "恭喜你完成了一个任务");
				v:set("state", -3);
				local tempid = v:get("npc");
				refresh_npc(tempid);
			end
		end
				
		return 1;
	end
	
	

	
	return 0;
end




function get_object(object)
	--print("get_ob");
	player = me();
	local v = player.quest:vars(21101);
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
				--sys(player, 1, "又拿到了");
			else		
				v:set("item_nums", get+1);
				--sys(player, 1, "又拿到了");
				if get >= 2 then
					sys(player, 1, "恭喜你收集了足够的物品");
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
		
			--print(5);
			--print(s);
			--print(type);
			--print(id);
			--print(item);
	
		--if s == 1 and id==npc:id() and item==npc:item() and type == 4 then
		if s == 1 and type == 4 then

			local get = v:get("item_nums");
			
			--print(2);
			if not get then 
				v:set("item_nums", 1); 
				sys(player, 5, "拿到了");
			else		
				v:set("item_nums", get+1);
				sys(player, 5, "拿到了");
				if get >= 2 then
					sys(player, 1, "恭喜你收集了足够的物品");
					v:set("state", -3);
					player:remove_ob(item, 3, 0);
					local tempid = v:get("item");
					refresh_npc(tempid);
				end
			end
				
			return 1;
		end
	
	return 0;
end

BASE_EXP = 90;
BASE_NUM = 5;

function gain_exp(player, qs)
	local exp = BASE_EXP*player.charbase.level*(0.8+0.2*math.mod(qs, BASE_NUM)*(qs/BASE_NUM));
	player:add_exp(exp, false, 0, 0, false);
end
