local sq = the_script();
sq:add(ScriptQuest.NPC_VISIT, 5104);

require "define891"
require "define888"
require "define889"

function visit_5104(npc)
	return visit_npc(npc);
end

function state_5104(npc)
	return state_npc(npc);
end