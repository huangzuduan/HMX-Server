local sq = the_script();
sq:add(ScriptQuest.NPC_VISIT, 441);

require "define821"

function visit_441(npc)
	return visit_npc(npc);
end

function state_441(npc)
	return state_npc(npc);
end