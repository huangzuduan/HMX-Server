local sq = the_script();
sq:add(ScriptQuest.NPC_VISIT, 454);

require "define823"

function visit_454(npc)
	return visit_npc(npc);
end

function state_454(npc)
	return state_npc(npc);
end