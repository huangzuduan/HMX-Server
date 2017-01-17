local sq = the_script();
sq:add(ScriptQuest.NPC_VISIT, 425);

require "define822"

function visit_425(npc)
	return visit_npc(npc);
end

function state_425(npc)
	return state_npc(npc);
end