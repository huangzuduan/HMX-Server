local sq = the_script();
sq:add(ScriptQuest.NPC_VISIT, 434);

require "define822"

function visit_434(npc)
	return visit_npc(npc);
end

function state_434(npc)
	return state_npc(npc);
end