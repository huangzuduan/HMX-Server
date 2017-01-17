local sq = the_script();
sq:add(ScriptQuest.NPC_VISIT, 439);

require "define820"

function visit_439(npc)
	return visit_npc(npc);
end

function state_439(npc)
	return state_npc(npc);
end