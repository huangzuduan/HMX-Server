local sq = the_script();
sq:add(ScriptQuest.NPC_VISIT, 442);

require "define821"

function visit_442(npc)
	return visit_npc(npc);
end

function state_442(npc)
	return state_npc(npc);
end