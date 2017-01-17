local sq = the_script();
sq:add(ScriptQuest.NPC_VISIT, 833);

menu_833_11 = [[
function IsHasTask()
return true
end
function TaskDialog()
this:AddTalk("   如果你环任务出现问题，我可以帮你清理一下，不过你今天的环任务将无法继续\n小提示：\n  做完当天所有的环任务后，可通过完成家族荣耀任务，获得重做环任务的权利。\n家族荣耀任务：\n  由族长在王城的家族管理员处发布荣耀任务，本家族成员可接，家族里只要有一个人完成荣耀任务，其他人就可以去家族管理员处领取重做环任务的权限。\n\n  家族荣耀任务每人每天只能做一次");
this:AddDialogItem("清理环任务(0)", "Dialog99")
end
function Dialog99()
this:AddTalk("    清理后您将无法再做今天的环任务，你确定要清理么？")
this:AddTaskCmdItem("我要清理", "accept_833", 21102, 11)
end
function MoveCanClose()
	return false
end

]]


--访问NPC开始
function visit_833(npc)
--任务判断	
	--print("begin visit");
	player = me();
	local v = player.quest:vars(21102);
	if not v then
		v = Vars(21102);
	end
	--print("begin level");
	local level = v:get("level");
	if not level then
		v:set("level", 1);
	end	
	--print("begin state");
	local s = v:get("state");
	if not s then
		v:set("state", 2);
	end
	--print("begin qss");
	local qss = v:get("finish_rounds");
	if not qss then
		v:set("finish_rounds", 1);
	end
	local qs = v:get("finish_quests"); 
	if not qs then
		v:set("finish_quests", 1);
	end
	
	--print("showdialog");
	show_dialog(npc, menu_833_11);	
	--print("passdialog");
	
	return 1;
end

--******************对话后的判断选项******************

function accept_833(npc, id, flag)
		player = me();

		local v = player.quest:vars(id);
		if not v then
		    return 1;
		end 
		local qss = v:get("finish_rounds");
		if not qss then
			v:set("finish_rounds", 1);
		end
		local qs = v:get("finish_quests"); 
		if not qs then
			v:set("finish_quests", 1);
		end

--重置环任务	
		if flag == 11 then
			sys(player, 1, "清理环式任务");		
			log2file(player, "清理环式任务成功");

			local uv = player:get_uservar(98);
				uv:set("todayend", 1);

			local qs = v:get("finish_quests");
			local qss = v:get("finish_rounds");
		
			v:set("finish_quests", 0); 
		  v:set("finish_rounds", 0); 
		  v:set("state",2);
		  v:set("level",1);
		  local xxxx="暂无任务";
			v:sets("text", xxxx);
			v:refresh(player,"text")
			player.quest.refresh(id);	
			
			npc:refresh();	
			--visit_833(npc);
			return 1;
		end		
		
	return 0;
end

function state_833(npc)
		player = me();

	--任务判断
		local v = player.quest:vars(21102);
		if not v then
			--print("no vars");
			v = Vars(21102);
		end

		local s = v:get("state");
		if not s then v:set("state",2); end
		local s = v:get("state");
		if not player then return 0; end
		
		local v = player.quest:vars(21102);
		if not v then
			return Quest.START;
		end
	
		local s = v:get("state");
		
		if s == 1 then
			--print("doing");
			return Quest.DOING;
		end
	
		if s == -3 then
			--print("finish");
			return Quest.FINISH;
		end

	return 0;
end