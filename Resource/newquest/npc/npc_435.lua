local sq = the_script();
sq:add(ScriptQuest.NPC_VISIT, 435);

require "define823"

function visit_435(npc)
	return visit_npc(npc);
end

function state_435(npc)
	return state_npc(npc);
end