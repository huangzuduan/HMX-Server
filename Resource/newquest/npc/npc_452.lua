local sq = the_script();
sq:add(ScriptQuest.NPC_VISIT, 452);

require "define823"
require "define889"

function visit_452(npc)
	return visit_npc(npc);
end

function state_452(npc)
	return state_npc(npc);
end