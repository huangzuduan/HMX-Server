local sq = the_script();
sq:add(ScriptQuest.NPC_VISIT, 451);

require "define822"
require "define888"

function visit_451(npc)
	return visit_npc(npc);
end

function state_451(npc)
	return state_npc(npc);
end