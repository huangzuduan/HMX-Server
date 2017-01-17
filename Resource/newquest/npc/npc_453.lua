local sq = the_script();
sq:add(ScriptQuest.NPC_VISIT, 453);

require "define822"

function visit_453(npc)
	return visit_npc(npc);
end

function state_453(npc)
	return state_npc(npc);
end