local sq = the_script();
sq:add(ScriptQuest.NPC_VISIT, 430);

require "define823"

function visit_430(npc)
	return visit_npc(npc);
end

function state_430(npc)
	return state_npc(npc);
end