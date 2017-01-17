local sq = the_script();
sq:add(ScriptQuest.NPC_VISIT, 438);

require "define820"

function visit_438(npc)
	return visit_npc(npc);
end

function state_438(npc)
	return state_npc(npc);
end