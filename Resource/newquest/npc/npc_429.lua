local sq = the_script();
sq:add(ScriptQuest.NPC_VISIT, 429);

require "define821"

function visit_429(npc)
	return visit_npc(npc);
end

function state_429(npc)
	return state_npc(npc);
end