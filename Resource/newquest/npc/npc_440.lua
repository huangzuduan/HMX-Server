local sq = the_script();
sq:add(ScriptQuest.NPC_VISIT, 440);

require "define822"
require "define888"

function visit_440(npc)
	return visit_npc(npc);
end

function state_440(npc)
	return state_npc(npc);
end