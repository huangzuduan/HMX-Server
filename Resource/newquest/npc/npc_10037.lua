local sq = the_script();
sq:add(ScriptQuest.NPC_KILL, 10037);

require "define497"

function kill_10037(npc)
	
	player = me();
	local v = player.quest:vars(21102);
	if not v then return 0; end
	
	local s = v:get("state");
	local id = v:get("id");
	local type = v:get("type");
	
	print(npc:id());
	print(1);
	
	if s == 1 and id==npc:id() and type == 4 then
			--sys(player, 5, "成功击杀目标");
			if(math.random(1,10) <5) then
				player:add_ob(2005, 1, 0, 0);
			end
		return 1;
	end	

	
	return kill_npc(npc);
end
