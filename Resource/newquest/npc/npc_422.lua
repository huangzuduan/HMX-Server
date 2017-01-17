local sq = the_script();
sq:add(ScriptQuest.NPC_VISIT, 422);

require "define822"
require "define888"
require "define889"
require "define891"

function visit_422(npc)
	return visit_npc(npc);
end

function state_422(npc)
	return state_npc(npc);
end