local sq = the_script();
sq:add(ScriptQuest.NPC_VISIT, 450);

require "define820"

function visit_450(npc)
	return visit_npc(npc);
end

function state_450(npc)
	return state_npc(npc);
end