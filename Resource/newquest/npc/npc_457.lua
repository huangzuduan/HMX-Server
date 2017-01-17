local sq = the_script();
sq:add(ScriptQuest.NPC_VISIT, 457);

require "define821"

function visit_457(npc)
	return visit_npc(npc);
end

function state_457(npc)
	return state_npc(npc);
end