LUA_PATH = "./newquest/?.lua";
print("可以进游戏啦~~");
require "npc/npc_421";
require "QmrQuest/qmrquest";
require "npc/npc_422";
require "npc/npc_423";
require "npc/npc_424";
require "npc/npc_425";
require "npc/npc_426";
require "npc/npc_427";
require "npc/npc_428";
require "npc/npc_429";
require "npc/npc_430";
require "npc/npc_431";
require "npc/npc_432";

require "npc/npc_433";

require "npc/npc_434";

require "npc/npc_435";

require "npc/npc_436";

require "npc/npc_437";

require "npc/npc_440";

require "npc/npc_441";

require "npc/npc_442";

require "npc/npc_443";

require "npc/npc_444";

require "npc/npc_447";

require "npc/npc_448";

require "npc/npc_449";

require "npc/npc_450";

require "npc/npc_451";

require "npc/npc_452";

require "npc/npc_453";

require "npc/npc_454";

require "npc/npc_455";

require "npc/npc_456";

require "npc/npc_457";

require "npc/npc_460";

require "npc/npc_461";

require "npc/npc_462";

require "npc/npc_463";

require "npc/npc_464";

require "npc/npc_467";

require "npc/npc_469";

require "npc/npc_470";

require "npc/npc_497";

require "npc/npc_820";

require "npc/npc_821";

require "npc/npc_822";

require "npc/npc_823";

require "npc/npc_825";

require "npc/npc_833";

require "npc/npc_888";

require "npc/npc_889";

require "npc/npc_890";

require "npc/npc_891";

require "npc/npc_5101";

require "npc/npc_5102";

require "npc/npc_5103";

require "npc/npc_5104";



require "npc/npc_10204";

require "npc/npc_10207";

require "npc/npc_10216";

require "npc/npc_10219";

require "npc/npc_10221";

require "npc/npc_10229";

require "npc/npc_10230";

require "npc/npc_15022";

require "npc/npc_15030";

require "npc/npc_15037";

require "npc/npc_15094";

require "npc/npc_15147";

require "npc/npc_15150";

require "npc/npc_15156";

require "npc/npc_15170";

require "npc/npc_15173";

require "npc/npc_15176";

require "npc/npc_16034";

require "npc/npc_16047";

require "npc/npc_16071";

require "npc/npc_16106";

require "npc/npc_16110";

require "npc/npc_16113";

require "npc/npc_16118";

require "npc/npc_16121";

require "npc/npc_16215";

require "npc/npc_16219";

require "npc/npc_16231";

require "npc/npc_16236";

require "npc/npc_16241";

require "npc/npc_16256";

require "npc/npc_16261";

require "npc/npc_16309";

require "npc/npc_16313";

require "npc/npc_16317";

require "npc/npc_16348";

require "npc/npc_16452";

require "npc/npc_16455";

require "npc/npc_16461";

require "npc/npc_16465";

require "npc/npc_16469";

require "npc/npc_16476";

require "npc/npc_16482";

require "npc/npc_16486";

require "npc/npc_16526";

require "npc/npc_16529";

require "npc/npc_16530";

require "npc/npc_16532";

require "npc/npc_16533";

require "npc/npc_16534";

require "npc/npc_16535";

require "npc/npc_16536";

require "npc/npc_16537";

require "npc/npc_16538";

require "npc/npc_16541";

require "npc/npc_16544";

require "npc/npc_16547";

require "npc/npc_16579";

require "npc/npc_16550";

require "npc/npc_16553";

require "npc/npc_16583";

require "npc/npc_16589";
require "npc/npc_16603";
require "npc/npc_16604";
require "npc/npc_16609";
require "npc/npc_16621";
require "npc/npc_16622";
require "npc/npc_16623";
require "npc/npc_16624";
require "npc/npc_16625";
require "npc/npc_16626";
require "npc/npc_16627";
require "npc/npc_16628";
require "npc/npc_16630";
function enter()
        --print("enter");
	player = me();
        --sys(player, 1, "进入游戏");	
			
 return 1;
end
function quit()
	player = me();
	--sys(player, 1, "退出测试");		
	return 1;
end
function die()
        --print("die");
	--player = me();
	--sys(player, 1, "死亡测试");		
	return 1;
end