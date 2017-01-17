local sq = the_script();
sq:add(ScriptQuest.NPC_KILL, 10002);

function kill_10002(npc)
	print("kill");
	player = me();
	local v = player.quest:vars(20270);
	if not v then return 0; end
	
	local state = v:get("state");
	if state == 1 then
		local kill = v:get("kill_10002");
		
		if not kill then 
			v:set("kill_10002", 1); 
			return 1;
		end
		
		kill = kill + 1;
		v:set("kill_10002", kill);
		if kill >= 3 then
			v:set("state", -3);
			local tempid = v:get("npc");
			refresh_npc(tempid);
		end
		
		return 1;
	end
	return 0;
end
