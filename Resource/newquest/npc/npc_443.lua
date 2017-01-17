local sq = the_script();
sq:add(ScriptQuest.NPC_VISIT, 443);

require "define820"

function visit_443(npc)
	return visit_npc(npc);
end

function state_443(npc)
	return state_npc(npc);
end