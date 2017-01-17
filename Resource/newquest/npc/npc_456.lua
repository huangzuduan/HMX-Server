local sq = the_script();
sq:add(ScriptQuest.NPC_VISIT, 456);

require "define820"

function visit_456(npc)
	return visit_npc(npc);
end

function state_456(npc)
	return state_npc(npc);
end