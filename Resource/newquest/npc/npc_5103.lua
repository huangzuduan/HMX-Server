local sq = the_script();
sq:add(ScriptQuest.NPC_VISIT, 5103);

require "define890"
require "define891"
require "define888"
require "define889"

function visit_5103(npc)
	return visit_npc(npc);
end

function state_5103(npc)
	return state_npc(npc);
end