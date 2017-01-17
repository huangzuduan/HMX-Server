local sq = the_script();
sq:add(ScriptQuest.NPC_VISIT, 247);

require "define"

function select_quest(npc,v)
	local type = math.random(3, 4);
	 --if type ==3 then type = 4 end;
	local id = 0;
	local r = 0;
	local menu = "";
	if type == 1 then
		r = math.random(1, table.getn(visit_npc_list));
		menu = string.gsub(menu_247_1, "#place#", visit_npc_list[r][1]);	
		menu = 	string.gsub(menu, "#npc#", visit_npc_list[r][2]);
		id = visit_npc_list[r][2];
		v:set("questnpc", r);
		print("type=1 npc");
	end
	
	if type == 2 then
		r = math.random(1, table.getn(kill_npc_list));
		menu = string.gsub(menu_247_2, "#name#", kill_npc_list[r][1]);
		menu = 	string.gsub(menu, "#npc#", kill_npc_list[r][2]);
		id = kill_npc_list[r][2]; 
		v:set("questkill", r);
		print("type=2 kill");
	end
	
	if type == 3 then
		r = math.random(1, table.getn(get_item_list));
		menu = string.gsub(menu_247_3, "#name#", get_item_list[r][1]);	
		menu = 	string.gsub(menu, "#id#", get_item_list[r][2]);
		id = get_item_list[r][2];
	  v:set("questobject", r);
	  print(id);
	end
	
	if type == 4 then
		r = math.random(1, table.getn(kill_get_list));
		print(r);
		menu = string.gsub(menu_247_13, "#name#", kill_get_list[r][1]);	
		menu = 	string.gsub(menu, "#kill#", kill_get_list[r][2]);
		menu = 	string.gsub(menu, "#item#", kill_get_list[r][3]);
		id = kill_get_list[r][2];
		item = kill_get_list[r][3];
		print(item);
		v:set("item",item);
	  v:set("questkillobject", r);
	end
	
	
	show_dialog(npc, menu);	
	print(type);
	print(id);

	return type, id;
end

function visit_247(npc)
	print("visiting");
	player = me();
	if player.charbase.level < 40 or player.charbase.level > 50 then
		return 0;
	end
	
	local v = player.quest:vars(21101);
	if not v then
		print("no vars");
		v = Vars(21101);
		local type, id = select_quest(npc,v);
		
		v:set("type", type);
		v:set("id", id);
		v:set("state", 2);
		v:set("npc", npc:tempid());
		player.quest:add(21101, v, player, true);
--		sys(player, 1, "接受了一个任务");
		npc:refresh();
		return 1;
	end

	local s = v:get("state");
	local type = v:get("type");

	if s == 1 and type == 1 then
		print("s=1");
			local r=v:get("questnpc");
			menu = string.gsub(menu_247_5, "#place#", visit_npc_list[r][1]);	
			menu = 	string.gsub(menu, "#npc#", visit_npc_list[r][2]);
			show_dialog(npc, menu);
		return 1;	
	end	

	if s == 1 and type == 2 then
		print("s=1");
			local r=v:get("questkill");
			menu = string.gsub(menu_247_6, "#name#", kill_npc_list[r][1]);
			menu = 	string.gsub(menu, "#npc#", kill_npc_list[r][2]);
			show_dialog(npc, menu);
		return 1;	
	end	
	
	if s == 1 and type == 3 then
		--print("type=3");
			local r=v:get("questobject");
			menu = string.gsub(menu_247_8, "#name#", get_item_list[r][1]);	
			menu = 	string.gsub(menu, "#id#", get_item_list[r][2]);
			show_dialog(npc, menu);
		return 1;	
	end	
	
	if s == 1 and type == 3 then
		--print("type=3");
			local r=v:get("questobject");
			menu = string.gsub(menu_247_4, "#name#", get_item_list[r][1]);	
			menu = 	string.gsub(menu, "#id#", get_item_list[r][2]);
			show_dialog(npc, menu);
		return 1;	
	end	

	if s == 1 and type == 4 then
		print("s=1");
			local r=v:get("questkillobject");
			menu = string.gsub(menu_247_23, "#name#", kill_get_list[r][1]);	
			menu = 	string.gsub(menu, "#kill#", kill_get_list[r][2]);
			menu = 	string.gsub(menu, "#item#", kill_get_list[r][3]);
			show_dialog(npc, menu);
		return 1;	
	end	
			
	if s == -3 then
		print("s=-3");
		show_dialog(npc, menu_247_11);
		local qs = v:get("finish_quests");
			if not qs then
				v:set("finish_quests", 1);
			else
				v:set("finish_quests", qs+1);
			end
		
			v:set("state", 2);
			v:set("kills", 0);
			v:set("item_nums", 0);
			npc:refresh();
		
			if qs == 1 then
				sys(player, 1, "本环还有4个任务");
			end
				
			if qs == 2 then
				sys(player, 1, "本环还有3个任务");
			end
				
			if qs == 3 then
				sys(player, 1, "本环还有2个任务");
			end
				
			if qs == 4 then
				sys(player, 1, "本环还有最后1个任务");
			end
			
			
			if math.mod(qs+1, 5) == 0 then
				sys(player, 1, "完成了一个环");
				v:set("qs", 0);
				npc:refresh();
			end
			
			gain_exp(player, qs+1);
			
		return 1;		
	end
	
	
	if s == 2 then
		local type, id = select_quest(npc,v);
		v:set("type", type);
		v:set("id", id);
--		v:set("state", 1);
		v:set("npc", npc:tempid());
--		npc:refresh();	
		return 1;
	end;
	
	return 0;
end

function accept_247(npc, id, flag)
		local v = player.quest:vars(id);
		if( v:get("state") == 2) and flag == 1 then
			local r=v:get("questnpc");
			v:set("state",1);
			menu = string.gsub(menu_247_5, "#place#", visit_npc_list[r][1]);	
			menu = 	string.gsub(menu, "#npc#", visit_npc_list[r][2]);
			show_dialog(npc, menu);
			player:add_ob(2068, 1, 0, 0);
			sys(player, 1, "接受了该任务");			
			npc:refresh();
			return 1;
		end
	  
	  if( v:get("state") == 2) and flag == 2 then
			local r=v:get("questkill");
			v:set("state",1);
			menu = string.gsub(menu_247_6, "#name#", kill_npc_list[r][1]);
			menu = 	string.gsub(menu, "#npc#", kill_npc_list[r][2]);
			show_dialog(npc, menu);
			sys(player, 1, "接受了该任务");			
			npc:refresh();
			return 1;
		end
	
		if( v:get("state") == 2) and flag == 3 then
			local r=v:get("questobject");
			v:set("state",1);
			menu = string.gsub(menu_247_4, "#name#", get_item_list[r][1]);	
			menu = 	string.gsub(menu, "#id#", get_item_list[r][2]);
			show_dialog(npc, menu);
			sys(player, 1, "接受了该任务");			
			npc:refresh();
			return 1;
		end
		
		if( v:get("state") == 1) and type == 3 and flag == 8 then
			local r=v:get("questobject");
			v:set("state",1);
			menu = string.gsub(menu_247_4, "#name#", get_item_list[r][1]);	
			menu = 	string.gsub(menu, "#id#", get_item_list[r][2]);
			show_dialog(npc, menu);
			sys(player, 1, "接受了该任务");			
			npc:refresh();
			return 1;
		end

	  
		if( v:get("state") == 2) and flag == 13 then
			local r=v:get("questkillobject");
			v:set("state",1);
			menu = string.gsub(menu_247_23, "#name#", kill_get_list[r][1]);	
			menu = 	string.gsub(menu, "#kill#", kill_get_list[r][2]);
			menu = 	string.gsub(menu, "#item#", kill_get_list[r][3]);
			show_dialog(npc, menu);
			sys(player, 1, "接受了该任务");			
			npc:refresh();
			return 1;
		end

		print("accept2");
		player = me();
				
		local s = v:get("state");
		local type = v:get("type");
		local id = v:get("id");
		print(id);
		print(s);
		print(type);
			
		if ( v:get("state") == 1) and type == 3 and flag == 8 and player:have_ob(id, 3, 0) then
			print("accept3");
			sys(player, 1, "完成了收集物品任务");		
			player:remove_ob(id, 3, 0);
		
			print("交物品任务");
			show_dialog(npc, menu_247_11);
			local qs = v:get("finish_quests");
				if not qs then
					v:set("finish_quests", 1);
				else
					v:set("finish_quests", qs+1);
				end
		
			v:set("state", 2);
			v:set("kills", 0);
			v:set("id", 0);
			v:set("item_nums", 0);
			npc:refresh();
		
				if qs == 1 then
					sys(player, 1, "本环还有4个任务");
				end
					
				if qs == 2 then
					sys(player, 1, "本环还有3个任务");
				end
					
				if qs == 3 then
					sys(player, 1, "本环还有2个任务");
				end
					
				if qs == 4 then
					sys(player, 1, "本环还有最后1个任务");
				end
			
			
				if math.mod(qs+1, 5) == 0 then
					sys(player, 1, "完成了一个环");
					v:set("qs", 0);
					npc:refresh();
				end
			
			gain_exp(player, qs+1);
			
			player.quest.refresh(id);	
			npc:refresh();	
			return 1;
		end
	
		local s = v:get("state");
		if s == -3 then
			sys(player, 1, "完成了该任务");		
			player:add_exp(100, false, 0, 0);	
			v:set("state", -1);	
			player.quest.refresh(id);	
			npc:refresh();	
			return 1;
		end
	
	
	return 0;
end

function state_247(npc)
	player = me();
	if not player then return 0; end
	if player.charbase.level < 40 or player.charbase.level > 50 then
		return 0;
	end
		
	local v = player.quest:vars(21101);
	if not v then
		print("start");
		return Quest.START;
	end

	local s = v:get("state");
	
	if s == 1 then
		print("doing");
		return Quest.DOING;
	end

	if s == -3 then
		print("finish");
		return Quest.FINISH;
	end

	return 0;
end