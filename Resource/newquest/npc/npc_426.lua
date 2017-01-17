local sq = the_script();
sq:add(ScriptQuest.NPC_VISIT, 426);

require "define821"

function visit_426(npc)
	return visit_npc(npc);
end

function state_426(npc)
	return state_npc(npc);
end