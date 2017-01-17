local sq = the_script();
sq:add(ScriptQuest.NPC_VISIT, 447);

require "define822"

function visit_447(npc)
	return visit_npc(npc);
end

function state_447(npc)
	return state_npc(npc);
end