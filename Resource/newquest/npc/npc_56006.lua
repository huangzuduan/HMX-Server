local sq = the_script();
sq:add(ScriptQuest.NPC_VISIT, 56006);

require "define"

function visit_56006(npc)
	return visit_npc(npc);
end

function state_56006(npc)
	return state_npc(npc);
end