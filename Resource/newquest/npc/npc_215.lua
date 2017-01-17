local sq = the_script();
sq:add(ScriptQuest.NPC_VISIT, 215);

local menu_215_1 = [[
function IsHasTask()
return true
end
function TaskDialog()
this:AddDialogItem("demo任务", "Dialog45")
end
function Dialog45()
this:AddTalk("去杀死....");
this:AddTaskCmdItem("接受任务", "accept_215", 20270, 1)
end

]]

local menu_215_2 = [[
function IsHasTask()
return true
end
function TaskDialog()
this:AddDialogItem("demo任务", "Dialog45")
end
function Dialog45()
this:AddTalk("恭喜。。。。");
this:AddTaskCmdItem("完成任务", "accept_215", 20270, 2)
end

]]

function visit_215(npc)
	player = me();
	local v = player.quest:vars(20270);
	if not v then
		show_dialog(npc, menu_215_1);	
		return 1;
	end

	local s = v:get("state");
	if s == -3 then
		show_dialog(npc, menu_215_2);	
		return 1;
	end	
	return 0;
end

function accept_215(npc, id, flag)
	print("accept");
	player = me();
	local v = player.quest:vars(id);
	if not v then
		v = Vars(id);
		v:set("state", 1);
		v:set("npc", npc:tempid());
		player.quest:add(20270, v, player, true);
		sys(player, 1, "接受了该任务");			
		npc:refresh();
		return 1;
	end
	
	local s = v:get("state");
	if s == -3 then
		sys(player, 1, "完成了该任务");		
		player:add_exp(100, false, 0, 0);	
		v:set("state", -1);	
		player.quest.refresh(id);	
		npc:refresh();	
		return 1;
	end
	
	return 0;
end

function state_215(npc)
	player = me();
	if not player then return 0; end
	
	local v = player.quest:vars(20270);
	if not v then
		print("start");
		return Quest.START;
	end

	local s = v:get("state");
	
	if s >= 1 then
		print("doing");
		return Quest.DOING;
	end

	if s == -3 then
		print("finish");
		return Quest.FINISH;
	end

	return 0;
end