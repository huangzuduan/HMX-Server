local sq = the_script();
sq:add(ScriptQuest.NPC_VISIT, 446);

require "define821"

function visit_446(npc)
	return visit_npc(npc);
end

function state_446(npc)
	return state_npc(npc);
end