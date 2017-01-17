local sq = the_script();
sq:add(ScriptQuest.NPC_VISIT, 421);

require "define822"
require "define888"

function visit_421(npc)
	return visit_npc(npc);
end

function state_421(npc)
	return state_npc(npc);
end