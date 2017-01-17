local sq = the_script();
sq:add(ScriptQuest.NPC_VISIT, 427);

require "define821"

function visit_427(npc)
	return visit_npc(npc);
end

function state_427(npc)
	return state_npc(npc);
end