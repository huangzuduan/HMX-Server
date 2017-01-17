local sq = the_script();
sq:add(ScriptQuest.NPC_VISIT, 423);

require "define821"

function visit_423(npc)
	return visit_npc(npc);
end

function state_423(npc)
	return state_npc(npc);
end