local sq = the_script();
sq:add(ScriptQuest.NPC_VISIT, 449);

require "define820"

function visit_449(npc)
	return visit_npc(npc);
end

function state_449(npc)
	return state_npc(npc);
end