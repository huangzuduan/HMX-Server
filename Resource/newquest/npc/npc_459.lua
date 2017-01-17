local sq = the_script();
sq:add(ScriptQuest.NPC_VISIT, 459);

require "define822"

function visit_459(npc)
	return visit_npc(npc);
end

function state_459(npc)
	return state_npc(npc);
end