range = 1
my_id = 99999
my_lv = 99999

function set_monster_id(id, lv)
	my_id = id
	my_lv = lv
end;

function event_move_none_target()
	API_move_none_target(my_id)
end

function event_move_active_target(player_id)
	API_move_active_target(my_id, player_id)
end

function event_monster_attack(player_id)
	if(my_lv < 3) then
		API_normal_attack(my_id, player_id)
	else
		monster_ex = API_get_monster_ex(my_id)
		if(monster_ex >= 100) then
			API_skill_attack(my_id, player_id)
		else
			API_normal_attack(my_id, player_id)
		end
	end	
end