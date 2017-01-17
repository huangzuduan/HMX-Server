local sq = the_script();
sq:add(ScriptQuest.NPC_VISIT, 432);

require "define820"

function visit_432(npc)
	return visit_npc(npc);
end

function state_432(npc)
	return state_npc(npc);
end