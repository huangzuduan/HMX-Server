local sq = the_script();
sq:add(ScriptQuest.NPC_VISIT, 466);

require "define823"

function visit_466(npc)
	return visit_npc(npc);
end

function state_466(npc)
	return state_npc(npc);
end