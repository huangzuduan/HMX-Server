local sq = the_script();
sq:add(ScriptQuest.NPC_VISIT, 467);

require "define825"
require "define889"
require "define890"
require "define891"

function visit_467(npc)
	return visit_npc(npc);
end

function state_467(npc)
	return state_npc(npc);
end