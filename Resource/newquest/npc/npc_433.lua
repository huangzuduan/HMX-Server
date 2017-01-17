local sq = the_script();
sq:add(ScriptQuest.NPC_VISIT, 433);

require "define820"

function visit_433(npc)
	return visit_npc(npc);
end

function state_433(npc)
	return state_npc(npc);
end