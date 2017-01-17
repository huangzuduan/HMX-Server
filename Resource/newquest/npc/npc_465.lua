local sq = the_script();
sq:add(ScriptQuest.NPC_VISIT, 465);

require "define823"

function visit_465(npc)
	return visit_npc(npc);
end

function state_465(npc)
	return state_npc(npc);
end