local sq = the_script();
sq:add(ScriptQuest.NPC_VISIT, 56001);

require "define"

function visit_56001(npc)
	return visit_npc(npc);
end

function state_56001(npc)
	return state_npc(npc);
end