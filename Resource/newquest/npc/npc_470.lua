local sq = the_script();
sq:add(ScriptQuest.NPC_VISIT, 470);

require "define825"
require "define890"
require "define891"

function visit_470(npc)
	return visit_npc(npc);
end

function state_470(npc)
	return state_npc(npc);
end