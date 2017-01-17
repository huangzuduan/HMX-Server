local sq = the_script();
sq:add(ScriptQuest.NPC_VISIT, 462);

require "define825"
require "define888"
require "define889"
require "define890"

function visit_462(npc)
	return visit_npc(npc);
end

function state_462(npc)
	return state_npc(npc);
end