range = 1
my_id = 99999
my_lv = 99999

function set_monster_id(id, lv)
	my_id = id
	my_lv = lv
end;

function event_player_move(player_id)
	player_x = API_get_player_x(player_id)
	player_y = API_get_player_y(player_id)
	player_z = API_get_player_z(player_id)
	monster_x = API_get_monster_x(my_id)
	monster_y = API_get_monster_y(my_id)
	monster_z = API_get_monster_z(my_id)
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