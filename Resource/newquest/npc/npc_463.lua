local sq = the_script();
sq:add(ScriptQuest.NPC_VISIT, 463);

require "define823"

function visit_463(npc)
	return visit_npc(npc);
end

function state_463(npc)
	return state_npc(npc);
end