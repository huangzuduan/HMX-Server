local sq = the_script();
sq:add(ScriptQuest.NPC_VISIT, 56003);

require "define"

function visit_56003(npc)
	return visit_npc(npc);
end

function state_56003(npc)
	return state_npc(npc);
end